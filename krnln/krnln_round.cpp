#include "stdafx.h"
#include <math.h>
//#include <stdio.h>
//�������� - ��������
/*
    ���ø�ʽ�� ��˫����С���͡� �������� ��˫����С���� ���������������ֵ���������� �������λ�ãݣ� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�round
    ���ذ���ָ���ķ�ʽ����������������Ľ����ֵ��������Ϊ�������
    ����<1>������Ϊ�����������������ֵ��������Ϊ��˫����С���ͣ�double������
    ����<2>������Ϊ���������λ�á�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ��������0����ʾС�����ұ�Ӧ������λ�����������0����ʾ���뵽���������С��0����ʾС����������뵽��λ�á����磺�������� (1056.65, 1) ���� 1056.7�� �������� (1056.65, 0) ���� 1057�� �������� (1056.65, -1) ���� 1060�����ʡ�Ա���������Ĭ��Ϊ0��
*/

double round(double x)
{
	return floor(x+0.5);
}

LIBAPI(void, krnln_round)
{
	PMDATA_INF pArg = &ArgInf;

	INT n;
	if(pArg[1].m_dtDataType == _SDT_NULL)
		n = 0;
	else
		n = pArg[1].m_int;
	if(n==0)
		ArgInf.m_double = round(ArgInf.m_double);
	else if(n>0)
	{
		double dbNum = pow(10, n);
		ArgInf.m_double = ArgInf.m_double * dbNum;

		ArgInf.m_double = round(ArgInf.m_double)/dbNum;

	}else
	{
		n = abs(n);
		double dbNum = pow(10, n);
		ArgInf.m_double = ArgInf.m_double / dbNum;
		ArgInf.m_double = round(ArgInf.m_double)* dbNum;
	}
	/*
		char str [100];

			sprintf(str,"%lf",(ArgInf.m_double));
MessageBox(NULL,str,NULL,MB_OK);
*/

	__asm
	{
		mov eax,ArgInf.m_unit.m_dwFormID;
		mov edx,ArgInf.m_unit.m_dwUnitID;
	}

}
