#include "MyVeh_Int3.h"

void VEH_INT3_HOOK::Init_1()
{
	T_OrgAdr=0;
		T_EFlags=0;
		T_OrgAdr_1Byte=0;
 
}





BOOL VEH_INT3_HOOK::SetHandle_2( __in PVECTORED_EXCEPTION_HANDLER Handler)
{
	

	 
	AddVectoredExceptionHandler(0,Handler);
 
	return  TRUE;

}




void VEH_INT3_HOOK::Add_Int3_HOOK_3(DWORD  OrgAdress)
{

	DWORD  dwOldProtect;

	 
			T_OrgAdr=OrgAdress;

			//�ָ�����
			VirtualProtect((void*)OrgAdress,2,PAGE_EXECUTE_READWRITE,&TMP_INT);
			if (*(BYTE*)OrgAdress!=0xcc)
			{
				T_OrgAdr_1Byte=*(BYTE*)OrgAdress;
			}else{
				OutputDebugStringA("CCָ���Ѵ���");
			}
	 

 
 
	VirtualProtect((void*)OrgAdress,2,PAGE_EXECUTE_READWRITE,&dwOldProtect);
	*(BYTE*)(OrgAdress)=0xcc;
	VirtualProtect((void*)OrgAdress,2,dwOldProtect,&dwOldProtect);
	OutputDebugStringA("My::����int3 hook");
}


