// Workspace.cpp: implementation of the CWorkspace class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <afxdao.h>
#include <wincrypt.h>
#include "winnetwk.h" 
#include <assert.h>
#include <math.h>
#include <afxdb.h>



#include <dbdao.h>

#include <afxole.h>



#include <iostream>
/*
#include "D:\Program Files\DevStudio\MyProjects\util.h"


#include "D:\Program Files\DevStudio\MyProjects\DBcmd\Debug\Pwdset.h"
#include "D:\Program Files\DevStudio\MyProjects\DBcmd\TCS.h"
#include "D:\Program Files\DevStudio\MyProjects\DBcmd\session.h"
*/
#include "util.h"
#include "tcs.h"
#include "pwdset.h"
#include "session.h"

#include "Workspace.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




CWorkspace::CWorkspace() :CUtil(), m_strUserName(_T("Sysop")), m_strPassword(_T("password")),m_strOldPassword(""),m_strSystemMDB( _T( "" ))
{
  
//fill session map
map_ptr = new CMapWordToOb;
map_ptr->SetAt(CareManagers,new CCareManagersSession());
map_ptr->SetAt(ServiceManagers,new CServiceManagersSession());
map_ptr->SetAt(Sysop,new CSysopSession());

// initialise default session


CObject* ptr;
map_ptr->Lookup(CareManagers,ptr);
mp_session = (CSession*) ptr;

// Initialize DAO for MFC
AfxDaoTerm( );
AfxDaoInit( );

CString errorstring;

SetSystemDB(GetRegString(CString("Sys"), CString("LocalSysPath")),errorstring);

loadata(errorstring);

    

}

CWorkspace::~CWorkspace()
{

CString errorstring;
savedata(errorstring); 

CObject* ptr; WORD id(0);

POSITION pos= map_ptr->GetStartPosition();

while(!map_ptr->IsEmpty())
	{ 
	
	map_ptr->GetNextAssoc(pos,id,ptr);
	map_ptr->RemoveKey(id);
	
	delete ptr;} 



delete map_ptr;


 
AfxDaoTerm( );

}




LRESULT CWorkspace::SetSystemDB(CString & strSystemMDB, CString& errorstring)
{
  
	COleVariant varSystemDB( strSystemMDB, VT_BSTRT );
   
   
   DAODBEngine* pDBEngine = AfxDaoGetEngine( );
   
    


 try
	  {  
   if( pDBEngine == NULL )
	   {
	   return 1;
	   }

   // Call put_SystemDB method to set the    // system database for DAO engine
   DAO_CHECK( pDBEngine->put_SystemDB( varSystemDB.bstrVal ) );
   m_strSystemMDB = strSystemMDB;
   return 0;
	  }
  catch(CdbException e)
	  {
	  
/*	  CdbError err;
	 CString stErr, stErr2;
	 for (int iErr = 0; iErr < engine.Errors.GetCount();iErr++)    {
        err = engine.Errors[long(iErr)];
        stErr.Format(_T("%ld"), DBERR(err.GetNumber()));
        stErr += _T(" : ");
        stErr2.Format(_T("%s"), err.GetDescription());
       
        stErr += stErr2 + _T("\n");    }
    
	errorstring = stErr;  */
    return DBERR(e.m_hr);



	  }
}



LRESULT CWorkspace::ChangePassword(const CString & strUserName,const CString & strOldPassword, const CString & strNewPassword, CString& errorstring)
{
 

 LRESULT nResult(113);
 CString verdict;

TRY
	{


CDaoWorkspace wsp;
wsp.Create( _T( "Temp Workspace" ), strUserName, strOldPassword );
wsp.Append();
if(!wsp.IsOpen())
	{ 
	
	nResult= 1;
	return nResult;}



      // Determine how many objects there are
   // in the Users collection 
	short nUserCount;
   short nCurrentUser;

   DAOUser *pUser  = NULL;
   DAOUsers *pUsers = NULL;

   // Side-effect is implicit   OLE AddRef( )  
   // on DAOUser object:
   DAO_CHECK( wsp.m_pDAOWorkspace->get_Users( &pUsers ) );
   // Side-effect is implicit OLE AddRef( )
   // on DAOUsers object
    DAO_CHECK( pUsers->get_Count( &nUserCount ) );

   // Traverse through the list of users 
   // and change password for the userid
	// used to create/open the workspace
   
   for( nCurrentUser = 0; nCurrentUser < nUserCount; nCurrentUser++ ) 
   {
       COleVariant varIndex( nCurrentUser, VT_I2 ); 
	   COleVariant varName;
       // Retrieve information for user nCurrentUser
       DAO_CHECK( pUsers->get_Item( varIndex, &pUser ) );
       // Retrieve name for user nCurrentUser
       DAO_CHECK( pUser->get_Name( &V_BSTR( &varName ) ) );
	   

       CString strTemp = V_BSTRT( &varName );
	   

       // If there is a match, change the password
       if( strTemp.CompareNoCase(strUserName)==0)//i.e matchfound    
	   {
           COleVariant varOldPwd( strOldPassword, 
                                  VT_BSTRT );
           COleVariant varNewPwd( strNewPassword, 
                                  VT_BSTRT );
           DAO_CHECK( pUser->NewPassword( V_BSTR( &varOldPwd ),
                      V_BSTR( &varNewPwd ) ) );
		   
		 nResult = 0;//success	      
		}//end if match 
   
   }
   // Clean up: decrement the usage count   // on the OLE objects
   pUser->Release( ); 
   pUsers->Release( );
   wsp.Close( );
   
	}// end TRY

CATCH(CDaoException, e)
	{
	errorstring = (e->m_pErrorInfo)->m_strDescription;
	
	nResult= (e->m_pErrorInfo)->m_lErrorCode;

	}

END_CATCH

return nResult;
}



LRESULT CWorkspace::UpdateRemote(CString& errorstring)
{

 LRESULT nResult(0);
 errorstring.Empty();

 TRY
	 {

	  
	  UINT i = GetRegInt(_T("RemoteDB"),_T("USEODBC"));
	  if(i)
		  {

		     nResult = ConnectDSN(errorstring);

		  

		  }
	  else
		  {

		 

		   nResult = ConnectAccess(errorstring);

		  }


	 }
 CATCH(CUserException,e)
	 {




	 }
 END_CATCH

return nResult;

}

LRESULT CWorkspace::CompactDB(CString& errorstring)
{





LRESULT nResult(1);
errorstring.Empty();


if(m_strPassword.IsEmpty())
	{
	 nResult = 9;
	 return nResult;

	}


CDaoWorkspace wsp;
wsp.Create( _T( "Temp Workspace" ), m_strUserName, m_strPassword );
wsp.Append();
if(!wsp.IsOpen())
	{ 
	
	nResult = 1;
	return nResult;}

TRY
	{


	
   
   CString strValue("No Path Set");
   CString strPath("replica of scenario.mdb");
   CString strTemp;

   strValue = GetRegString(CString("LocalDB"), CString("DBPath"));

   if((nResult=GetPathWithoutObject(strValue, strPath))>0)
	   {
	   
	   AfxThrowUserException();

	   }

   // create temporary filename

   strTemp = strPath;


   strTemp += _T("temp.mdb");
	 
	strValue = strPath;
	strValue +=_T("localdata.mdb");



	 wsp.CompactDatabase( strValue, strTemp);
	 CFile::Remove(strValue);

	 CFile::Rename( strTemp, strValue );

	 return 0;
	}

	  CATCH(CUserException, f)
	{  
	
	
	return nResult;

	
	}

	AND_CATCH(CMemoryException, g)
	{
	
	
	return 3;
    
	
	}

	 
	  	AND_CATCH(CDaoException, e)
	{
	
	
	//cout << (e->m_pErrorInfo)->m_strDescription << "\n";
	errorstring = (e->m_pErrorInfo)->m_strDescription;

	
	nResult= (e->m_pErrorInfo)->m_lErrorCode; 
	
	} 
	AND_CATCH( CFileException, e )
		
		{  
			/*
		 #ifdef _DEBUG
			
        afxDump << "File not found, cause = "
            << e->m_cause << "\n"; 
		   #endif
		errorstring = e->m_cause;
		*/
		return 4;
		}
	
	
	        
	
		
	END_CATCH
	
	{
	

	
	
	}
	
	
 
	}

LRESULT CWorkspace::Synchronise(CString& errorstring)
{

 LRESULT nResult(0);
 errorstring.Empty();

 if(m_strPassword.IsEmpty())
	{
	 nResult = 9;
	 return nResult;

	}

  DAODBEngine* pDBEngine = AfxDaoGetEngine( );
   if(pDBEngine == NULL)
	   {

		nResult = 1;
		return nResult;

	   }


 
  
   CString strValue("No Path Set");
   strValue = GetRegString(CString("LocalDB"), CString("DBPath"));


 CdbDBEngine engine( pDBEngine, TRUE);

 try
	 {

 CdbWorkspace wsp = engine.CreateWorkspace(_T("temp_workspace"),

m_strUserName,

m_strPassword,

dbUseJet);


 




engine.Workspaces.Append(wsp);

CdbDatabase db;
db = wsp.OpenDatabase(strValue,

dbDriverNoPrompt,

FALSE,

NULL);

strValue = GetRegString(CString("RemoteDB"),CString("Connect") );
strValue.MakeLower();
GetPathFromConnect(strValue,strValue);

DWORD value(dbRepImportChanges);

mp_session->GetDirection(value);

db.Synchronize(strValue,value);

db.Close();


 
// compact database

/*

CString strTemp("Replica of scenario.mdb");

strValue = GetRegString(CString("LocalDB"), CString("DBPath"));


if((nResult=GetPathWithoutObject(strValue, strTemp))>0)
	   {
	   
	   AfxThrowUserException();

	   }

   // create temporary filename

   
   strTemp += "temp.mdb";
	 


	 
	 engine.CompactDatabase (strValue,

strTemp,

NULL,

-1,

NULL);

 

	 CFile::Remove(strValue);

	 CFile::Rename( strTemp, strValue );

	 // compacting done


*/

wsp.Close();



nResult = 0;
	 }

 catch(CdbException e)
	{
	
	 CdbError err;
	 CString stErr, stErr2;
	 for (int iErr = 0; iErr < engine.Errors.GetCount();iErr++)    {
        err = engine.Errors[long(iErr)];
        stErr = err.GetDescription();
		stErr += _T("\n");    }
     
	errorstring = stErr;
    nResult = DBERR(e.m_hr);


	 }



 
  
return nResult;  
}



LRESULT CWorkspace::GetNewPassword(CString& errorstring)
{

LRESULT nResult(0);
errorstring.Empty();


TRY
	{

if(m_strPassword.IsEmpty())
	{
	 nResult = 9;
	 return nResult;

	}

CDaoWorkspace wsp;
wsp.Create( _T( "Temp Workspace" ), m_strUserName, m_strPassword );
wsp.Append();
if(!wsp.IsOpen())
	{ 
	
	nResult= 1;
	return nResult;}




CDaoDatabase db(&wsp);





  
   CString strTemp("Replica of scenario.mdb");
   
   
   
   CString strValue("No Path Set");
   strValue = GetRegString(CString("RemoteDB"), CString("Connect"));
   GetPathWithoutObject(strValue,strTemp);
   GetPathFromConnect(strTemp,strTemp);
   strTemp += "pwd.mdb";
   CString strConnect(";PWD=");
   strConnect += m_strPassword;

/*				exclusive and readonly*/
db.Open(strTemp,TRUE,TRUE,strConnect);

/* prepare temp string for new role as password holder */
strTemp.Empty();

CPwdset pwdset(&db);
pwdset.Open();
if(!(pwdset.IsBOF() && pwdset.IsEOF()))
	{
	 pwdset.MoveFirst();
	 strTemp.Empty();
	 while(!pwdset.IsEOF())
		 {
			

			strTemp = pwdset.m_pwd;
					
			pwdset.MoveNext();
		 }
	 
	}

pwdset.Close();
db.Close();
wsp.Close();
nResult= 0;




/*Finally, update your system.mda and password members to their new value */

		
		
		nResult = ChangePassword(m_strUserName,m_strPassword,strTemp,errorstring);


/* and reassign stored passwords */
		m_strOldPassword = m_strPassword;
		m_strPassword = strTemp;


	
}
CATCH(CDaoException, e)
	{
	  
	 /*Not being able to enter the database
	is the normal outcome. Either the current password
	is invalid or the database may not yet exist as Sysop may not have
	changed their password yet. If however the path to the database is wrongly 
	set, then in time the user will be locked out.
	The CatchUp menu item will readmit them.*/
	 switch((e->m_pErrorInfo)->m_lErrorCode)
		 {

		 
		 case 3031:
			 { errorstring = "no password change";
			  nResult= 0; }
			 break;
	
		 default:{ errorstring = (e->m_pErrorInfo)->m_strDescription;
			 nResult = (e->m_pErrorInfo)->m_lErrorCode;}
			 break;





		 }

	 
	 
	 
	}
END_CATCH

 return nResult;
	}

LRESULT CWorkspace::SetDBPassword(const CString& strOldOldPassword, CString& errorstring)
{

LRESULT nResult(0);


/* Called following a change of password by the system operator 
   Serves to update the central password database (pwd.mdb) so a 
   general update will follow via GetNewPassword during the unattended
   session. */


  DAODBEngine* pDBEngine = AfxDaoGetEngine( );
   if(pDBEngine == NULL)
	   {

		nResult = 1;
		return nResult;

	   }

 /* get in via the old old password	
 
	  */


   CString strTemp("Replica of scenario.mdb");
   CString strValue("No Path Set");
   strValue = GetRegString(CString("RemoteDB"), CString("Connect"));
   GetPathWithoutObject(strValue,strTemp);
   strTemp += "pwd.mdb";
   CString strConnect(";PWD=");
   strConnect += strOldOldPassword;

 /* to work, the connection must be up and running.
Either because sysop is on a LAN or because they have already
logged in manually via a dial up session */







   

 CdbDBEngine engine( pDBEngine, TRUE);

try
	{




 CdbWorkspace dbwsp = engine.CreateWorkspace(_T("temp_workspace"),

m_strUserName,

m_strPassword,

dbUseJet);
engine.Workspaces.Append(dbwsp);

CdbDatabase cdb;
GetPathFromConnect(strTemp,strTemp);
cdb = dbwsp.OpenDatabase(strTemp,

dbDriverNoPrompt,	   

FALSE,

strConnect);




// then set the oldpassword on the gate
// gaining access via the oldoldpassword

cdb.NewPassword(strOldOldPassword,m_strOldPassword );


// and set the new password  in the password field

CString strSQL = _T("UPDATE pwd SET pwd.pwd = '");
strSQL += m_strPassword;
strSQL  += _T("'");

cdb.Execute(strSQL); 

cdb.Close();




dbwsp.Close();

	 }
 catch(CdbException e)
	 {

	  CdbError err;
	 CString stErr, stErr2;
	 for (int iErr = 0; iErr < engine.Errors.GetCount();iErr++)    {
        err = engine.Errors[long(iErr)];
        stErr.Format(_T("%ld"), DBERR(err.GetNumber()));
        stErr += _T(" : ");
        stErr2.Format(_T("%s"), err.GetDescription());
        stErr += stErr2 + _T(" : ");
        stErr2.Format(_T("%s"), err.GetSource());
        stErr += stErr2 + _T("\n");    }
    
	errorstring = stErr;
    nResult = DBERR(e.m_hr);




	 }

	

return nResult;

}

LRESULT CWorkspace::savedata(CString& errorstring)
{


LRESULT nResult(0);


TRY
	{



CDaoWorkspace wsp;
wsp.Create( _T( "Temp Workspace" ), _T("custodiat"), _T("@@@@") );
wsp.Append();
if(!wsp.IsOpen())
	{ 
	
	nResult= 1;
	return nResult;}




CDaoDatabase db(&wsp);





  
   CString strTemp("Replica of scenario.mdb");
   
   
   
   CString strValue("No Path Set");
   strValue = GetRegString(CString("LocalDB"), CString("DBPath"));
   GetPathWithoutObject(strValue,strTemp);
   
   strTemp += "pwd.mdb";
   CString strConnect(";PWD=");
   strConnect += _T("@@@@");

/*				exclusive and readwrite*/
db.Open(strTemp,TRUE,FALSE,strConnect);




CPwdset pwdset(&db);


pwdset.Open();
if(!(pwdset.IsBOF() && pwdset.IsEOF()))
	{
	 pwdset.MoveFirst();
	 strTemp.Empty();
	 while(!pwdset.IsEOF())
		 {
			pwdset.Edit();
			pwdset.m_pwd = m_strPassword;
			pwdset.m_oldpwd = m_strOldPassword;
			pwdset.m_groupindex = (long) mp_session->GetGroup();
			pwdset.Update(); 					
			pwdset.MoveNext();
		 }
	 
	}

pwdset.Close();
db.Close();
wsp.Close();
nResult= 0;


	}

CATCH(CDaoException, e)
	{
	  
	 
	 
	 nResult = (e->m_pErrorInfo)->m_lErrorCode;
	 errorstring = (e->m_pErrorInfo)->m_strDescription;		 
	 
	 
	}
END_CATCH
return nResult;




}



LRESULT CWorkspace::loadata(CString& errorstring)
{


LRESULT nResult(0);


TRY
	{



CDaoWorkspace wsp;
wsp.Create( _T( "Temp Workspace" ), _T("custodiat"), _T("@@@@") );
wsp.Append();
if(!wsp.IsOpen())
	{ 
	
	nResult= 1;
	return nResult;}




CDaoDatabase db(&wsp);





  
   CString strTemp("Replica of scenario.mdb");
   
   
   
   CString strValue("No Path Set");
   strValue = GetRegString(CString("LocalDB"), CString("DBPath"));
   GetPathWithoutObject(strValue,strTemp);
   
   strTemp += "pwd.mdb";
   CString strConnect(";PWD=");
   strConnect += _T("@@@@");

/*				exclusive and readonly*/
db.Open(strTemp,TRUE,TRUE,strConnect);




CPwdset pwdset(&db);

group memberof;
CObject* ptr;
pwdset.Open();
if(!(pwdset.IsBOF() && pwdset.IsEOF()))
	{
	 pwdset.MoveFirst();
	 strTemp.Empty();
	 while(!pwdset.IsEOF())
		 {
			
			m_strPassword = pwdset.m_pwd;
			m_strOldPassword = pwdset.m_oldpwd;
			strTemp = pwdset.m_pwd;
			memberof = (group) pwdset.m_groupindex;
			pwdset.MoveNext();
		 }

	 map_ptr->Lookup(memberof,ptr);
	 mp_session = (CSession*) ptr;

	 

	  
	}

pwdset.Close();
db.Close();
wsp.Close();
nResult= 0;


	}

CATCH(CDaoException, e)
	{
	  
	 
	 
	 nResult = (e->m_pErrorInfo)->m_lErrorCode;
	  errorstring = (e->m_pErrorInfo)->m_strDescription;		 
	 
	 
	}
END_CATCH
return nResult;
}



LRESULT CWorkspace::CreateUser(const CString sysoppwd,const CString strUserName,  const CString strPID, const CString strPassword, const CString strGroup, CString& errorstring)
{

LRESULT nResult(0);

 if(m_strPassword.IsEmpty())
	{
	 nResult = 9;
	 return nResult;

	}

  DAODBEngine* pDBEngine = AfxDaoGetEngine( );
   if(pDBEngine == NULL)
	   {

		nResult = 1;
		return nResult;

	   }


 
   

 CdbDBEngine engine( pDBEngine, TRUE);

 try
	 {

	 CdbWorkspace wsp = engine.CreateWorkspace(_T("temp_workspace"),

	m_strUserName,

	sysoppwd,

	dbUseJet);
	engine.Workspaces.Append(wsp);


	CString strTemp("Users");

	

	CdbUser fred = wsp.CreateUser(strUserName,strPID,strPassword);
	wsp.Users.Append(fred);
		
	CdbGroup cm = fred.CreateGroup(strTemp);
	fred.Groups.Append(cm);
	cm = fred.CreateGroup(strGroup);
	fred.Groups.Append(cm);

	
	fred.Groups.Refresh();
	wsp.Users.Refresh();
	

	wsp.Close();


	}

catch(CMemoryException* g)
	{
	
	  
	LPTSTR lpszError = new TCHAR[255];
    g->GetErrorMessage( lpszError, 255);
	delete [] lpszError;
	nResult = 4;
	g->Delete();
    
	
	}

	
catch(CdbException e)
	{
	
	 
    CdbError err;
	 CString stErr,stErr2;
	 for (int iErr = 0; iErr < engine.Errors.GetCount();iErr++)    {
        err = engine.Errors[long(iErr)];
        stErr +=err.GetDescription();
        stErr += _T("\n");    }
    
	errorstring = stErr;	 
    nResult = DBERR(e.m_hr);

	
	
	 }
return nResult;
}

LRESULT CWorkspace::ConnectDSN(CString & errorstring)
{

LRESULT nResult(0);

if(m_strPassword.IsEmpty())
	{
	 nResult = 9;
	 return nResult;

	}


CDaoWorkspace wsp;
wsp.Create( _T( "Temp Workspace" ), m_strUserName, m_strPassword );
wsp.Append();
if(!wsp.IsOpen())
	{ 
	
	nResult= 1;
	return nResult;}


TRY
	{

 
 CDaoDatabase db(&wsp);


   
   
   CString strValue("No Path Set");
   strValue = GetRegString(CString("LocalDB"),CString( "DBPath"));
  
db.Open(strValue);

// Construct the tabledef then create attached table
CDaoTableDef td( &db );


// check to see if table exists if not create it



wsp.BeginTrans();



	td.Create( _T("Log2"),0,_T("log"),_T("ODBC;DSN=dsn_postgres;UID=andrew;PWD=footle") );
	td.Append( );
	



db.Execute(_T("applog2"),dbFailOnError);
db.Execute(_T("DELETE * FROM temp_table;"),dbFailOnError);
db.Execute(_T("upd_sync"),dbFailOnError);
db.Execute(_T("DROP TABLE Log2"),dbFailOnError);

wsp.CommitTrans();

	

	db.Close();
	wsp.Close();

	nResult = 0;
   
   } //end try

   CATCH(CUserException, f)
	{  
	
	
	nResult = 2;

	
	}
	 
	 	AND_CATCH(CDaoException, e)
	{
	
	
	
	errorstring = (e->m_pErrorInfo)->m_strDescription;

	wsp.Rollback();
	nResult= (e->m_pErrorInfo)->m_lErrorCode;


	
	} 
	
	AND_CATCH(CMemoryException, g)
	{
	
	wsp.Rollback();  
	LPTSTR lpszError = new TCHAR[255];
    g->GetErrorMessage( lpszError, 255);
	delete [] lpszError;
	nResult = 4;

    
	
	}
	        
	
		
	END_CATCH
	
	{
	

	
	
	}      

return nResult;


}

LRESULT CWorkspace::ConnectAccess(CString & errorstring)
{

/* attaches table from remote Access source protected by password */

// reset reporting variables

 LRESULT nResult(0);
 errorstring.Empty();

if(m_strPassword.IsEmpty())
	{
	 nResult = 9;
	 return nResult;

	}


 DAODBEngine* pDBEngine = AfxDaoGetEngine( );
   if(pDBEngine == NULL)
	   {

		nResult = 1;
		return nResult;

	   }

 CdbDBEngine engine( pDBEngine, TRUE);

try
	{
  
 
 


   
   
   CString strValue("No Path Set");
     
   strValue = GetRegString(CString("LocalDB"), CString("DBPath"));
   //connect string for linked table


   CString strConnect = GetRegString(CString("RemoteDB"),CString("DBPath"));
   
   



 
CdbWorkspace dbwsp = engine.CreateWorkspace(_T("temp_workspace"),

m_strUserName,

m_strPassword,

dbUseJet);
engine.Workspaces.Append(dbwsp);

CdbDatabase cdb;
cdb = dbwsp.OpenDatabase(strValue,

dbDriverNoPrompt,

FALSE,

_T(""));


// Construct the tabledef then create attached table
CdbTableDef td;


// check to see if table exists if not create it



dbwsp.BeginTrans();



	td = cdb.CreateTableDef(
		_T("Log2"),dbAttachExclusive,
		_T("log"),strConnect);
   
	cdb.TableDefs.Append(td );

	
/*
//  retrieve query name from appropriate
//  session :

// when synchronising

  Care Managers roll back deleted records on hub as
  locally unauthorised,
  everybody else deletes locals
	
  when updating remote

  CareManagers append remote
//  everybody else appends locally.
*/

CString strqry;
mp_session->GetSyncQueryName(strqry, errorstring);
cdb.Execute(strqry,dbFailOnError);
strqry.Empty();

mp_session->GetAppendQueryName(strqry,errorstring);
cdb.Execute(strqry,dbFailOnError);
cdb.Execute(_T("DELETE * FROM temp_table;"),dbFailOnError);
cdb.Execute(_T("DROP TABLE Log2"),dbFailOnError);

dbwsp.CommitTrans();

	

	cdb.Close();
	dbwsp.Close();

	nResult = 0;
   
   } //end try

   catch(CdbException e)
	 {

	CdbError err;
	 CString stErr, stErr2;
	 for (int iErr = 0; iErr < engine.Errors.GetCount();iErr++)    {
        err = engine.Errors[long(iErr)];
        stErr = err.GetDescription();
		stErr += _T("\n");    }
     
	errorstring = stErr;

    nResult = DBERR(e.m_hr);




	 }


return nResult;



}


LRESULT CWorkspace::GetCurrentPwd(CString& copystring)
{

LRESULT nResult(1);

TRY
	{
	copystring = m_strPassword;
	nResult = 0;



	}
CATCH(CUserException, e)
	{





	}

END_CATCH

return nResult;

}

LRESULT CWorkspace::connectshared(CString& errorstring)
{

// Connect to shared disk area

LRESULT nResult(0);
errorstring.Empty();

TRY
	{


NETRESOURCE nr;

     nr.dwType = RESOURCETYPE_DISK;
     nr.lpLocalName= NULL;
	 CString lpremote( GetRegString(_T("RemoteDB"),_T("Sharename")));
	 nr.lpRemoteName =  lpremote.GetBuffer(512);
	 nr.lpProvider = NULL;
	 nr.lpComment = _T("special connection for unattended session");
	    
    
	//used in function

	CString lpPassword = _T("sdb~3");
	

DWORD dword = WNetAddConnection2( &nr, 
 // points to structure that specifies connection details 
 
lpPassword, 
 // points to password string 
 
m_strUserName, 
 // points to user name string 
 
0 
 
 // set of bit flags that specify connection options 
 
); 

//check connection





 


if(filefound(CString("RemoteDB"),CString("Connect"))==0)
		{
			nResult = 0;
			return nResult;
		}// connection works

 

//delete lpNetResource;

switch(dword)
	{
	case ERROR_ACCESS_DENIED : 
 errorstring = _T("Access to the network resource was denied. ");
  AfxThrowUserException();

 	 break;

	case ERROR_ALREADY_ASSIGNED :
errorstring = _T("The local device specified by lpLocalName is already connected to a network resource. ");
 AfxThrowUserException();

 	 break;

	case ERROR_BAD_DEV_TYPE : 
errorstring = _T("The type of local device and the type of network resource do not match. ");
 AfxThrowUserException();

	 break;
 
	case ERROR_BAD_DEVICE :
 errorstring = _T("The value specified by lpLocalName is invalid. ");
  AfxThrowUserException();

	 break;
 
	case ERROR_BAD_NET_NAME :
 errorstring = _T("The value specified by lpRemoteName is not acceptable to any network resource provider. The resource name is invalid, or the named resource cannot be located. ");
  AfxThrowUserException();

	 break;
 
	case ERROR_BAD_PROFILE :
	errorstring = _T("The user profile is in an incorrect format. ");
	 AfxThrowUserException();

	break;

	case ERROR_BAD_PROVIDER : 
errorstring = _T(" The value specified by lpProvider does not match any provider. ");
 AfxThrowUserException();


	break;
 
	case ERROR_BUSY :

 errorstring = _T("The router or provider is busy, possibly initializing. The caller should retry. ");
  AfxThrowUserException();

	break;

 
	case ERROR_CANCELLED  :
 errorstring = _T("The attempt to make the connection was cancelled by the user through a dialog box from one of the network resource providers, or by a called resource. ");
  AfxThrowUserException();

	break;
 
	case ERROR_CANNOT_OPEN_PROFILE 	:
 errorstring = _T("The system is unable to open the user profile to process persistent connections. ");
  AfxThrowUserException();

	break;
 
	case ERROR_DEVICE_ALREADY_REMEMBERED  :
 errorstring = _T("An entry for the device specified in lpLocalName is already in the user profile. ");
  AfxThrowUserException();

	break;
 
	case ERROR_EXTENDED_ERROR :
		
 errorstring = _T("A network-specific error occured. Call the WNetGetLastError function to get a description of the error. ");
 	break;
	case ERROR_INVALID_PASSWORD :
 errorstring = _T("The specified password is invalid. ");
 AfxThrowUserException();

	break;
 
	case ERROR_NO_NET_OR_BAD_PATH :
errorstring = _T("A network component has not started, or the specified name could not be handled. ");
AfxThrowUserException();

	break;
 
	case ERROR_NO_NETWORK :
		errorstring = _T("There is no network present. ");
		AfxThrowUserException();

	break;

	
	default :

	break;





	}

 if( dword)
 {
	LPTSTR er = new TCHAR[512];
	LPTSTR namebuf = new TCHAR[512];

 


	
	
	
	WNetGetLastError( &dword, 
 // pointer to error code 
 
er, 
 // pointer to string describing error 
 
512, 
 // size of description buffer, in characters 
 
namebuf, 
 // pointer to buffer for provider name 
 
512
 // size of provider name buffer 
 
);
	
	

 
	errorstring += er;
	delete er;
	delete namebuf;

	 }

	}//end try

CATCH(CUserException, e)
	{

	 nResult = 14;


	}

END_CATCH
return nResult;

}

LRESULT CWorkspace::UpdateSysop(const CString& strUserName,const CString & strOldPassword, const CString & strNewPassword, CString& errorstring)
{

/*
PURPOSE: to handle password changes made by the system operator.

  
Sysop's password change may be a general change, which requires
propagating to all participating machines or may need to be confined to 
a local machine, for example immediately after installation.


*/


LRESULT nResult(0);
errorstring.Empty();

TRY{



		CString OldOldPassword(m_strOldPassword);


		nResult = ChangePassword(strUserName,strOldPassword,strNewPassword,errorstring);
		if(nResult>0){ AfxThrowUserException();}

		m_strOldPassword = strOldPassword;
		m_strPassword = strNewPassword;



		nResult = SetDBPassword(OldOldPassword,errorstring);
						 
					} // end if sysop

		CATCH(CUserException, e)
			{


			



			}
		END_CATCH


return nResult;
}

LRESULT CWorkspace::SetGroup(const enum group membership,const CString & sysoppwd, CString errorstring)
{

errorstring.Empty();

LRESULT nResult(0);

 

  DAODBEngine* pDBEngine = AfxDaoGetEngine( );
   if(pDBEngine == NULL)
	   {

		nResult = 1;
		return nResult;

	   }


 
   

 CdbDBEngine engine( pDBEngine, TRUE);

 try
	 {

	 // first check to see if supplied password is 
	 // correct

	 CdbWorkspace wsp = engine.CreateWorkspace(_T("temp_workspace"),

	m_strUserName,

	sysoppwd,

	dbUseJet);

   CObject* ptr;
   map_ptr->Lookup(membership,ptr );
   mp_session = (CSession*) ptr;
   assert(mp_session->GetGroup()==2);


	}
catch(CUserException* e)
	{





	}
 
catch(CdbException e)
	{
	
	 
    CdbError err;
	 CString stErr,stErr2;
	 for (int iErr = 0; iErr < engine.Errors.GetCount();iErr++)    {
        err = engine.Errors[long(iErr)];
        stErr += err.GetDescription();
        stErr += _T("\n");    }
    
	errorstring = stErr;	 
    nResult = DBERR(e.m_hr);
	AfxMessageBox(errorstring,MB_OK);
	
	
	 }

return nResult;
}

LRESULT CWorkspace::CatchUpPassword(const CString& strUserName,const CString & strOldPassword, const CString & strNewPassword, CString& errorstring)
{

/*
PURPOSE: to handle password changes made by the system operator for local machine only.

  
For example after lockout.


*/


LRESULT nResult(0);
errorstring.Empty();

TRY{



		CString OldOldPassword(m_strOldPassword);


		nResult = ChangePassword(strUserName,strOldPassword,strNewPassword,errorstring);
		if(nResult>0){ AfxThrowUserException();}

		m_strOldPassword = strOldPassword;
		m_strPassword = strNewPassword;



		
						 
					} // end if sysop

		CATCH(CUserException, e)
			{


			



			}
		END_CATCH


return nResult;


}

enum group CWorkspace::GetGroup()
{

return mp_session->GetGroup();

}

LRESULT CWorkspace::fillcombo (CComboBox*& pcombo,const CString& package)
{
/*Purpose: performs database lookup for conhrs by package*/

LRESULT nResult(0);



TRY
	{

if(m_strPassword.IsEmpty())
	{
	 nResult = 9;
	 return nResult;

	}

CDaoWorkspace wsp;
wsp.Create( _T( "Temp Workspace" ), m_strUserName, m_strPassword );
wsp.Append();
if(!wsp.IsOpen())
	{ 
	
	nResult= 1;
	return nResult;}




CDaoDatabase db(&wsp);

     
   
   
   CString strValue("No Path Set");
   strValue = GetRegString(CString("LocalDB"), CString("DBPath"));
   
   db.Open(strValue,TRUE,FALSE,_T(""));



CTCSset TCSset(&db);

CString strSQL("Select Package, Conhrs FROM TCS ");


 

TCSset.Open( AFX_DAO_USE_DEFAULT_TYPE, strSQL, 0 );




	
if(!(TCSset.IsBOF() && TCSset.IsEOF()))
	{

	TCSset.MoveFirst();
	int cnt(0);
	double hour_bit(0.0);
	double minbit(0.0);
	double mins(0.0);
	double secbit(0.0);
	double secs(0.0);

	CTimeSpan* timeptr=NULL;
	while(!TCSset.IsEOF())
		{

		if(!TCSset.m_Package.CompareNoCase(package))
			{
			mins = modf(TCSset.m_Conhrs/5,&hour_bit);// get remainder 

	minbit = mins * 60;  // Get minutes	and seconds in decimal

	secbit = modf(minbit ,&mins); // Get minutes

	secbit = secbit * 60;

	modf(secbit, &secs); // Get seconds

	timeptr=(CTimeSpan*) new CTimeSpan(0,(int) hour_bit,(int) mins ,(int) secs);
			

			pcombo->InsertString(cnt,timeptr->Format(_T("%H:%M")));
			pcombo->SetItemDataPtr(cnt,timeptr);
			cnt++;
			break;
			} // end if
			
		TCSset.MoveNext();
		} // end while
		
	if(!cnt){ AfxThrowUserException();}

	TCSset.Close();
	} //end if not empty set
	else
	{
	nResult = 5;
	AfxThrowUserException();
	}

db.Close();
wsp.Close();
nResult= 0;


	}

CATCH(CDaoException, e)
	{

	nResult = (e->m_pErrorInfo)->m_lErrorCode;



	}

AND_CATCH(CMemoryException, g)
	{
	
	
	return 3;
    
	
	}
AND_CATCH(CUserException, u)
	{
	
	
	return 4;
    
	
	}


END_CATCH

return nResult;

}

LRESULT CWorkspace::swapworkspace(CDaoWorkspace * & wsp)
{

/*Swaps an existing authorised workspace
for another with special privileges for an authorised
purpose. E.g called by the rota sketch pad for the Update Database
command which requires update privilages on tables not normally
available to Care Managers. This enables Care Managers to have read only 
privilages when accessing the care hours database manually
and only update privilages when updating it via the application*/

LRESULT nResult(0);
try
	{
	 

	if(!(wsp->IsOpen() && wsp)){ AfxThrowUserException();}

	// fine. This is a valid workspace. Close it and delete it.
	wsp->Close();
	delete wsp;

	// now create a sysop workspace using the current workspace

	if(m_strPassword.IsEmpty())
	{
	 nResult = 9;
	 return nResult;

	}

	
CDaoWorkspace* nwsp = new CDaoWorkspace;

nwsp->Create( _T( "Temp Workspace" ), m_strUserName, m_strPassword );
nwsp->Append();
if(!nwsp->IsOpen())
	{ 
	
	nResult= 1;
	return nResult;}

// assign the current workspace to the passed workspace pointer


wsp = nwsp;

	}

catch(CUserException* e)
	{


	 nResult = 4;

	}
catch(CDaoException* e)
	{
	  
	 
	 nResult = (e->m_pErrorInfo)->m_lErrorCode;


	}


return nResult;
}
