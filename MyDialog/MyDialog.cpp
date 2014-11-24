
// MyDialog.cpp : ����Ӧ�ó��������Ϊ��
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


//����Ҫ�ĺ���, ����Dump
static void DumpMiniDump(PEXCEPTION_POINTERS excpInfo)
{

	HANDLE hFile = CreateFile( (".\\�����������ļ�.dmp"), GENERIC_READ | GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 
	OutputDebugString(("writing minidump\r\n"));
	MINIDUMP_EXCEPTION_INFORMATION eInfo;
	eInfo.ThreadId = GetCurrentThreadId(); //����Ҫ����Ϣ���ȥ
	eInfo.ExceptionPointers = excpInfo;
	eInfo.ClientPointers = FALSE;

	// ����, ����Dump. 98��֧��
	// Dump��������С�͵�, ��ʡ�ռ�. ���Բο�MSDN���ɸ���ϸ��Dump.
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


// CMyDialogApp ����

CMyDialogApp::CMyDialogApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMyDialogApp ����

CMyDialogApp theApp;


// CMyDialogApp ��ʼ��

BOOL CMyDialogApp::InitInstance()
{
 	IsEndGame = false;
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

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
	//��¼�õĴ�Į

	InitDM();
	dm_denglu.Init();
	dm_denglu.MyReg();
	CMyDialogDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
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
		AfxMessageBox("��ȡ��ע�ắ��ʧ�ܣ�");
		return   ;
	}

	SetDllPathA(".\\dm2.dll",1);*/
	return  ;
/*
	HMODULE hSetDllPathA =LoadLibraryA(".\\DmReg.dll");
	SetDllPathA=(_SetDllPathA )GetProcAddress(hSetDllPathA,"SetDllPathA");

	if (SetDllPathA==NULL)
	{
		AfxMessageBox("��ȡ��ע�ắ��ʧ�ܣ�");
		return   ;
	}

	SetDllPathA(".\\dm2.dll",1);
	return  ;*/

}