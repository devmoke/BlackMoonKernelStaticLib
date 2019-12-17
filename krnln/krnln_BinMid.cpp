#include "stdafx.h"

//�ֽڼ����� - ȡ�ֽڼ��м�
/*
    ���ø�ʽ�� ���ֽڼ��� ȡ�ֽڼ��м� ���ֽڼ� ��ȡ�䲿�ֵ��ֽڼ��������� ��ʼȡ��λ�ã������� ��ȡ���ֽڵ���Ŀ�� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�BinMid
    ����һ���ֽڼ������а���ָ���ֽڼ��д�ָ��λ������ָ���������ֽڡ�������Ϊ�������
    ����<1>������Ϊ����ȡ�䲿�ֵ��ֽڼ���������Ϊ���ֽڼ���bin������
    ����<2>������Ϊ����ʼȡ��λ�á�������Ϊ�������ͣ�int������1Ϊ��λ�ã�2Ϊ��2��λ�ã�������ơ�
    ����<3>������Ϊ����ȡ���ֽڵ���Ŀ��������Ϊ�������ͣ�int������
*/
LIBAPI(void*, krnln_BinMid)
{
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_pBin == NULL)
		return NULL;
	INT nDataSize = pArgInf[0].m_pInt[1];
	INT nObjLen = pArgInf[2].m_int;
	if(nDataSize == 0 ||  nObjLen<= 0 )
		return NULL;
	INT nStart = pArgInf[1].m_int;
	if(nStart-1 > nDataSize)
		return NULL;
	if(nStart<=0)
		nStart = 1;
	if(nStart-1 + nObjLen >= nDataSize)
		nObjLen = nDataSize - nStart+1;
	nDataSize = nObjLen;


	return CloneBinData ((LPBYTE)(pArgInf[0].m_pBin + 2*sizeof(INT)+ nStart-1),nDataSize);
}
