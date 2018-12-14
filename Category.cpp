// category.cpp : implementation file
//

#include "stdafx.h"
#include <afxdb.h>
#include "Resource.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "span.h"
#include "shift.h" 
#include "period.h"
#include "timelist.h"
#include "addac.h" 
#include "category.h" 
//#include "contract.h"

//#include "regularp.h"
#include <stdio.h>



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//CCategory

IMPLEMENT_SERIAL(CCategory, CTimelist,2)

CCategory::CCategory():CTimelist(),Is_relative(FALSE),m_codelist(NULL)
{

m_codelist= new CObList;
 
CPeriod::setcolour(RGB(0,0,0));
shareuncle(uncle);

} 

CCategory::CCategory(const CString title,
						   CPeriod* prnt,
						   CPeriod* uncl):CTimelist(title,(CTimelist*)prnt,
						   										(CTimelist*)uncl,
						   										0,
						   										364),
						   										Is_relative(FALSE),
						   										table_ID("NOTHING"),
																m_codelist(NULL)
						   										
{
 
m_codelist= new CObList;
CPeriod::setcolour(RGB(0,0,0));

}

CCategory::CCategory(const CString title,
						   CPeriod* prnt,
						   CPeriod* uncl,
						   const CString table_id):CTimelist(title,(CTimelist*)prnt,
						   										(CTimelist*)uncl,
						   										0,
						   										364),
						   										Is_relative(FALSE),
						   										table_ID(table_id),
																m_codelist(NULL)
{ 


CPeriod::setcolour(RGB(0,0,0));

}


CCategory::~CCategory()
{
	while (!m_codelist->IsEmpty())

	{
		delete m_codelist->RemoveHead();
	}

	delete m_codelist;


}





/////////////////////////////////////////////////////////////////////////////
// CCategory message handlers

void CCategory::Get_uncle_colour(void)
{;} 


void CCategory::setcolour(void)
{;} 

void CCategory::resetcolour(void)
{;} 


CString CCategory::Getcode(CSpan* pshft)
{
  

CCategory* pd = NULL;
CString code("");

int cnt = pshft->GetFirstBalance();

if(cnt>=0)
{



pd=(CCategory*) Find_AT_Index(cnt);


if(pd!=NULL){  code = pd->get_table_ID();} }



return code;


}



CString CCategory::Getdlgcode(CSpan* pshft)
{


 return _T("");

}

CString CCategory::Getcodestring(CSpan* sp, CComboBox& combo )
{

CString codestring;
codestring.Empty();

if(m_codelist)
{

POSITION pos = m_codelist->GetHeadPosition();

while(pos && codestring.IsEmpty() )
{

CShift* shift = (CShift*) m_codelist->GetAt(pos);
if(sp->getstart()== shift->getstart() &&
		 sp->getduration()== shift->getduration())
		 { codestring = shift->getletter();}

m_codelist->GetNext(pos);


}


}

return codestring;



}

CTimelist* CCategory::Add(CTimelist* uncle,const long from=0,const long to=364)
{
  
return NULL;


}

int CCategory::FindSpan(CSpan* maybe_dupe,CComboBox& combo)
{

 /* returns index in list from 0, -1 if no match */
 
 BOOL Is_Match(FALSE);
 int cnt(0);

if(!m_codelist)
{ 

combo.SetCurSel(-1);

return -1;
}

else
{

	POSITION pos = m_codelist->GetHeadPosition();

	while(pos && !Is_Match)
	{

 	CSpan* ptr = (CSpan*) m_codelist->GetAt(pos);
 
 				if(*maybe_dupe==ptr){ Is_Match=TRUE; break;}
 	cnt++;
 	m_codelist->GetNext(pos);
 	
 	}

	if(Is_Match)
	{ 

	combo.SetCurSel(cnt);
	return cnt;
	}

	else 
	{
	
	combo.SetCurSel(-1);
	return -1;
	}

} // end if m_codelist

}

BOOL CCategory::Is_dupe(CShift* maybe_dupe)
{

BOOL Is_Dupe(FALSE);

if(m_codelist)
{

POSITION pos = m_codelist->GetHeadPosition();

while(pos && !Is_Dupe)
{

 CShift* ptr = (CShift*) m_codelist->GetAt(pos);
 Is_Dupe= *ptr==(maybe_dupe);
 m_codelist->GetNext(pos);}

}

return Is_Dupe;


}

BOOL CCategory::Delshift(CObject* item_to_go)
{

 POSITION pos = m_codelist->Find(item_to_go);

 if(pos){

 CObject* ptr = m_codelist->GetAt(pos);
 m_codelist->RemoveAt(pos);
 delete ptr;
 return TRUE;}

 else

 { return FALSE ;}



}

BOOL CCategory::Addshift(CObject*& newitem)
{



POSITION pos=NULL;
BOOL Is_Dupe(Is_dupe((CShift*) newitem));



// first see if duplicates shift 
if(!Is_Dupe)
{

pos = m_codelist->AddTail(newitem);}
else
{

AfxMessageBox( IDS_DUPE ,MB_OK|MB_ICONEXCLAMATION,0);

}



return Is_Dupe==FALSE && pos!=NULL;



}



int CCategory::IsDupeCode(const CString txt)
{

//returns index of duplicate code or -1 if not found

BOOL Is_Dupe(FALSE);
int cnt(0);

if(m_codelist)
{

POSITION pos = m_codelist->GetHeadPosition();

while(pos && !Is_Dupe)
{

 CShift* ptr = (CShift*) m_codelist->GetAt(pos);
 Is_Dupe= ptr->getletter()==txt;
 if(Is_Dupe){break;}
 m_codelist->GetNext(pos);
 cnt++;
 }

 if(Is_Dupe){return cnt;}
 else
 { return -1;}

 }

 else

 {

 return -1;

 }

}







BOOL CCategory::fillbox(CComboBox*& pcombo, CPeriod* parent)
{

 CTimeSpan finish(::NONE);
 pcombo->ResetContent();

 CString txt;

 if(m_codelist)
 {
 POSITION pos = m_codelist->GetHeadPosition();
	int cnt(0);
	 

	while(pos)
	{

	 CShift* shiftptr = (CShift*) m_codelist->GetAt(pos);
	 finish = shiftptr->getstart() + shiftptr->getduration();
	 txt=shiftptr->getletter() + _T(" - ") + shiftptr->getstart().Format("%H:%M") + _T(" ") + finish.Format("%H:%M");
	 pcombo->InsertString(cnt,txt);
	 pcombo->SetItemDataPtr(cnt,shiftptr); 
	 m_codelist->GetNext(pos);
	 cnt++;
	}

 }
return TRUE;


}

CString CCategory::get_table_ID(void)
{
return table_ID;
}

void CCategory::set_all_relative(void)
{ 
DWORD generated_id=(DWORD) getcolour();
setid_direct(generated_id);
set_relative_id(generated_id);


}

BOOL CCategory::codelistEmptyOrInActive(void)
{

BOOL defunct(FALSE);
defunct = !codelistIsActive(); 
if(!defunct){ defunct=m_codelist->IsEmpty();}

return defunct;

}

BOOL CCategory::codelistIsActive(void)
{


return m_codelist!=NULL;

}

BOOL CCategory::codelistUpdateable(void)
{

return TRUE;

}

BOOL CCategory::Is_Catview(void)
{


return TRUE;

}

void CCategory::Getcodelist(CObList*& ptr)
{


ptr = m_codelist;

}

BOOL CCategory::Setcodelist(CObList* codelist)
{




return FALSE;

}

void CCategory::set_relative_id(const UINT indent)
{

WORD index=1;

if(m_mainlist)
{

POSITION pos=m_mainlist->GetHeadPosition(); 



	while(pos)
		{
		CPeriod* ptr=(CPeriod*) m_mainlist->GetAt(pos);
        ptr->setid_direct( MAKELONG(indent,index)); 
        Is_relative=TRUE;
       	m_mainlist->GetNext(pos); 
		index++;

		}

}

}


void CCategory::setid(void)
{


CPeriod::setid_direct((DWORD) this);


} 





WORD CCategory::GetIndex(void)
{


WORD result = HIWORD(get_id());

return result;

}


WORD CCategory::GetIndent(void)
{


return LOWORD(get_id());



}

void CCategory::shareuncle(CPeriod* uncletobe)
{

set_uncle(uncletobe);

POSITION pos = GetHeadPosition();

  while(pos)
  {
  CCategory* ptr=(CCategory*) GetAt(pos);
  ptr->shareuncle(uncle);
  GetNext(pos); }


  }

BOOL CCategory::Restore_Uncle(CPeriod* uncptr)
{

if(CPeriod::Restore_Uncle(uncptr)){

return TRUE;}

else{ 

BOOL success=FALSE;

POSITION pos =    GetHeadPosition();
  while(pos && !success)
  {
  CCategory* ptr=(CCategory*) GetAt(pos);
  success=ptr->Restore_Uncle(uncptr);
  GetNext(pos); }
 
return success;  }


}   

void CCategory::set_uncle_id(void)
{

// do not do this


}

#ifdef _DEBUG
void CCategory::Dump(CDumpContext& dc) const
{   
    
    
	CObject::Dump(dc);
	//dc  <<"\n name"  << name <<"\n";
}
#endif //_DEBUG	 


BOOL CCategory::showmenu(CView* handle, const CPoint& coords)
{
    	
    CMenu popup;
    CMenu popup2;
    

	popup.CreatePopupMenu();
	popup2.CreatePopupMenu();
	
	HMENU mhand=popup2.GetSafeHmenu();
	
	popup.AppendMenu(MF_STRING,ID_EDIT,_T("&Edit"));
	if(((CCategory*)parent)->CanAddChildren()==FALSE)
	{ popup.EnableMenuItem(ID_EDIT,MF_GRAYED);}

	popup.AppendMenu(MF_STRING,ID_ADD,_T("&Add"));
	popup.EnableMenuItem(ID_ADD,MF_GRAYED);
		
	    
	popup.AppendMenu(MF_STRING,ID_DELETE,_T("&Delete"));

	if(((CCategory*)parent)->CanAddChildren()==FALSE)
	{ popup.EnableMenuItem(ID_DELETE,MF_GRAYED);}
	popup.AppendMenu(MF_SEPARATOR,0,_T(""));
	
	if(!is_open){
	popup.AppendMenu(MF_STRING,ID_ZOOM,_T("&Open"));}
	else if(parent){
    popup.AppendMenu(MF_STRING,ID_UNZOOM,_T("&Close"));}
    
	if(parent->Getparent())
    {
    popup.AppendMenu(MF_STRING,ID_VIEW_BYCATEGORY,_T("&Beam me up Scotty"));}
	popup.AppendMenu(MF_STRING,ID_NAVIGATE,_T("&Navigate"));
	
	popup.TrackPopupMenu(TPM_LEFTBUTTON ,coords.x ,coords.y + 150, handle ,0);
	popup.Detach();
	
    
return TRUE;	

 }

BOOL CCategory::Addcodes(void)
{

return FALSE;

}

BOOL CCategory::CanAddChildren(void)
{

return TRUE;//overridden in base classes

} 
 
void CCategory::Serialize(CArchive& ar)

{   


	
   
	CTimelist::Serialize(ar);
    
	
	
	
	if(ar.IsStoring())
	{ 
	
	
		
	ar << table_ID ;	} 
	
	else
	{

	
	
	 ar >> table_ID ; }
	
    TRACE("table_id %s",table_ID);
	
 }



BOOL CCategory::Deleteitem(CTimelist* item, CPeriodlist* m_data)
{   



if(!parent){

AfxMessageBox(IDS_NOCANDO,MB_OK,0);

return NULL;}

else
{

return CTimelist::Deleteitem(item,m_data);}





} 


BOOL CCategory::Edit(const CTime basedate)
{

CAddac dlg(basedate,NULL);

dlg.whichtitle=dlg.Edit;
dlg.m_name=Getname();
dlg.m_otherptr= m_mainlist;


if(parent){ dlg.nMin=(int) parent->GetFromToPosition(::MIN);}
else {dlg.nMin=0;}
if(parent){ dlg.nMax=(int) parent->GetFromToPosition(::MAX);}
else {dlg.nMax=364;}

              

dlg.from_position=(int) GetFromToPosition(::MIN);
dlg.to_position=(int) GetFromToPosition(::MAX);

if(dlg.DoModal()==IDOK)
{
		 
Setname(dlg.m_name);

SetFromToPosition(::MIN,(long) dlg.from_position);
SetFromToPosition(::MAX,(long) dlg.to_position); 


 
return TRUE;}
else { return FALSE;}

}

BOOL CCategory::IncrementNonstandard(CString& txt)
{

 //overridden in CGensup 

 return FALSE;




} 
   

BOOL CCategory::Overwrite(CRegularPeriod* arrangement, CAbsolutePeriod& slice)
{

// default behaviour of a category is to force overwriting of previous arrangements
// This behaviour is modified in the absence class which enables coexistence of an arrangement 
// of say training in the morning with a late shift


return TRUE;

}

 
