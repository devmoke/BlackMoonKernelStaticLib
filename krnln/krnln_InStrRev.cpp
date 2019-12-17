#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - �����ı�
/*
    ���ø�ʽ�� �������͡� �����ı� ���ı��� ����Ѱ���ı����ı��� ��Ѱ�ҵ��ı����������� ��ʼ��Ѱλ�ãݣ��߼��� �Ƿ����ִ�Сд�� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�InStrRev
    ����һ������ֵ��ָ��һ�ı�����һ�ı��������ֵ�λ�ã�λ��ֵ�� 1 ��ʼ�����δ�ҵ�������-1��������Ϊ�������
    ����<1>������Ϊ������Ѱ���ı���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ����Ѱ�ҵ��ı���������Ϊ���ı��ͣ�text������
    ����<3>������Ϊ����ʼ��Ѱλ�á�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�λ��ֵ�� 1 ��ʼ�������������ʡ�ԣ�Ĭ��Ϊ�ӱ���Ѱ�ı���β����ʼ��
    ����<4>������Ϊ���Ƿ����ִ�Сд��������Ϊ���߼��ͣ�bool��������ʼֵΪ���١���Ϊ�治���ִ�Сд��Ϊ�����֡�
*/
LIBAPI(int, krnln_InStrRev)
{ // �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	INT nStart;
	char *str1 = pArgInf[0].m_pText;
	char *str2 = pArgInf[1].m_pText;
	if (!str1 || !str2 || !*str1) return -1; //���ı�ֱ�ӷ���
	if (!*str2) return 1;
	if (pArgInf[2].m_dtDataType == _SDT_NULL)
		nStart = 0x7FFFFFFF;
	else
	{
		if (pArgInf[2].m_int <= 0)
			return -1;
		nStart = pArgInf[2].m_int - 1;
	}
	
	INT nDesLen = mystrlen(str2);
	char* pStart = str1 + nStart - nDesLen;
	
	char *cp, *s1, *s2;
	
	// ����str1���Ȼ����޶������ʼλ��
	for (cp = str1; cp < pStart && *cp; cp++);
	//	if (*cp < 0) cp++; // ���ֲ���2���������⣡��
	
	if (cp < str1) return -1;

	if (pArgInf[3].m_bool) //�����ִ�Сд
	{
		register unsigned char* lt = lowtable;
		while (cp >= str1)
		{
			s1 = cp;
			s2 = str2;
			while ( *s1 && *s2 && (*s1==*s2 || lt[(unsigned char)(*s1)]==lt[(unsigned char)(*s2)]) )
				s1++, s2++;
			if (!*s2)
				return cp - str1 + 1;
			cp--;
		}
	}
	else  // ���ִ�Сд
	{	
		while (cp >= str1)
		{
			s1 = cp;
			s2 = str2;
			while ( *s1 && *s2 && !(*s1-*s2) )
				s1++, s2++;
			if (!*s2)
				return cp - str1 + 1;
			cp--;
		}
	}
	return -1;
}
// {
// 	PMDATA_INF pArgInf = &ArgInf;
// 	INT nLen = strlen(ArgInf.m_pText);
// 	INT nSubLen = strlen(pArgInf[1].m_pText);
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
// 	char* pStart = ArgInf.m_pText + nStart;
// //MessageBox(NULL,pStart,NULL,MB_OK);
// 	if(pArgInf[3].m_bool) //�����ִ�Сд
// 	{
// 		while(pStart >= ArgInf.m_pText)
// 		{
// 			if(strnicmp(pStart,pArgInf[1].m_pText,nSubLen)==0)
// 			{
// 				nStart = pStart - ArgInf.m_pText +1;
// 				return nStart;
// 			}
// 			pStart--;
// 		}
// 
// 	}
// 	else
// 	{
// 		while(pStart >= ArgInf.m_pText)
// 		{
// 			if(strncmp(pStart,pArgInf[1].m_pText,nSubLen)==0)
// 			{
// 				nStart = pStart - ArgInf.m_pText +1;
// 				return nStart;
// 			}
// 			pStart--;
// 		}
// 	}
// 
// 
// 	return -1;	
// }
