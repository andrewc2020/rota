// estabdlg.cpp : implementation file
//

#include "stdafx.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include <afxdao.h>
#include "estabrec.h"
#include "resource.h"
#include "estabdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEstabdlg dialog


CEstabdlg::CEstabdlg(CDaoDatabase& db, CWnd* pParent /*=NULL*/)
	: CDialog(CEstabdlg::IDD, pParent), m_db(&db),m_estabID(""),m_estabstring(""),m_allin(FALSE)
{
	//{{AFX_DATA_INIT(CEstabdlg)
	//}}AFX_DATA_INIT
}

CEstabdlg::~CEstabdlg()
{

#ifdef _DEBUG
 afxDump << "m_estabID =" << m_estabID ;
 
#endif

}


void CEstabdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEstabdlg)
	DDX_Control(pDX, IDC_LIST1, m_LIST1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEstabdlg, CDialog)
	//{{AFX_MSG_MAP(CEstabdlg)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEstabdlg message handlers

BOOL CEstabdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	int cnt(0); 
	Estabrec ds(m_db);

	if(m_allin==TRUE){ m_LIST1.InsertString( cnt, _T("All")); 
	
	
	m_LIST1.SetItemDataPtr( cnt, ( CString*) new CString(_T("All")));		          
	
	cnt++; 
	
	
	}

		 
	ds.Open(dbOpenSnapshot,
			NULL,dbReadOnly);

	if(ds.IsOpen())
	{
    ds.MoveFirst();
    
    CString estabstr;    
      
        
	while(!ds.IsEOF())		
	{ 
	         	  				
  		m_LIST1.InsertString( cnt, ds.m_Establishment);
  		m_LIST1.SetItemDataPtr( cnt, ( CString*) new CString(ds.m_Estab));		          
  		if(!ds.m_Estab.CompareNoCase((m_db->m_pWorkspace)->GetUserName()))
			{


			 estabstr=ds.m_Establishment;

			}
  
 	 	cnt++;
  		ds.MoveNext();
  
  
  
  	}// end if !ds.IsEOF() 	
if(!estabstr.IsEmpty())
	{	
	m_LIST1.SelectString(0,estabstr);
	}
else
	{

	m_LIST1.SetCurSel(0);


	}
						
}//end if open



ds.Close();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEstabdlg::OnOK() 
{
	// TODO: Add extra validation here

	 
m_estabID = *((CString*) m_LIST1.GetItemDataPtr(m_LIST1.GetCurSel()));
m_LIST1.GetText(m_LIST1.GetCurSel(),m_estabstring);
Cleanup();
	
CDialog::OnOK();
}

void CEstabdlg::OnCancel() 
{
	// TODO: Add extra cleanup here

Cleanup();
	
	CDialog::OnCancel();


}


void CEstabdlg::Cleanup()
{

int cnt(m_LIST1.GetCount());

if(cnt==LB_ERR)
{
cnt=0;
}

while(cnt)
{

delete m_LIST1.GetItemDataPtr(cnt -1);

cnt--;

}


m_LIST1.ResetContent();


}


void CEstabdlg::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here

	CWnd* pwnd = GetDlgItem(IDOK);
	pwnd->EnableWindow(TRUE);

	
}

void CEstabdlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	WinHelp( 0x18033, HELP_CONTEXT);


	
}
