#pragma once
#include "Common.h"
class HookSystemcallx86tox64
{
public:
	HookSystemcallx86tox64(void);
	virtual ~HookSystemcallx86tox64(void);

	// X64��X86ģʽ�����ں˺�����ַ
	DWORD dwX86SwitchTo64BitMode;

	//���ú���GetDllFuncAddr�Ա��÷����
	int GetSysCallIndex( PCHAR FuncName );

	// ��ȡģʽת��������ַ
	DWORD GetX86toX64BitModeFun(void);
	// ��ʼ��
	BOOL Initialization(void);

	// ��װ����
	BOOL InstallHook(PCHAR FunName,//NTAPI
		DWORD pHookFunc,	//HOOK�ĺ���
		DWORD * pOrigFunc);	//���صĺ���

	// Ex��װ����
	BOOL InstallHookEx(DWORD dwIndex,		//NTAPI
		WORD dwRetIndex,	//���ض�ջƽ��
		DWORD pHookFunc,		//HOOK�ĺ���
		DWORD * pOrigFunc);	//���صĺ���

	// ������ʼ��ַ
	int GetEditLength(PVOID CodeAdderss);
};
