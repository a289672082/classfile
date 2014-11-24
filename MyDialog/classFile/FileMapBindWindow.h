 

#ifndef   D3D_FILEMAP
#include <d3d9.h>
#include  "Common.h"




typedef struct _DATA_TO_DX
{
	DWORD PID;
	HWND  thisWindow;
	DWORD  D3D_44;//SetTransformÆ«ÒÆÁ¿
	DWORD  D3D_17;//PresentÆ«ÒÆÁ¿
	DWORD  D3D_81;
	DWORD  D3D_82;//DrawIndexedPrimitiveÆ«ÒÆÁ¿
	DWORD  D3D_65;//DrawIndexedPrimitiveÆ«ÒÆÁ¿
	DWORD  hookpri;
	DWORD  Use_Stride;
	DWORD  Use_Nun;

}DATA_TO_DX,*PDATA_TO_DX;

class MyFileMap_d3d
{
public:
	MyFileMap_d3d();
	~MyFileMap_d3d();
	DATA_TO_DX  NewData[50];
	PDATA_TO_DX  Pdata;
	LONG BindWindow(DWORD   pid,DWORD  hwnd);
	LONG MyFileMap_d3d:: BindWindowByFile(DWORD   pid1);
	LPVOID GetClassVirtualFnAddress(LPVOID pthis,int Index) ;//Add 2010.8.6
	DWORD  MyPID;
	DWORD MyHwnd;
	char  PidStr[1024];
	HANDLE  FILEMAP;
protected:

private:
};


#define   D3D_FILEMAP
#endif

 