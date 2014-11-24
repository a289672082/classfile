
// MyDialog.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "MyDialog.h"
#include "MyDialogDlg.h"
#include "DbgHelp.h"
#include "CEyLoginSoft.h"
#pragma comment (lib,"dbghelp.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//最主要的函数, 生成Dump
static void DumpMiniDump(PEXCEPTION_POINTERS excpInfo)
{

	HANDLE hFile = CreateFile( (".\\程序错误调试文件.dmp"), GENERIC_READ | GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 
	OutputDebugString(("writing minidump\r\n"));
	MINIDUMP_EXCEPTION_INFORMATION eInfo;
	eInfo.ThreadId = GetCurrentThreadId(); //把需要的信息添进去
	eInfo.ExceptionPointers = excpInfo;
	eInfo.ClientPointers = FALSE;

	// 调用, 生成Dump. 98不支持
	// Dump的类型是小型的, 节省空间. 可以参考MSDN生成更详细的Dump.
	MiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		hFile,
		MiniDumpNormal,
		excpInfo ? &eInfo : NULL,
		NULL,
		NULL);

}
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)  
{   
	DumpMiniDump(pException);



	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	char szFileName[1024];
	GetModuleFileName(NULL, szFileName, 1024);

	/*	MessageBoxA(0,szFileName,0,0);*/

	if( !CreateProcess( NULL,   // No module name (use command line). 
		szFileName, // Command line. 
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi)             // Pointer to PROCESS_INFORMATION structure.
		)  
	{
		printf( "CreateProcess failed (%d).\n", GetLastError() );
	}

	ExitProcess(-1);
	//  
	//	FatalAppExit(-1,  _T("*** Unhandled Exception!222 ***"));  

	return EXCEPTION_EXECUTE_HANDLER;  
}  
// CMyDialogApp

BEGIN_MESSAGE_MAP(CMyDialogApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyDialogApp 构造

CMyDialogApp::CMyDialogApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMyDialogApp 对象

CMyDialogApp theApp;


// CMyDialogApp 初始化

BOOL CMyDialogApp::InitInstance()
{
 	IsEndGame = false;
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

/*
	InitDM();
	dm_denglu.Init();
	dm_denglu.MyReg();*/

	HMODULE useH=	GetModuleHandleA("user32.dll");
	MessageBoxTimeoutA=(_MessageBoxTimeoutA)  GetProcAddress(useH,"MessageBoxTimeoutA");


 	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
 
	memset(CurPath,0,1024);
	::GetModuleFileNameA(NULL,theApp.CurPath,1024); 
	Tmps1.Format("%s",theApp.CurPath);
/*
	theApp.Tmpsw1.Delete(theApp.Tmpsw1.ReverseFind(L'\\') ,theApp.Tmpsw1.GetLength());
	Tmps1.Format("%wz",Tmpsw1.GetBuffer(0)) ;*/
   tmpint1 = strlen("MyDialog.exe");
   Tmps1.Delete(Tmps1.GetLength()- tmpint1 ,tmpint1); 
	memset(theApp.CurPath,0,1024);
	memcpy(theApp.CurPath,theApp.Tmps1.GetBuffer(0),theApp.Tmps1.GetLength()); 
 
	::SetCurrentDirectoryA(theApp.CurPath);
	//登录用的大漠

	InitDM();
	dm_denglu.Init();
	dm_denglu.MyReg();
	CMyDialogDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}


typedef VOID (__stdcall *_SetDllPathA)(char* dllpath,int SETWHAT);
_SetDllPathA  SetDllPathA;
void CMyDialogApp::InitDM()
{

 MyCom  com1;
	dm.dm=(Idmsoft*)com1.ReCOM_DM_RES(IDR_DM21,"dm2");
		dm_game.dm =(Idmsoft*)com1.ReCOM_DM_RES(IDR_DM21,"dm2");
			dm_Help.dm =(Idmsoft*)com1.ReCOM_DM_RES(IDR_DM21,"dm2");
				dm_denglu.dm =(Idmsoft*)com1.ReCOM_DM_RES(IDR_DM21,"dm2");
 
/*
	HMODULE hSetDllPathA =LoadLibraryA(".\\DmReg.dll");
	SetDllPathA=(_SetDllPathA )GetProcAddress(hSetDllPathA,"SetDllPathA");

	if (SetDllPathA==NULL)
	{
		AfxMessageBox("获取免注册函数失败！");
		return   ;
	}

	SetDllPathA(".\\dm2.dll",1);*/
	return  ;
/*
	HMODULE hSetDllPathA =LoadLibraryA(".\\DmReg.dll");
	SetDllPathA=(_SetDllPathA )GetProcAddress(hSetDllPathA,"SetDllPathA");

	if (SetDllPathA==NULL)
	{
		AfxMessageBox("获取免注册函数失败！");
		return   ;
	}

	SetDllPathA(".\\dm2.dll",1);
	return  ;*/

}