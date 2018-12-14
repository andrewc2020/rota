#include <afxdao.h>


#include <afxdb.h>
#include "stdafx.h"


#include <dbdao.h>

#include <afxole.h>
#include <dbdao.h>

#include "session.h"



CSession::CSession()
	{




	}
CSession::~CSession()
	{




	}

/////////////////////////////////////////////////////////////////////////////
// CSession message handlers

LRESULT CSession::GetDirection(DWORD & direction)
{



return 0;

}




enum group CSession::GetGroup(void)
	{

	 
	/*NB Overridden in derived classes*/

	return CareManagers;



	}


LRESULT CSession::GetAppendQueryName(CString& strqry,CString errorstring)
	{
	LRESULT nResult(0);

	try
		{

		strqry = _T("aplocal");


		}
	catch(CUserException* e)
		{





		}
	return nResult;
	}

CCareManagersSession::CCareManagersSession():CSession()
	{




	}

CCareManagersSession::~CCareManagersSession()
	{




	}



enum group CCareManagersSession::GetGroup(void)
	{

	 


	return CareManagers;



	}

LRESULT CCareManagersSession::GetAppendQueryName(CString& strqry,CString errorstring)
	{
	LRESULT nResult(0);
	try
		{

		strqry = _T("applog2");


		}
	catch(CUserException* e)
		{





		}
	return nResult;
	}



//Service Managers


CServiceManagersSession::CServiceManagersSession():CSession()
	{




	}

CServiceManagersSession::~CServiceManagersSession()

	{




	}



enum group CServiceManagersSession::GetGroup(void)
	{

	 


	return ServiceManagers;



	}


//Sysop session


CSysopSession::CSysopSession():CSession()
	{




	}

CSysopSession::~CSysopSession()
	{




	}



enum group CSysopSession::GetGroup(void)
	{

	 


	return Sysop;



	}




LRESULT CSysopSession::GetDirection(DWORD & direction)
{

direction = dbRepExportChanges;
return 0;


}

LRESULT CSession::GetSyncQueryName(CString & strqry, CString errorstring)
{
LRESULT nResult(0);
	try
		{

		strqry = _T("del_sync");


		}
	catch(CUserException* e)
		{





		}
	return nResult;


}

LRESULT CCareManagersSession::GetSyncQueryName(CString & strqry, CString errorstring)
{
LRESULT nResult(0);
	try
		{

		strqry = _T("upd_sync");


		}
	catch(CUserException* e)
		{





		}
	return nResult;


}
