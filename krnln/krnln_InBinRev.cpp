#include "stdafx.h"

extern "C" int inline MyMemCmp2(unsigned char* a, unsigned char* b, int len)
{
	for (int i=0; i < (len>>2); i++)
	{
		if (((int*)a)[0]!=((int*)b)[0])
			return 1;
		a+=4;b+=4;
	}
	if ((len&2) != 0)
	{
		if (((short*)a)[0]!=((short*)b)[0])
			return 1;
		a+=2;b+=2;
	}
	if ((len&1) != 0 && a[0]!=b[0])
		return 1;
	return 0;
}
//�ֽڼ����� - �����ֽڼ�
/*
    ���ø�ʽ�� �������͡� �����ֽڼ� ���ֽڼ� ����Ѱ���ֽڼ����ֽڼ� ��Ѱ�ҵ��ֽڼ����������� ��ʼ��Ѱλ�ãݣ� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�InBinRev
    ����һ�ֽڼ�����һ�ֽڼ��������ֵ�λ�ã�λ��ֵ�� 1 ��ʼ�����δ�ҵ������� -1��������Ϊ�������
    ����<1>������Ϊ������Ѱ���ֽڼ���������Ϊ���ֽڼ���bin������
    ����<2>������Ϊ����Ѱ�ҵ��ֽڼ���������Ϊ���ֽڼ���bin������
    ����<3>������Ϊ����ʼ��Ѱλ�á�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�1Ϊ��λ�ã�2Ϊ��2��λ�ã�������ƣ������ʡ�ԣ���Ѱ���ֽڼ�������Ĭ�ϴ��ײ���ʼ���������ֽڼ�������Ĭ�ϴ�β����ʼ��
*/
LIBAPI(int, krnln_InBinRev)
{ // �����ߺ� ��
 	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_pBin==NULL || pArgInf[1].m_pBin==NULL)
 		return -1;

	INT nLen = pArgInf[0].m_pInt[1];
	INT nSubLen = pArgInf[1].m_pInt[1];
	if (nLen <= 0 || nSubLen <= 0 || nSubLen > nLen) return -1;

	register unsigned char* pSrc = pArgInf[0].m_pBin + 2*sizeof(INT);
	int off;
	if (pArgInf[2].m_dtDataType == _SDT_NULL)
		off = nLen - nSubLen;
	else
	{
		off = pArgInf[2].m_int;
		if (off < 1) 
			return -1;
		if (off <= nLen)
			nLen = off;
		off = nLen - nSubLen;
	}

 	if (off < 0) return -1;

	register unsigned char* pDes = pArgInf[1].m_pBin + 2*sizeof(INT);
	int i;
	//int j;
	// ���Ӵ�ֱ�ӱ�������
	if (nSubLen == 1)
	{
		for (i = off; i >= 0; i--)
			if (pSrc[i] == pDes[0])
				return i + 1;
			
		return -1;
	}
	else if (nSubLen == 2)
	{
		for (i = off; i >= 0; i--)
			if (((short*)(pSrc+i))[0] == ((short*)pDes)[0])
				return i + 1;
			
		return -1;
	}
	else if (nSubLen == 3)
	{
		for (i = off; i >= 0; i--)
			if (((short*)(pSrc+i))[0] == ((short*)pDes)[0])
				if (pSrc[i+2] == pDes[2])
					return i + 1;
			
		return -1;
	}
	else if (nSubLen == 4)
	{
		for (i = off; i >= 0; i--)
			if (((int*)(pSrc+i))[0] == ((int*)pDes)[0])
				return i + 1;
			
		return -1;
	}
	else if (nSubLen == 5)
	{
		for (i = off; i >= 0; i--)
			if (((int*)(pSrc+i))[0] == ((int*)pDes)[0])
				if (pSrc[i+4] == pDes[4])
					return i + 1;
			
		return -1;
	}
	else if (nSubLen == 6)
	{
		for (i = off; i >= 0; i--)
			if (((int*)(pSrc+i))[0] == ((int*)pDes)[0])
				if (((short*)(pSrc+i+4))[0] == ((short*)(pDes+4))[0])
					return i + 1;
				
		return -1;
	}
 
// 	for (i = off; i >= 0; i--)
// 		if (MyMemCmp2(pSrc+i, pDes, nSubLen)==0)
//  			return i + 1;
// 
// 	return -1;
	// ���Ӵ�ʹ�� Sunday�㷨,
	register unsigned int next[256];
	for (i = 0; i < 256; i++)
		next[i] = nSubLen;
	for (i = nSubLen; i > 0; i--)
		next[pDes[i-1]] = i;

	register unsigned char* naddr = pSrc + off;
	for (; naddr >= pSrc; naddr -= next[naddr[-1]])
		if (MyMemCmp2(naddr, pDes, nSubLen)==0)
			return naddr - pSrc + 1;
		
	return -1;
}
// {// ����ԭ��
// 	PMDATA_INF pArgInf = &ArgInf;
// 	if(pArgInf[0].m_pBin==NULL || pArgInf[1].m_pBin==NULL)
// 		return -1;
// 
// 	INT nLen = pArgInf[0].m_pInt[1];
// 	INT nSubLen = pArgInf[1].m_pInt[1];
// 	if(nLen==0 || nSubLen==0 || nSubLen > nLen)return -1;
// 	
// 	INT nStart;
// 	INT nEnd = nLen - nSubLen;
// 	if(pArgInf[2].m_dtDataType ==_SDT_NULL || pArgInf[2].m_int <=0)
// 		nStart = nEnd;
// 	else{
// 		nStart = pArgInf[2].m_int - nSubLen;
// 		if(nStart <0)
// 			nStart = 0;
// 	}
// 	
// 	if(nStart > nEnd)
// 		nStart = nEnd;
// 
// 	LPBYTE pSrc = pArgInf[0].m_pBin + 2*sizeof(INT);
// 	LPBYTE pStart = pSrc + nStart;
// 	LPBYTE pObj = pArgInf[1].m_pBin + 2*sizeof(INT);
// 
// 
// 	
// 	while(pStart >= pSrc)
// 	{
// 		if(memcmp(pStart,pObj,nSubLen)==0)
// 		{
// 			nStart = pStart - pSrc +1;
// 			return nStart;
// 		}
// 		pStart--;
// 	}
// 
// 
// 	return -1;	
// }
