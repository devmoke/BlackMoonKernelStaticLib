#include "stdafx.h"
#include "Myfunctions.h"

//�ı����� - Ѱ���ı�
/*
    ���ø�ʽ�� �������͡� Ѱ���ı� ���ı��� ����Ѱ���ı����ı��� ��Ѱ�ҵ��ı����������� ��ʼ��Ѱλ�ãݣ��߼��� �Ƿ����ִ�Сд�� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�InStr
    ����һ������ֵ��ָ��һ�ı�����һ�ı������ȳ��ֵ�λ�ã�λ��ֵ�� 1 ��ʼ�����δ�ҵ�������-1��������Ϊ�������
    ����<1>������Ϊ������Ѱ���ı���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ����Ѱ�ҵ��ı���������Ϊ���ı��ͣ�text������
    ����<3>������Ϊ����ʼ��Ѱλ�á�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�λ��ֵ�� 1 ��ʼ�������������ʡ�ԣ�Ĭ��Ϊ 1 ��
    ����<4>������Ϊ���Ƿ����ִ�Сд��������Ϊ���߼��ͣ�bool��������ʼֵΪ���١���Ϊ�治���ִ�Сд��Ϊ�����֡�
*/
LIBAPI(int, krnln_InStr)
{ // �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	INT nStart;
	char *str1 = pArgInf[0].m_pText;
	char *str2 = pArgInf[1].m_pText;
	if (!str1 || !str2 || !*str1) return -1; //���ı�ֱ�ӷ���
	if (!*str2) return 1;
	if (pArgInf[2].m_dtDataType == _SDT_NULL || pArgInf[2].m_int <= 1)
		nStart = 0;
	else
		nStart = pArgInf[2].m_int - 1;

	char* pStart = str1 + nStart;

	char *cp = str1;
	char *s1, *s2;
	
	for (; *cp && cp < pStart; cp++)
			if (*cp < 0) cp++;

	if (pArgInf[3].m_bool) //�����ִ�Сд
	{
		register unsigned char* lt = lowtable;
		while (*cp)
		{
			s1 = cp;
			s2 = str2;
			while ( *s1 && *s2 && (*s1==*s2 || lt[(unsigned char)(*s1)]==lt[(unsigned char)(*s2)]) )
				s1++, s2++;
			if (!*s2)
				return cp - str1 + 1;
				
			if (*cp < 0)
			{
				cp++;
				if (!*cp)
					return -1;
			}
			cp++;
		}
	}
	else  // ���ִ�Сд
	{	
		while (*cp)
		{
			s1 = cp;
			s2 = str2;
			while ( *s1 && *s2 && !(*s1-*s2) )
				s1++, s2++;
			if (!*s2)
				return cp - str1 + 1;
			
			if (*cp < 0)
			{
				cp++;
				if (!*cp)
					return -1;
			}
			cp++;
		}
	}
	return -1;
}
// 
// { // ����ԭ��
// 	PMDATA_INF pArgInf = &ArgInf;
// 	INT nLen = strlen(ArgInf.m_pText);
// 	INT nSubLen = strlen(pArgInf[1].m_pText);
// 	if(nLen==0 || nSubLen==0 || nSubLen > nLen)return -1;
// 	
// 	INT nStart;
// 	if(pArgInf[2].m_dtDataType ==_SDT_NULL || pArgInf[2].m_int <=0)
// 		nStart = 1;
// 	else
// 		nStart = pArgInf[2].m_int;
// 	INT nEnd = nLen - nSubLen;
// 	if(nStart > (nEnd+1))return -1;
// 	char* pStart = ArgInf.m_pText + nStart -1;
// 	char* pEnd = ArgInf.m_pText + nEnd;
// 	if(pArgInf[3].m_bool) //�����ִ�Сд
// 	{
// 		while(pStart <= pEnd)
// 		{
// 			if(strnicmp(pStart,pArgInf[1].m_pText,nSubLen)==0)
// 			{
// 				nStart = pStart - ArgInf.m_pText +1;
// 				return nStart;
// 			}
// 			if(*pStart<0)
// 				pStart+=2;
// 			else
// 				pStart++;
// 		}
// 
// 	}
// 	else
// 	{
// 		while(pStart <= pEnd)
// 		{
// 			if(strncmp(pStart,pArgInf[1].m_pText,nSubLen)==0)
// 			{
// 				nStart = pStart - ArgInf.m_pText +1;
// 				return nStart;
// 			}
// 			if(*pStart<0)
// 				pStart+=2;
// 			else
// 				pStart++;
// 		}
// 	}
// 
// 
// 	return -1;	
// }
