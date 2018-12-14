#include "stdafx.h"
#include "CONSTANT.H"
#include "STATE.H"
#include "Format_state.h"
#include "Format_Dur.h"
#include "Span.h"
#include "Period.h"
#include "Timelist.h"
#include <sstream>




/////////////////////////////////////////////////////////////////////////////
// Format_Dur (view times by duration)

Format_Dur::Format_Dur(const CString longstring = _T(""), const CString shortstring = _T(""), const WORD fontwidth = 0)
	:Format_state(longstring, shortstring, fontwidth)
{

	ID = ID_VIEW_FORMAT_HRS;

}

Format_Dur::~Format_Dur() {};

void Format_Dur::DrawMe(CPeriod* me, CRect& copybox, CDC* pDC, CView* handle)
{
	int fontheight(2);
	int fontweight(100);



	if (pDC->IsPrinting())
	{

		fontheight = fontweight = 0;


	}

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
		DEFAULT_QUALITY,
		DEFAULT_PITCH | TMPF_TRUETYPE, _T("FF_DONTCARE")
	);


	CFont* pOldfont = (CFont*)pDC->SelectObject(&testfont);




	long totalsecs = me->getbalance();
	char balancestring[10];
	


	double interval = 60.00F;

	double mins(totalsecs / interval);

	double hrs(mins / interval);

	char buff[100];
	snprintf(buff, sizeof(buff), "%f", hrs);
	std::string buffAsStdStr = buff;
	CString s(buff);


	pDC->DrawText(
		s,
		-1,
		copybox,
		DT_LEFT
	);



	pDC->SelectObject(pOldfont);
}

void Format_Dur::SummaryFormat(UINT& FuncId)
{

	FuncId = ID_VIEW_FORMAT_HRS;


}


/////////////////////////////////////////////////////////////////////////////
// Format_Dur_Sevenhalf (Duration in standard days for a 37.5 week )

Format_Dur_Sevenhalf::Format_Dur_Sevenhalf(const CString longstring = _T(""), const CString shortstring = _T(""), const WORD fontwidth = 0)
	: Format_Dur(longstring, shortstring, fontwidth)

{

	ID = ID_FORMAT_DUR_SEVENHALF;

}

Format_Dur_Sevenhalf::~Format_Dur_Sevenhalf() {};

void Format_Dur_Sevenhalf::DrawMe(CPeriod* me, CRect& copybox, CDC* pDC, CView* handle)
{
	int fontheight(2);
	int fontweight(100);

	if (pDC->IsPrinting())
	{

		fontheight = fontweight = 0;


	}

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
		DEFAULT_QUALITY,
		DEFAULT_PITCH | TMPF_TRUETYPE, _T("FF_DONTCARE")
	);


	CFont* pOldfont = (CFont*)pDC->SelectObject(&testfont);

	long totalsecs = me->getbalance();
	char balancestring[10];


	double interval = 60.00F;

	double mins(totalsecs / interval);

	double hrs(mins / interval);

	double days(hrs / 7.5);

	char buff[100];
	snprintf(buff, sizeof(buff), "%f", days);
	std::string buffAsStdStr = buff;
	CString s(buff);
	
	
	

	pDC->DrawText(
		s,
		-1,
		copybox,
		DT_LEFT
	);

	pDC->SelectObject(pOldfont);


}

double Format_Dur_Sevenhalf::Getdur(void)
{


	return 7.5;

}

void Format_Dur_Sevenhalf::SummaryFormat(UINT& FuncId)
{

	FuncId = ID;


}


/////////////////////////////////////////////////////////////////////////////
// Format_Dur_Day_SevenTwelve (view standard day 7.2)
Format_Dur_SevenTwelve::Format_Dur_SevenTwelve(const CString longstring = _T(""), const CString shortstring = _T(""), const WORD fontwidth = 0)
	:Format_Dur(longstring, shortstring, fontwidth)

{

	ID = ID_FORMAT_DUR_SEVENTWELVE;

}

Format_Dur_SevenTwelve::~Format_Dur_SevenTwelve() {};

void Format_Dur_SevenTwelve::DrawMe(CPeriod* me, CRect& copybox, CDC* pDC, CView* handle)
{
	int fontheight(2);
	int fontweight(100);

	if (pDC->IsPrinting())
	{

		fontheight = fontweight = 0;


	}

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
		DEFAULT_QUALITY,
		DEFAULT_PITCH | TMPF_TRUETYPE, _T("FF_SWISS")
	);


	CFont* pOldfont = (CFont*)pDC->SelectObject(&testfont);

	long totalsecs = me->getbalance();
	char balancestring[10];


	double interval = 60.00F;

	double mins(totalsecs / interval);

	double hrs(mins / interval);

	double days(hrs / 7.2);

	//sprintf(balancestring, pCurrent_setting->UnlockBuffer, days);
	char buff[100];
	snprintf(buff, sizeof(buff), "%f", days);
	std::string buffAsStdStr = buff;
	CString s(buff);

	pDC->DrawText(
		s,
		-1,
		copybox,
		DT_LEFT
	);

	pDC->SelectObject(pOldfont);

}

double Format_Dur_SevenTwelve::Getdur(void)
{


	return 7.2;

}

void Format_Dur_SevenTwelve::SummaryFormat(UINT& FuncId)
{

	FuncId = ID;


}


/////////////////////////////////////////////////////////////////////////////
// Format_Dur_Day_SevenTwentyfour (view standard day 7.4)
Format_Dur_SevenTwentyfour::Format_Dur_SevenTwentyfour(const CString longstring = _T(""), const CString shortstring = _T(""), const WORD fontwidth = 0)
	:Format_Dur(longstring, shortstring, fontwidth)

{

	ID = ID_FORMAT_DUR_SEVENTWENTYFOUR;

}

Format_Dur_SevenTwentyfour::~Format_Dur_SevenTwentyfour() {};

void Format_Dur_SevenTwentyfour::DrawMe(CPeriod* me, CRect& copybox, CDC* pDC, CView* handle)
{
	int fontheight(2);
	int fontweight(100);

	if (pDC->IsPrinting())
	{

		fontheight = fontweight = 0;


	}

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
		DEFAULT_QUALITY,
		DEFAULT_PITCH | TMPF_TRUETYPE, _T("FF_SWISS")
	);


	CFont* pOldfont = (CFont*)pDC->SelectObject(&testfont);

	long totalsecs = me->getbalance();
	char balancestring[10];


	double interval = 60.00F;

	double mins(totalsecs / interval);

	double hrs(mins / interval);

	double days(hrs / 7.4);

	//sprintf(balancestring, pCurrent_setting->UnlockBuffer, days);
	char buff[100];
	snprintf(buff, sizeof(buff), "%f", days);
	std::string buffAsStdStr = buff;
	CString s(buff);

	pDC->DrawText(
		s,
		-1,
		copybox,
		DT_LEFT
	);

	pDC->SelectObject(pOldfont);

}

double Format_Dur_SevenTwentyfour::Getdur(void)
{


	return 7.4;

}

void Format_Dur_SevenTwentyfour::SummaryFormat(UINT& FuncId)
{

	FuncId = ID;


}

/////////////////////////////////////////////////////////////////////////////
// Format_Dur_Day_SevenThirtysix (view standard day 7.6)
Format_Dur_SevenThirtysix::Format_Dur_SevenThirtysix(const CString longstring = _T(""), const CString shortstring = _T(""), const WORD fontwidth = 0)
	:Format_Dur(longstring, shortstring, fontwidth)

{

	ID = ID_FORMAT_DUR_SEVENTHIRTYSIX;

}

Format_Dur_SevenThirtysix::~Format_Dur_SevenThirtysix() {};

void Format_Dur_SevenThirtysix::DrawMe(CPeriod* me, CRect& copybox, CDC* pDC, CView* handle)
{
	int fontheight(2);
	int fontweight(100);

	if (pDC->IsPrinting())
	{

		fontheight = fontweight = 0;


	}

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
		DEFAULT_QUALITY,
		DEFAULT_PITCH | TMPF_TRUETYPE, _T("FF_SWISS")
	);


	CFont* pOldfont = (CFont*)pDC->SelectObject(&testfont);

	long totalsecs = me->getbalance();
	char balancestring[10];


	double interval = 60.00F;

	double mins(totalsecs / interval);

	double hrs(mins / interval);

	double days(hrs / 7.6);

	

	char buff[100];
	snprintf(buff, sizeof(buff), "%f", days);
	std::string buffAsStdStr = buff;
	CString s(buff);

	//sprintf(balancestring, pCurrent_setting->UnlockBuffer, days);

	pDC->DrawText(
		s,
		-1,
		copybox,
		DT_LEFT
	);

	pDC->SelectObject(pOldfont);

}

double Format_Dur_SevenThirtysix::Getdur(void)
{


	return 7.6;

}

void Format_Dur_SevenThirtysix::SummaryFormat(UINT& FuncId)
{

	FuncId = ID;


}



