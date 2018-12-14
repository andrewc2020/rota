// calstate.cpp : implementation file
//
#pragma warning(disable : 4996)
#include "stdafx.h"
#include <afxdb.h>
#include <afxdao.h>
#include "CONSTANT.H"
//#include "centool8.h"
#include "span.h"
#include "absolute.h"
#include "period.h"
#include "timelist.h"
#include <stdio.h>
#include "bitvec.h"
#include "log2.h"
#include "cal1.h"
#include "state.h"
#include "calstate.h"
#include "assert.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Calstate

Calstate::Calstate(): calendar(NULL),bigdiv(1,100)
,m_divisions(0),m_subdivisions(0)
,m_div_span(::ONE_DAY),m_sub_div_span(::ONE_DAY),m_offset(2)
{




}

Calstate::~Calstate()
{




}


void Calstate::set_calendar_ptr(CCalendar* cal)
{



 calendar=cal;

}


void Calstate::OnPrepareDC(CDC* pDC)
{




}


 



BOOL Calstate::print(CView* handle,
						CDC* pDC,
						CTimelist* ptr,
						CPeriodlist* datalist)
{   

  	
	int days_in_period(m_divisions); // five records per page

	
   CPoint org(0,0);

  //create scaled box for iteration

  CRect bigbox(org,bigdiv);	 // A4 page size strip set in derived class

  bigbox.OffsetRect(bigbox.Size().cx * m_offset ,0);
    
  

CTimeSpan divtime(m_div_span);

	CAbsolutePeriod div_period(calendar->GetCurrentPeriod(),::NONE, m_div_span);
	
	CAbsolutePeriod start(calendar->GetCurrentPeriod(),::NONE, ::ONE_DAY);
	
	

	
   	CString daystring;
	
   	
	   
   CString column_heading;
   CBitvector bv;
   calendar->setrepeater(bv);
   
   
   int weekno(0), fwkno(0);

  pDC->TextOut(0,0,ptr->Getname());  
  pDC->TextOut(0,-250, start.Get_start_string(_T("%B %d %Y")));	// date on next line
  
  if( !ptr->printall(calendar->GetBaseDate(),calendar->GetCurrentPeriod(),pDC,handle))
  {
  
  
  return FALSE; }

  else

  {

   for(UINT crank=0; crank < m_divisions ; crank++)
   	{
   
   daystring= set_column_heading(div_period ,daystring);	
	
		 			
	pDC->DrawText(daystring,-1,bigbox,DT_CENTER);
	
	// layout directions
	
	pDC->MoveTo(bigbox.TopLeft().x + bigbox.Width(),bigbox.TopLeft().y);
	pDC->LineTo(bigbox.BottomRight());
		
   	ptr->Clearbalance();

	BOOL verdict(TRUE);
	
   		
	for(UINT cnt=0; cnt < m_subdivisions ;cnt++)
	{
   
	verdict=TRUE;
	
	ptr->prioritise(calendar->GetBaseDate(),start,calendar->GetBudgetState(), bv.firstset(),verdict);
		 	
	start++;

	
	
	if(weekno == 6)
	{
	  		if(fwkno==3)
			{

			calendar->setrepeater(bv);
			fwkno=0;
	

			}

			else

			{
	 	  
		  	bv >> 1;
	 	  	fwkno++;
		  
	 		}

		weekno=0;

		}
	
		else
		{
	
	 	weekno++;
	
		}	    
	
	}
	   
	
	ptr->rebalance();

	ptr->displayalldata(calendar->GetBaseDate(),&bigbox, div_period ,pDC,handle);
	bigbox.OffsetRect(bigdiv.cx,0);
	
	div_period++;

	} 
	
	//Total hrs break down column
	
	ptr->Clearbalance();
	
	calendar->SetBudgetcontent(debit_only); 

	calendar->docket(datalist,ptr);
	

  	CString colstring;

	bigbox.SetRect(bigbox.TopLeft().x,bigbox.TopLeft().y,bigbox.TopLeft().x + (bigbox.Size().cx * 0.75),bigbox.BottomRight().y	);
		// columns narrower by 3/4
     
  	

   CRect totals_column_box(&bigbox);
   
   	
   	
   	calendar->set_special_format(handle);
   	
   	ptr->rebalance();
    ptr->displayallSum(calendar->GetBaseDate(),&totals_column_box,calendar->GetCurrentPeriod(),pDC,handle);
	
    
									
	
    
	/* other totals columns Hrs, Chrs, Bal, Cum Bal */

	/* set special budget for Hrs */

	ptr->Clearbalance();
	
	


	calendar->docket(datalist,ptr);


    ptr->rebalance();


	totals_column_box.OffsetRect((bigbox.Size().cx),0);
	CPoint pt(totals_column_box.TopLeft().x,bigbox.TopLeft().y);

	CRect headingbox(pt,totals_column_box.Size());

	pDC->DrawText(calendar->set_totals_heading(colstring,handle),-1,headingbox,DT_LEFT);
    
	
	ptr->sum_all_data(&totals_column_box,pDC,handle); 

	/* set special budget for contractual hours Chrs */

	ptr->Clearbalance();
	
	calendar->SetBudgetcontent(credit_only);


	calendar->docket(datalist,ptr);


    ptr->rebalance();


	totals_column_box.OffsetRect((bigbox.Size().cx),0);
	headingbox.OffsetRect((headingbox.Size().cx),0);

	

	pDC->DrawText(calendar->set_totals_heading(colstring,handle),-1,headingbox,DT_LEFT);
    

	
	ptr->sum_all_data(&totals_column_box,pDC,handle); 

 	/* set special budget for balance */

	ptr->Clearbalance();
	
	calendar->SetBudgetcontent(balance);


	calendar->docket(datalist,ptr);


    ptr->rebalance();


	totals_column_box.OffsetRect((bigbox.Size().cx),0);
	headingbox.OffsetRect((headingbox.Size().cx),0);

	

	pDC->DrawText(calendar->set_totals_heading(colstring,handle),-1,headingbox,DT_LEFT);
    

	
	ptr->sum_all_data(&totals_column_box,pDC,handle); 

	// create cummulative balance column if not cummulative state already


	BOOL cummulative(calendar->Is_Budget_Cummulative());

	if(!cummulative) 
	{

	ptr->Clearbalance();

		/* set special budget for cummulative balance */
	
	
	calendar->SetBudgetcontent(balance);
	calendar->SetBudgetCummulative(TRUE); 


	calendar->docket(datalist,ptr);


    ptr->rebalance();


	totals_column_box.OffsetRect((bigbox.Size().cx),0);
	headingbox.OffsetRect((headingbox.Size().cx),0);

	pDC->DrawText(calendar->set_totals_heading(colstring,handle),-1,headingbox,DT_LEFT);
    

	  
	 ptr->sum_all_data(&totals_column_box,pDC,handle); 

	}
	
	 
	// restore settings

	ptr->Clearbalance();

	calendar->SetBudgetcontent(debit_only);
	
	calendar->SetBudgetCummulative(cummulative); 

	calendar->restore_special_format(handle);
 

 }
 
 return TRUE;	
  
} 



 
void Calstate::DrawMe(CPeriod* me,CRect& copybox,CDC* pDC)
{


// overridden in derived classes


}


CString Calstate::set_column_heading(CAbsolutePeriod& start, CString& daystring)
{



return daystring;
}



void Calstate::display(CView* handle,
						CDC* pDC,
						CTimelist* ptr,
						CPeriodlist* datalist)
{


	

	CTimeSpan divtime(m_div_span);

	CAbsolutePeriod div_period(calendar->GetCurrentPeriod(),::NONE, m_div_span);
	
	CAbsolutePeriod smalltime(calendar->GetCurrentPeriod(),::NONE, ::ONE_DAY);
	
	

	
   	CString daystring;
	
      
   
   //create scaled box for iteration

    	

	CPoint org(0,4);
	
	CRect bigbox(org,bigdiv);
	
	
	   
   CString column_heading;

   
   CBitvector bv;
   calendar->setrepeater(bv);

   int weekno(0), fwkno(0);


   

   for(UINT crank=0; crank < m_divisions ; crank++)
   	{
   
   daystring= set_column_heading(div_period ,daystring);	
	
		 			
	pDC->DrawText(daystring,-1,bigbox,DT_CENTER);
	
	// layout directions
	
	pDC->MoveTo(bigbox.TopLeft().x + bigbox.Width(),bigbox.TopLeft().y);
	pDC->LineTo(bigbox.BottomRight());
		
   	ptr->Clearbalance();

	BOOL verdict(TRUE);
   		
	for(UINT cnt=0; cnt < m_subdivisions ;cnt++)
	{

	verdict=TRUE;
   	
	ptr->prioritise(calendar->GetBaseDate(),smalltime,calendar->GetBudgetState(), bv.firstset(),verdict);

	smalltime++;

	
	
	if(weekno == 6)
	{
	  		if(fwkno==3)
			{

			calendar->setrepeater(bv);
			fwkno=0;
	

			}

			else

			{

			bv >> 1;
	 	  	
	 	  	fwkno++;
		  
	 		}

		weekno=0;

		}
	
		else
		{
	
	 	weekno++;
	
		}	    
	
	}


	ptr->rebalance();

	ptr->displayalldata(calendar->GetBaseDate(),&bigbox, div_period ,pDC,handle);
	bigbox.OffsetRect(bigdiv.cx,0);
	div_period++;

	
	
   }
   
	
 

}


void Calstate::display(CView* handle,
						CDC* pDC,
						CTimelist* ptr,
						CPeriodlist* datalist,CAbsolutePeriod& smalltime)
{

 CTimeSpan divtime(m_div_span);

	CAbsolutePeriod div_period(calendar->GetCurrentPeriod(),::NONE, m_div_span);
	
	//CAbsolutePeriod smalltime(calendar->GetCurrentPeriod(),::NONE, ::ONE_DAY);
	
	

	
   	CString daystring;
	
      
   
   //create scaled box for iteration

    	

	CPoint org(0,4);
	
	CRect bigbox(org,bigdiv);
	
	
	   
   CString column_heading;

   
   CBitvector bv;
   calendar->setrepeater(bv);

   int weekno(0), fwkno(0);


   

   for(UINT crank=0; crank < m_divisions ; crank++)
   	{
   
   daystring= set_column_heading(div_period ,daystring);	
	
		 			
	pDC->DrawText(daystring,-1,bigbox,DT_CENTER);
	
	// layout directions
	
	pDC->MoveTo(bigbox.TopLeft().x + bigbox.Width(),bigbox.TopLeft().y);
	pDC->LineTo(bigbox.BottomRight());
		
   	ptr->Clearbalance();

	BOOL verdict(TRUE);
   		
	for(UINT cnt=0; cnt < m_subdivisions ;cnt++)
	{

	verdict=TRUE;
   	
	ptr->prioritise(calendar->GetBaseDate(),smalltime,calendar->GetBudgetState(), bv.firstset(),verdict);

	//smalltime++;
	smalltime+=::ONE_DAY;
	
	
	if(weekno == 6)
	{
	  		if(fwkno==3)
			{

			calendar->setrepeater(bv);
			fwkno=0;
	

			}

			else

			{

			bv >> 1;
	 	  	
	 	  	fwkno++;
		  
	 		}

		weekno=0;

		}
	
		else
		{
	
	 	weekno++;
	
		}	    
	
	}


	ptr->rebalance();

	ptr->displayalldata(calendar->GetBaseDate(),&bigbox, div_period ,pDC,handle);
	bigbox.OffsetRect(bigdiv.cx,0);
	div_period++;

	
	
   }


}
