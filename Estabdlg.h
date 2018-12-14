// estabdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEstabdlg dialog

class CEstabdlg : public CDialog
{
// Construction
private:
CDaoDatabase* m_db;
void Cleanup();
public:
	CEstabdlg(CDaoDatabase& db, CWnd* pParent = NULL);   // standard constructor
	~CEstabdlg();
	CString m_estabID;
	CString m_estabstring;
// Dialog Data
	//{{AFX_DATA(CEstabdlg)
	enum { IDD = IDD_DIALOG12 };
	CListBox	m_LIST1;
	//}}AFX_DATA
	BOOL m_allin;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEstabdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL



// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEstabdlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeList1();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
