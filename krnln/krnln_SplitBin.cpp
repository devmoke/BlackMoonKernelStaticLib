#include "stdafx.h"
#include "mem.h"
#include "Myfunctions.h"
//�ֽڼ����� - �ָ��ֽڼ�
/*
    ���ø�ʽ�� ���ֽڼ����页 �ָ��ֽڼ� ���ֽڼ� ���ָ��ֽڼ������ֽڼ� �����ָ���ֽڼ��ݣ��������� Ҫ���ص����ֽڼ���Ŀ�ݣ� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�SplitBin
    ��ָ���ֽڼ����зָ���طָ���һά�ֽڼ����顣������Ϊ�������
    ����<1>������Ϊ�����ָ��ֽڼ���������Ϊ���ֽڼ���bin�������������ֵ��һ������Ϊ����ֽڼ����򷵻�һ�������飬��û���κγ�Ա�����顣
    ����<2>������Ϊ�������ָ���ֽڼ���������Ϊ���ֽڼ���bin���������Ա�ʡ�ԡ����ڱ�ʶ���ֽڼ��߽硣�����������ʡ�ԣ���Ĭ��ʹ���ֽ� 0 ��Ϊ�ָ�����
    ����<3>������Ϊ��Ҫ���ص����ֽڼ���Ŀ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ʡ�ԣ���Ĭ�Ϸ������е����ֽڼ���
*/
LIBAPI(void*, krnln_SplitBin)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	INT nCount = pArgInf [2].m_dtDataType == _SDT_NULL ? 0x7FFFFFFF : pArgInf [2].m_int;
	if (nCount <= 0) 
		return E_NULLARRAY();
	
	LPBYTE pSrc = pArgInf[0].m_pBin ;
	if (!pSrc)
		return E_NULLARRAY();
	INT nSLen = pArgInf[0].m_pInt[1];
	if (nSLen <= 0)
		return E_NULLARRAY();
	pSrc += 2*sizeof(INT);

	LPBYTE pSub = NULL;
	INT nSubLen = 0;
	BYTE bMark [] = {0,0};
	if(pArgInf [1].m_dtDataType == _SDT_NULL)
	{
		pSub = bMark;
		nSubLen = 1;
	}
	else
	{
		if (pArgInf [1].m_pBin)
		{
			pSub = pArgInf [1].m_pBin + 2*sizeof(INT);
			nSubLen =  pArgInf [1].m_pInt[1];
		}
	}

	if (nSubLen == 0)
		nCount = -1;//����һ����Ա

	// ��ʼ����
	PINT pTb = (PINT)malloc(256);
	if (!pTb)
		return E_NULLARRAY();
	
	pTb[0] = 256; // TSize
	pTb[1] = 0; // Count
	pTb[2] = 0; // TLen
	
	INT nPos;
	INT nSYLen = nSLen;
	LPBYTE pFirst = pSrc;
	LPBYTE cp = pSrc;
	for (; nCount > 0; nCount--)
	{
		nPos = myinstring(cp, nSYLen, pSub, nSubLen);
		if (nPos == -1)
			break;
		cp += nPos;
		recSub(&pTb, (INT)pFirst, cp - pFirst);
		cp += nSubLen;
		nSYLen -= nPos + nSubLen;
		pFirst = cp;
	}
	LPBYTE pLast = pSrc + nSLen;
	if (pLast - pFirst > 0 && nCount != 0)
		recSub(&pTb, (INT)pFirst, pLast - pFirst);
	
	// �����������ݡ�
	nCount = pTb[1];
	PINT pTbtmp = pTb;
	pTbtmp += 3;
	INT nSize = nCount * sizeof (DWORD);
	LPBYTE p = (LPBYTE)E_MAlloc_Nzero (sizeof (INT) * 2 + nSize);
	*(LPINT)p = 1;  // ����ά����
	*(LPINT)(p + sizeof (INT)) = nCount;
	LPINT pp = (LPINT)(p + 2*sizeof(INT));
	for (int i=0; i < nCount; i++)
	{
		*pp = (INT)CloneBinData((LPBYTE)(pTbtmp[0]), pTbtmp[1]);
		pTbtmp += 2;
		pp++;
	}
	
	if (pTb)
		free(pTb);
	return p;  // �����������顣
}
// {// ����ԭ��
// 	PMDATA_INF pArgInf = &ArgInf;
// 	
// 	LPBYTE szBeSplited = NULL;
// 	if(pArgInf [0].m_pBin)
// 	{
// 		szBeSplited = pArgInf [0].m_pBin+2*sizeof(INT);
// 	}
// 	// ���ĳ������ AS_DEFAULT_VALUE_IS_EMPTY ��־�Ĳ����û�������û��Ϊ���ṩ����ֵ��
// 	// ������������Ϊ _SDT_NULL ��
// 	LPBYTE szMark = NULL;
// 	INT nLen2 = 0;
// 	BYTE bMark []={0,0};
// 	if(pArgInf [1].m_dtDataType == _SDT_NULL)
// 	{
// 		szMark = bMark;
// 		nLen2 = 1;
// 	}
// 	else
// 	{
// 		if(pArgInf [1].m_pBin)
// 		{
// 			szMark = pArgInf [1].m_pBin +2*sizeof(INT);
// 			nLen2 =  pArgInf [1].m_pInt[1];
// 		}
// 	}
// 	INT nCount = pArgInf [2].m_dtDataType == _SDT_NULL ? -1 : max (0, pArgInf [2].m_int);
// 	
// 	INT nLen1 = szBeSplited ? pArgInf [0].m_pInt[1]:0;
// 	 
// 	
// 	CMyDWordArray aryText;
// 	
// 	if (nLen1 > 0 && nCount != 0)
// 	{
// 		if (nLen2 == 0)
// 		{
// 			// �й� CloneTextData ��μ�
// 			LPBYTE pData = CloneBinData(szBeSplited,nLen1);
// 			aryText.Add ((DWORD)pData);
// 		}
// 		else
// 		{
// 			LPBYTE pBegin = szBeSplited;
// 			LPBYTE ps = pBegin;
// 			LPBYTE pEnd = pBegin +  nLen1;
// 			
// 			while (nLen1 >= nLen2)
// 			{
// 				if (!memcmp (ps, szMark, nLen2))
// 				{
// 					INT nLen = ps - pBegin;
// 
// 					LPBYTE pData = CloneBinData(pBegin,nLen);
// 					aryText.Add ((DWORD)pData);
// 					ps += nLen2;
// 					nLen1 -= nLen2;
// 					pBegin = ps;
// 					if (nCount != -1)
// 					{
// 						nCount--;
// 						if (nCount == 0)  break;
// 					}
// 				}
// 				else
// 				{
// 					ps++;
// 					nLen1--;
// 				}
// 			}
// 			
// 			if (pBegin < pEnd && nCount != 0)
// 			{
// 				INT nLen = pEnd - pBegin;
// 				LPBYTE pData = CloneBinData(pBegin,nLen);
// 				aryText.Add ((DWORD)pData);
// 			}
// 		}
// 	}
// 	
// 	// �����������ݡ�
// 	INT nSize = aryText.GetDWordCount () * sizeof (DWORD);
// 	LPBYTE p = (LPBYTE)E_MAlloc_Nzero (sizeof (INT) * 2 + nSize);
// 	*(LPINT)p = 1;  // ����ά����
// 	*(LPINT)(p + sizeof (INT)) = aryText.GetDWordCount ();
// 	memcpy (p + sizeof (INT) * 2, aryText.GetPtr (), nSize);
// 	
// 	return p;  // �����������顣
// }
