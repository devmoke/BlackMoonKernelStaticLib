#include "stdafx.h"

//�߼��Ƚ� - ���Ƶ���
/*
    ���ø�ʽ�� ���߼��͡� ���Ƶ��� ���ı��� ���Ƚ��ı����ı��� �Ƚ��ı��� - ϵͳ����֧�ֿ�->�߼��Ƚ�
    Ӣ�����ƣ�like
    ���Ƚ��ı��ڱ��Ƚ��ı����ײ�������ʱ�����棬���򷵻ؼ٣��������Ϊ��?=���򡰡֡���������Ϊ�������
    ����<1>������Ϊ�����Ƚ��ı���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ���Ƚ��ı���������Ϊ���ı��ͣ�text������
*/
LIBAPI(BOOL, krnln_like)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	register char *str1 = pArgInf[0].m_pText;
	register char *str2 = pArgInf[1].m_pText;
	if (!str1 || !str2 || !*str1 || !*str2) return FALSE; //���ı�ֱ�ӷ���

	while ( *str1 && *str2 && *str1==*str2 )
		str1++, str2++;

	return *str2==0;
}
// {// ����ԭ��
// /*	PMDATA_INF pArgInf =&ArgInf;
// 	INT nLen = strlen(pArgInf[1].m_pText);
// 	if(strlen(pArgInf[0].m_pText) < nLen)
// 		return FALSE;
// 	if(memcmp(pArgInf[0].m_pText,pArgInf[1].m_pText,nLen)==0)
// 		return TRUE;
// 	return FALSE;*/
//   BOOL result; // eax@1
//   char *v4; // edx@1
//   size_t v5; // ebx@1
//   char *v6; // esi@1
//   char *v7; // edi@1
//   PMDATA_INF pArgInf =&ArgInf;
// 
//   v4 = pArgInf->m_pText;
//   v6 = pArgInf[1].m_pText;
//   v7 = pArgInf[1].m_pText;
//   result = FALSE;
//   v5 = strlen(v7);
//   if ( v5 <= strlen(v4) )
//   {
//     result = strncmp(v6, v4, v5) == 0;
//   }
//   return result;
// }
