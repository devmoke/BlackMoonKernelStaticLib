#include "stdafx.h"
#include <math.h>
//�������� - ������
/*
    ���ø�ʽ�� ��˫����С���͡� ������ ��˫����С���� ��������˫����С���� ������... �� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�mod
    ���������ֵ���̣��������������֣��������Ϊ��%����Mod����������Ϊ���������������������һ���������Ա��ظ���ӡ�
    ����<1>������Ϊ����������������Ϊ��˫����С���ͣ�double������
    ����<2>������Ϊ��������������Ϊ��˫����С���ͣ�double������
*/
LIBAPI(void, krnln_mod)
{

	PMDATA_INF pArg = &ArgInf;

	for(int i=1;i< nArgCount;i++)
	{
		ArgInf.m_double = fmod(ArgInf.m_double, pArg[i].m_double);
	}

	__asm
	{
		mov eax,ArgInf.m_unit.m_dwFormID;
		mov edx,ArgInf.m_unit.m_dwUnitID;
	}
}
