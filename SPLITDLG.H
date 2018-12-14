// splitdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplitdlg dialog
class CAbsolutePeriod;

class CSplitdlg : public CDialog
{
// Construction

private:

void Refresh(void);

public:
	CSplitdlg(CWnd* pParent = NULL);	// standard constructor
	// Dialog Data
	//{{AFX_DATA(CSplitdlg)
	enum { IDD = IDD_DIALOG3 };
	CButton	m_sum;
	double	m_exhrs;
	double	m_newhrs;
	double	m_currweeks;
	double	m_earweeks;
	double	m_curtot;
	double	m_eartot;
	double	m_eartot2;
	//}}AFX_DATA
	
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSplitdlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnUpdateNewhrs();
	afx_msg void OnWeeks();
	afx_msg void OnDays();
	afx_msg void OnUpdateEarwk();
	afx_msg void OnChangeNewhrs();
	afx_msg void OnButton2();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
