#include "stdafx.h"

//�ֽڼ����� - ȡ�ֽڼ��ұ�
/*
    ���ø�ʽ�� ���ֽڼ��� ȡ�ֽڼ��ұ� ���ֽڼ� ��ȡ�䲿�ֵ��ֽڼ��������� ��ȡ���ֽڵ���Ŀ�� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�BinRight
    ����һ���ֽڼ������а���ָ���ֽڼ��д��ұ�����ָ���������ֽڡ�������Ϊ�������
    ����<1>������Ϊ����ȡ�䲿�ֵ��ֽڼ���������Ϊ���ֽڼ���bin������
    ����<2>������Ϊ����ȡ���ֽڵ���Ŀ��������Ϊ�������ͣ�int������
*/
LIBAPI(void*, krnln_BinRight)
{
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_pBin == NULL)
		return NULL;
	INT nDataSize = pArgInf[0].m_pInt[1];
	if(nDataSize == 0 || pArgInf[1].m_int <= 0 )
		return NULL;
	INT nOffset = nDataSize - pArgInf[1].m_int;
	if(nOffset < 0)
		nOffset = 0;
	nDataSize = pArgInf[1].m_int;

	return CloneBinData ((LPBYTE)(pArgInf[0].m_pBin + 2*sizeof(INT)+ nOffset),nDataSize);
}
