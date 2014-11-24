#pragma once


class HookSystemCall
{
public:
	HookSystemCall(void);
	~HookSystemCall(void);
	
	//��ʼ��
	BOOL Initialization();

	//���ú���GetDllFuncAddr�Ա��÷����
	int GetSysCallIndex( PCHAR FuncName );

	//��DLL�ĵ������л�ȡ������ַ
	DWORD GetExportFuncAddr(IN PCHAR lpFunctionName,     //��������
							IN PCHAR pDllName); //Ҫӳ���ģ������

	// ��װ����
	BOOL InstallHook(PCHAR FunName,			//NTAPI
					 DWORD pHookFunc,		//HOOK�ĺ���
					 DWORD * pOrigFunc);	//���صĺ���

	// Ex��װ����
	BOOL InstallHookEx(DWORD dwIndex,		//NTAPI
						WORD dwRetIndex,	//���ض�ջƽ��
						DWORD pHookFunc,		//HOOK�ĺ���
						DWORD * pOrigFunc);	//���صĺ���
	// ж��HOOK
	BOOL UnHook(PCHAR FunName);

	// ж��ϵͳ����
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