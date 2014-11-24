#ifndef MEM_H

//以下代码经过Win2k Sp4/WinXp Sp2下测试通过

// MemLoadDll.h: interface for the CMemLoadDll class.
//
//////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <windef.h>

typedef    bool (__stdcall *ProcDllMain)(HINSTANCE a, DWORD b ,  LPVOID c);

class CMemLoadDll  
{
public:
	PIMAGE_DOS_HEADER pDosHeader;
	CMemLoadDll();
	virtual ~CMemLoadDll();
	BOOL ReloadFile(char* FileName);
	DWORD  pImageBase;
	BOOL    MemLoadLibrary( void* lpFileData , int DataLength);  // Dll file data buffer
	FARPROC MemGetProcAddress(LPCSTR lpProcName);
private:
	BOOL isLoadOk;
	BOOL CheckDataValide(void* lpFileData, int DataLength);
	int  CalcTotalImageSize();
	void CopyDllDatas(void* pDest, void* pSrc);
	BOOL FillRavAddress(void* pBase);
	void DoRelocation(void* pNewBase);
	int  GetAlignedSize(int Origin, int Alignment); 

private:

	ProcDllMain pDllMain;


private:


	//	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNTHeader;
	PIMAGE_SECTION_HEADER pSectionHeader;


}; 



#define MEM_H
#endif








