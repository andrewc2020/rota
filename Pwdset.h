#if !defined(AFX_PWDSET_H__0FB5ABA3_404D_11D3_87EB_00104BA41D62__INCLUDED_)
#define AFX_PWDSET_H__0FB5ABA3_404D_11D3_87EB_00104BA41D62__INCLUDED_
#pragma warning(disable : 4995)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Pwdset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPwdset DAO recordset
class CDaoRecordset;


class CPwdset : public CDaoRecordset
{
public:
	
	
	
	CPwdset(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPwdset)

// Field/Param Data
	//{{AFX_FIELD(CPwdset, CDaoRecordset)
	long	m_index;
	CString	m_login;
	CString	m_oldpwd;
	CString	m_pwd;
	long	m_groupindex;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPwdset)
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

#endif // !defined(AFX_PWDSET_H__0FB5ABA3_404D_11D3_87EB_00104BA41D62__INCLUDED_)
