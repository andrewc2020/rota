// crprop.cpp : implementation file
//

#include "stdafx.h"
//#include "centool8.h"
#include "CONSTANT.H"
#include "crprop.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCrprop dialog


CCrprop::CCrprop(CWnd* pParent /*=NULL*/)
	: CDialog(CCrprop::IDD, pParent),nMin(0),nMax(0),from(),from_position(0),to_position(0)
{
	//{{AFX_DATA_INIT(CCrprop)
	m_mon = FALSE;
	m_tue = FALSE;
	m_wed = FALSE;
	m_thu = FALSE;
	m_fri = FALSE;
	m_sat = FALSE;
	m_sun = FALSE;
	m_starthrs = 0;
	m_startmins = 0;
	m_durhrs = 0;
	m_durmins = 0;
	m_total = _T("");
	m_perwk = _T("");
	//}}AFX_DATA_INIT
}


void CCrprop::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCrprop)
	DDX_Check(pDX, IDC_MON, m_mon);
	DDX_Check(pDX, IDC_TUE, m_tue);
	DDX_Check(pDX, IDC_WED, m_wed);
	DDX_Check(pDX, IDC_THU, m_thu);
	DDX_Check(pDX, IDC_FRI, m_fri);
	DDX_Check(pDX, IDC_SAT, m_sat);
	DDX_Check(pDX, IDC_SUN, m_sun);
	DDX_Text(pDX, IDC_EDIT1, m_starthrs);
	DDV_MinMaxInt(pDX, m_starthrs, 0, 23);
	DDX_Text(pDX, IDC_EDIT2, m_startmins);
	DDV_MinMaxInt(pDX, m_startmins, 0, 59);
	DDX_Text(pDX, IDC_EDIT3, m_durhrs);
	DDV_MinMaxInt(pDX, m_durhrs, 0, 23);
	DDX_Text(pDX, IDC_EDIT4, m_durmins);
	DDV_MinMaxInt(pDX, m_durmins, 0, 59);
	DDX_Text(pDX, IDC_EDIT5, m_total);
	DDX_Text(pDX, IDC_EDIT6, m_perwk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCrprop, CDialog)
	//{{AFX_MSG_MAP(CCrprop)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCrprop message handlers

BOOL CCrprop::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CScrollBar* pSB= (CScrollBar*) GetDlgItem(IDC_FSCROLL);
	pSB->SetScrollRange(nMin,nMax);
	pSB->SetScrollPos(from_position);
	
	CTimeSpan span_from((from_position),0,0,0);
	CTime temp_date(from);
	
	temp_date += span_from;
// for debugging only	
//	CWnd::SetDlgItemInt(IDC_FROM, from_position, FALSE);
	CWnd::SetDlgItemText(IDC_FROM, temp_date.Format("%B %d,%Y"));
	
	temp_date=from;
//	getbasedate(temp_date, m_fixed);

	pSB= (CScrollBar*) GetDlgItem(IDC_TOSCROLL);
	pSB->SetScrollRange(nMin,nMax);
	pSB->SetScrollPos(to_position); 
	
	
	CTimeSpan span_to( to_position,0,0,0);
	
	temp_date += span_to; 
//for debugging int display	
//	CWnd::SetDlgItemInt(IDC_TO, to_position, FALSE);
	
	CWnd::SetDlgItemText(IDC_TO, temp_date.Format("%B %d,%Y"));
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCrprop::OnHelp() 
{
	// TODO: Add your control notification handler code here

	WinHelp(0x1802E, HELP_CONTEXT);
}

void CCrprop::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	UINT STRING_ID(0);

	TRY{

	UINT cntrl=0;
	cntrl=pScrollBar->GetDlgCtrlID();

	if(!cntrl)
   	{ AfxThrowUserException();} 
	
	CTime temp_date=from;
	

	switch(cntrl)
	{
	
	case IDC_FSCROLL:{ cntrl=IDC_FROM;}
	break;
	case IDC_TOSCROLL:{ cntrl=IDC_TO;}
	break;
	default: { AfxMessageBox(IDS_PGERR,MB_OK,MB_ICONSTOP);}
	 
	}
	
	int nPosition;
	nPosition= pScrollBar->GetScrollPos();
	
	switch(nSBCode)
	{
	case SB_THUMBPOSITION:
	{
	pScrollBar->GetScrollRange(&nMin, &nMax);
	pScrollBar->SetScrollPos(nPos);
	CTimeSpan time2add(nPos,0,0,0);
	
	temp_date+=time2add;
// for debugging integer display 
//	CWnd::SetDlgItemInt(cntrl, nPos, FALSE);
	CWnd::SetDlgItemText(cntrl,temp_date.Format("%B %d,%Y"));
	}
	
	break;
	
	case SB_LINEUP: // left arrow button
	{
	pScrollBar->GetScrollRange(&nMin, &nMax);
	
	if((nPosition-1) > nMin){nPosition-=1;}
	else { nPosition=nMin ;}
	
	pScrollBar->SetScrollPos(nPosition);
	CTimeSpan nNewSpan(nPosition,0,0,0);
	temp_date+=nNewSpan;
	CWnd::SetDlgItemText(cntrl, temp_date.Format("%B %d,%Y"));
 //for debugging integer display 
//	CWnd::SetDlgItemInt(cntrl, nPosition, FALSE);
	}
	break;
	
	case SB_LINEDOWN://right arrow button
	{
	pScrollBar->GetScrollRange(&nMin, &nMax);
	
	if((nPosition+1) < nMax){nPosition+=1;}
	else { nPosition=nMax ;}
	pScrollBar->SetScrollPos(nPosition);	
	CTimeSpan nNewSpan(nPosition,0,0,0);
	temp_date+=nNewSpan;
/* for debugging integer display */
//	CWnd::SetDlgItemInt(cntrl, nPosition, FALSE);
	CWnd::SetDlgItemText(cntrl, temp_date.Format("%B %d,%Y"));
	}
	break;
	
	
	
	
	
  }
			
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);


	}//end TRY

	CATCH(CUserException, e)
	{
	
	  if(AfxMessageBox(STRING_ID,MB_RETRYCANCEL,0)==IDCANCEL)
	 	 			{ CDialog::OnCancel();} 
	
	}
	        
		 	    
		
	END_CATCH
	
	{
	
	
	
	
	}
}

void CCrprop::OnOK() 
{
	// TODO: Add extra validation here

	UINT STRING_ID(0);

	TRY{

	CScrollBar* pSB= (CScrollBar*) GetDlgItem(IDC_FSCROLL);
	from_position=pSB->GetScrollPos();
	
	pSB= (CScrollBar*) GetDlgItem(IDC_TOSCROLL);
	to_position = pSB->GetScrollPos();

	if( from_position > to_position)
   	{ STRING_ID=IDS_SPAN_ERR;
   	  AfxThrowUserException();} 
	
	CDialog::OnOK();

	}

	CATCH(CUserException, e)
	{
	
	  if(AfxMessageBox(STRING_ID,MB_RETRYCANCEL,0)==IDCANCEL)
	 	 			{ CDialog::OnCancel();} 
	
	}
	        
		 	    
		
	END_CATCH
	
	{
	
	
	
	
	}
}
