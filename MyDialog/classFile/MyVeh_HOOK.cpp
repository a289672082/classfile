#include "MyVeh_HOOK.h"
#include "Common.h"
#include <WinNT.h>
VEH_HOOK::VEH_HOOK()
{



}



VEH_HOOK::~VEH_HOOK()
{

}



/*
LONG NTAPI ExceptionHandler(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
	 

	if (ExceptionInfo->ContextRecord!=0  && ExceptionInfo->ExceptionRecord->ExceptionAddress!=0)
	{
		if (ExceptionInfo->ContextRecord!=0)
		{
			for (int x=0;x<4;x++)
			{
				if (ExceptionInfo->ExceptionRecord->ExceptionAddress==(LPVOID)T_OrgProc[x])
				{
				/ *	ddd.Format("�쳣��ַ adress: %0.8x  ,  ��ת��: Eip: %0.8x",ExceptionInfo->ExceptionRecord->ExceptionAddress,T_NewProc[x]);
					OutputDebugStringA(ddd);* /
				 
					 ExceptionInfo->ContextRecord->Eip= T_NewProc[x];
	 
					//Stop();
					return EXCEPTION_CONTINUE_EXECUTION;

				}
			}
		}
	}

	OutputDebugStringA("IN ");
	return EXCEPTION_CONTINUE_SEARCH;
}*/



BOOL VEH_HOOK:: Initialize_Hardware_breakpoint_1(PVECTORED_EXCEPTION_HANDLER Handler)/*handle ����ԭ�� ������*/

{

	memset(T_OrgProc,0,4*4);
	memset(T_NewProc,0,4*4);



	for (int x=0;x<4;x++)
	{
		 
			T_OrgProc[x]=0;
			T_NewProc[x]=0;
 
	}

	DWORD  Ret= (DWORD)AddVectoredExceptionHandler(1,Handler);
	if (Ret <=0)
	{
		OutputDebugStringA( "Myclass ERRO Initialize_Hardware_breakpoint_1");
	}
	return  Ret>0?1:0;
}





void VEH_HOOK::AddHook_Hardware_breakpoint_2(DWORD OrgProc, DWORD NewProc)
{


	for (int x=0;x<4;x++)
	{
		if (T_OrgProc[x]==0)
		{
			T_OrgProc[x]=OrgProc;
			T_NewProc[x]=NewProc;
			return ;
		}
	}


	return ;
}




/************************************************************************
SetHardWareBP:
�����߳�Ӳ���ϵ�
hThread:  �߳̾��
dwAddr:    �ϵ��ַ
dwDrIndex:  Ӳ���Ĵ���(0~3)
nType:    �ϵ�����(0:ִ��,1:��ȡ,2:д��)
nLen:    ��д�ϵ����ݳ���(1,2,4)
/************************************************************************/

BOOL VEH_HOOK::SetHardWareBP(HANDLE hThread,DWORD dwAddr,DWORD dwDrIndex,UINT nType,UINT nLen)
{
	BOOL bResult=FALSE;
	BOOL Isself=TRUE;

	CONTEXT context = {0};
	context.ContextFlags=CONTEXT_DEBUG_REGISTERS;
	if (::GetCurrentThreadId()!= GetThreadIdByHandle(hThread))
	{

		Isself=FALSE;
		::SuspendThread(hThread);
	}
	 
	if(::GetThreadContext(hThread,&context))
	{
		DWORD dwDrFlags=context.Dr7;


		//���ϵ��ַ���ƽ����ӦDr�Ĵ���(�ο�CONTEXT�ṹ)
		memcpy(((BYTE *)&context)+4+dwDrIndex*4,&dwAddr,4);  

		//����ʹ���ĸ��Ĵ���
		dwDrFlags|=(DWORD)0x1<<(2*dwDrIndex);

		//��OD��д�ϵ�ʱ �����λ��,ִ��û��(��λҲ����-_-)
		dwDrFlags|=0x100;


		//�Ƚ���Ӧ�Ĵ�����Ӧ4������λ����(�Ȼ�,�����,���������÷�����) =.= ���ߵ�Сѧ��
		dwDrFlags|=(DWORD)0xF<<(16+4*dwDrIndex);
		dwDrFlags^=(DWORD)0xF<<(16+4*dwDrIndex);


		//���öϵ�����,ִ��:00 ��ȡ:11 д��:01
		//(��֪�ι�,����ʱ���ֲ�����11����01,��д����ʱ���������)
		if (nType==1)    
			dwDrFlags|=(DWORD)0x3<<(16+4*dwDrIndex);  //��ȡ
		else if(nType==2)  
			dwDrFlags|=(DWORD)0x1<<(16+4*dwDrIndex);  //д��
		//else if(nType==0) 
		//dwDrFlags=dwDrFlags            //ִ��


		//���ö�д�ϵ�ʱ���ݳ���
		if (nType!=0)
		{
			if(nLen==2 && dwAddr%2==0)      
				dwDrFlags|=(DWORD)0x1<<(18+4*dwDrIndex);  //2�ֽ�
			else if(nLen==4  && dwAddr%4==0)  
				dwDrFlags|=(DWORD)0x3<<(18+4*dwDrIndex);  //4�ֽ�
		}
 
		context.Dr7=/*1029*/dwDrFlags;
		
		context.ContextFlags=CONTEXT_DEBUG_REGISTERS;
		if (::SetThreadContext(hThread,&context)) 
		{ 
		   
			bResult=TRUE;
		}
	 	if (Isself==FALSE)
		{
				ResumeThread(hThread);
		} 
		
		
		
	}

	if (bResult==FALSE)
	{
		OutputDebugStringA( "Myclass ERRO SetHardWareBP");
	}
	return bResult;
}



void  VEH_HOOK:: Start_SetHardWareBP_3( HANDLE  threadHandle )
{


	for (int x=0;x<4;x++)
	{
		SetHardWareBP(threadHandle,T_OrgProc[x],x);
	}





}







void VEH_HOOK::Start(  )
{

	CONTEXT Context={0};

	Context.ContextFlags =   CONTEXT_FULL|CONTEXT_DEBUG_REGISTERS;      // �� λ�� (#CONTEXT_FULL, #CONTEXT_DEBUG_REGISTERS)
	GetThreadContext (GetCurrentThread (), &Context);
	Context.Dr0 = T_OrgProc [0];
	Context.Dr1 = T_OrgProc [1]  ;
	Context.Dr2 = T_OrgProc [2];
	Context.Dr3 = T_OrgProc [3];
	Context.Dr7 = 1029;

	SetThreadContext (GetCurrentThread (), &Context);

}


void VEH_HOOK::Stop()
{

	CONTEXT Context={0};

	Context.ContextFlags =   CONTEXT_FULL|CONTEXT_DEBUG_REGISTERS;      // �� λ�� (#CONTEXT_FULL, #CONTEXT_DEBUG_REGISTERS)
	if (GetThreadContext (GetCurrentThread (), &Context)==FALSE)
	{
		OutputDebugStringA("erro  Stop1");
	}

	Context.Dr0 =0;
	Context.Dr1 = 0 ;
	Context.Dr2 =0;
	Context.Dr3 =0;
	Context.Dr7 = 0;
	SetThreadContext (GetCurrentThread (), &Context);
}










/***********************************************************************************************
* �������� �� CloseObjectByThreadAdr
* ������; �� ����������̵߳�ַ����λ��16���Ƶ�ַ�رմ��߳�
* ������� ��  �̵߳�ַ����λ
* ��    �� �� ��
* ע    �� �� ֻ�������ڱ����̡�
/**********************************************************************************************/
bool VEH_HOOK::Start_SetHardWareBP_3_AllThread()
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
		RR.Format("ID  %d",GetThreadIdByHandle((HANDLE)Handles->Information[i].Handle));
		::MessageBoxA(0,RR,RR,0);*/

	 
		Start_SetHardWareBP_3((HANDLE)Handles->Information[i].Handle);
 
	 





	}

	//�ͷ�����Ŀռ�
	free(Handles);
	free(ObjName);

	return true;
}



DWORD  VEH_HOOK::GetThreadIdByHandle(HANDLE hThread)
{
	HMODULE hHanlde = GetModuleHandle("ntdll.dll");
	if(NULL == hHanlde)
	{
		//����Ntdll.dllʧ��
		return false;
	}

	   _ZwQueruInfomationThread ZwQueruInfomationThread;
	//��ȡZwQuerySystemInformation������ַ  
	  ZwQueruInfomationThread = (_ZwQueruInfomationThread)GetProcAddress(hHanlde, "NtQueryInformationThread");

	THREAD_BASIC_INFORMATION threadBasicInfo;
	LONG status = ZwQueruInfomationThread(hThread, ThreadBasicInformation, &threadBasicInfo,sizeof(threadBasicInfo), NULL);


	return (DWORD)threadBasicInfo.ClientId.UniqueThread;
/*
	_tprintf   (TEXT("process ID is %u\n"), threadBasicInfo.ClientId.UniqueProcess);  
	_tprintf   (TEXT("Thread ID is %u\n"),  threadBasicInfo.ClientId.UniqueThread);  
	_tprintf   (TEXT("TEB is 0x%p\n"),threadBasicInfo.TebBaseAddress);

	return TRUE;*/
}