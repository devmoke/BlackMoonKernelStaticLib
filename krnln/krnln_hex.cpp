#include "stdafx.h"
#include <stdio.h>
//��ֵת�� - ȡʮ�������ı�
/*
    ���ø�ʽ�� ���ı��͡� ȡʮ�������ı� �������� ��ȡ�����ı�����ֵ�� - ϵͳ����֧�ֿ�->��ֵת��
    Ӣ�����ƣ�hex
    ����һ���ı�������ָ����ֵ��ʮ��������ʽ��������Ϊ�������
    ����<1>������Ϊ����ȡ�����ı�����ֵ��������Ϊ�������ͣ�int������
*/
LIBAPI(char*, krnln_hex)
{
	char *pText = (char*)E_MAlloc_Nzero(16);
	sprintf(pText,"%X",ArgInf.m_int);
	return pText;
}
