#include "stdafx.h"
#include <math.h>
//�������� - ȡ����ֵ
/*
    ���ø�ʽ�� ��˫����С���͡� ȡ����ֵ ��˫����С���� ��ȡ�����ֵ����ֵ�� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�abs
    ������ṩ��ֵΪ�ֽ��ͣ���ֱ�ӷ��ظ���ֵ��������Ϊ�������
    ����<1>������Ϊ����ȡ�����ֵ����ֵ��������Ϊ��˫����С���ͣ�double������
*/
LIBAPI(void, krnln_abs)
{
	ArgInf.m_double = fabs(ArgInf.m_double);
	__asm
	{
		mov eax,ArgInf.m_unit.m_dwFormID;
		mov edx,ArgInf.m_unit.m_dwUnitID;
	}
}
