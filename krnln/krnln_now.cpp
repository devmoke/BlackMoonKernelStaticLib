#include "stdafx.h"

//ʱ����� - ȡ����ʱ��
/*
    ���ø�ʽ�� ������ʱ���͡� ȡ����ʱ�� ���� - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�now
    ���ص�ǰϵͳ���ڼ�ʱ�䡣������Ϊ�������
*/
LIBAPI(void, krnln_now)
{
	SYSTEMTIME now;
	MDATA_INF ArgInf2;
	GetLocalTime(&now);
	ArgInf2.m_double = GetSpecDateTime(now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
	__asm{
		mov eax, ArgInf2.m_unit.m_dwFormID;
		mov edx, ArgInf2.m_unit.m_dwUnitID;
	}
}
