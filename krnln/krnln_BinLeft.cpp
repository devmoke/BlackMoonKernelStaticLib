#include "stdafx.h"

//�ֽڼ����� - ȡ�ֽڼ����
/*
    ���ø�ʽ�� ���ֽڼ��� ȡ�ֽڼ���� ���ֽڼ� ��ȡ�䲿�ֵ��ֽڼ��������� ��ȡ���ֽڵ���Ŀ�� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�BinLeft
    ����һ���ֽڼ������а���ָ���ֽڼ��д��������ָ���������ֽڡ�������Ϊ�������
    ����<1>������Ϊ����ȡ�䲿�ֵ��ֽڼ���������Ϊ���ֽڼ���bin������
    ����<2>������Ϊ����ȡ���ֽڵ���Ŀ��������Ϊ�������ͣ�int������
*/
LIBAPI(void*, krnln_BinLeft)
{
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_pBin == NULL)
		return NULL;
	INT nDataSize = pArgInf[0].m_pInt[1];
	if(nDataSize == 0 || pArgInf[1].m_int <= 0 )
		return NULL;
	if(nDataSize > pArgInf[1].m_int)
		nDataSize = pArgInf[1].m_int;

	return CloneBinData ((LPBYTE)(pArgInf[0].m_pInt + 2),nDataSize);
}
