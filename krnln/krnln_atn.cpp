#include "stdafx.h"
#include <math.h>
//�������� - ������
/*
    ���ø�ʽ�� ��˫����С���͡� ������ ��˫����С���� �����䷴����ֵ����ֵ�� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�atn
    ����ָ�����ķ�����ֵ��������Ϊ�������
    ����<1>������Ϊ�������䷴����ֵ����ֵ��������Ϊ��˫����С���ͣ�double������
*/
LIBAPI(void, krnln_atn)
{
	ArgInf.m_double = atan(ArgInf.m_double);
	__asm
	{
		mov eax,ArgInf.m_unit.m_dwFormID;
		mov edx,ArgInf.m_unit.m_dwUnitID;
	}
}
