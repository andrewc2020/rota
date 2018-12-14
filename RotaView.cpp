
// RotaView.cpp : implementation of the CRotaView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Rota.h"
#endif
#include "CONSTANT.H"
#include "RotaDoc.h"
#include "RotaView.h"
#include "STATE.h"
#include "Format_state.h"
#include "Format_Dur.h"
#include "ROWBUILD.H"
#include "Cal1.h"
#include "Span.h"
#include "Period.h"
#include "Timelist.h"
#include "Absolute.h"
#include "NAVDLG.H"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRotaView

IMPLEMENT_DYNCREATE(CRotaView, CView)

BEGIN_MESSAGE_MAP(CRotaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FORMAT_ROWSTYLE_SHALLOW, OnFormatRowstyleShallow)
	ON_COMMAND(ID_VIEW_BYITEM, OnViewByitem)
	ON_COMMAND(ID_FORMAT_TIMECODES, OnFormatTimecodes)
	ON_COMMAND(ID_NAVIGATE, OnNavigate)
END_MESSAGE_MAP()

// CRotaView construction/destruction

CRotaView::CRotaView() noexcept : m_toplist(NULL), pclicked(NULL), 
mbCaptured(FALSE), pFormat_state(NULL),format_option(NULL),
m_pVscroll(NULL),//pointer to the vertical scroll bar
mp_rowstyle(NULL), format_row_map(NULL),m_rowlist(NULL)
{
	// TODO: add construction code here
	format_option = new	CMapWordToOb;
	format_row_map = new CMapWordToOb;
	m_rowlist = new CObList();

	set_format_options();
	

}

CRotaView::~CRotaView()
{
	delete calendar;
	delete m_rowlist;

	CObject* ptr; WORD id(0);


	/*empty maps*/

	POSITION pos = format_option->GetStartPosition();

	while (!format_option->IsEmpty())
	{

		format_option->GetNextAssoc(pos, id, ptr);
		format_option->RemoveKey(id);

		delete ptr;
	}



	delete format_option;


	pos = format_row_map->GetStartPosition();

	while (!format_row_map->IsEmpty())
	{

		format_row_map->GetNextAssoc(pos, id, ptr);
		format_row_map->RemoveKey(id);

		delete ptr;
	}


	delete format_row_map;

}

BOOL CRotaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRotaView drawing

/////////////////////////////////////////////////////////////////////////////
// CRotaview drawing

void CRotaView::set_format_options(void)
{

	CObject* ptr;

	

	ptr = new Format_Dur(_T("%.2f"), _T("%.0f"), 0);

	pFormat_state = (Format_state*)ptr;

	format_option->SetAt(ID_VIEW_FORMAT_HRS, ptr);

	/*register standard day formats  */

		//7.5

	ptr = new Format_Dur_Sevenhalf( _T("%.2f"), _T("%.0f"), 0);

	pFormat_state = (Format_state*)ptr;

	format_option->SetAt(ID_FORMAT_DUR_SEVENHALF, ptr);

	//7.2

	ptr = new Format_Dur_SevenTwelve( _T("%.2f"), _T("%.0f"), 0);

	pFormat_state = (Format_state*)ptr;

	format_option->SetAt(ID_FORMAT_DUR_SEVENTWELVE, ptr);



	//7.4

	ptr = new Format_Dur_SevenTwentyfour(_T("%.2f"), _T("%.0f") , 0);

	pFormat_state = (Format_state*)ptr;

	format_option->SetAt(ID_FORMAT_DUR_SEVENTWENTYFOUR, ptr);


	//7.6

	ptr = new Format_Dur_SevenThirtysix(_T("%.2f"), _T("%.0f"), 0);

	pFormat_state = (Format_state*)ptr;

	format_option->SetAt(ID_FORMAT_DUR_SEVENTHIRTYSIX, ptr);



	/*register start finish format  */

	ptr = new Format_SF( _T("%H:%M") , _T("%H:%M"), 0);


	format_option->SetAt(ID_VIEW_FORMAT_STARTFINISH, ptr);

	/*register timecodes format  */

	ptr = new Format_CD(_T("%H:%M") , _T("%H:%M") , 0);


	format_option->SetAt(ID_FORMAT_TIMECODES, ptr);

	/*register blockgraph format  */

	ptr = new Format_BL(_T(""), _T(""), 0);

	format_option->SetAt(ID_VIEW_FORMAT_BLOCKGRAPH, ptr);

	/* register shallow row style format */

	ptr = new Shallow_Rowbuilder();

	format_row_map->SetAt(ID_FORMAT_ROWSTYLE_SHALLOW, ptr);


	/* register deep row style format */

	ptr = new Deep_Rowbuilder();

	format_row_map->SetAt(ID_FORMAT_ROWSTYLE_DEEP, ptr);



}

void CRotaView::setlongformat(const BOOL Is_longformat = TRUE)
{
	CObject* ptr; WORD id(0); Format_state* p_state = NULL;

	POSITION pos = format_option->GetStartPosition();

	while (pos)
	{

		format_option->GetNextAssoc(pos, id, ptr);
		p_state = (Format_state*)ptr;

		p_state->longstring(Is_longformat);


	}


}

void CRotaView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{




	OnPrepareDC(pDC);

}

void CRotaView::OnPrepareDC(CDC* pDC)
{

	CRect rect;
	GetClientRect(rect);

	CSize Totalsize(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(Totalsize);
	pDC->SetWindowExt(54, 100); //was 55
	pDC->SetViewportOrg(0, 0);


	/* reset display variables which will be overridden in cases */

	calendar->OnPrepareDC(pDC);




}

void CRotaView::OnDraw(CDC* pDC)
{
	try
	{
	CRotaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	

	m_rowlist->RemoveAll();

	if (!m_toplist) { AfxThrowUserException(); }

	CTimelist* ptr = (CTimelist*)m_toplist;




	SetScrollRange(SB_VERT, 0, ptr->getdisplaycount(), TRUE);
	// sets scrollbar to number to display

	CRect box;

	GetClientRect(&box);
	ptr->setbox(&box);



	ptr->displayall(calendar->GetBaseDate(), calendar->GetCurrentPeriod(), pDC, this);


	calendar->display(this, pDC, ptr, pDoc->m_data);






	// TODO: add draw code for native data here
}//end try
catch(CUserException* e)
{

	AfxMessageBox(IDS_PGERR, MB_OK | MB_ICONEXCLAMATION, 0);


}

}

void CRotaView::DrawMe(CPeriod* me, CRect& copybox, CDC* pDC, CView* handle)
{

	/* The device context must be shaped by two user defined states of the current
	 view: the calendar state and the format menu. These are accessed through
	 the view's data which is configured by the combinations of
	 states resulting from the menu choices eg ID_FOURWEEK &&  ID_FINISH_START.
	 The Format variables are set on command id and the states are called after
	 the commands which invoke them eg ID_START_FINISH. The state machine must also
	 take account of the current calendar state, as some string and position formats
	 must be truncated or altered for the fourweek view.The OnPrepareDC function
	 passes on print info data to the statemachine.

	*/



	try
	{

		if (!pFormat_state)
		{
			AfxThrowUserException();
		}



		pFormat_state->DrawMe(me, copybox, pDC, handle);

		pDC->SetTextColor(::BLACK);

	}
	catch (CUserException* e)
	{

		AfxMessageBox(IDS_PGERR, MB_OK | MB_ICONEXCLAMATION, 0);

	}




}

CCalendar* CRotaView::getcalendarptr(void)
{


	return calendar;

}

UINT CRotaView::GetCalendarState(void)
{


	return calendar->Getstate();

}


// CRotaView printing

BOOL CRotaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRotaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRotaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CRotaView diagnostics

#ifdef _DEBUG
void CRotaView::AssertValid() const
{
	CView::AssertValid();
}

void CRotaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRotaDoc* CRotaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRotaDoc)));
	return (CRotaDoc*)m_pDocument;
}


void CRotaView::getshowing(UINT& placeholder)
{

	placeholder = pFormat_state->Getstate();




}

BOOL CRotaView::setshowing(const UINT changeto)
{


	CObject* ptr;

	format_option->Lookup(changeto, ptr);

	pFormat_state = (Format_state*)ptr;

	assert(pFormat_state->Getstate() == changeto);

	return pFormat_state->Getstate() == changeto;

}

void CRotaView::fontheight(int& ht, CDC* pDC)
{

	if (pDC->IsPrinting())
	{
		ht = 0;
	}
	else
	{

		mp_rowstyle->fontheight(ht);

	}


}

/////////////////////////////////////////////////////////////////////////////
// CRotaview message handlers
void CRotaView::OnInitialUpdate(void)
{
	CView::OnInitialUpdate();

	CRotaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	calendar = new CCalendar(pDoc->GetBaseDate());
	OnFormatRowstyleShallow();
	OnViewByitem();
	OnFormatTimecodes();
	setlongformat(TRUE);
	SetScrollPos(SB_VERT, 0, FALSE);


}

void CRotaView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CRotaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	/*if (lHint == 999)
	{

		calendar->ResetBasedate(pDoc->GetBaseDate());


	}*/

	InvalidateRect(NULL, TRUE);


}
void CRotaView::OnFormatRowstyleShallow()
{
	// TODO: Add your command handler code here

	CObject* ptr;

	format_row_map->Lookup(ID_FORMAT_ROWSTYLE_SHALLOW, ptr);

	mp_rowstyle = (Rowbuilder*)ptr;

	assert(mp_rowstyle->Getstate() == ID_FORMAT_ROWSTYLE_SHALLOW);

	CRect lp, border;
	GetClientRect(lp);
	border.SetRect(0, 0, lp.BottomRight().x, calendar->GetContentOrg().y);
	lp.SubtractRect(lp, border);

	InvalidateRect(lp, TRUE);

}
void CRotaView::OnFormatTimecodes()
{
	// TODO: Add your command handler code here

	CObject* ptr;

	format_option->Lookup(ID_FORMAT_TIMECODES, ptr);

	pFormat_state = (Format_state*)ptr;

	assert(pFormat_state->Getstate() == ID_FORMAT_TIMECODES);

	CRect lp, border;
	GetClientRect(lp);
	border.SetRect(0, 0, calendar->GetContentOrg().x, lp.BottomRight().y);
	lp.SubtractRect(lp, border);

	InvalidateRect(lp, TRUE);

	//InvalidateRect(NULL, TRUE);

}
void CRotaView::OnViewByitem()
{
	// TODO: Add your command handler code here 
	TRY
	{
	CRotaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);



	pclicked = NULL;
	m_toplist = (CPeriod*) pDoc->listptr;
	if (!m_toplist) { AfxThrowUserException(); }

	SetScrollPos(SB_VERT,0,FALSE);




	InvalidateRect(NULL,TRUE);
	}
		CATCH(CUserException, e)
	{


		AfxMessageBox(IDS_PGERR, MB_OK | MB_ICONEXCLAMATION, 0);


	}
	END_CATCH


}
void CRotaView::OnNavigate()
{
	// TODO: Add your command handler code here

	CRotaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	TRY  // diagnostics
	{

	if (!m_toplist || !pclicked) { AfxThrowUserException(); }

	CTimelist* ptr = (CTimelist*)pclicked;


	CNavdlg dlg((CTimelist*)ptr);



	dlg.titlestring = "Scenario Navigator    ";


	if (dlg.DoModal() == IDOK)
	{


	if (!dlg.m_peg) { AfxThrowUserException(); }



	m_toplist = dlg.m_peg;


	SetScrollPos(SB_VERT,0,FALSE);

	InvalidateRect(NULL, TRUE);

	pclicked = NULL;

	}//end if do Modal



	}


		CATCH(CUserException, e)
	{

		AfxMessageBox(IDS_PGERR, MB_OK | MB_ICONEXCLAMATION, 0);

	}


	END_CATCH



}
#endif //_DEBUG


// CRotaView message handlers



