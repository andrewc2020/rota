// subbankd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubBankdlg dialog

class CSubBankdlg : public CDialog
{

private:
	void EnableOK(void);



CDaoDatabase* m_db;
void Cleanup(void);
void FillExist(void);

// Construction
public:
	CSubBankdlg(CWnd* pParent = NULL);   // standard constructor
	CSubBankdlg(CDaoDatabase& db,CObList*, CWnd* pParent = NULL);   // standard constructor
	~CSubBankdlg(void);
	CMapPtrToPtr m_map;
	CObList* m_existptr;
	CTime m_endrota;

// Dialog Data
	//{{AFX_DATA(CSubBankdlg)
	enum { IDD = IDD_DIALOG18 };
	CButton	m_reset;
	CListBox	m_LIST3;
	CListBox	m_LIST2;
	CListBox	m_LIST1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubBankdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubBankdlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList1();
	afx_msg void OnButton1();
	afx_msg void OnSelchangeList3();
	afx_msg void OnButton3();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
