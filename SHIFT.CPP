// daystate.cpp : implementation file
//

#include "stdafx.h"
#include "span.h"
#include "shift.h"
//#include "centool8.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CShift encapsulates standard shift

IMPLEMENT_SERIAL(CShift, CSpan ,1)

CShift::CShift():CSpan(),codeletter()
{




}

CShift::CShift(const CTimeSpan start, const CTimeSpan duration, const CString codeletter)
:CSpan(start,duration),codeletter(codeletter)
{


}



CShift::~CShift()
{

 

}


void CShift::Serialize(CArchive& ar)

{   

	CSpan::Serialize(ar);
  	 	
		
	if(ar.IsStoring())
	{ 
	
		
	ar << codeletter;
	
	} 
	
	else
	{
	
	 ar >> codeletter;
	 
	}
	
    
	
 } 
 
 CString CShift::getletter(void)
 {
 
 return codeletter;
 
 }





CObject* CShift::clone(void)
{

return new CShift(getstart(), getduration(), codeletter);

}

 
