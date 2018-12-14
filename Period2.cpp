// period.cpp : implementation file
//


#include "stdafx.h"
#include "span.h"
//#include "centool8.h"
#include "CONSTANT.H"
//#include "calbar.h"
#include "absolute.h"
#include "period.h"
#include "timelist.h"
#include "prdlst.h"
#include "cal1.h"
#include "regularp.h"
#include "credit.h"
#include "debit.h"
#include "sodialog.h"
#include "addac.h" 
//#include "basedlg.h"
//#include "seld2.h"
#include "navdlg.h"
#include "state.h"
#include "rotaview.h"
#include "assert.h"
//#include "centodoc.h"
#include "mainfrm.h"
#include "category.h"
#include "contract.h"
#ifndef STANDALONE
#include "log2.h"
#endif
#include <math.h>
#include <stdio.h>



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPeriod




IMPLEMENT_SERIAL(CPeriod, CObject, 0) 

//Constructors


    		
/* 1. Creates from serialization. */


CPeriod::CPeriod(void): CSpan(),
						box(NULL),
						m_from_position(0),
						m_to_position(364),
						id(0),
						is_open(FALSE),
						name(""),
						colour(RGB(0,0,0)),
						parent(NULL),
						uncle(NULL)
{
box=new CRect();
box->SetRectEmpty();
}
						
    		
CPeriod::CPeriod(const CTimeSpan& start, const CTimeSpan& duration,CPeriod* parent,CPeriod* uncle):CSpan(start,duration),box(NULL),m_from_position(0),
m_to_position(364),is_open(FALSE),name(""),colour(RGB(0,0,0)),parent(parent),uncle(uncle)
,id(0)
{

box=new CRect();
box->SetRectEmpty();



}
	
			


CPeriod::CPeriod(const CTimeSpan& start,
				 const CTimeSpan& duration,
				 const long from,
				 const long to,
				 CPeriod* parent,
				 CPeriod* uncle):CSpan(start,duration),
				 				 box(NULL),id(0),
				 				 m_from_position(from),
				 				 m_to_position(to),
				 				 is_open(FALSE),
				 				 name(""),
				 				 colour(RGB(0,0,0)),
				 				 parent(parent),
				 				 uncle(uncle)
{

box=new CRect();
box->SetRectEmpty();


}


CPeriod::~CPeriod(void)
{

#ifdef _DEBUG

//afxDump << "\n Item is " << name << "parent is " << *parent  ;
#endif
delete box;

} 

CObject* CPeriod::Clone(void)
{

// overridden in derived classes

return NULL;
}

void CPeriod::Serialize(CArchive& ar)
{
	CSpan::Serialize(ar);
	
	
	if(ar.IsStoring()){
	
	
   

    setid();
    
    
	ar  << m_from_position << m_to_position << id << colour << name;}
	else {
	ar  >> m_from_position >> m_to_position >> id >> colour >> name;}
	
	assert(id);
}

void CPeriod::Clearbalance(void)
{


setduration(::NONE);

setstart(::ONE_DAY); 

resetcolour();


}


void CPeriod::setid_direct(const DWORD newid)
{


id=newid;



}	
 
void CPeriod::resetid(void)
{

id=0;


}


void CPeriod::Get_uncle_colour(void)
{

setcolour(uncle->colour);

}





WORD CPeriod::GetIndex(void)
{




return uncle->GetIndex();

}



void CPeriod::setid(void)
{

// overridden in derived classes
// CRegularPeriod id is foscilised parent



}



BOOL CPeriod::Restore_Uncle(CPeriod* uncptr)
{

if(id==uncptr->id){
uncptr->set_uncle(this);


return TRUE;}
else
{return FALSE;}

} 

BOOL CPeriod::Is_uncle(const CPeriod* testptr)
{

return uncle==testptr;


}


DWORD CPeriod::get_id(void)
{
return id;
}  

CPeriod* CPeriod::Getparent(void)
{

if(parent){return parent;}

else {return NULL;}

}



CPeriod* CPeriod::Getultiparent(void)
{

CPeriod* ptr; CPeriod* ptr2= ptr =this;


while(ptr2=ptr2->Getparent())
{
  
 ptr=ptr2;}

return ptr;


} 

#ifndef STANDALONE

void CPeriod::UpdateDatabase(CLog& ds, CString contractno,const CString estab, CAbsolutePeriod start)
{

CString status_string("Opening Database....");
CStatusBar* pStatus= (CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);

pStatus->SetPaneText(0,status_string);

CAbsolutePeriod occasion(start,getstart(),getduration());


if(ds.CanAppend() && getbalance())
{
ds.AddNew();
ds.m_Confrn= contractno;
ds.m_Lev2IDfrn=  ((CCategory*) uncle)->get_table_ID();
ds.m_Estabfrn = estab;
TRACE("Lev2ID= %s",ds.m_Lev2IDfrn);
TRACE("finish = %s",occasion.Get_absolute_finish());

ds.m_Timeonstr = occasion.Get_absolute_starttime().Format("%d/%m/%y %H:%M:%S");
ds.m_Timeoffstr= occasion.Get_absolute_finishtime().Format("%d/%m/%y %H:%M:%S");
ds.Update();}

}
#endif

void CPeriod::set_uncle(CPeriod* uncle_address)
{

uncle=uncle_address;

} 


CPeriod* CPeriod::Getuncle(void)
{

return uncle;

} 

BOOL CPeriod::datalogin(CObject* ptr)
{


return FALSE;
} 

   
BOOL CPeriod::datalogout(CObject* ptr)
{ 



return FALSE;
} 



BOOL CPeriod::CheckAddresses(void)
{  




if(!(uncle && id && id==uncle->get_id()))
{



return FALSE;

}

else
{

return TRUE;

}

}

void CPeriod::decimal_to_time(const double hour_frac, CTimeSpan& time_to_fill)
{
/* converts a decimal time display to a time span */
double hour_bit(0.0);
double minbit(0.0);
double mins(0.0);
double secbit(0.0);
double secs(0.0);

if(hour_frac )
    {
	
	
	mins = modf(hour_frac,&hour_bit);// get remainder 

	minbit = mins * 60;  // Get minutes	and seconds in decimal

	secbit = modf(minbit ,&mins); // Get minutes

	secbit = secbit * 60;

	modf(secbit, &secs); // Get seconds

CTimeSpan duration(0,(int) hour_bit,(int) mins ,(int) secs);

time_to_fill = duration;}



}

void CPeriod::SetFromToPosition(const int flag,const long value)
{

switch(flag)
		{

		case ::MIN:
		 
           m_from_position = value;
           
        break;
        
        case ::MAX: 
        
        
           m_to_position = value;
          
           
        break;
        
        default: { AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONSTOP,0);}
        
        break;
        
        }  


}

long CPeriod::GetFromToPosition(const int flag)
{

switch(flag)
		{

		case ::MIN:
		 
           return m_from_position;
           
        break;
        
        case ::MAX:
           return m_to_position;
          
           
        break;
        
        default: { AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONSTOP,0);
        			return IDS_PGERR;}
        
        break;
        
        }  
         

}

BOOL CPeriod::IsWithin(const long someother_from, const long someother_to)
{

 if(  someother_from <= m_to_position && someother_to >= m_from_position)
 { return FALSE;}
 else
 {return TRUE;}

}

  

CPeriod* CPeriod:: GetStaff(void)
{
CPeriod* ptr=NULL;

if(!name.IsEmpty())
{

return this;} 


else {
 
ptr=Getparent();

if(!ptr){ AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

 AfxThrowUserException();}	// uncaught: will bring down programme

return ptr->GetStaff();}

} 

void CPeriod::Setname(const CString newname)
{


name=newname;

}

CString CPeriod::Getname(void)
{ 

CString returnname("");

TRY
{

	 

		if(name.IsEmpty())
		{

			if(!(parent && uncle)){ AfxThrowUserException();}

			returnname= (parent->Getname()).Mid(0,2) + "/ " + uncle->Getname();} 

		else{ returnname= name;}


 
}


CATCH(CUserException, e)
{

AfxMessageBox(IDS_PGERR , MB_OK|MB_ICONEXCLAMATION, 0);
exit(1);
 
}

END_CATCH
	
	
return returnname;
 
} 
 
CString CPeriod::Getbriefname(void)
{

CString returnname(Getname());

return returnname.Mid(0,3);


}

BOOL CPeriod::displaysum(const CRect* calendarbox,CDC* pDC, CView* handle)
{

if(getduration().GetTotalMinutes()!=0)
{



pDC->SetTextColor(::BLACK);




CRect copybox;


copybox.IntersectRect(box,calendarbox);

CPoint org(copybox.BottomRight().x,copybox.TopLeft().y);



CRect proto(org,copybox.Size());


   


CRotaview* mainview=(CRotaview*) handle;



mainview->DrawMe(this,proto,pDC,handle);} 


return TRUE;

} 

CPeriod* CPeriod::GetOtherRelative(const CPeriod* caller)
{
assert(caller);

if(caller==uncle){
assert(parent);
return parent;}
else
if(caller==parent){ 
assert(uncle);
return uncle;}
else
{return NULL;
AfxMessageBox(IDS_PGERR,MB_OK,0);}

}

void CPeriod::print(const CTime basedate,
					CAbsolutePeriod currentperiod,
					CDC* pDC) 
{

CAbsolutePeriod scope(basedate,m_from_position, m_to_position);
    
    if(currentperiod.IsWithinPeriod(scope))
    {
	 	pDC->TextOut(box->TopLeft().x,box->TopLeft().y , Getname());
	 }

}

BOOL CPeriod::display(const CTime basedate,
					  CAbsolutePeriod currentperiod,
					  CDC* pDC,
					  CView* handle)
{

	
	
	CSize bitsize(5,2);
	CRect bitbox(box->TopLeft(),bitsize);

	picture(&bitbox,handle);  
	
	// dividing line
	    
    pDC->SelectStockObject(BLACK_PEN); 
    
    		
	
	 CFont testfont;
	testfont.CreateFont(-4,0,0,0,0,
						FALSE,FALSE,
						0,ANSI_CHARSET ,
						OUT_DEFAULT_PRECIS,  
						CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,
						DEFAULT_PITCH|FF_SWISS,"Arial");
	
	CFont* pOldfont=(CFont*) pDC->SelectObject(&testfont); 
	
	
    
	
	pDC->TextOut(box->TopLeft().x,box->TopLeft().y + 5, Getname());
		
	pDC->SelectObject(pOldfont);

	CRect copybox(box);
	
	if(parent)	// toplist needs no box
	{

	pDC->LPtoDP(copybox);

	CRectTracker trackbox(copybox,1);

	trackbox.Draw(pDC);} 


	// register with view

	CRotaview* rotaptr =(CRotaview*) handle;
	rotaptr->register_item(this);

	
	
	return TRUE; 


}

int CPeriod::getboxWidth(void)
{
return box->Width();
}




BOOL CPeriod::displaydata(const CRect* calendarbox,
						  CDC* pDC,
						  CView* handle)
{

if(getbalance())
{


CRect copybox(calendarbox);
CPoint org(copybox.TopLeft().x,box->TopLeft().y);// used when printing

 
copybox.IntersectRect(box,calendarbox);
CRect copybox2(org,box->Size());// used when printing

switch(pDC->IsPrinting())
	  {
	  case FALSE:

	     
	    
	  
	  	pDC->SetTextColor(getcolour());

		

	  break;

	  case TRUE:

	  
	  
	  copybox.CopyRect(&copybox2);
	   
	  pDC->SetTextColor(::BLACK);

	  break;

	  default:

	  AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

	  }


   


CRotaview* mainview=(CRotaview*) handle;



mainview->DrawMe(this,copybox,pDC,handle);

pDC->SetTextColor(::BLACK);	//restore device context

return TRUE;} 
 
else
{

return FALSE;}

}



CRect* CPeriod::getbox(void)
{

return box;



} 

BOOL CPeriod::CanCutandPaste(const UINT param)
{


return FALSE;

}



COLORREF CPeriod::getcolour(void)
{
return colour;
} 

void CPeriod::setcolour(COLORREF newcolour)
{

colour=newcolour;


}


void CPeriod::resetcolour(void)
{


colour=RGB(0,0,0);


}

void CPeriod::setboxempty(void)
{
if(!(box->IsRectEmpty()))
{
box->SetRectEmpty();}
}



 

 
#ifdef _DEBUG
void CPeriod::Dump(CDumpContext& dc) const
{   
    
    
	
}
#endif //_DEBUG	


BOOL CPeriod::Edit(const CTime)
{ 
return FALSE;
}

BOOL CPeriod::showmenu(CView* handle, const CPoint& coords)
{


return FALSE;

}


 

UINT CPeriod::GetImage(void)
{

return 0;

}
void CPeriod::picture(CRect* copybox, CView* handle)
{
 
CClientDC dc(handle);
handle->OnPrepareDC(&dc,NULL);


CDC* pDisplayMemDC = new CDC;
CBitmap* pBitmap = new CBitmap;
pBitmap->LoadBitmap(GetImage());
pDisplayMemDC->CreateCompatibleDC(&dc);
CBitmap* pOldBitmap=(CBitmap*) pDisplayMemDC->SelectObject(pBitmap);
dc.LPtoDP(copybox); 
dc.SetMapMode(MM_TEXT);

dc.BitBlt( copybox->TopLeft().x,copybox->TopLeft().y + 5 ,100,copybox->TopLeft().y + 100, pDisplayMemDC, 0,0,SRCCOPY);
delete  pDisplayMemDC->SelectObject(pOldBitmap);
delete   pDisplayMemDC;

} 

void CPeriod::setbox(const CRect* copybox)
{   
			
	box->CopyRect(copybox);
	    
}
