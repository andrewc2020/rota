// period.cpp : implementation file
//

#define STANDALONE
#include "stdafx.h"
#include <afxdb.h>
#include <afxdao.h>
#include "resource.h"
#include "CONSTANT.H"
#include "span.h"

//#include "centool8.h"
#include "absolute.h"
#include "period.h"
#include "timelist.h"
#include "prdlst.h"
#include "cal1.h"
//#include "regularp.h"
//#include "state.h"
//#include "rotaview.h"
#include "assert.h"

//#include "centodoc.h"
#include "category.h"
//#include "contract.h"
#include "log2.h"
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
						uncle(NULL),
						drpstatus(FALSE)
{
box=new CRect();
box->SetRectEmpty();
}
						
    		
CPeriod::CPeriod(const CTimeSpan& start, const CTimeSpan& duration,CPeriod* parent,CPeriod* uncle):CSpan(start,duration),box(NULL),m_from_position(0),
m_to_position(364),is_open(FALSE),name(""),colour(RGB(0,0,0)),parent(parent),uncle(uncle),drpstatus(FALSE)
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
								 ,drpstatus(FALSE)
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
    
    
	ar  << m_from_position << m_to_position << id << colour << name ;}
	else {
	ar  >> m_from_position >> m_to_position >> id >> colour >> name;}
	
	assert(id);
}

void CPeriod::Clearbalance(void)
{


setduration(::NONE);

setstart(::ONE_DAY); 

resetcolour();

drpstatus = FALSE;


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

void CPeriod::UpdateDatabase(CLog& ds, CString contractno, const long empno, const CString estab, CAbsolutePeriod start)
{

CString status_string("Opening Database....");
CStatusBar* pStatus= (CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);

pStatus->SetPaneText(0,status_string);

CAbsolutePeriod occasion(start,getstart(),getduration());


if(ds.CanAppend() && getbalance())
{
ds.AddNew();
ds.m_estabfrn = estab;

CString codestring(((CCategory*) uncle)->Getcode(this));

if(codestring.IsEmpty())
{

codestring=	((CCategory*) uncle)->get_table_ID();



}


if(GetDRPstatus()){codestring += "*" ;}

ds.m_shiftcodefrn =	codestring;

ds.m_time_onstr  = (occasion.Get_absolute_starttime()).Format("%b/%d/%Y  %H:%M:%S");
ds.m_time_offstr = (occasion.Get_absolute_finishtime()).Format("%b/%d/%Y  %H:%M:%S");
ds.m_date_onstr =  (occasion.Get_absolute_midnight()).Format("%b/%d/%Y %H:%M:%S");
ds.m_rota = occasion.Get_rota_num(occasion.Get_absolute_midnight());
ds.m_contractnofrn = empno;
ds.m_budgetlinefrn = contractno;
ds.m_auth = FALSE;

TRACE("Lev2ID= %s",ds.m_shiftcodefrn);
TRACE("finish = %s",occasion.Get_absolute_finish());


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

 if(  m_to_position <= someother_from  || m_from_position >= someother_to )
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

			returnname= (parent->Getname()).Mid(0,2) + _T("/ ") + uncle->Getname();} 

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


   


//CRotaview* mainview=(CRotaview*) handle;

if(pDC->IsPrinting())
{



CRect copybox(calendarbox);
CPoint org(copybox.TopLeft().x,box->TopLeft().y);// used when printing

 


/* copybox now the intersection of box and calendar box, the day square */

CRect copybox2(org,box->Size());// used when printing

proto.CopyRect(&copybox2);

}



/*mainview->DrawMe(this,proto,pDC,handle);*/} 


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
	testfont.CreateFont(0,0,0,0,0,
						FALSE,FALSE,
						0,ANSI_CHARSET ,
						OUT_DEFAULT_PRECIS,  
						CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,
						DEFAULT_PITCH|FF_DONTCARE,_T(""));
	
	CFont* pOldfont=(CFont*) pDC->SelectObject(&testfont); 
	
	
    
	
	//pDC->TextOut(box->TopLeft().x ,box->TopLeft().y + 5 , Getname());
	pDC->TextOut(box->TopLeft().x + 1,box->TopLeft().y  , Getname());
		
	pDC->SelectObject(pOldfont);

	CRect copybox(box);
	
	if(parent)	// toplist needs no box
	{

	pDC->LPtoDP(copybox);

	CRectTracker trackbox(copybox,1);

	trackbox.Draw(pDC);} 


	// register with view

	/*CRotaview* rotaptr =(CRotaview*) handle;*/
	/*rotaptr->register_item(this);*/

	
	
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

/* make copy of calendar box */

CRect copybox(calendarbox);
CPoint org(copybox.TopLeft().x,box->TopLeft().y);// used when printing

 
copybox.IntersectRect(box,calendarbox);

/* copybox now the intersection of box and calendar box, the day square */

CRect copybox2(org,box->Size());// used when printing

/* copybox2 is row beginning with this column top left hand corner */

switch(pDC->IsPrinting())
	  {
	  case FALSE:

	   /* when not printing, use intersected row and column */  
	    
	  
	  	pDC->SetTextColor(getcolour());

		

	  break;

	  case TRUE:

	  
	  
	  copybox.CopyRect(&copybox2);

	  /* when printing use row starting at day column */
	   
	  pDC->SetTextColor(::BLACK);

	  break;

	  default:

	  AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

	  }


   


//CRotaview* mainview=(CRotaview*) handle;



//mainview->DrawMe(this,copybox,pDC,handle);

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


int CPeriod::GetFirstBalance(void)
{


//overriden in CTimelist
 


 return -1;


}



void CPeriod::SetDRPstatus(const BOOL newsetting)
{


 drpstatus = newsetting;



}


BOOL CPeriod::GetDRPstatus(void)
{

 return drpstatus;


}
