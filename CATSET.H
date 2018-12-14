// catset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCatset recordset
#pragma warning(disable : 4995)
class CCatset : public CDaoRecordset
{
public:
	CCatset(CDaoDatabase* pDatabase = NULL);
	~CCatset();
	DECLARE_DYNAMIC(CCatset)

// Field/Param Data
	//{{AFX_FIELD(CCatset, CDaoRecordset)
	long	m_Lev3ID;
	CString	m_Lev2;
	CString	m_Level2_Name;
	CString	m_Level3_Name;
	//}}AFX_FIELD

 
 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatset)
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
