// conset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConset recordset
#pragma warning(disable : 4995)

class CConset : public CDaoRecordset
{
public:
	CConset(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CConset)
	
	

// Field/Param Data
	//{{AFX_FIELD(CConset, CDaoRecordset)
	CString m_FRNM1;
	CString	m_EMPLOYEE_N;
	CString	m_Package;
	double	m_Conhrs;
	CString	m_Estabfrn;
	CString	m_ContractNo;
	long	m_IDfrn;
	COleDateTime m_Startdate;
	COleDateTime m_Termdate;
	//}}AFX_FIELD

	CString m_estabParam;
	CTime m_endrotaParam;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConset)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
