// conset.cpp : implementation file
//

#include "stdafx.h"
#pragma warning(disable : 4996)
#pragma warning(disable : 4995)
//#include "centool8.h"
#include <afxdao.h>

#include "conset.h"
//#include "quotes.c"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConset

IMPLEMENT_DYNAMIC(CConset, CDaoRecordset)

CConset::CConset(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CConset)
	m_FRNM1 = _T("");
	m_EMPLOYEE_N = _T("");
	m_Package = _T("");
	m_Conhrs = 0;
	m_Estabfrn = "";
	m_ContractNo = _T("");
	m_IDfrn = 0;
	m_Startdate;
	m_Termdate;
	m_nFields = 9;
	//}}AFX_FIELD_INIT

	
	m_estabParam = _T("");
	m_nParams = 1;
}




CString CConset::GetDefaultConnect()
{
	return _T("C:\\My Documents\\Replica of scenario.mdb");
}

CString CConset::GetDefaultSQL()
{
      
 


   CString sql("PARAMETERS [?] TEXT; "); 
   sql += "SELECT FRNM1, EMPLOYEE_N, Package, Hrs, Estabfrn, Budgetline,";
   sql += " [Pers Number], Startdate," ;
   sql += " IIf(Not IsDate([Termdate]),#";
   sql += m_endrotaParam.Format("%m/%d/%Y");
   sql += "#,[Termdate]) AS Termcalc " ;
   sql += "    FROM staffqryparam";
   sql += " WHERE Estabfrn= [?] "; 
		
		
	    
                          
		
	//return _T(sql);
   return sql;
}

void CConset::DoFieldExchange(CDaoFieldExchange* pFX)
{ 

	//{{AFX_FIELD_MAP(CConset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("FRNM1"), m_FRNM1);
	DFX_Text(pFX, _T("EMPLOYEE_N"), m_EMPLOYEE_N);
	DFX_Text(pFX, _T("Package"), m_Package);
	DFX_Double(pFX, _T("Hrs"), m_Conhrs);
	DFX_Text(pFX, _T("Estabfrn"), m_Estabfrn);
	DFX_Text(pFX, _T("Budgetline"), m_ContractNo);
	DFX_Long(pFX, _T("[Pers Number]"), m_IDfrn);
	DFX_DateTime(pFX, _T("Startdate"), m_Startdate);
	DFX_DateTime(pFX, _T("Termcalc"), m_Termdate);
	//}}AFX_FIELD_MAP

	pFX->SetFieldType( CDaoFieldExchange::param );
	DFX_Text(pFX, _T("[?]"), m_estabParam);
	//SetParamValue( 1, COleVariant (m_estabParam,VT_BSTRT ) );

	
	
}

/////////////////////////////////////////////////////////////////////////////
// CConset diagnostics

#ifdef _DEBUG
void CConset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CConset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
