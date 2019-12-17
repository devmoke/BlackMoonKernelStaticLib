#include "stdafx.h"
#include "Myfunctions.h"

//�ı����� - ��ȫ��
/*
    ���ø�ʽ�� ���ı��͡� ��ȫ�� ���ı��� ���任���ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�QJCase
    ���ı��еİ����ĸ���ո�����ֱ任Ϊȫ�ǣ����ر任��Ľ���ı���������Ϊ�������
    ����<1>������Ϊ�����任���ı���������Ϊ���ı��ͣ�text������

' ���ַ�Χ163��ͷ��176--185
' ��д��ĸ��163��ͷ��193--218
' Сд��ĸ��163��ͷ��225--250
' ///////////����Ϊȫ�ǵģ������ǰ�ǵ�
' ���ַ�Χ��48--57
' ��д��ĸ��65--90
' Сд��ĸ��97-122
���ֽڼ� (��������)  ' 163,174,163,173
*/
/*
extern "C" char* _cdecl krnln_QJCase (INT nArgCount,MDATA_INF ArgInf,...)
{
	PMDATA_INF pArgInf = &ArgInf;
	INT nLen = strlen(ArgInf.m_pText);
	if(nLen==0)return NULL;
	INT i = 0;
	INT nBufLen = 0;
	while(i < nLen)
	{
		char* pSrc = ArgInf.m_pText + i;
		if(* pSrc < 0)//����
		{
			i+=2;
			nBufLen+=2;
		}
		else
		{
			nBufLen++;
			if((48<= *pSrc && *pSrc <= 57) || (65<= *pSrc && *pSrc <= 90) || (97<= *pSrc && *pSrc <= 122) || *pSrc == '-' || *pSrc == '.')
				nBufLen++;
			i++;
		}
	}

	char *pQJText = (char*)E_MAlloc(nBufLen+1);
	if(nBufLen==nLen)//û����ĸ����
	{
		strcpy(pQJText,ArgInf.m_pText);
		return pQJText;
	}
	char *pText = pQJText;
	i = 0;
	unsigned char strQj [3]={0,0,0};
	while(i < nLen)
	{
		char* pSrc = ArgInf.m_pText + i;
			//char t[20];
	//itoa(nBufLen,t,10);

		if(* pSrc < 0)//����
		{
			memcpy(pText,pSrc,2);
			pText+=2;
			i+=2;
		}
		else
		{
			INT nWord = 1;
			if(48<= *pSrc && *pSrc <= 57)//����
			{
				strQj[0] = 163;
				strQj[1] = 176 + *pSrc - 48;
				nWord = 2;

			}else if (65<= *pSrc && *pSrc <= 90)//��д��ĸ
			{
				strQj[0] = 163;
				strQj[1] = 193 + *pSrc - 65;
				nWord = 2;				
			}else if (97<= *pSrc && *pSrc <= 122)
			{
				strQj[0] = 163;
				strQj[1] = 225 + *pSrc - 97;
				nWord = 2;		
			}else if (*pSrc =='-')
			{
				strQj[0] = 163;
				strQj[1] = 173;
				nWord = 2;		
			}else if (*pSrc =='.')
			{
				strQj[0] = 163;
				strQj[1] = 174;
				nWord = 2;		
			}
			else
			{
				strQj[0] = *pSrc;
				strQj[1] = 0;
			}
			
			strcpy(pText,(const char *)strQj);
			pText+=nWord;
			i++;
		}
	}
	
	pQJText[nBufLen] = 0;
	return pQJText;	
}*/

LIBAPI(char*, krnln_QJCase)
{
	PMDATA_INF pArgInf = &ArgInf;
	INT nLen = mystrlen(ArgInf.m_pText);
	if(nLen==0)return NULL;
	LPSTR pszSrc = ArgInf.m_pText;
	BOOL bRet = replaceText(pszSrc,"/","��",FALSE);
	BOOL bFree =FALSE;
	bFree|=bRet;	
	bRet = replaceText(pszSrc,"\\","��",bFree);
	bFree|=bRet;
	
	nLen = mystrlen(pszSrc);
	INT nBufLen = (nLen+1)*2;
	char *pQJText = (char*)malloc(nBufLen);
	memset(pQJText,0,nBufLen);
	//pQJText[0]=0;
	LCMapString (2052, LCMAP_FULLWIDTH, pszSrc,nLen, pQJText, nBufLen);
	if(bFree)
		free(pszSrc);
	nLen = mystrlen(pQJText);
	char *pText = CloneTextData(pQJText,nLen);
	free(pQJText);
	return pText;
}