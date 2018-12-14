// addac.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddac dialog
class CScrollbar;
class CTimelist;
class CAddac : public CDialog
{
// Construction
private: 
	int remember_to_pos;
	int remember_from_pos;

BOOL Fill_listbox(CObList*);

public:
	CAddac(CWnd* pParent = NULL);	// standard constructor
	CAddac(const CTime,CWnd* pParent=NULL); 
      
   CTime from;
   CObList* m_otherptr;
   int nMin;
   int nMax;
   int from_position;
   int to_position;
   enum {Add,Edit} whichtitle;
   BOOL IsEstablishment;
   CString m_titlestring; 
// Dialog Data
	//{{AFX_DATA(CAddac)
	enum { IDD = IDD_DIALOG4 };
	CListBox	m_pLB;
	CString	m_name;
	CString	m_code;
	long m_ID;
	CString	m_package;
	double	m_conhrs;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CAddac)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
