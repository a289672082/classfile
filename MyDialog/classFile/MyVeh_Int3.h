#ifndef  VEH_INT3




#include "Common.h"
class VEH_INT3_HOOK
{
public:
	DWORD  TMP_INT;
   DWORD T_OrgAdr;//保存要下断的地址
   BYTE T_OrgAdr_1Byte;//保存被下断的地址的头1字节 因为被改成了CC
   DWORD T_EFlags;//保存执行到断点时候的状态 单步执行还原用
   void Init_1();
   BOOL SetHandle_2( __in PVECTORED_EXCEPTION_HANDLER Handler);
   void Add_Int3_HOOK_3(DWORD  OrgAdress);
 
protected:
private:
};
#define  VEH_INT3
#endif


/************************************************************************/
/* 示例



*/
/************************************************************************/



/*

CString  ffff;
DWORD adr1;
DWORD efl;
LPVOID addr;
DWORD  tmp_11;
LONG NTAPI  Handle1(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
	if(ExceptionInfo->ExceptionRecord->ExceptionCode==EXCEPTION_BREAKPOINT)
	{
		addr=ExceptionInfo->ExceptionRecord->ExceptionAddress;
		if   (addr!=(PVOID)0)
		{

			OutputDebugStringA("2"); 
			//修改参数
			char *lpText="Hello World!";
			*(int*)((ExceptionInfo->ContextRecord->Esp)+0x8)=(int)lpText;
			*(int*)((ExceptionInfo->ContextRecord->Esp)+0xc)=(int)lpText;

			//修改状态
			ExceptionInfo->ContextRecord->ContextFlags=CONTEXT_CONTROL;
			ExceptionInfo->ContextRecord->Eip = / *(DWORD)&MessageBoxA;* /(DWORD)addr;
			efl=ExceptionInfo->ContextRecord->EFlags;
			ExceptionInfo->ContextRecord->EFlags |= 0x100;


			//恢复代码
			VirtualProtect((void*)addr,2,PAGE_EXECUTE_READWRITE,&tmp_11);	
			*(BYTE*)(addr) = 0x8b; 
			//	OutputDebugStringA("My::单步运行，取消断点"); 



			//AddVectoredExceptionHandler(NULL,(PVECTORED_EXCEPTION_HANDLER)ExceptionInfo);
			return EXCEPTION_CONTINUE_EXECUTION;
		} 
	}
	else if ( ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP )
	{
		//还原断点，标志位。
		//	OutputDebugStringA("My::还原断点");
		ExceptionInfo->ContextRecord->EFlags =efl;

		VirtualProtect((void*)addr,2,PAGE_EXECUTE_READWRITE,&tmp_11);	
		*(BYTE*)(addr) = 0xcc;

		return EXCEPTION_CONTINUE_EXECUTION;
	}


	return EXCEPTION_CONTINUE_SEARCH ;

}



void CMyClassInDlg::OnBnClickedButton3()
{
	CS2.int3_hook.Init_1();
	SetUnhandledExceptionFilter(Handle1);

	CS2.int3_hook.SetHandle_2(Handle1);
	CS2.int3_hook.Add_Int3_HOOK_3((DWORD)::MessageBoxA);

	// TODO: 在此添加控件通知处理程序代码
}*/