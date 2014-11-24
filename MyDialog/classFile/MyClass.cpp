#include "MyClass.h"



MyClass::MyClass()
{

}



MyClass::~MyClass()
{
	
}





DWORD   MyClass::GetThreadAdrByHandle(HANDLE  tidH)
{


	HINSTANCE hdll;
	NTSTATUS  status;
	ULONG     uAddr = 0;
	ULONG     uSize;

	_ZwQueruInfomationThread NtQueryInformationThread = 0;

	hdll    = LoadLibrary(TEXT("ntdll.dll"));
	NtQueryInformationThread = (_ZwQueruInfomationThread)GetProcAddress(hdll, 
		"NtQueryInformationThread");





	if (!tidH)  
	{  
		OutputDebugStringA("cant  open   thread");
		return 0;  
	}  

	DWORD dwStaAddr = NULL;  
	DWORD dwReturnLength = 0;  
	if(NtQueryInformationThread(tidH, ThreadQuerySetWin32StartAddress,  
		&dwStaAddr, sizeof(dwStaAddr), &dwReturnLength))  
	{  
		return 0;  
	}  

	return dwStaAddr;
}




/***********************************************************************************************
* 函数名称 ： CloseObjectByThreadAdr
* 函数用途 ： 根据输入的线程地址后四位的16进制地址关闭此线程
* 输入参数 ：  线程地址后四位
* 返    回 ： 略
* 注    意 ： 只适用用于本进程。
/**********************************************************************************************/
bool MyClass::CloseObjectByThreadAdr(DWORD  adr)
{
	int i;
	ULONG pid;
	ULONG ulSize;
	ULONG* pHandleInfor;
	CHAR pName[200];
	NTSTATUS ntStatus;
	HMODULE hHanlde;
	POBJECT_NAME_INFORMATION ObjName;
	PSYSTEM_HANDLE_INFORMATION_EX Handles;
	_NtQueryObject ZwQueryObject;
   NTQUERYSYSINFOMATION ZwQuerySystemInformation;


	//初始化变量
	ulSize = 0x4000;
	pHandleInfor = NULL;
	ZwQueryObject = NULL;
	ZwQuerySystemInformation =NULL;


	//由于ZwQueryObject和ZwQuerySystemInformation是未导出的函数，需要动态加载Ntdll,dll，然后通过函数GetProcAddress
	//得到它们的函数地址，由于这个dll一般的进程都会在创建的时候加载，所以省略加载，直接获取其模块地址
	hHanlde = GetModuleHandle("ntdll.dll");
	if(NULL == hHanlde)
	{
		//加载Ntdll.dll失败
		return false;
	}

	//获取ZwQuerySystemInformation函数地址  
	ZwQuerySystemInformation = (NTQUERYSYSINFOMATION)GetProcAddress(hHanlde, "ZwQuerySystemInformation");
	if(NULL == ZwQuerySystemInformation)
	{
		//获取ZwQuerySystemInformation函数地址失败
		return false;
	}

	//获取ZwQueryObject函数地址
	ZwQueryObject = (_NtQueryObject)GetProcAddress(hHanlde, "ZwQueryObject");
	if(NULL == ZwQueryObject)
	{
		//获取ZwQueryObject函数地址失败
		return false;
	}

	//获取系统所有句柄信息
	do
	{
		//申请内存
		pHandleInfor = (ULONG*)malloc(ulSize);
		if(NULL == pHandleInfor)
		{
			//申请内存失败
			return false;
		}

		ntStatus = ZwQuerySystemInformation( SystemHandleInformation, pHandleInfor, ulSize, NULL);    
		if(!NT_SUCCESS(ntStatus))
		{
			//空间不足继续申请。
			free(pHandleInfor);
			ulSize = ulSize * 2;  

			//为防止ZwQuerySystemInformation一直失败，程序陷入死循环，当申请的空间超过64M时则返回失败
			if(ulSize > 0x4000000)
			{
				return false;
			}
		}
	}while(!NT_SUCCESS(ntStatus));

	//转换数据结构类型
	Handles = (PSYSTEM_HANDLE_INFORMATION_EX)pHandleInfor;
	if(NULL == Handles)
	{
		return false;
	}

	//获取当前进程pid
	pid = GetCurrentProcessId();

	//申请空间，用于存储对象的名字信息
	ObjName =  (POBJECT_NAME_INFORMATION)malloc(0x2000 );

	//开始搜索获取的句柄信息，并对句柄对应的对象名进行比较，如果与要求关闭的名字相同，则关闭此句柄
	for(i = 0; i < Handles->NumberOfHandles; i++)
	{  

		//对于不是本进程的句柄对象，直接pass掉，如果要实现关闭其它进程的对象，则可以首先根据PID打开这个句柄所在的进程，
		//然后复制此对象，然后进行名字比较，如果相同，则可以通过创建远程线程的方式，关闭掉。
		if(pid != Handles->Information[i].ProcessId)
		{      
			continue;
		}
		if (Handles->Information[i].ObjectTypeNumber != 0x6)  //0x0d 信号量类型值
		{

			continue;
		}
		 
/*
		CAtlStringA  RR;
		RR.Format("ID  %d",::GetThreadId((HANDLE)Handles->Information[i].Handle));
		::MessageBoxA(0,RR,RR,0);*/

		
		tt1.Format(L"%X",GetThreadAdrByHandle((HANDLE)Handles->Information[i].Handle));
		tt2.Format(L"%X",adr);
		if (tt1.Find(tt2)!=-1)
		{

			TerminateThread((HANDLE)Handles->Information[i].Handle ,0);

		}





	}

	//释放申请的空间
	free(Handles);
	free(ObjName);

	return true;
}



/***********************************************************************************************
* 函数名称 ： CloseObjectByName
* 函数用途 ： 根据输入的对象名，将其关闭。
* 输入参数 ： char  *pObjectName 要关闭的对象名。  Type 对象的类型
* 返    回 ： 略
* 注    意 ： 只适用用于本进程。
/**********************************************************************************************/
bool MyClass::CloseObjectByName(char  *pObjectName,DWORD  Type)
{
	int i;
	ULONG pid;
	ULONG ulSize;
	ULONG* pHandleInfor;
	CHAR pName[200]={0};
	NTSTATUS ntStatus;
	HMODULE hHanlde;
	POBJECT_NAME_INFORMATION ObjName;
	PSYSTEM_HANDLE_INFORMATION_EX Handles;
	_NtQueryObject ZwQueryObject;
	NTQUERYSYSINFOMATION ZwQuerySystemInformation;


	//初始化变量
	ulSize = 0x4000;
	pHandleInfor = NULL;
	ZwQueryObject = NULL;
	ZwQuerySystemInformation =NULL;


	//由于ZwQueryObject和ZwQuerySystemInformation是未导出的函数，需要动态加载Ntdll,dll，然后通过函数GetProcAddress
	//得到它们的函数地址，由于这个dll一般的进程都会在创建的时候加载，所以省略加载，直接获取其模块地址
	hHanlde = GetModuleHandle("ntdll.dll");
	if(NULL == hHanlde)
	{
		//加载Ntdll.dll失败
		return false;
	}

	//获取ZwQuerySystemInformation函数地址  
	ZwQuerySystemInformation = (NTQUERYSYSINFOMATION)GetProcAddress(hHanlde, "ZwQuerySystemInformation");
	if(NULL == ZwQuerySystemInformation)
	{
		//获取ZwQuerySystemInformation函数地址失败
		return false;
	}

	//获取ZwQueryObject函数地址
	ZwQueryObject = (_NtQueryObject)GetProcAddress(hHanlde, "ZwQueryObject");
	if(NULL == ZwQueryObject)
	{
		//获取ZwQueryObject函数地址失败
		return false;
	}

	//获取系统所有句柄信息
	do
	{
		//申请内存
		pHandleInfor = (ULONG*)malloc(ulSize);
		if(NULL == pHandleInfor)
		{
			//申请内存失败
			return false;
		}

		ntStatus = ZwQuerySystemInformation( SystemHandleInformation, pHandleInfor, ulSize, NULL);    
		if(!NT_SUCCESS(ntStatus))
		{
			//空间不足继续申请。
			free(pHandleInfor);
			ulSize = ulSize * 2;  

			//为防止ZwQuerySystemInformation一直失败，程序陷入死循环，当申请的空间超过64M时则返回失败
			if(ulSize > 0x4000000)
			{
				return false;
			}
		}
	}while(!NT_SUCCESS(ntStatus));

	//转换数据结构类型
	Handles = (PSYSTEM_HANDLE_INFORMATION_EX)pHandleInfor;
	if(NULL == Handles)
	{
		return false;
	}

	//获取当前进程pid
	pid = GetCurrentProcessId();

	//申请空间，用于存储对象的名字信息
	ObjName =  (POBJECT_NAME_INFORMATION)malloc(0x2000 );

	//开始搜索获取的句柄信息，并对句柄对应的对象名进行比较，如果与要求关闭的名字相同，则关闭此句柄
	for(i = 0; i < Handles->NumberOfHandles; i++)
	{  

		//对于不是本进程的句柄对象，直接pass掉，如果要实现关闭其它进程的对象，则可以首先根据PID打开这个句柄所在的进程，
		//然后复制此对象，然后进行名字比较，如果相同，则可以通过创建远程线程的方式，关闭掉。
		if(pid != Handles->Information[i].ProcessId)
		{      
			continue;
		}
		if (Handles->Information[i].ObjectTypeNumber != Type)  //0x0d 信号量类型值
		{

			continue;
		}

		//获取这个对象的名字信息
		ntStatus = ZwQueryObject((HANDLE)Handles->Information[i].Handle, ObjectNameInformation, ObjName, 0x2000, NULL);
		if(!NT_SUCCESS(ntStatus))
		{
			//查询对象失败，进行下一个
			continue;
		}

		//将unicode 字串转换为 ansi字串
		WideCharToMultiByte(CP_ACP, 0, ObjName->Name.Buffer, -1, pName, 200, NULL, NULL);   
		
		if( 0 == strcmp(pName, pObjectName))
		{
			//找到对应名字的对象，将其关闭
			CloseHandle((HANDLE)Handles->Information[i].Handle);
		}
	}

	//释放申请的空间
	free(Handles);
	free(ObjName);

	return true;
}



/************************************************************************/
/* 重载模块 失败返回NULL    成功返回   CMemLoadDll*                     */
/************************************************************************/
CMemLoadDll*   MyClass::BeginMemReload(char* FilenameA)
{
	CMemLoadDll*  mem=new CMemLoadDll;
	 
	if (mem->ReloadFile(FilenameA)==FALSE)
	{
		return NULL;
	}
		
	return  mem;
}


/************************************************************************/
/* 功能:	 HOOK 32位系统的Kifastcall  并且初始化
* 返回值:	 失败返回 NULL
*说明:		返回HookSystemCall*指针  用指针调用InstallHook添加HOOK函数
* 示例  HookSystemCall.InstallHook("NtOpenFile",(DWORD)MyZwOpenFile,&OldNtOpenFile); 
/************************************************************************/
HookSystemCall*  MyClass::BeginHookSystenCall32()
{
	HookSystemCall*  hookA=new HookSystemCall;
	if ( hookA->Initialization()==FALSE)
	{
		return  NULL;
	}
	

	return  hookA;
}





/************************************************************************/
/* 功能:	 HOOK 64位系统的Kifastcall  并且初始化
* 返回值:	 失败返回 NULL
*说明:		返回HookSystemCall*指针  用指针调用InstallHook添加HOOK函数
* 示例  HookSystemCall.InstallHook("NtOpenFile",(DWORD)MyZwOpenFile,&OldNtOpenFile); 
	/************************************************************************/
HookSystemcallx86tox64*  MyClass::BeginHookSystenCall64()
{

	HookSystemcallx86tox64*  Hook64=new HookSystemcallx86tox64;
	Hook64->Initialization();
	return Hook64;
	 
}






/************************************************************************/
/*
*				判断是不是64位系统
*
*				是64位返回真														
 *//************************************************************************/
BOOL MyClass::IsWow64()
{
	BOOL bIsWow64 = FALSE;
	LPFN_ISWOW64PROCESS fnIsWow64Process=NULL;
	//IsWow64Process is not available on all supported versions of Windows.
	//Use GetModuleHandle to get a handle to the DLL that contains the function
	//and GetProcAddress to get a pointer to the function if available.

	fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
		GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

	if(NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
		{
			return FALSE;
		}
	}
	return bIsWow64;
}





void MyClass::EmunProcess( WCHAR*  ProcessName)
{ 

	NTQUERYSYSINFOMATION NtQuerySysInfoMation=(NTQUERYSYSINFOMATION)(GetProcAddress(LoadLibraryA("NTDLL.DLL"),"NtQuerySystemInformation")) ;
	if (NtQuerySysInfoMation==NULL)
	{
		//AfxMessageBox("获得系统接口失败！");
	}
	NTSTATUS Stas;
	DWORD size=16666;
	DWORD needsize=0;
	BYTE* buf;
	buf=new BYTE[size];
	int n=0;
	while(1)
	{



		Stas=NtQuerySysInfoMation(SystemProcessesAndThreadsInformation,buf,size,&needsize);
		if (!NT_SUCCESS(Stas))
		{
			if (Stas==STATUS_INFO_LENGTH_MISMATCH)
			{
				size=size*4;
				delete []buf;
				buf=new BYTE[size];//返回数据不足就重新申请
				//AfxMessageBox(L"数据长度不足！");
				continue;
			}else{
				delete []buf;//返回失败就释放内存
				return;
			}
		}

		if(NT_SUCCESS(Stas))//返回成功就退出循环进入下一轮
		{
			break;
		}
	}
	Stas=NtQuerySysInfoMation(SystemProcessesAndThreadsInformation,buf,size,&needsize);
	PSYSTEM_PROCESSES_INFORMATION PROINFO=(PSYSTEM_PROCESSES_INFORMATION)buf;
	while(PROINFO->NextEntryDelta!=0)
	{	

		if (PROINFO->ProcessName.Buffer!=NULL)
		{



			if (wcsstr(PROINFO->ProcessName.Buffer,ProcessName) !=NULL)
			{
				BOOL Is_has=FALSE;

				 
				if (Is_has==FALSE)
				{
			
					  
				 
				}
			}


/*
			m_processList.InsertItem(n,PROINFO->ProcessName.Buffer);
			proclass.pidforserch.Format(L"%d",PROINFO->ProcessId);
			m_processList.SetItemText(n,1,proclass.pidforserch);
			proclass.pidforserch.Format(L"%d",PROINFO->ThreadCount);
			m_processList.SetItemText(n,2,proclass.pidforserch);
			proclass.pidforserch.Format(L"%d",PROINFO->HandleCount);
			m_processList.SetItemText(n,3,proclass.pidforserch);
			proclass.pidforserch.Format(L"%d",PROINFO->InheritedFromProcessId);
			m_processList.SetItemText(n,4,proclass.pidforserch);*/
		}


		PROINFO=(PSYSTEM_PROCESSES_INFORMATION)((DWORD)PROINFO+PROINFO->NextEntryDelta);


	}

	delete []buf;//删除缓冲区

}
 












 HWND  WND_TMP=0;
 DWORD   PID_TMP=0;
BOOL CALLBACK EnumWindowsProc(
	HWND hwnd,      // handle to parent window
	LPARAM lParam   // application-defined value
	){
	 
		DWORD PID;
		BOOL  Result=TRUE;
		GetWindowThreadProcessId(hwnd,&PID);
		if (PID=PID_TMP)
		{
			WND_TMP = hwnd;//这个g_hwin在你的DLL里定义为一个全局的HWND,也是你想要的句柄
			Result = FALSE;
		}
		return Result;
}


HWND   GetWindowByProcessID(DWORD  PID_)
{
	PID_TMP=PID_;
   EnumWindows(EnumWindowsProc,0);
   return WND_TMP;
}
