// contract : implementation file
//
#include "stdafx.h"
#include <afxdb.h>
#include <afxdao.h>
//#include "centool8.h"
#include "CONSTANT.H"
#include "assert.h"

#include "absolute.h"
#include "span.h"
#include "period.h"
#include "timelist.h"
#include "addac.h"
#include "regularp.h"
#include "prdlst.h"

#include "contract.h"
#include "conset.h"
//#include "estab.h"

#include <stdio.h>
#pragma warning(disable : 4996)


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContract

IMPLEMENT_SERIAL(CContract, CTimelist,2)

CContract::CContract():CTimelist()
{
 


}


CContract::CContract(const CString title,
					 CPeriod* prnt,
					 CPeriod* uncl,
					 const long from,
					 const long to,
					 const CString contractno,
					 const long ID,
					 const CString package,
					 const double conhrs):CTimelist(title,
					 				(CTimelist*)prnt,
					 				(CTimelist*)uncl,
					 				from,
					 				to					 				
					 				),m_IDfrn(ID),
					 				   m_ContractNo(contractno),
					 				   m_Package(package),  
					 				   m_Conhrs(conhrs)
					 				      
{ 



} 



CContract::~CContract()
{
}


/////////////////////////////////////////////////////////////////////////////
// CContract message handlers  



void CContract::Serialize(CArchive& ar)

{   


		CTimelist::Serialize(ar);
	
	
	if(ar.IsStoring())
	{ 
	 
		
	ar << m_ContractNo << m_IDfrn << m_Package << m_Conhrs ; } 
	
	else
	{
	
	 ar >> m_ContractNo >> m_IDfrn >> m_Package >> m_Conhrs ; }
   
	
	
	
	
	
    
	
 } 




	
BOOL CContract::displaydata(const CRect* calendarbox,CDC* pDC, CView* handle)
{ 

/* Overridden to show break down of child summaries rather than just a
	summary */




// get display count of non zero durations 

int total_show = getdisplaycount();

if(total_show)
{



CSize topslice_size(getbox()->Width(),getbox()->Height()/2);//total_show);

//CSize topslice_size(getbox()->Size());

CPoint topleft(getbox()->TopLeft());


POSITION pos=GetHeadPosition();

if(pDC->IsPrinting()){topleft.Offset(0,topslice_size.cy);}

while(pos)
{

CPeriod* ptr =(CPeriod*) GetAt(pos);

CRect copyrect(topleft,topslice_size);
ptr->setbox(&copyrect);
ptr->displaydata(calendarbox,pDC,handle);
topleft.Offset(0,topslice_size.cy); 
GetNext(pos);
}


return TRUE; }

else

{ return FALSE; }

}


	
#ifdef _DEBUG
void CContract::Dump(CDumpContext& dc) const
{   
    
    
	CObject::Dump(dc);
//	dc  <<"\n name"  << name <<"\n";
}
#endif //_DEBUG	

#ifndef STANDALONE
  
void CContract::UpdateDatabase(CLog& ds, CString contractno, const long empno, const CString estab, CAbsolutePeriod start)
{



POSITION pos=GetHeadPosition();

	while(pos)

		{

			CTimelist* ptr= (CTimelist*) GetAt(pos);

			ptr->OnFileUpdateDatabase(ds, get_table_ID(), get_contract_holder_ID(),  estab, start);

			GetNext(pos);

		}


}
#endif //STANDALONE

CString CContract::get_table_ID(void)
{


return m_ContractNo;


} 



void CContract::set_contractNo(const CString identifyer)
{

assert(!identifyer.IsEmpty());
m_ContractNo = identifyer;


}

void CContract::get_contractNo(CString& proxy)
{


proxy = m_ContractNo;


}

long CContract::get_contract_holder_ID(void)
{

return m_IDfrn;

}

void CContract::get_contract_holder_ID(long identifyer)
{

identifyer = m_IDfrn;

}

void CContract::set_contract_holder_ID(const long identifyer)
{


m_IDfrn = identifyer;


}


BOOL CContract::Edit(const CTime basedate)
{

CAddac dlg(basedate,NULL);
dlg.IsEstablishment=IsEstablishment();
dlg.whichtitle=dlg.Edit;
dlg.m_name=Getname();
dlg.m_code= m_ContractNo;
dlg.m_ID = m_IDfrn;
dlg.m_package= m_Package;
dlg.m_conhrs= m_Conhrs;
dlg.m_otherptr=m_mainlist;       
dlg.m_titlestring=_T("Edit Properties of ") + Getname();					 				   


              

dlg.nMin=0;
dlg.nMax=364;
	


dlg.from_position=(int) GetFromToPosition(::MIN);
dlg.to_position=(int) GetFromToPosition(::MAX);

if(dlg.DoModal()==IDOK)
{
		 
Setname(dlg.m_name);
m_ContractNo = dlg.m_code;
m_IDfrn = dlg.m_ID; 






if(IsEstablishment())
	{
	m_Package = dlg.m_package;
	m_Conhrs = dlg.m_conhrs;

	}
else
	{
	 // for contracts only
	 // altering the contract means all instructions
	 // are altered too.

	

	 SetFromToPositionYouAndBelow(::MIN,(long)dlg.from_position);
	 SetFromToPositionYouAndBelow(::MAX,(long)dlg.to_position);


	}
m_IDfrn = dlg.m_ID;
 
return TRUE;}
else { return FALSE;}

}

BOOL CContract::CanCutandPaste(const UINT param)
{


return param== cut_and_copy;

}

CTimelist* CContract::AddStarter(const CTime basedate, CPeriodlist*& m_data)

{

CAddac dlg(basedate,NULL);

CTimelist* ptr=NULL;

dlg.nMin= 0;
dlg.nMax= 364;
dlg.m_otherptr=m_mainlist;
dlg.m_titlestring="Add a Contract";

/* Generates a default contract string and ID */
char contractNo[10];
DWORD number((DWORD) this);
number+= getdisplaycount() +1;
sprintf(contractNo,"%d" , number);


dlg.m_code = contractNo;
dlg.m_ID = number;
dlg.from_position=dlg.nMin;
dlg.to_position=dlg.nMax;

if(dlg.DoModal()==IDOK)
{ 

assert(!dlg.m_name.IsEmpty());

CTimelist* uncleptr=(CTimelist*) uncle;

ptr=Add(dlg.m_name,
		uncleptr,
		dlg.from_position,
		dlg.to_position,
		dlg.m_code,
		dlg.m_ID,
		dlg.m_package,
		dlg.m_conhrs,
		TRUE);


uncleptr->AddAll(ptr,0,364);
m_data->CreditConhrs((CContract*) ptr);



}

return ptr;

}

BOOL CContract::Deleteitem(CTimelist* item, CPeriodlist* m_data, const UINT NOWARNINGS)
{  

POSITION pos=  m_mainlist-> Find(item);
CTimelist* ptr=(CTimelist*)   m_mainlist-> GetAt(pos);
CTimelist* uncleptr=(CTimelist*) uncle;
ptr->Removeall();
m_mainlist->RemoveAt(pos);
delete ptr;

return TRUE; 

}

									  


CTimelist* CContract::Add(CString title,
						CTimelist* uncle,
						const long childmin,
						const long childmax,
						const CString contractno,
						const long ID,
						const CString package,
						const double conhrs,
						BOOL IsManual)
{ 
  
  CTimelist* prnt=this;  
  CObject* ptr=NULL;

  ptr =new CContract(title,
  					 prnt,
  					 uncle,
  					 childmin,
  					 childmax,
  					 contractno,
  					 ID,
  					 package,
  					 conhrs);
  					 
  //m_mainlist->AddTail(ptr);
  
  if(IsManual){Addbeforebank(ptr);}
  else { m_mainlist->AddTail(ptr);}
  
  CTimelist* lptr=(CTimelist*) ptr;
 
  
return lptr;}

void CContract::Addbeforebank(CObject* ptr)
{

m_mainlist->AddTail(ptr); 

}

BOOL CContract::IsBank(void)
{

return FALSE;


}


BOOL CContract::prioritise(const CTime basedate, CAbsolutePeriod slice, const UINT trans_type, const int fwkno, BOOL& has_priority)
{

 

 POSITION pos=GetHeadPosition();
	while(pos)
		{
		CTimelist* ptr=(CTimelist*) GetAt(pos);
		
		has_priority = 	ptr->prioritise(basedate,slice,trans_type, fwkno, has_priority);
		
		GetNext(pos);}	//end while




return TRUE;
}



void CContract::get_contracts_held_by(const long HOLDERS_ID , CObList& conlist)
{

if(get_contract_holder_ID()==HOLDERS_ID)
			{

				conlist.AddTail(this);

			} 
		 

// overridden in derived estab class


}



BOOL CContract::showmenu(CView* handle, const CPoint& coords)
{
    	
    CMenu popup;
    CMenu popup2;

	popup.CreatePopupMenu();
	popup2.CreatePopupMenu();
	
	HMENU mhand = popup2.GetSafeHmenu();
	
	popup.AppendMenu(MF_POPUP,(UINT)mhand,_T("&Add"));
		
		popup2.AppendMenu(MF_STRING,ID_ADD_ADDINSTRUCTION,_T("&Shift"));
		
	
	popup.AppendMenu(MF_STRING,ID_DELETE,_T("&Delete"));
	popup.AppendMenu(MF_SEPARATOR,0,_T("")); 
	if(!is_open){
	popup.AppendMenu(MF_STRING,ID_ZOOM,_T("&Open"));}
	else {
    popup.AppendMenu(MF_STRING,ID_UNZOOM,_T("&Close"));}

	if(parent->Getparent())
    {
    popup.AppendMenu(MF_STRING,ID_VIEW_BYITEM,_T("&Beam me up Scotty"));}
	popup.AppendMenu(MF_STRING,ID_NAVIGATE,_T("&Navigate"));
	popup.AppendMenu(MF_STRING,ID_EDIT,_T("&Properties"));
	popup.TrackPopupMenu(TPM_LEFTBUTTON ,coords.x ,coords.y + 150, handle ,0);
	popup.Detach();
	
    
return TRUE;	

 }




BOOL CContract::Does_Clash_From_Top(CObList* conlist, CContract* root)
{
 /*
/*purpose: determins if next shift in queue conflicts with absence arrangement


CObList mydata;
BOOL does_clash(FALSE); 

//long id(get_contract_holder_ID());

//if(conlist && root)

//{ 

//root->get_contracts_held_by(id,*conlist);	



 // get 
   
POSITION pos = GetHeadPosition();

if(pos){
CTimelist* ptr = (CTimelist*) GetAt(pos);
ptr->scoopdata(&mydata);	 

}

							                     
							                     
while(!does_clash && pos && !mydata.IsEmpty())
{




		CRegularPeriod* test = (CRegularPeriod*) mydata.RemoveHead();
		does_clash = ptr->Clashes(*test,NULL);
  		delete test;

		conlist->GetNext(pos);

}


/* give the user the option of changing the id 

if(does_clash &&
		AfxMessageBox(IDS_CHANGE_ID,MB_OKCANCEL|MB_ICONQUESTION,0)==IDOK){

		m_IDfrn= (DWORD) this;
		
		does_clash=FALSE;}





while(!mydata.IsEmpty())
{

mydata.RemoveHead();

}

}  //end if conlist
*/
return FALSE;

}






CObject* CContract::Clone(void)
{

CObject* ptr= new CContract( Getname(),
							(CTimelist*) parent,
							(CTimelist*) uncle,
							GetFromToPosition(::MIN),
							GetFromToPosition(::MAX),
							m_ContractNo,
							m_IDfrn,
					 		m_Package,  
					 		m_Conhrs
							);
						
							

return ptr;
}

BOOL CContract::IsConflict(CRegularPeriod& test, CPeriod* original, const BOOL timeshared)
{
/* Called  by CSodialog with a test to check conflict with Absence arrangements only */


   
BOOL does_clash(FALSE); 

  
   
// Absence folder is and must remain first 

// Test is based on whether test object is an absence arrangement or a cover arrangement
// decided by its colour. Absence arrangements are red, cover are blue

COLORREF itemcolour;


itemcolour = test.getcolour();

POSITION pos = GetHeadPosition();

switch(itemcolour)
{

 case ::BLUE :	 // select Absence folder to test Cover arrangement against

  
  break;

  case ::RED:

  

  GetNext(pos);	 // select Cover folder to test Absence arrangement against

  break;

  default :


  AfxMessageBox(IDS_PGERR,MB_OK,0);
  break;
}



	 							                     
							                     
if(!does_clash && pos)
{

CTimelist* ptr= (CTimelist*) GetAt(pos);


does_clash = ptr->IsConflict(test,original,timeshared);



}

		


return does_clash;

}

BOOL CContract::IsConflictDay(CRegularPeriod& test, CPeriod* original,const UINT dayoftheweek)
{

 BOOL does_clash(FALSE);
 COLORREF itemcolour;


itemcolour = test.getcolour();

POSITION pos = GetHeadPosition();

switch(itemcolour)
{

 case ::BLUE :	 // select Absence folder to test Cover arrangement against

  
  break;

  case ::RED:

  

  GetNext(pos);	 // select Cover folder to test Absence arrangement against

  break;

  default :


  AfxMessageBox(IDS_PGERR,MB_OK,0);
  break;
}



	 							                     
							                     
if(!does_clash && pos)
{

CTimelist* ptr= (CTimelist*) GetAt(pos);



  
does_clash = ptr->IsConflictDay(test,original,dayoftheweek);

}

		


return does_clash;



}

BOOL CContract::IsConflictWithOwn(CRegularPeriod& test, CPeriod* original,const BOOL timeshared)
{
/* Called  by CSodialog with a test to check conflict with Absence arrangements only */


   
BOOL does_clash(FALSE); 

  
   
// Absence folder is and must remain first 

// Test is based on whether test object is an absence arrangement or a cover arrangement
// decided by its colour. Absence arrangements are red, cover are blue

COLORREF itemcolour;


itemcolour = test.getcolour();

POSITION pos = GetHeadPosition();

switch(itemcolour)
{

 case ::BLUE :	 // select Cover folder to test Cover arrangement against

  GetNext(pos);

  break;

  case ::RED:

  

  // do nothing. Absence objects search the absence folder for conflicts

  break;

  default :


  AfxMessageBox(IDS_PGERR,MB_OK,0);
  break;
}



	 							                     
							                     
if(!does_clash && pos)
{

CTimelist* ptr= (CTimelist*) GetAt(pos);



  
does_clash = ptr->IsConflict(test,original,timeshared);

}

		


return does_clash;

}



double CContract::Getconhrs(void)
{


return m_Conhrs;

}

BOOL CContract::EditBank(void)
{


 return FALSE;


}


BOOL CContract::RestoreContractNo(void)
{


return FALSE;


}

void CContract::GetTCSpackage(CString& package)
{

  package = m_Package;

}

LRESULT CContract::Get_not_catered_for(CObList & partial_contracts, double & not_catered_for)
{

LRESULT nResult(0);

try
	{


	

	 // if a partial contract and conhrs > 0 add to list
	if(m_Conhrs)
		{
			if(GetFromToPosition(::MIN)==0 && GetFromToPosition(::MAX)== 364 ){ ; }
			else { partial_contracts.AddTail(this);}
			

		//if(GetFromToPosition(::MIN)!=0 ){ partial_contracts.AddTail(this) ; }
		//if(GetFromToPosition(::MAX)!=364 ){ partial_contracts.AddTail(this) ; }

		

			not_catered_for -= m_Conhrs; 

		}
	 

	}
catch(CUserException* e)
	{




	}
return nResult;





}

LRESULT CContract::ClearBudget(CPeriodlist * &)
{

LRESULT nResult(0);


try
	{
	 
	 //overridden in CExtraProvision object


	}
catch(CUserException* e)
	{




	}
return nResult;


}

LRESULT CContract::GetExtraProv(CContract *  ptr)
{

//overridden in CExtraProvision

return 0;

}

BOOL CContract::IsExtraProv(void)
{
 return false;
}

LRESULT CContract::get_staff_bar_this_one(const long ID, CObList & conlist)
{
  LRESULT nResult(0);

  try
	  {

	  if(get_contract_holder_ID()!=ID)
			{

				conlist.AddTail(this);

			} 
		 

// overridden in derived estab class




	  }
  catch(CUserException* e)
	  {



	  }
  return nResult;
}

BOOL CContract::FilltempConTable(CDaoRecordset *& ds)
{
BOOL outcome(false);
try
	{
	CConset* rs = (CConset*) ds;

	if( rs->CanAppend() && !IsExtraProv() &&!IsBank() )
		{

		rs->AddNew();
		rs->m_Conhrs = m_Conhrs;
		rs->m_ContractNo = m_ContractNo;
		rs->m_EMPLOYEE_N = Getname();
		rs->m_FRNM1= Getname();
		rs->m_IDfrn = m_IDfrn;
		rs->m_Package = m_Package;
		((CContract*) Getparent())->get_contractNo(rs->m_Estabfrn);

		rs->Update();
		outcome = true;
		
		}


	}
catch(CUserException* e)
	{




	}
 return outcome;
}
