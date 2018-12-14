
// RotaView.h : interface of the CRotaView class
//
#pragma warning(disable : 4995)
#pragma once

class CPeriod;
class CRotaDoc;
class Rowbuilder;
class CCalendar;
class CDaoWorkspace;



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
	void fontheight(int& wt, CDC* pDC); // relay call to rowbuilder for font height
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void DrawMe(CPeriod*, CRect&, CDC*, CView*);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL setshowing(const UINT); //used by calendar only 
	void getshowing(UINT&);
	virtual void OnInitialUpdate(void);
	virtual void OnUpdate(CView*, LPARAM, CObject*);
	void setlongformat(const BOOL);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	CScrollBar* m_pVscroll;

// Implementation
public:
	virtual ~CRotaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo*);
	void OnPrepareDC(CDC* pDC); // called by objects in turn
private:
	/* settings remembered for display and printing service */
	CCalendar* calendar;
	CObList* m_rowlist;
	CPeriod* m_toplist; // view's reference to users data selection 
	CPeriod* pclicked; //used for opening dialogs, and exploration
	BOOL mbCaptured;

	const enum FormatOptions { duration, startfinish, blockgraph };
	Rowbuilder* mp_rowstyle; //stores current row setting 
	
	CMapWordToOb* format_row_map;
	CMapWordToOb* format_option;
	class Format_state* pFormat_state;
	void set_format_options(void);
protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFormatRowstyleShallow();
	afx_msg void OnViewByitem();
	afx_msg void OnFormatTimecodes();
public:
	CDaoWorkspace* GetWorkspace(void);
	virtual UINT GetCalendarState(void);
	CCalendar* getcalendarptr(void);
	afx_msg void OnNavigate();
};

#ifndef _DEBUG  // debug version in RotaView.cpp
inline CRotaDoc* CRotaView::GetDocument() const
   { return reinterpret_cast<CRotaDoc*>(m_pDocument); }
#endif

