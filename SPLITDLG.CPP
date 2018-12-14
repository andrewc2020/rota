// splitdlg.cpp : implementation file
//

#include "stdafx.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "splitdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitdlg dialog
 

CSplitdlg::CSplitdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSplitdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSplitdlg)
	m_exhrs = 0;
	m_newhrs = 0;
	m_currweeks = 0.0;
	m_earweeks = 0.0;
	m_curtot = 0.0;
	m_eartot = 0.0;
	m_eartot2 = 0.0;
	//}}AFX_DATA_INIT
}

void CSplitdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplitdlg)
	DDX_Text(pDX, IDC_EXHRS, m_exhrs);
	DDX_Text(pDX, IDC_NEWHRS, m_newhrs);
	DDX_Text(pDX, IDC_CURWK, m_currweeks);
	DDX_Text(pDX, IDC_EARWK, m_earweeks);
	DDX_Text(pDX, IDC_CURTOT, m_curtot);
	DDX_Text(pDX, IDC_EARTOT, m_eartot);
	DDX_Text(pDX, IDC_EARTOT2, m_eartot2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSplitdlg, CDialog)
	//{{AFX_MSG_MAP(CSplitdlg)
	ON_EN_UPDATE(IDC_NEWHRS, OnUpdateNewhrs)
	ON_BN_CLICKED(IDC_WEEKS, OnWeeks)
	ON_BN_CLICKED(IDC_DAYS, OnDays)
	ON_EN_UPDATE(IDC_EARWK, OnUpdateEarwk)
	ON_EN_CHANGE(IDC_NEWHRS, OnChangeNewhrs)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplitdlg message handlers

BOOL CSplitdlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	
CButton* pwnd = (CButton*) GetDlgItem(IDC_WEEKS);
pwnd->SetCheck(1);

Refresh();	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSplitdlg::OnOK()
{
	// TODO: Add extra validation here 
	
	UINT STRING_ID(0);
	
	TRY  // diagnostics
	{
	
	CWnd::UpdateData(TRUE);
	
		
	if( m_eartot >= m_curtot)
	{
	
	STRING_ID=IDS_TOOBIG;
	AfxThrowUserException();}

	/* if weeks unit option has been selected switch to day so variables are in right 
	units for the split method */

	CButton* pbtn = (CButton*) GetDlgItem(IDC_DAYS);
	enum { weeks , days };

	if(pbtn->GetCheck()== weeks)
	{
	
	OnDays();}

	
		
	// if all clear
	
	CDialog::OnOK();  }
	
	CATCH(CUserException, e)
	{
	
	if( AfxMessageBox(STRING_ID,MB_RETRYCANCEL,0)==IDCANCEL)
	 	 			{ CDialog::OnCancel();} 
	
	}
	        
		 	    
		
	END_CATCH
	
	{
	
	
	
	
	}
	
	
}


void CSplitdlg::OnChangeNewhrs() 

{


	

}



void CSplitdlg::OnWeeks() 
{
	// TODO: Add your control notification handler code here

  UpdateData(TRUE);

	/* i.e return to weeks */

	m_exhrs = m_exhrs * 5;
	m_currweeks = m_currweeks /5;
    
	

	m_newhrs = m_newhrs * 5;
	m_earweeks = m_earweeks /5;
	

		

	Refresh();

	CWnd* pwnd = GetDlgItem(IDC_RATE);
	pwnd->SetWindowText(_T("Hrs per Week"));

	pwnd = GetDlgItem(IDC_MULT);
	pwnd->SetWindowText(_T("Weeks"));

 UpdateData(FALSE);  

}

void CSplitdlg::OnDays() 
{
	// TODO: Add your control notification handler code here

 /* i.e switch to days */

 UpdateData(TRUE);

	m_exhrs = m_exhrs / 5;
	m_currweeks = m_currweeks * 5;
    

	m_newhrs = m_newhrs / 5;
	m_earweeks = m_earweeks * 5;

	

	Refresh();

	


	CWnd* pwnd = GetDlgItem(IDC_RATE);
	pwnd->SetWindowText(_T("Hrs per Day"));

	pwnd = GetDlgItem(IDC_MULT);
	pwnd->SetWindowText(_T("Working Days"));

UpdateData(FALSE);
	
}

void CSplitdlg::OnUpdateEarwk() 
{
	// TODO: Add your control notification handler code here


	UINT message(0);

	TRY{

	//UpdateData(TRUE);

	//Refresh();

	OnButton2();

	//if(m_eartot > m_curtot){
	
	// m_earweeks = m_currweeks;
	// m_eartot = m_curtot;
	// message = IDS_NOCANDO2;
	 
	// }

	 

	UpdateData(FALSE);

	if(message){ AfxThrowUserException(); }

	}//end of TRY

  CATCH(CUserException, e)
  {

   if( AfxMessageBox( message ,MB_RETRYCANCEL,0)==IDCANCEL)
	 	 			{ CDialog::OnCancel();} 


  }


  END_CATCH
  {



  }
}


void CSplitdlg::Refresh(void)
{
   

	m_eartot = m_newhrs * m_earweeks;
	m_eartot2 = m_curtot - m_eartot;


	CWnd* pwnd;
	pwnd = GetDlgItem(IDOK);
	pwnd->EnableWindow(0 < m_eartot && m_eartot < m_curtot);

}



void CSplitdlg::OnUpdateNewhrs() 
{
	// TODO: Add your control notification handler code here
  CWnd* pwnd;
	pwnd = GetDlgItem(IDC_BUTTON2);
	pwnd->EnableWindow(TRUE);

}

void CSplitdlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	UINT message(0);

	TRY{


	
	
	
	UpdateData(TRUE);
	Refresh();

	

	if(m_eartot > m_curtot){

	 m_earweeks = m_currweeks;
	 m_eartot = m_curtot;
	 m_newhrs = m_exhrs;			
	 m_eartot = m_curtot;

	 message = IDS_NOCANDO2;
	 }
	
	 
	UpdateData(FALSE);
	

  	if (message){ AfxThrowUserException();}

	CWnd* pwnd;
	pwnd = GetDlgItem(IDC_BUTTON2);
	pwnd->EnableWindow(FALSE); 					

  }//end of TRY

  CATCH(CUserException, e)
  {

   if( AfxMessageBox( message ,MB_RETRYCANCEL,0)==IDCANCEL)
	 	 			{ CDialog::OnCancel();} 
   else { OnButton2();}

  }


  END_CATCH
  {



  }	
}

void CSplitdlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	WinHelp( 0x1008D, HELP_CONTEXT);
}
