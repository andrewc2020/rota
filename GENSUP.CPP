// gensup.cpp : implementation file
//

#include "stdafx.h"
#include <stdlib.h>
//#include "centool8.h"
#include "absolute.h"
#include "span.h"
#include "period.h"
#include "timelist.h"
#include "category.h"
#include "gensup.h" 
#include "shift.h"
#include <iostream>
#include <string>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGensup

IMPLEMENT_SERIAL(CGensup, CCategory,2)

CGensup::CGensup():CCategory()
{
 
CPeriod::setcolour(RGB(0,0,255));

}

CGensup::CGensup(const CString title, CPeriod* prnt,CPeriod* uncl)
:CCategory(title,(CTimelist*)prnt,(CTimelist*)uncl)
{ 

CPeriod::setcolour(RGB(0,0,255));

}

CGensup::CGensup(const CString title, CPeriod* prnt,CPeriod* uncl, const CString table_id):CCategory(title,(CTimelist*)prnt,(CTimelist*)uncl,table_id)
{ 

CPeriod::setcolour(RGB(0,0,255)); 



}

CGensup::~CGensup()
{


}


/////////////////////////////////////////////////////////////////////////////
// CGensup message handlers  

BOOL CGensup::Setcodelist(CObList* codelist)
{


m_codelist=codelist;

POSITION pos = GetHeadPosition();

while(pos)
{

CGensup* ptr = (CGensup*) GetAt(pos);
ptr->Setcodelist(codelist);

GetNext(pos);


}

return m_codelist!=NULL;

}


CString CGensup::Getcode(CSpan* sp)
{

CString codestring;
codestring.Empty();

if(m_codelist)
{

POSITION pos = m_codelist->GetHeadPosition();

while(pos && codestring.IsEmpty() )
{

m_shift = (CShift*) m_codelist->GetAt(pos);
if(sp->getstart()==m_shift->getstart() &&
		 sp->getduration()==m_shift->getduration())
		 { codestring = m_shift->getletter();}

m_codelist->GetNext(pos);


}

}// end if m_codelist

if(codestring.IsEmpty()){ codestring = "NS";}


return codestring;

}

CString CGensup::Getdlgcode(CSpan* pshft)
{

CString codestring(Getcode(pshft));

if(!codestring.IsEmpty())

	{

	 return codestring;

	}

	else

	{

	return _T("N/S");

	}

}

#ifdef _DEBUG
void CGensup::Dump(CDumpContext& dc) const
{   
    
    
	CObject::Dump(dc);
//	dc  <<"\n name"  << Getname() <<"\n";
}
#endif //_DEBUG	 




 BOOL CGensup::Addcodes(void)
{



return TRUE;

}




void CGensup::Serialize(CArchive& ar)

{   
	

	CCategory::Serialize(ar);

		
	
	
 }  

CTimelist* CGensup::Add(CString title,
						CTimelist* uncle,
						const long from,
						const long to,
						const CString table_id)
{ 
CObject* ptr=NULL;
ptr =new CGensup(title, this,uncle,table_id);
m_mainlist->AddTail(ptr);

return (CTimelist*) ptr;

}

BOOL CGensup::IncrementNonstandard(CString& txt)
{

// Purpose: For nonstandard shifts returns next highest number otherwise returns it unchanged

if(txt.Left(2)=="NS")
{

// find the last NS entry

CString codestring;
codestring.Empty();



POSITION pos = m_codelist->GetTailPosition();

while(pos && codestring.Left(2)!="NS" )
{

m_shift = (CShift*) m_codelist->GetAt(pos);
		 { codestring = m_shift->getletter();}

m_codelist->GetPrev(pos);


}

// codestring is either empty or the highest non standard shift



int answer(0);
CString substring ;
substring.Empty();

/*
#ifdef _DEBUG
 afxDump << "\n codestring   =" << codestring << "\n";
 
#endif
 */

substring = codestring;

substring.MakeReverse();
substring = substring.SpanExcluding(_T("NS"));
substring.MakeReverse();

if(!substring.IsEmpty()	)
{
answer = _wtoi(substring);


answer++;

}
else
{
answer = 1;
}
char seriesno[10];
sprintf_s(seriesno,"%d" ,answer);
txt = _T("NS") + ((CString)seriesno);

return TRUE;


}

else
{


 return FALSE;


}



}
