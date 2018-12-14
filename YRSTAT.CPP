// implementation file
//

#include "stdafx.h"
#include "centool8.h"
#include "absolute.h"
#include "state.h"
#include "calstate.h"
#include "yrstat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CYearstate

CYearstate::CYearstate():Calstate()
{



m_divisions=13;
m_subdivisions=28;

m_div_span=::FOUR_WEEKS;
m_sub_div_span = ::ONE_WEEK;

ID=ID_CALENDAR_YEAR;


}

CYearstate::~CYearstate()
{


}





void CYearstate::OnPrepareDC(CDC* pDC)
{

	if(pDC->IsPrinting())
	{
	/*
	bigdiv.cx = 11520/12;
	bigdiv.cy = -15120;	*/

	bigdiv.cx = 15120/20;
	bigdiv.cy = -11520;

	}

	else
	{
 
	pDC->ScaleViewportExt(1,13,1,1);

	bigdiv.cx=28;
	bigdiv.cy = 100;

	}
}




CString CYearstate::set_column_heading(CAbsolutePeriod& start, CString& daystring)
{


	
	daystring=start.Get_start_string("%d")
	+ "\n"
	+ start.Get_start_string("%b");
	



return daystring;

}


