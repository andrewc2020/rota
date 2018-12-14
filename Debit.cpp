 // debit.cpp : implementation file
//


#include "stdafx.h"
#include "resource.h"
#include "CONSTANT.H"
//#include "centool8.h"
#include "absolute.h"
#include "span.h"
#include "period.h"
#include "regularp.h"
#include "sodialog.h"
#include "bitvec.h"
#include "debit.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegularPeriod 



IMPLEMENT_SERIAL(CDebitPeriod, CRegularPeriod,1) 





CDebitPeriod::CDebitPeriod(): CRegularPeriod(), m_weekvector(NULL),m_drpvector(NULL)
			 
{

 m_weekvector = new CBitvector;
 m_drpvector = new CBitvector;

}

CDebitPeriod::CDebitPeriod(
							 CBitvector* bitvector,
							 CBitvector* drpvector,	
							 CObArray* dayarray,
							 const long from,
							 const long to,
							 CPeriod* p_parent,
							 CPeriod* uncleptr,
							 const BOOL Is_Fixed,
							 const CTime basedate
							 ) : CRegularPeriod(
							 					dayarray,
							 					from,
							 					to,
							 					p_parent,
							 					uncleptr
							 					),
							 					m_weekvector(NULL),
												m_drpvector(NULL),
							 					m_IsFixed(Is_Fixed),
												m_basedate(basedate)


{

m_weekvector = new CBitvector(bitvector);
m_drpvector = new CBitvector(drpvector);
} 

/* caution 

 builds object for testing purposes only - eg clash test 
 destroy immediately after use in test do not add to list */ 

CDebitPeriod::CDebitPeriod(	   CBitvector* bitvector,
								CBitvector* drpvector,
							   CObArray* dayarray,
							   const long from,
							   const long to,
							   CPeriod* p_parent,
							   const BOOL Is_Fixed,
							   const CTime basedate
							   ) :CRegularPeriod(
											dayarray,
											from,
											to,
											p_parent
											)
											,m_weekvector(NULL)
											,m_drpvector(NULL)
							 				,m_IsFixed(Is_Fixed),
											m_basedate(basedate)
{


 m_weekvector = new CBitvector(bitvector);
 m_drpvector = new CBitvector(drpvector);

}		 


CDebitPeriod::~CDebitPeriod()
{ 

 delete m_weekvector;
 delete m_drpvector;
}


/////////////////////////////////////////////////////////////////////////////
// CDebitPeriod  handlers


void CDebitPeriod::Serialize(CArchive& ar)
{    
     long dummy;// necessary because of ambiguity of BOOL / int 
     			// when archived
				// probably due to 'Big Endian', 'Little Endian' dependency

	 CRegularPeriod::Serialize(ar);

	 m_weekvector->Serialize(ar);
	 m_drpvector->Serialize(ar);
    
	if(ar.IsStoring())
	{

	dummy = (long) m_IsFixed;

	ar << dummy << m_basedate ;

	}

	else
	{

	ar >>  dummy >> m_basedate;

	m_IsFixed =(BOOL) dummy;

	}
    
		
}

BOOL CDebitPeriod::proxydocket(const CTime basedate, CAbsolutePeriod slice,const UINT trans_type, const int fwkno, const BOOL newvalue)
{
 /* sets showme according to whether it is most recently introduced arrangement*/

CTime tempdate(basedate);

if(m_IsFixed){ tempdate=m_basedate;} // tether arrangement if fixed


 
	

if(trans_type != credit_only
	  &&  newvalue
	  &&  m_weekvector->IsSet(fwkno) 
	  && CRegularPeriod::proxydocket(tempdate,slice,trans_type, fwkno, newvalue ) 
	  ) 
{


CSpan* ptr = 0;



ptr = (CSpan*) m_dayarray->GetAt(slice.GetDayOfWeek()-1);

	 

setduration(ptr->getduration());
//drp status
SetDRPstatus(m_drpvector->IsSet(slice.GetDayOfWeek()-1));
parent->SetDRPstatus(GetDRPstatus());

*parent +=  getduration();
*uncle +=   getduration();

m_balance += getduration();
	 

return TRUE;


 }

else

{


return FALSE;



}



}

BOOL CDebitPeriod::docket(const CTime basedate, CAbsolutePeriod slice , const UINT trans_type, const int fwkno)
{ 

CTime tempdate(basedate);

if(m_IsFixed){ tempdate=m_basedate;} // tether arrangement if fixed



	

if(trans_type != credit_only
	 
	  &&  m_weekvector->IsSet(fwkno) 
	  && CRegularPeriod::docket(tempdate,slice,trans_type, fwkno ) 
	  
	  ) 
{
 
/*
#ifdef _DEBUG
TRACE( "credit  %d", getduration().GetTotalHours()); 
#endif //_DEBUG
*/

CSpan* ptr = 0;



ptr = (CSpan*) m_dayarray->GetAt(slice.GetDayOfWeek()-1);



setduration(ptr->getduration());

*parent +=  getduration();
*uncle +=   getduration();

m_balance += getduration();
/*
if(getduration().GetTotalHours())
{
#ifdef _DEBUG
TRACE( "credit  %d", getduration().GetTotalHours()); 
#endif //_DEBUG
}
*/
return TRUE;}	

else

{  return FALSE;} 

}


BOOL CDebitPeriod::IsCheckable(void)
{

 return TRUE;


} 

BOOL CDebitPeriod::Clashes(CRegularPeriod& test,const UINT dayoftheweek)
{

BOOL IsClash(FALSE);

CSpan* ptr = (CSpan*) m_dayarray->GetAt(dayoftheweek);
		if(ptr->getduration().GetTotalMinutes()>0 )
		{

		IsClash = ( test.IsWithin( ptr->getstart(),ptr->getduration(), dayoftheweek)); 
		 }
		
		
 return IsClash;
}

BOOL CDebitPeriod::IsToil(const UINT dayoftheweek)
{

 CSpan* ptr = (CSpan*) m_dayarray->GetAt(dayoftheweek);

 CTimeSpan toil(0,0,1,0);
  //AfxMessageBox( ptr->getstart().Format("%H:%M:%S"),MB_OK,0);
 return ptr->getstart()==toil;

}


BOOL CDebitPeriod::Clashes(CRegularPeriod& test)
{


/* compares the dayarrays of both regularperiod objects for overlapping times */

BOOL IsClash(FALSE);

CSpan* ptr=NULL;
int cnt=0;


		while(IsClash==FALSE && cnt<=6)
		{
		ptr = (CSpan*) m_dayarray->GetAt(cnt);
		if(ptr->getduration().GetTotalMinutes()>0)
		{
		IsClash = Clashes(test,cnt);}
		
		cnt++;
		} 

return IsClash;
	

}

BOOL CDebitPeriod::dayshared(CRegularPeriod& test, const UINT dayoftheweek)
{
 
 /* test for shared eventful day	*/

/*1. Is test within ball park? */


if(test.CPeriod::IsWithin(GetFromToPosition(::MIN),GetFromToPosition(::MAX))==FALSE)
{


return FALSE;

}



/*2. tests for common weeks in bitvectors */

CBitvector bv(m_weekvector);
CBitvector bv2;

test.fillvector(bv2);

bv &= bv2;



if(bv.IsClear())
{

 return FALSE;}

else

{

/*3. compares both regularperiod objects for shared day */

BOOL IsDayshared(FALSE);





		
		
		if(test.IsEventfulDay(dayoftheweek))
		{
		 	 	 
		 IsDayshared = IsToil(dayoftheweek) || IsEventfulDay(dayoftheweek);
		 
		 }
		 
		 
		 
		


return IsDayshared;
	}

}


BOOL CDebitPeriod::dayshared(CRegularPeriod& test)
{
 
 /* test for shared eventful day	*/

/*1. Is test within ball park? */


if(test.CPeriod::IsWithin(GetFromToPosition(::MIN),GetFromToPosition(::MAX))==FALSE)
{


return FALSE;

}



/*2. tests for common weeks in bitvectors */

CBitvector bv(m_weekvector);
CBitvector bv2;

test.fillvector(bv2);

bv &= bv2;



if(bv.IsClear())
{

 return FALSE;}

else

{

/*3. compares both regularperiod objects for shared day */

BOOL IsDayshared(FALSE);

CSpan* ptr=NULL;
UINT cnt(0);


		while(IsDayshared==FALSE && cnt<=6)
		{
		ptr = (CSpan*) m_dayarray->GetAt(cnt);

		
		if(test.IsEventfulDay(cnt))
		{
		 	 	 
		 IsDayshared = (IsToil(cnt) || IsEventfulDay(cnt));
		 
		 }
		 
		cnt++;
		} 


return IsDayshared;
	}

}

BOOL CDebitPeriod::IsEventfulDay(const UINT dayofweek)
{

/* tests to see if day has an event arranged */

 

 CSpan* ptr = (CSpan*) m_dayarray->GetAt(dayofweek);

 

 
 
 return (ptr->getduration().GetTotalMinutes()>0) ;
	

}


void CDebitPeriod::fillvector(CBitvector& tofill)
{


tofill = *m_weekvector;


}

void CDebitPeriod::Fix(const BOOL tethered=TRUE)
{

m_IsFixed = tethered;


}

CTime CDebitPeriod::getbasedate(void)
{

return m_basedate;

}

BOOL CDebitPeriod::Edit(const CTime basedate,const long weekstart)
{



CSOdialog dlg(basedate,NULL);
	dlg.m_parent=(CTimelist*) parent;
	dlg.whichtitle=dlg.Edit;
	dlg.m_original=this;
	dlg.weekstart = weekstart;
	
    

	// copy contents of dayarray into dlg.dayarray

	CSpan* ptr=NULL;

	for(int cnt=0;cnt<=6;cnt++)
	{

	 if(ptr = (CSpan*) m_dayarray->GetAt(cnt))
	 {
	  
	  
	  ptr = (CSpan*) ptr->clone();

	  dlg.m_dayarray->SetAt(cnt,ptr);}


	}
    
    dlg.nMin=(int) parent->GetFromToPosition(::MIN);
    dlg.nMax=(int) parent->GetFromToPosition(::MAX);
    
    dlg.from_position=(int) GetFromToPosition(::MIN);
    dlg.to_position=(int) GetFromToPosition(::MAX);
    
    dlg.m_freq=TRUE;
    
    dlg.m_fixed=m_IsFixed;

	*dlg.m_bitvector= *m_weekvector;
	*dlg.m_drpvector = *m_drpvector;

	

	



    if(dlg.DoModal()==IDOK)
    {
    
    

	// update m_dayarray

	

	CSpan* ptr=NULL;

	for(int cnt=0;cnt <=6;cnt++)
	{

	 
	 ptr = (CSpan*) m_dayarray->GetAt(cnt);

	 ptr->ResetPeriod((CSpan*) dlg.m_dayarray->GetAt(cnt));
	 	
	 
	}
	
	


	
    
    //time bars update operational period members
   
   
   SetFromToPosition(::MIN,(long) dlg.from_position);
   SetFromToPosition(::MAX,(long) dlg.to_position);

   Fix(dlg.m_fixed);

   *m_weekvector = *dlg.m_bitvector;
   *m_drpvector = *dlg.m_drpvector;

    return TRUE;
    }

else { return FALSE;}




}

#ifdef _DEBUG
void CDebitPeriod::Dump(CDumpContext& dc) const
{   
    
 CObject::Dump(dc);   
	
dc  << "\nUncle is= "<< uncle->Getname() << "\nParent= " << parent->Getname() <<"\n";
}
#endif //_DEBUG	



CObject* CDebitPeriod::Clone(void)
{



CObArray* dayarray = new CObArray;
dayarray->SetSize(7,0);

for(char cnt=0;cnt<=6;cnt++)
{
   dayarray->SetAt(cnt, m_dayarray->GetAt(cnt)); }
   
/* uses test object constructor so does not login */

CObject* ptr= new CDebitPeriod(	m_weekvector,
								m_drpvector,
								dayarray,
								GetFromToPosition(::MIN),
								GetFromToPosition(::MAX),
									parent,
									m_IsFixed,
									m_basedate);							
									
return ptr;



}


BOOL  CDebitPeriod::IsWithin(const CTimeSpan someotherstart, const CTimeSpan sometherduration, const int day)
{

 
 CSpan* spanptr = (CSpan*) m_dayarray->GetAt(day);

 if(spanptr->IsWithin(someotherstart, sometherduration) && spanptr->getduration().GetTotalMinutes()>0)
 {
 
 return TRUE; }

 else 

 { return FALSE;}
  

}

BOOL CDebitPeriod::showmenu(CView* handle, const CPoint& coords)
{ 


    	
   CMenu popup;
   
    

	popup.CreatePopupMenu();

	
	popup.AppendMenu(MF_STRING,ID_EDITINSTRUCTION,_T("&Edit Shift"));
	popup.AppendMenu(MF_STRING,ID_MOVE,_T("&Move Shift"));
	popup.AppendMenu(MF_STRING,ID_DELETEINSTRUCTION,_T("&Delete Shift"));
	popup.TrackPopupMenu(TPM_LEFTBUTTON ,coords.x ,coords.y + 150, handle ,0);
	popup.Detach();
	
	
	
 return TRUE;
 
 }


 

LRESULT CDebitPeriod::SetFromToPositionToCredit(const int flag, const long value)
{

LRESULT nResult(0);

try
	{

	

	switch(flag)
		{

		case ::MIN:
			{
			//adjust the from position

			if(value > GetFromToPosition(::MIN))
				{
				SetFromToPosition(::MAX,value);
				SetFromToPosition(::MIN,value);
				ClearWeeks();
				
				}
			 if(value <= GetFromToPosition(::MIN) && value < GetFromToPosition(::MAX) )
				{

				SetFromToPosition(::MIN,value);
				

				}

			
			}
			break;
		case ::MAX:
			{
			// adjust the to position

			if(value < GetFromToPosition(::MIN) )
				{

				SetFromToPosition(::MAX,value);
				SetFromToPosition(::MIN,value);
				ClearWeeks();

				}
			
			if(value >= GetFromToPosition(::MIN) && value < GetFromToPosition(::MAX) )
				{

				SetFromToPosition(::MAX,value);
				

				}

			
			
			}
			break;
		default:
			{ 
			AfxThrowUserException();
			}
			break;



		}


	}
catch(CUserException* e)
	{



	}
return nResult;

}

void CDebitPeriod::ClearWeeks(void)
{

m_weekvector->reset();

}



BOOL CDebitPeriod::IsClearWeeks(void)
{
BOOL one_checked(false);

try
	{

	if(!m_weekvector){ AfxThrowUserException();}

	for(UINT cnt(0);cnt<4;cnt++)
		{

		one_checked=(m_weekvector->IsSet(cnt));
		if(one_checked){ break;}

		}

	}
catch(CUserException* e)
	{

	AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);


	}

return (!one_checked);


}
