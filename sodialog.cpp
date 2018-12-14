// sodialog.cpp : implementation file
//


#include "stdafx.h"
#include <afxdb.h>
#include "resource.h"
#include "CONSTANT.H"
//#include "centool8.h"
#include "absolute.h"
#include "span.h"
#include "shift.h"
#include "period.h"
#include "timelist.h"
#include "contract.h"
#include "category.h" 
#include "prdlst.h"
#include "regularp.h"
#include "debit.h"
#include "sodialog.h"
#include "assert.h"
#include "bitvec.h"
#include <math.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSOdialog dialog
CSOdialog::CSOdialog(const CTime basedate,CWnd* pParent /*=NULL*/)
	: CDialog(CSOdialog::IDD, pParent) ,nMin(0),nMax(0),from(basedate),from_position(0),to_position(0),whichtitle(Add),m_parent(NULL),weekstart(0)
	,m_original(NULL),m_dayarray(NULL),m_day(monday),m_bitvector(NULL),m_drpvector(NULL)
{
	//{{AFX_DATA_INIT(CSOdialog)
	m_fixed = FALSE;
	m_starthrs = 0;
	m_startmins = 0;
	m_durhrs = 0;
	m_durmins = 0;
	m_check1 = FALSE;
	m_check2 = FALSE;
	m_check3 = FALSE;
	m_check4 = FALSE;
	//}}AFX_DATA_INIT
    m_freq= FALSE;
    
    m_dayarray = new CObArray;
	m_dayarray->SetSize(7,0);
	m_bitvector = new CBitvector();
	m_drpvector = new CBitvector();
}


CSOdialog::CSOdialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSOdialog::IDD, pParent) ,nMin(0),nMax(0),from(),from_position(0),to_position(0),whichtitle(Add),m_parent(NULL),weekstart(0)
	,m_original(NULL),m_dayarray(NULL),m_day(monday),m_bitvector(NULL),m_drpvector(NULL)

	{
	
	m_starthrs = 0;
	m_startmins = 0;
	m_durhrs = 0;
	m_durmins = 0;

	m_check1 = FALSE;
	m_check2 = FALSE;
	m_check3 = FALSE;
	m_check4 = FALSE;

	m_freq = FALSE;
	m_fixed=FALSE;

	m_dayarray = new CObArray;
	m_dayarray->SetSize(7,0);

	m_bitvector = new CBitvector();
	m_drpvector = new CBitvector();
}

CSOdialog::~CSOdialog()

{

CSpan* ptr=NULL;

 for(int cnt(0);cnt<=6;cnt++)
 {

 ptr= (CSpan*) m_dayarray->GetAt(cnt);

 
 delete ptr;

 }


delete m_dayarray;
delete m_bitvector;
delete m_drpvector;
CDialog::~CDialog();


}



void CSOdialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSOdialog)
	DDX_Control(pDX, IDC_CODEBOX, m_codebox);
	DDX_Check(pDX, IDC_FIXED, m_fixed);
	DDX_Text(pDX, IDC_STHRS, m_starthrs);
	DDV_MinMaxInt(pDX, m_starthrs, 0, 23);
	DDX_Text(pDX, IDC_STMINS, m_startmins);
	DDV_MinMaxInt(pDX, m_startmins, 0, 59);
	DDX_Text(pDX, IDC_DURHRS, m_durhrs);
	DDV_MinMaxInt(pDX, m_durhrs, 0, 24);
	DDX_Text(pDX, IDC_DURMNS, m_durmins);
	DDV_MinMaxInt(pDX, m_durmins, 0, 59);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	DDX_Check(pDX, IDC_CHECK3, m_check3);
	DDX_Check(pDX, IDC_CHECK4, m_check4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSOdialog, CDialog)
	//{{AFX_MSG_MAP(CSOdialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_ONEOFF, OnOneoff)
	ON_BN_CLICKED(IDC_WEEKLY, OnWeekly)
	ON_WM_SHOWWINDOW()
	ON_CBN_EDITCHANGE(IDC_CODEBOX, OnEditchangeCodebox)
	ON_CBN_EDITUPDATE(IDC_CODEBOX, OnEditupdateCodebox)
	ON_CBN_SELCHANGE(IDC_CODEBOX, OnSelchangeCodebox)
	ON_BN_CLICKED(IDC_ADCODEBTN, OnAdcodebtn)
	ON_BN_CLICKED(IDC_DELCODE, OnDelcode)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	ON_EN_SETFOCUS(IDC_MON, OnSetfocusMon)
	ON_EN_SETFOCUS(IDC_TUE, OnSetfocusTue)
	ON_EN_SETFOCUS(IDC_WED, OnSetfocusWed)
	ON_EN_SETFOCUS(IDC_THU, OnSetfocusThu)
	ON_EN_SETFOCUS(IDC_FRI, OnSetfocusFri)
	ON_EN_SETFOCUS(IDC_SAT, OnSetfocusSat)
	ON_EN_SETFOCUS(IDC_SUN, OnSetfocusSun)
	ON_BN_CLICKED(IDC_NONSTAN, OnNonstan)
	ON_EN_UPDATE(IDC_STHRS, OnUpdateSthrs)
	ON_EN_UPDATE(IDC_STMINS, OnUpdateStmins)
	ON_EN_UPDATE(IDC_DURHRS, OnUpdateDurhrs)
	ON_EN_UPDATE(IDC_DURMNS, OnUpdateDurmns)
	ON_EN_UPDATE(IDC_MON, OnUpdateMon)
	ON_BN_CLICKED(IDC_DRP, OnDrp)
	ON_BN_CLICKED(IDC_WEEKLY, OnWeekly)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSOdialog message handlers

void CSOdialog::OnOK()
{
	// TODO: Add extra validation here 
	
	 UINT STRING_ID(0); // default message for buried exception
	
	
	
	TRY  // diagnostics
	{ 
	
	if(!IsValidInstruction())
		{

		STRING_ID = IDS_NODUR;

		AfxThrowUserException();


		}
	

	 
	 
				  
    if(m_freq){
	
	CScrollBar* pSB= (CScrollBar*) GetDlgItem(IDC_FSCROLL);
	from_position=pSB->GetScrollPos();
	
	pSB= (CScrollBar*) GetDlgItem(IDC_TOSCROLL);
	to_position = pSB->GetScrollPos();}

	/* check for less than a day error */
	
   	if( from_position > to_position)
   	{ STRING_ID=IDS_SPAN_ERR;
   	  AfxThrowUserException();}
	
	
   	  
   	/* check for double booking  */

	

	UpdateData(TRUE);

	if(m_freq)
	{

	m_bitvector->set(0,m_check1);
	m_bitvector->set(1,m_check2);
	m_bitvector->set(2,m_check3);
	m_bitvector->set(3,m_check4);

	}
	else

	{

	SetCheckboxes();

	

	
	}


	/* check for no checked weeks error */


	if(IsClearWeeks())
		{
		STRING_ID=IDS_NO_CLEAR_WEEKS;
		AfxThrowUserException();

		}


	/*

  TO DO

	if(!IsWithinContractualPeriod())
		{

		STRING_ID = IDS_EXTRA_CONTRACT;

		AfxThrowUserException();


		}
	*/
   	  
  	/* update standard shift list */ 








   		
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

BOOL CSOdialog::OnInitDialog()
{

	
	// TODO: Add extra initialization here 
	
	assert(m_parent);
	

	
	
	if(whichtitle==Edit){
	 CWnd::SetWindowText(_T("Edit an Instruction on ") + m_parent->Getname());
	 	 
	 
	 	 	 	 
	 }
	else
	
	{
	

	SetCheckboxes();
	 
	
	CWnd::SetWindowText(_T("Add an Instruction to ") + m_parent->Getname());
	
	}
		
	
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
	

	pSB= (CScrollBar*) GetDlgItem(IDC_TOSCROLL);
	pSB->SetScrollRange(nMin,nMax);
	pSB->SetScrollPos(to_position); 
	
	
	CTimeSpan span_to( to_position,0,0,0);
	
	temp_date += span_to; 
//for debugging int display	
//	CWnd::SetDlgItemInt(IDC_TO, to_position, FALSE);
	
	CWnd::SetDlgItemText(IDC_TO, temp_date.Format("%B %d,%Y"));
	
	
	
	
	/* set frequency */ 
	
	 if(!m_freq && IsWithinContractualPeriod()){ 

	 OnOneoff(); 
	 
	}    
    else
    {
    CheckRadioButton(IDC_ONEOFF,IDC_WEEKLY,IDC_WEEKLY);}   

	// initialise combo box for time codes
	CCategory* catptr = (CCategory*) m_parent->Getuncle();
	CComboBox* pcombo = (CComboBox*) GetDlgItem(IDC_CODEBOX);

	if(catptr->codelistIsActive())
	{

	CWnd* pbtn;

	if(!catptr->codelistUpdateable())
	{

	
	pbtn = (CWnd*) GetDlgItem(IDC_ADCODEBTN);
	pbtn->ShowWindow(SW_HIDE);
	pbtn->EnableWindow(FALSE);
	pbtn = (CWnd*) GetDlgItem(IDC_DELCODE);
	pbtn->ShowWindow(SW_HIDE);
	pbtn->EnableWindow(FALSE);
	pbtn = (CWnd*) GetDlgItem(IDC_STAN);
	pbtn->SetWindowText(_T("Standard Days"));

	// make DRP setter invisible

	pbtn = (CWnd*) GetDlgItem(IDC_DRP);
	for(int cnt(0);cnt<7;cnt++)
	{m_drpvector->set(cnt,FALSE);}
	pbtn->ShowWindow(SW_HIDE);
	pbtn = (CWnd*) GetDlgItem(IDC_DRPBOX);
	pbtn->ShowWindow(SW_HIDE);

	}

	else

	{

	pbtn = (CWnd*) GetDlgItem(IDC_ADCODEBTN);
	pbtn->ShowWindow(SW_SHOW);
	pbtn->EnableWindow(FALSE);
	pbtn = (CWnd*) GetDlgItem(IDC_DELCODE);
	pbtn->ShowWindow(SW_SHOW);
	pbtn->EnableWindow(FALSE);





	}

	pbtn = (CWnd*) GetDlgItem(IDC_STAN);
	pbtn->ShowWindow(SW_SHOW);
	
	pcombo->ShowWindow(SW_SHOW);
	fillcombo();
	
	
		
			
		

		
	   
		EnableCurrentWeek(IsWithinContractualPeriod());
		
	 

	
	 }

	 
	
	return CDialog::OnInitDialog();  // return TRUE  unless you set the focus to a control

}

void CSOdialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	
	UINT cntrl=0;
	cntrl=pScrollBar->GetDlgCtrlID();
	assert(cntrl);
	CTime temp_date(from);
	

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



void CSOdialog::OnOneoff()
{
	// TODO: Add your control notification handler code here
	

	// adjust the week's start if the contract begins
	// later in the week
	
	int trueweekstart(weekstart);
	if(m_parent->GetFromToPosition(::MIN)>weekstart)
		{
		from_position = m_parent->GetFromToPosition(::MIN);
		
		
		}
	else
		{
		from_position= (int) weekstart;
		
		}


	if(m_parent->GetFromToPosition(::MAX)< (weekstart + 6))
		{

		to_position = m_parent->GetFromToPosition(::MAX);
		
		
		}
	else
		{

		to_position = (int)(weekstart + 6);
		

		}

	CTimeSpan time2add(from_position,0,0,0);
	CTimeSpan weekend(to_position,0,0,0);
	CTime temp_date(from);
	
	temp_date+=time2add;


	// calculate week end which will be six days
	// on from the week start

	CTime temp_end(from);
	temp_end+=weekend;
	
	
	CWnd::SetDlgItemText(IDC_FROM,temp_date.Format("%B %d,%Y"));
	
	CWnd::SetDlgItemText(IDC_TO,temp_end.Format("%B %d,%Y")); 
	

	EnableScrollBars(FALSE);
	
	
	
	m_freq=FALSE;


	SetCheckboxes();

	EnableCheckboxes(SW_HIDE);
	
}

void CSOdialog::OnWeekly()
{
	// TODO: Add your control notification handler code here 
	m_freq=TRUE;

	EnableScrollBars(TRUE);
	
	
	CScrollBar* pSB= (CScrollBar*) GetDlgItem(IDC_FSCROLL);
    	
	OnHScroll(SB_THUMBPOSITION,pSB->GetScrollPos(), pSB);
	
	pSB= (CScrollBar*) GetDlgItem(IDC_TOSCROLL);
	
	OnHScroll(SB_THUMBPOSITION,pSB->GetScrollPos(), pSB);

	EnableCheckboxes(SW_SHOW);

}




void CSOdialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here  
	
	 if(!m_freq){CheckRadioButton(IDC_ONEOFF,IDC_WEEKLY,IDC_ONEOFF);} 

	 
	 
	m_check1 =  m_bitvector->IsSet(0);
	m_check2 =  m_bitvector->IsSet(1);
	m_check3 =  m_bitvector->IsSet(2);
	m_check4 =  m_bitvector->IsSet(3);

   	UpdateData(FALSE);
	
}





LRESULT CSOdialog::Clashes(CSpan* testspan, const weekdays dayofweek)
{ 

/* create CRegularPeriod components for test purposes */ 

BOOL does_clash(FALSE);
CTime tempdate(from);

LRESULT nResult(0);
UINT STRING_ID(0);
CRegularPeriod* test = NULL;


TRY
	{

	// first test whether new shift is a non event

	if(testspan->getduration()==::NONE)
	{ return FALSE;} 


	CObArray* dayarray = new CObArray;

	dayarray->SetSize(7,0);

	CSpan* spanptr=NULL;

	for(int cnt=0; cnt <=6; cnt++)
	{

  

	if(testspan && cnt == dayofweek ){spanptr = (CSpan*) testspan->clone();

	dayarray->SetAt(cnt , spanptr);
	
	}
	else
	{ 
	
	
	dayarray->SetAt(cnt , new CSpan(::NONE,::NONE));}

    
  	}
  
   
   long from=0;
   long to=0;
         
  
   from= from_position;
   to= to_position;
   
   // create test arrangement with day set


	



   
 

	test = new CDebitPeriod (m_bitvector,m_drpvector,dayarray,from,to,m_parent,m_fixed,tempdate); 




	CContract* ptr=( CContract*) m_parent->GetStaff(); // call the potentially
												  //double booked contract
	COLORREF colour(test->getcolour());											  
	switch(colour)
		{
		

		case ::RED:
			{
			 	

		does_clash = ptr->IsConflictWithOwn(*test, m_original);
		if(does_clash)
				{

		
				nResult = 1;
				} //end if
			} //end case RED i.e Absence object

			break;

		case ::BLUE:
			{


			does_clash = ptr->IsConflict(*test,m_original,TRUE);
			if(does_clash)
				{
				nResult=2;
				}	//end if

			}  //end case BLUE i.e Cover object
			break;
		default:
			{

			STRING_ID = IDS_PGERR;
			nResult=3;
			AfxThrowUserException();


			}
			break;

		}//end switch


	}//end try
CATCH(CUserException, e)
	{

	nResult = 3;

	
	

	}
END_CATCH

delete test;

return nResult;

}

void CSOdialog::OnEditchangeCodebox() 
{
	// TODO: Add your control notification handler code here


	
}

void CSOdialog::OnEditupdateCodebox() 
{
	// TODO: Add your control notification handler code here
	CButton* btn =(CButton*) GetDlgItem(IDC_DELCODE);
	btn->EnableWindow(FALSE);
	btn = (CButton*) GetDlgItem(IDC_ADCODEBTN);
	btn->EnableWindow(TRUE);
	
}

void CSOdialog::OnSelchangeCodebox() 
{
	// TODO: Add your control notification handler code here

	UINT STRING_ID(IDS_PGERR);

	TRY{

	

	int index = m_codebox.GetCurSel();

	if(index==LB_ERR){ AfxThrowUserException();}

	CShift* codeptr = (CShift*) m_codebox.GetItemDataPtr(index);

	if(!codeptr){ AfxThrowUserException();}


	LRESULT nResult(Clashes(codeptr, m_day)); 
	
	switch(nResult)
  		{

		case 0:
			{

			// no clash, so do nothing.

			}
			break;

		case 1:
			{

			m_codebox.SetCurSel(m_codebox.GetCount()-1);
  			
			STRING_ID = IDS_CONFLICT;
  			AfxThrowUserException();

			}// end conflict of Absence with Absence
			break;

		case 2:
			{


			STRING_ID = IDS_CLASH_ERR;
  			AfxThrowUserException();

			} // end conflict of Cover with Absence

			break;

		default:
			{

			// error!
			AfxThrowUserException();



			} //end default error case

			break;

			 


  		}//end switch
	

	CSpan* currentspan;

	if(currentspan = (CSpan*) m_dayarray->GetAt(m_day))
	{

	
		


	currentspan->ResetPeriod((CSpan*) codeptr);

	
	
	}

	else

	{


	m_dayarray->SetAt( m_day , new CSpan(codeptr->getstart(),codeptr->getduration()));
	

	}

	


	Refresh();
	
	

	CButton* btn =(CButton*) GetDlgItem(IDC_DELCODE);
	btn->EnableWindow(TRUE);
	btn = (CButton*) GetDlgItem(IDC_ADCODEBTN);
	btn->EnableWindow(FALSE);
	} // end try

	CATCH(CUserException, e){
	
	 if(AfxMessageBox(STRING_ID,MB_RETRYCANCEL,0)==IDCANCEL)
	 	 			{ CDialog::OnCancel();} else { Refresh();}
	 	 			 }

	END_CATCH{ }
}

void CSOdialog::fillcombo(void)
{

CComboBox* pcombo = (CComboBox*) GetDlgItem(IDC_CODEBOX);
	
	

	CCategory* catptr = (CCategory*) m_parent->Getuncle();
	CPeriod* ptr = m_parent->GetStaff();
	catptr->fillbox(pcombo,ptr);

	
}



void CSOdialog::OnAdcodebtn() 
{
	// TODO: Add your control notification handler code here


UpdateData(TRUE);

 
	
	UINT STRING_ID(IDS_DUPE);
	
TRY{

	CString txt;
	m_codebox.GetWindowText(txt);


	
	CCategory* catptr = (CCategory*) m_parent->Getuncle();

	// increment if a nonstandard shift	to next highest	in series

	catptr->IncrementNonstandard(txt);

	

// check new code does not exist

	int index( catptr->IsDupeCode(txt));

	if( index >=0){ 
	
	// code exists. Stop action


	m_codebox.SetEditSel(0,-1);	
	STRING_ID = IDS_DUPECODE;
	AfxThrowUserException();
	
	}

	CTimeSpan dummystar(0,m_starthrs,m_startmins,0);
	CTimeSpan dummydur(0,m_durhrs - m_starthrs ,m_durmins-m_startmins,0);
	CTimeSpan dummyfin(0,m_durhrs ,m_durmins,0);
	

	

	
	   

	if(dummystar > dummyfin)
  	{

  		
	dummydur +=::ONE_DAY; 
  	}

	

		

	if(index < 0
		 && !txt.IsEmpty() &&
		 AfxMessageBox(_T("Create a new standard shift\n")
		 				 + txt + _T(" ")
		 				 + dummystar.Format("%H:%M") + _T(" ")
		 				 + dummyfin.Format("%H:%M"),MB_OKCANCEL||MB_ICONQUESTION,0)==IDOK)
		{
	
			CObject* ptr = new CShift(dummystar,dummydur,txt);

		

			

			catptr->Addshift(ptr);  

			fillcombo();
	
			
			m_codebox.SetCurSel(catptr->IsDupeCode(txt));
			OnSelchangeCodebox();
			
			
		
	
	}// Ask user if wants to build new shift

	CWnd* pwnd;

 	pwnd= CWnd::GetDlgItem(IDOK);

		pwnd->EnableWindow(TRUE);
				   // OK button disabled by any change to start or finish time

	}//end of TRY


	CATCH(CUserException, e)
	{

	AfxMessageBox( STRING_ID ,MB_OK|MB_ICONEXCLAMATION,0);


	}

	AND_CATCH(CFileException, e)
	{



	}

	END_CATCH
	{




	}
	
}

void CSOdialog::OnDelcode() 
{
	// TODO: Add your control notification handler code here

	CCategory* catptr = (CCategory*) m_parent->Getuncle();

			
			
			int index = m_codebox.GetCurSel();
			CObject* ptr = (CObject*) m_codebox.GetItemData(index);
			if(catptr->Delshift(ptr))
			{  

			fillcombo();}
			else
			{
			AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);}
	
			

	
}



void CSOdialog::EnableCurrentWeek(const BOOL verdict)
{

CWnd* pwnd = GetDlgItem(IDC_ONEOFF);
pwnd->EnableWindow(verdict); 



}


void CSOdialog::EnableScrollBars(const BOOL verdict)
{



 CWnd* pSB = GetDlgItem(IDC_FSCROLL);
 	
 pSB->EnableWindow(verdict);

 pSB = GetDlgItem(IDC_TOSCROLL);

 pSB->EnableWindow(verdict);

}

void CSOdialog::EnableCheckboxes(const UINT mode)
{

 CWnd* pCB = NULL;
 
 pCB = 	CWnd::GetDlgItem(IDC_CHECK1);  // must do seperately because of ID

 pCB->ShowWindow(mode);
 
 for(int cnt(0);cnt<=2;cnt++)
 {
 
 pCB = 	CWnd::GetDlgItem(IDC_CHECK2 + cnt);

 pCB->ShowWindow(mode);
 
 } 

}



void CSOdialog::OnHelp() 
{
	// TODO: Add your control notification handler code here
	WinHelp(0x1800A, HELP_CONTEXT);
}

void CSOdialog::Refresh(void)
{

UINT STRING_ID(0);

	TRY{


	
	CSpan* currentspan;
	

	if(currentspan = (CSpan*) m_dayarray->GetAt(m_day))
	{
	m_starthrs = currentspan->getstart().GetHours();
	m_startmins = currentspan->getstart().GetMinutes();



	m_durhrs =  m_starthrs + currentspan->getduration().GetHours();
	if(m_durhrs > 24){ m_durhrs -= 24;}
	m_durmins = m_startmins + currentspan->getduration().GetMinutes();
	if(m_durmins == 60){ m_durhrs +=1 ; m_durmins =0;}

	
	UpdateData(FALSE);

	}

	// update combo



	CCategory* catptr = (CCategory*) m_parent->Getuncle();

	if(currentspan)
	{
	 
	 catptr->FindSpan(currentspan,m_codebox); 	
	}


	//update DRP
		CButton* pbtn;
		pbtn=(CButton*) CWnd::GetDlgItem(IDC_DRP);

	
		currentspan= (CSpan*) m_dayarray->GetAt(m_day);
		pbtn->EnableWindow(currentspan->getduration().GetTotalMinutes()>0);
		// if the shift is time off undo drp status

		if(currentspan->getduration().GetTotalMinutes()==0)
		{

		m_drpvector->set(m_day,FALSE);
		}

		pbtn->SetCheck(m_drpvector->IsSet(m_day));

		//update codewindows

	CWnd* pwnd = NULL;

	for(UINT cnt=0;cnt<= 6;cnt++)
	{	
	
	 currentspan= (CSpan*) m_dayarray->GetAt(cnt);

	 	if(currentspan)
	 	{

	 	pwnd=CWnd::GetDlgItem(IDC_MON + cnt);



		

		CString code(catptr->Getdlgcode(currentspan));



		


		if(m_drpvector->IsSet(cnt)){ 
		
			
		code += "*" ;} 

		pwnd->SetWindowText(code);


		pwnd= CWnd::GetDlgItem(IDC_LABMON + cnt);

		pwnd->EnableWindow(cnt==m_day);

		

		}

	/* Finally if the OK button has been disabled, enable it */

	CWnd* pwnd =  CWnd::GetDlgItem(IDOK);
	
	if(!pwnd->IsWindowEnabled()){pwnd->EnableWindow(TRUE);}
		

	 }

	
 

	
 }	 // end Try
	
	CATCH(CUserException, e)
	{
	
	  if(AfxMessageBox(STRING_ID,MB_RETRYCANCEL,0)==IDCANCEL)
	 	 			{ CDialog::OnCancel();} 
	
	}
	        
		 	    
		
	END_CATCH
	
	{
	
	
	
	
	}
 
 	

}

void CSOdialog::OnSetfocusMon() 
{
	// TODO: Add your control notification handler code here
	
	m_day = monday;
	

	

	Refresh();

	
	

}



void CSOdialog::OnSetfocusTue() 
{
	// TODO: Add your control notification handler code here

	m_day=tuesday;

	Refresh();
	
}

void CSOdialog::OnSetfocusWed() 
{
	// TODO: Add your control notification handler code here

	m_day=wednesday;

	Refresh();
	
}

void CSOdialog::OnSetfocusThu() 
{
	// TODO: Add your control notification handler code here

	m_day = thursday;

	Refresh();
	
}

void CSOdialog::OnSetfocusFri() 
{
	// TODO: Add your control notification handler code here

	m_day = friday;

	Refresh();
	
}

void CSOdialog::OnSetfocusSat() 
{
	// TODO: Add your control notification handler code here

	m_day = saturday;

	Refresh();
	
}

void CSOdialog::OnSetfocusSun() 
{
	// TODO: Add your control notification handler code here
	
	m_day = sunday;

	Refresh();
}

void CSOdialog::OnNonstan() 
{
	// TODO: Add your control notification handler code here

UINT STRING_ID(IDS_NEGSPAN);

  UpdateData(TRUE);

  TRY{

  /*check for silly times */

 CTimeSpan dummystar(0,m_starthrs,m_startmins,0);
 CTimeSpan dummydur(0,(m_durhrs - m_starthrs),(m_durmins-m_startmins),0);
 CTimeSpan dummyfin(0,(m_durhrs),(m_durmins),0);

  if(dummystar > dummyfin)
  {

  
  dummydur += ::ONE_DAY;

  }

  

  CSpan testspan(dummystar,dummydur);

  /*Prohibit absence overwriting absence */
  
  if(Clashes(&testspan, m_day))
  {

  STRING_ID = IDS_CONFLICT;

  AfxThrowUserException();


  }	 


  CSpan* currentspan;

  currentspan= (CSpan*) m_dayarray->GetAt(m_day);
  currentspan->ResetPeriod(dummystar,dummydur);

  





  
  
  CWnd* pwnd;

 pwnd= CWnd::GetDlgItem(IDC_NONSTAN);

		pwnd->EnableWindow(FALSE);
 
 pwnd= CWnd::GetDlgItem(IDOK);

		pwnd->EnableWindow(TRUE);

  Refresh();
  
  }
  
  CATCH(CUserException, e)
	{
	
	   if(AfxMessageBox(STRING_ID,MB_RETRYCANCEL,0)==IDCANCEL)
	 	 			{ CDialog::OnCancel();} else { Refresh();}
	
	}
	        
		 	    
		
	END_CATCH
	
	{
	
	
	
	
	}						
	
}


void CSOdialog::OnUpdateSthrs() 
{
	// TODO: Add your control notification handler code here

 CWnd* pwnd;

 pwnd= CWnd::GetDlgItem(IDC_NONSTAN);

		pwnd->EnableWindow(FALSE);				
	
}

void CSOdialog::OnUpdateStmins() 
{
	// TODO: Add your control notification handler code here

CWnd* pwnd;

 pwnd= CWnd::GetDlgItem(IDC_NONSTAN);

		pwnd->EnableWindow(FALSE);	
 
}

void CSOdialog::OnUpdateDurhrs() 
{
	// TODO: Add your control notification handler code here

CWnd* pwnd;

 pwnd= CWnd::GetDlgItem(IDC_NONSTAN);

		pwnd->EnableWindow(TRUE);
		
 pwnd =	CWnd::GetDlgItem(IDOK);	
 pwnd->EnableWindow(FALSE);	
 
 pwnd = (CComboBox*) CWnd::GetDlgItem(IDC_CODEBOX);
 ((CComboBox*)pwnd)->SetEditSel(0,-1);				
	
}

void CSOdialog::OnUpdateDurmns() 
{
	// TODO: Add your control notification handler code here




CWnd* pwnd;

 pwnd= CWnd::GetDlgItem(IDC_NONSTAN);

		pwnd->EnableWindow(TRUE);	
	
}


void CSOdialog::SetCheckboxes() 
{
	// TODO: Add your control notification handler code here

// reset all

ClearAllCheckboxes();

   double integerbit(0.0);

	double result(0.0);

	result = (double) weekstart;

	result/=28;

	result = modf(result , &integerbit);

	result *=100;

	int phase =(int) result;

	

	switch(phase)
	{

	case 0:
	m_bitvector->set(0,TRUE);
	break;
	case 25:
	m_bitvector->set(1,TRUE);
	break;
	case 50:
	m_bitvector->set(2,TRUE);
	break;
	case 75:
	m_bitvector->set(3,TRUE);
	break;
	
	default:
	break;



	}
}

void CSOdialog::OnUpdateMon() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	

	/* User types in text such as "E", sets combo text to value 
	and calls on Addbutton 

	CWnd* pwnd =  GetDlgItem(IDC_MON);

	CString txt;
	pwnd->GetWindowText(txt);
	
   m_codebox.SetWindowText(txt);
   OnAdcodebtn(); 


   */



}

void CSOdialog::OnDrp() 
{
	// TODO: Add your control notification handler code here
	

	m_drpvector->set(m_day,CWnd::IsDlgButtonChecked(IDC_DRP));
	Refresh();
	
}

BOOL CSOdialog::IsValidInstruction()
{

try
	{

	 CSpan* currentspan;
	 CTimeSpan collectorspan(::NONE);

	 for(int cnt(0);cnt<7;cnt++)
		 {

			currentspan = (CSpan*) m_dayarray->GetAt(cnt);
	
			if(!currentspan)
				{

				AfxThrowUserException();

				}

			collectorspan += currentspan->getstart();
			collectorspan += currentspan->getduration();
	
			}

	 if(collectorspan==::NONE)
		 {

		 return FALSE;

		 }
	 else
		 {


		 return TRUE;

		 }



	}
catch(CUserException* e)
	{

	AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);
	return FALSE;

	}

}

BOOL CSOdialog::IsWithinContractualPeriod(void)
{

BOOL outcome(false);

try
	{
   
	 long weekfinish(weekstart + 6);
	 return (m_parent->IsWithin(weekstart,weekfinish));

	}
catch(CUserException* e)
	{

	AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);
	outcome = false;

	}

 return outcome;
}

void CSOdialog::ClearAllCheckboxes()
{
try
	{


	m_bitvector->reset();

	}
catch(CUserException* e)
	{



	}

}

BOOL CSOdialog::IsClearWeeks()
{

BOOL one_checked(false);

try
	{

	if(!m_bitvector){ AfxThrowUserException();}

	for(UINT cnt(0);cnt<4;cnt++)
		{

		one_checked=(m_bitvector->IsSet(cnt));
		if(one_checked){ break;}

		}

	}
catch(CUserException* e)
	{

	AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);


	}

return (!one_checked);

}
