#include "stdafx.h"

//�ı����� - ȡ�հ��ı�
/*
    ���ø�ʽ�� ���ı��͡� ȡ�հ��ı� �������� �ظ������� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�space
    ���ؾ���ָ����Ŀ��ǿո���ı���������Ϊ�������
    ����<1>������Ϊ���ظ�������������Ϊ�������ͣ�int������
*/
LIBAPI(char*, krnln_space)
{
	if(ArgInf.m_int<= 0) return NULL;
	char *pText = (char*)E_MAlloc_Nzero(ArgInf.m_int+1);
	memset(pText,32,ArgInf.m_int);
	pText[ArgInf.m_int]=0;
	return pText;	
}
