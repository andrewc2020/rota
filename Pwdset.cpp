// Pwdset.cpp : implementation file
//
#pragma warning(disable : 4995)

#include "stdafx.h"
#include <afxdao.h>


//#include "script1.h"
#include "pwdset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPwdset

IMPLEMENT_DYNAMIC(CPwdset, CDaoRecordset)

CPwdset::CPwdset(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPwdset)
	m_index = 0;
	m_login = _T("");
	m_oldpwd = _T("");
	m_pwd = _T("");
	m_groupindex = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
    

	m_nDefaultType = dbOpenDynaset;
}


CString CPwdset::GetDefaultDBName()
{
	return _T("pwd.mdb");
}

CString CPwdset::GetDefaultSQL()
{
	return _T("Select index, login, oldpwd, pwd, group FROM pwd");
}

void CPwdset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPwdset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[index]"), m_index);
	DFX_Text(pFX, _T("[login]"), m_login);
	DFX_Text(pFX, _T("[oldpwd]"), m_oldpwd);
	DFX_Text(pFX, _T("[pwd]"), m_pwd);
	DFX_Long(pFX, _T("[group]"), m_groupindex);
	//}}AFX_FIELD_MAP
	
}

/////////////////////////////////////////////////////////////////////////////
// CPwdset diagnostics

#ifdef _DEBUG
void CPwdset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CPwdset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG


