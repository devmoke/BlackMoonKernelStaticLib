#include "stdafx.h"

//�ֽڼ����� - ȡ�ظ��ֽڼ�
/*
    ���ø�ʽ�� ���ֽڼ��� ȡ�ظ��ֽڼ� �������� �ظ��������ֽڼ� ���ظ����ֽڼ��� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�bin
    ����һ���ֽڼ������а���ָ���������ֽڼ��ظ������������Ϊ�������
    ����<1>������Ϊ���ظ�������������Ϊ�������ͣ�int������
    ����<2>������Ϊ�����ظ����ֽڼ���������Ϊ���ֽڼ���bin���������ֽڼ������ڽ������ص��ֽڼ������Ϊ�գ�������һ�����ֽڼ���
*/
LIBAPI(void*, krnln_bin)
{
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_int <=0 || pArgInf[1].m_pBin==NULL)
		return NULL;
	INT nLen = pArgInf[1].m_pInt[1];
	if(nLen==0)return NULL;

	LPBYTE pSrc = pArgInf[1].m_pBin + 2*sizeof(INT);
	INT nBuf = nLen * pArgInf[0].m_int;
	LPBYTE pData = (LPBYTE)E_MAlloc_Nzero(nBuf+2*sizeof(INT));
	LPBYTE pDest = pData;
	*(LPINT)pDest=1;
	pDest+=sizeof(INT);
	*(LPINT)pDest=nBuf;
	pDest+=sizeof(INT);
	for(INT i=0;i<pArgInf[0].m_int;i++)
	{
		memcpy(pDest,pSrc,nLen);
		pDest+=nLen;
	}
	return pData;
}
