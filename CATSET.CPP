// catset.cpp : implementation file
//

#include "stdafx.h"
#pragma warning(disable : 4995)
//#include "centool8.h"
#include <afxdao.h>
#include "catset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCatset

IMPLEMENT_DYNAMIC(CCatset, CDaoRecordset)

CCatset::CCatset(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCatset)
	m_Lev3ID = 0;
	m_Lev2 = _T("");
	m_Level2_Name = _T("");
	m_Level3_Name = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	
	
	
}

CCatset::~CCatset()

{




}


CString CCatset::GetDefaultConnect()
{
	return _T("C:\\My Documents\\Replica of scenario.mdb");
}

CString CCatset::GetDefaultSQL()
{
   
	
	
	CString sql("SELECT Level3.Lev3ID, Level2.Lev2, Level2.Lev2_Name, Level3.Lev3_Name");
	sql += " FROM Level3 Level3 , Level2 Level2";
	sql += " WHERE Level3.Lev3ID = Level2.Lev3frn";
	sql += " ORDER BY Level3.Lev3ID"; 



	return sql;
}

void CCatset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCatset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("Lev3ID"), m_Lev3ID);
	DFX_Text(pFX, _T("Lev2"), m_Lev2);
	DFX_Text(pFX, _T("Lev2_Name"), m_Level2_Name);
	DFX_Text(pFX, _T("Lev3_Name"), m_Level3_Name);
	//}}AFX_FIELD_MAP
	


}

/////////////////////////////////////////////////////////////////////////////
// CCatset diagnostics

#ifdef _DEBUG
void CCatset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CCatset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
