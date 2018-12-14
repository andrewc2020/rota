// absolute.cpp : implementation file
//

#include "stdafx.h"
//#include "centool8.h"
#include "resource.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "span.h"
#include <stdio.h>





#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbsolutePeriod  NB No serialisation or member intances Highly volatile


IMPLEMENT_DYNAMIC(CAbsolutePeriod,CObject)

/*
Constructors
1.) Default. Builds absolute period based on an arbitrary hard coded date
	midnight */


CAbsolutePeriod::CAbsolutePeriod(void):m_start(::NONE),m_duration(::NONE),m_absolute_midnight(1995,10,9,0,0,0)
{

//getpriormonday(); 



}

CAbsolutePeriod::CAbsolutePeriod(const CTime basedate): m_start(::NONE),m_duration(::FOUR_WEEKS),m_absolute_midnight(basedate)
{




}


/*1b ) builds from offset data. Assumes whole days */

CAbsolutePeriod::CAbsolutePeriod(const CTime basedate,
								const long from,
								const long to):
								m_start(::NONE),
								m_duration(::NONE)
{

if(from > to){ 
 AfxMessageBox(IDS_PGERR,MB_OK,0);
 AfxThrowUserException(); }

CTimeSpan dfb(from,0,0,0);
CTimeSpan dur(to - from,0,0,0);
m_absolute_midnight=basedate;
m_absolute_midnight+= dfb;
m_duration=dur;

} 

CAbsolutePeriod::CAbsolutePeriod(const CTime basedate,
								const long from,
								const long to,
								const CTimeSpan start):
								m_start(start),
								m_duration(::NONE)
{

if(from > to){ 
 AfxMessageBox(IDS_PGERR,MB_OK,0);
 AfxThrowUserException(); }

CTimeSpan dfb(from,0,0,0);
CTimeSpan dur(to - from,0,0,0);
m_absolute_midnight=basedate;
m_absolute_midnight+= dfb;
m_duration=dur;

} 


/* 2.) Makes deep copy of parameter object reference */


CAbsolutePeriod::CAbsolutePeriod(const CAbsolutePeriod& currentperiod): m_start(currentperiod.m_start), m_duration(currentperiod.m_duration),
m_absolute_midnight(currentperiod.m_absolute_midnight)
{   
 }
	

	
/* 3.) Pegs m_absolute_midnight of new object to parameter object with start and 
	 duration supplied. */
	 
CAbsolutePeriod::CAbsolutePeriod(const CAbsolutePeriod& someotherperiod, const CTimeSpan start, const CTimeSpan duration):  m_start(start), m_duration(m_duration), 
m_absolute_midnight(someotherperiod.m_absolute_midnight)
{   
	 } 

/* 3.b) Pegs m_absolute_midnight of new object to parameter stack copy object with start and 
	 duration supplied. */
	 	
/*CAbsolutePeriod::CAbsolutePeriod(const CAbsolutePeriod someotherperiod, const CTimeSpan start, const CTimeSpan duration):  m_start(start), m_duration(duration),
m_absolute_midnight(someotherperiod.m_absolute_midnight)
{   
 }    */
	
	

/* 5.) Provides complete data for new object in pieces */

CAbsolutePeriod::CAbsolutePeriod(const CTime datetime, const CTimeSpan start, const CTimeSpan duration):m_start(start),m_duration(duration),
m_absolute_midnight(datetime)
{



}





CAbsolutePeriod::~CAbsolutePeriod()
{


}


/* Other member functions

*/

/* 1. converts sunbased to monbased */

	
						
int CAbsolutePeriod::Sun2Mon(int sunbased){
	switch(sunbased){
		case 1: return 7;
		break;
		default: return sunbased-1;}
							}
							
/* 2. returns inFormation based on absolute midnight 

a) Day */


int CAbsolutePeriod::GetDay(void)
	{
		return m_absolute_midnight.GetDay();}
		
// b) date string
		
CString CAbsolutePeriod::GetDayStr(void)
	{   
		
		return m_absolute_midnight.FormatGmt("%A,%B %d,%Y");} 
		
// c) Day of the week Monday==0

int CAbsolutePeriod::GetDayOfWeek(void)
	{
		return Sun2Mon(m_absolute_midnight.GetDayOfWeek());}
		
// d) month number 1 to 12
		
int CAbsolutePeriod::Getmonth(void)		
	{
		return 	m_absolute_midnight.GetMonth();}
		
// e) year number

int CAbsolutePeriod::Getyear(void)		
	{
		return 	m_absolute_midnight.GetYear();}
		
/* 3.) Reset an existing CAbsolutePeriod

a) Peg to absolute midnight of parameter NB CPeriod unchanged.

*/

//deep copy

void CAbsolutePeriod::ResetPeriod(const CAbsolutePeriod& newperiod)
{
m_absolute_midnight=newperiod.m_absolute_midnight;
m_start=newperiod.m_start;
m_duration=newperiod.m_duration;
}

void CAbsolutePeriod::ResetPeriod(const CAbsolutePeriod& newperiod,const CTimeSpan start,const CTimeSpan duration)
{
m_absolute_midnight=newperiod.m_absolute_midnight;  

m_start=start;
m_duration=m_duration;

}


void CAbsolutePeriod::ResetPeriod(const CTime datetime, const CTimeSpan start, const CTimeSpan duration)
{  

m_absolute_midnight=datetime;
m_start=start;
m_duration=duration;


}

void CAbsolutePeriod::ResetPeriod(const CTimeSpan newstart, const CTimeSpan duration)
{

m_start=newstart;
m_duration=duration;

}

/* b) Repeg m_absolute_midnight by a whole number of days, earlier or later

NB CPeriod unchanged */ 

void CAbsolutePeriod::ResetPeriod(const int variation)
			{   
				
				int no_days=variation;
				if (no_days <0){ no_days= no_days * -1;}
				
				CTimeSpan days(no_days,0,0,0);
				if(variation>=0){ m_absolute_midnight += days;}
				 
				 else{ m_absolute_midnight-= days;}
				 
			}
			
			
void CAbsolutePeriod::ResetPeriod(const CTime basedate,const long from_position,const long to_position)
{
CAbsolutePeriod dummy(basedate,from_position,to_position);
*this=dummy;

}
			
void CAbsolutePeriod::ResetPeriod(const CTime basedate, const long numberdays, const int CommandID)
			{   
							
			    switch(CommandID)
			    {
			    
			    case ID_FOURWEEK: { m_duration=::FOUR_WEEKS;}
				
				break;
			    
			    case ID_WEEK:{ m_duration=::ONE_WEEK;}
			    
			    break;
			    
			    
			    case ID_DAY: { m_duration=::ONE_DAY;}
				
				break;
				
				}
								
				CTimeSpan days2add(numberdays,0,0,0);				
				m_absolute_midnight =basedate;
				m_absolute_midnight+=days2add;
				m_start=::NONE;
				
				
				
	}


CTime CAbsolutePeriod::Get_absolute_midnight(void)
{


return m_absolute_midnight;

}


long CAbsolutePeriod::Get_rota_num(const CTime occasion)
{

CTime fifthApril(occasion.GetYear(),4,5,0,0,0);

CTimeSpan diff(occasion - CAbsolutePeriod::Getnearestmonday(fifthApril));





if(diff< ::NONE)//if(diff<=::NONE)
{

diff = (occasion - Getnearestmonday(CTime(occasion.GetYear()-1,4,5,0,0,0)));


}


return diff.GetDays()/7;

}


CTime CAbsolutePeriod::Getnearestmonday(const CTime anydate)
{

const int MONDAY(2);
CTime moveable(anydate);
UINT cnt(0);


while(moveable.GetDayOfWeek()!=MONDAY && cnt < 6)
{
moveable +=::ONE_DAY;
cnt++;

}


return moveable;

}

CTime CAbsolutePeriod::Get_start_time(void)
{
return m_absolute_midnight+=m_start;

}

long CAbsolutePeriod::count_days(void)
{
return m_duration.GetDays();
}

long CAbsolutePeriod::gettotalstartmins(void)
{

return m_start.GetTotalMinutes();
}

long CAbsolutePeriod::gettotaldurmins(void)
{

return m_duration.GetTotalMinutes();


}

long CAbsolutePeriod::getstartoffset(const CTime basedate)
{

CTimeSpan diff(m_absolute_midnight-basedate);
//assert(diff>=0);
if(diff<0){ diff = ::NONE;}
return diff.GetDays();

}

long CAbsolutePeriod::getfinishoffset(const CTime basedate)
{
long startoffset=getstartoffset(basedate);
return startoffset+=count_days(); 


}


// information about relationship between this period and another



BOOL CAbsolutePeriod::IsWithinPeriod(CAbsolutePeriod scope)
{

return *this <= scope && *this >= scope;//<= scope && *this >= scope;
}

/* Operators




a)  makes deep copy */

void CAbsolutePeriod::operator =(const CAbsolutePeriod& someotherperiod)
{
m_absolute_midnight= someotherperiod.m_absolute_midnight;
m_start=someotherperiod.m_start;
m_duration=someotherperiod.m_duration;

}



//4.) NB  CPeriod NOT copied. Provides a means of repegging absolute part of period.

void CAbsolutePeriod::operator -=(const CTimeSpan time2minus)
	{
		
		m_absolute_midnight-=time2minus;}
		
void CAbsolutePeriod::operator +=(const CTimeSpan time2add)
	{
		
		m_absolute_midnight+=time2add;} 
		

	
/* increments period by duration */
		
void CAbsolutePeriod::operator ++(void)
	{   
		
		m_absolute_midnight+=m_duration;}
		 
/////"Prefix" operator here same to avoid warning fix properly
		
void CAbsolutePeriod::operator ++(int)
{


m_absolute_midnight+=m_duration;

}

		
void CAbsolutePeriod::operator --(void)
	{   
		m_absolute_midnight-=m_duration;
		
		} 
		
BOOL CAbsolutePeriod::operator <=(const CAbsolutePeriod& someotherperiod)
{  

	return m_absolute_midnight + m_start <= someotherperiod.m_absolute_midnight + someotherperiod.m_start + someotherperiod.m_duration;
}

BOOL CAbsolutePeriod::operator >=(const CAbsolutePeriod& someotherperiod)
{
  return m_absolute_midnight + m_start >= someotherperiod.m_absolute_midnight + someotherperiod.m_start;
}

long CAbsolutePeriod::operator /(const int denominator)
{ 
 ASSERT(denominator);
 return m_duration.GetTotalHours()/denominator;
}
/*
void CAbsolutePeriod::operator /(const int denominator)
{

CTimeSpan newlength(0,m_duration.GetTotalHours()/denominator,0,0);

m_duration=newlength;

}
*/

void CAbsolutePeriod::operator *(const int multiple)
{

int cnt=multiple;
while(cnt>0)
{
m_absolute_midnight+=m_duration;
cnt--; }

}

/* Change date to first Monday before existing date by subtracting days.
 CPeriod part (start and duration) unchanged.*/
  		
void CAbsolutePeriod::getpriormonday(void){
	
			int daynum=GetDayOfWeek();
			 CTimeSpan days2minus((daynum-1),0,0,0);
			 m_absolute_midnight -=days2minus;	}


/* Return next Monday after existing date (unaffected). */
			 
void CAbsolutePeriod::getnextmonday(void){
	       	        
			int daynum= GetDayOfWeek();
			// change to base 0;
			daynum=daynum-1;
			long days_to_offset=0;
			
			if(daynum==0)
			{;}
			else
			{
			days_to_offset=long(7-daynum);}
			
			
			
			
			CTimeSpan days2add(	days_to_offset,0,0,0);
			m_absolute_midnight +=days2add; }
			 
		

/* 5. Printout functions */

		

		
CString CAbsolutePeriod::Get_start_string(const CString Format_string)
	{   
		return m_absolute_midnight.Format(Format_string);}

CString CAbsolutePeriod::Get_finish_string(const CString Format_string)
	{   
		CTime finish(m_absolute_midnight);
		finish+=(m_start + m_duration);
		return finish.Format(Format_string);}
		
CString CAbsolutePeriod::Get_near_finish_string(void)
	{   
		CTime finish=m_absolute_midnight + (m_start + (m_duration-::ONE_HOUR));
		
		return finish.Format("%A, %B %d, %Y");}	
		
CString CAbsolutePeriod::Get_near_finish_string(const CString Format_string)
	{   
		   
		CTime finish(m_absolute_midnight);
		finish+=(m_start + (m_duration - ::ONE_HOUR));
		return finish.Format(Format_string);}		 
		
CString CAbsolutePeriod::Get_start_string(void)
	{   
	    CTime start=m_absolute_midnight + m_start;
		return start.Format("%A, %B %d, %Y");}
		

CString CAbsolutePeriod::Get_finish_string(void)
	{   
		CTime finish=m_absolute_midnight + (m_start + m_duration);
		
		return finish.Format("%A, %B %d, %Y");} 
		

CString CAbsolutePeriod::Get_absolute_start(void)
	{   
	    CTime start=m_absolute_midnight + m_start;
		return start.Format("%A, %B %d, %Y,%H:%M");}
		
CTime CAbsolutePeriod::Get_absolute_starttime(void)
	{ 
		CTime start=m_absolute_midnight + m_start;
		return start;}
		
  
CTime CAbsolutePeriod::Get_absolute_finishtime(void)
	{ 
		CTime finish=m_absolute_midnight + (m_start + m_duration);
		return finish;}		

CString CAbsolutePeriod::Get_absolute_finish(void)
	{   
		CTime finish=m_absolute_midnight + (m_start + m_duration);
		
		return finish.Format("%A, %B %d, %Y,%H:%M");} 
		

    
CTimeSpan CAbsolutePeriod::getduration(void)
{


return m_duration;

}


CTimeSpan CAbsolutePeriod::getduration(CAbsolutePeriod someday, CTimeSpan time_to_fill)
{ 
  
  time_to_fill=NONE;
 
 if(m_absolute_midnight==someday.m_absolute_midnight)
 {   
   time_to_fill=m_duration;}
 			
 	
return time_to_fill; 	

} 


#ifdef _DEBUG
void CAbsolutePeriod::Dump(CDumpContext& dc) const
{   
    
    
	CObject::Dump(dc);
	dc << "\nthis="<< m_absolute_midnight << m_duration <<"\n";
}
#endif //_DEBUG	
