#include "stdafx.h"
#include "mem.h"
#include "Myfunctions.h"
//�ı����� - ���ı��滻
/*
    ���ø�ʽ�� ���ı��͡� ���ı��滻 ���ı��� �����滻���ı����ı��� �����滻�����ı������ı��� �����滻�����ı��ݣ��������� �����滻����ʼλ�ãݣ��������� �滻���еĴ����ݣ��߼��� �Ƿ����ִ�Сд�� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�RpSubText
    ����һ���ı������ı���ָ�������ı��ѱ��滻����һ���ı��������滻�����Ĵ���Ҳ�Ǳ�ָ���ġ�������Ϊ�������
    ����<1>������Ϊ�������滻���ı���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ�������滻�����ı���������Ϊ���ı��ͣ�text������
    ����<3>������Ϊ�������滻�����ı���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ������������ʡ�ԣ�Ĭ��Ϊ���ı���
    ����<4>������Ϊ�������滻����ʼλ�á�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵָ�����滻���ı�����ʼ����λ�á����ʡ�ԣ�Ĭ�ϴ� 1 ��ʼ��
    ����<5>������Ϊ���滻���еĴ�����������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵָ�������ı������滻�Ĵ��������ʡ�ԣ�Ĭ�Ͻ������п��ܵ��滻��
    ����<6>������Ϊ���Ƿ����ִ�Сд��������Ϊ���߼��ͣ�bool��������ʼֵΪ���桱��Ϊ�����ִ�Сд��Ϊ�ٲ����֡�


char* StrCpyForE(char* pSrc)
{
	INT nLen = strlen(pSrc);
	char *pText = (char*)E_MAlloc(nLen+1);
	strcpy(pText,pSrc);
	return pText;
}*/
LIBAPI(char*, krnln_RpSubText)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	char* pSrc = pArgInf[0].m_pText;
	if (!pSrc || !*pSrc) return NULL;
	//��ʼ�滻λ��
	INT nStart;
	if (pArgInf[3].m_dtDataType == _SDT_NULL || pArgInf[3].m_int <= 1)
		nStart = 0;
	else
		nStart = pArgInf[3].m_int - 1;
	//�жϿ�ʼλ��
	char* cp = pSrc;
	char* pStart = pSrc + nStart;
	for (; *cp && cp < pStart; cp++)
		if (*cp < 0) cp++; // ����
	//MessageBox(NULL,"1","432",MB_OK);
	if (!*cp)
		return CloneTextData(pSrc, cp - pSrc);

	INT nSLen = (cp + mystrlen(cp)) - pSrc;
	//MessageBox(NULL,"2","432",MB_OK);
	//�������ı�
	char* pDes = pArgInf[1].m_pText;
	INT nDLen = 0;
	if (pDes)
		nDLen = mystrlen(pDes);
	//�滻����
	//MessageBox(NULL,"3","432",MB_OK);
	INT nCount = pArgInf[4].m_int;
	if (pArgInf[4].m_dtDataType == _SDT_NULL)
		nCount = 0x7FFFFFFF;// ����滻����21��
	//MessageBox(NULL,"4","432",MB_OK);
	if (nDLen <=0 || nCount<=0) // �ؼ��������Ϸ���ֱ�ӷ���ԭ�ı�
		return CloneTextData(pSrc, nSLen);
	//MessageBox(NULL,"5","432",MB_OK);
	char* pSub;
	INT nSubLen = 0;
	if (pArgInf[2].m_dtDataType != _SDT_NULL)
	{
		pSub = pArgInf[2].m_pText;
		if (pSub)
			nSubLen = mystrlen(pSub);
	}
	//MessageBox(NULL,"6","432",MB_OK);
	// ��ʼ����
	PINT pTb = (PINT)malloc(256);
	if (!pTb)
		return CloneTextData(pSrc, nSLen);
	//MessageBox(NULL,"123","432",MB_OK);
	pTb[0] = 256; // TSize
	pTb[1] = 0; // Count
	pTb[2] = 0; // TLen
	//MessageBox(NULL,"7","432",MB_OK);
	INT nPos;
	char* pFirst = pSrc;
	char* pLast = pSrc + nSLen;
	//char* pMsg = (char*)malloc(256);
	//sprintf(pMsg,"addr:%x",pTb);
	//MessageBox(NULL,pMsg,"432",MB_OK);
	if (pArgInf[5].m_bool) // ���ִ�Сд
	{
		for (; nCount > 0; nCount--)
		{
			nPos = mystrstr((char*)cp, (char*)pDes);
			if (nPos == -1)
				break;
			if (cp + nPos - pFirst > 0)
				recSub(&pTb, (INT)pFirst, cp + nPos - pFirst);
		
			if (nSubLen > 0)
				recSub(&pTb, (INT)pSub, nSubLen);
		
			cp += nPos + nDLen;
			pFirst = cp;
		}
	}
	else
	{
		for (; nCount > 0; nCount--)
		{
			nPos = mystristr((char*)cp, (char*)pDes);
			if (nPos == -1)
				break;
			if (cp + nPos - pFirst > 0)
				recSub(&pTb, (INT)pFirst, cp + nPos - pFirst);
			
			if (nSubLen > 0)
				recSub(&pTb, (INT)pSub, nSubLen);
			
			cp += nPos + nDLen;
			pFirst = cp;
		}
	}
	//MessageBox(NULL,"8","432",MB_OK);
	if (pLast - pFirst > 0)
		recSub(&pTb, (INT)pFirst, pLast - pFirst);
	
	//MessageBox(NULL,"9","432",MB_OK);
	// ���Ƽ�����
	char* pRetn = (char*)E_MAlloc_Nzero(pTb[2] + 1);
	char* pRetnTmp = pRetn;
	
	nCount = pTb[1];
	PINT pTbtmp = pTb;
	pTbtmp += 3;
	INT nTLen;
	//sprintf(pMsg,"nCount:%d,addr:%x",nCount,pTb);
	//MessageBox(NULL,pMsg,"432",MB_OK);
	//MessageBox(NULL,"10","432",MB_OK);
	for (int i = 0; i < nCount; i++)
	{
		nTLen = pTbtmp[1];
		//sprintf(pMsg,"addr:%x,nTLen:%d",pTbtmp[0],nTLen);
		//MessageBox(NULL,pMsg,"432",MB_OK);
		memcpy(pRetnTmp, (void*)(pTbtmp[0]), nTLen);
		pRetnTmp += nTLen;
		pTbtmp += 2;
	}
	//MessageBox(NULL,"11","432",MB_OK);
	pRetn[pTb[2]] = '\0';
	if (pTb)
		free(pTb);
	//MessageBox(NULL,"12","432",MB_OK);
	return pRetn;
}
// { // ����ԭ��
// 	PMDATA_INF pArgInf = &ArgInf;
// 	INT nLen = strlen(ArgInf.m_pText);
// 	INT nSubLen = strlen(pArgInf[1].m_pText);
// 	if(nLen==0)return NULL;
// 	if(nSubLen==0 || nSubLen > nLen)
// 		return CloneTextData(ArgInf.m_pText);
// 	
// 	char* pStrRpl = NULL;
// 	INT nStrRpl = 0;
// 	if(pArgInf[2].m_dtDataType !=_SDT_NULL)
// 	{
// 		pStrRpl = pArgInf[2].m_pText;
// 		nStrRpl = strlen(pStrRpl);
// 	}
// 
// 	INT nStart;
// 	if(pArgInf[3].m_dtDataType ==_SDT_NULL)
// 		nStart = 1;
// 	else
// 		nStart = pArgInf[3].m_int;
// 
// 	INT nRplCount;
// 	if(pArgInf[4].m_dtDataType ==_SDT_NULL)
// 		nRplCount = 0x7fffffff;
// 	else
// 		nRplCount = pArgInf[4].m_int;
// 
// 	INT nEnd = nLen - nSubLen;
// 	if(nStart > nEnd+1 || nRplCount <= 0  || nStart <= 0)//Ѱ�ҵ��ı����ڿ�ʼѰ��λ�� �� û���滻����
// 		return CloneTextData(ArgInf.m_pText);
// //��ʼ�滻
// 	CFreqMem cDest;
// 
// 	char* pStart = pArgInf->m_pText + nStart -1;
// 	char* pEnd = pArgInf->m_pText + nEnd+1;
// 	INT nFind = 0;
// 	char* pSrc = pArgInf->m_pText;
// 	if(pArgInf[5].m_bool) //���ִ�Сд
// 	{
// 		while(pStart < pEnd)
// 		{
// 			if(strncmp(pStart,pArgInf[1].m_pText,nSubLen)==0)
// 			{
// 				INT nStr = pStart - pSrc;
// 				cDest.Append((LPBYTE)pSrc,nStr);//�����ϴζ�
// 				if(pStrRpl)
// 					cDest.Append((LPBYTE)pStrRpl,nStrRpl);//�����滻�ı�
// 
// 				pStart+=nSubLen;
// 				pSrc = pStart; //����һ��;
// 				nFind++;
// 				if(nFind == nRplCount)
// 					break;
// 
// 			}
// 			else
// 			{
// 				if(*pStart<0)
// 					pStart+=2;
// 				else
// 					pStart++;
// 			}
// 		}
// 
// 	}
// 	else
// 	{
// 		while(pStart < pEnd)
// 		{
// 			if(strnicmp(pStart,pArgInf[1].m_pText,nSubLen)==0)
// 			{
// 				INT nStr = pStart - pSrc;
// 				cDest.Append((LPBYTE)pSrc,nStr);//�����ϴζ�
// 				if(pStrRpl)
// 					cDest.Append((LPBYTE)pStrRpl,nStrRpl);//�����滻�ı�
// 
// 				pStart+=nSubLen;
// 				pSrc = pStart; //����һ��;
// 				nFind++;
// 				if(nFind == nRplCount)
// 					break;
// 			}
// 			else
// 			{
// 
// 				if(*pStart<0)
// 					pStart+=2;
// 				else
// 					pStart++;
// 			}
// 
// 		}
// 	}
// 	if(pStart - pArgInf->m_pText<= nLen){
// 		INT nLen = tcsallbytes(pSrc);
// 		cDest.Append((LPBYTE)pSrc, nLen);
// 	}
// 	char* m_pText = 
// 		CloneTextData((char *)cDest.GetPtr(),cDest.GetSize());
// 	cDest.Free();
// 	return m_pText;
// 	/*
// //ͳ���ҵ��Ĵ����ͻ��峤��
// 	char* pStart = ArgInf.m_pText + nStart -1;
// 	char* pEnd = ArgInf.m_pText + nEnd+1;
// 	INT nFind = 0;
// 	if(pArgInf[5].m_bool) //���ִ�Сд
// 	{
// 		while(pStart < pEnd)
// 		{
// 			if(strncmp(pStart,pArgInf[1].m_pText,nSubLen)==0)
// 			{
// 				nFind++;
// 				if(nFind == nRplCount)
// 					break;
// 				pStart+=nSubLen;
// 			}
// 			else
// 			{
// 				if(*pStart<0)
// 					pStart+=2;
// 				else
// 					pStart++;
// 			}
// 		}
// 
// 	}
// 	else
// 	{
// 		while(pStart < pEnd)
// 		{
// 			if(strnicmp(pStart,pArgInf[1].m_pText,nSubLen)==0)
// 			{
// 				nFind++;
// 				if(nFind == nRplCount)
// 					break;
// 				pStart+=nSubLen;
// 			}
// 			else
// 			{
// 				if(*pStart<0)
// 					pStart+=2;
// 				else
// 					pStart++;
// 			}
// 		}
// 	}
// 	if(nFind==0)//һ��Ҳû�ҵ�
// 		return StrCpyForE(ArgInf.m_pText);
// 
// 	INT nBuf = nLen + (nStrRpl - nSubLen) * nFind;
// 	char *pText = (char*)E_MAlloc(nBuf+1);
// 	char* pDest = pText;
// 	
// 
// 
// //��ʼ�滻
// 
// 	pStart = ArgInf.m_pText + nStart -1;
// 	pEnd = ArgInf.m_pText + nEnd+1;
// 	char* pSrc = ArgInf.m_pText;
// 	if(pArgInf[5].m_bool) //���ִ�Сд
// 	{
// 		while(pStart < pEnd)
// 		{
// 			if(strncmp(pStart,pArgInf[1].m_pText,nSubLen)==0)
// 			{
// 				INT nStr = pStart - pSrc;
// 				strncpy(pDest,pSrc,nStr);//�����ϴζ�
// 				pDest+=nStr;
// 				*pDest =0;
// 				if(pStrRpl)
// 				{
// 					strncpy(pDest,pStrRpl,nStrRpl);//�����滻�ı�
// 					pDest+=nStrRpl;
// 					*pDest =0;
// 				}
// 				pStart+=nSubLen;
// 				pSrc = pStart; //����һ��;
// 				nFind--;
// 
// 				if(nFind == 0)
// 				{
// 					
// 					if(pStart - ArgInf.m_pText<= nLen)
// 						strcat(pText,pSrc);
// 					break;
// 				}
// 			}
// 			else
// 			{
// 				if(*pStart<0)
// 					pStart+=2;
// 				else
// 					pStart++;
// 			}
// 		}
// 
// 	}
// 	else
// 	{
// 		while(pStart < pEnd)
// 		{
// 			if(strnicmp(pStart,pArgInf[1].m_pText,nSubLen)==0)
// 			{
// 				INT nStr = pStart - pSrc;
// 				strncpy(pDest,pSrc,nStr);//�����ϴζ�
// 				pDest+=nStr;
// 				*pDest =0;
// 				if(pStrRpl)
// 				{
// 					strncpy(pDest,pStrRpl,nStrRpl);//�����滻�ı�
// 					pDest+=nStrRpl;
// 					*pDest =0;
// 				}
// 				pStart+=nSubLen;
// 				pSrc = pStart; //����һ��;
// 				nFind--;
// 				if(nFind == 0)
// 				{
// 
// 					if(pStart - ArgInf.m_pText<= nLen)
// 						strcat(pText,pSrc);
// 
// 					break;
// 				}
// 			}
// 			else
// 			{
// 
// 				if(*pStart<0)
// 					pStart+=2;
// 				else
// 					pStart++;
// 			}
// 
// 		}
// 	}
// 	pText [nBuf]=0;
// 	return pText;
// 	*/
// }
