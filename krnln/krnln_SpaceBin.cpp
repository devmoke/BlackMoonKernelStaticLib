#include "stdafx.h"

//�ֽڼ����� - ȡ�հ��ֽڼ�
/*
    ���ø�ʽ�� ���ֽڼ��� ȡ�հ��ֽڼ� �������� ���ֽ���Ŀ�� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�SpaceBin
    ���ؾ����ض���Ŀ 0 �ֽڵ��ֽڼ���������Ϊ�������
    ����<1>������Ϊ�����ֽ���Ŀ��������Ϊ�������ͣ�int������
*/
LIBAPI(void*, krnln_SpaceBin)
{
	if(ArgInf.m_int <=0)return NULL;
	LPINT pData = (LPINT)E_MAlloc(ArgInf.m_int+2*sizeof(INT));
	pData[0]=1;
	pData[1]=ArgInf.m_int;
	return pData;
}
