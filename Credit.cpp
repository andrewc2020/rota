 // regularp.cpp : implementation file
//

#include "stdafx.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "span.h"
#include "period.h"
#include "regularp.h"
#pragma warning(disable : 4996)
#include "credit.h"
#include "timelist.h"
#include "crprop.h"
#include "splitdlg.h"
#include <math.h>
#include "assert.h"
#include <stdio.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegularPeriod 



IMPLEMENT_SERIAL(CCreditPeriod, CRegularPeriod,1) 





CCreditPeriod::CCreditPeriod(): CRegularPeriod()
			 
{


}

CCreditPeriod::CCreditPeriod(	
							 CObArray* dayarray,
							 const long from,
							 const long to,
							 CPeriod* p_parent,
							 CPeriod* uncleptr
							 ) : CRegularPeriod(
							 					dayarray,
							 					from,
							 					to,
							 					p_parent,
							 					uncleptr
							 					)


{



}

		 
/* caution 

 builds object for testing purposes only - eg clash test 
 destroy immediately after use in test do not add to list */ 

CCreditPeriod::CCreditPeriod(CObArray* dayarray,
							   const long from,
							   const long to,
							   CPeriod* p_parent
							   ) :CRegularPeriod(
											dayarray,
											from,
											to,
											p_parent
											)
{



}	

CCreditPeriod::~CCreditPeriod()
{ 
  
  


}


/////////////////////////////////////////////////////////////////////////////
// CCreditPeriod  handlers




BOOL CCreditPeriod::proxydocket(const CTime basedate, CAbsolutePeriod slice , const UINT trans_type, const int weekno, const BOOL newvalue)
{ 


	

if(trans_type != debit_only && CRegularPeriod::proxydocket(basedate,slice,trans_type, weekno, newvalue)) 
{

/*
#ifdef _DEBUG
TRACE( "credit  %d", getduration().GetTotalHours()); 
#endif //_DEBUG
*/

if(trans_type==balance)
{ 

*parent += (::NONE - getduration());
*uncle += (::NONE - getduration()); }

else
{

CSpan* ptr = 0;

ptr = (CSpan*) m_dayarray->GetAt(slice.GetDayOfWeek()-1);

setduration(ptr->getduration());
*parent += getduration();
*uncle += getduration();
 
m_balance += getduration();

}

}

return FALSE; 

}

BOOL CCreditPeriod::Clashes(CRegularPeriod& test,const UINT dayoftheweek)
{
 
// Always false. Credit does not refer to particular time period,
// but provision of time for future use


return FALSE;

}

BOOL CCreditPeriod::Clashes(CRegularPeriod& test)
{
 
// Always false. Credit does not refer to particular time period,
// but provision of time for future use


return FALSE;

}

void CCreditPeriod::Serialize(CArchive& ar)
{    
    

	 CRegularPeriod::Serialize(ar);
    
    
		
} 


UINT CCreditPeriod::GetImage(void)
{
return IDB_LEAF1; 

}


 
 
BOOL CCreditPeriod::Edit(const CTime basedate,const long weekstart)
{

CCrprop dlg;
	

	
	dlg.m_starthrs=getstart().GetHours();
    dlg.m_startmins=getstart().GetMinutes();
    dlg.m_durhrs=getduration().GetHours();
    dlg.m_durmins=getduration().GetMinutes();
    
	
    dlg.m_mon= TRUE;
    dlg.m_tue= TRUE;
    dlg.m_wed= TRUE;
    dlg.m_thu= TRUE;
	dlg.m_fri= TRUE;
    dlg.m_sat= FALSE;
    dlg.m_sun= FALSE;	

	
    
    CAbsolutePeriod period_to_run(
    basedate,
    GetFromToPosition(::MIN),
    GetFromToPosition(::MAX),::NONE);
    
    

	dlg.nMin=0;//(int) parent->GetFromToPosition(::MIN);
    dlg.nMax=364;//(int) parent->GetFromToPosition(::MAX);
    
    dlg.from_position=(int) GetFromToPosition(::MIN);
    dlg.to_position=(int) GetFromToPosition(::MAX);

	dlg.from = basedate;
    
    double hour_frac(0.0);

	dur_as_decimal(hour_frac);

    

	int totalweeks = (GetFromToPosition(::MAX)- GetFromToPosition(::MIN))/7;

	
	char totalstring[20];
	

	//dlg.m_perwk = getduration().Format("%H:%M:%S");
    
	sprintf(totalstring,"%.3f",hour_frac *= 5);
    dlg.m_perwk = totalstring;
    
   	sprintf(totalstring,"%.3f",hour_frac *= totalweeks);
	dlg.m_total=totalstring;


   	 if(dlg.DoModal()==IDOK)
   	 {
   	 
   	 SetFromToPosition(::MIN,(long) dlg.from_position);
     SetFromToPosition(::MAX,(long) dlg.to_position);
   	 
   	 }
        
    
    return TRUE;
    

}



CObject* CCreditPeriod::split(CObList* m_data)
{ 
        
    CPeriod* ptr;

    CSplitdlg dlg;
	
	// get existing start and duration

	CSpan* spanptr =NULL;

	spanptr = (CSpan*) m_dayarray->GetAt(0);

    
    /* calculate weekly credit amount of this credit to display in dialog */
       
    
    double hour_frac(spanptr->getduration().GetTotalMinutes() * 5);
    
    if(hour_frac)
    {
	hour_frac/=60;}
			
	dlg.m_exhrs = hour_frac;
	dlg.m_currweeks = (GetFromToPosition(::MAX)-GetFromToPosition(::MIN))/7;
	dlg.m_earweeks = dlg.m_currweeks;
    dlg.m_curtot = hour_frac * dlg.m_currweeks;
	

    
    if(dlg.DoModal()==IDOK)
    {


    
   hour_frac= dlg.m_eartot/dlg.m_currweeks;
   
   /* 
   provide from existing credit by
   spreading provision over total weeks of existing credit at rate
   to produce required hours*/	
	
	

	ptr= (CPeriod*) split(hour_frac);

	
	
	
	m_data->AddTail(ptr);

	

	
	
    
    
return ptr;}    
    
   
 else {return NULL;}


}


CObject* CCreditPeriod::split(const double hour_frac)
{

CSpan* spanptr = NULL;
int cnt(0);	

CObject* objptr=NULL;



if(hour_frac )
    {
	
	
	// 1. set local m_dayarray to new reduced duration
	 
	//CPeriod::decimal_to_time(hour_frac,duration);

	for(cnt=0;cnt<=4;cnt++)
	{
	   spanptr = (CSpan*) m_dayarray->GetAt(cnt);
	   
	   *spanptr-=hour_frac;
	   
    }
	
    
    // 2. create new credit period with remainder duration		

	CObArray* dayarray = new CObArray;
	dayarray->SetSize(7,0);		

			for(cnt=0;cnt<=4;cnt++)
			{

			dayarray->SetAt(cnt,new CSpan(getstart(),hour_frac));}
 			dayarray->SetAt(5,new CSpan(::NONE,::NONE));
 			dayarray->SetAt(6,new CSpan(::NONE,::NONE));



  			   
	         objptr = new CCreditPeriod(
			 							dayarray,
			 							GetFromToPosition(::MIN),
			 							GetFromToPosition(::MAX),
			 							parent,
			 							Getuncle()); 

 // 3. cleanup

 		cnt = 6;
 		while(cnt)
 			{
 
				 delete dayarray->GetAt(cnt);
 				 cnt--;
 
 
 			}    
    
 delete dayarray;
 	}  
 return objptr;
}



BOOL CCreditPeriod::showmenu(CView* handle, const CPoint& coords)
{ 


    	
   CMenu popup;
   
    

	popup.CreatePopupMenu();

	
	popup.AppendMenu(MF_STRING,ID_EDITINSTRUCTION,_T("&Edit Credit")); 
	/*
	popup.AppendMenu(MF_STRING,ID_DELETEINSTRUCTION,"&Delete Credit");
	popup.AppendMenu(MF_STRING,ID_SPLITINSTRUCTION,"&Split Credit");
	popup.AppendMenu(MF_STRING,ID_MOVE,"&Move Credit");	 */
	popup.TrackPopupMenu(TPM_LEFTBUTTON ,coords.x ,coords.y + 150, handle ,0);
	popup.Detach();
	
	
 return TRUE;
 
 }
 
#ifdef _DEBUG
void CCreditPeriod::Dump(CDumpContext& dc) const
{   
    
 CObject::Dump(dc);   
	
dc  << "\nUncle is= "<< uncle->Getname() << "\nParent= " << parent->Getname() <<"\n";
}
#endif //_DEBUG	

CObject* CCreditPeriod::Clone(CPeriod* list_parent)
{

CObject* ptr=NULL;

if(list_parent)// safeguard and in case top of tree
{

CObArray* dayarray = new CObArray;

  dayarray->SetSize(7,0);

  CSpan* spanptr=NULL;

  for(int cnt=0; cnt <=6; cnt++)
  {

  spanptr = (CSpan*) m_dayarray->GetAt(cnt);

  if(spanptr){ spanptr = (CSpan*) spanptr->clone();

  dayarray->SetAt(cnt , spanptr);}

  spanptr=NULL;
  
  	}
   
/* uses test object constructor so does not login */

ptr= new CCreditPeriod(	dayarray,
	 					GetFromToPosition(::MIN),
						GetFromToPosition(::MAX),
						list_parent,
						list_parent->Getuncle()); }
									
									
															
									
return ptr;



}

BOOL CCreditPeriod::IsRecoverable(void)
{

return TRUE;

}



LRESULT CCreditPeriod::SetFromToPositionToCredit(const int flag, const long value)
{

LRESULT nResult(0);

try
	{

	 SetFromToPosition(flag,value);

	
	}
catch(CUserException* e)
	{



	}
return nResult;


}
