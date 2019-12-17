#include "stdafx.h"

//�ֽڼ����� - �ֽڼ��滻
/*
    ���ø�ʽ�� ���ֽڼ��� �ֽڼ��滻 ���ֽڼ� ���滻�䲿�ֵ��ֽڼ��������� ��ʼ�滻λ�ã������� �滻���ȣ����ֽڼ� �����滻���ֽڼ��ݣ� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�RpBin
    ��ָ���ֽڼ���ĳһ�������������ֽڼ��滻��Ȼ�󷵻��滻��Ľ����������Ϊ�������
    ����<1>������Ϊ�����滻�䲿�ֵ��ֽڼ���������Ϊ���ֽڼ���bin������
    ����<2>������Ϊ����ʼ�滻λ�á�������Ϊ�������ͣ�int�������滻����ʼλ�ã�1Ϊ��λ�ã�2Ϊ��2��λ�ã�������ơ�
    ����<3>������Ϊ���滻���ȡ�������Ϊ�������ͣ�int������
    ����<4>������Ϊ�������滻���ֽڼ���������Ϊ���ֽڼ���bin���������Ա�ʡ�ԡ������������ʡ�ԣ���ɾ���ֽڼ��е�ָ�����֡�
*/
LIBAPI(void*, krnln_RpBin)
{// �����ߺŸ�
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_pBin==NULL)
		return NULL;
	LPBYTE pBin = pArgInf[0].m_pBin + 2*sizeof(INT);
	LPBYTE pSubBin = pArgInf[3].m_pBin + 2*sizeof(INT);
	INT nSubLen;
	INT nLen = pArgInf[0].m_pInt[1];
	if (pArgInf[3].m_dtDataType==_SDT_NULL)
		nSubLen = 0;
	else
		nSubLen = pArgInf[3].m_pInt[1];
	
	INT nRpLen = pArgInf[2].m_int;
	if (nRpLen < 0) nRpLen = 0;
	
	INT nStart = pArgInf[1].m_int - 1;
	if (nStart < 0) 
		nStart = 0;
	else if (nStart > nLen)
		nStart = nLen - 1;
	
	// �³��� = Դ���� - �滻���� + �Ӵ�����
	// ��ʼ�� + �滻���� <= Դ����
	if (nStart + nRpLen > nLen) nRpLen = nLen - nStart;
	INT nNewLen = nLen - nRpLen + nSubLen;
	if (nNewLen <= 0) return NULL;
	
	LPBYTE pRetn;
	LPBYTE pTemp;
	if (nStart == 0) // ��ǰƴ��
	{
		if (nSubLen == 0) // �Ӵ�Ϊ��
			return CloneBinData(pBin + nRpLen, nNewLen);
		
		pRetn = (LPBYTE)E_MAlloc_Nzero ((DWORD)(nNewLen + 2*sizeof(INT)));
		pTemp = pRetn;
		*(LPINT)pTemp = 1; //һά����
		pTemp+=sizeof(INT);
		*(LPINT)pTemp = nNewLen;
		pTemp+=sizeof(INT);
		memcpy(pTemp, pSubBin, nSubLen);
		memcpy(pTemp + nSubLen, pBin + nRpLen, nLen - nRpLen);
		return pRetn;
	}
	else if (nStart >= nLen) // ����ƴ��
	{
		if (nSubLen == 0) // �Ӵ�Ϊ��
			return CloneBinData(pBin, nNewLen);
		
		pRetn = (LPBYTE)E_MAlloc_Nzero ((DWORD)(nNewLen + 2*sizeof(INT)));
		pTemp = pRetn;
		*(LPINT)pTemp = 1; //һά����
		pTemp+=sizeof(INT);
		*(LPINT)pTemp = nNewLen;
		pTemp+=sizeof(INT);
		memcpy(pTemp, pBin, nLen);
		memcpy(pTemp + nLen, pSubBin, nSubLen);
		return pRetn;
	}
	
	// �м�ƴ��
	pRetn = (LPBYTE)E_MAlloc_Nzero ((DWORD)(nNewLen + 2*sizeof(INT)));
	pTemp = pRetn;

	*(LPINT)pTemp = 1; //һά����
	pTemp+=sizeof(INT);
	*(LPINT)pTemp = nNewLen;
	pTemp+=sizeof(INT);

	memcpy(pTemp, pBin, nStart);
	pTemp+=nStart;
	if (nSubLen > 0)
	{
		memcpy(pTemp, pSubBin, nSubLen);
		pTemp+=nSubLen;
	}
	if (nStart + nSubLen < nNewLen)
		memcpy(pTemp, pBin + nStart + nRpLen, nLen - nStart - nRpLen);
	
	return pRetn;
}
// { ����ԭ��
// 	PMDATA_INF pArgInf = &ArgInf;
// 	if(pArgInf[0].m_pBin==NULL)
// 		return NULL;
// 	UINT nLen = pArgInf[0].m_pInt[1];
// 	
// 	if(nLen==0 )
// 	{
// 		if(pArgInf[3].m_pBin == _SDT_NULL)
// 			return NULL;
// 		nLen = pArgInf[3].m_pInt[1];
// 		if(nLen==0)
// 			return NULL;
// 		
// 		return CloneBinData(pArgInf[3].m_pBin + 2*sizeof(INT),nLen);
// 	}
// 	LPBYTE pSrc = pArgInf[0].m_pBin + 2 *sizeof(INT);
// 	if(pArgInf[1].m_int > nLen || pArgInf[2].m_int <= 0)
// 		return CloneBinData (pSrc, nLen);
// 
// 	INT nSubStr = 0;
// 	LPBYTE pSubStr = NULL;
// 	
// 	if(pArgInf[3].m_dtDataType != _SDT_NULL && pArgInf[3].m_pBin)
// 	{
// 		pSubStr = pArgInf[3].m_pBin + 2 *sizeof(INT);
// 		nSubStr = pArgInf[3].m_pInt[1];
// 	}
// 	if(pArgInf[1].m_int <=0 )
// 		pArgInf[1].m_int = 1;
// 	INT nForce = pArgInf[1].m_int - 1;
// 	INT nBack = nLen - nForce;
// 	BOOL bStrcat;
// 	INT nCount ;
// 	if(nBack < pArgInf[2].m_int)
// 	{
// 		nCount = nForce + nSubStr;
// 		bStrcat = TRUE;
// 	}else{
// 
// 		nCount = nLen - pArgInf[2].m_int + nSubStr;
// 		bStrcat = FALSE;
// 	}
// 
// 	LPBYTE pText = (LPBYTE)E_MAlloc(nCount+2 *sizeof(INT));
// 	LPBYTE pDest = (LPBYTE)pText;
// 	*(LPINT)pDest=1;
// 	pDest+=sizeof(INT);
// 	*(LPINT)pDest=nCount;
// 	pDest+=sizeof(INT);
// 
// 	if(bStrcat)
// 	{
// 		memcpy(pDest,pSrc,nForce);
// 		if(pSubStr)
// 		{
// 			pDest+=nForce;
// 			memcpy(pDest,pSubStr,nSubStr);
// 		}
// 	}
// 	else
// 	{
// 		memcpy(pDest,pSrc,nForce);
// 		pDest+=nForce;
// 		if(pSubStr)
// 		{
// 			memcpy(pDest,pSubStr,nSubStr);
// 			pDest+=nSubStr;
// 		}
// 		nBack = nBack-pArgInf[2].m_int;
// 		pSubStr = pSrc + nForce + pArgInf[2].m_int;
// 		memcpy(pDest,pSubStr,nBack);
// 	}
// 	return pText;
// }
