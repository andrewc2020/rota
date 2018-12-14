// prdlist.cpp : implementation file
//


#include "stdafx.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include "span.h"
#include "absolute.h"
#include "period.h"
#include "timelist.h"
#include "contract.h"
#include "regularp.h"
#include "credit.h"
#include "debit.h"
#include "sodialog.h"
//#include "credlg.h"
#include "prdlst.h"
#include <math.h>
#include <stdio.h>
#include "assert.h"
#include "resource.h"




#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPeriodlist

IMPLEMENT_SERIAL(CPeriodlist, CObList, 1)


// Constructor 
CPeriodlist::CPeriodlist()
{



}

			 		
CPeriodlist::~CPeriodlist()
	{   
		Removeall();	 	
		
		    	} 
  	



BOOL CPeriodlist::Removeall(void)
{   

 while(!IsEmpty()){
 
 		CRegularPeriod* listptr;
 		listptr = (CRegularPeriod*) RemoveHead();
 		
#ifdef _DEBUG
afxDump << "\n CRegPeriod Item is " << *listptr << "\n" ;
#endif
		delete listptr;} 

return TRUE;} 



  
BOOL CPeriodlist::Add(const CTime basedate,
					  CTimelist* parent,
					  CPeriod* unc,
					  const long weekstart)
{
CTimelist* deeper=NULL; 
BOOL success(false);

try
	{

	deeper=parent->Add(basedate,_T(""));// user can seek a deeper level

 
	CSOdialog dlg(basedate,NULL);

	enum {oneoff,repeating}; 

 
	dlg.m_parent=deeper;
	dlg.nMin=(int)parent->GetFromToPosition(::MIN);
	dlg.nMax=(int)parent->GetFromToPosition(::MAX);

	//check whether the current week setting is usable
	// i.e. whether it is within the contractual period
	
	long weekfinish(weekstart + 6);

		if(!(parent->IsWithin(weekstart,weekfinish)))
		{

		dlg.m_freq=repeating;

		}
		else
		{

		dlg.m_freq=oneoff;

		}
	 
	dlg.weekstart=weekstart;

	dlg.from_position=dlg.nMin;
	dlg.to_position=dlg.nMax;

	dlg.m_dayarray = new CObArray;
	dlg.m_dayarray->SetSize(7,0);

	for(int cnt(0);cnt<=6;cnt++)
	{

	dlg.m_dayarray->SetAt(cnt, new CSpan(CTimeSpan(::NONE),CTimeSpan(::NONE)));

	}


   if(deeper && dlg.DoModal()==IDOK)
    {
    
   
      
   
   
	long from=0;
	long to=0;
         
  
	from=dlg.from_position;
	to=dlg.to_position;
   
   // normal use case. Otherwise adding from catview
   
	if(deeper!=parent || unc==NULL){
	unc=deeper->Getuncle();}
   		
     
	CObject* ptr=0;

    
  
	ptr =new CDebitPeriod(dlg.m_bitvector,
  						dlg.m_drpvector,
  						dlg.m_dayarray,
  						from,
  						to,
  						deeper,
  						unc,
  						dlg.m_fixed,
  						basedate);
  
  
  
	AddTail(ptr);
  
	CPeriod* pPd=(CPeriod*) ptr;
	pPd->Get_uncle_colour();
	
	success = true;
  

	   }

	else {	


	success =  false;
 
	
	
		}

	}//end try
catch(CUserException* e)
	{
	success = false;
	AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

	}
 return success;   
}




BOOL CPeriodlist::CreditCompensator(CContract* Compensator ,CObList& partial_contracts )
{

/*
Purpose: Credits the special account instance of
CExtraProvision with the CCreditPeriod objects
it needs to cater for partial contracts.

The partial_contracts list is filled by the Get_not_catered_for
process which cycles through the contracts picking
up those beginning or ending (or both) after the start
or before the end of the financial year.


*/



BOOL success(TRUE);

double dayrate(0.0);
CTimeSpan start(0,9,0,0);
CPeriod* pPd=NULL;

try
	{


CTimelist* parent = (CTimelist*) Compensator->Find_BY_Name(_T("Cover"));



if(!parent){AfxThrowUserException();}



 /* breaking down contractual hours */

// retrieve each partial contract

while( !partial_contracts.IsEmpty() )
{

CContract* ptr = (CContract*)	 partial_contracts.RemoveHead();

// pointer must be valid 

if (!ptr){ AfxThrowUserException();}


// generate one Credit to offset start and finish

dayrate = ptr->Getconhrs()/5;

	if(	ptr->GetFromToPosition(::MIN)> 0 && dayrate!= 0.0)
	{



   
	// create dayarray to pass in constructor

		CObArray* dayarray = new CObArray;
		dayarray->SetSize(7,0);

			for(int cnt(0);cnt<=4;cnt++)
			{

			dayarray->SetAt(cnt, new CSpan(start,dayrate));

			}

		dayarray->SetAt(5, new CSpan(::NONE,::NONE));
		dayarray->SetAt(6, new CSpan(::NONE,::NONE));
    
   	
 		pPd = new CCreditPeriod(dayarray ,0,(ptr->GetFromToPosition(::MIN)-1),parent,parent->Getuncle());

 		AddTail(pPd);

		}////end if contract to compensate starts late

		if(	ptr->GetFromToPosition(::MAX)!= 364 && dayrate!= 0.0)
			{
			// create dayarray to pass in constructor

			CObArray* dayarray = new CObArray;
			dayarray->SetSize(7,0);

				for(int cnt(0);cnt<=4;cnt++)
				{

				dayarray->SetAt(cnt, new CSpan(start, dayrate));

				}

			dayarray->SetAt(5, new CSpan(::NONE,::NONE));
			dayarray->SetAt(6, new CSpan(::NONE,::NONE));
    
   
	

			pPd = new CCreditPeriod(dayarray ,ptr->GetFromToPosition(::MAX)+1,364,parent,parent->Getuncle());

 			AddTail(pPd);




			} //end if contract to compensate finishes early

  
		}// end while

	}//end try
catch(CUserException* e)
	{

	AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

	}

return success;
}


BOOL CPeriodlist::CreditConhrs(CContract* newcontract)
{

/*Purpose: Used to create a contracts credit objects
N.B. With ordinary contracts, this is taken care of in the constructor
However, the ExtraProvision contract is continually being 
updated in accordance with staff changes.

*/

BOOL success(true);

try
	{


	double dayrate((newcontract->Getconhrs())/5);



	CTimelist* parent = (CTimelist*) newcontract->Find_BY_Name(_T("Cover"));

	// the topmost (i.e. parentless) list is the establishment
	// Establishments are not credited with 
	// contractual hours. They receive the budget instead.
	// which is then subcontracted, giving rise to appointments
	// and the extra provision contract.

	if(!parent){AfxThrowUserException();}



	 /* breaking down contractual hours */





	CTimeSpan start(0,9,0,0);

   
	// create dayarray to pass in constructor

	CObArray* dayarray = new CObArray;
	dayarray->SetSize(7,0);

	for(int cnt(0);cnt<=4;cnt++)
	{

	dayarray->SetAt(cnt, new CSpan(start,dayrate));

	}

	dayarray->SetAt(5, new CSpan(::NONE,::NONE));
	dayarray->SetAt(6, new CSpan(::NONE,::NONE));
    
   


	CObject* ptr=NULL;
	CPeriod* pPd=NULL;



	pPd = new CCreditPeriod(dayarray ,newcontract->GetFromToPosition(::MIN),newcontract->GetFromToPosition(::MAX),parent,parent->Getuncle());

	AddTail(pPd);
  
 
	pPd->Get_uncle_colour(); 
	}//end try
catch(CUserException* e)
	{

	AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

	}
 
return TRUE; 

}
	
void CPeriodlist::login(const DWORD id, CTimelist* itemptr)
{
POSITION pos=GetHeadPosition();
while(pos)
{

CRegularPeriod* ptr=(CRegularPeriod*) GetAt(pos);
ptr->login(id,itemptr, TRUE);

GetNext(pos);

}

}

 



void CPeriodlist::docket(const CTime basedate,  CAbsolutePeriod slice , const UINT trans_type, const int weekno)
{



POSITION pos=GetHeadPosition();

	while(pos)
	{

pPd=(CRegularPeriod*) GetAt(pos);

pPd->docket(basedate, slice, trans_type, weekno);

GetNext(pos);

	}

	

} 



BOOL CPeriodlist::Deleteitem(CObject* ptr_to_go, BOOL Warnings)
{

UINT STRING_ID(IDS_PGERR);


TRY
{


POSITION pos= Find(ptr_to_go,0);

 

CRegularPeriod* ptr=(CRegularPeriod*) ptr_to_go;



/*Check that object to be deleted is in the list*/ 

if(pos)
{
if(ptr_to_go!=GetAt(pos))
{

STRING_ID=IDS_PGERR;
AfxThrowUserException();

}
}



if((Warnings==TRUE) && AfxMessageBox(IDS_DELETEINSTRUCTION,MB_OKCANCEL|MB_ICONQUESTION,0)!=IDOK )
{
STRING_ID = IDS_USERABORT;
AfxThrowUserException();
}

pos = Find(ptr_to_go);
ptr=(CRegularPeriod*) GetAt(pos);
RemoveAt(pos);

delete ptr_to_go;
return TRUE;


}

CATCH(CUserException,e)
{
 

 
 AfxMessageBox(STRING_ID,MB_OK|MB_ICONEXCLAMATION,0);


 
 return FALSE;



}

END_CATCH
{


 return TRUE;



}
}

void CPeriodlist::Recover(CRegularPeriod* pPd)
{

CPeriod* ptr = NULL;

ptr= pPd->Getparent();
ptr= ptr->Getparent();
// get current credit's parent's parent i.e the list's parent.


if(pPd->IsRecoverable() && (ptr=(CPeriod*) pPd->Clone(ptr))!=NULL)// get current credit's parent's parent.
{

// if credit and not at top level, will clone and assign to parent
// original will be deleted by calling function



AddTail(ptr);


  
ptr->Get_uncle_colour(); }




}
	  				      

LRESULT CPeriodlist::DeleteWeekless(void)
{
LRESULT nResult(0);
CRegularPeriod* rpd=NULL;

CObList ptrlist;


try
	{

	POSITION pos=GetHeadPosition();

	while(pos)
	{

	rpd=(CRegularPeriod*) GetAt(pos);

	if(rpd->IsClearWeeks())
		{

		
		ptrlist.AddTail((CObject*)rpd);


		}
		
	
	
		GetNext(pos);
		    

		
		

	}


	while(!ptrlist.IsEmpty())
		{


		Deleteitem(ptrlist.RemoveHead(),false);

		}


	}
catch(CUserException* e)
	{




	}
return nResult;


}
