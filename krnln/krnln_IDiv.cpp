#include "stdafx.h"
#include <math.h>
//�������� - ����
/*
    ���ø�ʽ�� ��˫����С���͡� ���� ��˫����С���� ��������˫����С���� ������... �� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�IDiv
    ���������ֵ���̣����������������֣��������Ϊ��\����������Ϊ���������������������һ���������Ա��ظ���ӡ�
    ����<1>������Ϊ����������������Ϊ��˫����С���ͣ�double������
    ����<2>������Ϊ��������������Ϊ��˫����С���ͣ�double������
*/
LIBAPI(void, krnln_IDiv) // ֱ���޸���eax��edx�����Բ���Ҫָ������ֵ����
{
	PMDATA_INF pArg = &ArgInf;

	for(int i=1;i< nArgCount;i++)
	{
		ArgInf.m_double = floor(ArgInf.m_double /pArg[i].m_double);
	}

	__asm
	{
		mov eax,ArgInf.m_unit.m_dwFormID;
		mov edx,ArgInf.m_unit.m_dwUnitID;
	}
}
