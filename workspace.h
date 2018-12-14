// Workspace.h: interface for the CWorkspace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKSPACE_H__C6A4DCA9_39EA_11D3_87EB_00104BA41D62__INCLUDED_)
#define AFX_WORKSPACE_H__C6A4DCA9_39EA_11D3_87EB_00104BA41D62__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CUtil;
class CSession;
class CDaoWorkspace;

class CWorkspace : public CUtil
{
public:
	LRESULT SetGroup(const enum group ,const CString&,CString);
	LRESULT UpdateSysop(const CString&,const CString&,const CString&,CString&);
	
	LRESULT GetCurrentPwd(CString&);
	LRESULT connectshared(CString&);
	LRESULT CreateUser(const CString, const CString, const CString, const CString,  const CString, CString&);
	LRESULT GetNewPassword(CString&);
	LRESULT Synchronise(CString&);
	LRESULT CompactDB(CString&);
	LRESULT UpdateRemote(CString&);
	LRESULT ChangePassword(const CString&,const CString&,const CString&, CString&);
	
	LRESULT SetSystemDB(CString&,CString& );
	CWorkspace();
	virtual ~CWorkspace();

	
	
public:
	LRESULT swapworkspace(CDaoWorkspace*&);
	LRESULT fillcombo(CComboBox*& pCombo, const CString&);
	enum group GetGroup(void);
	LRESULT CatchUpPassword(const CString&,const CString&,const CString&,CString&);
	CSession* mp_session;



private:
	
	
	CMapWordToOb* map_ptr;
	LRESULT SetDBPassword(const CString& strOldOldPassword, CString& errorstring);
	LRESULT ConnectDSN(CString&);
	LRESULT ConnectAccess(CString&);
	CString m_strOldPassword;
	LRESULT loadata(CString&);
	LRESULT savedata(CString&);
	CString m_strSystemMDB;
	CString m_strPassword;
	CString m_strUserName;
};

#endif // !defined(AFX_WORKSPACE_H__C6A4DCA9_39EA_11D3_87EB_00104BA41D62__INCLUDED_)
