//����QQ 289672082  ��������C++���������
#ifndef  Myclass_H





#include "Common.h"
#include <atlstr.h>
#include "MemLoadDll.h"
#include "HookSystemCall.h"
#include "HookSystemcallx86tox64.h"
#include "./MyVeh_HOOK.h"
#include "MyVeh_Int3.h"
class MyClass
{
public:



	MyClass();
	~MyClass();
	VEH_HOOK  veh_hook1;//�ӹܽ���Ӳ���ϵ��쳣 ��֪�����޸��ڴ�
	VEH_INT3_HOOK  int3_hook;//�ӹܽ���int3�쳣 ��֪�����޸��ڴ�

					/************************************************************************/
					/*
					*				�ж��ǲ���64λϵͳ
					*
					*				��64λ������														
					*//************************************************************************/
					BOOL IsWow64();


	/***********************************************************************************************
	* �������� �� CloseObjectByThreadAdr
	* ������; �� ����������̵߳�ַ����λ��16���Ƶ�ַ�رմ��߳�
	* ������� ��  �̵߳�ַ����λ
	* ��    �� �� ��
	* ע    �� �� ֻ�������ڱ����̡�
	/**********************************************************************************************/
	bool CloseObjectByThreadAdr(DWORD  adr);

	/***********************************************************************************************
	* �������� �� CloseObjectByName
	* ������; �� ��������Ķ�����������رա�
	* ������� �� char  *pObjectName Ҫ�رյĶ�������  Type ���������
	* ��    �� �� ��
	* ע    �� �� ֻ�������ڱ����̡�
	/**********************************************************************************************/
	bool CloseObjectByName(char  *pObjectName,DWORD  Type);


	/************************************************************************/
	/*     ��ȡ�ƶ��߳̾�����̵߳�ַ                                       */
	/************************************************************************/
	DWORD   GetThreadAdrByHandle(HANDLE  tidH);


	/************************************************************************/
	/* ����ģ�� ʧ�ܷ���NULL    �ɹ�����   CMemLoadDll*                     */
	/************************************************************************/
	CMemLoadDll*  BeginMemReload(char* FilenameA);


	/************************************************************************/
	/* ����:	 HOOK 32λϵͳ��Kifastcall  ���ҳ�ʼ��
	* ����ֵ:	 ʧ�ܷ��� NULL
	*˵��:		����HookSystemCall*ָ��  ��ָ�����InstallHook���HOOK����
	* ʾ��  HookSystemCall.InstallHook("NtOpenFile",(DWORD)MyZwOpenFile,&OldNtOpenFile); 
	/************************************************************************/
	HookSystemCall*  BeginHookSystenCall32();




	/************************************************************************/
	/* ����:	 HOOK 64λϵͳ��Kifastcall  ���ҳ�ʼ��
	* ����ֵ:	 ʧ�ܷ��� NULL
	*˵��:		����HookSystemCall*ָ��  ��ָ�����InstallHook���HOOK����
	* ʾ��  HookSystemCall.InstallHook("NtOpenFile",(DWORD)MyZwOpenFile,&OldNtOpenFile); 
	/************************************************************************/
	HookSystemcallx86tox64*  BeginHookSystenCall64();



	/************************************************************************/
	/*  ö���ƶ����� 
	����������
	*/
	/************************************************************************/
	void EmunProcess( WCHAR*  ProcessName);
	//��ʱ����
	CAtlStringW tt1;
	CAtlStringW  tt2;
protected:
	
private:
};





typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);













#define   Myclass_H
#endif
