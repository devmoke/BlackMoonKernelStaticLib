#include "stdafx.h"

//�ı����� - �ַ�
/*
    ���ø�ʽ�� ���ı��͡� �ַ� ���ֽ��� ��ȡ���ַ����ַ����룩 - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�chr
    ����һ���ı������а�������ָ���ַ�������ص��ַ���������Ϊ�������
    ����<1>������Ϊ����ȡ���ַ����ַ����롱������Ϊ���ֽ��ͣ�byte������
*/
LIBAPI(char*, krnln_chr)
{
	if(ArgInf.m_byte==0)return NULL;

	char *pText = (char*)E_MAlloc_Nzero(2);
	pText[0]=ArgInf.m_byte;
	pText[1]=0;
	return pText;	
}
