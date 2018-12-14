#if !defined(AFX_LOG2_H__4B78C343_855B_11D3_87EB_00104BA41D62__INCLUDED_)
#define AFX_LOG2_H__4B78C343_855B_11D3_87EB_00104BA41D62__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Log2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLog2 DAO recordset
#pragma warning(disable : 4995)

class CDaoRecordset;
class CLog : public CDaoRecordset
{
public:
	BOOL CanAppend(void);
	CLog(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLog)

// Field/Param Data
	//{{AFX_FIELD(CLog, CDaoRecordset)
	short	m_auth;
	CString	m_budgetlinefrn;
	long	m_contractnofrn;
	CString	m_date_onstr;
	CString	m_estabfrn;
	short	m_rota;
	CString	m_shiftcodefrn;
	CString	m_time_offstr;
	CString	m_time_onstr;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLog2)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOG2_H__4B78C343_855B_11D3_87EB_00104BA41D62__INCLUDED_)
