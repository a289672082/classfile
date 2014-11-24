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
				/ *	ddd.Format("异常地址 adress: %0.8x  ,  跳转到: Eip: %0.8x",ExceptionInfo->ExceptionRecord->ExceptionAddress,T_NewProc[x]);
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



BOOL VEH_HOOK:: Initialize_Hardware_breakpoint_1(PVECTORED_EXCEPTION_HANDLER Handler)/*handle 函数原型 在上面*/

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
设置线程硬件断点
hThread:  线程句柄
dwAddr:    断点地址
dwDrIndex:  硬件寄存器(0~3)
nType:    断点类型(0:执行,1:读取,2:写入)
nLen:    读写断点数据长度(1,2,4)
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


		//将断点地址复制进入对应Dr寄存器(参考CONTEXT结构)
		memcpy(((BYTE *)&context)+4+dwDrIndex*4,&dwAddr,4);  

		//决定使用哪个寄存器
		dwDrFlags|=(DWORD)0x1<<(2*dwDrIndex);

		//见OD读写断点时 这个置位了,执行没有(置位也正常-_-)
		dwDrFlags|=0x100;


		//先将对应寄存器对应4个控制位清零(先或,再异或,还有其它好方法吗) =.= 悲催的小学生
		dwDrFlags|=(DWORD)0xF<<(16+4*dwDrIndex);
		dwDrFlags^=(DWORD)0xF<<(16+4*dwDrIndex);


		//设置断点类型,执行:00 读取:11 写入:01
		//(不知何故,测试时发现不论是11还是01,读写数据时均会断下来)
		if (nType==1)    
			dwDrFlags|=(DWORD)0x3<<(16+4*dwDrIndex);  //读取
		else if(nType==2)  
			dwDrFlags|=(DWORD)0x1<<(16+4*dwDrIndex);  //写入
		//else if(nType==0) 
		//dwDrFlags=dwDrFlags            //执行


		//设置读写断点时数据长度
		if (nType!=0)
		{
			if(nLen==2 && dwAddr%2==0)      
				dwDrFlags|=(DWORD)0x1<<(18+4*dwDrIndex);  //2字节
			else if(nLen==4  && dwAddr%4==0)  
				dwDrFlags|=(DWORD)0x3<<(18+4*dwDrIndex);  //4字节
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

	Context.ContextFlags =   CONTEXT_FULL|CONTEXT_DEBUG_REGISTERS;      // ＝ 位或 (#CONTEXT_FULL, #CONTEXT_DEBUG_REGISTERS)
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

	Context.ContextFlags =   CONTEXT_FULL|CONTEXT_DEBUG_REGISTERS;      // ＝ 位或 (#CONTEXT_FULL, #CONTEXT_DEBUG_REGISTERS)
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
* 函数名称 ： CloseObjectByThreadAdr
* 函数用途 ： 根据输入的线程地址后四位的16进制地址关闭此线程
* 输入参数 ：  线程地址后四位
* 返    回 ： 略
* 注    意 ： 只适用用于本进程。
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
		RR.Format("ID  %d",GetThreadIdByHandle((HANDLE)Handles->Information[i].Handle));
		::MessageBoxA(0,RR,RR,0);*/

	 
		Start_SetHardWareBP_3((HANDLE)Handles->Information[i].Handle);
 
	 





	}

	//释放申请的空间
	free(Handles);
	free(ObjName);

	return true;
}



DWORD  VEH_HOOK::GetThreadIdByHandle(HANDLE hThread)
{
	HMODULE hHanlde = GetModuleHandle("ntdll.dll");
	if(NULL == hHanlde)
	{
		//加载Ntdll.dll失败
		return false;
	}

	   _ZwQueruInfomationThread ZwQueruInfomationThread;
	//获取ZwQuerySystemInformation函数地址  
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