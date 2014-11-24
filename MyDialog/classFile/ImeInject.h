#include <windows.h>
BOOL ImeInstallEx(CString lpszdllName);
BOOL ImeUnInstallEx();
BOOL ImeStopEx();
BOOL IMEActivEx(HWND hWnd);
HKL EnumIme(CString imename,CString imefilename);
void GetImeHandleString();
void SetAllWindowActiv(HKL imehandle);
void QuitImeSystemDefault(HKL imehandle);
void ImedeleteReg();

BOOL InitGameData( CString strGameExeName,HWND &GameHwnd,DWORD &GameThreadID,DWORD &GameProcessID);

