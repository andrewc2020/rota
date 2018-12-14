// TCS.cpp : implementation file
//

#include "stdafx.h"

#include <afxdao.h>



#include "TCS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTCSset

IMPLEMENT_DYNAMIC(CTCSset, CDaoRecordset)

CTCSset::CTCSset(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTCSset)
	m_Package = _T("");
	m_Conhrs = 0.0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CTCSset::GetDefaultDBName()
{
	return _T("C:\\\\My Programs\\Scenario Care Hours Database\\replica of scenario.mdb");
}

CString CTCSset::GetDefaultSQL()
{
	return _T("[TCS]");
}

void CTCSset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTCSset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Package]"), m_Package);
	DFX_Double(pFX, _T("[Conhrs]"), m_Conhrs);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTCSset diagnostics

#ifdef _DEBUG
void CTCSset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CTCSset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
