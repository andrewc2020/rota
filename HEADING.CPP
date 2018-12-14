// heading.cpp : implementation file
//

#include "stdafx.h"

#include <afxdb.h>
#include <afxdao.h>
//#include "catset.h"

#include "CONSTANT.H"

#include "RotaView.h"
#include "assert.h"
#include "state.h"
#include "absolute.h"
#include "span.h"
#include "period.h"
#include "timelist.h"
#include "category.h"
#include "heading.h"
#include "gensup.h" 
#include "absence.h"







#include <stdio.h>



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeading

IMPLEMENT_SERIAL(CHeading, CCategory,2)

CHeading::CHeading():CCategory()
{

m_codelist = new CObList;

CPeriod::setcolour(RGB(0,0,255)); 

}

CHeading::CHeading(const CString title, CPeriod* prnt,CPeriod* uncl):CCategory(title,(CTimelist*)prnt,(CTimelist*)uncl,_T("Hdg"))
{


m_codelist = new CObList;

CPeriod::setcolour(RGB(0,0,255)); 


}


CHeading::~CHeading()
{

}


/////////////////////////////////////////////////////////////////////////////
// CHeading message handlers

void CHeading::Serialize(CArchive& ar)

{   
	
	if(ar.IsStoring())
	{

	file_codes(TRUE);

	}

	CCategory::Serialize(ar);
	

 }  

void::CHeading::Get_uncle_colour(void)
{;}

#ifndef STANDALONE
CTimelist* CHeading::Add(CTimelist* uncle,
						 CDaoDatabase& db,
						 const long from=0,
						 const long to=364)
{

   
	

    CPeriod* prnt=this;  
	CObject* ptr=NULL;
	CTimelist* tmptr=NULL; 
    CString headings("");

         

	CCatset* dsptr = new CCatset(&db);
    
   	 
   	 
	dsptr->Open(dbOpenSnapshot,
			NULL,dbReadOnly);
			
     
    
	if(dsptr->IsOpen())
	{
    dsptr->MoveFirst();


		if(dsptr->m_Level3_Name=="Absence"){ 
     
    
    	ptr = (CObject*) new CAbsence(dsptr->m_Level3_Name, prnt,uncle);
    	m_mainlist->AddTail(ptr);
    	tmptr = (CTimelist*) ptr; }  


    
    	while(!dsptr->IsEOF())		
	     {
	     
	      
    	
    	 
    
        
		if(dsptr->m_Lev3ID == 1)		
	     { 
	         	  				
  			((CAbsence*) tmptr)->Add(dsptr->m_Level2_Name,uncle,0,364,dsptr->m_Lev2);
  		 }
  				          
  				
  
  
  	/*	
  
  		if(dsptr->m_Level3_Name=="Specific"){ 
   
  		ptr =new CSpecsup(dsptr->m_Level3_Name, prnt,uncle,"SP");
  		m_mainlist->AddTail(ptr);
  		tmptr=(CSpecsup*) ptr;}	

		

				
		if(dsptr->m_Lev3ID == 2)
  		{		
  				
  				((CSpecsup*)tmptr)->Add(dsptr->m_Level2_Name,uncle,0,364,dsptr->m_Lev2);
  				}     
				  */
   
				
  		if(dsptr->m_Level3_Name=="Cover"){ 
   
  		ptr = (CObject*) new CGensup(dsptr->m_Level2_Name, prnt,uncle,dsptr->m_Lev2 );
  		m_mainlist->AddTail(ptr);}
  
  			
						

		dsptr->MoveNext();

		}// end if !dsptr->EOF 	

	}// end if !open				               
					dsptr->Close();
					delete dsptr; 
					
/* reset name and id of establishment in .ini from incoming data */ 
   
   
  
   
return tmptr;


}

#endif

BOOL CHeading::shareuncle(void)
{


CCategory::shareuncle(uncle);

return uncle!=NULL;

}

BOOL CHeading::load_codes(void)
{

BOOL success(FALSE);

assert(uncle);

POSITION pos = GetHeadPosition();


while(pos)
{

 CCategory* pcat= (CCategory*) GetAt(pos);

  
 success = pcat->Setcodelist(m_codelist);
 

 pcat->GetNext(pos);


}

success=file_codes(FALSE);

return 	success;

}  

CTimelist* CHeading::Add(CTimelist* uncle,
						 const long from=0,
						 const long to=364)
{

 CPeriod* prnt=this;  
 CObject* ptr=NULL;
 CTimelist* tmptr=NULL; 
 
 

 ptr = (CObject*) new CAbsence(_T("Absence"), prnt,uncle);
 m_mainlist->AddTail(ptr);
 tmptr = (CTimelist*) ptr; 

 

 
  
  				
				

  				tmptr->Add(_T("Training"),uncle,0,364,_T("TR"));
  				tmptr->Add(_T("Sickness"),uncle,0,364,_T("S"));
  				tmptr->Add(_T("A/L"),uncle,0,364,_T("AL"));
  
  
  
  
  
  /*
  ptr =new CSpecsup("Specific", prnt,uncle,"SP");
  m_mainlist->AddTail(ptr);
  tmptr=(CTimelist*) ptr;
  */ 


  ptr = (CObject*) new CGensup(_T("Cover"), prnt,uncle,_T("C"));
  m_mainlist->AddTail(ptr);
  
return tmptr;

}

BOOL CHeading::CanAddChildren(void)
{
int count(getcount());
return (count < 3);
}
 
void CHeading::set_all_relative(void)
{ 

CPeriod::setid_direct(1234);

POSITION pos = GetHeadPosition();


while(pos)
{ 

CCategory* ptr=(CCategory*) GetAt(pos);
ptr->set_all_relative();
GetNext(pos);
}


}




BOOL CHeading::showmenu(CView* handle, const CPoint& coords)
{
  	
 ((CRotaView*) handle)->OnNavigate();
    
return FALSE;	

 }

 BOOL CHeading::file_codes(const BOOL storing)
 {

 

 // attempts to load or save common file used to hold shift codes
 // codes are shared by Scenario documents describing the same home
 // hence this data may not be stored in with the normal document archive.

 

 


CFileException e;

UINT STRING_ID(IDS_NOFILE);


// trapping CFileException::m_cause, CUserException


TRY
{
 BOOL success(FALSE);

 CFile f;

 CString FileName;

 FileName += uncle->Getname();

 if(FileName.IsEmpty()){ AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);exit(1);}

 /*make filename dos compatible extract illegal characters*/
 
 CString badcharset;

 badcharset="., '\''/'";
 
 CString dummy;
 CString dummy2;
 int cnt(0);
 int result(0);
  
  while(cnt<=FileName.GetLength())
 {
  dummy = FileName.Mid(cnt,1);
  result = badcharset.Find(dummy);
  if(result==-1){dummy2+=dummy;}
  cnt++;}
  
    
 FileName = dummy2.Left(8);
  
 
 FileName += ".sft";
  
 
 switch(storing)
 {

 case FALSE:	/* i.e loading */
 {

  
  if(!f.Open(FileName, CFile::modeRead ,&e))
  	{
		
		// try to open default instead

		if(!f.Open(_T("default.sft"), CFile::modeRead ,&e))
				
				{

				 // begin search

				AfxMessageBox(IDS_SEEKFILE,MB_OK);
	  
   				CFileDialog dlg(TRUE,_T("sft"),_T("*.sft")); 

				if(dlg.DoModal()==IDOK)
				{
		
		 			FileName=dlg.GetPathName();
		 			f.Open(FileName, CFile::modeRead ,&e);
		 
		 		} // end of successful file search

		 	else // warn user to build own file
		 		{
		 	

				AfxThrowUserException();
				
				} 	
		 	

	 
		   } // search aborted by user
	  

  }	// no file
   
  
  CArchive ar( &f, CArchive::load, 512 * 8, NULL );

   m_codelist->Serialize(ar);
   	  
  
 }

 break;


 case TRUE:
 	{

  
  
	f.Open( FileName, CFile::modeCreate | CFile::modeWrite,&e );
				
 		
 		CArchive ar( &f, CArchive::store, 512 * 8, NULL );

		 			
  		 m_codelist->Serialize(ar);		
 		
	}

 break;


 default:
 	{
 	  AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);
 	 
 	}

 break;

 	}//end of switch

 
 }//end of TRY

 CATCH( CFileException, e)
{
    if( e->m_cause == CFileException::fileNotFound )
       		{ 
       
       	

       /* do nothing:
       		handled within method.
       		Either user will find file through dialogue or  
       		user will build new shift codes file in current directory.
       */ }
    
}

AND_CATCH( CUserException, f)
{


 AfxMessageBox(IDS_NOSHIFTS,MB_OK,0);



}

 END_CATCH
 {



 }




 

 return TRUE;


 }
