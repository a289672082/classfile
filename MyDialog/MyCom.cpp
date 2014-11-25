#include "stdafx.h"
#include "MyCom.h" 

MyCom::MyCom(void)
{
}


MyCom::~MyCom(void)
{
	
}




 
DWORD*   MyCom::ReCOM_DM(char*  file  )
{
	 CoInitialize(NULL);
	typedef HRESULT (__stdcall * pfnHello)(REFCLSID,REFIID,void**);

	CLSID  clsid; 
	::CLSIDFromString( L"{26037a0e-7cbd-4fff-9c63-56f2d0770214}",&clsid);


	pfnHello fnHello= NULL;
	HINSTANCE hdllInst = LoadLibrary(file);
	fnHello=(pfnHello)GetProcAddress(hdllInst,"DllGetClassObject");
	if (fnHello != 0)
	{

		IClassFactory* pcf = NULL;
		HRESULT hr=(fnHello)(clsid,IID_IClassFactory,(void**)&pcf);
		if (SUCCEEDED(hr) && (pcf != NULL))
		{
			 
			DWORD* pGetRes=NULL;
			hr = pcf->CreateInstance(NULL, IID_IUnknown , (void**)&pGetRes); 
			if (SUCCEEDED(hr)  /* && (pFoo != NULL)*/)
			{
				 //pcf->AddRef();
		  	
				 pcf->Release();
			//	pcf->LockServer(TRUE);
				return  pGetRes;
			} 

		}
		//FreeLibrary(hdllInst);
	} else
	{
		AfxMessageBox("erro 1");
		return NULL;
	}

	return  NULL;
}


DWORD* MyCom::ReCOM_DM_RES(DWORD  IDR_DLL,char* DLLtype)
{

 
	HINSTANCE hinst=AfxGetInstanceHandle();
	HRSRC hr=NULL;
	HGLOBAL hg=NULL;
 
	hr=FindResource(hinst,MAKEINTRESOURCE(IDR_DLL),TEXT(DLLtype));
	if (NULL == hr)
	{
		AfxMessageBox("erro hr");
		return FALSE;
	}
	//获取资源的大小
	DWORD dwSize = SizeofResource(hinst, hr); 
	if (0 == dwSize) return FALSE;
	hg=LoadResource(hinst,hr);
	if (NULL == hg) return FALSE;
	//锁定资源
	AfxMessageBox("1 hr");
	LPVOID pBuffer =(LPSTR)LockResource(hg);
	if (NULL == pBuffer) return FALSE;
	AfxMessageBox("2 hr");
	//对pBuffer进行处理
	if (pMemLoadDll ==nullptr)
	{
		AfxMessageBox("NULL");
		  pMemLoadDll  =new CMemLoadDll();
		  AfxMessageBox("3 hr");
		  if(!pMemLoadDll->MemLoadLibrary(pBuffer, dwSize)) //加载dll到当前进程的地址空间
		  { 
			  AfxMessageBox("重载失败");
			  return  nullptr;
		  }
	}
	AfxMessageBox("4 hr");
 //////////////////////////////////////////////////////////////////////////
	CoInitialize(NULL);
	typedef HRESULT (__stdcall * pfnHello)(REFCLSID,REFIID,void**);

	CLSID  clsid; 
	::CLSIDFromString( L"{26037a0e-7cbd-4fff-9c63-56f2d0770214}",&clsid);


	pfnHello fnHello= NULL; 
	fnHello=(pfnHello)pMemLoadDll->MemGetProcAddress("DllGetClassObject");
	if (fnHello != 0)
	{

		IClassFactory* pcf = NULL;
		HRESULT hr=(fnHello)(clsid,IID_IClassFactory,(void**)&pcf);
		if (SUCCEEDED(hr) && (pcf != NULL))
		{

			DWORD* pGetRes=NULL;
			hr = pcf->CreateInstance(NULL, IID_IUnknown , (void**)&pGetRes); 
			if (SUCCEEDED(hr)  /* && (pFoo != NULL)*/)
			{
				//pcf->AddRef();

				pcf->Release();
				//pcf->LockServer(TRUE);
				return  pGetRes;
			} 

		}
		//FreeLibrary(hdllInst);
	} else
	{
		AfxMessageBox("erro 1");
		return NULL;
	}

	return  NULL;
 

/*
		SENSE3 = (DllSENSE3)pMemLoadDll->MemGetProcAddress(dllname);
		if(SENSE3 == NULL)
		{
			return TRUE;
		}*/

}


DWORD*  MyCom::ReCOM(char*  file  , REFCLSID clsid )
{
	typedef HRESULT (__stdcall * pfnHello)(REFCLSID,REFIID,void**);
	pfnHello fnHello= NULL;
	HINSTANCE hdllInst = LoadLibrary(file);
	fnHello=(pfnHello)GetProcAddress(hdllInst,"DllGetClassObject");
	if (fnHello != 0)
	{
 
		IClassFactory* pcf = NULL;
		HRESULT hr=(fnHello)(clsid,IID_IClassFactory,(void**)&pcf);
		if (SUCCEEDED(hr) && (pcf != NULL))
		{

			DWORD* pGetRes ;
			hr = pcf->CreateInstance(NULL, IID_IUnknown , (void**)&pGetRes);

			if (SUCCEEDED(hr)  /* && (pFoo != NULL)*/)
			{ 
				return  pGetRes;
			}
			pcf->Release();
		} 
	} else
	{

		AfxMessageBox("错误的重载");
				return  false;
	}
	return  false;
}