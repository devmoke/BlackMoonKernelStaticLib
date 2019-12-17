#include "stdafx.h"
#include "mem.h"
#include "Myfunctions.h"


//�ı����� - �ָ��ı�
/*
    ���ø�ʽ�� ���ı������页 �ָ��ı� ���ı��� ���ָ��ı������ı��� �����ָ���ı��ݣ��������� Ҫ���ص����ı���Ŀ�ݣ� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�split
    ��ָ���ı����зָ���طָ���һά�ı����顣������Ϊ�������
    ����<1>������Ϊ�����ָ��ı���������Ϊ���ı��ͣ�text�������������ֵ��һ������Ϊ����ı����򷵻�һ�������飬��û���κγ�Ա�����顣
    ����<2>������Ϊ�������ָ���ı���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ�����ֵ���ڱ�ʶ���ı��߽硣�����ʡ�ԣ���Ĭ��ʹ�ð�Ƕ����ַ���Ϊ�ָ����������һ������Ϊ����ı����򷵻ص����������һ����Ա���������ġ����ָ��ı�����
    ����<3>������Ϊ��Ҫ���ص����ı���Ŀ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ʡ�ԣ���Ĭ�Ϸ������е����ı���

*/
#define IS_CC(p) p<0

LIBAPI(void*, krnln_split)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	INT nCount = pArgInf [2].m_dtDataType == _SDT_NULL ? 0x7FFFFFFF : pArgInf [2].m_int;
	LPBYTE p;
	if (nCount <= 0) 
		return E_NULLARRAY();

	char* pSub = pArgInf [1].m_dtDataType == _SDT_NULL ? "," : pArgInf [1].m_pText;
	INT nSubLen = mystrlen(pSub);

	char* pSrc = pArgInf[0].m_pText;
	if (!pSrc || !*pSrc)
		return E_NULLARRAY();

	if (nSubLen==0)
		nCount = -1;//����һ����Ա

	// ��ʼ����
	PINT pTb = (PINT)malloc(256);
	if (!pTb)
		return E_NULLARRAY();

	pTb[0] = 256; // TSize
	pTb[1] = 0; // Count
	pTb[2] = 0; // TLen

	INT nPos;
	char* pFirst = pSrc;
	char* cp = pSrc;
	for (; nCount > 0; nCount--)
	{
		nPos = mystrstr((char*)cp, (char*)pSub);
		if (nPos == -1)
			break;
		cp += nPos;
		recSub(&pTb, (INT)pFirst, cp - pFirst);
		cp += nSubLen;
		pFirst = cp;
	}
	
	INT nSlen = mystrlen(cp) + cp - pSrc;
	char* pLast = pSrc + nSlen;
	if (pLast - pFirst > 0 && nCount != 0)
		recSub(&pTb, (INT)pFirst, pLast - pFirst);

	// �����������ݡ�
	nCount = pTb[1];
	PINT pTbtmp = pTb;
	pTbtmp += 3;
	INT nSize = nCount * sizeof (DWORD);
	p = (LPBYTE)E_MAlloc_Nzero (sizeof (INT) * 2 + nSize);
	*(LPINT)p = 1;  // ����ά����
	*(LPINT)(p + sizeof (INT)) = nCount;
	LPINT pp = (LPINT)(p + 2*sizeof(INT));
	for (int i=0; i < nCount; i++)
	{
		*pp = (INT)CloneTextData((char*)(pTbtmp[0]), pTbtmp[1]);
		pTbtmp += 2;
		pp++;
	}

	if (pTb)
		free(pTb);
	return p;  // �����������顣
}
// {// ����ԭ��
// 	PMDATA_INF pArgInf = &ArgInf;
// 	LPTSTR szBeSplited = pArgInf [0].m_pText;
// 	// ���ĳ������ AS_DEFAULT_VALUE_IS_EMPTY ��־�Ĳ����û�������û��Ϊ���ṩ����ֵ��
// 	// ������������Ϊ _SDT_NULL ��
// 	LPTSTR szMark = pArgInf [1].m_dtDataType == _SDT_NULL ? "," : pArgInf [1].m_pText;
// 	INT nCount = pArgInf [2].m_dtDataType == _SDT_NULL ? -1 : max (0, pArgInf [2].m_int);
// 	
// 	INT nLen1 = strlen (szBeSplited);
// 	INT nLen2 = strlen (szMark);
// 	
// 	CMyDWordArray aryText;
// 	
// 	if (nLen1 > 0 && nCount != 0)
// 	{
// 		if (nLen2 == 0)
// 		{
// 			// �й� CloneTextData ��μ�
// 			/*INT nLen = strlen(szBeSplited);
// 			char *pText = (char*)E_MAlloc(nLen+1);
// 			strcpy(pText,szBeSplited);*/
// 			char *pText = CloneTextData(szBeSplited);
// 			aryText.Add ((DWORD)pText);
// 		}
// 		else
// 		{
// 			LPTSTR pBegin = szBeSplited;
// 			LPTSTR ps = pBegin;
// 			
// 			while (nLen1 >= nLen2)
// 			{
// 				if (!memcmp (ps, szMark, nLen2))
// 				{
// 					INT nLen = ps - pBegin;
// 					/*char *pText = (char*)E_MAlloc(nLen+1);
// 					strncpy(pText,pBegin,nLen);
// 					pText[nLen]=0;*/
// 					char *pText = CloneTextData(pBegin,nLen);
// 					aryText.Add ((DWORD)pText);
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
// 					if (IS_CC (*ps))
// 					{
// 						if (ps [1] == 0)  break;
// 						ps++;
// 						nLen1--;
// 					}
// 					ps++;
// 					nLen1--;
// 				}
// 			}
// 			
// 			if (*pBegin != '\0' && nCount != 0)
// 			{
// 				/*INT nLen = strlen(pBegin);
// 				char *pText = (char*)E_MAlloc(nLen+1);
// 				strcpy(pText,pBegin);*/
// 				char *pText = CloneTextData(pBegin);
// 				aryText.Add ((DWORD)pText);
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
// 	//MessageBox(NULL,"ok2",NULL,MB_OK);
// 	//Sleep(100);
// 	return p;  // �����������顣
// }
