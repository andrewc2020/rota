// navdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNavdlg dialog
class CScrollbar;
class CTimelist;
class CNavdlg : public CDialog
{
// Construction
private: 

BOOL Fill_listbox(CTimelist*);
void 	setbackup(CTimelist*);
void SetTitle(CTimelist*);
public:
	CNavdlg(CTimelist* pPeg = NULL);	//  constructor
	   
   CTimelist* m_peg;
   CString titlestring; 
// Dialog Data
	//{{AFX_DATA(CNavdlg)
	enum { IDD = IDD_DIALOG8 };
	CListBox	m_LB;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CNavdlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeList1();
	afx_msg void OnDblclkList1();
	afx_msg void OnBackup();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
