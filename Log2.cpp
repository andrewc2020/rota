// log2.cpp : implementation file
//

#include "stdafx.h"
#pragma warning(disable : 4995)
#include <afxdao.h>



//#include "centool8.h"

#include "log2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLog

IMPLEMENT_DYNAMIC(CLog, CDaoRecordset)

CLog::CLog(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLog)
	m_auth = 0;
	m_budgetlinefrn = _T("");
	m_contractnofrn = 0;
	m_date_onstr = _T("");
	m_estabfrn = _T("");
	m_rota = 0;
	m_shiftcodefrn = _T("");
	m_time_offstr = _T("");
	m_time_onstr = _T("");
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CLog::GetDefaultDBName()
{
	return _T("C:\\My Documents\\Replica of scenario.mdb");
}

CString CLog::GetDefaultSQL()
{
	return _T("LOG");
}

void CLog::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLog)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Short(pFX, _T("auth"), m_auth);
	DFX_Text(pFX, _T("budgetlinefrn"), m_budgetlinefrn);
	DFX_Long(pFX, _T("contractnofrn"), m_contractnofrn);
	DFX_Text(pFX, _T("date_onstr"), m_date_onstr);
	DFX_Text(pFX, _T("estabfrn"), m_estabfrn);
	DFX_Short(pFX, _T("rota"), m_rota);
	DFX_Text(pFX, _T("shiftcodefrn"), m_shiftcodefrn);
	DFX_Text(pFX, _T("time_offstr"), m_time_offstr);
	DFX_Text(pFX, _T("time_onstr"), m_time_onstr);
	//}}AFX_FIELD_MAP
}






/////////////////////////////////////////////////////////////////////////////
// CLog diagnostics

#ifdef _DEBUG
void CLog::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CLog::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG




BOOL CLog::CanAppend()
{

return CDaoRecordset::CanAppend();

}
