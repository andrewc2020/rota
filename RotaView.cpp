
// RotaView.cpp : implementation of the CRotaView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Rota.h"
#endif

#include "RotaDoc.h"
#include "RotaView.h"

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
END_MESSAGE_MAP()

// CRotaView construction/destruction

CRotaView::CRotaView() noexcept
{
	// TODO: add construction code here

}

CRotaView::~CRotaView()
{
}

BOOL CRotaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRotaView drawing

void CRotaView::OnDraw(CDC* /*pDC*/)
{
	CRotaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
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
#endif //_DEBUG


// CRotaView message handlers
