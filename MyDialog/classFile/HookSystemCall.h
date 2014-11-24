#pragma once


class HookSystemCall
{
public:
	HookSystemCall(void);
	~HookSystemCall(void);
	
	//初始化
	BOOL Initialization();

	//调用函数GetDllFuncAddr以便获得服务号
	int GetSysCallIndex( PCHAR FuncName );

	//从DLL的导出表中获取函数地址
	DWORD GetExportFuncAddr(IN PCHAR lpFunctionName,     //函数名称
							IN PCHAR pDllName); //要映射的模块名称

	// 安装钩子
	BOOL InstallHook(PCHAR FunName,			//NTAPI
					 DWORD pHookFunc,		//HOOK的函数
					 DWORD * pOrigFunc);	//返回的函数

	// Ex安装钩子
	BOOL InstallHookEx(DWORD dwIndex,		//NTAPI
						WORD dwRetIndex,	//返回堆栈平衡
						DWORD pHookFunc,		//HOOK的函数
						DWORD * pOrigFunc);	//返回的函数
	// 卸载HOOK
	BOOL UnHook(PCHAR FunName);

	// 卸载系统钩子
	BOOL UnSystemHook();
};


typedef struct _SECTION_IMAGE_INFORMATION {
	PVOID EntryPoint; 
	ULONG StackZeroBits; 
	ULONG StackReserved; 
	ULONG StackCommit; 
	ULONG ImageSubsystem; 
	WORD  SubsystemVersionLow; 
	WORD  SubsystemVersionHigh; 
	ULONG Unknown1; 
	ULONG ImageCharacteristics; 
	ULONG ImageMachineType; 
	ULONG Unknown2[3];
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _STRING {
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength), length_is(Length) ]
#endif // MIDL_PASS
	PCHAR Buffer;
} STRING;
typedef STRING *PSTRING;