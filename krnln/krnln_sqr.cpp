#include "stdafx.h"
#include <math.h>
//�������� - ��ƽ����
/*
    ���ø�ʽ�� ��˫����С���͡� ��ƽ���� ��˫����С���� ������ƽ��������ֵ�� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�sqr
    ����ָ��������ƽ������������Ϊ�������
    ����<1>������Ϊ��������ƽ��������ֵ��������Ϊ��˫����С���ͣ�double����������ֵ���С���㽫���¼������
*/
LIBAPI(void, krnln_sqr)
{
	PMDATA_INF pArg = &ArgInf;

	ArgInf.m_double = sqrt(ArgInf.m_double);

	__asm
	{
		mov eax,ArgInf.m_unit.m_dwFormID;
		mov edx,ArgInf.m_unit.m_dwUnitID;
	}
}
