
#include "Common.h"
_ZwQueryInformationProcess ZwQueryInformationProcess=NULL;
void DbgPrint(LPCSTR lpszFormat, ...)
{
	va_list   args;
	int       nBuf;
	CHAR     szBuffer[0x4000];
	va_start(args, lpszFormat);
	nBuf = wvsprintfA(szBuffer, lpszFormat, args);
	////OutputDebugStringA(szBuffer);
	va_end(args);
}


DWORD GetParentProcessId(HANDLE hProcess)
{
	if (ZwQueryInformationProcess==NULL)
	{
		ZwQueryInformationProcess=(_ZwQueryInformationProcess)(GetProcAddress(LoadLibraryA("NTDLL.DLL"),"NtQueryInformationProcess")) ;
	}
	PROCESS_BASIC_INFORMATION stInfo = {0};
	DWORD dwRetnLen = 0;
	DWORD dw = ZwQueryInformationProcess(hProcess, ProcessBasicInformation, &stInfo, sizeof(stInfo), &dwRetnLen);
	return stInfo.InheritedFromUniqueProcessId;
}
BOOL  hide(HMODULE hModMyself)
{
	if (ZwQueryInformationProcess==NULL)
	{
		ZwQueryInformationProcess=(_ZwQueryInformationProcess)(GetProcAddress(LoadLibraryA("NTDLL.DLL"),"NtQueryInformationProcess")) ;
	}

	PROCESS_BASIC_INFORMATION stInfo = {0};
	DWORD dwRetnLen = 0;
	DWORD dw = ZwQueryInformationProcess(GetCurrentProcess(), 0, &stInfo, sizeof(stInfo), &dwRetnLen);

	PPEB pPeb = (PPEB)stInfo.PebBaseAddress;
	PLIST_ENTRY ListHead, Current;
	PLDR_DATA_TABLE_ENTRY pstEntry = NULL;

	ListHead = &( ((PPEB)stInfo.PebBaseAddress)->Ldr->InLoadOrderModuleList);
	Current = ListHead->Flink;
	while ( Current != ListHead)
	{
		pstEntry = CONTAINING_RECORD( Current, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
		if ( pstEntry->DllBase == hModMyself)
		{
			pstEntry->InLoadOrderLinks.Flink->Blink = pstEntry->InLoadOrderLinks.Blink;
			pstEntry->InLoadOrderLinks.Blink->Flink = pstEntry->InLoadOrderLinks.Flink;
			break;
		}
		Current = pstEntry->InLoadOrderLinks.Flink;
	}

	ListHead = &( ((PPEB)stInfo.PebBaseAddress)->Ldr->InMemoryOrderModuleList);
	Current = ListHead->Flink;
	while ( Current != ListHead)
	{
		pstEntry = CONTAINING_RECORD( Current, LDR_DATA_TABLE_ENTRY, InMemoryOrderModuleList);
		if ( pstEntry->DllBase == hModMyself)
		{
			pstEntry->InMemoryOrderModuleList.Flink->Blink = pstEntry->InMemoryOrderModuleList.Blink;
			pstEntry->InMemoryOrderModuleList.Blink->Flink = pstEntry->InMemoryOrderModuleList.Flink;
			break;
		}
		Current = pstEntry->InMemoryOrderModuleList.Flink;
	}

	ListHead = &( ((PPEB)stInfo.PebBaseAddress)->Ldr->InInitializationOrderModuleList);
	Current = ListHead->Flink;
	while ( Current != ListHead)
	{
		pstEntry = CONTAINING_RECORD( Current, LDR_DATA_TABLE_ENTRY, InInitializationOrderModuleList);
		if ( pstEntry->DllBase == hModMyself)
		{
			pstEntry->InInitializationOrderModuleList.Flink->Blink = pstEntry->InInitializationOrderModuleList.Blink;
			pstEntry->InInitializationOrderModuleList.Blink->Flink = pstEntry->InInitializationOrderModuleList.Flink;
			break;
		}
		Current = pstEntry->InInitializationOrderModuleList.Flink;
	}
	return TRUE; 
}