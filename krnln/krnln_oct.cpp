#include "stdafx.h"
#include <stdio.h>
//��ֵת�� - ȡ�˽����ı�
/*
    ���ø�ʽ�� ���ı��͡� ȡ�˽����ı� �������� ��ȡ�����ı�����ֵ�� - ϵͳ����֧�ֿ�->��ֵת��
    Ӣ�����ƣ�oct
    ����һ���ı�������ָ����ֵ�İ˽�����ʽ��������Ϊ�������
    ����<1>������Ϊ����ȡ�����ı�����ֵ��������Ϊ�������ͣ�int������
*/
LIBAPI(char*, krnln_oct)
{
	char *pText = (char*)E_MAlloc_Nzero(256);
	sprintf(pText,"%o",ArgInf.m_int);
	return pText;
}
