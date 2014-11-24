#pragma once
#include "./classFile/MemLoadDll.h"
class MyCom
{
public:
	MyCom(void);
		CMemLoadDll* pMemLoadDll;
	DWORD*   ReCOM_DM(char*  file  );
	DWORD*  ReCOM(char*  file  , REFCLSID clsid );
	DWORD* ReCOM_DM_RES(DWORD  IDR_DLL,char* DLLtype);
	~MyCom(void);
};

