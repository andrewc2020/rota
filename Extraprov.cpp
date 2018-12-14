// extraprovision : implementation file
//

#include "stdafx.h"


#include <afxdb.h>
//#include "centool8.h"
#include "constant.h"

#include "absolute.h" 
#include "span.h"
#include "period.h"
#include "timelist.h"
#include "contract.h"
#include "regularp.h"
#include "cal1.h"
#include "Extraprov.h"
#include "resource.h"
#include <stdio.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBank

IMPLEMENT_SERIAL(CExtraProvision, CContract,3)

CExtraProvision::CExtraProvision():CContract()
{
 


}


CExtraProvision::CExtraProvision(const CString title,
					 CPeriod* prnt,
					 CPeriod* uncl,
					 const long from,
					 const long to,
					 const CString contractno,
					 const long ID,
					 const CString package,
					 const double conhrs):CContract(title,
					 				(CTimelist*)prnt,
					 				(CTimelist*)uncl,
					 				from,
					 				to,
					 				contractno,
									ID,
					 				package,
					 				conhrs					 				
					 				)
					 				      
{ 



} 



CExtraProvision::~CExtraProvision()
{
}


/////////////////////////////////////////////////////////////////////////////
// CExtraProvision message handlers  

void CExtraProvision::Serialize(CArchive& ar)

{   


		CContract::Serialize(ar);
	
	
	if(ar.IsStoring())
	{ 
	 
		
	} 
	
	else
	{
	
	 }
   
	
	
	
	
	
    
	
 } 


LRESULT CExtraProvision::Get_not_catered_for(CObList & partial_contracts, double & not_catered_for)
{

LRESULT nResult(0);

try
	{

	 
	
	  m_Conhrs = not_catered_for;

	}
catch(CUserException* e)
	{




	}
return nResult;





}


UINT CExtraProvision::GetImage(void)
{

if(is_open){return IDB_OPEN;}
else {return IDB_CLOSED3;}

}


LRESULT CExtraProvision::ClearBudget(CPeriodlist * & pdata)
{

LRESULT nResult(0);


try
	{
	 
	 CTimelist* ptr = (CTimelist*) Find_BY_Name(_T("Cover"));
	 ptr->Removedata(pdata,FALSE);
	 


	}
catch(CUserException* e)
	{




	}
return nResult;


}

LRESULT CExtraProvision::GetExtraProv(CContract *  ptr)
{
LRESULT nResult(0);

try
	{
	 ptr = this;

	}
catch(CUserException* e)
	{



	}
return nResult;

}

BOOL CExtraProvision::IsExtraProv()
{

return true;

}

BOOL CExtraProvision::showmenu(CView * handle, const CPoint & coords)
{

 /*

CMenu popup;
//    CMenu popup2;
  //  CMenu popup3;

	popup.CreatePopupMenu();
	//popup2.CreatePopupMenu();
	//popup3.CreatePopupMenu();
	/*
	HMENU mhand=popup2.GetSafeHmenu();
	
	popup.AppendMenu(MF_POPUP,(UINT)mhand,"&Edit");
		popup2.AppendMenu(MF_STRING,ID_EDIT,"&Properties");
	
	
	mhand=popup3.GetSafeHmenu();
	popup.AppendMenu(MF_POPUP,(UINT)mhand,"&Add");
		
		popup3.AppendMenu(MF_STRING,ID_ADD,"&Account");
		popup3.AppendMenu(MF_STRING,ID_ADD_ADDINSTRUCTION,"&Instruction");
		
	
	popup.AppendMenu(MF_STRING,ID_DELETE,"&Delete");
	popup.AppendMenu(MF_SEPARATOR,0,""); 
	if(!is_open){
	popup.AppendMenu(MF_STRING,ID_ZOOM,"&Open");}
	else {
    popup.AppendMenu(MF_STRING,ID_UNZOOM,"&Close");}
	
	if(parent->Getparent())
    {
    popup.AppendMenu(MF_STRING,ID_VIEW_BYITEM,"&Beam me up Scotty");}
	popup.AppendMenu(MF_STRING,ID_NAVIGATE,"&Navigate");
*/	
/*	popup.AppendMenu(MF_STRING,ID_EDIT,"&Properties");
	popup.TrackPopupMenu(TPM_LEFTBUTTON ,coords.x ,coords.y + 150, handle ,0);
	popup.Detach();	  
	
*/   
return TRUE;



}
