
#include "Common.h"
#include "HookSystemCall.h"


DWORD	dwIndex;
DWORD	dwKiFastSystemCall;
DWORD	dwKiFastSystemCallReturn;


//HOOK后跳入的函数地址
DWORD dwHookSystemCall[0x2048];

//保存原始函数调用地址
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
	//是我们要HOOK 的ZW函数
	if (dwHookSystemCall[dwIndex] != NULL)
	{
		__asm {
			popfd 
			popad
			add esp,4;这里的ZW不需要再返回了。直接加4
			lea edx,dwHookSystemCall
			mov eax,dwIndex
			jmp dword ptr [edx + eax*4];跳到我们的HOOK函数
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

//初始化
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

// 安装钩子
BOOL HookSystemCall::InstallHook(PCHAR FunName,		//NTAPI
								 DWORD pHookFunc,	//HOOK的函数
								 DWORD * pOrigFunc)	//返回的函数
{
	DWORD dwOldProtect;
	DWORD dwIndex = GetSysCallIndex(FunName);
	DWORD	dwFunadd =PtrToUlong(GetProcAddress(GetModuleHandleA("NTDLL.dll"), FunName));
	
	//保存各种信息
	dwHookSystemCall[dwIndex] = pHookFunc;
	dwOrigSystemCall[dwIndex] = (PDWORD)malloc(0x10);

	//将原本的ZW函数保存进去
	memcpy(dwOrigSystemCall[dwIndex],(PVOID)dwFunadd,0x10);
	
	//野猪改造开始
	VirtualProtect(ULongToPtr(dwOrigSystemCall[dwIndex]), 0x10, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	*(PBYTE)((DWORD)dwOrigSystemCall[dwIndex]	+ 5)	=	 0xE8;
	*(PDWORD)((DWORD)dwOrigSystemCall[dwIndex] + 6)		=	 (DWORD)KiFastSystemCallEx - (DWORD)dwOrigSystemCall[dwIndex] -0xA;
	*(PWORD)((DWORD)dwOrigSystemCall[dwIndex]	+ 10)	=	 0x9090;

	* pOrigFunc = (DWORD)dwOrigSystemCall[dwIndex];
	
	return 0;
}


// Ex安装钩子
BOOL HookSystemCall::InstallHookEx(DWORD dwIndex,		//NTAPI
								   WORD dwRetIndex,	//返回堆栈平衡
								   DWORD pHookFunc,		//HOOK的函数
								   DWORD * pOrigFunc)	//返回的函数
{
	DWORD dwOldProtect;

	//保存各种信息
	dwHookSystemCall[dwIndex] = pHookFunc;
	dwOrigSystemCall[dwIndex] = (PDWORD)malloc(0x10);

	//将原本的ZW函数保存进去
	memcpy(dwOrigSystemCall[dwIndex],(PVOID)SystemCall,0x10);

	//野猪改造开始
	VirtualProtect(ULongToPtr(dwOrigSystemCall[dwIndex]), 0x10, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	*(PDWORD)((DWORD)dwOrigSystemCall[dwIndex] + 2)		=	 (DWORD)dwIndex;
	*(PDWORD)((DWORD)dwOrigSystemCall[dwIndex] + 7)		=	 (DWORD)KiFastSystemCallEx - (DWORD)dwOrigSystemCall[dwIndex] - 0xB;
	*(PWORD)((DWORD)dwOrigSystemCall[dwIndex]	+ 12)	=	 dwRetIndex;

	* pOrigFunc = (DWORD)dwOrigSystemCall[dwIndex];

	return 0;
}

// 卸载HOOK
BOOL HookSystemCall::UnHook(PCHAR FunName)
{
	DWORD dwIndex = GetSysCallIndex(FunName);
	dwHookSystemCall[dwIndex] = NULL;
	free(dwOrigSystemCall[dwIndex]);
	return 0;
}

// 卸载系统钩子
BOOL HookSystemCall::UnSystemHook()
{
	DWORD dwOldProtect;
	BYTE	szCode[0xF] = {0x8D,0xA4,0x24,0x00,0x00,0x00,0x00,0x8D,0x49,0x00,0x8B,0xD4,0x0F,0x34,0xC3};
	DWORD dwSystemCall = dwKiFastSystemCallReturn-2;
	VirtualProtect(ULongToPtr(dwSystemCall - 0xA), 100, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	memcpy((VOID*)(dwSystemCall - 0xA),szCode,0xF);
	return 0;
}




//从DLL的导出表中获取函数地址
DWORD HookSystemCall::GetExportFuncAddr(IN PCHAR lpFunctionName,     //函数名称
										IN PCHAR pDllName) //要映射的模块名称
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

//调用函数GetDllFuncAddr以便获得服务号
int HookSystemCall::GetSysCallIndex( PCHAR FuncName )
{
	DWORD          FuncAddr;    //函数地址
	int            SysCallIndex;//服务号
	FuncAddr = GetExportFuncAddr(FuncName, "ntdll.dll");
	SysCallIndex = *( (WORD*)(FuncAddr + 1) );
	return SysCallIndex;
}
