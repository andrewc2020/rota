 // regularp.cpp : implementation file
//


#include "stdafx.h"
#include "bitvec.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include "resource.h"

#include "absolute.h"
#include "span.h"
#include "period.h"	
#include "timelist.h"
#include "regularp.h"
//#include "navdlg.h"

#include "assert.h"
#include "category.h"

#include <stdio.h>



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegularPeriod 



IMPLEMENT_SERIAL(CRegularPeriod, CPeriod,1) 





CRegularPeriod::CRegularPeriod(): CPeriod(), m_dayarray(NULL),m_balance(::NONE)
			 
{



}

CRegularPeriod::CRegularPeriod(
							   CObArray* dayarray,
							   const long from,
							   const long to,
							   CPeriod* p_parent,
							   CPeriod* uncleptr) : CPeriod(::NONE,
							   								::NONE,
							   								from,
							   								to,
							   								p_parent,
							   								uncleptr)

, m_dayarray(NULL),m_balance(::NONE)


{


m_dayarray =new CObArray;

m_dayarray->SetSize(7,0);

CSpan* ptr=NULL;

for(int cnt(0); cnt <= 6; cnt++)
{

ptr = (CSpan*) dayarray ->GetAt(cnt);

m_dayarray->SetAt(cnt ,ptr->clone());

}



parent->datalogin(this);


uncle->datalogin(this);

Get_uncle_colour();

 
}

/* caution 

 builds object for testing purposes only - eg clash test 
 destroy immediately after use in test do not add to list */  
 
 
 
CRegularPeriod::CRegularPeriod(
							   CObArray* dayarray,
							   const long from,
							   const long to,
							   CPeriod* p_parent
							   ) : CPeriod(::NONE,
							   			   ::NONE,
							   			   from,
							   			   to,
							   			   p_parent,
							   			   p_parent->Getuncle()
							   			   )

, m_dayarray(NULL),m_balance(::NONE)


{


m_dayarray =new CObArray;

m_dayarray->SetSize(7,0);

CSpan* ptr=NULL;

for(int cnt(0); cnt <= 6; cnt++)
{

ptr = (CSpan*) dayarray ->GetAt(cnt);

m_dayarray->SetAt(cnt ,ptr->clone());

}







Get_uncle_colour();

}


		 
 
void CRegularPeriod::Serialize(CArchive& ar)
{    
    

	CPeriod::Serialize(ar);
    
    
	  if (ar.IsStoring())
	
	{   
	
	
		
		// TODO: add storing code here

	
		
	ar << m_dayarray ;
		
		

			
	}
	else
	{
		// TODO: add loading code here
	    
	
	ar >>  m_dayarray ;
	
	    
	
		
		 
 
		
	}
		
		
	
	
}

CRegularPeriod::~CRegularPeriod()
{ 

if(parent)// else as in test engagements created but not added to list
{
parent->datalogout((CObject*) this);}

if(uncle)
{
uncle->datalogout((CObject*)this);}

for(int cnt=0;cnt<=6;cnt++)
{


delete (CSpan*) m_dayarray->GetAt(cnt);


} 

delete  m_dayarray;


}


/////////////////////////////////////////////////////////////////////////////
// CRegularPeriod  handlers

BOOL CRegularPeriod::amend_start(CSpan* spanptr)
{

setstart(spanptr->getstart());

parent->setstart(spanptr->getstart());	
uncle->setstart(spanptr->getstart());

BOOL amended(TRUE);
/*
    if( parent->getstart() > spanptr->getstart()){
		parent->setstart(spanptr->getstart());
		
			
		
		}	
		else {amended=FALSE;}  

	
		 


	if( uncle->getstart() >= spanptr->getstart()){
		uncle->setstart(spanptr->getstart());}
		else { amended=FALSE;} 	 

		
 */
return amended;

}

BOOL CRegularPeriod::proxydocket(const CTime basedate, CAbsolutePeriod slice,const UINT trans_type, const int fwkno, const BOOL newvalue)
{

 int slice_day=slice.GetDayOfWeek()-1;
CSpan* spanptr=0;

spanptr =(CSpan*) m_dayarray->GetAt(slice_day);
CRegularPeriod* ptr=0;
		       
CAbsolutePeriod scope(basedate,GetFromToPosition(::MIN),
												GetFromToPosition(::MAX));


	if(slice.IsWithinPeriod(scope) && (!(spanptr->getstart()==::NONE && spanptr->getduration()==::NONE)))
	{
      
	 



amend_start(spanptr);

/*
#ifdef _DEBUG
TRACE( "credit  %d", spanptr->getduration().GetTotalHours()); 
#endif //_DEBUG
 */


parent->setcolour(getcolour());
uncle->setcolour(getcolour());  
	

	 return TRUE;	
  
   	}
   	
else {return FALSE;}


}


BOOL CRegularPeriod::docket(const CTime basedate,
						 	 CAbsolutePeriod slice ,
						    const UINT trans_type, const int fwkno)
{ 


	


int slice_day=slice.GetDayOfWeek()-1;
CSpan* spanptr=0;

spanptr =(CSpan*) m_dayarray->GetAt(slice_day);
CRegularPeriod* ptr=0;
		       
CAbsolutePeriod scope(basedate,GetFromToPosition(::MIN),
												GetFromToPosition(::MAX));


	if(spanptr->getduration().GetTotalMinutes() && slice.IsWithinPeriod(scope))
	{
      
	 



amend_start(spanptr);

/*
#ifdef _DEBUG
TRACE( "credit  %d", spanptr->getduration().GetTotalHours()); 
#endif //_DEBUG
 */


parent->setcolour(getcolour());
uncle->setcolour(getcolour());  
	
/*
#ifdef _DEBUG
 afxDump << "\n slice   =" << slice << uncle << "\n";
 
#endif
*/

return TRUE;	
  
   	}
   	
else {return FALSE;}

}

void CRegularPeriod::fillvector(CBitvector& tofill)
{


// does nothing as has no vector
// overidden in CDebitPeriod


}

//BOOL CRegularPeriod::move(void)
//{
//
//UINT STRING_ID(IDS_PGERR);
//
//
//TRY
//
//{
//
//
//// check that by deleting this item you are not going to cause a conflict
//
//
//
//
//CNavdlg dlg((CTimelist*) parent);
//
//
//
//dlg.titlestring="Reassign Instruction for ";
//
//
//if(dlg.DoModal()==IDOK )
//{
//
//	
//if(!dlg.m_peg){ AfxThrowUserException(); }
//
//
//
//
//parent->datalogout(this);
//uncle->datalogout(this);
//
//
//parent=dlg.m_peg;
//
//parent->datalogin(this);
//    
//set_uncle(parent->Getuncle()); 
//uncle->datalogin(this);
//
//
//Get_uncle_colour();
//
//}
//
//return TRUE;
//}
//
//CATCH(CUserException, e)
//{
// 
// AfxMessageBox(STRING_ID,MB_OK|MB_ICONEXCLAMATION,0);
// 
// return FALSE;
//}
//
//END_CATCH
//{
//
//return TRUE;
//
//}
//
//}


CObject* CRegularPeriod::split(void)
{



return NULL;
}



BOOL CRegularPeriod::showmenu(CView* handle, const CPoint& coords)
{ 

   /*Overridden in derived classes
    	
   CMenu popup;
   
    

	popup.CreatePopupMenu();

	
	popup.AppendMenu(MF_STRING,ID_EDITINSTRUCTION,"&Edit Debit");
	popup.AppendMenu(MF_STRING,ID_MOVE,"&Move Debit");
	popup.AppendMenu(MF_STRING,ID_DELETEINSTRUCTION,"&Delete Debit");
	popup.TrackPopupMenu(TPM_LEFTBUTTON ,coords.x ,coords.y + 150, handle ,0);
	popup.Detach();
	
*/	
 return TRUE;
 
 }
 



UINT CRegularPeriod::GetImage(void)
{
return IDB_LEAF; 

}



void CRegularPeriod::login(const DWORD parent_id, CTimelist* itemptr,const BOOL Is_Parent)
{

 

if(parent_id==get_id())
{
parent=itemptr;
assert(parent_id); 
uncle=parent->Getuncle();
parent->datalogin(this);
uncle->datalogin(this);
resetid();}


}


void CRegularPeriod::ResetPeriod(CTimeSpan start,CTimeSpan someotherperiod_duration)
{

setstart(start);
setduration(someotherperiod_duration);

}

void CRegularPeriod::setid(void)
{

CPeriod::setid_direct((DWORD) parent);


}

BOOL CRegularPeriod::Edit(const CTime basedate,const long weekstart)
{

// virtual method overridden in derived classes.

return FALSE;

}



CObject* CRegularPeriod::Clone(CPeriod* list_parent)
{

/*overridden in base classes*/
			
return NULL;

}

CObject* CRegularPeriod::Clone(void)
{

/*overridden in base classes*/
			
return NULL;

}


BOOL CRegularPeriod::IsRecoverable(void)
{

return FALSE;

}


BOOL CRegularPeriod::IsCheckable(void)
{

 return FALSE;

}


BOOL CRegularPeriod::Clashes(CRegularPeriod& test)
{

return FALSE;

/* overridden in CDebitPeriod */

}

BOOL CRegularPeriod::Clashes(CRegularPeriod& test,const UINT dayoftheweek)
{

return FALSE;

/* overridden in CDebitPeriod */

}

BOOL CRegularPeriod::IsToil(const UINT dayoftheweek)
{

return FALSE;

/* overridden in CDebitPeriod */

}


BOOL CRegularPeriod::IsWithin(const CTimeSpan, const CTimeSpan, const int)
{

 // overriden in CDebitPeriod

 return FALSE;

}

BOOL CRegularPeriod::dayshared(CRegularPeriod& test,const UINT dayoftheweek)
{
// overriden in CDebitPeriod
return FALSE;
}

BOOL CRegularPeriod::dayshared(CRegularPeriod& test)
{
// overriden in CDebitPeriod
return FALSE;
}

BOOL CRegularPeriod::IsEventfulDay(const UINT dayofweek)
{

 // overriden in CDebitPeriod
 return FALSE;


}

void CRegularPeriod::Clearbalance(void)
{

m_balance=::NONE;


}

long CRegularPeriod::getbalance(void)
{


return m_balance.GetTotalSeconds();


}

BOOL CRegularPeriod::Overwrite(CAbsolutePeriod& slice)
{
 // default behaviour of an arrangement is always to overwrite a previous arrangement
 // The exception is an absence arrangement of less than a whole day
 // e.g. Training in the morning followed by a late

 

 return ((CCategory*)uncle)->Overwrite(this,slice);

 


}

#ifdef _DEBUG
void CRegularPeriod::Dump(CDumpContext& dc) const
{   
    
 CObject::Dump(dc);   
	
dc  << "\nUncle is= "<< uncle->Getname() << "\nParent= " << parent->Getname() <<"\n";
}
#endif //_DEBUG	



BOOL CRegularPeriod::IsClearWeeks(void)
{

return false;// overridden in CDebitPeriod

}

LRESULT CRegularPeriod::SetFromToPositionToCredit(const int flag, const long value)
{
 return 0;// overriddent in CDebitPeriod
}


