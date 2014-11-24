#include "FileMapBindWindow.h"

 

 
MyFileMap_d3d::MyFileMap_d3d()
{

	MyPID=0;
	MyHwnd=0;
}
MyFileMap_d3d::~MyFileMap_d3d()
{

}



LPDIRECT3D9             g_pD3D222 = NULL; // Used to create the D3DDevice
static LPDIRECT3DDEVICE9       g_pd3dDevice222 = NULL; // Our rendering device

HRESULT InitD3D__(   )
{
	if (g_pD3D222!=NULL  &&  g_pd3dDevice222!=NULL)
	{
		return  S_OK;
	}
	// Create the D3D object.
	if( NULL == ( g_pD3D222 = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	// Create the D3DDevice
	if( FAILED( g_pD3D222->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, ::GetDesktopWindow(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice222 ) ) )
	{
		::MessageBoxA(0,"CreateDevice erro","CreateDevice erro",0);
	 
		return E_FAIL;
	}

	return S_OK;
}
 




LPVOID MyFileMap_d3d::GetClassVirtualFnAddress(LPVOID pthis,int Index) //Add 2010.8.6
{
	LPVOID FnAddress;

	*(int*)&FnAddress = *(int*)pthis;                       //lpvtable
	*(int*)&FnAddress = *(int*)((int*)FnAddress + Index);
	return FnAddress;
}


LONG MyFileMap_d3d:: BindWindowByFile(DWORD   pid1)
{


	
	//AfxMessageBox("0");
	if (g_pd3dDevice222==NULL)
	{
		if (	InitD3D__() != S_OK)
		{
				::MessageBoxA(0,"InitD3D__ erro","InitD3D__ erro",0);
		}
	
	}


/*
	if(pid1==NULL)
	{
			::MessageBoxA(0,"Process erro","Process erro",0);
		//	AfxMessageBox("窗口不存在！");
		return 0;

	}*/



	::LoadLibraryA("d3d9.dll");
	DWORD  d3d9_adr=(DWORD)GetModuleHandleA("d3d9.dll");
	//DWORD  d3d9KEYBORD_adr=(DWORD)GetModuleHandleA("DINPUT8.dll"); 
	for (int i =0 ; i<50 ;i++)
	{
		NewData[i].D3D_44=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,44)-d3d9_adr;
		NewData[i].D3D_65=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,65)-d3d9_adr;
		NewData[i].D3D_81=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,81)-d3d9_adr;
		NewData[i].D3D_82=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,82)-d3d9_adr;
		NewData[i].D3D_17=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,17)-d3d9_adr;  
	}
	
/*
	char* Strpid=new char[256];
	memset(Strpid,0,256);
	MyPID=pid1;
 

	sprintf_s(Strpid,256,"%x",pid1); */

	/*			::MessageBoxA(0,Strpid,"Mapo erro",0);
	 */
		/*		__try
				{
		 
					WritePrivateProfileStructA("MAIN",Strpid,&NewData,sizeof(DATA_TO_DX),"C:\\TLBB.ini"); 
					 
				}
				__except (1)
				{
					
				}*/
			 
	
 
 
 

	//delete []Strpid;

	return 1;
}
LONG MyFileMap_d3d:: BindWindow(DWORD   pid1,DWORD Hwnd)
{	
	//AfxMessageBox("0");
	if (g_pd3dDevice222==NULL)
	{
		if (	InitD3D__() != S_OK)
		{
				::MessageBoxA(0,"InitD3D__ erro","InitD3D__ erro",0);
		}
	
	}


/*
	if(pid1==NULL)
	{
			::MessageBoxA(0,"Process erro","Process erro",0);
		//	AfxMessageBox("窗口不存在！");
		return 0;

	}
*/



	::LoadLibraryA("d3d9.dll");
	DWORD  d3d9_adr=(DWORD)GetModuleHandleA("d3d9.dll");
	//DWORD  d3d9KEYBORD_adr=(DWORD)GetModuleHandleA("DINPUT8.dll"); 
	for (int i =0 ; i<50 ;i++)
	{
		NewData[i].D3D_44=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,44)-d3d9_adr;
		NewData[i].D3D_65=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,65)-d3d9_adr;
		NewData[i].D3D_81=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,81)-d3d9_adr;
		NewData[i].D3D_82=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,82)-d3d9_adr;
		NewData[i].D3D_17=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,17)-d3d9_adr;  
	}

	for (int i =0 ; i<50 ;i++)
	{
		if(NewData[i].PID==0  || NewData[i].thisWindow==0)
		{
			NewData[i].PID = pid1;
			NewData[i].thisWindow = (HWND)Hwnd;
			break;
		}
  	}
/*
	NewData.D3D_44=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,44)-d3d9_adr;
	NewData.D3D_65=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,65)-d3d9_adr;
	NewData.D3D_81=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,81)-d3d9_adr;
	NewData.D3D_82=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,82)-d3d9_adr;
	NewData.D3D_17=(DWORD)GetClassVirtualFnAddress(g_pd3dDevice222,17)-d3d9_adr;  */

	
/*
	char* Strpid=new char[256];
	memset(Strpid,0,256);
	MyPID=pid1;
 
	sprintf(Strpid,"%x",pid1); 
*/

		//		::MessageBoxA(0,Strpid,"Mapo erro",0);
	 
				__try
				{
		 
					   FILEMAP= ::CreateFileMappingA((HANDLE)0xffffffff,NULL,PAGE_READWRITE,0,0x1000,(LPCSTR)"MyPro");
					 
				}
				__except (1)
				{
					OutputDebugStringA("ERR");
				}
			 
	
	if (FILEMAP==(HANDLE)0  ||  FILEMAP==INVALID_HANDLE_VALUE)
	{
				::MessageBoxA(0,"Mapo erro","Mapo erro",0);
				return 0;
	}

	LPVOID   ADR=::MapViewOfFile(FILEMAP,FILE_MAP_ALL_ACCESS,0,0,0);

	memcpy(ADR,NewData,sizeof(DATA_TO_DX)*50);

	Pdata=PDATA_TO_DX(ADR);

 


	return 1;
	//	momo1.data->Begin_CF=TRUE;

}







