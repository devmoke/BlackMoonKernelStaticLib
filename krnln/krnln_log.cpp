#include "stdafx.h"
#include <math.h>
//�������� - ����Ȼ����
/*
    ���ø�ʽ�� ��˫����С���͡� ����Ȼ���� ��˫����С���� ��������Ȼ��������ֵ�� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�log
    ����ָ����������Ȼ����ֵ����Ȼ�������� e Ϊ�׵Ķ��������� #e ��ֵ��Լ�� 2.718282��������Ϊ�������
    ����<1>������Ϊ����������Ȼ��������ֵ��������Ϊ��˫����С���ͣ�double������
*/
LIBAPI(void, krnln_log)
{
	ArgInf.m_double = log(ArgInf.m_double);
	__asm
	{
		mov eax,ArgInf.m_unit.m_dwFormID;
		mov edx,ArgInf.m_unit.m_dwUnitID;
	}
}
