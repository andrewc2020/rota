// bank : implementation file
//

#include "stdafx.h"


#include <afxdb.h>
//#include "centool8.h"
#include "CONSTANT.H"

#include "absolute.h" 
#include "span.h"
#include "period.h"
#include "timelist.h"
#include "contract.h"
#include "regularp.h"
#include "cal1.h"
#include "bank.h"
#include "resource.h"
#include <stdio.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBank

IMPLEMENT_SERIAL(CBank, CContract,2)

CBank::CBank():CContract(),m_tempno(""),m_tempID(0)
{
 


}


CBank::CBank(const CString title,
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
					 				),m_tempno(contractno),m_tempID(ID)
					 				      
{ 



} 



CBank::~CBank()
{
}


/////////////////////////////////////////////////////////////////////////////
// CBank message handlers  

void CBank::Serialize(CArchive& ar)

{   


		CContract::Serialize(ar);
	
	
	if(ar.IsStoring())
	{ 
	 
		
	ar << m_tempno << m_tempID; } 
	
	else
	{
	
	ar >> m_tempno >> m_tempID; }
   
	
	
	
	
	
    
	
 } 


BOOL CBank::EditBank(void)
{

BOOL hasbalance(FALSE);
 
 TRY
 {
 

 if(getbalance() )
 {

 // only concerned with positive return for week

 

 hasbalance = TRUE;

 


 
  }

 }//end of try


  CATCH(CUserException, e)
	{  
	
	 AfxMessageBox(IDS_PGERR,MB_OK,0);
	
	}
	        
		 	    
		
	END_CATCH
	
	

 

return hasbalance; 

}




BOOL CBank::RestoreContractNo(void)
{

// restore suspense account details	to bank slot

CContract::set_contractNo(m_tempno);

CContract::set_contract_holder_ID(m_tempID);



return TRUE;


}


UINT CBank::GetImage(void)
{

if(is_open){return IDB_OPEN;}
else {return IDB_CLOSED2;}

}


BOOL CBank::IsBank(void)
{

return TRUE;


}

BOOL CBank::IsConflict(CObList& contracts_to_check, const CTime endtime, const long days_into_period)
{

TRY
{

CObList my_instructions;
CRegularPeriod* my_data_item=NULL;
BOOL IsConflicting(FALSE);
CTimelist* coverlist;



POSITION pos = CTimelist::GetHeadPosition();


if(pos)
{
CTimelist::GetNext(pos);
coverlist= (CTimelist*) CTimelist::GetAt(pos);
coverlist->scoopdata(&my_instructions);
}

// first get data



//coverlist->scoopdata(&my_instructions);

long endofperiod(days_into_period +7);

while(!my_instructions.IsEmpty())
{



my_data_item = (CRegularPeriod*) my_instructions.RemoveTail();

if(my_data_item && my_data_item->IsCheckable())
{



my_data_item->SetFromToPosition(::MIN,days_into_period);
my_data_item->SetFromToPosition(::MAX,endofperiod);

	while(!contracts_to_check.IsEmpty()	&& !IsConflicting)
	{
	 IsConflicting = FALSE; // reset for each 
	 CContract* ptr =  (CContract*)  contracts_to_check.RemoveHead();

	  CString rstring;

	 // test for conflict with an absence arrangement
	 IsConflicting = ptr->IsConflict(*my_data_item, my_data_item,TRUE);



	 

	 if(!IsConflicting){
	 // do nothing 
	 	 
	 }
	 else
	 {

	  // offer the user the chance to bale out

	  AfxFormatString2(rstring,IDS_BANKABSCONFLICT,ptr->Getname(),(my_data_item->GetStaff())->Getname());
                            
	  int result = AfxMessageBox( rstring, MB_OKCANCEL|MB_ICONQUESTION,0x18021);
	  if(result==IDOK){ IsConflicting= TRUE ;}else{ IsConflicting = FALSE; }


	 }

	 // Test for conflict with a cover shift if clear or substitution not abandoned
	 if(IsConflicting)
	  {
	 IsConflicting = ptr->IsConflictWithOwn(*my_data_item, my_data_item,TRUE); }
	 else
	 { IsConflicting=FALSE;}// reset to false as clear or substitution does not apply.
	 
	  if(IsConflicting)
	  {
	  AfxFormatString1(rstring,IDS_BANKCONFLICT,ptr->Getname());
                                                
	  AfxMessageBox(rstring ,MB_OK,0); }
	  
	  }// end while contract-to-check

	}  // end if checkable




delete my_data_item;   // each is a clone and should be deleted


contracts_to_check.RemoveAll();





}//end while
		
		

return IsConflicting;

}

CATCH(CUserException,e)
{

 return FALSE;

}

END_CATCH
{


 return TRUE;


}



}


void CBank::get_contracts_held_by(const long HOLDERS_ID , CObList& conlist)
{

// do nothing as bank contracts are special	 




}
