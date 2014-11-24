#include "stdafx.h"
#include "ImeInject.h"
#include <imm.h>
#include <tlhelp32.h>
#pragma comment(lib,"imm32.lib")

#pragma warning( disable: 4005 )
#pragma warning( disable: 4102 )
#pragma warning( disable: 4101 )
#pragma warning( disable: 4305 )
#pragma warning( disable: 4312 )
#pragma warning( disable: 4311 )
#pragma warning( disable: 4244 )
#pragma warning( disable: 4267 )
#pragma warning( disable: 4996 )
#pragma warning( disable: 4533 )
#pragma warning( disable: 4700 )

typedef int  (WINAPI  *g_IMEClearPubString)();

typedef int  (WINAPI  *g_IMESetPubString)(PTCHAR tmpStr,DWORD UnloadDLL,DWORD loadNextIme,DWORD DllData1,DWORD DllData2,DWORD DllData3);

g_IMEClearPubString IMEClearPubString = NULL;

g_IMESetPubString IMESetPubString = NULL;

HKL InputHandle = NULL;

HKL oldInputHandle = NULL;

TCHAR ImeSymbol[255];

HINSTANCE hModule = NULL;

typedef void (__stdcall* _SetPid)(DWORD pid);
_SetPid  SetPid=NULL;
BOOL ImeInstallEx(CString lpszdllName)
{
	char szPath[255] = {0};
	GetModuleFileName(NULL,szPath,255);
	CString strPath;
	strPath.Format(_T("%s"),szPath);
	strPath.Delete(strPath.ReverseFind('\\') + 1,strPath.GetLength());
	strPath += lpszdllName;
	//AfxMessageBox(strPath);
	::SystemParametersInfo(SPI_GETDEFAULTINPUTLANG,NULL,oldInputHandle,NULL);

	

	hModule = LoadLibrary("C:\\WINDOWS\\SYSTEM32\\free.ime"/*"C:\\WINDOWS\\SYSTEM32\\free.ime"*/); 
/*

	SetPid=(_SetPid)GetProcAddress(hModule,"SetPid");
	if (SetPid==NULL)
	{
		AfxMessageBox("输入法未加载");
		return FALSE;
	}*/
	InputHandle = ImmInstallIME("C:\\WINDOWS\\SYSTEM32\\free.ime","沫、D输入法225");/*沫、D输入法1.1234*/

	//获取输入法标识符
	
	GetImeHandleString();
 
	return TRUE;
}

BOOL ImeUnInstallEx()
{
	HKL handle;

	QuitImeSystemDefault(oldInputHandle);

	SetAllWindowActiv(oldInputHandle);

	if (InputHandle != NULL)
	{
		//卸载输入法
		UnloadKeyboardLayout(InputHandle);
	}
	else
	{
		HKL imehandle = EnumIme("沫、D输入法225","C:\\WINDOWS\\SYSTEM32\\free.ime");

		if (imehandle != NULL)
		{
			UnloadKeyboardLayout(imehandle);
		} 
		else
		{
			//AfxMessageBox("1");
			return FALSE;
		}
	} 

	if (ImeSymbol != "")
	{
		ImedeleteReg();
	}	

	FreeLibrary(hModule);

	return TRUE;
}

BOOL ImeStopEx()
{
	if (hModule)
	{
		IMEClearPubString = (g_IMEClearPubString)GetProcAddress(hModule,"IMEClearPubString"); 

		if (IMEClearPubString)
		{
			IMEClearPubString();
		}
		else
		{
			FreeLibrary(hModule);
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK  EnumChildProc_IME(HWND hWnd,LPARAM lParam)
{
 
	::PostMessage(hWnd,WM_INPUTLANGCHANGEREQUEST,0x1,(LPARAM)lParam);
	::PostMessage(hWnd,WM_INPUTLANGCHANGE,0x1,(LPARAM)lParam); 
	return true;
}
BOOL IMEActivEx(HWND hWnd)
{

/*	hModule = LoadLibrary("C:\\WINDOWS\\SYSTEM32\\free.ime"); 


	SetPid=(_SetPid)GetProcAddress(hModule,"SetPid");
	 
	DWORD pidd;
	GetWindowThreadProcessId(hWnd,&pidd);
	SetPid(pidd);*/
	if (InputHandle != NULL)
	{
		//激活指定窗口输入法
		::PostMessage(hWnd,WM_INPUTLANGCHANGEREQUEST,0x1,(LPARAM)InputHandle);
		::PostMessage(hWnd,WM_INPUTLANGCHANGE,0x1,(LPARAM)InputHandle); 
		::EnumChildWindows(hWnd,EnumChildProc_IME,(LPARAM)InputHandle);

	} 
	else
	{
		//句柄不存在，枚举输入法句柄，激活
		HKL imehandle = EnumIme("沫、D输入法225","C:\\WINDOWS\\SYSTEM32\\free.ime");
		if (imehandle != NULL)
		{
			::EnumChildWindows(hWnd,EnumChildProc_IME,(LPARAM)imehandle);
			::PostMessage(hWnd,WM_INPUTLANGCHANGEREQUEST,0x1,(LPARAM)imehandle);
		}
		else
		{
				AfxMessageBox("2");
			return FALSE;
		}
	}

	return TRUE;
}

void QuitImeSystemDefault(HKL imehandle)
{
	HKL retV = NULL;

	::SystemParametersInfo(SPI_GETDEFAULTINPUTLANG,0,&retV,0);

	if (retV != imehandle)
	{
		::SystemParametersInfo(SPI_SETDEFAULTINPUTLANG,0,imehandle,SPIF_SENDWININICHANGE);
	}
}

HKL EnumIme(CString InputName,CString FileName)
{
	HKL *HKLList;

	HKL Imehandle=NULL;

	int StrCount=0,FileCount=0;

	HKLList = NULL;

	UINT uCount = GetKeyboardLayoutList(0, NULL);

	if (0 != uCount)
	{
		HKLList = new HKL[uCount];

		GetKeyboardLayoutList(uCount, HKLList);

		TRACE("GetKeyboardLayoutList OK!!\n");
	}
	else
	{
		int nErr = GetLastError();

		TRACE("Error is %d\n", nErr);
	}

	CString strLayoutText;

	CString strFileText;

	CString InputString;

	CString InputFile;

	for (UINT i = 0; i < uCount; i++)
	{
		//取得输入法名
		StrCount = ImmGetDescription(HKLList[i], strLayoutText.GetBuffer(256), 256);

		InputString = strLayoutText.Left(StrCount);

		if (InputString == InputName)
		{
			FileCount = ImmGetIMEFileName(HKLList[i], strFileText.GetBuffer(256), 256);

			InputFile = strFileText.Left(FileCount);

			if (InputFile = FileName)
			{
				Imehandle = HKLList[i];

				break;
			}
		}	
	}
	delete[]HKLList;

	return Imehandle;
}

void SetAllWindowActiv(HKL imehandle)
{
	HWND mhWnd = NULL;

	do 
	{
		mhWnd = ::FindWindowExA(NULL,mhWnd,NULL,NULL);

		if (mhWnd != NULL)
		{
			::PostMessage(mhWnd,WM_INPUTLANGCHANGEREQUEST,0x1,(LPARAM)imehandle);
		}
	} while (mhWnd == NULL);
}

void GetImeHandleString()
{
	//获得指定线程的活动键盘布局
	HKL iHandle = GetKeyboardLayout(NULL);

	//激活新输入法键盘布局
	::ActivateKeyboardLayout(InputHandle,NULL);
	//获取输入法键盘布局
	::GetKeyboardLayoutName(ImeSymbol);
	//激活原来活动键盘布局
	::ActivateKeyboardLayout (iHandle,NULL);
}

void ImedeleteReg()
{
	HKEY phkResult;

	int i = NULL;

	TCHAR ValueName[255] = {0};  //存储得到的键值名

	TCHAR lpData[255] = {0};     //存储得到的键值数据

	DWORD lenValue = 255;  //存储键值的数据长度

	DWORD lenData = 255;   //存储键值的数据长度

	//打开注册表项目，获取句柄
	RegOpenKey(HKEY_CURRENT_USER,"Keyboard Layout\\Preload",&phkResult);

	//枚举注册表项目
	while(RegEnumValue (phkResult,i,ValueName,&lenValue,NULL,NULL,(LPBYTE)lpData,&lenData) != ERROR_NO_MORE_ITEMS)
	{
		if (lenData != NULL)
		{
			if (_tcscmp(ImeSymbol,lpData)==NULL)
			{
				RegDeleteValue (phkResult,ValueName);//删除项目数值
				break;
			}
		}

		//必须重新设置变量长度与变量数据为空，否则会造成数据不全 如：E0200804 不全为：0000804

		lpData[255] = NULL;

		ValueName[255] = NULL;

		lenValue = 255; 

		lenData = 255;

		i++;
	}
}

BOOL InitGameData( CString strGameExeName,HWND &GameHwnd,DWORD &GameThreadID,DWORD &GameProcessID )
{
	CString strGameName;
	strGameName=strGameExeName;
	strGameName.MakeLower();
	HANDLE hCreateSnap32;
	hCreateSnap32=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 GameProcessPe;
	GameProcessPe.dwSize=sizeof(PROCESSENTRY32);
	BOOL bProcessIsOpen=Process32First(hCreateSnap32,&GameProcessPe);
	while (bProcessIsOpen)
	{
		CString strGameFind;
		strGameFind=GameProcessPe.szExeFile;
		strGameFind.MakeLower();
		if (strGameFind==strGameName)
		{
			DWORD Pid=GameProcessPe.th32ProcessID;
			GameProcessID=Pid;
			CWnd* pFindWnd=NULL;
			pFindWnd=CWnd::GetDesktopWindow();
			CWnd* pGameWnd=pFindWnd->GetWindow(GW_CHILD);
			while(*pGameWnd)
			{
				DWORD dwPid,dwTid;
				dwTid=GetWindowThreadProcessId(pGameWnd->GetSafeHwnd(),&dwPid);
				if (dwPid==Pid)
				{
					GameHwnd=pGameWnd->GetSafeHwnd();
					CString str;
					::GetWindowText(pGameWnd->GetSafeHwnd(),str.GetBuffer(256),256);
					str.ReleaseBuffer();
					GameThreadID=dwTid;
					return TRUE;
				}
				pGameWnd=pGameWnd-> GetWindow(GW_HWNDNEXT);
			}

		}
		bProcessIsOpen=Process32Next(hCreateSnap32,&GameProcessPe);
	}
	return FALSE;
}
