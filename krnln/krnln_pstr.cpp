#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - ָ�뵽�ı�
/*
    ���ø�ʽ�� ���ı��͡� ָ�뵽�ı� �������� �ڴ��ı�ָ�룩 - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�pstr
    ����ָ���ڴ�ָ����ָ���ַ�����ı���ע����ñ�����ǰһ��Ҫȷ�����ṩ���ڴ�ָ����ʵ��Ч����ָ��һ�������ַ��������ı���������������ʹ�ó��Ͼ����������Իص��ӳ����������DLL�����ӳ���������ȡ�ⲿ���ݡ�������Ϊ�߼����
    ����<1>������Ϊ���ڴ��ı�ָ�롱������Ϊ�������ͣ�int�������������ṩָ��һ�������ַ��������ı����ڴ�ָ��ֵ��
*/
LIBAPI(char*, krnln_pstr)
{
	if (!ArgInf.m_pText || !*(ArgInf.m_pText)) return NULL;
	int nLen = mystrlen(ArgInf.m_pText);
	if(nLen==0)	return NULL;

	char *pText = (char*)E_MAlloc_Nzero(nLen+1);
	
	memcpy(pText, ArgInf.m_pText, nLen);
	pText[nLen] = '\0';
	return pText;
}
