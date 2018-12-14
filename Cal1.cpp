// cal1.cpp : implementation file
//
#include "stdafx.h"
#include <afxdb.h>
#include <afxdao.h>
//#include "centool8.h"
//#include "absolute.h"
//#include "span.h"
//#include "period.h"
//#include "timelist.h"
//#include "contract.h"
//#include "estab.h"
//#include "state.h"
//#include "calstate.h"
//#include "yrstat.h"
//#include "frwkstat.h"
//#include "wkstat.h"
//#include "daystate.h"
#include "rotaview.h"
/*#include "log2.h" */ 

#include <stdio.h>
#include "assert.h"

#include "cal1.h"
//#include "bitvec.h"

#include <math.h>




#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCalendar




CCalendar::CCalendar(CTime basedate):  Calendar_options(NULL),
									   pCalstate(NULL),
									   pOffset(NULL),
									   pBudget_state(NULL),
									   m_currentperiod(NULL),
									   m_currentfourweek(NULL),
									   m_currentyear(NULL),
									   m_BASE_DATE(basedate),
									   m_copyshowing(0),
									   m_content_org(110,95)
									   
									   
{

Calendar_options = new CMapWordToOb;


CObject* ptr = new CYearstate();	/* 6 font width */


Calendar_options->SetAt(ID_CALENDAR_YEAR,ptr);

	ptr = new CFourweekstate();

Calendar_options->SetAt(ID_FOURWEEK,ptr);


	ptr = new CWeekstate();

Calendar_options->SetAt(ID_WEEK,ptr);


  
ptr = new CDaystate();

Calendar_options->SetAt(ID_DAY,ptr);


pOffset= new Offset;
pBudget_state = new Budget_state;

pBudget_state->content=debit_only;
pBudget_state->Is_Cummulative=FALSE;
m_currentyear = new CAbsolutePeriod(m_BASE_DATE,::NONE,::ONE_YEAR);
m_currentfourweek=new CAbsolutePeriod(m_BASE_DATE);
m_currentperiod=new CAbsolutePeriod(m_BASE_DATE);

OnFourweek(0);
OnWeekOne();



}




CCalendar::~CCalendar() {

CObject* ptr; WORD id(0);

POSITION pos= Calendar_options->GetStartPosition();

while(!Calendar_options->IsEmpty())
	{ 
	
	Calendar_options->GetNextAssoc(pos,id,ptr);
	Calendar_options->RemoveKey(id);
	assert(id==ID_CALENDAR_YEAR ||
	       id==ID_FOURWEEK ||
		   id==ID_WEEK ||
		   id == ID_DAY);
	delete ptr;} 


delete Calendar_options;


delete pOffset;
delete pBudget_state;
delete m_currentyear;
delete m_currentfourweek;
delete m_currentperiod;

 
} 



/////////////////////////////////////////////////////////////////////////////
// cal1 message handlers

void CCalendar::ResetBasedate(CTime basedate)
{


m_BASE_DATE=basedate;
m_currentyear->ResetPeriod(m_BASE_DATE,::NONE,::ONE_YEAR);
m_currentfourweek->ResetPeriod(m_BASE_DATE);
m_currentperiod->ResetPeriod(m_BASE_DATE);


OnFourweek(0);
OnWeekOne();
}

CTime CCalendar::GetBaseDate(void)
{

return m_BASE_DATE;


}

void CCalendar::OnPrepareDC(CDC* pDC)
{

// offset area to draw by width of margin (120 pixels)
   
//pDC->SetViewportOrg(120,0);

pDC->SetViewportOrg(110,0);
   
pCalstate->OnPrepareDC(pDC);


}

CPoint CCalendar::GetContentOrg(void)
{


return m_content_org;

}

		
CString CCalendar::Getcurrent_startstring(void)
	  	{
	  	  return m_currentperiod->Get_start_string(); }

CString CCalendar::Getcurrent_finishstring(void)
	  	{
	  	  return m_currentperiod->Get_finish_string(); }

CString CCalendar::Getcurrent_near_finishstring(void)
	  	{
	  	  return m_currentperiod->Get_near_finish_string(); }

long CCalendar::getfourweekoffset(void)
{

return pOffset->fourweekoffset;

}

long CCalendar::getweekoffset(void)
{

return pOffset->weekoffset;

}

long CCalendar::getdayoffset(void)
{

return pOffset->dayoffset;

}


long CCalendar::get_days_into_period(void)
{

return (getweekoffset() * 7) + getdayoffset();


} 

void CCalendar::getcurrentweek(long& daystofill)
{
daystofill=0;
daystofill+=pOffset->fourweekoffset * 28;
daystofill+=pOffset->weekoffset * 7;

}

enum Transaction CCalendar::GetBudgetState(void)
{


return pBudget_state->content;

}

CString CCalendar::set_totals_heading(CString colhead,CView* handle)
{

if(!handle){ AfxThrowUserException();}

CRotaview*viewptr = (CRotaview*) handle;
		UINT currently_showing(0);
		viewptr->getshowing(currently_showing);
try
	{
		switch(Is_Budget_Cummulative())
		{

		case FALSE:

		colhead="\n";

		break;


		case TRUE:


		colhead="Cum\n";

		break;
		default:

	AfxThrowUserException();

	}


			switch(GetBudgetState())
			{
	
			 case credit_only:
	  
			colhead += "\nCon";
	  		break;


			case debit_only:
	  
	  	

			switch(	currently_showing)
			{

			case ID_FORMAT_DUR_SEVENHALF:
	  
			colhead += "7.5hr\nDays";
			break;

	 

			case ID_FORMAT_DUR_SEVENTWELVE:
	  
			colhead += "7.2hr\nDays";
			break;


			case ID_FORMAT_DUR_SEVENTWENTYFOUR:
	  
		 	colhead += "7.4hr\nDays";
			break;


			case ID_FORMAT_DUR_SEVENTHIRTYSIX:
	  
		 	colhead += "7.6hr\nDays";
		 	break;


			default:

			colhead += "\nHrs";


			}//end switch

	  break;
	  case balance :
	
		colhead += "\nBal";
		break;
		
		     
	  default:
	  	AfxThrowUserException();
	  	
	
	
	}



	}//end try

catch(CUserException e)
	{


	 AfxMessageBox(IDS_PGERR,MB_OK,0);





	}

	
	

return colhead;

} 


BOOL CCalendar::Is_Budget_Cummulative(void)
{


return pBudget_state->Is_Cummulative;


}


		
CAbsolutePeriod CCalendar::GetCurrentPeriod(void)
{

return *m_currentperiod;

}


BOOL CCalendar::Is_shortperiod(void)
{

// used by view when formating strings.
// Shorter periods allow longer strings.  


return (pCalstate->Getstate()==ID_WEEK || pCalstate->Getstate()==ID_DAY);

}



void CCalendar::docket(CPeriodlist* datalist, CTimelist* proxylist)
{

long MAXCOUNT(0);
long count(0);

  CAbsolutePeriod terminus_ab_quo(GetCurrentPeriod());

   


   CBitvector bv;
   
   int weekno , fwkno;
   
   weekno = fwkno = 0;

  
 // CAbsolutePeriod smalltime = new CAbsolutePeriod(terminus_ab_quo,::NONE,::ONE_DAY);

  CAbsolutePeriod smalltime(terminus_ab_quo,::NONE,::ONE_DAY);

  

   if(Is_Budget_Cummulative()==TRUE )
   {

    MAXCOUNT= GetTotalOffset();
	terminus_ab_quo.ResetPeriod(GetBaseDate());
	smalltime.ResetPeriod(terminus_ab_quo,::NONE,::ONE_DAY);

	BOOL verdict(TRUE);	

	while(count< MAXCOUNT)
   {
    verdict=TRUE; 

	

    proxylist->prioritise(GetBaseDate(),smalltime,GetBudgetState(), fwkno, verdict);
     			
	
 
	 
	smalltime++;
    
    if(weekno == 6)
	{
	  if(fwkno==3)
		{

		
		
		fwkno=0;
	

		}

		else
		{
	 	  
	 	  fwkno++;
		  
	 	}

	weekno=0;
	}
	
	else
	{
	
	 weekno++;
	
	}	    

	
	
	count++	;



   	} // end while
   	
   }//end if cummulative

   else	  // non cummulative
   {

    MAXCOUNT = GetCurrentPeriod().getduration().GetDays() ; 

	weekno = fwkno = 0; 
	
  	setrepeater(bv);	// offsets week to that being viewed 
  	
  	BOOL verdict(TRUE); 
      
   while(count< MAXCOUNT)
   {
     
	verdict=TRUE;
    proxylist->prioritise(GetBaseDate(),smalltime,GetBudgetState(), bv.firstset(), verdict);
     			
	// proxylist->prioritise(GetBaseDate(),smalltime,credit_only, bv.firstset(), verdict);
	//smalltime+=::ONE_DAY;
	smalltime++;
    
    if(weekno == 6)
	{
	  if(fwkno==3)
		{

		setrepeater(bv);
		
		fwkno=0;
	

		}//end if fwkno==3

		else
		{
	 	  bv >> 1;
	 	  fwkno++;
		  
	 	}

	weekno=0;
	} // end if weekno == 6
	
	else
	{
	
	 weekno++;
	
	}//end else
	
		    
	
	count++;
       
   } //end while


   } // end else






}

		
void CCalendar::display(CView* handle,
						CDC* pDC,
						CTimelist* ptr,
						CPeriodlist* datalist)
{

 
	
pCalstate->set_calendar_ptr(this);



CRect bigbox(38,4,41,100);

/* cummulative view has one less column
 and more to display so give it a slightly bigger box */

if(Is_Budget_Cummulative()){ bigbox.SetRect(38,4,42,100);}



CRect totals_column_box(&bigbox);
  
  ptr->Clearbalance(); 
	
  // seed data


  docket(datalist,ptr);
  
   
   CString column_heading;
	
  
    
   
   // offset totals downwards 
   
   totals_column_box.OffsetRect(0, 10);	

   // extra totals column for contracts (because of grouping at top level) 
	// Totals Column 2	
   	
   	set_special_format(handle);
   	
   	ptr->rebalance();

    ptr->displayallSum(GetBaseDate(),&totals_column_box,GetCurrentPeriod(),pDC,handle);

	
	
    restore_special_format(handle);
   	
	
	



	
	set_special_format(handle);

	   ptr->sum_all_data(&totals_column_box,pDC,handle); 
        

	/* contractual hours column */

	totals_column_box.OffsetRect((bigbox.Size().cx),0);

	CPoint pt(totals_column_box.TopLeft().x,bigbox.TopLeft().y);

	CRect headingbox(pt,totals_column_box.Size());
	
	pDC->DrawText(set_totals_heading(column_heading,handle),-1,headingbox,DT_LEFT);
    

	

	// remember budget state 

	Transaction t = pBudget_state->content;
	BOOL cumstate = pBudget_state->Is_Cummulative;
	
	/* set special budget for contractual hours */

	pBudget_state->content = credit_only;

	 ptr->Clearbalance(); 
	
  // seed data


  docket(datalist,ptr);


    ptr->rebalance();

	headingbox.OffsetRect((headingbox.Size().cx),0);

	pDC->DrawText(set_totals_heading(column_heading,handle),-1,headingbox,DT_LEFT);
    
	
	 ptr->sum_all_data(&totals_column_box,pDC,handle); 

	
	
	
	

	// create balance column

	ptr->Clearbalance();

		/* set special budget for contractual hours */
	
	pBudget_state->content = balance;


	docket(datalist,ptr);


    ptr->rebalance();


	totals_column_box.OffsetRect((bigbox.Size().cx),0);
	headingbox.OffsetRect((headingbox.Size().cx),0);

	pDC->DrawText(set_totals_heading(column_heading,handle),-1,headingbox,DT_LEFT);
    

	 ptr->sum_all_data(&totals_column_box,pDC,handle); 



	// create cummulative balance column if not cummulative state already

	if(!Is_Budget_Cummulative()) 
	{

	ptr->Clearbalance();

		/* set special budget for cummulative balance */
	
	
	pBudget_state->content = balance;
	pBudget_state->Is_Cummulative = TRUE;


	docket(datalist,ptr);


    ptr->rebalance();


	totals_column_box.OffsetRect((bigbox.Size().cx),0);
	headingbox.OffsetRect((headingbox.Size().cx),0);

	pDC->DrawText(set_totals_heading(column_heading,handle),-1,headingbox,DT_LEFT);
    

	 ptr->sum_all_data(&totals_column_box,pDC,handle); 
	
	}
	
	 
	// restore settings

	ptr->Clearbalance();

	pBudget_state->content = debit_only;
	
	pBudget_state->Is_Cummulative = cumstate; 

	restore_special_format(handle);
	
    
    


  

OnPrepareDC(pDC);   
pCalstate->display(handle,pDC,ptr,datalist);
	
 
}

void CCalendar::set_special_format(CWnd* handle)
{

CRotaview* rotaptr=(CRotaview*) handle;
rotaptr->getshowing(m_copyshowing);	//  temporarily changes view
assert(m_copyshowing);

// if is already showing a duration format, do nothing

switch(m_copyshowing)
{
case ID_VIEW_FORMAT_HRS :

break;

case ID_FORMAT_DUR_SEVENHALF :

break;

case ID_FORMAT_DUR_SEVENTWELVE :

break;

case ID_FORMAT_DUR_SEVENTWENTYFOUR :

break;

case ID_FORMAT_DUR_SEVENTHIRTYSIX :

break;

default:

rotaptr->setshowing(ID_VIEW_FORMAT_HRS); //  one off format

break;
	 }

}


void CCalendar::restore_special_format(CWnd* handle)
{

CRotaview* rotaptr=(CRotaview*) handle;

rotaptr->setshowing(m_copyshowing);
m_copyshowing=0;


}

CString CCalendar::set_column_heading(CAbsolutePeriod& start, CString& daystring)
{

return daystring;

}


void CCalendar::DrawMe(CPeriod* me,CRect& copybox,CDC* pDC)
{


pCalstate->DrawMe(me,copybox,pDC);


}



BOOL CCalendar::print(CView* handle,
						CDC* pDC,
						CTimelist* ptr,
						CPeriodlist* datalist)
{

pCalstate->OnPrepareDC(pDC);
return  pCalstate->print( handle,pDC,ptr,datalist);




}


UINT CCalendar::Getstate(void)
{

return pCalstate->Getstate();


}

long CCalendar::GetTotalOffset(void)
{
CTimeSpan thisperiod(::NONE);

long total(0);

total=
(pOffset->fourweekoffset * 28)
+ (pOffset->weekoffset * 7) 
+ (pOffset->dayoffset)
+ (m_currentperiod->getduration()).GetDays();



return total;

}





/* The Calendar object generates the Time axis of the Rota. In this case,
the x axis. The default view is the week one of the current fourweek view. So the calendar keeps track
of the offsets applied by the user to the BASEDATE
which it embodies in the CAbsolutePeriod pointed to by m_currentperiod.
When called to display, it provides the current view and then 
manipulates the viewport origin and extent to zoom in and out, providing the
views corresponding to the states ID_DAY, ID_WEEK, ID_FOURWEEK, ID_YEAR
*/ 

void CCalendar::OnCalendarYear(void)
{

CObject* ptr;

Calendar_options->Lookup(ID_CALENDAR_YEAR,ptr);	
pCalstate= (Calstate*) ptr;

pOffset->fourweekoffset= 0;
pOffset->weekoffset=0;
pOffset->dayoffset=0;
pOffset->m_WeekFrag=0;
pOffset->m_DayFrag=0; 




m_currentfourweek->ResetPeriod(m_BASE_DATE,0,ID_FOURWEEK);
m_currentperiod->ResetPeriod(*m_currentyear);




}

void CCalendar::OnUpdateCalendarYear(CCmdUI* pCmdUI)
{



pCmdUI->SetCheck(pCalstate->Is_state(ID_CALENDAR_YEAR));



}
 	
void CCalendar::OnFourweek(const long index)
{
	// TODO: Add your command handler code here 
	
CObject* ptr;

Calendar_options->Lookup(ID_FOURWEEK,ptr);	
pCalstate= (Calstate*) ptr;

pOffset->fourweekoffset= index;
pOffset->weekoffset=0;
pOffset->dayoffset=0;
pOffset->m_WeekFrag=0;
pOffset->m_DayFrag=0; 




m_currentfourweek->ResetPeriod(m_BASE_DATE,index *28,ID_FOURWEEK);
m_currentperiod->ResetPeriod(*m_currentfourweek);
	
	
	
}

void CCalendar::OnUpdateFourweek(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	
	    BOOL outcome(pCalstate->Getstate()==ID_FOURWEEK);
	    
	    switch(outcome)
	    {
	    case TRUE:{ pCmdUI->SetCheck(2); }
	    break;
	    default: { pCmdUI->SetCheck(0);}
	    
	    
	    }
	     
			
	
}

void CCalendar::OnWeekOne(void)
{
	// TODO: Add your command handler code here
	 
CObject* ptr;

Calendar_options->Lookup(ID_WEEK,ptr);	
pCalstate= (Calstate*) ptr;

pOffset->m_WeekFrag=ID_WEEK_ONE;
pOffset->weekoffset=pOffset->dayoffset=pOffset->m_DayFrag=0; 




m_currentperiod->ResetPeriod(m_BASE_DATE,(long) pOffset->fourweekoffset * 28,ID_WEEK);


	
}

void CCalendar::OnUpdateWeekOne(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
		
	if(pOffset->m_WeekFrag==ID_WEEK_ONE && pCalstate->Getstate()==ID_DAY)
	{ pCmdUI->SetCheck(2);}
	
	else
		
	{pCmdUI->SetCheck(pOffset->m_WeekFrag==ID_WEEK_ONE);}
}    

void CCalendar::OnWeekTwo(void)
{
	// TODO: Add your command handler code here 
	
CObject* ptr;

Calendar_options->Lookup(ID_WEEK,ptr);	
pCalstate= (Calstate*) ptr;
	
pOffset->weekoffset=1;
pOffset->dayoffset=pOffset->m_DayFrag=0;
pOffset->m_WeekFrag=ID_WEEK_TWO;


long total_offset=(pOffset->fourweekoffset * 28) + 7;

m_currentperiod->ResetPeriod(m_BASE_DATE,total_offset,ID_WEEK);
 
	
}

void CCalendar::OnUpdateWeekTwo(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	
	if(pOffset->m_WeekFrag==ID_WEEK_TWO && pCalstate->Getstate()==ID_DAY)
	{ pCmdUI->SetCheck(2);}
	
	else
	
	{ pCmdUI->SetCheck(pOffset->m_WeekFrag==ID_WEEK_TWO);}
} 

void CCalendar::OnWeekThree(void)
{
	// TODO: Add your command handler code here
	
	 
	CObject* ptr;

	Calendar_options->Lookup(ID_WEEK,ptr);	
	pCalstate= (Calstate*) ptr;
	
	pOffset->weekoffset=2;
	pOffset->dayoffset=pOffset->m_DayFrag=0;
	pOffset->m_WeekFrag=ID_WEEK_THREE;
	
	
   long total_offset=0;	
   total_offset=(pOffset->fourweekoffset * 28) + 14;

m_currentperiod->ResetPeriod(m_BASE_DATE,total_offset,ID_WEEK);
	
	
}

void CCalendar::OnUpdateWeekThree(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
	
	if(pOffset->m_WeekFrag==ID_WEEK_THREE && pCalstate->Getstate()==ID_DAY)
	{ pCmdUI->SetCheck(2);}
	
	else
	
	{ pCmdUI->SetCheck(pOffset->m_WeekFrag==ID_WEEK_THREE);}	
}

void CCalendar::OnWeekFour(void)
{
	// TODO: Add your command handler code here 
	
	CObject* ptr;

	Calendar_options->Lookup(ID_WEEK,ptr);	
	pCalstate= (Calstate*) ptr;

	pOffset->weekoffset=3;
	pOffset->dayoffset=	pOffset->m_DayFrag=0;
	pOffset->m_WeekFrag=ID_WEEK_FOUR;

	
long total_offset=total_offset=(pOffset->fourweekoffset *28) + 21;


m_currentperiod->ResetPeriod(m_BASE_DATE,total_offset,ID_WEEK);
	
	
}

void CCalendar::OnUpdateWeekFour(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	
	if(pOffset->m_WeekFrag==ID_WEEK_FOUR && pCalstate->Getstate()==ID_DAY)
	{ pCmdUI->SetCheck(2);}
	
	else
	
	{ pCmdUI->SetCheck(pOffset->m_WeekFrag==ID_WEEK_FOUR);}
}        

void CCalendar::OnDayMonday(void)
{

CObject* ptr;

Calendar_options->Lookup(ID_DAY,ptr);	
pCalstate= (Calstate*) ptr;


pOffset->m_DayFrag=ID_DAY_MONDAY;

if(pOffset->weekoffset==0){pOffset->m_WeekFrag=ID_WEEK_ONE;}
pOffset->dayoffset=0;

	
long total_offset=total_offset=(pOffset->fourweekoffset *28);
total_offset += (pOffset->weekoffset * 7);

m_currentperiod->ResetPeriod(m_BASE_DATE,total_offset,ID_DAY);



}
void CCalendar::OnUpdateDayMonday(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	pCmdUI->SetCheck(pOffset->m_DayFrag==ID_DAY_MONDAY);
	
}

void CCalendar::OnDayTuesday(void)
{

CObject* ptr=NULL;
Calendar_options->Lookup(ID_DAY,ptr);	
pCalstate= (Calstate*) ptr;

pOffset->m_DayFrag=ID_DAY_TUESDAY;
if(pOffset->weekoffset==0){pOffset->m_WeekFrag=ID_WEEK_ONE;}
pOffset->dayoffset=1;



	
long total_offset=total_offset=(pOffset->fourweekoffset *28);
total_offset += (pOffset->weekoffset * 7) + 1;

m_currentperiod->ResetPeriod(m_BASE_DATE,total_offset,ID_DAY);

}
void CCalendar::OnUpdateDayTuesday(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	pCmdUI->SetCheck(pOffset->m_DayFrag==ID_DAY_TUESDAY);
	
} 

void CCalendar::OnDayWednesday(void)
{
CObject* ptr=NULL;
Calendar_options->Lookup(ID_DAY,ptr);	
pCalstate= (Calstate*) ptr;

pOffset->m_DayFrag=ID_DAY_WEDNESDAY;
if(pOffset->weekoffset==0){pOffset->m_WeekFrag=ID_WEEK_ONE;}
pOffset->dayoffset=2;



	
long total_offset=total_offset=(pOffset->fourweekoffset *28);
total_offset += (pOffset->weekoffset * 7) + 2;

m_currentperiod->ResetPeriod(m_BASE_DATE,total_offset,ID_DAY);

}
void CCalendar::OnUpdateDayWednesday(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 

	pCmdUI->SetCheck(pOffset->m_DayFrag==ID_DAY_WEDNESDAY);
	
}
void CCalendar::OnDayThursday(void)
{

CObject* ptr=NULL;
Calendar_options->Lookup(ID_DAY,ptr);	
pCalstate= (Calstate*) ptr;

pOffset->m_DayFrag=ID_DAY_THURSDAY; 
if(pOffset->weekoffset==0){pOffset->m_WeekFrag=ID_WEEK_ONE;}
pOffset->dayoffset=3;



	
long total_offset=total_offset=(pOffset->fourweekoffset *28);
total_offset += (pOffset->weekoffset * 7) + 3;

m_currentperiod->ResetPeriod(m_BASE_DATE,total_offset,ID_DAY);


}
void CCalendar::OnUpdateDayThursday(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	pCmdUI->SetCheck(pOffset->m_DayFrag==ID_DAY_THURSDAY);
	
} 

void CCalendar::OnDayFriday(void)
{ 

CObject* ptr=NULL;
Calendar_options->Lookup(ID_DAY,ptr);	
pCalstate= (Calstate*) ptr;

pOffset->m_DayFrag=ID_DAY_FRIDAY;
if(pOffset->weekoffset==0){pOffset->m_WeekFrag=ID_WEEK_ONE;}
pOffset->dayoffset=4;



	
long total_offset=total_offset=(pOffset->fourweekoffset *28);
total_offset += (pOffset->weekoffset * 7) + 4;

m_currentperiod->ResetPeriod(m_BASE_DATE,total_offset,ID_DAY);


}
void CCalendar::OnUpdateDayFriday(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	pCmdUI->SetCheck(pOffset->m_DayFrag==ID_DAY_FRIDAY);
	
}  

void CCalendar::OnDaySaturday(void)
{

CObject* ptr=NULL;
Calendar_options->Lookup(ID_DAY,ptr);	
pCalstate= (Calstate*) ptr;

pOffset->m_DayFrag=ID_DAY_SATURDAY;
if(pOffset->weekoffset==0){pOffset->m_WeekFrag=ID_WEEK_ONE;}
pOffset->dayoffset=5;



	
long total_offset=total_offset=(pOffset->fourweekoffset *28);
total_offset += (pOffset->weekoffset * 7) + 5;

m_currentperiod->ResetPeriod(m_BASE_DATE,total_offset,ID_DAY);


}
void CCalendar::OnUpdateDaySaturday(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
pCmdUI->SetCheck(pOffset->m_DayFrag==ID_DAY_SATURDAY);
	
}

void CCalendar::OnDaySunday(void)
{ 

CObject* ptr=NULL;
Calendar_options->Lookup(ID_DAY,ptr);	
pCalstate= (Calstate*) ptr;

pOffset->m_DayFrag=ID_DAY_SUNDAY;
if(pOffset->weekoffset==0){pOffset->m_WeekFrag=ID_WEEK_ONE;}
pOffset->dayoffset=6;



	
long total_offset=total_offset=(pOffset->fourweekoffset *28);
total_offset += (pOffset->weekoffset * 7) + 6;

m_currentperiod->ResetPeriod(m_BASE_DATE,total_offset,ID_DAY);


}
void CCalendar::OnUpdateDaySunday(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	pCmdUI->SetCheck(pOffset->m_DayFrag==ID_DAY_SUNDAY);
	
}


void CCalendar::OnUpdateViewFormatHrs(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
	
}


void CCalendar::OnUpdateViewFormatBlockgraph(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	
	pCmdUI->Enable( pBudget_state->content!=balance &&
					pBudget_state->content!=credit_only &&
					pCalstate->Getstate()!=ID_FOURWEEK &&
					pCalstate->Getstate()!=ID_CALENDAR_YEAR);
}

void CCalendar::OnUpdateViewFormatStartfinish(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	
	pCmdUI->Enable( pBudget_state->content!=balance  &&
					pBudget_state->content!= credit_only  &&
					pCalstate->Getstate()!=ID_FOURWEEK &&
					pCalstate->Getstate()!=ID_CALENDAR_YEAR );
}


void CCalendar::OnBudgetCredit(void)
{


pBudget_state->content= credit_only;




}


void CCalendar::OnBudgetDebit(void)
{


pBudget_state->content= debit_only;




}



void CCalendar::OnBudgetBalance(void)
{


pBudget_state->content= balance;




}


void CCalendar::OnBudgetCummulative(const BOOL flag = FALSE)
{


pBudget_state->Is_Cummulative = flag;

} 



void CCalendar::OnUpdateBudgetCurrentCredit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	

	
	pCmdUI->SetCheck(pBudget_state->content==credit_only &&
					 pBudget_state->Is_Cummulative==FALSE);

	
}


void CCalendar::OnUpdateBudgetCurrentDebit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	

	
	pCmdUI->SetCheck(pBudget_state->content==debit_only &&
					 pBudget_state->Is_Cummulative==FALSE);

	
}  

void CCalendar::OnUpdateBudgetCurrentBalance(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	
    
	
	pCmdUI->SetCheck(pBudget_state->content== balance &&
					 pBudget_state->Is_Cummulative==FALSE);

	
}

void CCalendar::OnUpdateBudgetCummulativeCredit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	

	
	pCmdUI->SetCheck(pBudget_state->content==credit_only &&
					 pBudget_state->Is_Cummulative==TRUE);
	
}


void CCalendar::OnUpdateBudgetCummulativeDebit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	

	
	pCmdUI->SetCheck(pBudget_state->content==debit_only &&
					 pBudget_state->Is_Cummulative==TRUE);
	
} 

BOOL CCalendar::EditBank(CDaoDatabase& db, CTimelist* ptr,  CPeriodlist* datalist)
{
 /* prime balance of each bank contract */
   // create the current year

   BOOL success(TRUE);
   
   
   ptr->Clearbalance();

   

   docket(datalist,ptr);

   

   ptr->rebalance();
   
   ((CEstab*)ptr)->SubstituteConID(db,m_currentyear->Get_absolute_finishtime(),get_days_into_period());
   success = ((CEstab*)ptr)->EditBank(db,m_currentyear->Get_absolute_finishtime(),get_days_into_period()); 

   ptr->Clearbalance();
   
   return success; 

}

#ifndef STANDALONE
void CCalendar::OnFileUpdatedatabase(CLog& ds, CTimelist* ptr, CPeriodlist* datalist)
{

/* calendar selects objects. Rebalance for current week*/

	

 
CAbsolutePeriod start(*m_currentperiod,::NONE,::ONE_DAY);

   CBitvector bv;
   setrepeater(bv);
   
   ptr->Clearbalance();

   BOOL verdict(TRUE);
   
   for(int cnt=0;cnt<7;cnt++)
       {
	verdict = TRUE;
    ptr->prioritise(GetBaseDate(),start,debit_only, bv.firstset(),verdict);			
	ptr->OnFileUpdateDatabase(ds,"",((CContract*) ptr)->get_contract_holder_ID(),((CContract*) ptr)->get_table_ID(), start);
	
	start++;
    ptr->Clearbalance();   
   } 

 ((CEstab*) ptr)->RestoreContractNo(); 
} 

#endif 

void CCalendar::OnUpdateBudgetCummulativeBalance(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here 
	
    
	
	pCmdUI->SetCheck(pBudget_state->content== balance &&
					 pBudget_state->Is_Cummulative==TRUE);
	
} 

void CCalendar::setrepeater(CBitvector& counterperiod)
{

counterperiod.reset();






 switch(pOffset->m_WeekFrag)

 {

  case 0:	 // Fourweek or Calendar Year or cumulative

  counterperiod.set(0);

  break;

  case ID_WEEK_ONE :

  counterperiod.set(0);

  break;

  case ID_WEEK_TWO :

   counterperiod.set(1);

  break;

  case ID_WEEK_THREE :

  counterperiod.set(2);

  break;

  case ID_WEEK_FOUR :

  counterperiod.set(3);

  break;


  
  }




}



void CCalendar::SetBudgetcontent(const Transaction newstate)
{



pBudget_state->content = newstate;



}


void CCalendar::SetBudgetCummulative(const BOOL verdict)
{


pBudget_state->Is_Cummulative = verdict;


} 

CString CCalendar::Get_fwkweek(void)
{


char weekstring[10];

sprintf(weekstring, "%d", ((pOffset->fourweekoffset * 4) + pOffset->weekoffset));



return CString(weekstring);

}
