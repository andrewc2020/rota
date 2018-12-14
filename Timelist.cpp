// timelist.cpp : implementation file
//


#include "stdafx.h"
#include <afxdb.h>
#include <afxdao.h>
#include "CONSTANT.H"
//#include "centool8.h"
#include "absolute.h"
#include "span.h"
#include "period.h"

#include "regularp.h"
#include "addac.h"
#include "assert.h"
#include "state.h"
//#include "rotaview.h"
#include "navdlg.h"
#include "assert.h"


#include "timelist.h"
#include "category.h" 
#include "prdlst.h"
#include "resource.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimelist

IMPLEMENT_SERIAL(CTimelist,CPeriod,1)
#define new DEBUG_NEW

// Constructor 

CTimelist::CTimelist(void) :CPeriod(),
							m_dataptrs(NULL),
							m_mainlist(NULL),
							parent_id(0)
{


m_mainlist=new CObList();


}

					
CTimelist::CTimelist(CString title,
					 CTimelist* prnt,
					 CTimelist* uncl,
					 const long from ,
					 const long to) : CPeriod(::NONE,
					 						  ::NONE,
					 						    from,
					 						    to,
					 						    prnt,
					 						    uncl),m_dataptrs(NULL),
					 						          m_mainlist(NULL)
					 						          ,parent_id(0)
{



m_mainlist=new CObList();
Setname(title);


}

	
			 		
CTimelist::~CTimelist()
{



if(m_dataptrs){

while(!m_dataptrs->IsEmpty())
{
CRegularPeriod* ptr= (CRegularPeriod*) m_dataptrs->RemoveHead(); 

/*
#ifdef _DEBUG 
afxDump 
<< "Rewg pd " << *ptr << "\n" ;
#endif
*/ 

}
if(!m_dataptrs->IsEmpty()){ AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);}
delete m_dataptrs; 

Removeall();
if(!m_dataptrs->IsEmpty()){ AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);}
delete m_mainlist; }
 
} 

BOOL CTimelist::IsEstablishment(void)
{

//overridden true in CEstab

return FALSE;

}



BOOL CTimelist::Edit(const CTime basedate)
{

CAddac dlg(basedate,NULL);

dlg.whichtitle=dlg.Edit;
dlg.m_name=Getname();


/*
if(parent){ dlg.nMin=(int) parent->GetFromToPosition(::MIN);}
else {dlg.nMin=0;}
if(parent){ dlg.nMax=(int) parent->GetFromToPosition(::MAX);}
else {dlg.nMax=364;}
*/

dlg.from_position = dlg.nMin = 0;
dlg.to_position =  dlg.nMax = 364;
              
/*
dlg.from_position=(int) GetFromToPosition(::MIN);
dlg.to_position=(int) GetFromToPosition(::MAX);
*/

if(dlg.DoModal()==IDOK)
{
		 
Setname(dlg.m_name);


 
return TRUE;}
else { return FALSE;}

}

void CTimelist::restore_children(void)
{
CTimelist* ptr=0;
POSITION pos=  m_mainlist-> GetHeadPosition();
while(pos)
{

ptr=(CTimelist*)   m_mainlist-> GetAt(pos);
ptr->parent=this;
  m_mainlist-> GetNext(pos);
	}
}

BOOL CTimelist::datalogin(CObject* ptr)
{

if(!m_dataptrs){ m_dataptrs= new CObList();}

m_dataptrs->AddTail(ptr);

return TRUE;
} 

BOOL CTimelist::datalogout(CObject* ptr)
{
BOOL successful=FALSE;
if(m_dataptrs)
{


POSITION pos=m_dataptrs->Find(ptr,0);
if(pos){ m_dataptrs->RemoveAt(pos);
successful=TRUE;}

if(m_dataptrs->IsEmpty()){
delete m_dataptrs;
m_dataptrs=0;}}
return successful;
}



BOOL CTimelist::displayalldata(const CTime basedate, const CRect* calendarbox,CAbsolutePeriod slice,CDC* pDC, CView* handle)
{
BOOL show=FALSE;


int cnt(5);
//((CRotaview*)handle)->max_rows(cnt);

int scrollindex(GetScrollIndex(handle));

/* Convert calendarbox */



POSITION pos=  m_mainlist->GetHeadPosition();

pos=m_mainlist->FindIndex(scrollindex);

while(pos && cnt)
{
CTimelist* ptr=(CTimelist*)   m_mainlist->GetAt(pos); 

show=ptr->displaydata(calendarbox,pDC, handle);

m_mainlist->GetNext(pos);


cnt--;
}



if(m_dataptrs)
{ 

scrollindex -= m_mainlist->GetCount();


POSITION pos=m_dataptrs->GetHeadPosition();

if(scrollindex >=0 && pos){ pos=m_dataptrs->FindIndex(scrollindex);}
	// index into list if necessary

while(cnt && pos)
{
CPeriod* ptr=(CPeriod*) m_dataptrs->GetAt(pos);



ptr->displaydata(calendarbox,pDC, handle);
cnt--;
m_dataptrs->GetNext(pos);}



}

return show;
}


BOOL CTimelist::Is_Catview(void)
{


return FALSE;

}


BOOL CTimelist::Is_Root_Contract(void)
{



return parent==NULL;

}

BOOL CTimelist::displayallSum(const CTime basedate, const CRect* calendarbox,CAbsolutePeriod slice,CDC* pDC, CView* handle)
{
BOOL show=FALSE;


//int cnt(5);
int cnt(5);
//((CRotaview*)handle)->max_rows(cnt);

int scrollindex(GetScrollIndex(handle));

/* Convert calendarbox */



POSITION pos=  m_mainlist->GetHeadPosition();

pos=m_mainlist->FindIndex(scrollindex);

while(pos && cnt)
{
CTimelist* ptr=(CTimelist*)   m_mainlist->GetAt(pos); 

show=ptr->displaydata(calendarbox,pDC, handle);

m_mainlist->GetNext(pos);

cnt--;
}



if(m_dataptrs)
{ 
scrollindex -= m_mainlist->GetCount();

POSITION pos=m_dataptrs->GetHeadPosition();

if(scrollindex >=0 && pos){ pos=m_dataptrs->FindIndex(scrollindex);}	// index into list if necessary

while(cnt && pos)
{
CPeriod* ptr=(CPeriod*) m_dataptrs->GetAt(pos);


ptr->displaydata(calendarbox,pDC, handle);

cnt--;
m_dataptrs->GetNext(pos);}



}

return show;
}


BOOL CTimelist::printall(const CTime basedate,CAbsolutePeriod currentperiod,CDC* pDC,CView* handle)
{

int cnt(5);
//((CRotaview*)handle)->max_rows(cnt);
int scrollindex(GetScrollIndex(handle));

CRect copyrect(0,0,pDC->GetWindowExt().cx,pDC->GetWindowExt().cy); 


setbox(&copyrect);

		
		CPoint topleft(getbox()->TopLeft().x ,getbox()->TopLeft().y -250);//set up indent
	
    	CSize topslice_size(getbox()->Width(),-550);//-1500);
    	//CSize topslice_size(getbox()->Width(),-(getbox()->Height()/5));
    	



POSITION pos=  m_mainlist->GetHeadPosition();

pos=m_mainlist->FindIndex(scrollindex);

if(!pos){ return FALSE;}

else
{

while(pos )
		{
	    CTimelist* listptr=(CTimelist*)   m_mainlist->GetAt(pos);
		topleft.Offset(0,topslice_size.cy); 
		CRect copyrect(topleft,topslice_size);
	    listptr->setbox(&copyrect);
	    listptr->print(basedate,currentperiod,pDC);
	    topleft.Offset(0,topslice_size.cy); //break in rows
	    m_mainlist->GetNext(pos);
		
		cnt--; }



if(m_dataptrs)
{

scrollindex -= m_mainlist->GetCount(); 

POSITION pos=m_dataptrs->GetHeadPosition();

if(scrollindex >=0 && pos){ pos=m_dataptrs->FindIndex(scrollindex);}	// index into list if necessary
	while(cnt && pos)
		{
		CPeriod* ptr=(CPeriod*) m_dataptrs->GetAt(pos);  
		topleft.Offset(0,topslice_size.cy); 
        CRect copyrect(topleft,topslice_size);
	    ptr->setbox(&copyrect);
		ptr->print(basedate,currentperiod,pDC);
		cnt--;
        m_dataptrs->GetNext(pos);}//end while

		} //end if

  return TRUE;

  }
}


void CTimelist::print(
						const CTime basedate,
						CAbsolutePeriod currentperiod,
						CDC* pDC
						) 
{

CAbsolutePeriod scope(basedate,GetFromToPosition(::MIN),GetFromToPosition(::MAX));



		
		CPoint topleft(
						getbox()->TopLeft().x + 800,
						getbox()->TopLeft().y
							);//set up indent
	
    	CSize topslice_size(
    						getbox()->Width(),getbox()->Height()
    						/2
    						);
    				 
	
    
    if(currentperiod.IsWithinPeriod(scope))
    {
	    
		pDC->TextOut(getbox()->TopLeft().x ,getbox()->TopLeft().y , Getname());
		
		
	
		POSITION pos=GetHeadPosition();
		while(pos)
		{

		CPeriod* ptr =(CPeriod*) GetAt(pos);
        topleft.Offset(0,topslice_size.cy); 
		CRect copyrect(topleft,topslice_size);
	    ptr->setbox(&copyrect);
		pDC->TextOut(topleft.x,topleft.y,(ptr->Getuncle())->Getname());
		
		GetNext(pos);  	}
	
	  
	
	 }//end if within scope
	


	 

} 

BOOL CTimelist::printalldata(const CTime basedate,
							 CRect* calendarbox,
							 CAbsolutePeriod slice,
							 CDC* pDC,
							 CView* handle)
{ 

int cnt(5);

int scrollindex(GetScrollIndex(handle));
BOOL show(FALSE);


/* Convert calendarbox */


POSITION pos=  m_mainlist->GetHeadPosition();

pos=m_mainlist->FindIndex(scrollindex);

while(pos && cnt)
{
CTimelist* ptr=(CTimelist*)   m_mainlist->GetAt(pos); 

show=ptr->printdata(calendarbox,pDC,handle);

m_mainlist->GetNext(pos);

cnt--; }



if(m_dataptrs)
{ 

scrollindex -= m_mainlist->GetCount();

POSITION pos=m_dataptrs->GetHeadPosition();

if(scrollindex >=0 && pos){ pos=m_dataptrs->FindIndex(scrollindex);}	// index into list if necessary
while(cnt && pos)
{
CPeriod* ptr=(CPeriod*) m_dataptrs->GetAt(pos);

ptr->displaydata(calendarbox,pDC,handle);
cnt--;
m_dataptrs->GetNext(pos);}

}

return TRUE;
} 



CString CTimelist::Getcode(CSpan* me)
{



return _T("");

}





BOOL CTimelist::printdata(CRect* calendarbox, CDC* pDC,CView* handle)
{ 



POSITION pos=GetHeadPosition();

displaydata(calendarbox,pDC,handle);

	while(pos )
		{
		
		
		CPeriod* ptr =(CPeriod*) GetAt(pos);

		
		ptr->displaydata(calendarbox,pDC,handle);
		GetNext(pos);
		}
		
		




return TRUE;

}

 
int CTimelist::GetScrollIndex(CView* handle)
{

return handle->GetScrollPos(SBS_VERT);

}


void CTimelist::pop(CPeriod* placeholder, const int index)
{



POSITION pos = m_mainlist->FindIndex(index);

if(pos)
{


placeholder = (CPeriod*) m_mainlist->GetAt(pos);}

 

}


BOOL CTimelist::sum_all_data(CRect* calendarbox, CDC* pDC,CView* handle)
{

//int cnt(5);
int cnt(5);
//((CRotaview*)handle)->max_rows(cnt);

POSITION pos=GetHeadPosition();
pos=m_mainlist->FindIndex(GetScrollIndex(handle)); 

displaysum(calendarbox,pDC,handle);


	while(pos && cnt)
		{
		
		
		CPeriod* ptr =(CPeriod*) GetAt(pos);

		ptr->displaysum(calendarbox,pDC,handle);
		
		GetNext(pos);
		cnt--;}
		   

return TRUE;
}

void CTimelist::displayall(const CTime basedate,CAbsolutePeriod currentperiod,CDC* pDC,CView* handle)
{


int cnt(5);//  display five when deep, 10 when shallow 
//((CRotaview*)handle)->max_rows(cnt);

int scrollindex(GetScrollIndex(handle));


CRect copybox;

copybox.SetRect(0,20,getboxWidth(),30);// build head portion of row display


setopen(TRUE);
display(basedate,currentperiod,pDC,handle);


//copybox.SetRect(0,20,getboxWidth(),25);
//((CRotaview*) handle)->SetRow(copybox);

if(m_mainlist)
{

POSITION pos=  m_mainlist->GetHeadPosition();

pos=m_mainlist->FindIndex(scrollindex);

while(pos && cnt)
		{
	    CTimelist* listptr=(CTimelist*)   m_mainlist->GetAt(pos);
	    listptr->setbox(&copybox);
		listptr->setopen(FALSE);
		listptr->display(basedate,currentperiod,pDC,handle);
		copybox.OffsetRect(0,copybox.Height());	
		m_mainlist->GetNext(pos);
		cnt--; }




if(m_dataptrs)
{ 

scrollindex-=m_mainlist->GetCount();// Zero scrollindex to list index

POSITION pos=m_dataptrs->GetHeadPosition();


if(scrollindex >=0 && pos){ pos=m_dataptrs->FindIndex(scrollindex);}	
while( pos && cnt)
{
CRegularPeriod* ptr=(CRegularPeriod*) m_dataptrs->GetAt(pos);  

ptr->setbox(&copybox);
if(ptr->display(basedate,currentperiod,pDC,handle))
{
copybox.OffsetRect(0,copybox.Height());}
cnt--;
m_dataptrs->GetNext(pos);}

}

}// end if m_mainlist

}



UINT CTimelist::GetImage(void)
{

if(is_open){return IDB_OPEN;}
else {return IDB_CLOSED;}

}

DWORD CTimelist::getparent_id(void)
{




return parent_id;

}
void CTimelist::setopen(const BOOL openstate)
{


is_open=openstate;

}

void CTimelist::resetallid(void)
{

CPeriod::resetid();

if(m_mainlist)
{

POSITION pos=m_mainlist->GetHeadPosition();
while(pos)
{
CCategory* ptr=(CCategory*) m_mainlist->GetAt(pos);

ptr->resetallid();
m_mainlist->GetNext(pos);

}

}// end if m_mainlist

} 


void CTimelist::setallid(void)
{


setid();

POSITION pos=GetHeadPosition();

	while(pos)

		{

			CTimelist* ptr= (CTimelist*) GetAt(pos);

			ptr->setallid();

			GetNext(pos);

			}



}

#ifndef STANDALONE 		  

void CTimelist::OnFileUpdateDatabase(CLog& ds, CString contractno, const long empno, const CString estab, CAbsolutePeriod start)
{



POSITION pos=GetHeadPosition();

if(!pos)
{
UpdateDatabase(ds, contractno, empno ,estab, start);
	}

else
	{

	while(pos)
	

		{

			CPeriod* ptr= (CPeriod*) GetAt(pos);

			ptr->UpdateDatabase(ds, contractno, empno, estab, start); // filled by overridden contract

			GetNext(pos);

			}

    }

} 


#endif


CString CTimelist::truncate(CString to_truncate)
{
if(!getdisplaycount())
{

to_truncate=to_truncate.Mid(0,1) + _T("..."); }

else
{
if(getbox()->TopLeft().y >=60)
{to_truncate.Empty();}

to_truncate=to_truncate.Mid(0,1);
}
return (to_truncate);
}

void CTimelist::Clearbalance(void)
{
 
CPeriod::Clearbalance();

if(m_mainlist)
{

POSITION pos=   m_mainlist-> GetHeadPosition();
while(pos)
{
CPeriod* ptr= (CPeriod*)   m_mainlist-> GetAt(pos);
ptr->Clearbalance();
m_mainlist-> GetNext(pos);}

if(m_dataptrs)
{
POSITION pos=  m_dataptrs-> GetHeadPosition();
while(pos)
	{
	CPeriod* ptr2=(CPeriod*)   m_dataptrs-> GetAt(pos);
	ptr2->Clearbalance();
	m_dataptrs-> GetNext(pos); }
	}

}// end if m_mainlist
}



void CTimelist::rebalance(void)
{

if(m_mainlist)
{

POSITION pos=  m_mainlist-> GetHeadPosition();
while(pos)
{
CTimelist* ptr=(CTimelist*)   m_mainlist-> GetAt(pos);
ptr->rebalance();


if( getstart() > ptr->getstart())

{ setstart(ptr->getstart());}  




*this += ptr;
 
/*
#ifdef _DEBUG
TRACE("%s,%d",Getname(),getduration().GetTotalHours());
#endif //_DEBUG	
*/
 

if(ptr->getduration().GetTotalMinutes()!=0){
setcolour(ptr->getcolour());

// DRP status

SetDRPstatus(ptr->GetDRPstatus());


}


m_mainlist-> GetNext(pos); }

}// end if m_mainlist

}    
	 
BOOL CTimelist::Removeall()
{
CTimelist* listptr=NULL;

if(m_mainlist)
{

#ifdef _DEBUG


 
POSITION pos=  m_mainlist-> GetHeadPosition();

while(pos){

listptr=(CTimelist*)   m_mainlist-> GetAt(pos);

afxDump << "\n Item is " << *listptr << "\n" ;


  m_mainlist-> GetNext(pos); } 

#endif
		  

while(!m_mainlist->IsEmpty()){
 
 		
delete   m_mainlist-> RemoveHead();} 

}// end m_mainlist

return TRUE;}


void CTimelist::flushdata(const BOOL All=TRUE)
{

if(m_dataptrs)
{
m_dataptrs->RemoveAll(); }


POSITION pos=  GetHeadPosition();
while(pos && All==TRUE)
{

CTimelist* ptr=(CTimelist*)   GetAt(pos);
ptr->flushdata(TRUE);

GetNext(pos);}




}


void CTimelist::flushmain(const BOOL ALL = TRUE)
{ 

	
m_mainlist-> RemoveAll();


POSITION pos=  GetHeadPosition();
while(pos && ALL==TRUE)
{

CTimelist* ptr=(CTimelist*)   GetAt(pos);
ptr->flushmain(TRUE);

GetNext(pos);} 


}


CTimelist* CTimelist::Findit(CObject* ptr)
{ 


CTimelist* listptr=this;



POSITION pos=0;
while(!(pos=listptr->m_mainlist->Find(ptr,0)) && listptr)
{

listptr=getnext_indent(listptr);

}

if(pos){listptr= (CTimelist*)   m_mainlist-> GetAt(pos);}

         

return listptr;}


 

void CTimelist::AddAll( CTimelist* rowlist,const long childmin,const long childmax)
{ 
CTimelist* ref=rowlist;

if(parent){
ref=rowlist->Add(this,childmin,childmax);}

if(m_mainlist)
{

POSITION pos=  m_mainlist-> GetHeadPosition();
while(pos)
{
CTimelist* ptr=(CTimelist*)   m_mainlist-> GetAt(pos);
ptr->AddAll(ref,childmin,childmax);

m_mainlist-> GetNext(pos);}

}// end if m_mainlist

}


POSITION  CTimelist::Add(CObject* ptr, const BOOL Is_List=TRUE /* assumes CTimelist* */)
{

POSITION pos=0;


if(Is_List)
{
pos= m_mainlist->AddTail((CObject*) ptr); }

else

{ pos= m_dataptrs->AddTail((CObject*) ptr);  }

return pos;



} 




//CTimelist* CTimelist::Add(const CTime basedate, const CString titlestring)
//{
//
//CTimelist* list_to_populate = NULL; 
//
//TRY
//	{
//
//	CNavdlg dlg(this);
//
//
//
//			if(m_mainlist->GetCount()==0)
//			{
//
//			list_to_populate =this;
//
//			//No navigator necessary
//
//			}
//
//			else
//
//			if(dlg.DoModal()==IDOK)
//			{
//
//					if(!titlestring.IsEmpty())
//						{dlg.titlestring=titlestring;}
//
//
//					if(dlg.m_peg->getcount()!=0)
//					{
//					AfxThrowUserException();
//
//					}
//
//
//			list_to_populate = dlg.m_peg;
//			// whichever list the navigator selects
//
//			// provided it has no subfolders
//			
//				}
//	}// end try
//
//	
//CATCH(CUserException, e)
//	{
//
//	 AfxMessageBox(IDS_NOADD_INSTRUCTION,MB_OK,0);
//
//	}
//
//END_CATCH
//
//
// return list_to_populate;
//} 



CObList* CTimelist::Getmainlist(void)
{

return m_mainlist;


}

void CTimelist::AddTail(CTimelist* feeder, 
						 BOOL strip)
{


CObList* lptr = feeder->Getmainlist();
  

while(!lptr->IsEmpty())
{

CObject* ptr = lptr->RemoveHead();
m_mainlist->AddTail(ptr);

}



}


CObject* CTimelist::Clone(void)
{

CObject* ptr= new CTimelist( Getname(),
							(CTimelist*) parent,
							(CTimelist*) uncle,
							GetFromToPosition(::MIN),
							GetFromToPosition(::MAX) 
							);
						
							

return ptr;
}
 

void CTimelist::Fill(CObList* listofill)
{  

CObject* ptr=0;

if(m_mainlist)
{

POSITION pos =   m_mainlist-> GetHeadPosition();
  while(pos)
  {
  ptr =   m_mainlist-> GetAt(pos);
   
  listofill->AddTail(ptr); 
  
    m_mainlist-> GetNext(pos);
  }
 
 }// end if m_mainlist



}



CTimelist* CTimelist::Add(CTimelist* uncle, const long childmin, const long childmax)
{ 
  
  CTimelist* prnt=this;  
  CObject* ptr;
  ptr =new CTimelist(_T(""),prnt,uncle,childmin, childmax);
  Place((CPeriod*) ptr);
  CTimelist* lptr=(CTimelist*) ptr;
 
  
return lptr;} 



CTimelist* CTimelist::Add(CString title,CTimelist* uncle, const long childmin, const long childmax,const CString contractno=_T("NOLOGIN"))
{ 

 
  
return NULL;}






void CTimelist::AddTail(CObList* newlist)
{
m_mainlist->AddTail(newlist);}

POSITION CTimelist::AddTail(CObject* item_to_add)
{

return m_mainlist->AddTail(item_to_add);


} 


BOOL CTimelist::Removedata(CPeriodlist* m_data, BOOL Warnings)
{ 

BOOL carry_on=TRUE;

if(m_mainlist)
{


POSITION pos=  m_mainlist-> GetHeadPosition();
while(pos && carry_on)
{

CTimelist* listptr=(CTimelist*)   m_mainlist-> GetAt(pos);
carry_on=listptr->Removedata(m_data,Warnings);
  m_mainlist-> GetNext(pos);


}

}//	 end if

while(m_dataptrs && !(m_dataptrs->IsEmpty()) && carry_on )
{ 

CObject* ptr= m_dataptrs->GetHead();
/*
#ifdef _DEBUG 
afxDump 
<< "m_dataptrs " << *ptr << "\n" ;
#endif
*/
carry_on=m_data->Deleteitem(ptr,Warnings);

}// end while


return carry_on;


}


BOOL CTimelist::Deleteitem(CTimelist* item, CPeriodlist* m_data)
{   

UINT STRING_ID=0;
CString rstring;

TRY{

POSITION pos=  m_mainlist-> Find(item);
CTimelist* ptr=(CTimelist*)   m_mainlist-> GetAt(pos);
CTimelist* uncleptr=(CTimelist*) uncle; 

if(uncleptr->has_this_uncle(ptr)){

STRING_ID=IDS_NOCANDO;

AfxThrowUserException();}

AfxFormatString1(rstring, IDS_DIREDELETEWARNING,item->Getname()); 


switch(AfxMessageBox(rstring,MB_YESNOCANCEL|MB_ICONQUESTION,(UINT)0))
	{

	case IDYES:
		{

		
		STRING_ID=IDS_GET_HELP;
		AfxThrowUserException();
		
		}
		break;
	case IDNO:{;}
		break;
	default:
		{
		STRING_ID=IDS_USERABORT;
			AfxThrowUserException();
		}
		break;




	}
	   /*
		if(AfxMessageBox(rstring,MB_YESNOCANCEL|MB_ICONQUESTION,0)!=IDOK)
		{

		STRING_ID=IDS_USERABORT;
		AfxThrowUserException();

		}
		*/

if (pos && ptr->Removedata(m_data))
{

// delete any subheadings and data items 


ptr->Removeall();
m_mainlist->RemoveAt(pos);
delete ptr;
}



return TRUE;





}



CATCH(CUserException, e)
{
	
AfxMessageBox(STRING_ID,MB_OKCANCEL|MB_ICONEXCLAMATION,0);
return FALSE;	
}
	        
		 	    
		
END_CATCH
	
{
	
return TRUE;	
	
} 


} 



/* Iteration and location services.
  
1) Returns head of indent, or nothing if invalid indent.

*/

CTimelist* CTimelist::getnext_indent( CTimelist* ptr)
{


ptr=0;


if(m_mainlist)
{



POSITION pos=   m_mainlist-> GetHeadPosition();
    if(pos)
    {
    ptr=(CTimelist*)   m_mainlist-> GetAt(pos);
               	
  	}

}// end if  	
  	
return ptr;

}



				



  
BOOL CTimelist::showmenu(CView* handle, const CPoint& coords)
{
    	
    CMenu popup;
    CMenu popup2;
    

	popup.CreatePopupMenu();
	popup2.CreatePopupMenu();
	
	HMENU mhand=popup2.GetSafeHmenu();
	BOOL CanAddChildren(((CCategory*) Getuncle())->CanAddChildren()); 
	
	
	popup.AppendMenu(MF_POPUP,(UINT)mhand,_T("&Add"));
		//popup2.AppendMenu(MF_STRING,ID_ADD,"&Account");
		//if(!CanAddChildren){ popup.EnableMenuItem(ID_ADD,MF_GRAYED);}
	popup2.AppendMenu(MF_STRING,ID_ADD_ADDINSTRUCTION,_T("&Instruction"));
	if(parent){
	
	popup.AppendMenu(MF_SEPARATOR,0,_T("")); }
	
	if(!is_open){
	popup.AppendMenu(MF_STRING,ID_ZOOM,_T("&Open"));
	}
	else if(parent){
    popup.AppendMenu(MF_STRING,ID_UNZOOM,_T("&Close"));
	popup.AppendMenu(MF_STRING,ID_NAVIGATE,_T("&Navigate"));
    
    }
	
	popup.AppendMenu(MF_STRING,ID_VIEW_BYITEM,_T("&Beam me up Scotty"));
	popup.TrackPopupMenu(TPM_LEFTBUTTON ,coords.x ,coords.y + 150, handle ,0);
	popup.Detach();
	
    
return TRUE;	

 }

/* Functions to enable storage and retrieval uncles */


BOOL CTimelist::CheckAddresses(void)
{
                                          
BOOL IsOk = CPeriod::CheckAddresses();

if(m_mainlist)
{


POSITION pos=  m_mainlist->GetHeadPosition();
while(pos && IsOk)
{

CPeriod* ptr=(CPeriod*)   m_mainlist-> GetAt(pos);
IsOk= ptr->CheckAddresses();

m_mainlist-> GetNext(pos);}

}// end if

return IsOk;

}

CTimelist* CTimelist::GetHead(void)
{

return (CTimelist*) m_mainlist->GetHead();
}

CTimelist* CTimelist::GetTail(void)
{

return (CTimelist*) m_mainlist->GetTail();
}


CPeriod* CTimelist::Find_BY_Name(const CString name)
{

POSITION pos = GetHeadPosition();

CPeriod* ptr=NULL;

while(pos)
{

ptr = (CPeriod*) m_mainlist->GetAt(pos);

		if(name==ptr->Getname())
		{


 		break;
 
 
 		}

GetNext(pos); 


}

return ptr;



}


CPeriod* CTimelist::Find_AT_Index(int index)
{

POSITION pos = m_mainlist->FindIndex(index);

return ((CPeriod*) GetAt(pos));

}

POSITION CTimelist::GetHeadPosition(void)
{
 TRY
 {

 if(!m_mainlist){ AfxThrowUserException();}

 }

 CATCH(CUserException, e)
 {

 AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

 }

 END_CATCH
 {


 }

 return	 m_mainlist->GetHeadPosition();
}

POSITION CTimelist::GetTailPosition(void)
{

return m_mainlist->GetTailPosition();
}


CPeriod* CTimelist::GetAt(POSITION& pos)
{




return (CPeriod*) m_mainlist->GetAt(pos);

}




CPeriod* CTimelist::GetNext(POSITION& pos)
{


return (CPeriod*) m_mainlist->GetNext(pos);

} 

void  CTimelist::GetPrev(CObject*& searchitem)
{

/* gets the previous arrangement in the list, if any*/
TRY
{

if(m_dataptrs)
{



POSITION pos=m_dataptrs->Find(searchitem,0);
if(pos){ 

m_dataptrs->GetPrev(pos);


	}

if(pos)
{

searchitem = (CObject*) m_dataptrs->GetAt(pos);


}
else
{
searchitem = NULL;

}



}

else { AfxThrowUserException();}

}

CATCH(CUserException,e)
{

AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

}

END_CATCH
{



}
}


CPeriod* CTimelist::GetPrev(POSITION& pos)
{


return (CPeriod*) m_mainlist->GetPrev(pos);

} 

BOOL CTimelist::Append(void)
{

// example for CArchive::CArchive

return FALSE;
}

 

BOOL CTimelist::has_this_uncle(const CPeriod* uncptr)
{


if(Is_uncle(uncptr)){return TRUE;}

else{ 

BOOL success=FALSE;

POSITION pos =    GetHeadPosition();
  while(pos && !success)
  {
  CTimelist* ptr=(CTimelist*) GetAt(pos);
  success=ptr->has_this_uncle(uncptr);
  GetNext(pos); }
 
return success;  }


}





void CTimelist::Serialize(CArchive& ar)

{   

    

	m_mainlist->Serialize(ar);	
   
	CPeriod::Serialize(ar);
	
    
    
	if(ar.IsStoring())
	{ 
	
	parent_id =(DWORD) this;
	
	
	ar << parent_id;	} 
	
	else
	{
	
	 ar >> parent_id;
	
	
	 
	 restore_children();}
		
	
  }
		  

		  
		  
int CTimelist::getcount(void)
{
	int cnt(0);

	if(m_mainlist)
	{

	POSITION pos=  m_mainlist-> GetHeadPosition();
	
	while(pos)
	{   
		cnt++;
		m_mainlist-> GetNext(pos);
	}

	}// end if
		
return cnt;

}

int CTimelist::getdisplaycount(void)
{
	int cnt(0);

	if(m_mainlist)
	{
	
	cnt= m_mainlist->GetCount();}
	
	if(m_dataptrs)
	{

	cnt += m_dataptrs->GetCount();} 
		
return cnt;

}	

#ifdef _DEBUG
void CTimelist::Dump(CDumpContext& dc) const
{   
    
    
	CObject::Dump(dc);
//	dc  <<"\n name"  << name <<"\n";
}
#endif //_DEBUG		  	
	  	


BOOL CTimelist::DeleteInstruction(CPeriod* item, CPeriodlist* m_data)
{


BOOL outcome= m_data->Deleteitem(item);

return outcome;
}


void CTimelist::setboxesempty(void)
{
//set yourself

setboxempty();

 
// set your data items 



if(m_dataptrs)
{
POSITION datapos=  m_dataptrs-> GetHeadPosition();
while(datapos)
	{
	CRegularPeriod* ptr=(CRegularPeriod*)   m_dataptrs-> GetAt(datapos);
	ptr->setboxempty();
	m_dataptrs-> GetNext(datapos); }
	} // end if

if(m_mainlist)
{

POSITION pos=  m_mainlist-> GetHeadPosition();
while(pos)
	{
	CTimelist* ptr=(CTimelist*)   m_mainlist-> GetAt(pos);
	ptr->setboxesempty();
	m_mainlist-> GetNext(pos);
	}

 }// end if

}

BOOL CTimelist::prioritise(const CTime basedate, CAbsolutePeriod slice, const UINT trans_type, const int fwkno, BOOL& has_priority)
{
 /* recursively looks for CDebit objects that obscures another for this day
	for a given staff member and assigns priority among them */

  

if(m_dataptrs)
	{
	POSITION pos = m_dataptrs->GetTailPosition();
	
	while(pos )
		{
		CRegularPeriod* ptr=(CRegularPeriod*) m_dataptrs->GetAt(pos);
			
		if( ptr->proxydocket(basedate,slice,trans_type,fwkno,has_priority) && ptr->Overwrite(slice))	
			{
			
			// By default all new arrangements override previous arrangements
			// unless the previous arrangement is an absence of less than seven hours
			
			
			has_priority=FALSE;
			
			 
			} //end if proxydocket

		  
		
		m_dataptrs->GetPrev(pos);} 	// end while
  	 
	}//end if m_dataptrs



	POSITION pos2=GetHeadPosition();
	while(pos2)
		{
		CTimelist* ptr=(CTimelist*) GetAt(pos2);
		//   has_priority=TRUE;
		ptr->prioritise(basedate,slice,trans_type, fwkno, has_priority);
		GetNext(pos2);}	//end while
	
return has_priority; 


}

BOOL CTimelist::IsConflictDay(CRegularPeriod& test, CPeriod* original, const UINT dayoftheweek)
{
BOOL clashfound(FALSE);
BOOL keepdigging(TRUE);

if(m_dataptrs)
	{
	POSITION pos = m_dataptrs->GetTailPosition();
	
	while(pos  && !clashfound && keepdigging)	   // keep iterating until first with common eventful day found
		{
		keepdigging=FALSE; 
		CRegularPeriod* ptr=(CRegularPeriod*) m_dataptrs->GetAt(pos);
		clashfound = original != ptr && ptr->dayshared(test,dayoftheweek);	// test for overlapping day

		if(clashfound ){
		// 
		 clashfound = ptr->Clashes(test,dayoftheweek); } // test the shift for overlapping time
		 else
		 {

		 // not an eventful day i.e day off 
		 keepdigging = TRUE;

		 }
		
		
		m_dataptrs->GetPrev(pos);
		} // end while
		
	 }	// end if
  	 

	POSITION pos2=GetHeadPosition();
	while(pos2 && !clashfound && keepdigging)
		{
		CTimelist* ptr=(CTimelist*) GetAt(pos2);
		clashfound=ptr->IsConflictDay(test, original,dayoftheweek);
		GetNext(pos2);}	
	
return clashfound; 

}


BOOL CTimelist::IsConflict(CRegularPeriod& test, CPeriod* original, const BOOL timeshared)
{ 

/* checks whether most recently added shift with common day	clashes 
 timeshared variable determins whether test of time overlap is carried out
 keepdigging variable determins whether test is to continue when e.g. a day off is encountered
  */

	
 

BOOL clashfound(FALSE);
BOOL keepdigging(TRUE);
UINT dy;
for(dy=0;dy<7;dy++)
{
if(clashfound){break;}
else{clashfound=FALSE;
keepdigging = TRUE;	}

if(m_dataptrs)
	{
	POSITION pos = m_dataptrs->GetTailPosition();
	
	while(pos  && !clashfound && keepdigging)	   // keep iterating until first with common eventful day found
		{
		
		
		CRegularPeriod* ptr=(CRegularPeriod*) m_dataptrs->GetAt(pos);
		
		clashfound = (original != ptr && ptr->dayshared(test,dy));//original != ptr && 	// test for overlapping day
		
		if(clashfound ){ keepdigging=FALSE; clashfound = ptr->Clashes(test,dy); } // test the shift for overlapping time
		else
		{
		 /* all days off */
		 keepdigging = TRUE;
		 
		}
		
		m_dataptrs->GetPrev(pos);
		} // end while
		
	 }	// end if
  	 

	POSITION pos2=GetHeadPosition();
	while(pos2 && !clashfound && keepdigging)
		{
		CTimelist* ptr=(CTimelist*) GetAt(pos2);
		clashfound=ptr->IsConflict(test, original,timeshared);
		GetNext(pos2);}	

}//next dy	
return clashfound; 

} 



void CTimelist::setid(void)
{

CPeriod::setid_direct( uncle->get_id());



} 




void CTimelist::Place(CPeriod* ptr)
{ 
/* The list's uncleptr must set its children's id's 
	so that its child accounts can be placed in uncle order */

CCategory* uncleptr = (CCategory*)  Getuncle();
uncleptr->set_relative_id(0); /* dummy indent; not used in this operation */

CPeriod* itemptr=0;
WORD existing_item_index=0;
WORD item_to_place_index=ptr->GetIndex();

if(m_mainlist)
{

POSITION pos=m_mainlist->GetHeadPosition();


while(pos)
{

itemptr= (CPeriod*) m_mainlist->GetAt(pos);

existing_item_index= itemptr->GetIndex();

if(item_to_place_index > existing_item_index)

{ m_mainlist->GetNext(pos);} 

else{

break;} 




}// end while 

if(pos){ m_mainlist->InsertBefore(pos,(CObject*) ptr);}

else { m_mainlist->AddTail((CObject*) ptr);}

}// end if m_mainlist

uncleptr->resetid();

}




BOOL CTimelist::scoopdata(CObList* datalist)
{


if(m_dataptrs) {
            
            POSITION pos=m_dataptrs->GetHeadPosition();
			while(pos)
				{

				CRegularPeriod* ptr= (CRegularPeriod*) m_dataptrs->GetAt(pos);
				CObject* newptr=ptr->Clone();
				if(newptr) // if it is a credit then this will be null
				{
				ASSERT_VALID(newptr);
				datalist->AddTail(newptr);}
				m_dataptrs->GetNext(pos);}




}




POSITION pos2 = GetHeadPosition();


while(pos2)
{ 

CTimelist* ptr=(CTimelist*) GetAt(pos2);
ptr->scoopdata(datalist);
GetNext(pos2);
}

return TRUE;



} 

BOOL CTimelist::ContainsNoEstab(void)
{

//overridden in derived class
return TRUE;

}


void CTimelist::doit(void (*func )(void) )
{

BOOL BINGO=FALSE;

func();
BINGO=TRUE;



}


int CTimelist::GetFirstBalance(void)
{



 int cnt(-1);
 


 POSITION pos = GetHeadPosition();
 
 if(pos){cnt=0;}
 
 while(pos)
 {

 

 CPeriod* pd = (CPeriod*) GetAt(pos);

 if(!pd->getbalance())
 {

 }

 else
 {

 break;
 
 
 }

 

 cnt++;

 GetNext(pos);

 }


 return cnt;


}

   

BOOL CTimelist::IsExtraProv(void)
{
return false;
}

void CTimelist::SetFromToPositionYouAndBelow(const int flag, const long value)
{

if(m_dataptrs) {
            
            POSITION dpos=m_dataptrs->GetHeadPosition();
			while(dpos)
				{

				CRegularPeriod* ptr= (CRegularPeriod*) m_dataptrs->GetAt(dpos);
				ptr->SetFromToPositionToCredit(flag,value);

				m_dataptrs->GetNext(dpos);}
				}

  SetFromToPosition(flag,value);


 POSITION pos =  GetHeadPosition();
	while(pos)
	{

	CTimelist* ptr=(CTimelist*)   GetAt(pos);
	ptr->SetFromToPositionYouAndBelow(flag,value);

	GetNext(pos);

	}




}

CTimelist* CTimelist::Add(const CTime basedate, const CString titlestring)
{

	CTimelist* list_to_populate = NULL;

	TRY
	{

	CNavdlg dlg(this);



			if (m_mainlist->GetCount() == 0)
			{

			list_to_populate = this;

			//No navigator necessary

			}

			else

			if (dlg.DoModal() == IDOK)
			{

					if (!titlestring.IsEmpty())
						{
dlg.titlestring = titlestring;
}


if (dlg.m_peg->getcount() != 0)
{
AfxThrowUserException();

}


list_to_populate = dlg.m_peg;
// whichever list the navigator selects

// provided it has no subfolders

	}
	}// end try


		CATCH(CUserException, e)
	{

		AfxMessageBox(IDS_NOADD_INSTRUCTION, MB_OK, 0);

	}

	END_CATCH


		return list_to_populate;
}


