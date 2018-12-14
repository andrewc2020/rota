// absence.cpp : implementation file
//


#include "stdafx.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "span.h"
#include "period.h"
#include "timelist.h"
#include "assert.h"
#include "category.h"
#include "absence.h"
#include "contract.h"
#include "shift.h"
#include "regularp.h"
#include <stdio.h>
#include "util.h"
#ifndef STANDALONE
#include "workspace.h"
#endif
#include "Rota.h"
/*
#include "D:\Program Files\DevStudio\MyProjects\util.h"
#include "D:\Program Files\DevStudio\MyProjects\DBcmd\Workspace.h"
*/








#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbsence

IMPLEMENT_SERIAL(CAbsence, CCategory, 2)

CAbsence::CAbsence():CCategory()
{
 
CPeriod::setcolour(RGB(255,0,0));


}

CAbsence::CAbsence(const CString title,
						 CPeriod* prnt,
						 CPeriod* uncl):CCategory(title,(CTimelist*)prnt,
						 								(CTimelist*)uncl,_T("Abs"))
{ 

CPeriod::setcolour(RGB(255,0,0));

}

CAbsence::CAbsence(const CString title,
						 CPeriod* prnt,
						 CPeriod* uncl,
				   const CString table_id):CCategory(title,(CTimelist*)prnt,
						 								(CTimelist*)uncl, table_id)
{ 

CPeriod::setcolour(RGB(255,0,0));

}

CAbsence::~CAbsence()
{
}


/////////////////////////////////////////////////////////////////////////////
// CAbsence message handlers



CTimelist* CAbsence::Add(CString title,CTimelist* uncle,
						const long from=0,
						const long to=364,
					    const CString table_id=_T("NOLOGIN"))
{
 
CObject* ptr=NULL;
ptr =new CAbsence(title, this,uncle,table_id);
m_mainlist->AddTail(ptr);

return (CTimelist*) ptr;

}

CTimelist* CAbsence::Add(CString title,CTimelist* uncle,
										const long from=0,
										const long to=364)
{ 
CObject* ptr=NULL;
ptr =new CAbsence(title, this,uncle);
m_mainlist->AddTail(ptr);

return (CTimelist*) ptr;

}



#ifdef _DEBUG
void CAbsence::Dump(CDumpContext& dc) const
{   
    
    
	CObject::Dump(dc);
	
}
#endif //_DEBUG	 

  
BOOL CAbsence::file_codes(const BOOL storing)
{



return TRUE;

}


CString CAbsence::Getdlgcode(CSpan* pshft)
{
  if(!(pshft->getstart()==::NONE && pshft->getduration()==::NONE))
  {
  return CPeriod::Getbriefname();}
  else
  { return _T(""); }
}

CString CAbsence::Getcodestring(CSpan* sp , CComboBox& combo)
{

CString codeletter;
codeletter.Empty();
int cnt=0;

while(cnt< combo.GetCount())
{

CSpan* ptr = (CSpan*) combo.GetItemDataPtr(cnt);

if(*ptr==sp)
{

 combo.GetLBText(cnt,codeletter);
 cnt = combo.GetCount();
 }

 cnt++;

}




return codeletter;
}


BOOL CAbsence::fillbox(CComboBox*& pcombo,CPeriod* parent)
{


 //The standard day depends on the TCS
// package held by the contract concerned

// first get the package held by the person


 assert(parent!=NULL) ;

 pcombo->ResetContent();

 
CRotaApp* pApp = (CRotaApp*) AfxGetApp();
#ifndef STANDALONE
	CWorkspace*	workserver = (CWorkspace*) pApp->GetWorkspaceServer();
	
 // Get the terms and conditions of service
 // for the contract in question
	CString package;
	((CContract*)parent)->GetTCSpackage(package);
 if(workserver->fillcombo(pcombo,package)>0 || package.IsEmpty())
	{
	  pcombo->ResetContent();

	// provide a default range of 
	// standard days

	pcombo->InsertString(0,_T("7.6 - 38"));
	pcombo->SetItemDataPtr(0, new CShift(CTimeSpan(0,9,0,0),::THIRTY_EIGHT_PW,_T("38")));
 
	pcombo->InsertString(1,_T("7.5 - 37.5"));
	pcombo->SetItemDataPtr(1, new CShift(CTimeSpan(0,9,0,0),::THIRTY_SEVEN_HALF_PW,_T("37.5")));

	pcombo->InsertString(2,_T("7.4 - 37"));
	pcombo->SetItemDataPtr(2, new CShift(CTimeSpan(0,9,0,0),::THIRTY_SEVEN_PW,_T("37")));

	 pcombo->InsertString(3,_T("7.2 - 36"));
	 pcombo->SetItemDataPtr(3, new CShift(CTimeSpan(0,9,0,0),::THIRTY_SIX_PW,_T("36")));

	pcombo->InsertString(4,_T("Clear"));
	pcombo->SetItemDataPtr(4, new CShift(::NONE,::NONE,_T("X")));
	 }
 else
	 {

	 // lookup the whole time contracted hours
	 // associated with the package
	 int boxitem(0);
	 for(boxitem=0;boxitem < pcombo->GetCount( );boxitem++)
		 {
		  CTimeSpan* ptr = (CTimeSpan*) pcombo->GetItemDataPtr(boxitem);
		  pcombo->SetItemDataPtr(boxitem, new CShift(CTimeSpan(0,9,0,0),*ptr,ptr->Format(_T("%H:%M"))));




		 }	//end for

	 // and add the clearing choice
	 pcombo->InsertString(boxitem,_T("Clear"));
	pcombo->SetItemDataPtr(boxitem, new CShift(::NONE,::NONE,_T("X")));
	 


	 }	//end else
#endif

 return TRUE;

}


BOOL CAbsence::codelistIsActive(void)
{
  return TRUE;

}


BOOL CAbsence::codelistUpdateable(void)
{

  return FALSE;

}

BOOL CAbsence::Overwrite(CRegularPeriod* arrangement, CAbsolutePeriod& slice)
{
/* look at the next cover arrangement*/

BOOL should_overwrite(TRUE);

CTimelist* parentcontract;

if(arrangement)
{

parentcontract = (CTimelist*) arrangement->GetStaff();

should_overwrite = parentcontract->IsConflictDay(*arrangement, arrangement,slice.GetDayOfWeek()-1);
}

return should_overwrite;

}

int CAbsence::FindSpan(CSpan* maybe_dupe,CComboBox& combo)
{
 /* overridden CCategory method. Since Absence object does not have a codelist*/
 /* returns index from 0 or -1 if no match */
 /* matches if duration is one of the standard days */

 

 TRY
 {

	if(!maybe_dupe){
		combo.SetCurSel(-1);
		AfxThrowUserException();
		}
	
	 CSpan* ptr = (CSpan*) combo.GetItemDataPtr(0);
	
	 
		   	if(maybe_dupe->getduration()==ptr->getduration())
				{
				combo.SetCurSel(0);
				
				return 0;

				}

			if(	maybe_dupe->getduration()==::NONE)
			{
			combo.SetCurSel(1);
			
			return 1;	
			}

			 else // one off case
			{
			combo.SetCurSel(-1);
			
			return -1;}

		 
   	

 }
 CATCH(CUserException,e)
 {
 	AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

 	return -1;

 }
 END_CATCH
 
			   
 
}
