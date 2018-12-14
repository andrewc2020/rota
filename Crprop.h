// crprop.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCrprop dialog

class CCrprop : public CDialog
{
// Construction
public:
	CCrprop(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCrprop)
	enum { IDD = IDD_DIALOG10 };
	BOOL	m_mon;
	BOOL	m_tue;
	BOOL	m_wed;
	BOOL	m_thu;
	BOOL	m_fri;
	BOOL	m_sat;
	BOOL	m_sun;
	int		m_starthrs;
	int		m_startmins;
	int		m_durhrs;
	int		m_durmins;
	CString	m_total;
	CString	m_perwk;
	//}}AFX_DATA

   int nMin;
   int nMax;
   int from_position;
   int to_position;
   CTime from;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrprop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCrprop)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	void OnHelp();
	afx_msg void OnHelpbtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
