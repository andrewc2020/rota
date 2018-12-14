#if !defined(AFX_TCS_H__05FB1DA0_91F3_11D3_87EC_00104BA41D62__INCLUDED_)
#define AFX_TCS_H__05FB1DA0_91F3_11D3_87EC_00104BA41D62__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TCS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTCSset DAO recordset
#pragma warning(disable : 4995)

class CTCSset : public CDaoRecordset
{
public:
	CTCSset(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTCSset)

// Field/Param Data
	//{{AFX_FIELD(CTCSset, CDaoRecordset)
	CString	m_Package;
	double	m_Conhrs;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCSset)
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

#endif // !defined(AFX_TCS_H__05FB1DA0_91F3_11D3_87EC_00104BA41D62__INCLUDED_)
