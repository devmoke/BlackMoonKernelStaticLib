#include "stdafx.h"

//�ı����� - ȡ����
/*
    ���ø�ʽ�� �������͡� ȡ���� ���ı��� ��ȡ�ַ�������ı����������� ��ȡ�������ַ�λ�ãݣ� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�asc
    �����ı���ָ��λ�ô��ַ��Ĵ��롣���ָ��λ�ó����ı����ȣ�����0��������Ϊ�������
    ����<1>������Ϊ����ȡ�ַ�������ı���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ����ȡ�������ַ�λ�á�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�1Ϊ��λ�ã�2Ϊ��2��λ�ã�������ơ������������ʡ�ԣ�Ĭ��Ϊ��λ�á�
*/
LIBAPI(int, krnln_asc)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	INT nIdx;
	if(pArgInf[1].m_dtDataType == _SDT_NULL)
		nIdx = 0;
	else
		nIdx = pArgInf[1].m_int - 1;

	if (nIdx < 0) return 0;

	char* cp = pArgInf[0].m_pText;
	if (!cp) return 0;

	char* pStart = pArgInf[0].m_pText + nIdx;

	//�������������Ƿ�Խ�磬���Ҳ��ñ��������ڴ档
	while (*cp && cp < pStart)
		cp++;

	return (int)*cp;
}
// { // ����ԭ��
// 	PMDATA_INF pArgInf = &ArgInf;
// 	INT nLen = strlen(ArgInf.m_pText);
// 	if(nLen==0)return 0;
// 	INT nIdx;
// 	if(pArgInf[1].m_dtDataType == _SDT_NULL)
// 		nIdx = 1;
// 	else
// 		nIdx = pArgInf[1].m_int;
// 	if(nIdx <= 0 || nIdx > nLen)return 0;
// 
// 	return ArgInf.m_pText[nIdx-1];	
// }
