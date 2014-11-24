
#include "MemLoadDll.h"

CMemLoadDll::CMemLoadDll()
{
  isLoadOk = FALSE;
  pImageBase = NULL;
  pDllMain = NULL;
}
CMemLoadDll::~CMemLoadDll()
{
  if(isLoadOk)
  {
/*
    ASSERT(pImageBase != NULL);
    ASSERT(pDllMain != NULL);*/
    //�ѹ���׼��ж��dll
    pDllMain((HINSTANCE)pImageBase,DLL_PROCESS_DETACH,0);

	delete  (LPVOID)pImageBase;
   // VirtualFree((LPVOID)pImageBase, 0, MEM_RELEASE);
  }
}

//MemLoadLibrary�������ڴ滺���������м���һ��dll����ǰ���̵ĵ�ַ�ռ䣬ȱʡλ��0��10000000
//����ֵ�� �ɹ�����TRUE , ʧ�ܷ���FALSE
//lpFileData: ���dll�ļ����ݵĻ�����
//DataLength: �����������ݵ��ܳ���
BOOL CMemLoadDll::MemLoadLibrary(void* lpFileData, int DataLength)
{
  if(pImageBase != NULL)
  {
    return FALSE; //�Ѿ�����һ��dll����û���ͷţ����ܼ����µ�dll
  }

  //���������Ч�ԣ�����ʼ��
  if(!CheckDataValide(lpFileData, DataLength))return FALSE;

  //��������ļ��ؿռ�
  int ImageSize = CalcTotalImageSize();

  if(ImageSize == 0) return FALSE;

  // ���������ڴ�
  //void *pMemoryAddress = VirtualAlloc((LPVOID)0x10000000, ImageSize,MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);

  //�޸�,��ָ��dll��ַ�����ڴ�

 // void *pMemoryAddress = ::VirtualAlloc((LPVOID)NULL, ImageSize,MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);
BYTE* pMemoryAddress;
  pMemoryAddress= new BYTE[ImageSize];

  if(pMemoryAddress == NULL)
  {
    return FALSE;
  }
  else
  {
    CopyDllDatas(pMemoryAddress, lpFileData); //����dll���ݣ�������ÿ����
    //�ض�λ��Ϣ
    if(pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress >0
    && pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size>0)
    {
		DoRelocation(pMemoryAddress);
    }
    //��������ַ��
    if(!FillRavAddress(pMemoryAddress)) //���������ַ��ʧ��
    {
      //::VirtualFree(pMemoryAddress,0,MEM_RELEASE);

	delete []pMemoryAddress;
      return FALSE;
    }
    //�޸�ҳ���ԡ�Ӧ�ø���ÿ��ҳ�����Ե����������Ӧ�ڴ�ҳ�����ԡ������һ�¡�
    //ͳһ���ó�һ������PAGE_EXECUTE_READWRITE

    unsigned long old;

    ::VirtualProtect(pMemoryAddress, ImageSize, PAGE_EXECUTE_READWRITE,&old);

  }
  
  //��������ַ
  pNTHeader->OptionalHeader.ImageBase = (DWORD)pMemoryAddress;

  //������Ҫ����һ��dll����ں���������ʼ��������
  
 
  pDllMain = (ProcDllMain)(pNTHeader->OptionalHeader.AddressOfEntryPoint +(DWORD) pMemoryAddress);

  BOOL InitResult = pDllMain((HINSTANCE)pMemoryAddress,DLL_PROCESS_ATTACH,0);

  if(!InitResult) //��ʼ��ʧ��
  {
	  MessageBoxA(0,"��ʼ��ʧ��","��ʼ��ʧ��",0);
    pDllMain((HINSTANCE)pMemoryAddress,DLL_PROCESS_DETACH,0);

    //::VirtualFree(pMemoryAddress,0,MEM_RELEASE);
	delete []pMemoryAddress;

    pDllMain = NULL;

    return FALSE;
  }

  isLoadOk = TRUE;

  pImageBase = (DWORD)pMemoryAddress;
  
  return TRUE;
}

//MemGetProcAddress������dll�л�ȡָ�������ĵ�ַ
//����ֵ�� �ɹ����غ�����ַ , ʧ�ܷ���NULL
//lpProcName: Ҫ���Һ��������ֻ������
FARPROC CMemLoadDll::MemGetProcAddress(LPCSTR lpProcName)
{
  if(pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == 0)
  return NULL;

  if (  pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size == 0)
  {
	  return NULL;
  }
  if(!isLoadOk) return NULL;

  DWORD OffsetStart = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

  DWORD Size = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

  PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pImageBase + pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

  int iBase = pExport->Base;

  int iNumberOfFunctions = pExport->NumberOfFunctions;

  int iNumberOfNames = pExport->NumberOfNames; //<= iNumberOfFunctions

  LPDWORD pAddressOfFunctions = (LPDWORD)(pExport->AddressOfFunctions + pImageBase);

  LPWORD pAddressOfOrdinals = (LPWORD)(pExport->AddressOfNameOrdinals + pImageBase);

  LPDWORD pAddressOfNames = (LPDWORD)(pExport->AddressOfNames + pImageBase);

  int iOrdinal = -1;

  if(((DWORD)lpProcName & 0xFFFF0000) == 0) //IT IS A ORDINAL!
  {
    iOrdinal = (DWORD)lpProcName & 0x0000FFFF - iBase;
  }
  else //use name
  {
    int iFound = -1;

    for(int i=0;i<iNumberOfNames;i++)
    {
      char* pName= (char* )(pAddressOfNames[i] + pImageBase);
	//  MessageBoxA(0,pName,"ö�ٺ�����",0);
      if(strcmp(pName, lpProcName) == 0)
      {
        iFound = i; break;
      }
    }

    if(iFound >= 0)
    {
      iOrdinal = (int)(pAddressOfOrdinals[iFound]);
    }
  }

  if(iOrdinal < 0 || iOrdinal >= iNumberOfFunctions ) return NULL;
  else
  {
    DWORD pFunctionOffset = pAddressOfFunctions[iOrdinal];

    if(pFunctionOffset > OffsetStart && pFunctionOffset < (OffsetStart+Size))//maybe Export Forwarding
    return NULL;
    else return (FARPROC)(pFunctionOffset + pImageBase);
  }

}

// �ض���PE�õ��ĵ�ַ
void CMemLoadDll::DoRelocation( void *NewBase)
{
  /* �ض�λ��Ľṹ��
  // DWORD sectionAddress, DWORD size (����������Ҫ�ض�λ������)
  // ���� 1000����Ҫ����5���ض�λ���ݵĻ����ض�λ���������
  // 00 10 00 00 14 00 00 00 xxxx xxxx xxxx xxxx xxxx 0000
  // �������C �������C ��-
  // �����ڵ�ƫ�� �ܳߴ�=8+6*2 ��Ҫ�����ĵ�ַ ���ڶ���4�ֽ�
  // �ض�λ�������ɸ����������address �� size����0 ��ʾ����
  // ��Ҫ�����ĵ�ַ��12λ�ģ���4λ����̬�֣�intel cpu����3
  */
  //����NewBase��0��600000,���ļ������õ�ȱʡImageBase��0��400000,������ƫ��������0��200000

  DWORD Delta = (DWORD)NewBase - pNTHeader->OptionalHeader.ImageBase;

  //ע���ض�λ���λ�ÿ��ܺ�Ӳ���ļ��е�ƫ�Ƶ�ַ��ͬ��Ӧ��ʹ�ü��غ�ĵ�ַ
  PIMAGE_BASE_RELOCATION pLoc = (PIMAGE_BASE_RELOCATION)((unsigned long)NewBase
  + pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

  while((pLoc->VirtualAddress + pLoc->SizeOfBlock) != 0) //��ʼɨ���ض�λ��
  {
    WORD *pLocData = (WORD *)((int)pLoc + sizeof(IMAGE_BASE_RELOCATION));

    //���㱾����Ҫ�������ض�λ���ַ������Ŀ
    int NumberOfReloc = (pLoc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION))/sizeof(WORD);

    for( int i=0 ; i < NumberOfReloc; i++)
    {
      if( (DWORD)(pLocData[i] & 0xF000) == 0x00003000) //����һ����Ҫ�����ĵ�ַ
      {
      // ������
      // pLoc->VirtualAddress = 0��1000;
      // pLocData[i] = 0��313E; ��ʾ����ƫ�Ƶ�ַ0��13E����Ҫ����
      // ��� pAddress = ����ַ + 0��113E
      // ����������� A1 ( 0c d4 02 10) �������ǣ� mov eax , [1002d40c]
      // ��Ҫ����1002d40c�����ַ
      DWORD * pAddress = (DWORD *)((unsigned long)NewBase + pLoc->VirtualAddress + (pLocData[i] & 0x0FFF));

      *pAddress += Delta;
      
      }
    }

    //ת�Ƶ���һ���ڽ��д���
    pLoc = (PIMAGE_BASE_RELOCATION)((DWORD)pLoc + pLoc->SizeOfBlock);

  }

}

//��������ַ��
BOOL CMemLoadDll::FillRavAddress(void *pImageBase)
{
  // �����ʵ������һ�� IMAGE_IMPORT_DESCRIPTOR �ṹ���飬ȫ����0��ʾ����
  // ���鶨�����£�
  //
  // DWORD OriginalFirstThunk; // 0��ʾ����������ָ��δ�󶨵�IAT�ṹ����
  // DWORD TimeDateStamp;
  // DWORD ForwarderChain; // -1 if no forwarders
  // DWORD Name; // ����dll������
  // DWORD FirstThunk; // ָ��IAT�ṹ����ĵ�ַ(�󶨺���ЩIAT�������ʵ�ʵĺ�����ַ)
  unsigned long Offset = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress ;

  if(Offset == 0) return TRUE; //No Import Table

  PIMAGE_IMPORT_DESCRIPTOR pID = (PIMAGE_IMPORT_DESCRIPTOR)((unsigned long) pImageBase + Offset);

  while(pID->Characteristics != 0 )
  {
    PIMAGE_THUNK_DATA pRealIAT = (PIMAGE_THUNK_DATA)((unsigned long)pImageBase + pID->FirstThunk);

    PIMAGE_THUNK_DATA pOriginalIAT = (PIMAGE_THUNK_DATA)((unsigned long)pImageBase + pID->OriginalFirstThunk);

    //��ȡdll������
	char  buf[1024]   ; //dll name;
	//buf=new char[1024];
    //�޸�,��Ҫbuf����,����dll���Ʋ���
    memset(buf,0,sizeof(buf));

    BYTE* pName = (BYTE*)((unsigned long)pImageBase + pID->Name);

    for(int i=0;i<1024;i++)
    {
      if(pName[i] == NULL)break;

      buf[i] = pName[i];
    }

  HMODULE hDll = ::GetModuleHandleA(buf);

   if(hDll == NULL) 
    {
		hDll = ::LoadLibraryA(buf); //�п���������dll��û�м���,���û�м��ؼ��غ����ж��Ƿ���سɹ�

      if (hDll == NULL)

      return FALSE; //NOT FOUND DLL

    } /*   *///��ȡDLL��ÿ�����������ĵ�ַ������IAT

    //ÿ��IAT�ṹ�� ��
    // union { PBYTE ForwarderString;
    // PDWORD Function;
    // DWORD Ordinal;
    // PIMAGE_IMPORT_BY_NAME AddressOfData;
    // } u1;
    // ������һ��DWORD ����������һ����ַ��
    for(int i=0; ;i++)
    {
      if(pOriginalIAT[i].u1.Function == 0)  break;

      FARPROC lpFunction = NULL;

      if(pOriginalIAT[i].u1.Ordinal & IMAGE_ORDINAL_FLAG) //�����ֵ�������ǵ������
      {
        lpFunction = ::GetProcAddress(hDll, (LPCSTR)(pOriginalIAT[i].u1.Ordinal & 0x0000FFFF));
      }
      else //�������ֵ���
      {
        //��ȡ��IAT���������ĺ�������
        PIMAGE_IMPORT_BY_NAME pByName = (PIMAGE_IMPORT_BY_NAME)
        ((DWORD)pImageBase + (DWORD)(pOriginalIAT[i].u1.AddressOfData));
        // if(pByName->Hint !=0)
        // lpFunction = GetProcAddress(hDll, (LPCSTR)pByName->Hint);
        // else
        lpFunction = GetProcAddress(hDll, (char *)pByName->Name);
      }

      if(lpFunction != NULL) //�ҵ��ˣ�
      {
        pRealIAT[i].u1.Function = (DWORD) lpFunction;
      }
      else return FALSE;
    }

    //move to next
    pID = (PIMAGE_IMPORT_DESCRIPTOR)( (DWORD)pID + sizeof(IMAGE_IMPORT_DESCRIPTOR));

  }

  return TRUE;
}

//CheckDataValide�������ڼ�黺�����е������Ƿ���Ч��dll�ļ�
//����ֵ�� ��һ����ִ�е�dll�򷵻�TRUE�����򷵻�FALSE��
//lpFileData: ���dll���ݵ��ڴ滺����
//DataLength: dll�ļ��ĳ���
BOOL CMemLoadDll::CheckDataValide(void* lpFileData, int DataLength)
{
  //��鳤��
  if(DataLength < sizeof(IMAGE_DOS_HEADER)) return FALSE;

  pDosHeader = (PIMAGE_DOS_HEADER)lpFileData; // DOSͷ

  //���dosͷ�ı��
  if(pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) return FALSE; //0*5A4D : MZ

  //��鳤��
  if((DWORD)DataLength < (pDosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS)) ) return FALSE;

  //ȡ��peͷ
  pNTHeader = (PIMAGE_NT_HEADERS)( (unsigned long)lpFileData + pDosHeader->e_lfanew); // PEͷ
  //���peͷ�ĺϷ���
  if(pNTHeader->Signature != IMAGE_NT_SIGNATURE) return FALSE; //0*00004550 : PE00

  if((pNTHeader->FileHeader.Characteristics & IMAGE_FILE_DLL) == 0) //0*2000 : File is a DLL
  return FALSE;

  if((pNTHeader->FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) == 0) //0*0002 : ָ���ļ���������
  return FALSE;

  if(pNTHeader->FileHeader.SizeOfOptionalHeader != sizeof(IMAGE_OPTIONAL_HEADER)) return FALSE;


  //ȡ�ýڱ��α�
  pSectionHeader = (PIMAGE_SECTION_HEADER)((int)pNTHeader + sizeof(IMAGE_NT_HEADERS));

  //��֤ÿ���ڱ�Ŀռ�
  for(int i=0; i< pNTHeader->FileHeader.NumberOfSections; i++)
  {
    if((pSectionHeader[i].PointerToRawData + pSectionHeader[i].SizeOfRawData) > (DWORD)DataLength)return FALSE;
  }


  return TRUE;
}

//�������߽�
int CMemLoadDll::GetAlignedSize(int Origin, int Alignment)
{
  return (Origin + Alignment - 1) / Alignment * Alignment;
}
//��������dllӳ���ļ��ĳߴ�
int CMemLoadDll::CalcTotalImageSize()
{
  int Size;

  if(pNTHeader == NULL)return 0;

  int nAlign = pNTHeader->OptionalHeader.SectionAlignment; //�ζ����ֽ���

  // ��������ͷ�ĳߴ硣����dos, coff, peͷ �� �α�Ĵ�С
  Size = GetAlignedSize(pNTHeader->OptionalHeader.SizeOfHeaders, nAlign);

  // �������нڵĴ�С
  for(int i=0; i < pNTHeader->FileHeader.NumberOfSections; ++i)
  {
    //�õ��ýڵĴ�С
    int CodeSize = pSectionHeader[i].Misc.VirtualSize ;
    int LoadSize = pSectionHeader[i].SizeOfRawData;
    int MaxSize = (LoadSize > CodeSize)?(LoadSize):(CodeSize);

    int SectionSize = GetAlignedSize(pSectionHeader[i].VirtualAddress + MaxSize, nAlign);
    if(Size < SectionSize)
    Size = SectionSize; //Use the Max;
  }

  return Size;

}
//CopyDllDatas������dll���ݸ��Ƶ�ָ���ڴ����򣬲��������н�
//pSrc: ���dll���ݵ�ԭʼ������
//pDest:Ŀ���ڴ��ַ
void CMemLoadDll::CopyDllDatas(void* pDest, void* pSrc)
{
  // ������Ҫ���Ƶ�PEͷ+�α��ֽ���

  int HeaderSize = pNTHeader->OptionalHeader.SizeOfHeaders;

  int SectionSize = pNTHeader->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);

  int MoveSize = HeaderSize + SectionSize;

  //����ͷ�Ͷ���Ϣ
  memmove(pDest, pSrc, MoveSize);


//����ÿ����
for(int i=0; i < pNTHeader->FileHeader.NumberOfSections; ++i)
{
  if(pSectionHeader[i].VirtualAddress == 0 || pSectionHeader[i].SizeOfRawData == 0) continue;

  // ��λ�ý����ڴ��е�λ��
  void *pSectionAddress = (void *)((unsigned long)pDest + pSectionHeader[i].VirtualAddress);
  
  // ���ƶ����ݵ������ڴ�
  memmove((void *)pSectionAddress,
  (void *)((DWORD)pSrc + pSectionHeader[i].PointerToRawData),
  pSectionHeader[i].SizeOfRawData);

}

  //����ָ�룬ָ���·�����ڴ�
  //�µ�dosͷ
  pDosHeader = (PIMAGE_DOS_HEADER)pDest;
  //�µ�peͷ��ַ
  pNTHeader = (PIMAGE_NT_HEADERS)((int)pDest + (pDosHeader->e_lfanew));
  //�µĽڱ��ַ
  pSectionHeader = (PIMAGE_SECTION_HEADER)((int)pNTHeader + sizeof(IMAGE_NT_HEADERS));

  return ;
}


/*

//������ԴDLL
#define strKey (char)0x15
char DLLtype[4]={'D' ^ strKey ,'l'^ strKey,'l'^ strKey,0x00};
HINSTANCE hinst=AfxGetInstanceHandle();
HRSRC hr=NULL;
HGLOBAL hg=NULL;
//����Դ�����ַ������м򵥵����������ﵽ����ͨ���ⲿ�ַ����ο��¶ϵ�
for(int i=0;i<sizeof(DLLtype)-1;i++) 
{
  DLLtype[i]^=strKey;
}
hr=FindResource(hinst,MAKEINTRESOURCE(IDR_DLL),TEXT(DLLtype));
if (NULL == hr) return FALSE;
//��ȡ��Դ�Ĵ�С
DWORD dwSize = SizeofResource(hinst, hr); 
if (0 == dwSize) return FALSE;
hg=LoadResource(hinst,hr);
if (NULL == hg) return FALSE;
//������Դ
LPVOID pBuffer =(LPSTR)LockResource(hg);
if (NULL == pBuffer) return FALSE;

//��pBuffer���д���
pMemLoadDll=new CMemLoadDll();
if(pMemLoadDll->MemLoadLibrary(pBuffer, dwSize)) //����dll����ǰ���̵ĵ�ַ�ռ�
{
  for(int i=0;i<sizeof(dllname)-1;i++) 
  {
    dllname[i]^=strKey;
  }
       
SENSE3 = (DllSENSE3)pMemLoadDll->MemGetProcAddress(dllname);
  if(SENSE3 == NULL)
  {
     return TRUE;
  }
}

FreeResource(hg); //����Դʹ����Ϻ����ǲ���Ҫʹ��UnlockResource��FreeResource���ֶ����ͷ���Դ����Ϊ���Ƕ���16λWindows���������ģ���Win32�У���ʹ����Ϻ�ϵͳ���Զ����ա� 
*/


BOOL  CMemLoadDll::ReloadFile(char* Filename)
{

 
	HANDLE FileHandle;
	ULONG_PTR FILESIZE;

	DWORD TEMP;

	FileHandle=::CreateFileA(Filename,GENERIC_READ,0,0,OPEN_ALWAYS,FILE_ATTRIBUTE_SYSTEM,NULL);
	//����ϵͳģ�� �����
	if (FileHandle==NULL)
	{

		return FALSE;
	}

	FILESIZE=GetFileSize(FileHandle,NULL);
	/*	BUFER=new BYTE[FILESIZE];*/

	void* BUFER;
	(void*)BUFER=::VirtualAllocEx(::GetCurrentProcess(), NULL,FILESIZE, MEM_COMMIT, PAGE_EXECUTE_READWRITE ); //




	if (ReadFile(FileHandle,BUFER,FILESIZE,&TEMP,NULL)==FALSE)
	{

		delete []BUFER;
		return FALSE;
	}
	::CloseHandle(FileHandle);


	if (this->MemLoadLibrary(BUFER,FILESIZE)!=TRUE)
	{

		//OutputDebugStringA("erro!!");


		delete []BUFER;
		return FALSE;
	}

	return  TRUE;
}