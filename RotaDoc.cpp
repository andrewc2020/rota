
// RotaDoc.cpp : implementation of the CRotaDoc class
//

#include "stdafx.h"
#include "CONSTANT.H"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Rota.h"
#endif

#include "RotaDoc.h"
#include "Span.h"
#include "Period.h"
#include "Timelist.h"
#include "Contract.h"
#include "Estab.h"
#include "Prdlst.h"
#include "category.h"
#include "heading.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRotaDoc

IMPLEMENT_DYNCREATE(CRotaDoc, CDocument)

BEGIN_MESSAGE_MAP(CRotaDoc, CDocument)
END_MESSAGE_MAP()


// CRotaDoc construction/destruction

CRotaDoc::CRotaDoc() noexcept : BASE_DATE(), listptr(NULL), listptr2(NULL), m_data(NULL), importptr(NULL), ptr(NULL)
{
	// TODO: add one-time construction code here
	listptr2 = (CTimelist*) new CHeading(_T("Headings"), NULL, NULL);
	listptr = new CEstab(_T("default"), NULL, listptr2, 0, 364, _T("BAXH"), 777, _T(""), 0.0);
	m_data = new CPeriodlist();
	importptr = new CObList();
	if (_putenv("TZ=GMT0") == TRUE)
	{
		AfxMessageBox(IDS_PGERR, MB_OK | MB_ICONEXCLAMATION, 0);
		exit(1);
	}
	else
	{
		_tzset();
#ifdef _DEBUG 
		//TRACE( "_daylight = %d\n", _daylight );
		//TRACE( "_timezone = %ld\n", _timezone );
		//TRACE( "_tzname[0] = %s\n", _tzname[0] );
#endif

	}



	CTime postenv(2018, 10, 9, 0, 0, 0);

	BASE_DATE = postenv;
	ptr = listptr;

}

CRotaDoc::~CRotaDoc()
{
	delete m_data;
	delete listptr2;
	delete listptr;
	delete importptr;

	//m_wsp->Close();

	//delete m_wsp;

}

BOOL CRotaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	CTimelist* temptr = NULL;

	//temptr = ((CHeading*)listptr2)->Add(listptr, 0, 364);
	//AfxMessageBox(IDS_NOWANTFILL, MB_OK, 0);
	//AddBudget();
//	assert(temptr);
	//((CHeading*)listptr2)->shareuncle();
	//((CHeading*)listptr2)->load_codes();//load shift codes from common file
	SetModifiedFlag(TRUE);

	return TRUE;
}

LRESULT CRotaDoc::AddBudget(void)
{

	LRESULT nResult(0);
	try
	{



		CTimelist* ptr = NULL;




		ptr = ((CEstab*)listptr)->AddExtraProvision(_T("Extras"),
			listptr2,
			0,
			364,
			_T("0"),
			0,
			_T(""),
			0);

		POSITION pos2 = listptr2->GetHeadPosition();

		CTimelist* ptr2 = NULL;

		while (pos2)
		{
			ptr2 = (CTimelist*)listptr2->GetAt(pos2);
			ptr2->AddAll(ptr, 0, 364);
			listptr2->GetNext(pos2);

		}//end while pos2


// set the Establishments budget to reflect position.

		((CEstab*)listptr)->SetBudget(0.0);
		((CEstab*)listptr)->SetTCSPackage(_T(""));



		ResetBudget();

	}
	catch (CUserException* e)
	{




	}
	return nResult;


}
LRESULT CRotaDoc::ResetBudget(void)
{

	/*Purpose: recalculates the budget as distributed between the contracts, vacancy factor and extra provision
	by a) clearing the current credits
	   b) recalculating the portion to be added as credits to the ExtraProvision account
	   c) crediting the portion*/

	LRESULT nResult(0);

	try
	{


		ClearBudget();

		// trigger recalc



		CObList partial_contracts;
		double not_catered_for(0.0);

		CContract* ptr = NULL;
		((CEstab*)listptr)->GetExtraProv(ptr);

		if (!ptr) { AfxThrowUserException(); }

		((CEstab*)listptr)->Get_not_catered_for(partial_contracts, not_catered_for);

		m_data->CreditConhrs((CContract*)ptr);

		// add for partial contracts

		m_data->CreditCompensator((CContract*)ptr, partial_contracts);

	}
	catch (CUserException* e)
	{

		AfxMessageBox(IDS_PGERR, MB_OK | MB_ICONEXCLAMATION, 0);
		nResult = 1;

	}
	return nResult;

}
LRESULT CRotaDoc::ClearBudget()
{

	LRESULT nResult(0);
	try
	{

		((CEstab*)listptr)->ClearBudget(m_data);




	}
	catch (CUserException* e)
	{




	}
	return nResult;
}


// CRotaDoc serialization

void CRotaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
CTime CRotaDoc::GetBaseDate(void)
{

	return BASE_DATE;


}


CTime CRotaDoc::Getnearestmonday(const CTime anydate)
{

	const int MONDAY(2);
	CTime moveable(anydate);
	UINT cnt(0);


	while (moveable.GetDayOfWeek() != MONDAY && cnt < 6)
	{
		moveable += ::ONE_DAY;
		cnt++;

	}


	return moveable;

}

void CRotaDoc::SetBaseDate(void)
{

	CTime now;
	now = now.GetCurrentTime();

	int finyear = GetFinYear(now);

	assert(finyear != 0);

	CTime fifthApril(finyear, 4, 5, 0, 0, 0);

	BASE_DATE = Getnearestmonday(fifthApril);


}

int CRotaDoc::GetFinYear(const CTime anydate)
{


	int mnth(anydate.GetMonth());
	int returnvalue(0);

	if (mnth >= 1 && mnth < 4) { returnvalue = anydate.GetYear() - 1; }

	if (mnth > 4 && mnth <= 12) { returnvalue = anydate.GetYear(); }

	if (mnth == 4) {

		if (anydate.GetDay() >= 5) { returnvalue = anydate.GetYear(); }
		else { returnvalue = anydate.GetYear() - 1; }

	}

	return returnvalue;
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CRotaDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CRotaDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CRotaDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CRotaDoc diagnostics

#ifdef _DEBUG
void CRotaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRotaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRotaDoc commands
