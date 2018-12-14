// sodialog.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSOdialog dialog



class CTimelist;



class CSOdialog : public CDialog
{   

private:
	BOOL IsClearWeeks(void);
	void ClearAllCheckboxes(void);
	BOOL IsWithinContractualPeriod(void);
	BOOL IsValidInstruction(void);

/*enum weekdays { monday,
				tuesday,
				wednesday,
				thursday ,
				friday ,
				saturday,
				sunday}; */
weekdays m_day;

void Refresh(void);
LRESULT Clashes(CSpan*, const weekdays);
void fillcombo(void);

void EnableScrollBars(const BOOL verdict);
void EnableCurrentWeek(const BOOL verdict);
void EnableCheckboxes(const UINT mode);
void SetCheckboxes(void);
// Construction
public:
	CSOdialog(CWnd* pParent = NULL);	// standard constructor
	CSOdialog(const CTime basedate,CWnd* pParent /*=NULL*/);
	CSOdialog::~CSOdialog();
   CTime from;
   enum {Add,Edit} whichtitle;
   int nMin;
   int nMax;
   int from_position;
   int to_position;
   long weekstart;
   CTimelist* m_parent;
   CPeriod* m_original;
   BOOL m_freq;
   CObArray* m_dayarray;
   CBitvector* m_bitvector;
   CBitvector* m_drpvector;
// Dialog Data
	//{{AFX_DATA(CSOdialog)
	enum { IDD = IDD_DIALOG5 };
	CComboBox	m_codebox;
	int		m_am;
	BOOL	m_fixed;
	int		m_starthrs;
	int		m_startmins;
	int		m_durhrs;
	int		m_durmins;
	BOOL	m_check1;
	BOOL	m_check2;
	BOOL	m_check3;
	BOOL	m_check4;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSOdialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnOneoff();
	afx_msg void OnWeekly();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnEditchangeCodebox();
	afx_msg void OnEditupdateCodebox();
	afx_msg void OnSelchangeCodebox();
	afx_msg void OnAdcodebtn();
	afx_msg void OnDelcode();
	afx_msg void OnHelp();
	afx_msg void OnSetfocusMon();
	afx_msg void OnSetfocusTue();
	afx_msg void OnSetfocusWed();
	afx_msg void OnSetfocusThu();
	afx_msg void OnSetfocusFri();
	afx_msg void OnSetfocusSat();
	afx_msg void OnSetfocusSun();
	afx_msg void OnNonstan();
	afx_msg void OnUpdateSthrs();
	afx_msg void OnUpdateStmins();
	afx_msg void OnUpdateDurhrs();
	afx_msg void OnUpdateDurmns();
	afx_msg void OnUpdateMon();
	afx_msg void OnDrp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
