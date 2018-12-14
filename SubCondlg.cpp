// SubCondlg.cpp : implementation file
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

#include "SubCondlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubCondlg dialog


CSubCondlg::CSubCondlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubCondlg::IDD, pParent)
{
	
}

CSubCondlg::CSubCondlg(CDaoDatabase & db, CObList * original, CWnd * pParent)
		: CDialog(CSubCondlg::IDD, pParent), m_db(&db),m_existptr(original),m_endrota()
{
	//{{AFX_DATA_INIT(CSubCondlg)
	m_LIST3 = _T("");
	//}}AFX_DATA_INIT

}



void CSubCondlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubCondlg)
	DDX_Control(pDX, IDC_LIST2, m_LIST2);
	DDX_Control(pDX, IDC_LIST1, m_LIST1);
	DDX_Control(pDX, IDC_BUTTON3, m_reset);
	DDX_LBString(pDX, IDC_LIST3, m_LIST3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubCondlg, CDialog)
	//{{AFX_MSG_MAP(CSubCondlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_LBN_SELCHANGE(IDC_LIST3, OnSelchangeList3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubCondlg message handlers

void CSubCondlg::OnButton1() 
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

void CSubCondlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
CListBox* pLB3 = (CListBox*) GetDlgItem(IDC_LIST3);

	m_map.RemoveAll();
	pLB3->ResetContent();
	FillExist();
	//update OK button
	EnableOK();
	
}

void CSubCondlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	WinHelp(0x1801D, HELP_CONTEXT);

}

void CSubCondlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	Cleanup();
	AfxMessageBox(IDS_NO_SUB_CON,MB_OK|MB_ICONEXCLAMATION);
	
	CDialog::OnCancel();

}

void CSubCondlg::OnOK() 
{
	// TODO: Add extra validation here
	
	Cleanup();

	
	CDialog::OnOK();

}

BOOL CSubCondlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// load LIST1 with new staff

	
	int cnt(0); 
	CConset ds(m_db);

   CString sql;
   

	sql ="PARAMETERS [?] TEXT; "; 
   sql += "SELECT FRNM1, EMPLOYEE_N, Package, Hrs, Estabfrn, Budgetline,";
   sql += " staffqryparam.[Pers Number], Startdate," ;
   sql += " IIf(Not IsDate([Termdate]),#";
   sql += m_endrota.Format("%m/%d/%Y");
   sql += "#,[Termdate]) AS Termcalc " ;
   sql += "    FROM staffqryparamNoContractTemp";
   sql += " WHERE Estabfrn= [?] ";


   

   
	ds.m_estabParam = AfxGetApp()->GetProfileString(_T("Database"),_T("EstabID"),_T(""));
	ds.m_endrotaParam = m_endrota;

	ds.m_strSort = "EMPLOYEE_N ASC";
			 
	ds.Open(dbOpenDynaset,
			sql,dbReadOnly);

	if(ds.IsOpen() && !ds.IsBOF())
	{




    ds.MoveFirst();
    
    	
       
      
        
	while(!ds.IsEOF())		
	{ 
	    CString nmstring(ds.m_EMPLOYEE_N);
	    nmstring += " ,";
	    nmstring += ds.m_FRNM1;
		
		CTime startdate(ds.m_Startdate.GetYear(),ds.m_Startdate.GetMonth(),ds.m_Startdate.GetDay(),ds.m_Startdate.GetHour(),ds.m_Startdate.GetMinute(),ds.m_Startdate.GetSecond());
		CTime termdate(ds.m_Termdate.GetYear(),ds.m_Termdate.GetMonth(),ds.m_Termdate.GetDay(),ds.m_Termdate.GetHour(),ds.m_Termdate.GetMinute(),ds.m_Termdate.GetSecond());
		CTime basedate(m_endrota - CTimeSpan(364,0,0,0));

		if(termdate >basedate)
			{
  			m_LIST1.InsertString( cnt, nmstring);
  			m_LIST1.SetItemDataPtr(cnt, new Stringlong(ds.m_IDfrn,ds. m_ContractNo)); 		
  			cnt++;
			}
		
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

void CSubCondlg::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	CListBox* pLB = (CListBox*) GetDlgItem(IDC_LIST3);
	CWnd* button = GetDlgItem(IDC_BUTTON1);
	button->EnableWindow((m_LIST2.GetCurSel()!=LB_ERR) && (m_LIST1.GetCurSel()!=LB_ERR) && pLB->GetCount()< m_LIST1.GetCount());
	
	
}

void CSubCondlg::OnSelchangeList3() 
{
	// TODO: Add your control notification handler code here
	CWnd* button = GetDlgItem(IDC_BUTTON3);
	button->EnableWindow(TRUE);
	button = GetDlgItem(IDC_BUTTON1);
	button->EnableWindow(FALSE);

}

void CSubCondlg::Cleanup()
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

void CSubCondlg::FillExist()
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

void CSubCondlg::EnableOK()
{

try
	{

	UpdateData(TRUE);
	CListBox* lb = (CListBox*) GetDlgItem(IDC_LIST2);
	CWnd* pwnd = GetDlgItem(IDOK);
	if(!pwnd || !lb){AfxThrowUserException();}
	pwnd->EnableWindow(m_map.GetCount() && (lb->GetCount()==0)); 


	}
catch(CUserException* e)
	{
	AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);
	e->Delete();

	}


}


