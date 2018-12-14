// cal1.cpp : implementation file
//

#include "stdafx.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "state.h"
#include "calstate.h"
#include "frwkstat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CFourweekstate

CFourweekstate::CFourweekstate():Calstate()
{


m_divisions = 4;
m_subdivisions= 7;

m_div_span=::ONE_WEEK;
m_sub_div_span = ::ONE_DAY;

ID=ID_FOURWEEK;



}

CFourweekstate::~CFourweekstate()
{


}




void CFourweekstate::OnPrepareDC(CDC* pDC)
{

if(pDC->IsPrinting())
	{

	m_offset = 1;
	bigdiv.cx = 11520/6;
	bigdiv.cy = -15120;

	}

	else
	{


	pDC->ScaleViewportExt(1,1,1,1);

	bigdiv.cx= 7;
	bigdiv.cy = 100;

	}

}





CString CFourweekstate::set_column_heading(CAbsolutePeriod& start, CString& daystring)
{


	
	daystring=(start.Get_start_string(_T("%a"))
	 + _T("\n")
	 + start.Get_start_string(_T("%d:%b"))
	 + _T(" - ")
	 + _T("\n") 
	 + start.Get_near_finish_string(_T("%d:%b")));
	



return daystring;

}


