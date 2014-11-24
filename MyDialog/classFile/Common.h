#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <atlstr.h>
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
extern void DbgPrint(LPCSTR lpszFormat, ...);
extern BOOL  hide(HMODULE hModMyself);
DWORD GetParentProcessId(HANDLE hProcess);

typedef LONG	NTSTATUS;
#define NT_SUCCESS(Status)			((NTSTATUS)(Status) >= 0)
#define STATUS_SUCCESS                          ((NTSTATUS)0x00000000L) // ntsubauth
typedef LONG KPRIORITY;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
#ifdef MIDL_PASS
	[size_is(MaximumLength / 2), length_is((Length) / 2) ] USHORT * Buffer;
#else // MIDL_PASS
	PWSTR  Buffer;
#endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	USHORT LoadCount;
	USHORT TlsIndex;
	union
	{
		LIST_ENTRY HashLinks;
		PVOID SectionPointer;
	};
	ULONG CheckSum;
	union
	{
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	};
	PVOID EntryPointActivationContext;
	PVOID PatchInformation;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB_LDR_DATA
{
	ULONG Length;
	BOOLEAN Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _PEB
{
	UCHAR InheritedAddressSpace;                     // 00h
	UCHAR ReadImageFileExecOptions;                  // 01h
	UCHAR BeingDebugged;                             // 02h
	UCHAR Spare;                                     // 03h
	PVOID Mutant;                                    // 04h
	PVOID ImageBaseAddress;                          // 08h
	PPEB_LDR_DATA Ldr;                               // 0Ch
} PEB, *PPEB;

typedef struct _PROCESS_BASIC_INFORMATION
{
	NTSTATUS ExitStatus;
	PPEB PebBaseAddress;
	ULONG AffinityMask;
	KPRIORITY BasePriority;
	ULONG UniqueProcessId;
	ULONG InheritedFromUniqueProcessId;
}PROCESS_BASIC_INFORMATION;

typedef struct _CURDIR
{
	UNICODE_STRING DosPath;
	HANDLE         Handle;
} CURDIR, *PCURDIR;

typedef struct _CLIENT_ID {
	HANDLE  UniqueProcess;
	HANDLE  UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

 typedef NTSTATUS (_stdcall* _ZwQueryInformationProcess)(
	HANDLE ProcessHandle,
	ULONG ProcessInformationClass,
	PVOID ProcessInformation,
	ULONG ProcessInformationLength,
	PULONG ReturnLength
	);


typedef struct _RTL_DRIVE_LETTER_CURDIR {
	USHORT Flags;
	USHORT Length;
	ULONG TimeStamp;
	UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;


typedef struct _RTL_USER_PROCESS_PARAMETERS {
	ULONG MaximumLength;
	ULONG Length;
	ULONG Flags;
	ULONG DebugFlags;
	PVOID ConsoleHandle;
	ULONG ConsoleFlags;
	HANDLE StdInputHandle;
	HANDLE StdOutputHandle;
	HANDLE StdErrorHandle;
	UNICODE_STRING CurrentDirectoryPath;
	HANDLE CurrentDirectoryHandle;
	UNICODE_STRING DllPath;
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
	PVOID Environment;
	ULONG StartingPositionLeft;
	ULONG StartingPositionTop;
	ULONG Width;
	ULONG Height;
	ULONG CharWidth;
	ULONG CharHeight;
	ULONG ConsoleTextAttributes;
	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING WindowTitle;
	UNICODE_STRING DesktopName;
	UNICODE_STRING ShellInfo;
	UNICODE_STRING RuntimeData;
	RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _NT_PROC_THREAD_ATTRIBUTE_ENTRY {
	ULONG Attribute;    // PROC_THREAD_ATTRIBUTE_XXX，参见MSDN中UpdateProcThreadAttribute的说明
	SIZE_T Size;        // Value的大小
	ULONG_PTR Value;    // 保存4字节数据（比如一个Handle）或数据指针
	ULONG Unknown;      // 总是0，可能是用来返回数据给调用者
} PROC_THREAD_ATTRIBUTE_ENTRY, *PPROC_THREAD_ATTRIBUTE_ENTRY;

typedef struct _NT_PROC_THREAD_ATTRIBUTE_LIST {
	ULONG Length;       // 结构总大小
	PROC_THREAD_ATTRIBUTE_ENTRY Entry[1];
} NT_PROC_THREAD_ATTRIBUTE_LIST, *PNT_PROC_THREAD_ATTRIBUTE_LIST;


typedef enum _OBJECT_INFORMATION_CLASS {
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectAllInformation,
	ObjectDataInformation
} OBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;
typedef struct _OBJECT_NAME_INFORMATION {               
	UNICODE_STRING Name;                                
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;   

typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
	PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;
typedef CONST OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

typedef enum _EVENT_TYPE {
	NotificationEvent,
	SynchronizationEvent
} EVENT_TYPE;

#define ProcessBasicInformation 0

typedef struct _IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID Pointer;
	} DUMMYUNIONNAME;

	ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;



typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG ProcessId;
	UCHAR ObjectTypeNumber;
	UCHAR Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;



typedef struct _SYSTEM_HANDLE_INFORMATION_EX 
{
	ULONG NumberOfHandles;            //句柄数目
	SYSTEM_HANDLE_INFORMATION Information[1];
} SYSTEM_HANDLE_INFORMATION_EX, *PSYSTEM_HANDLE_INFORMATION_EX;


typedef struct _THREAD_TIMES_INFORMATION {
	LARGE_INTEGER           CreationTime;
	LARGE_INTEGER           ExitTime;
	LARGE_INTEGER           KernelTime;
	LARGE_INTEGER           UserTime;
} THREAD_TIMES_INFORMATION, *PTHREAD_TIMES_INFORMATION;


typedef struct _THREAD_BASIC_INFORMATION {
	NTSTATUS                ExitStatus;
	PVOID                   TebBaseAddress;
	CLIENT_ID               ClientId;
	KAFFINITY               AffinityMask;
	KPRIORITY               Priority;
	KPRIORITY               BasePriority;

} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;



typedef enum _THREADINFOCLASS {  
	ThreadBasicInformation,  
	ThreadTimes,  
	ThreadPriority,  
	ThreadBasePriority,  
	ThreadAffinityMask,  
	ThreadImpersonationToken,  
	ThreadDescriptorTableEntry,  
	ThreadEnableAlignmentFaultFixup,  
	ThreadEventPair_Reusable,  
	ThreadQuerySetWin32StartAddress,  
	ThreadZeroTlsCell,  
	ThreadPerformanceCount,  
	ThreadAmILastThread,  
	ThreadIdealProcessor,  
	ThreadPriorityBoost,  
	ThreadSetTlsArrayAddress,   // Obsolete  
	ThreadIsIoPending,  
	ThreadHideFromDebugger,  
	ThreadBreakOnTermination,  
	ThreadSwitchLegacyState,  
	ThreadIsTerminated,  
	ThreadLastSystemCall,  
	ThreadIoPriority,  
	ThreadCycleTime,  
	ThreadPagePriority,  
	ThreadActualBasePriority,  
	ThreadTebInformation,  
	ThreadCSwitchMon,          // Obsolete  
	ThreadCSwitchPmu,  
	ThreadWow64Context,  
	ThreadGroupInformation,  
	ThreadUmsInformation,      // UMS  
	ThreadCounterProfiling,  
	ThreadIdealProcessorEx,  
	MaxThreadInfoClass  
} THREADINFOCLASS;  





typedef
VOID
(NTAPI *PIO_APC_ROUTINE) (
						  __in PVOID ApcContext,
						  __in PIO_STATUS_BLOCK IoStatusBlock,
						  __in ULONG Reserved
						  );


typedef NTSTATUS (NTAPI *_NtQueryObject)(IN HANDLE               ObjectHandle,
										 IN OBJECT_INFORMATION_CLASS ObjectInformationClass,
										 OUT PVOID               ObjectInformation,
										 IN ULONG                Length,
										 OUT PULONG              ResultLength );

typedef NTSTATUS (NTAPI *_NtCreateMutant)(OUT PHANDLE             MutantHandle,
										  IN ACCESS_MASK          DesiredAccess,
										  IN POBJECT_ATTRIBUTES   ObjectAttributes OPTIONAL,
										  IN BOOLEAN              InitialOwner );

typedef NTSTATUS (NTAPI *_NtOpenMutant)(OUT PHANDLE             MutantHandle,
										IN ACCESS_MASK          DesiredAccess,
										IN POBJECT_ATTRIBUTES   ObjectAttributes );

typedef NTSTATUS  (NTAPI *_NtCreateSection)(OUT PHANDLE SectionHandle,    
											IN ACCESS_MASK DesiredAccess,    
											IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,    
											IN PLARGE_INTEGER MaximumSize OPTIONAL,    
											IN ULONG SectionPageProtection,    
											IN ULONG AllocationAttributes,    
											IN HANDLE FileHandle OPTIONAL    
											);
typedef NTSTATUS (NTAPI *_NtOpenSection)(OUT PHANDLE SectionHandle, IN ACCESS_MASK DesiredAccess,IN POBJECT_ATTRIBUTES ObjectAttributes);
typedef NTSTATUS (NTAPI *_NtCreateSemaphore)(OUT PHANDLE SemaphoreHandle,
											 IN ACCESS_MASK DesiredAccess,
											 IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
											 IN ULONG InitialCount,
											 IN ULONG MaximumCount);

typedef NTSTATUS (NTAPI *_NtTerminateProcess)(IN HANDLE ProcessHandle OPTIONAL,IN NTSTATUS ExitStatus);

typedef NTSTATUS (NTAPI *_NtOpenSemaphore)(OUT PHANDLE             SemaphoreHandle,
	IN ACCESS_MASK          DesiredAccess,
	IN POBJECT_ATTRIBUTES   ObjectAttributes );

typedef NTSTATUS (NTAPI *_NtCreateEvent)(OUT PHANDLE             EventHandle,
										 IN ACCESS_MASK          DesiredAccess,
										 IN POBJECT_ATTRIBUTES   ObjectAttributes OPTIONAL,
										 IN EVENT_TYPE           EventType,
										 IN BOOLEAN              InitialState );

typedef NTSTATUS (NTAPI *_NtOpenEvent)(OUT  PHANDLE EventHandle,
									   IN   ACCESS_MASK DesiredAccess,
									   IN   POBJECT_ATTRIBUTES ObjectAttributes
									   );

typedef NTSTATUS (NTAPI *_NtCreateIoCompletion)(OUT PHANDLE IoCompletionHandle,
												IN ACCESS_MASK          DesiredAccess,
												IN POBJECT_ATTRIBUTES   ObjectAttributes OPTIONAL,
												IN ULONG                NumberOfConcurrentThreads );

typedef NTSTATUS (NTAPI *_NtCreateUserProcess)(OUT PHANDLE ProcessHandle,
											   OUT PHANDLE ThreadHandle,
											   IN ACCESS_MASK ProcessDesiredAccess,
											   IN ACCESS_MASK ThreadDesiredAccess,
											   IN POBJECT_ATTRIBUTES ProcessObjectAttributes OPTIONAL,
											   IN POBJECT_ATTRIBUTES ThreadObjectAttributes OPTIONAL,
											   IN ULONG CreateProcessFlags,
											   IN ULONG CreateThreadFlags,
											   IN PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
											   IN PVOID Parameter9,
											   IN PNT_PROC_THREAD_ATTRIBUTE_LIST AttributeList);


typedef NTSTATUS (NTAPI *_NtResumeThread)(
	IN HANDLE ThreadHandle,
	OUT PULONG PreviousSuspendCount OPTIONAL
	);

typedef NTSTATUS (NTAPI *_LdrLoadDll)(IN PWCHAR               PathToFile OPTIONAL,
									  IN PULONG                Flags OPTIONAL,
									  IN PUNICODE_STRING      ModuleFileName,
									  OUT PHANDLE             ModuleHandle );

typedef HWND (NTAPI *_NtUserFindWindowEx)(IN HWND hwndParent,  
	IN HWND hwndChild,  
	IN PUNICODE_STRING pstrClassName OPTIONAL,  
	IN PUNICODE_STRING pstrWindowName OPTIONAL,  
	IN DWORD dwType);

typedef NTSTATUS (NTAPI *_ZwDeviceIoControlFile)(
	IN   HANDLE FileHandle,
	IN   HANDLE Event,
	IN   PIO_APC_ROUTINE ApcRoutine,
	IN   PVOID ApcContext,
	OUT  PIO_STATUS_BLOCK IoStatusBlock,
	IN   ULONG IoControlCode,
	IN   BYTE * InputBuffer,
	IN   ULONG InputBufferLength,
	OUT  PVOID OutputBuffer,
	IN   ULONG OutputBufferLength
	);

typedef NTSTATUS (NTAPI*_ZwReadVirtualMemory)(IN HANDLE               ProcessHandle,
	IN PVOID                BaseAddress,
	OUT PVOID               Buffer,
	IN ULONG                NumberOfBytesToRead,
	OUT PULONG              NumberOfBytesReaded OPTIONAL   
	);



typedef NTSTATUS (NTAPI *_ZwOpenProcess)
	(_Out_     PHANDLE ProcessHandle,
	_In_      ACCESS_MASK DesiredAccess,
	_In_      POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_  PCLIENT_ID ClientId
	);









typedef NTSTATUS (WINAPI *_ZwQueruInfomationThread   )(  
	HANDLE ThreadHandle,   
	ULONG ThreadInformationClass,   
	PVOID ThreadInformation,   
	ULONG ThreadInformationLength,   
	PULONG ReturnLength); 





typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation,                // 0 Y N
	SystemProcessorInformation,            // 1 Y N
	SystemPerformanceInformation,        // 2 Y N
	SystemTimeOfDayInformation,            // 3 Y N
	SystemNotImplemented1,                // 4 Y N
	SystemProcessesAndThreadsInformation, // 5 Y N
	SystemCallCounts,                    // 6 Y N
	SystemConfigurationInformation,        // 7 Y N
	SystemProcessorTimes,                // 8 Y N
	SystemGlobalFlag,                    // 9 Y Y
	SystemNotImplemented2,                // 10 Y N
	SystemModuleInformation,            // 11 Y N
	SystemLockInformation,                // 12 Y N
	SystemNotImplemented3,                // 13 Y N
	SystemNotImplemented4,                // 14 Y N
	SystemNotImplemented5,                // 15 Y N
	SystemHandleInformation,            // 16 Y N
	SystemObjectInformation,            // 17 Y N
	SystemPagefileInformation,            // 18 Y N
	SystemInstructionEmulationCounts,    // 19 Y N
	SystemInvalidInfoClass1,            // 20
	SystemCacheInformation,                // 21 Y Y
	SystemPoolTagInformation,            // 22 Y N
	SystemProcessorStatistics,            // 23 Y N
	SystemDpcInformation,                // 24 Y Y
	SystemNotImplemented6,                // 25 Y N
	SystemLoadImage,                    // 26 N Y
	SystemUnloadImage,                    // 27 N Y
	SystemTimeAdjustment,                // 28 Y Y
	SystemNotImplemented7,                // 29 Y N
	SystemNotImplemented8,                // 30 Y N
	SystemNotImplemented9,                // 31 Y N
	SystemCrashDumpInformation,            // 32 Y N
	SystemExceptionInformation,            // 33 Y N
	SystemCrashDumpStateInformation,    // 34 Y Y/N
	SystemKernelDebuggerInformation,    // 35 Y N
	SystemContextSwitchInformation,        // 36 Y N
	SystemRegistryQuotaInformation,        // 37 Y Y
	SystemLoadAndCallImage,                // 38 N Y
	SystemPrioritySeparation,            // 39 N Y
	SystemNotImplemented10,                // 40 Y N
	SystemNotImplemented11,                // 41 Y N
	SystemInvalidInfoClass2,            // 42
	SystemInvalidInfoClass3,            // 43
	SystemTimeZoneInformation,            // 44 Y N
	SystemLookasideInformation,            // 45 Y N
	SystemSetTimeSlipEvent,                // 46 N Y
	SystemCreateSession,                // 47 N Y
	SystemDeleteSession,                // 48 N Y
	SystemInvalidInfoClass4,            // 49
	SystemRangeStartInformation,        // 50 Y N
	SystemVerifierInformation,            // 51 Y Y
	SystemAddVerifier,                    // 52 N Y
	SystemSessionProcessesInformation    // 53 Y N
} SYSTEM_INFORMATION_CLASS;



typedef enum _THREAD_STATE {
	StateInitialized,
	StateReady,
	StateRunning,
	StateStandby,
	StateTerminated,
	StateWait,
	StateTransition,
	StateUnknown
} THREAD_STATE;


typedef enum _KWAIT_REASON {
	Executive,
	FreePage,
	PageIn,
	PoolAllocation,
	DelayExecution,
	Suspended,
	UserRequest,
	WrExecutive,
	WrFreePage,
	WrPageIn,
	WrPoolAllocation,
	WrDelayExecution,
	WrSuspended,
	WrUserRequest,
	WrEventPair,
	WrQueue,
	WrLpcReceive,
	WrLpcReply,
	WrVirtualMemory,
	WrPageOut,
	WrRendezvous,
	WrKeyedEvent,
	WrTerminated,
	WrProcessInSwap,
	WrCpuRateControl,
	WrCalloutStack,
	WrKernel,
	WrResource,
	WrPushLock,
	WrMutex,
	WrQuantumEnd,
	WrDispatchInt,
	WrPreempted,
	WrYieldExecution,
	WrFastMutex,
	WrGuardedMutex,
	WrRundown,
	MaximumWaitReason
} KWAIT_REASON;
typedef struct _SYSTEM_THREADS_INFORMATION {
	LARGE_INTEGER   KernelTime;
	LARGE_INTEGER   UserTime;
	LARGE_INTEGER   CreateTime;
	ULONG           WaitTime;
	PVOID           StartAddress;
	CLIENT_ID       ClientId;
	KPRIORITY       Priority;
	KPRIORITY       BasePriority;
	ULONG           ContextSwitchCount;
	THREAD_STATE    State;
	KWAIT_REASON    WaitReason;
} SYSTEM_THREADS_INFORMATION, *PSYSTEM_THREADS_INFORMATION;
typedef struct _VM_COUNTERS {
	ULONG PeakVirtualSize;
	ULONG VirtualSize;
	ULONG PageFaultCount;
	ULONG PeakWorkingSetSize;
	ULONG WorkingSetSize;
	ULONG QuotaPeakPagedPoolUsage;
	ULONG QuotaPagedPoolUsage;
	ULONG QuotaPeakNonPagedPoolUsage;
	ULONG QuotaNonPagedPoolUsage;
	ULONG PagefileUsage;
	ULONG PeakPagefileUsage;
} VM_COUNTERS, *PVM_COUNTERS;
typedef struct _SYSTEM_PROCESSES_INFORMATION {
	ULONG                       NextEntryDelta;
	ULONG                       ThreadCount;
	ULONG                       Reserved1[6];
	LARGE_INTEGER               CreateTime;
	LARGE_INTEGER               UserTime;
	LARGE_INTEGER               KernelTime;
	UNICODE_STRING              ProcessName;
	KPRIORITY                   BasePriority;
	ULONG                       ProcessId;
	ULONG                       InheritedFromProcessId;
	ULONG                       HandleCount;
	ULONG                       SessionId;
	ULONG                       Reserved2;
	VM_COUNTERS                 VmCounters;
#if (VER_PRODUCTBUILD >= 2195)
	IO_COUNTERS                 IoCounters;
#endif // (VER_PRODUCTBUILD >= 2195)
	SYSTEM_THREADS_INFORMATION  Threads[1];
} SYSTEM_PROCESSES_INFORMATION, *PSYSTEM_PROCESSES_INFORMATION;

// 定义NtQuerySystemInformation函数
typedef NTSTATUS (WINAPI *NTQUERYSYSINFOMATION)(   
	SYSTEM_INFORMATION_CLASS   SystemInformationClass,    // 定义服务类型号
	PVOID   SystemInformation,                            // 用户存储信息的缓冲区
	ULONG   SystemInformationLength,                    // 缓冲区大小
	PULONG   ReturnLength   );     