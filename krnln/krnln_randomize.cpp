#include "stdafx.h"
#include <math.h>
//�������� - �����������
/*
    ���ø�ʽ�� ���޷���ֵ�� ����������� ���������� �������������ֵ�ݣ� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�randomize
    Ϊ�������������ʼ��һ������ֵ����ͬ������ֵ�����¡�ȡ�����������ز�ͬ�������ϵ�С�������Ϊ�������
    ����<1>������Ϊ���������������ֵ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ����ʡ�Ա���������Ĭ��ʹ�õ�ǰ�����ϵͳ��ʱ��ֵ��
*/
LIBAPI(void, krnln_randomize)
{
	UINT unSeed;
	if(ArgInf.m_dtDataType==_SDT_NULL)
		unSeed = ::GetTickCount();
	else
		unSeed  = ArgInf.m_dwSubCodeAdr;
	srand(unSeed);

}
