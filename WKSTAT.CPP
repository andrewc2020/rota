// cal1.cpp : implementation file
//

#include "stdafx.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "state.h"
#include "calstate.h"
#include "wkstat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWeekstate

CWeekstate::CWeekstate():Calstate()
{


m_divisions=7;
m_subdivisions=1;

ID=ID_WEEK;
}

CWeekstate::~CWeekstate()
{


}







void CWeekstate::OnPrepareDC(CDC* pDC)
{

if(pDC->IsPrinting())
{



bigdiv.cx = 11520/9;
bigdiv.cy = -15120;


}

else

{

pDC->ScaleViewportExt(4,1,1,1);

bigdiv.cx = 1;
bigdiv.cy = 100;

 }

}



CString CWeekstate::set_column_heading(CAbsolutePeriod& start, CString& daystring)
{


	
	daystring= start.Get_start_string(_T("%a"))
	 + _T("\n")
	 + start.Get_start_string(_T("%d"));
	



return daystring;

}
