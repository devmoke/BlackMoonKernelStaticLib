#include "stdafx.h"

//������ȡ - ����������
/*
    ���ø�ʽ�� ���ı��͡� ���������� ���ı��� �����������ƣ� - ϵͳ����֧�ֿ�->������ȡ
    Ӣ�����ƣ�GetEnv
    �����ı�����������һ������ϵͳ�����������ɹ�ʱ������ȡ�õ�ֵ��ʧ���򷵻ؿ��ı���������Ϊ�������
    ����<1>������Ϊ�������������ơ�������Ϊ���ı��ͣ�text������
*/
LIBAPI(char*, krnln_GetEnv)
{
	char* pBuf ;
	UINT nLen = MAX_PATH;
	UINT nRet;
redo:
	pBuf = (char*)E_MAlloc(nLen);
	nRet = GetEnvironmentVariable(ArgInf.m_pText,pBuf,nLen);
	if(nRet > nLen)
	{
		E_MFree(pBuf);
		nLen = nRet;
		goto redo;
	}
	return pBuf;
}
