//作者QQ 289672082  最淫荡的C++盘门左道类
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
	VEH_HOOK  veh_hook1;//接管进程硬件断点异常 神不知鬼不觉修改内存
	VEH_INT3_HOOK  int3_hook;//接管进程int3异常 神不知鬼不觉修改内存

					/************************************************************************/
					/*
					*				判断是不是64位系统
					*
					*				是64位返回真														
					*//************************************************************************/
					BOOL IsWow64();


	/***********************************************************************************************
	* 函数名称 ： CloseObjectByThreadAdr
	* 函数用途 ： 根据输入的线程地址后四位的16进制地址关闭此线程
	* 输入参数 ：  线程地址后四位
	* 返    回 ： 略
	* 注    意 ： 只适用用于本进程。
	/**********************************************************************************************/
	bool CloseObjectByThreadAdr(DWORD  adr);

	/***********************************************************************************************
	* 函数名称 ： CloseObjectByName
	* 函数用途 ： 根据输入的对象名，将其关闭。
	* 输入参数 ： char  *pObjectName 要关闭的对象名。  Type 对象的类型
	* 返    回 ： 略
	* 注    意 ： 只适用用于本进程。
	/**********************************************************************************************/
	bool CloseObjectByName(char  *pObjectName,DWORD  Type);


	/************************************************************************/
	/*     获取制定线程句柄的线程地址                                       */
	/************************************************************************/
	DWORD   GetThreadAdrByHandle(HANDLE  tidH);


	/************************************************************************/
	/* 重载模块 失败返回NULL    成功返回   CMemLoadDll*                     */
	/************************************************************************/
	CMemLoadDll*  BeginMemReload(char* FilenameA);


	/************************************************************************/
	/* 功能:	 HOOK 32位系统的Kifastcall  并且初始化
	* 返回值:	 失败返回 NULL
	*说明:		返回HookSystemCall*指针  用指针调用InstallHook添加HOOK函数
	* 示例  HookSystemCall.InstallHook("NtOpenFile",(DWORD)MyZwOpenFile,&OldNtOpenFile); 
	/************************************************************************/
	HookSystemCall*  BeginHookSystenCall32();




	/************************************************************************/
	/* 功能:	 HOOK 64位系统的Kifastcall  并且初始化
	* 返回值:	 失败返回 NULL
	*说明:		返回HookSystemCall*指针  用指针调用InstallHook添加HOOK函数
	* 示例  HookSystemCall.InstallHook("NtOpenFile",(DWORD)MyZwOpenFile,&OldNtOpenFile); 
	/************************************************************************/
	HookSystemcallx86tox64*  BeginHookSystenCall64();



	/************************************************************************/
	/*  枚举制定进程 
	参数进程名
	*/
	/************************************************************************/
	void EmunProcess( WCHAR*  ProcessName);
	//零时变量
	CAtlStringW tt1;
	CAtlStringW  tt2;
protected:
	
private:
};





typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);













#define   Myclass_H
#endif
