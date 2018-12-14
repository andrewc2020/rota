// subbankd.cpp : implementation file
//

#include "stdafx.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include <afxdao.h>
#include "span.h"
#include "absolute.h"
#include "period.h"
#include "conset.h"
#include "timelist.h"
#include "contract.h"
#include "strlong.h"
#include "subbankd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubBankdlg dialog

CSubBankdlg::CSubBankdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubBankdlg::IDD, pParent)
{

 

}

CSubBankdlg::CSubBankdlg(CDaoDatabase& db, CObList* original, CWnd* pParent /*=NULL*/)
	: CDialog(CSubBankdlg::IDD, pParent), m_db(&db),m_existptr(original),m_endrota()
{
	//{{AFX_DATA_INIT(CSubBankdlg)
	//}}AFX_DATA_INIT


}

CSubBankdlg::~CSubBankdlg(void)
{




}


void CSubBankdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubBankdlg)
	DDX_Control(pDX, IDC_BUTTON3, m_reset);
	DDX_Control(pDX, IDC_LIST3, m_LIST3);
	DDX_Control(pDX, IDC_LIST2, m_LIST2);
	DDX_Control(pDX, IDC_LIST1, m_LIST1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubBankdlg, CDialog)
	//{{AFX_MSG_MAP(CSubBankdlg)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_LBN_SELCHANGE(IDC_LIST3, OnSelchangeList3)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSubBankdlg message handlers

void CSubBankdlg::OnOK() 
{
	// TODO: Add extra validation here

	
	Cleanup();

	
	CDialog::OnOK();
}

void CSubBankdlg::OnCancel() 
{
	// TODO: Add extra cleanup here

	Cleanup();
	AfxMessageBox(IDS_NO_SUB,MB_OK|MB_ICONEXCLAMATION);
	
	CDialog::OnCancel();
}

BOOL CSubBankdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// load LIST1 with bank staff

	
	int cnt(0); 
	CConset ds(m_db);

	ds.m_estabParam = AfxGetApp()->GetProfileString(_T("Database"),_T("Bank"),_T("BANK"));
	ds.m_endrotaParam = m_endrota;

	ds.m_strSort = "EMPLOYEE_N ASC";
			 
	ds.Open(dbOpenDynaset,
			NULL,dbReadOnly);

	if(ds.IsOpen() && !ds.IsBOF())
	{




    ds.MoveFirst();
    
    
		
       
      
        
	while(!ds.IsEOF())		
	{ 
	    CString nmstring(ds.m_EMPLOYEE_N);
	    nmstring += " ,";
	    nmstring += ds.m_FRNM1;     	  				
  		m_LIST1.InsertString( cnt, nmstring);
  		m_LIST1.SetItemDataPtr(cnt, new Stringlong(ds.m_IDfrn,ds. m_ContractNo)); 		
  		cnt++;
		
  		ds.MoveNext();
  	  
  	}// end if !ds.IsEOF() 			
						
}//end if open

ds.Close();


// load LIST2 with Bank1 Bank2 etc

cnt=0;

if(m_existptr)
{

POSITION pos = m_existptr->GetHeadPosition();


while(pos)
{

CContract* ptr =  (CContract*) m_existptr->GetAt(pos);

m_LIST2.InsertString(cnt,ptr->Getname());
m_LIST2.SetItemDataPtr(cnt,(CContract*)  ptr);


m_existptr->GetNext(pos);
cnt++;

}

}// end if m_existptr	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubBankdlg::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	
	CWnd* button = GetDlgItem(IDC_BUTTON1);
	button->EnableWindow((m_LIST2.GetCurSel()!=LB_ERR) && (m_LIST1.GetCurSel()!=LB_ERR));
	

}	


void CSubBankdlg::Cleanup(void)
{

// substitutes  new list of names for existing ones


// first empty list




TRY{
	m_existptr->RemoveAll();


	int cnt(0);

	

	cnt = ((m_LIST1.GetCount())-1);
	if(cnt!= LB_ERR)
		{
			while(cnt)
			{

			delete  m_LIST1.GetItemDataPtr(cnt);
			cnt--;

			}
		}
		

}

CATCH(CUserException, d)
	{
	
	  AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION);
	  CDialog::OnCancel();
	
	}
AND_CATCH(CDaoException, e)
	{


	AfxMessageBox((e->m_pErrorInfo)->m_strDescription,MB_OK|MB_ICONEXCLAMATION,0);

	  CDialog::OnCancel();



	}
	        
		 	    
		
	END_CATCH
	
	{
	
	
	
	
	}


} 

 

void CSubBankdlg::OnButton1() 
{
	// TODO: Add your control notification handler code here

	


	TRY{


	int index(LB_ERR);
	CString txt, txt2;
	CListBox* pLB1 = (CListBox*) GetDlgItem(IDC_LIST1);
	CListBox* pLB2 = (CListBox*) GetDlgItem(IDC_LIST2);
	
	 


	index = pLB2->GetCurSel();

	pLB2->GetText(index,txt);

	
	

	

	pLB1->GetText(pLB1->GetCurSel(),txt2);

	txt = (txt + _T(" -> ") + txt2);

	CListBox* pLB3 = (CListBox*) GetDlgItem(IDC_LIST3);

	pLB3->AddString(txt);
	


	//Fill map 
	 
	//CContract* bankptr = (CContract*) pLB2->GetItemDataPtr(index);
	
	//CStringlong contractno((CStringlong*) pLB1->GetItemDataPtr(pLB1->GetCurSel()));


	if(!pLB1->GetItemDataPtr(pLB1->GetCurSel()) || !pLB2->GetItemDataPtr(index)){AfxThrowUserException();}


	m_map.SetAt(pLB1->GetItemDataPtr(pLB1->GetCurSel()),pLB2->GetItemDataPtr(index)); 
	pLB2->DeleteString(index);


	CWnd* button = GetDlgItem(IDC_BUTTON1);
	button->EnableWindow(FALSE);
	button = GetDlgItem(IDC_BUTTON3);
	button->EnableWindow(TRUE);
	EnableOK();

	}//end TRY


	CATCH(CUserException, e)
	{
	
	  if(AfxMessageBox(IDS_PGERR,MB_RETRYCANCEL,0)==IDCANCEL)
	 	 			{ CDialog::OnCancel();} 
	
	}
	        
		 	    
		
	END_CATCH
	
	{
	
	
	
	
	}


}



void CSubBankdlg::OnSelchangeList3() 
{
	// TODO: Add your control notification handler code here

	CWnd* button = GetDlgItem(IDC_BUTTON3);
	button->EnableWindow(TRUE);
	button = GetDlgItem(IDC_BUTTON1);
	button->EnableWindow(FALSE);
}

void CSubBankdlg::OnButton3() 
{
	// TODO: Add your control notification handler code here

	
	CListBox* pLB3 = (CListBox*) GetDlgItem(IDC_LIST3);

	m_map.RemoveAll();
	pLB3->ResetContent();
	FillExist();
	//update OK button
	EnableOK();
	
	
}

void CSubBankdlg::FillExist(void)
{

// fill LIST2

int cnt(0);

m_LIST2.ResetContent();

if(m_existptr)
{

POSITION pos = m_existptr->GetHeadPosition();


while(pos)
{

CContract* ptr =  (CContract*) m_existptr->GetAt(pos);

m_LIST2.InsertString(cnt,ptr->Getname());
m_LIST2.SetItemDataPtr(cnt,(CContract*)  ptr);


m_existptr->GetNext(pos);
cnt++;

}

}//end if m_existptr	

m_reset.EnableWindow(FALSE);
UpdateData(TRUE);

}

void CSubBankdlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	WinHelp(0x18021, HELP_CONTEXT);
	
}

void CSubBankdlg::EnableOK()
{

try
	{

	CWnd* pwnd = GetDlgItem(IDOK);
	if(!pwnd){AfxThrowUserException();}
	pwnd->EnableWindow(m_map.GetCount()); 


	}
catch(CUserException* e)
	{

	e->Delete();

	}

}
