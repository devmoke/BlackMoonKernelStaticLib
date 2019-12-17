#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include "Myfunctions.h"

char bigChn []= "��\0Ҽ\0��\0��\0��\0��\0½\0��\0��\0��\0";//48-57
char smlChn []= "��\0һ\0��\0��\0��\0��\0��\0��\0��\0��\0";
char strNumLeven1 []= "��\0Ǫ\0��\0ʰ\0\0";
char strNumLeven2 []= "��\0ǧ\0��\0ʮ\0\0";

BOOL ReadChnNum(LPSTR pText,LPSTR pStrSrc,LPSTR pNumStr,LPSTR pNumLeven,INT nNum,INT& nPre)
{

	pNumLeven += ((5-nNum)*3);
	BOOL bAllZero = TRUE;

	for(INT i=0;i<nNum;i++)
	{
		INT nOffset = pStrSrc[i]-48;
		LPSTR pStr = pNumStr + nOffset*3;

		if(nOffset !=0)
		{
			if(nPre ==0)
				strcat(pText,"��");
			strcat(pText,pStr);
			pStr = pNumLeven + i*3;
			strcat(pText,pStr);
			bAllZero = FALSE;
		}
		nPre = nOffset;

	}
	return bAllZero;

}
LPSTR IntNumToChn (double dNum,BOOL bSml,INT& nPre)
{
	char str [MAX_PATH];
	LPSTR pText = NULL;
	sprintf(str,"%.0lf",dNum);
	INT nLen = mystrlen(str);
	if(nLen>13)
	{
		pText = (LPSTR)malloc (3);
		strcpy(pText,"���");
		return pText;
	}
	pText = (LPSTR)malloc (nLen*4+4);
	*pText=0;
	LPSTR pNum;
	LPSTR pNumLeven;
	if(bSml)
	{
		pNum = smlChn;
		pNumLeven = strNumLeven2;
	}
	else
	{
		pNum = bigChn;
		pNumLeven = strNumLeven1;
	}

	LPSTR pSrc = str;
	if(*pSrc==45)
	{
		pSrc++;
		strcat(pText,"��");
	}
	//��Ǫ��ʰ��-Ǫ��ʰ��-Ǫ��ʰ��
	nPre = -1;
	if(nLen > 8)
	{
		INT nNum = nLen - 8;
		ReadChnNum(pText,pSrc,pNum,pNumLeven,nNum,nPre);
		strcat(pText,"��");
		pSrc+=nNum;
		BOOL nAll0 = ReadChnNum(pText,pSrc,pNum,pNumLeven,4,nPre);
		if(!nAll0)
			//strcat(pText,"��");
		//else
			strcat(pText,"��");
		pSrc+=4;
		ReadChnNum(pText,pSrc,pNum,pNumLeven,4,nPre);


	}else if(nLen > 4)
	{
		INT nNum = nLen - 4;
		ReadChnNum(pText,pSrc,pNum,pNumLeven,nNum,nPre);
		strcat(pText,"��");
		pSrc+=nNum;
		ReadChnNum(pText,pSrc,pNum,pNumLeven,4,nPre);
	}
	else 
	{
		ReadChnNum(pText,pSrc,pNum,pNumLeven,nLen,nPre);
	}


	
	return pText;
	

}
LPSTR FloatNumToChn (double dNum,BOOL bSml)//���ﲻ�ܴ���0ֵ
{
	char str [MAX_PATH];
	dNum = fabs(dNum);

	sprintf(str,"%.2lf",dNum);
	LPSTR pSrc = str;
	while(*pSrc !=0 && *pSrc != '.')
		pSrc++;
	if(*pSrc ==0)
		return NULL;
	pSrc++;

	LPSTR pNum;

	if(bSml)
		pNum = smlChn;
	else
		pNum = bigChn;

	LPSTR pText = (LPSTR)malloc (64);
	strcpy(pText,"��");

	INT nOffset = pSrc[0]-48;
	LPSTR pStr = pNum + nOffset*3;
	strcat(pText,pStr);
	nOffset = pSrc[1]-48;
	if(nOffset)
	{
		pStr = pNum + nOffset*3;
		strcat(pText,pStr);
	}

	return pText;
}

LPSTR FloatNumToRMB (double dNum,BOOL bSml)//���ﲻ�ܴ���0ֵ
{
	char str [MAX_PATH];
	dNum = fabs(dNum);

	sprintf(str,"%.2lf",dNum);
	LPSTR pSrc = str;
	while(*pSrc !=0 && *pSrc != '.')
		pSrc++;
	if(*pSrc ==0)
		return NULL;
	pSrc++;

	LPSTR pNum;

	if(bSml)
		pNum = smlChn;
	else
		pNum = bigChn;

	LPSTR pText = (LPSTR)malloc (64);
	*pText=0;


	INT nOffset = pSrc[0]-48;
	if(nOffset)
	{
		LPSTR pStr = pNum + nOffset*3;
		strcat(pText,pStr);
		strcat(pText,"��");
	}
	nOffset = pSrc[1]-48;
	if(nOffset)
	{
		LPSTR pStr = pNum + nOffset*3;
		strcat(pText,pStr);
		strcat(pText,"��");
	}

	return pText;
}