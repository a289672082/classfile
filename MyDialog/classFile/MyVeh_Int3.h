#ifndef  VEH_INT3




#include "Common.h"
class VEH_INT3_HOOK
{
public:
	DWORD  TMP_INT;
   DWORD T_OrgAdr;//����Ҫ�¶ϵĵ�ַ
   BYTE T_OrgAdr_1Byte;//���汻�¶ϵĵ�ַ��ͷ1�ֽ� ��Ϊ���ĳ���CC
   DWORD T_EFlags;//����ִ�е��ϵ�ʱ���״̬ ����ִ�л�ԭ��
   void Init_1();
   BOOL SetHandle_2( __in PVECTORED_EXCEPTION_HANDLER Handler);
   void Add_Int3_HOOK_3(DWORD  OrgAdress);
 
protected:
private:
};
#define  VEH_INT3
#endif


/************************************************************************/
/* ʾ��



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
			//�޸Ĳ���
			char *lpText="Hello World!";
			*(int*)((ExceptionInfo->ContextRecord->Esp)+0x8)=(int)lpText;
			*(int*)((ExceptionInfo->ContextRecord->Esp)+0xc)=(int)lpText;

			//�޸�״̬
			ExceptionInfo->ContextRecord->ContextFlags=CONTEXT_CONTROL;
			ExceptionInfo->ContextRecord->Eip = / *(DWORD)&MessageBoxA;* /(DWORD)addr;
			efl=ExceptionInfo->ContextRecord->EFlags;
			ExceptionInfo->ContextRecord->EFlags |= 0x100;


			//�ָ�����
			VirtualProtect((void*)addr,2,PAGE_EXECUTE_READWRITE,&tmp_11);	
			*(BYTE*)(addr) = 0x8b; 
			//	OutputDebugStringA("My::�������У�ȡ���ϵ�"); 



			//AddVectoredExceptionHandler(NULL,(PVECTORED_EXCEPTION_HANDLER)ExceptionInfo);
			return EXCEPTION_CONTINUE_EXECUTION;
		} 
	}
	else if ( ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP )
	{
		//��ԭ�ϵ㣬��־λ��
		//	OutputDebugStringA("My::��ԭ�ϵ�");
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

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}*/