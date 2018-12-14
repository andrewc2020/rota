#if !defined(AFX_SUBCONDLG_H__F8419E00_B303_11D3_87EC_00104BA41D62__INCLUDED_)
#define AFX_SUBCONDLG_H__F8419E00_B303_11D3_87EC_00104BA41D62__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SubCondlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubCondlg dialog

class CSubCondlg : public CDialog
{
// Construction
public:
	 CSubCondlg(CDaoDatabase& db, CObList* original, CWnd* pParent /*=NULL*/);
	CMapPtrToPtr m_map;
	CSubCondlg(CWnd* pParent = NULL);   // standard constructor
	CObList* m_existptr;
	CTime m_endrota;

// Dialog Data
	//{{AFX_DATA(CSubCondlg)
	enum { IDD = IDD_DIALOG19 };
	CListBox	m_LIST2;
	CListBox	m_LIST1;
	CButton	m_reset;
	CString	m_LIST3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubCondlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubCondlg)
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnHelp();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList1();
	afx_msg void OnSelchangeList3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void EnableOK(void);
	void FillExist(void);
	void Cleanup(void);
	CDaoDatabase* m_db;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBCONDLG_H__F8419E00_B303_11D3_87EC_00104BA41D62__INCLUDED_)
