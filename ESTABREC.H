// estabrec.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Estabrec recordset
#pragma warning(disable : 4995)

class Estabrec : public CDaoRecordset
{
public:
	Estabrec(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Estabrec)

// Field/Param Data
	//{{AFX_FIELD(Estabrec, CDaoRecordset)
	CString	m_Estab;
	CString	m_Establishment;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Estabrec)
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
