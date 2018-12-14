#include "stdafx.h"
#include "STATE.H"
#include "Format_state.h"
#include "CONSTANT.H"
#include "Span.h"
#include "Period.h"
#include "Timelist.h"
#include "RotaView.h"


/////////////////////////////////////////////////////////////////////////////
// Format_state

Format_state::Format_state(const CString longstring = _T(""), const CString shortstring = _T(""), const WORD fontwidth = 0)
	:CState(), long_formatstring(longstring), short_formatstring(shortstring), m_fontwidth(fontwidth)

{


	pCurrent_setting = &long_formatstring;


}



void Format_state::DrawMe(CPeriod* me, CRect& copybox, CDC* pDC, CView* handle)
{




}

void Format_state::longstring(const BOOL TO_LONG_FORMAT)
{

	switch (TO_LONG_FORMAT)
	{

	case TRUE:

		pCurrent_setting = &long_formatstring;

		break;

	case FALSE:

		pCurrent_setting = &short_formatstring;

		break;

	default:

		AfxMessageBox(IDS_PGERR, MB_OK, 0);

	}

}

double Format_state::Getdur(void)
{


	return 1.0;

}

void Format_state::SummaryFormat(UINT& FuncId)
{

	FuncId = ID_VIEW_FORMAT_HRS;
	//overridden in dervived classes

}



Format_state::~Format_state()
{
}


/////////////////////////////////////////////////////////////////////////////
// Format_SF (view times by start finish)
Format_SF::Format_SF(const CString longstring = _T(""), const CString shortstring = _T(""), const WORD fontwidth = 0)
	:Format_state(longstring, shortstring, fontwidth)

{

	ID = ID_VIEW_FORMAT_STARTFINISH;

}

Format_SF::~Format_SF() {};

void Format_SF::DrawMe(CPeriod* me, CRect& copybox, CDC* pDC, CView* handle)
{




	CTimeSpan finishtime(me->getstart() + me->getduration());



	CString finishstring(_T("-") + finishtime.Format(*pCurrent_setting));
	if (me->GetDRPstatus()) { finishstring += _T("*"); }

	int fontheight(2);
	((CRotaView*)handle)->fontheight(fontheight, pDC);
	int fontweight(100);

	CFont testfont;

	testfont.CreateFont(
		fontheight,
		0,
		0,
		0,
		fontweight,
		FALSE, FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,
		DEFAULT_PITCH | TMPF_TRUETYPE, _T("FF_DONTCARE")
	);


	CFont* pOldfont = (CFont*)pDC->SelectObject(&testfont);



	pDC->DrawText(
		me->getstart().Format(*pCurrent_setting) +
		finishstring,
		-1,
		copybox,
		DT_LEFT
	);

	pDC->SelectObject(pOldfont);


}

/////////////////////////////////////////////////////////////////////////////
// Format_CD (view times by Timecode if set otherwise start finish)

Format_CD::Format_CD(const CString longstring = _T(""), const CString shortstring = _T(""), const WORD fontwidth = 0)
	:Format_SF(longstring, shortstring, fontwidth)
{

	ID = ID_FORMAT_TIMECODES;

}

Format_CD::~Format_CD() {};

void Format_CD::DrawMe(CPeriod* me, CRect& copybox, CDC* pDC, CView* handle)
{

	// Shows timecodes if any set . Only works if viewbyitem.
	// menu disabled if view by category as makes no sense

	CString codestring;

	CTimelist* me_uncle = (CTimelist*)me->Getuncle();

	codestring = me_uncle->Getcode(me);



	if (codestring.Left(2) != _T("NS") && !codestring.IsEmpty()) {

		codestring = _T("     ") + codestring;


		if (me->GetDRPstatus()) { codestring += _T("*"); }

		CFont testfont;
		int wt;
		((CRotaView*)handle)->fontheight(wt, pDC);

		testfont.CreateFont(
			wt,
			0,
			0,
			0,
			FW_THIN,
			FALSE, FALSE,
			0,
			ANSI_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DRAFT_QUALITY,
			DEFAULT_PITCH | TMPF_TRUETYPE, _T("FF_DONTCARE")
		);


		CFont* pOldfont = (CFont*)pDC->SelectObject(&testfont);



		pDC->DrawText(
			codestring,
			-1,
			copybox,
			DT_TOP | DT_LEFT
		);

		pDC->SelectObject(pOldfont);


	}

	else

	{
		Format_SF::DrawMe(me, copybox, pDC, handle);
	}


}

/////////////////////////////////////////////////////////////////////////////
// Format_BL (view times as blockgraph)


Format_BL::Format_BL(const CString longstring = _T(""), const CString shortstring = _T(""), const WORD fontwidth = 0)
	:Format_state(longstring, shortstring, fontwidth)

{

	ID = ID_VIEW_FORMAT_BLOCKGRAPH;

}

Format_BL::~Format_BL() {};


void Format_BL::DrawMe(CPeriod* me, CRect& copybox, CDC* pDC, CView* handle)
{
	CClientDC dc(handle);

	if (pDC->IsPrinting())
	{

		pDC->InvertRect(copybox);

	}

	else

	{




		int bxwidth(copybox.Width());  // get box width (period in days)
		pDC->LPtoDP(&copybox);
		CSize sz = copybox.Size();
		dc.SetMapMode(MM_ANISOTROPIC);
		dc.SetWindowExt(1440 * bxwidth, 1000);// box width (period in minutes)
		dc.SetViewportExt(sz);
		dc.SetViewportOrg(copybox.TopLeft());


		int start = (int)(me->getstart()).GetTotalMinutes();

		int duration = (int)me->getbalance();

		duration /= 60;// seconds to minutes

		CRect fillin(start, 0, start + duration, 1000);  // fill portion of period


		CBrush nbrush(HS_DIAGCROSS, me->getcolour());

		CBrush* oldbrush = dc.SelectObject(&nbrush);

		dc.FillRect(&fillin, &nbrush);

		dc.SelectObject(oldbrush);
	}

}
