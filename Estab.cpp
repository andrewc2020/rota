// contract : implementation file
//

#include "stdafx.h"
#pragma warning(disable : 4995)
#pragma warning(disable : 4996)
#include <afxdb.h>
#include <afxdao.h>
//#include "centool8.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "span.h"
#include "period.h"
#include "timelist.h"
#include "contract.h"
#include "conset.h"
#include "addac.h" 
#include "estab.h"
#include "bank.h"
#include "Extraprov.h"
#include "strlong.h"
#include "subbankd.h"
#include "SubCondlg.h"

#include "assert.h"
#include "cal1.h"

#include <stdio.h>



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEstab

IMPLEMENT_SERIAL(CEstab, CContract,2)

CEstab::CEstab():CContract()
{
 


}


CEstab::CEstab(const CString title,
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



CEstab::~CEstab()
{
}


/////////////////////////////////////////////////////////////////////////////
// CEstab message handlers  



COLORREF CEstab::getcolour(void)
{
return ::BLACK;

}



	
BOOL CEstab::displaydata(const CRect* calendarbox,CDC* pDC, CView* handle)
{ 

/* Overridden to override CContract
	summary */



if(pDC->IsPrinting()){
return CContract::displaydata(calendarbox,pDC,handle);}

else{
                                                        
return CTimelist::displaydata(calendarbox,pDC,handle);}

}


	
UINT CEstab::GetImage(void)
{

if(is_open){return IDB_OPEN;}
else {return IDB_CLOSED1;}

}

BOOL CEstab::CanCutandPaste(const UINT param)
{


return param== paste_only;

}


void CEstab::print(
						const CTime basedate,
						CAbsolutePeriod currentperiod,
						CDC* pDC
						) 

{

 if(parent)
 {
     
	    
  pDC->TextOut(getbox()->TopLeft().x ,getbox()->TopLeft().y , Getname());}

  else
  {
		
		
 	CTimelist::print(basedate,currentperiod,pDC);}


 }

BOOL CEstab::showmenu(CView* handle, const CPoint& coords)
{
	CMenu popup;
    CMenu popup2;	
    

	popup.CreatePopupMenu();
	popup2.CreatePopupMenu();
	
    

		
	HMENU mhand =popup2.GetSafeHmenu();
	
	popup.AppendMenu(MF_POPUP,(UINT)mhand,_T("&Add"));
		popup2.AppendMenu(MF_STRING,ID_ADDCONTRACT,_T("&Contract"));
		

	if(!is_open){
	popup.AppendMenu(MF_STRING,ID_ZOOM,_T("&Open"));}
	else if(parent){
    popup.AppendMenu(MF_STRING,ID_UNZOOM,_T("&Close"));
    }
	popup.AppendMenu(MF_STRING,ID_NAVIGATE,_T("&Navigate"));
	popup.AppendMenu(MF_STRING,ID_EDIT,_T("&Properties"));

	popup.TrackPopupMenu(TPM_LEFTBUTTON ,coords.x ,coords.y + 150, handle ,0);
	popup.Detach();
	
    
return TRUE;	

 }


CTimelist* CEstab::EstabStarter(const CTime basedate)

{

CAddac dlg(basedate,NULL);

CTimelist* ptr=NULL;

dlg.nMin=(int) GetFromToPosition(::MIN);
dlg.nMax=(int) GetFromToPosition(::MAX);
dlg.m_otherptr=m_mainlist;
dlg.m_titlestring="Add an Establishment";

/* Generates a default contract string and ID from pointer */
char contractNo[10];
DWORD number((DWORD)this);


sprintf(contractNo,"%d" ,number);


dlg.m_code = contractNo;
dlg.m_ID = number;
dlg.from_position=dlg.nMin;
dlg.to_position=dlg.nMax;

if(dlg.DoModal()==IDOK)
{ 

assert(!dlg.m_name.IsEmpty());

CTimelist* uncleptr=(CTimelist*) uncle;

ptr=AddEstab(dlg.m_name,
		uncleptr,
		dlg.nMin,
		dlg.nMax,
		dlg.m_code,
		dlg.m_ID,
		dlg.m_package,
		dlg.m_conhrs);



}

return ptr;

}


CTimelist* CEstab::AddBank(CString title,
						CTimelist* uncle,
						const long childmin,
						const long childmax,
						const CString contractno,
						const long ID,
						const CString package,
						const double conhrs)
{ 
  
  CTimelist* prnt=this;  
  CObject* ptr=NULL;

  ptr =new CBank(title,
  					 prnt,
  					 uncle,
  					 childmin,
  					 childmax,
  					 contractno,
  					 ID,
  					 package,
  					 conhrs);
  					 
  m_mainlist->AddTail(ptr); 
  
  CTimelist* lptr=(CTimelist*) ptr;
 
  
return lptr;}


CTimelist* CEstab::AddExtraProvision(CString title,
						CTimelist* uncle,
						const long childmin,
						const long childmax,
						const CString contractno,
						const long ID,
						const CString package,
						const double conhrs)
{ 
  
  CTimelist* prnt=this;  
  CObject* ptr=NULL;

  ptr =new CExtraProvision(title,
  					 prnt,
  					 uncle,
  					 childmin,
  					 childmax,
  					 contractno,
  					 ID,
  					 package,
  					 conhrs);
  					 
  m_mainlist->AddTail(ptr); 
  
  CTimelist* lptr=(CTimelist*) ptr;
 
  
return lptr;}



CTimelist* CEstab::AddEstab(CString title,
						CTimelist* uncle,
						const long childmin,
						const long childmax,
						const CString contractno,
						const long ID,
						const CString package,
						const double conhrs)
{ 
  
  CTimelist* prnt=this;  
  CObject* ptr=NULL;

  ptr =new CEstab(title,
  					 prnt,
  					 uncle,
  					 childmin,
  					 childmax,
  					 contractno,
  					 ID,
  					 package,
  					 conhrs);
  					 
  m_mainlist->AddTail(ptr); 
  
  CTimelist* lptr=(CTimelist*) ptr;
 
  
return lptr;}


BOOL CEstab::IsEstablishment(void)
{

return TRUE;


}


CObject* CEstab::Clone(void)
{

CObject* ptr= new CEstab( Getname(),
							(CTimelist*) parent,
							(CTimelist*) uncle,
							GetFromToPosition(::MIN),
							GetFromToPosition(::MAX),
							_T("BAXH"),
					 		0,
					 		_T("XXX"),  
					 		0.0
							);
						
							

return ptr;
}

BOOL CEstab::prioritise(const CTime basedate, CAbsolutePeriod slice, const UINT trans_type, const int fwkno, BOOL& has_priority)
{
 /* give priority to the most recently allocated shift */


BOOL verdict(TRUE);

POSITION pos = GetHeadPosition();

while(pos)
{

CContract* ptr= (CContract*) GetAt(pos);

/* ask each contract to call all with a restored verdict*/





	verdict=TRUE;

	ptr->prioritise(basedate,slice,trans_type,fwkno,verdict);





GetNext(pos);

}



return TRUE;
}

BOOL CEstab::Does_Clash_From_Top(CObList* conlist, CContract* root)
{

BOOL does_clash(FALSE);

assert(conlist);

POSITION pos = GetHeadPosition();

while(pos && !does_clash)
{

CContract* ptr= (CContract*) GetAt(pos);

/*the search item is present in each list, so excluding must be set true */



does_clash = ptr->Does_Clash_From_Top(conlist,root);

conlist->RemoveAll();

GetNext(pos);

}



return does_clash;






}





BOOL CEstab::ContainsNoEstab(void)
{

BOOL noestab(TRUE);

POSITION pos = GetHeadPosition();

while (pos && noestab)

{

 CTimelist* ptr = (CTimelist*) GetAt(pos);

 noestab = ptr->IsEstablishment()==FALSE;  
 GetNext(pos);

}


return noestab;


}


BOOL CEstab::ContainsNoContract(void)
{

BOOL nocontracts(TRUE);

POSITION pos = GetHeadPosition();

while (pos && nocontracts)

{

 CContract* ptr = (CContract*) GetAt(pos);

 nocontracts = ptr->IsEstablishment();  
 GetNext(pos);

}



return nocontracts ;


}

BOOL CEstab::EditBank(CDaoDatabase& db, const CTime endrota, const long days_into_period)
{

  BOOL success(TRUE);

  CObList*  active_list = (CObList*) new CObList;

  


//dlg.m_existptr = active_list;	 !active_list->IsEmpty()) &&

POSITION pos = GetHeadPosition();



while(pos)
{

 CContract* ptr = (CContract*) GetAt(pos);


 if(ptr->EditBank())
 {

 active_list->AddTail(ptr);

 
 }

 GetNext(pos);

}

CSubBankdlg dlg(db,active_list,NULL);

dlg.m_endrota = endrota;

 

if(!active_list->IsEmpty() && dlg.DoModal()==IDOK )
	{

	 

	 void* bankptr;
	 void* slotptr;
	 
	 


	POSITION pos = dlg.m_map.GetStartPosition();  
	CObList conlist;

	 while(  pos )
	{
	  
	  dlg.m_map.GetNextAssoc(pos, bankptr ,   slotptr );
	  // test each for possible conflicts

	  // prime conlist with contracts belonging to holderID

	  
	  get_contracts_held_by(((Stringlong*) bankptr)->longbit, conlist);
	  
	  

	  if(slotptr && !((CBank*) slotptr)->IsConflict(conlist,endrota,days_into_period))
	  {

	    
	  ((CContract*) slotptr)->set_contractNo( (((Stringlong*) bankptr)->stringbit));

	  ((CContract*) slotptr)->set_contract_holder_ID( (((Stringlong*) bankptr)->longbit));

	  
	  }
	  else
	  {

	  success = FALSE;

	  }
	  

	  delete  bankptr;

	  }

	}

 
delete active_list;

 return success;

}

BOOL CEstab::RestoreContractNo(void)
{

POSITION pos = GetHeadPosition();

while (pos)

{

 CContract* ptr = (CContract*) GetAt(pos);

 ptr->RestoreContractNo();  
 GetNext(pos);

}


return TRUE;




}

void CEstab::get_contracts_held_by(const long HOLDER_ID, CObList& conlist)
{

POSITION pos = GetHeadPosition();



while(pos)
{

 CContract* ptr = (CContract*) GetAt(pos);

 ptr->get_contracts_held_by(HOLDER_ID,conlist);

 GetNext(pos);




}




}


void CEstab::Addbeforebank(CObject* ptr)
{

BOOL found_first_bank(FALSE);

if(m_mainlist)
{

POSITION pos = m_mainlist->GetHeadPosition();


while(pos && found_first_bank==FALSE)
{

CContract* conptr = (CContract*) m_mainlist->GetAt(pos);

found_first_bank = (conptr->IsBank()||conptr->IsExtraProv());

if(found_first_bank ){ m_mainlist->InsertBefore(pos,ptr);}


m_mainlist->GetNext(pos);

}


if(!found_first_bank ) {  m_mainlist->AddTail(ptr); }


}// end if m_mainlist



}

LRESULT CEstab::SetBudget(const double budget)
{

LRESULT nResult(0);

try
	{


	 m_Conhrs = budget;

	}
catch(CUserException* e)
	{




	}
return nResult;

}

LRESULT CEstab::SetTCSPackage(const CString package)
{

LRESULT nResult(0);

try
	{


	 m_Package = package;

	}
catch(CUserException* e)
	{




	}
return nResult;


}



LRESULT CEstab::Get_not_catered_for(CObList& partial_contracts, double& not_catered_for)
{

/*Purpose: cycle through existing contracts reducing the non allocated budget by each contracts hours*/

LRESULT nResult(0);


try
	{
	 
	 not_catered_for = m_Conhrs;

	 POSITION pos = GetHeadPosition();



		while(pos)
		{

		 CContract* ptr = (CContract*) GetAt(pos);

			ptr->Get_not_catered_for( partial_contracts, not_catered_for);

		 GetNext(pos);




		}


	}
catch(CUserException* e)
	{




	}
return nResult;


}

LRESULT CEstab::ClearBudget(CPeriodlist * & pdata)
{

 LRESULT nResult(0);


try
	{
	 
	 

	 POSITION pos = GetHeadPosition();



		while(pos)
		{

		 CContract* ptr = (CContract*) GetAt(pos);

			ptr->ClearBudget(pdata);

		 GetNext(pos);




		}


	}
catch(CUserException* e)
	{




	}
return nResult;




}

LRESULT CEstab::GetExtraProv(CContract *&  Xtraptr)
{
LRESULT nResult(0);


try
	{
	 
	 

	 POSITION pos = GetHeadPosition();



		while(pos)
		{

		 CContract* ptr = (CContract*) GetAt(pos);

			if(ptr->IsExtraProv())
				{
				
				Xtraptr = ptr;
				
				}

			if(Xtraptr){ break;}	

		 GetNext(pos);




		}


	}
catch(CUserException* e)
	{




	}
return nResult;

}

LRESULT CEstab::get_staff_bar_this_one(const long ID, CObList & conlist)
{

/*Cycles through the contracts adding all bar the passed ID, filling list as
it goes */

LRESULT nResult(0);

try{

	POSITION pos = GetHeadPosition();



		while(pos)
		{

		CContract* ptr = (CContract*) GetAt(pos);

		ptr->get_staff_bar_this_one(ID,conlist);

		GetNext(pos);




		}
	}

	catch(CUserException* e)
		{





		}

return nResult;


}

LRESULT CEstab::SubstituteConID(CDaoDatabase & db, const CTime endrota, const long days_into_period)
{
LRESULT nResult(0);
try
	{
	BOOL HasBalance(false);

// delete existing records
  CString sql(_T("DELETE * FROM ContractTemp;"));
	  db.Execute(sql);

// extract table from database
	
	CConset* ds = new CConset(&db);
	sql ="PARAMETERS [?] TEXT; "; 
   sql += "SELECT FRNM1, EMPLOYEE_N, Package, Hrs, Estabfrn, Budgetline,";
   sql += " [Pers Number], Startdate," ;
   sql += " IIf(Not IsDate([Termdate]),#";
   sql += endrota.Format("%m/%d/%Y");
   sql += "#,[Termdate]) AS Termcalc " ;
   sql += "    FROM ContractTemp";
   sql += " WHERE Estabfrn= [?] ";


   ds->m_endrotaParam = endrota;

   get_contractNo(ds->m_estabParam);
	

   	
	 
	ds->Open(dbOpenDynaset,sql );

	
	


	POSITION pos = GetHeadPosition();



		while(pos)
		{

		 CContract* ptr = (CContract*) GetAt(pos);


		if(ptr->FilltempConTable(((CDaoRecordset*&)ds)))
		 {

		 
		 
	
 
		 }

		

		

		GetNext(pos);


			}

	// fill the list with staff not found in database

		ds->Close();
		


		sql ="PARAMETERS [?] TEXT; "; 
   sql += "SELECT FRNM1, EMPLOYEE_N, Package, Hrs, Estabfrn, Budgetline,";
   sql += " [Pers Number], Startdate," ;
   sql += " IIf(Not IsDate([Termdate]),#";
   sql += endrota.Format("%m/%d/%Y");
   sql += "#,[Termdate]) AS Termcalc " ;
   sql += "    FROM ContractTempNoContract";
   sql += " WHERE Estabfrn= [?] ";


   ds->m_endrotaParam = endrota;
   

   get_contractNo(ds->m_estabParam);

   ds->Open(dbOpenSnapshot,
			sql,dbReadOnly);
 	 
	
		CObList* active_list = new CObList;
		
		if(!ds->IsBOF( ))
	{

	ds->MoveFirst();
	while(!ds->IsEOF() ) // add contracts		
	     {
		 get_contracts_held_by(ds->m_IDfrn,*active_list);

	
			ds->MoveNext();
			}
		}//end try


   ds->Close();

   /*Finally, the dialogue needs only be displayed
   if the new contracts have a balance so check */
   pos = active_list->GetHeadPosition();

   while(pos)
	   {

	   CContract* conptr = (CContract*) active_list->GetHead();
	   HasBalance = conptr->getbalance();
	   if(HasBalance){ break;}
	   active_list->GetNext(pos);


	   }


	CSubCondlg dlg(db,active_list,NULL);

dlg.m_endrota = endrota;

 

if( HasBalance && !active_list->IsEmpty() && dlg.DoModal()==IDOK )
	{

	 

	 void* rostered_staff_ptr;
	 void* slotptr;
	 
	 


	POSITION pos = dlg.m_map.GetStartPosition();  
	CObList conlist;

	 while(  pos )
	{
	  
	  dlg.m_map.GetNextAssoc(pos, rostered_staff_ptr ,   slotptr );
	  // test each for possible conflicts

	  // prime conlist with contracts belonging to holderID

	  
	  get_contracts_held_by(((Stringlong*) rostered_staff_ptr)->longbit, conlist);
	  
	  

	 

	    
	  ((CContract*) slotptr)->set_contractNo( (((Stringlong*) rostered_staff_ptr)->stringbit));

	  ((CContract*) slotptr)->set_contract_holder_ID( (((Stringlong*) rostered_staff_ptr)->longbit));

	  
	  
	  

	  delete  rostered_staff_ptr;

	  }

	}

 
delete active_list;
delete ds;
 



	}// end try

catch(CUserException* e)
	{





	}
catch(CDaoException* f)
	{

	return false;

	


	}

 return nResult;
}


