#include "stdafx.h"
#include "Myfunctions.h"


//�ı����� - �����
/*
    ���ø�ʽ�� ���ı��͡� ����� ���ı��� ���任���ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�BJCase
    ���ı��е�ȫ����ĸ���ո�����ֱ任Ϊ��ǣ����ر任��Ľ���ı���������Ϊ�������
    ����<1>������Ϊ�����任���ı���������Ϊ���ı��ͣ�text������

' ���ַ�Χ163��ͷ��176--185
' ��д��ĸ��163��ͷ��193--218
' Сд��ĸ��163��ͷ��225--250
' ///////////����Ϊȫ�ǵģ������ǰ�ǵ�
' ���ַ�Χ��48--57
' ��д��ĸ��65--90
' Сд��ĸ��97-122
���ֽڼ� (��������)  ' 163,174,163,173


extern "C" char* _cdecl krnln_BJCase (INT nArgCount,MDATA_INF ArgInf,...)
{
	PMDATA_INF pArgInf = &ArgInf;
	INT nLen = strlen(ArgInf.m_pText);
	if(nLen==0)return NULL;
	INT i = 0;
	INT nBufLen = 0;
	while(i < nLen)
	{
		LPBYTE pSrc = (LPBYTE)ArgInf.m_pText + i;
		if(* pSrc > 127)//����
		{
			i+=2;
			if(pSrc[0] ==163)
			{
				if((176 <= pSrc[1] && pSrc[1] <=185) || (193 <= pSrc[1] && pSrc[1] <=218) || (225 <= pSrc[1] && pSrc[1] <=250) || pSrc[1]==173 || pSrc[1]==174)
					nBufLen++;
				else
					nBufLen+=2;
			}
			else
				nBufLen+=2;

		}
		else
		{
			nBufLen++;
			i++;
		}
	}

	char *pBJText = (char*)E_MAlloc(nBufLen+1);
	if(nBufLen==nLen)
	{
		strcpy(pBJText,ArgInf.m_pText);
		return pBJText;
	}
	LPBYTE pText = (LPBYTE)pBJText;
	i = 0;

	while(i < nLen)
	{
		LPBYTE pSrc = (LPBYTE)ArgInf.m_pText + i;

		if(* pSrc > 127)//����
		{
			if(pSrc[0] ==163)
			{

				if (176 <= pSrc[1] && pSrc[1] <=185)//����
				{
					*pText = 48 + pSrc[1] - 176;
					pText++;
					
				}else if (193 <= pSrc[1] && pSrc[1] <=218)//��д��ĸ
				{
					*pText = 65 + pSrc[1] - 193;
					pText++;		
				}else if (225 <= pSrc[1] && pSrc[1] <=250)
				{
					*pText = 97 + pSrc[1] - 225;
					pText++;	
				}else if(pSrc[1]==173)//����
				{
					*pText = '-';
					pText++;

				}
				else if(pSrc[1]==174)//���
				{
					*pText = '.';
					pText++;
				}
				else
				{
					memcpy(pText,pSrc,2);
					pText+=2;
				}
			}
			else
			{
				memcpy(pText,pSrc,2);
				pText+=2;
			}

			i+=2;
		}
		else
		{
			*pText = * pSrc;
			pText++;
			i++;
		}
	}
	
	pBJText[nBufLen] = 0;
	return pBJText;	
}
*/
LIBAPI(char*, krnln_BJCase)
{
	PMDATA_INF pArgInf = &ArgInf;
	INT nLen = mystrlen(ArgInf.m_pText);
	if(nLen==0)return NULL;
	LPSTR pszSrc = ArgInf.m_pText;
	BOOL bRet = replaceText(pszSrc,"��","/",FALSE);
	BOOL bFree =FALSE;
	bFree |=bRet;
		
	bRet = replaceText(pszSrc,"��","\\",bFree);

	bFree |=bRet;
	
	nLen = mystrlen(pszSrc);
	INT nBufLen = nLen+1;
	char *pBJText = (char*)malloc(nBufLen);
	memset(pBJText,0,nBufLen);
	//pBJText[0]=0;
	LCMapString (2052, LCMAP_HALFWIDTH, pszSrc, nLen, pBJText, nBufLen);
	if(bFree)
		free(pszSrc);
	nLen = mystrlen(pBJText);
	char *pText = CloneTextData(pBJText,nLen);
	free(pBJText);
	return pText;
}