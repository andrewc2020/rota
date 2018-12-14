// estabrec.cpp : implementation file
//

#include "stdafx.h"
#pragma warning(disable : 4995)
#include <afxdao.h>
//#include "centool8.h"

#include "estabrec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Estabrec

IMPLEMENT_DYNAMIC(Estabrec, CDaoRecordset)

Estabrec::Estabrec(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(Estabrec)
	m_Estab = _T("");
	m_Establishment = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
}


CString Estabrec::GetDefaultConnect()
{
	return _T("");
}

CString Estabrec::GetDefaultSQL()
{
	return _T("[Funded Estab]");
}

void Estabrec::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(Estabrec)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("Estab"), m_Estab);
	DFX_Text(pFX, _T("Establishment"), m_Establishment);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// Estabrec diagnostics

#ifdef _DEBUG
void Estabrec::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void Estabrec::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
