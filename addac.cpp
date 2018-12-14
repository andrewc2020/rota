// addac.cpp : implementation file
//

#include "stdafx.h"
#include <afxdb.h>
//#include "centool8.h"
#include "CONSTANT.H"
#include "absolute.h"
#include "span.h"
#include "period.h"
#include "timelist.h"
#include "assert.h"
#include "addac.h" 
#include <stdio.h>




#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddac dialog

CAddac::CAddac(CWnd* pParent /*=NULL*/)
	:CDialog(CAddac::IDD, pParent),nMin(0),nMax(364),from(),from_position(0),to_position(364),whichtitle(Add),IsEstablishment(FALSE),m_titlestring("Edit an Account")
{
    m_code = "";
	m_name = "";
	

}

CAddac::CAddac(const CTime basedate,CWnd* pParent /*=NULL*/)
	: CDialog(CAddac::IDD, pParent),nMin(0),nMax(364),from(basedate),from_position(0),to_position(364),whichtitle(Add),m_otherptr(NULL),IsEstablishment(FALSE),m_titlestring("Edit an Account")
	
{
	//{{AFX_DATA_INIT(CAddac)
	m_name = "";
	m_code = "";
	m_ID = 0;
	m_package = _T("");
	m_conhrs = 0.0;
	//}}AFX_DATA_INIT
}

void CAddac::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddac)
	DDX_Control(pDX, IDC_LIST1, m_pLB);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDV_MaxChars(pDX, m_name, 20);
	DDX_Text(pDX, IDC_CODE, m_code);
	DDV_MaxChars(pDX, m_code, 10);
	DDX_Text(pDX, IDC_ID, m_ID);
	DDX_Text(pDX, IDC_TC, m_package);
	DDX_Text(pDX, IDC_HRS, m_conhrs);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAddac, CDialog)
	//{{AFX_MSG_MAP(CAddac)
	ON_WM_HSCROLL()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAddac message handlers

BOOL CAddac::OnInitDialog()
{
	
	
	// TODO: Add extra initialization here 
	
	
	
	CWnd::SetWindowText(m_titlestring);

	
	CScrollBar* pSB= (CScrollBar*) GetDlgItem(IDC_FSCROLL);
	pSB->SetScrollRange(nMin,nMax);
	pSB->SetScrollPos(from_position);
	
	CTimeSpan span_from((from_position),0,0,0);
	CTime temp_date(from);
	temp_date += span_from;

	((GetDlgItem(IDC_HRS))->EnableWindow(whichtitle==Add));
	((GetDlgItem(IDC_TC))->EnableWindow(whichtitle==Add));

// for debugging only	
//	CWnd::SetDlgItemInt(IDC_FROM, from_position, FALSE);
	CWnd::SetDlgItemText(IDC_FROM, temp_date.Format("%B %d,%Y"));
	
	temp_date=from;
	
	pSB= (CScrollBar*) GetDlgItem(IDC_TOSCROLL);
	pSB->SetScrollRange(nMin,nMax);
	pSB->SetScrollPos(to_position); 
	
	
	CTimeSpan span_to( to_position,0,0,0);
	
	temp_date += span_to; 
//for debugging int display	
//	CWnd::SetDlgItemInt(IDC_TO, to_position, FALSE);
	
	CWnd::SetDlgItemText(IDC_TO, temp_date.Format("%B %d,%Y"));

	//remember from and to positions for later checking to warn of changes
	remember_from_pos = from_position;
	remember_to_pos	 = to_position;

Fill_listbox(m_otherptr);
	
	return CDialog::OnInitDialog();  // return TRUE  unless you set the focus to a control
}

void CAddac::OnOK()
{
	// TODO: Add extra validation here 
	UINT STRING_ID=0;
	
	CScrollBar* pSB= (CScrollBar*) GetDlgItem(IDC_FSCROLL);
	from_position=pSB->GetScrollPos();
	
	pSB= (CScrollBar*) GetDlgItem(IDC_TOSCROLL);
	to_position = pSB->GetScrollPos();
	
	
	
	TRY  // diagnostics
	{
	
	
	 
	/*char str[20];
	char str2[10];*/
		CString str;
	CString str2;
	
	
	
	if(!GetDlgItemText(IDC_EDIT1,str) )
	{ STRING_ID=IDS_TXT_ERR; AfxThrowUserException( );}
	
	if(!GetDlgItemText(IDC_CODE,str2))
	{ STRING_ID=IDS_TXT_CDERR; AfxThrowUserException( );}
		
	if(from_position > to_position)
	{ STRING_ID=IDS_SPAN_ERR; AfxThrowUserException( );}

	// warn on term change
	if( !IsEstablishment)
		{
			if((remember_from_pos==from_position) && (remember_to_pos==to_position) )
			{
			}
			else
			{

		
			if(AfxMessageBox(IDS_WARN_ON_TERM_CHANGE,MB_OKCANCEL,(UINT)0)!=IDOK)
			{

			 STRING_ID=IDS_CONFIRM_TERM;
			 AfxThrowUserException();


			}

		}// end if not establishment

		}
	
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

void CAddac::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	
	UINT cntrl=0;
	cntrl=pScrollBar->GetDlgCtrlID();
	assert(cntrl);
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
}





BOOL CAddac::Fill_listbox(CObList* listfiller)
{

	/* Fill list box */ 
	
	
	CListBox* pLB=(CListBox*) GetDlgItem(IDC_LIST1);
	
	
	
    	if(listfiller)
		{
	    			    
    	POSITION pos=listfiller->GetHeadPosition();
   		int cnt=0;
   		
   		CString txt("");
   		   		
    	while(pos)
    		{
    		CTimelist* ptr=(CTimelist*) listfiller->GetAt(pos);
            pLB->InsertString(cnt,ptr->Getname());
						
			listfiller->GetNext(pos);
			cnt++;}
		
		
	    return TRUE;
		}
		
        else {return FALSE;}


}


void CAddac::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here 
	CWnd* pWnd=GetDlgItem(IDC_EDIT1);
    pWnd->SetFocus();

	/*when editing a category, disable or make invisible most of box*/
	
	pWnd=GetDlgItem(IDC_FSCROLL);
	pWnd->ShowWindow(IsEstablishment==FALSE);
	pWnd=GetDlgItem(IDC_TOSCROLL);
	pWnd->ShowWindow(IsEstablishment==FALSE);
	
	
	
	if(IsEstablishment==TRUE)
	{

	pWnd=GetDlgItem(IDC_TC);
	pWnd->EnableWindow(TRUE);
	pWnd=GetDlgItem(IDC_HRS);
	pWnd->EnableWindow(TRUE);


	}
	

}

void CAddac::OnHelp() 
{
	// TODO: Add your control notification handler code here
	WinHelp(0x18005, HELP_CONTEXT);
}
