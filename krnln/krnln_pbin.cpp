#include "stdafx.h"

//�ֽڼ����� - ָ�뵽�ֽڼ�
/*
    ���ø�ʽ�� ���ֽڼ��� ָ�뵽�ֽڼ� �������� �ڴ�����ָ�룬������ �ڴ����ݳ��ȣ� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�pbin
    ����ָ���ڴ�ָ����ָ���ַ����һ�����ݣ�ע����ñ�����ǰһ��Ҫȷ�����ṩ���ڴ��ַ����ʵ��Ч������������ʹ�ó��Ͼ����������Իص��ӳ����������DLL�����ӳ���������ȡ�ⲿ���ݡ�������Ϊ�߼����
    ����<1>������Ϊ���ڴ�����ָ�롱������Ϊ�������ͣ�int�������������ṩָ��һ���ڴ��ַ��ָ��ֵ��
    ����<2>������Ϊ���ڴ����ݳ��ȡ�������Ϊ�������ͣ�int�������������ṩ���ڴ��ַ�������ȡ�����ݳ��ȡ�
*/
LIBAPI(void*, krnln_pbin)
{
	PMDATA_INF pArgInf = &ArgInf;
	if (!pArgInf[0].m_pCompoundData) return NULL;
	INT nLen = pArgInf[1].m_int;
	if(nLen<=0) return NULL; // || IsBadReadPtr(pArgInf[0].m_pCompoundData,nLen)

	LPINT pText = (LPINT)E_MAlloc_Nzero(nLen+2*sizeof(INT));
	pText[0]=1;
	pText[1]=nLen;
	memcpy(pText+2,pArgInf[0].m_pCompoundData,nLen);

	return pText;
}
