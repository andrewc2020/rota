
// Rota.cpp : Defines the class behaviors for the application.
//
#define STANDALONE
#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Rota.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "RotaDoc.h"
#include "RotaView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRotaApp

BEGIN_MESSAGE_MAP(CRotaApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CRotaApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CRotaApp construction

CRotaApp::CRotaApp() noexcept
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Rota.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CRotaApp object

CRotaApp theApp;


// CRotaApp initialization

BOOL CRotaApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_RotaTYPE,
		RUNTIME_CLASS(CRotaDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CRotaView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// enable filemanager drag and drop & DDE Execute Open

	m_pMainWnd->DragAcceptFiles();
	EnableShellOpen();
	RegisterShellFileTypes();

	/* by default the MRU should provide the first document. If this
	fails the application will call OnFileNew() which will
	try the data source.

	We do not want to overwrite the command line member:

	a) in case the user has chosen to do an embedded launch

	b) because the CWinApp member m_lpCmdLine might be used by other
		code. It is a public member so it should be safe, but..*/



	CString lastused(AfxGetApp()->GetProfileString(_T("Recent File List"),
		_T("Rota1"),
		_T("Not found")));


	CString pFileName = lastused.GetBuffer(lastused.GetLength());


	/*Check MRU entry in case it has been moved or deleted*/







	CFileStatus status;
	CFile cfile;

	//char* pFileName = "test.dat";
	if (cfile.GetStatus(pFileName, status))   // static function
	{
#ifdef _DEBUG
		afxDump << "Full file name = " << status.m_szFullName << "\n";
#endif

		m_lpCmdLine = status.m_szFullName;

	}

	else

	{


		/*AfxMessageBox(
			_T("File could not be opened\n")
			, MB_OK, 0
		);*/
	}


	if (m_lpCmdLine[0] == '\0') // i.e MRU is empty
	{
		// TODO: add command line processing here 
		OnFileNew();// in this application creates a new document
					// filled from the data source

	}

	else if ((m_lpCmdLine[0] == '-' || m_lpCmdLine[0] == '/') &&
		(m_lpCmdLine[0] == 'e' || m_lpCmdLine[0] == 'E'))

	{

		//embedded launch

	}

	else

	{
		OpenDocumentFile(m_lpCmdLine);
	}

	// The main window has been initialized, so show and update it.
	lastused.ReleaseBuffer();

#ifndef STANDALONE
	// finally initialise the workspaceserver
	//mp_workserver = new CWorkspace;
#endif

	return TRUE;
}

int CRotaApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CRotaApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CRotaApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CRotaApp message handlers
CWorkspace* CRotaApp::GetWorkspaceServer()
{

	assert(mp_workserver != NULL);

	return mp_workserver;

}


