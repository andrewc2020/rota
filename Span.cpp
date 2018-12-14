// daystate.cpp : implementation file
//

#include "stdafx.h"
#include "span.h"
#include "CONSTANT.H"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CShift encapsulates standard shift

IMPLEMENT_SERIAL(CSpan, CObject ,1)

CSpan::CSpan():m_start(::NONE),m_duration(::NONE),CObject()
{




}

CSpan::CSpan(const CTimeSpan start, const CTimeSpan duration)
:m_start(start),m_duration(duration),CObject()
{


}

CSpan::CSpan(CSpan* someotherspan)
{

CSpan(someotherspan->getstart(),someotherspan->getduration());


}

CSpan::CSpan(const CTimeSpan start, const double duration):m_start(start),m_duration(::NONE)
{

decimal_to_time(duration,m_duration);


}



CSpan::~CSpan()
{

 

}

CTimeSpan CSpan::getstart(void)
{

return m_start;


}

CTimeSpan CSpan::getduration(void)
{


return m_duration;


}

void CSpan::setstart(const CTimeSpan newstart)
{

m_start=newstart;

}


void CSpan::setduration(const CTimeSpan newduration)
{
m_duration=newduration;
}


void CSpan::ResetPeriod(CSpan& someotherperiod)
{
	m_start=someotherperiod.getstart();
	m_duration=someotherperiod.getduration();}

void CSpan::ResetPeriod(CSpan* someotherperiod)
{

ResetPeriod(*someotherperiod);

}


	
void CSpan::ResetPeriod(const CTimeSpan start, const CTimeSpan duration)
{
	m_start=start;
	m_duration=duration;}
	
	
long CSpan::getbalance(void)
{

return m_duration.GetTotalSeconds();

}

BOOL CSpan::IsWithin(const CTimeSpan someother_start, const CTimeSpan someother_duration)
{

if(someother_start >= m_start + m_duration ||
				 someother_start + someother_duration <= m_start )
	{

	return FALSE;

	}
else
	{ 
	
	#ifdef _DEBUG

	afxDump << "\n passed start is " << someother_start << "passed duration is " << someother_duration ;
	#endif

	return TRUE;


	} 
}



void  CSpan::operator +=(const CTimeSpan amendment)
{

	m_duration+=amendment;
}

void  CSpan::operator -=(const CTimeSpan amendment)
{

	m_duration-=amendment;

}

void  CSpan::operator +=( CSpan* amender)
{

	m_duration+= amender->getduration();

} 

void  CSpan::operator -=(CSpan* amender)
{

	m_duration-= amender->getduration();

}

void CSpan::operator -=(const double amender)
{

	CTimeSpan reduce_by(::NONE);
	decimal_to_time(amender, reduce_by);
	m_duration -= reduce_by;

}

BOOL CSpan::operator ==(CSpan* maybe_dupe)
{

 

 return maybe_dupe->getstart()==m_start
  && maybe_dupe->getduration()==m_duration;






} 		


void CSpan::Serialize(CArchive& ar)

{   

	CObject::Serialize(ar);
  	 	
		
	  	 	
		
	if(ar.IsStoring())
	{ 
	
		
	ar << m_start << m_duration ;
	
	} 
	
	else
	{
	
	 ar >> m_start >> m_duration ;
	 
	}
	
    
	
 } 
	
    
void CSpan::decimal_to_time(const double hour_frac, CTimeSpan& time_to_fill)
{
/* converts a decimal time display to a time span */
double hour_bit(0.0);
double minbit(0.0);
double mins(0.0);
double secbit(0.0);
double secs(0.0);
double millisecs(0.0);



if(hour_frac)
    {
	
	
	mins = modf(hour_frac,&hour_bit);// get remainder 

	minbit = mins * 60;  // Get minutes	and seconds in decimal

	secbit = modf(minbit ,&mins); // Get minutes

	secbit = secbit * 60;

	

CTimeSpan duration(0,(int) hour_bit,(int) mins ,(int) secbit);

time_to_fill = duration;}

}
	
  
 
 




CObject* CSpan::clone(void)
{

return new CSpan(m_start, m_duration);

}

 
int CSpan::GetFirstBalance(void)
{


 //overriden in CTimelist
 


 return -1;


}

void CSpan::dur_as_decimal(double& proxy)
{
  /*try
	  {*/

	  proxy = getduration().GetTotalSeconds();
	  proxy /= 60;
	  proxy /= 60;


	  /*}*/
  //catch(/*CUserException e*/)
	 // {




	 // }
}
