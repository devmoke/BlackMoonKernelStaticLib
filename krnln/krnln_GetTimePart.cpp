#include "stdafx.h"
#include <math.h>
//ʱ����� - ȡʱ��
/*
    ���ø�ʽ�� ������ʱ���͡� ȡʱ�� ������ʱ���� ʱ�䣩 - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�GetTimePart
    ����һ������ʱ�������ݵ�ʱ�䲿�֣����ꡢ�¡��ձ��̶�����Ϊ2000��1��1�ա�������Ϊ�������
    ����<1>������Ϊ��ʱ�䡱������Ϊ������ʱ���ͣ�date������
*/
LIBAPI(void, krnln_GetTimePart) // ֱ���޸���Eax��edx�����Բ���Ҫָ������ֵ����
{
	DATE objDate;
	DATE dt = modf(ArgInf.m_date,&objDate);
	INT nHour, nMinute, nSecond;
	GetTimePart(dt,nHour, nMinute, nSecond);
	ArgInf.m_date = GetSpecDateTime(2000,1,1,nHour, nMinute, nSecond);
	__asm{
		mov eax, ArgInf.m_unit.m_dwFormID;
		mov edx, ArgInf.m_unit.m_dwUnitID;
	}
}
