#include "stdafx.h"
#include <math.h>
//ʱ����� - ȡ����
/*
    ���ø�ʽ�� ������ʱ���͡� ȡ���� ������ʱ���� ʱ�䣩 - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�GetDatePart
    ����һ������ʱ�������ݵ����ڲ��֣���Сʱ�����ӡ��뱻�̶�����Ϊ0ʱ0��0�롣������Ϊ�������
    ����<1>������Ϊ��ʱ�䡱������Ϊ������ʱ���ͣ�date������
*/
LIBAPI(void, krnln_GetDatePart) // ֱ���޸�eax��edx,���Բ���Ҫָ������ֵ����
{
	DATE objDate;
	DATE dt = modf(ArgInf.m_date,&objDate);
	ArgInf.m_date = objDate;
	__asm{
		mov eax, ArgInf.m_unit.m_dwFormID;
		mov edx, ArgInf.m_unit.m_dwUnitID;
	}
}
