
#include "Common.h"
#include "HookSystemCall.h"


DWORD	dwIndex;
DWORD	dwKiFastSystemCall;
DWORD	dwKiFastSystemCallReturn;


//HOOK������ĺ�����ַ
DWORD dwHookSystemCall[0x2048];

//����ԭʼ�������õ�ַ
DWORD *dwOrigSystemCall[0x2048];


HookSystemCall::HookSystemCall(void)
{
	Initialization();
}

HookSystemCall::~HookSystemCall(void)
{
	
}
__declspec(naked) void OrigCall()
{
	__asm  {
		lea esp,dword ptr ss:[esp]
		lea ecx,dword ptr ds:[ecx]
		mov edx,esp
		__emit 0x0F
		__emit 0x34
		retn
	}
}





__declspec(naked) void KiFastSystemCallEx()
{
	__asm  {
		mov edx,esp
		__emit 0x0F
		__emit 0x34
		retn
	}
}

//EX SystemCall
__declspec(naked) void SystemCall()
{
	__asm  {
		__emit 0x90
		mov eax,0x11B2
		call KiFastSystemCallEx
		retn 0xFF
		__emit 0x90
	}
}


__declspec(naked) void KiFastSystemCall()
{
	
	__asm{
		pushad
			pushfd

			cmp         dword ptr [eax*4+dwHookSystemCall],0

			jz          Label
			popfd
			popad
			add         esp,4
			jmp         dword ptr [dwHookSystemCall+eax*4]

Label:
			popfd
			popad
			jmp         KiFastSystemCallEx

	}
/*
	__asm {
		pushad
		pushfd
		mov dwIndex,eax
	}
	//������ҪHOOK ��ZW����
	if (dwHookSystemCall[dwIndex] != NULL)
	{
		__asm {
			popfd 
			popad
			add esp,4;�����ZW����Ҫ�ٷ����ˡ�ֱ�Ӽ�4
			lea edx,dwHookSystemCall
			mov eax,dwIndex
			jmp dword ptr [edx + eax*4];�������ǵ�HOOK����
		}
	}
	
	__asm {
		popfd
		popad
	}
	__asm
	{
		JMP KiFastSystemCallEx
	*/
}

//��ʼ��
BOOL HookSystemCall::Initialization()
{

	DWORD dwOldProtect;
	HMODULE hModule = GetModuleHandleA("NTDLL.dll");

	memset(dwHookSystemCall,0,sizeof(DWORD)*0x2048);
	memset(dwOrigSystemCall,0,sizeof(DWORD)*0x2048);

	dwKiFastSystemCall = PtrToUlong(GetProcAddress(hModule, "KiFastSystemCall"));
	dwKiFastSystemCallReturn = dwKiFastSystemCall + 2;

	VirtualProtect(ULongToPtr(dwKiFastSystemCall - 0xA), 100, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	//	Hook KiFastSystemCall
	*(PWORD)ULongToPtr(dwKiFastSystemCall) = 0xF4EB;
	*(PBYTE)ULongToPtr(dwKiFastSystemCall - 0xA) = 0xE9;
	*(PDWORD)ULongToPtr(dwKiFastSystemCall - 0x9) = PtrToUlong(KiFastSystemCall) - (dwKiFastSystemCall - 0xA) - 5;

	//VirtualProtect(ULongToPtr(dwKiFastSystemCall - 0xA), 100, dwOldProtect, &dwOldProtect);
	
	return 0;
}

// ��װ����
BOOL HookSystemCall::InstallHook(PCHAR FunName,		//NTAPI
								 DWORD pHookFunc,	//HOOK�ĺ���
								 DWORD * pOrigFunc)	//���صĺ���
{
	DWORD dwOldProtect;
	DWORD dwIndex = GetSysCallIndex(FunName);
	DWORD	dwFunadd =PtrToUlong(GetProcAddress(GetModuleHandleA("NTDLL.dll"), FunName));
	
	//���������Ϣ
	dwHookSystemCall[dwIndex] = pHookFunc;
	dwOrigSystemCall[dwIndex] = (PDWORD)malloc(0x10);

	//��ԭ����ZW���������ȥ
	memcpy(dwOrigSystemCall[dwIndex],(PVOID)dwFunadd,0x10);
	
	//Ұ����쿪ʼ
	VirtualProtect(ULongToPtr(dwOrigSystemCall[dwIndex]), 0x10, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	*(PBYTE)((DWORD)dwOrigSystemCall[dwIndex]	+ 5)	=	 0xE8;
	*(PDWORD)((DWORD)dwOrigSystemCall[dwIndex] + 6)		=	 (DWORD)KiFastSystemCallEx - (DWORD)dwOrigSystemCall[dwIndex] -0xA;
	*(PWORD)((DWORD)dwOrigSystemCall[dwIndex]	+ 10)	=	 0x9090;

	* pOrigFunc = (DWORD)dwOrigSystemCall[dwIndex];
	
	return 0;
}


// Ex��װ����
BOOL HookSystemCall::InstallHookEx(DWORD dwIndex,		//NTAPI
								   WORD dwRetIndex,	//���ض�ջƽ��
								   DWORD pHookFunc,		//HOOK�ĺ���
								   DWORD * pOrigFunc)	//���صĺ���
{
	DWORD dwOldProtect;

	//���������Ϣ
	dwHookSystemCall[dwIndex] = pHookFunc;
	dwOrigSystemCall[dwIndex] = (PDWORD)malloc(0x10);

	//��ԭ����ZW���������ȥ
	memcpy(dwOrigSystemCall[dwIndex],(PVOID)SystemCall,0x10);

	//Ұ����쿪ʼ
	VirtualProtect(ULongToPtr(dwOrigSystemCall[dwIndex]), 0x10, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	*(PDWORD)((DWORD)dwOrigSystemCall[dwIndex] + 2)		=	 (DWORD)dwIndex;
	*(PDWORD)((DWORD)dwOrigSystemCall[dwIndex] + 7)		=	 (DWORD)KiFastSystemCallEx - (DWORD)dwOrigSystemCall[dwIndex] - 0xB;
	*(PWORD)((DWORD)dwOrigSystemCall[dwIndex]	+ 12)	=	 dwRetIndex;

	* pOrigFunc = (DWORD)dwOrigSystemCall[dwIndex];

	return 0;
}

// ж��HOOK
BOOL HookSystemCall::UnHook(PCHAR FunName)
{
	DWORD dwIndex = GetSysCallIndex(FunName);
	dwHookSystemCall[dwIndex] = NULL;
	free(dwOrigSystemCall[dwIndex]);
	return 0;
}

// ж��ϵͳ����
BOOL HookSystemCall::UnSystemHook()
{
	DWORD dwOldProtect;
	BYTE	szCode[0xF] = {0x8D,0xA4,0x24,0x00,0x00,0x00,0x00,0x8D,0x49,0x00,0x8B,0xD4,0x0F,0x34,0xC3};
	DWORD dwSystemCall = dwKiFastSystemCallReturn-2;
	VirtualProtect(ULongToPtr(dwSystemCall - 0xA), 100, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	memcpy((VOID*)(dwSystemCall - 0xA),szCode,0xF);
	return 0;
}




//��DLL�ĵ������л�ȡ������ַ
DWORD HookSystemCall::GetExportFuncAddr(IN PCHAR lpFunctionName,     //��������
										IN PCHAR pDllName) //Ҫӳ���ģ������
{
	HANDLE hMod;
	PIMAGE_DOS_HEADER       pDosHeader;
	PIMAGE_OPTIONAL_HEADER  pOptHeader;
	PIMAGE_EXPORT_DIRECTORY pExportTable;

	DWORD* arrayOfFuncAddr;
	DWORD* arrayOfFuncNames;
	WORD*  arrayOfFuncOrdinals;
	DWORD  funcOrdinal;
	DWORD  Base, i, FuncAddr;
	PCHAR  FuncName;
	PVOID  BaseAddress = NULL;
	SIZE_T size = 0;



	hMod = GetModuleHandleA(pDllName);
	pDosHeader = (PIMAGE_DOS_HEADER)hMod;
	pOptHeader = (PIMAGE_OPTIONAL_HEADER)( (BYTE*)hMod + pDosHeader->e_lfanew + 24 );
	pExportTable =(IMAGE_EXPORT_DIRECTORY*)((BYTE*) hMod 
		+ pOptHeader->DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT]. VirtualAddress);

	//now we can get the exported functions, but note we convert from RVA to address
	arrayOfFuncAddr     = (DWORD*)( (BYTE*)hMod + pExportTable->AddressOfFunctions);
	arrayOfFuncNames    = (DWORD*)( (BYTE*)hMod + pExportTable->AddressOfNames);
	arrayOfFuncOrdinals = (WORD* )( (BYTE*)hMod + pExportTable->AddressOfNameOrdinals);
	Base = pExportTable->Base;

	for( i=0; i<pExportTable->NumberOfFunctions; i++ )
	{
		FuncName = (PCHAR)( (BYTE*)hMod + arrayOfFuncNames[i]);
		funcOrdinal = arrayOfFuncOrdinals[i] + Base - 1; 
		//always need to add base, -1 as array counts from 0
		//this is the funny bit.  you would expect the function pointer to simply be arrayOfFunAddr[i]...
		//oh no... thats too simple.  it is actually arrayOfFuncAddr[funcOrdinal]!!
		FuncAddr = (DWORD)( (BYTE*)hMod + arrayOfFuncAddr[funcOrdinal]);
		if (strcmp(FuncName, lpFunctionName) == 0) 
		{
			return FuncAddr;
		}
	}
	return 0;
}

//���ú���GetDllFuncAddr�Ա��÷����
int HookSystemCall::GetSysCallIndex( PCHAR FuncName )
{
	DWORD          FuncAddr;    //������ַ
	int            SysCallIndex;//�����
	FuncAddr = GetExportFuncAddr(FuncName, "ntdll.dll");
	SysCallIndex = *( (WORD*)(FuncAddr + 1) );
	return SysCallIndex;
}
