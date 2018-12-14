//navdlg.h: implementation file
//

#include "stdafx.h"
#include <afxdb.h>
//#include "centool8.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "span.h"
#include "period.h" 
#include "timelist.h"
#include "navdlg.h"

#include <stdio.h>




#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNavdlg dialog


CNavdlg::CNavdlg(CTimelist* pPeg /*!=NULL*/)
	:CDialog(CNavdlg::IDD, NULL),m_peg(pPeg),titlestring("Move to ")
{
	//{{AFX_DATA_INIT(CNavdlg)
	//}}AFX_DATA_INIT
	
	
}



void CNavdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNavdlg)
	DDX_Control(pDX, IDC_LIST1, m_LB);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNavdlg, CDialog)
	//{{AFX_MSG_MAP(CNavdlg)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BACKUP, OnBackup)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNavdlg message handlers

BOOL CNavdlg::OnInitDialog()
{
		
	// TODO: Add extra initialization here 
	
	if(m_peg){
	
    SetTitle(m_peg);	
	
    setbackup(m_peg);

	Fill_listbox(m_peg);

	CWnd* pwnd = GetDlgItem(IDOK);
	pwnd->EnableWindow(false);
	
	return CDialog::OnInitDialog();}  

	else
	{

	// cancelling will ensure that the main programme still has
	 //a valid pointer 
	CDialog::OnCancel();
	return FALSE;

	}
}

void CNavdlg::OnOK()
{
	// TODO: Add extra validation here 
	
	TRY  // diagnostics
	{
		
	
	/* make sure not NULL */
	
	
	if(!m_peg){AfxThrowUserException();}


	
	
	// if all clear
	
	CDialog::OnOK();	
		
	}//end Try
	
	CATCH(CUserException, e)
	{
	 
	 AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);
	 CDialog::OnCancel();// cancelling will ensure that the main programme still has
	 //a valid pointer 
	
	}
	        
		 	    
		
	END_CATCH
	
	{
	
	
	
	
	}
	

	
	  
}



void CNavdlg::OnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	
	TRY{
	 
	
	
		
	CListBox* pLB=(CListBox*) GetDlgItem(IDC_LIST1);
	int index=pLB->GetCurSel();

	if(index!=LB_ERR)
	{ 
	m_peg =(CTimelist*) pLB->GetItemDataPtr(index);

	}

	

SetTitle(m_peg);	

Fill_listbox(m_peg);

CWnd* pwnd = GetDlgItem(IDOK);
pwnd->EnableWindow(true);

}//end of Try

CATCH(CUserException, e)
	{
	 
	 AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);
	 CDialog::OnCancel();}

	 /* All selections should be of a valid index and pointer.
	 Cancelling will ensure that the main programme
	 still has a valid list pointer */


END_CATCH
	
	{
	
	
	
	
	}	
		
	
} 


void CNavdlg::SetTitle(CTimelist* currentlist)
{


CWnd::SetWindowText(titlestring + currentlist->Getname());

 
SetDlgItemText(IDC_CURRENT,_T("current selection: ") + currentlist->Getname()); 

}

void CNavdlg::OnDblclkList1()
{
	// TODO: Add your control notification handler code here 
	
}


BOOL CNavdlg::Fill_listbox(CTimelist* listfiller)
{

	/* Fill list box */ 
	
	
	CListBox* pLB=(CListBox*) GetDlgItem(IDC_LIST1);
	
	
	
   if(listfiller)
	{
	    			    
    	POSITION pos=listfiller->GetHeadPosition();
   		int cnt=0;
   		
   		
   			if(pos)
   			{
   		
   		
   				for(int cnt=0;cnt<pLB->GetCount();cnt++)
					{pLB->SetItemDataPtr(cnt,NULL);	}
			pLB->ResetContent();
   		                        		
   			}
   		
   		
   		
   		
    	while(pos)
    		{
    		CTimelist* ptr=(CTimelist*) listfiller->GetAt(pos);
    		if(!ptr->IsExtraProv())
				{
				pLB->InsertString(cnt,ptr->Getname());
				pLB->SetItemDataPtr(cnt,ptr);
				cnt++;
				}
			listfiller->GetNext(pos);
			}
		
		setbackup(listfiller);
	    return TRUE;
		}
		
        else {return FALSE;}


}
void CNavdlg::setbackup(CTimelist* currentlist)
{

TRY
{

CButton* pBtn=(CButton*) GetDlgItem(IDC_BACKUP);

CPeriod* ptr=0;

if(!currentlist){AfxThrowUserException();}

ptr = currentlist->Getparent();
pBtn->EnableWindow(ptr!=NULL);

}

CATCH(CUserException,e)
{

 AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);


}

END_CATCH
{



}

} 



void CNavdlg::OnBackup()
{
	// TODO: Add your control notification handler code here 

	TRY{

	CPeriod* ptr= m_peg;
	ptr = ptr->Getparent();
	if(ptr==NULL){AfxThrowUserException();}
	// disabled button should make this impossible
	m_peg=(CTimelist*) ptr;
	
	
	if(Fill_listbox(m_peg)){
	SetTitle(m_peg);	
	}


	CWnd* pwnd = GetDlgItem(IDOK);
	pwnd->EnableWindow(true);


	}

	CATCH(CUserException, e)
	{
	 
	 AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);
	 CDialog::OnCancel();
	 /* cancelling will ensure that the main programme
	 still has a valid list pointer */
	
	}


	
END_CATCH
{



}





}

void CNavdlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	WinHelp( 0x18032, HELP_CONTEXT);
}
