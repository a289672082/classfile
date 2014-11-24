#ifndef  VEH_HOOK1
#include <Windows.h>
class VEH_HOOK
{
public:
	VEH_HOOK();
	~VEH_HOOK();
/************************************************************************/
/* 执行顺序  标号 1  2  3                                             */
/************************************************************************/

	int  T_OrgProc[4];//硬件断点用的  4个原始地址 要HOOK的地址
	int  T_NewProc[4];//硬件断点用的  4个原始地址 新的地址
	BOOL  Initialize_Hardware_breakpoint_1(PVECTORED_EXCEPTION_HANDLER Handler);
	void AddHook_Hardware_breakpoint_2(DWORD OrgProc, DWORD NewProc);
	void Start_SetHardWareBP_3( HANDLE  threadHandle );
	bool Start_SetHardWareBP_3_AllThread();
	BOOL SetHardWareBP(HANDLE hThread,DWORD dwAddr,DWORD dwDrIndex=0,UINT nType=0,UINT nLen=4);
	void Start();
	void Stop();



	/************************************************************************/
	/*                    通过线程句柄获取它的线程ID                                                  */
	/************************************************************************/
	DWORD  GetThreadIdByHandle(HANDLE hThread);
protected:
	
private:
};






#define   VEH_HOOK1
#endif


/************************************************************************/
/*                             

				示例:异常处理函数
 LONG NTAPI ExceptionHandler(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
	 

	if (ExceptionInfo->ContextRecord!=0  && ExceptionInfo->ExceptionRecord->ExceptionAddress!=0)
	{
		if (ExceptionInfo->ContextRecord!=0)
		{
			for (int x=0;x<4;x++)
			{
				if (ExceptionInfo->ExceptionRecord->ExceptionAddress==(LPVOID)veh_Hook1.T_OrgProc[x])
				{
				 
				 
					 ExceptionInfo->ContextRecord->Eip= veh_Hook1.T_NewProc[x];
	 
					//Stop();
					return EXCEPTION_CONTINUE_EXECUTION;

				}
			}
		}
	}

	OutputDebugStringA("IN ");
	return EXCEPTION_CONTINUE_SEARCH;
}



调用:



veh_Hook1.Initialize_Hardware_breakpoint_1(ExceptionHandler);
veh_Hook1.AddHook_Hardware_breakpoint_2((DWORD)::MessageBoxA,(DWORD)Mymsg);
HANDLE th1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)The1,NULL,0,NULL);
veh_Hook1.Start_SetHardWareBP_3(th1);


DWORD WINAPI The1(LPVOID)
{ 
while(1)
{
Sleep(500);
MessageBoxA(0,"1","1",0);
}
return  0;
}


自定义跳转到的函数
DWORD __stdcall  Mymsg(HWND a, LPCSTR b, LPCSTR c,DWORD d)
{  
veh_Hook1.Stop();
if(b=="1")
{ 
::MessageBoxA(a,b,"hook",d);
}else{ 
::MessageBoxA(a,b,"no hook",d);
::MessageBoxA(a,b,"no hook",d);
::MessageBoxA(a,b,"no hook",d);
}
veh_Hook1.Start();
return 1;

}

*/
/************************************************************************/