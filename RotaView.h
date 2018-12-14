
// RotaView.h : interface of the CRotaView class
//

#pragma once


class CRotaView : public CView
{
protected: // create from serialization only
	CRotaView() noexcept;
	DECLARE_DYNCREATE(CRotaView)

// Attributes
public:
	CRotaDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CRotaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RotaView.cpp
inline CRotaDoc* CRotaView::GetDocument() const
   { return reinterpret_cast<CRotaDoc*>(m_pDocument); }
#endif

