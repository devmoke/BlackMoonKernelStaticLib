#include "stdafx.h"


extern "C" PDESTROY ECodeStart();
PDESTROY DllEntryFunc(){
	DWORD dwReturn;//������Ҫ�Ĵ�������Ȼ����ʱ����
	__asm{
        push esi
        push edi
        push ebx
        call ECodeStart
        pop ebx
        pop edi
        pop esi
		mov dwReturn,eax
 	}
	return (PDESTROY)dwReturn;

}


