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
* �������� �� CloseObjectByThreadAdr
* ������; �� ����������̵߳�ַ����λ��16���Ƶ�ַ�رմ��߳�
* ������� ��  �̵߳�ַ����λ
* ��    �� �� ��
* ע    �� �� ֻ�������ڱ����̡�
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


	//��ʼ������
	ulSize = 0x4000;
	pHandleInfor = NULL;
	ZwQueryObject = NULL;
	ZwQuerySystemInformation =NULL;


	//����ZwQueryObject��ZwQuerySystemInformation��δ�����ĺ�������Ҫ��̬����Ntdll,dll��Ȼ��ͨ������GetProcAddress
	//�õ����ǵĺ�����ַ���������dllһ��Ľ��̶����ڴ�����ʱ����أ�����ʡ�Լ��أ�ֱ�ӻ�ȡ��ģ���ַ
	hHanlde = GetModuleHandle("ntdll.dll");
	if(NULL == hHanlde)
	{
		//����Ntdll.dllʧ��
		return false;
	}

	//��ȡZwQuerySystemInformation������ַ  
	ZwQuerySystemInformation = (NTQUERYSYSINFOMATION)GetProcAddress(hHanlde, "ZwQuerySystemInformation");
	if(NULL == ZwQuerySystemInformation)
	{
		//��ȡZwQuerySystemInformation������ַʧ��
		return false;
	}

	//��ȡZwQueryObject������ַ
	ZwQueryObject = (_NtQueryObject)GetProcAddress(hHanlde, "ZwQueryObject");
	if(NULL == ZwQueryObject)
	{
		//��ȡZwQueryObject������ַʧ��
		return false;
	}

	//��ȡϵͳ���о����Ϣ
	do
	{
		//�����ڴ�
		pHandleInfor = (ULONG*)malloc(ulSize);
		if(NULL == pHandleInfor)
		{
			//�����ڴ�ʧ��
			return false;
		}

		ntStatus = ZwQuerySystemInformation( SystemHandleInformation, pHandleInfor, ulSize, NULL);    
		if(!NT_SUCCESS(ntStatus))
		{
			//�ռ䲻��������롣
			free(pHandleInfor);
			ulSize = ulSize * 2;  

			//Ϊ��ֹZwQuerySystemInformationһֱʧ�ܣ�����������ѭ����������Ŀռ䳬��64Mʱ�򷵻�ʧ��
			if(ulSize > 0x4000000)
			{
				return false;
			}
		}
	}while(!NT_SUCCESS(ntStatus));

	//ת�����ݽṹ����
	Handles = (PSYSTEM_HANDLE_INFORMATION_EX)pHandleInfor;
	if(NULL == Handles)
	{
		return false;
	}

	//��ȡ��ǰ����pid
	pid = GetCurrentProcessId();

	//����ռ䣬���ڴ洢�����������Ϣ
	ObjName =  (POBJECT_NAME_INFORMATION)malloc(0x2000 );

	//��ʼ������ȡ�ľ����Ϣ�����Ծ����Ӧ�Ķ��������бȽϣ������Ҫ��رյ�������ͬ����رմ˾��
	for(i = 0; i < Handles->NumberOfHandles; i++)
	{  

		//���ڲ��Ǳ����̵ľ������ֱ��pass�������Ҫʵ�ֹر��������̵Ķ�����������ȸ���PID�����������ڵĽ��̣�
		//Ȼ���ƴ˶���Ȼ��������ֱȽϣ������ͬ�������ͨ������Զ���̵߳ķ�ʽ���رյ���
		if(pid != Handles->Information[i].ProcessId)
		{      
			continue;
		}
		if (Handles->Information[i].ObjectTypeNumber != 0x6)  //0x0d �ź�������ֵ
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

	//�ͷ�����Ŀռ�
	free(Handles);
	free(ObjName);

	return true;
}



/***********************************************************************************************
* �������� �� CloseObjectByName
* ������; �� ��������Ķ�����������رա�
* ������� �� char  *pObjectName Ҫ�رյĶ�������  Type ���������
* ��    �� �� ��
* ע    �� �� ֻ�������ڱ����̡�
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


	//��ʼ������
	ulSize = 0x4000;
	pHandleInfor = NULL;
	ZwQueryObject = NULL;
	ZwQuerySystemInformation =NULL;


	//����ZwQueryObject��ZwQuerySystemInformation��δ�����ĺ�������Ҫ��̬����Ntdll,dll��Ȼ��ͨ������GetProcAddress
	//�õ����ǵĺ�����ַ���������dllһ��Ľ��̶����ڴ�����ʱ����أ�����ʡ�Լ��أ�ֱ�ӻ�ȡ��ģ���ַ
	hHanlde = GetModuleHandle("ntdll.dll");
	if(NULL == hHanlde)
	{
		//����Ntdll.dllʧ��
		return false;
	}

	//��ȡZwQuerySystemInformation������ַ  
	ZwQuerySystemInformation = (NTQUERYSYSINFOMATION)GetProcAddress(hHanlde, "ZwQuerySystemInformation");
	if(NULL == ZwQuerySystemInformation)
	{
		//��ȡZwQuerySystemInformation������ַʧ��
		return false;
	}

	//��ȡZwQueryObject������ַ
	ZwQueryObject = (_NtQueryObject)GetProcAddress(hHanlde, "ZwQueryObject");
	if(NULL == ZwQueryObject)
	{
		//��ȡZwQueryObject������ַʧ��
		return false;
	}

	//��ȡϵͳ���о����Ϣ
	do
	{
		//�����ڴ�
		pHandleInfor = (ULONG*)malloc(ulSize);
		if(NULL == pHandleInfor)
		{
			//�����ڴ�ʧ��
			return false;
		}

		ntStatus = ZwQuerySystemInformation( SystemHandleInformation, pHandleInfor, ulSize, NULL);    
		if(!NT_SUCCESS(ntStatus))
		{
			//�ռ䲻��������롣
			free(pHandleInfor);
			ulSize = ulSize * 2;  

			//Ϊ��ֹZwQuerySystemInformationһֱʧ�ܣ�����������ѭ����������Ŀռ䳬��64Mʱ�򷵻�ʧ��
			if(ulSize > 0x4000000)
			{
				return false;
			}
		}
	}while(!NT_SUCCESS(ntStatus));

	//ת�����ݽṹ����
	Handles = (PSYSTEM_HANDLE_INFORMATION_EX)pHandleInfor;
	if(NULL == Handles)
	{
		return false;
	}

	//��ȡ��ǰ����pid
	pid = GetCurrentProcessId();

	//����ռ䣬���ڴ洢�����������Ϣ
	ObjName =  (POBJECT_NAME_INFORMATION)malloc(0x2000 );

	//��ʼ������ȡ�ľ����Ϣ�����Ծ����Ӧ�Ķ��������бȽϣ������Ҫ��رյ�������ͬ����رմ˾��
	for(i = 0; i < Handles->NumberOfHandles; i++)
	{  

		//���ڲ��Ǳ����̵ľ������ֱ��pass�������Ҫʵ�ֹر��������̵Ķ�����������ȸ���PID�����������ڵĽ��̣�
		//Ȼ���ƴ˶���Ȼ��������ֱȽϣ������ͬ�������ͨ������Զ���̵߳ķ�ʽ���رյ���
		if(pid != Handles->Information[i].ProcessId)
		{      
			continue;
		}
		if (Handles->Information[i].ObjectTypeNumber != Type)  //0x0d �ź�������ֵ
		{

			continue;
		}

		//��ȡ��������������Ϣ
		ntStatus = ZwQueryObject((HANDLE)Handles->Information[i].Handle, ObjectNameInformation, ObjName, 0x2000, NULL);
		if(!NT_SUCCESS(ntStatus))
		{
			//��ѯ����ʧ�ܣ�������һ��
			continue;
		}

		//��unicode �ִ�ת��Ϊ ansi�ִ�
		WideCharToMultiByte(CP_ACP, 0, ObjName->Name.Buffer, -1, pName, 200, NULL, NULL);   
		
		if( 0 == strcmp(pName, pObjectName))
		{
			//�ҵ���Ӧ���ֵĶ��󣬽���ر�
			CloseHandle((HANDLE)Handles->Information[i].Handle);
		}
	}

	//�ͷ�����Ŀռ�
	free(Handles);
	free(ObjName);

	return true;
}



/************************************************************************/
/* ����ģ�� ʧ�ܷ���NULL    �ɹ�����   CMemLoadDll*                     */
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
/* ����:	 HOOK 32λϵͳ��Kifastcall  ���ҳ�ʼ��
* ����ֵ:	 ʧ�ܷ��� NULL
*˵��:		����HookSystemCall*ָ��  ��ָ�����InstallHook���HOOK����
* ʾ��  HookSystemCall.InstallHook("NtOpenFile",(DWORD)MyZwOpenFile,&OldNtOpenFile); 
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
/* ����:	 HOOK 64λϵͳ��Kifastcall  ���ҳ�ʼ��
* ����ֵ:	 ʧ�ܷ��� NULL
*˵��:		����HookSystemCall*ָ��  ��ָ�����InstallHook���HOOK����
* ʾ��  HookSystemCall.InstallHook("NtOpenFile",(DWORD)MyZwOpenFile,&OldNtOpenFile); 
	/************************************************************************/
HookSystemcallx86tox64*  MyClass::BeginHookSystenCall64()
{

	HookSystemcallx86tox64*  Hook64=new HookSystemcallx86tox64;
	Hook64->Initialization();
	return Hook64;
	 
}






/************************************************************************/
/*
*				�ж��ǲ���64λϵͳ
*
*				��64λ������														
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
		//AfxMessageBox("���ϵͳ�ӿ�ʧ�ܣ�");
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
				buf=new BYTE[size];//�������ݲ������������
				//AfxMessageBox(L"���ݳ��Ȳ��㣡");
				continue;
			}else{
				delete []buf;//����ʧ�ܾ��ͷ��ڴ�
				return;
			}
		}

		if(NT_SUCCESS(Stas))//���سɹ����˳�ѭ��������һ��
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

	delete []buf;//ɾ��������

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
			WND_TMP = hwnd;//���g_hwin�����DLL�ﶨ��Ϊһ��ȫ�ֵ�HWND,Ҳ������Ҫ�ľ��
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
