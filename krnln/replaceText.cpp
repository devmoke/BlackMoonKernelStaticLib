#include "stdafx.h"
#include "mem.h"
#include "Myfunctions.h"
/*
BOOL replaceText(LPSTR& pDest,LPSTR pSub,LPSTR pRplStr,BOOL bNeedFree)
{
//ͳ���ҵ��Ĵ����ͻ��峤��
	INT nSubLen =strlen(pSub);
	INT nLen = strlen(pDest);
	char* pStart = pDest;
	char* pEnd = pDest+nLen-nSubLen;

	INT nFind = 0;
	while(pStart <= pEnd)
	{
		if(strncmp(pStart,pSub,nSubLen)==0)
		{
			nFind++;
			pStart+=nSubLen;
		}
		else
		{
			if(*pStart<0)
				pStart+=2;
			else
				pStart++;
		}
	}
	if(nFind==0)
	{
		return FALSE;
	}
	INT nStrRpl = strlen(pRplStr);

	INT nBuf = nLen + (nStrRpl - nSubLen) * nFind;
	char *pText = (char*)malloc(nBuf+1);
	char* pszDest = pText;
	


//��ʼ�滻
	pStart = pDest;
	pEnd = pDest+nLen-nSubLen;
	char* pSrc = pDest;
	while(pStart <= pEnd)
	{
		if(strncmp(pStart,pSub,nSubLen)==0)
		{
			INT nStr = pStart - pSrc;
			if(nStr)
			{
				strncpy(pszDest,pSrc,nStr);//�����ϴζ�
				pszDest+=nStr;
				*pszDest =0;
			}
				
			strncpy(pszDest,pRplStr,nStrRpl);//�����滻�ı�
			pszDest+=nStrRpl;
			*pszDest =0;
			

	
			pStart+=nSubLen;//����һ��;
			pSrc = pStart; //����һ��;
			nFind--;
			if(nFind == 0)
			{
				if(pStart <= pEnd)
					strcat(pText,pStart);
				break;
			}
		}
		else
		{
			if(*pStart<0)
				pStart+=2;
			else
				pStart++;
		}
	}

	pText [nBuf]=0;
	if(bNeedFree)
		free(pDest);
	pDest = pText;
	
	return TRUE;


}*/
BOOL replaceText(LPSTR& pDest,LPSTR pSub,LPSTR pRplStr,BOOL bNeedFree){
//��ʼ�滻
	CFreqMem cDest;

	char* pStart = pDest;
	char* pEnd = pDest + mystrlen(pDest);
	INT nFind = 0;
	char* pSrc = pDest;
	INT nLen = mystrlen(pDest);
	INT nStrRpl = mystrlen(pRplStr);
	INT nSubLen = mystrlen(pSub);
	while(pStart < pEnd)
	{
		if(strncmp(pStart,pSub,nSubLen)==0)
		{
			INT nStr = pStart - pSrc;
			cDest.Append((LPBYTE)pSrc,nStr);//�����ϴζ�
			if(pRplStr)
				cDest.Append((LPBYTE)pRplStr,nStrRpl);//�����滻�ı�
			
			pStart+=nSubLen;
			pSrc = pStart; //����һ��;
			nFind++;
			
		}
		else
		{
			if(*pStart<0)
				pStart+=2;
			else
				pStart++;
		}
	}
	if(nFind==0){
		cDest.Free();
		return FALSE;
	}
	if(pStart - pDest<= nLen){
		INT nLen = tcsallbytes(pSrc);
		cDest.Append((LPBYTE)pSrc, nLen);
	}


	INT nBufLen = nLen+1;
	char* m_pText = (char*)malloc(nBufLen);
	memset(m_pText,0,nBufLen);
	memcpy(m_pText,cDest.GetPtr(),cDest.GetSize());
	cDest.Free();

	if(bNeedFree)
		free(pDest);
	pDest=m_pText;
	bNeedFree = TRUE;

	return TRUE;
}