// daystate.cpp : implementation file
//

#include "stdafx.h"
#include <afxdb.h>
//#include "centool8.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "assert.h"
#include "state.h"
#include "calstate.h"
#include "daystate.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDaystate

CDaystate::CDaystate():Calstate()
{

ID=ID_DAY;
m_divisions=1;
m_subdivisions=1;

}

CDaystate::~CDaystate()
{



}



void CDaystate::OnPrepareDC(CDC* pDC)
{

if(pDC->IsPrinting())
	{

	m_offset = 1;
	bigdiv.cx = 11520/4;
	bigdiv.cy = -15120;

	}

	else
	{

	pDC->ScaleViewportExt(28,1,1,1);
	bigdiv.cx = 1;
	bigdiv.cy = 100;

	}

}




CString CDaystate::set_column_heading(CAbsolutePeriod& start, CString& daystring)
{


	
	daystring= start.Get_start_string(_T("%a, %d %b"));
	



return daystring;

}
