#include "stdafx.h"
#include <math.h>
//�������� - ��η�
/*
    ���ø�ʽ�� ��˫����С���͡� ��η� ��˫����С���� ����η���ֵ��˫����С���� �η����� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�pow
    ����ָ����ֵ��ָ���η���������Ϊ�������
    ����<1>������Ϊ������η���ֵ��������Ϊ��˫����С���ͣ�double����������ֵָ��������ĳ�η�����ֵ��
    ����<2>������Ϊ���η�����������Ϊ��˫����С���ͣ�double����������ֵָ��������η���ֵ������ָ����
*/
LIBAPI(void, krnln_pow)
{
	PMDATA_INF pArg = &ArgInf;

	ArgInf.m_double = pow(ArgInf.m_double,pArg[1].m_double);

	__asm
	{
		mov eax,ArgInf.m_unit.m_dwFormID;
		mov edx,ArgInf.m_unit.m_dwUnitID;
	}
}
