#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - �ı��滻
/*
    ���ø�ʽ�� ���ı��͡� �ı��滻 ���ı��� �����滻���ı��������� ��ʼ�滻λ�ã������� �滻���ȣ����ı��� �����滻���ı��ݣ� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�ReplaceText
    ��ָ���ı���ĳһ�������������ı��滻��������Ϊ�������
    ����<1>������Ϊ�������滻���ı���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ����ʼ�滻λ�á�������Ϊ�������ͣ�int�������滻����ʼλ�ã�1Ϊ��λ�ã�2Ϊ��2��λ�ã�������ơ�
    ����<3>������Ϊ���滻���ȡ�������Ϊ�������ͣ�int������
    ����<4>������Ϊ�������滻���ı���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ������������ʡ�ԣ���ɾ���ı��е�ָ�����֡�
*/
LIBAPI(char*, krnln_ReplaceText)
{// �����ߺŸ�
	PMDATA_INF pArgInf = &ArgInf;
	char* pStr = pArgInf[0].m_pText;
	char* pSubstr = pArgInf[3].m_pText;
	INT nSubLen;
	INT nLen = mystrlen(pStr);
	if (pArgInf[3].m_dtDataType==_SDT_NULL)
		nSubLen = 0;
	else
		nSubLen = mystrlen(pSubstr);
	
	INT nRpLen = pArgInf[2].m_int;
	if (nRpLen < 0) nRpLen = 0;

	INT nStart = pArgInf[1].m_int - 1;
	if (nStart < 0) 
		nStart = 0;
	else if (nStart > nLen)
		nStart = nLen - 1;

	// �³��� = Դ���� - �滻���� + �Ӵ�����
	// ��ʼ�� + �滻���� <= Դ����
	if (nStart + nRpLen > nLen) nRpLen = nLen - nStart;
	INT nNewLen = nLen - nRpLen + nSubLen;
	if (nNewLen <= 0) return NULL;

	char* pText;
	if (nStart == 0) // ��ǰƴ��
	{
		if (nSubLen == 0) // �Ӵ�Ϊ��
			return CloneTextData(pStr + nRpLen, nNewLen);

		pText = (char*)E_MAlloc_Nzero ((DWORD)(nNewLen + 1));
		memcpy(pText, pSubstr, nSubLen);
		memcpy(pText + nSubLen, pStr + nRpLen, nLen - nRpLen + 1);//+1�ǰ�\0Ҳ���ƽ�ȥ
		return pText;
	}
	else if (nStart >= nLen) // ����ƴ��
	{
		if (nSubLen == 0) // �Ӵ�Ϊ��
			return CloneTextData(pStr, nNewLen);

		pText = (char*)E_MAlloc_Nzero ((DWORD)(nNewLen + 1));
		memcpy(pText, pStr, nLen);
		memcpy(pText + nLen, pSubstr, nSubLen + 1);//+1�ǰ�\0Ҳ���ƽ�ȥ
		return pText;
	}

	// �м�ƴ��
	pText = (char*)E_MAlloc_Nzero ((DWORD)(nNewLen + 1));
	char* pTemp = pText;
	memcpy(pTemp, pStr, nStart);
	pTemp+=nStart;
	if (nSubLen > 0)
	{
		memcpy(pTemp, pSubstr, nSubLen);
		pTemp+=nSubLen;
	}
	if (nStart + nSubLen < nNewLen)
		memcpy(pTemp, pStr + nStart + nRpLen, nLen - nStart - nRpLen);

	pText[nNewLen] = '\0';
	return pText;
}
// {//����ԭ��
// 	PMDATA_INF pArgInf = &ArgInf;
// 	UINT nLen = mystrlen(ArgInf.m_pText);
// 	if(nLen==0)
// 	{
// 		if(pArgInf[3].m_dtDataType == _SDT_NULL)
// 			return NULL;
// 		nLen = mystrlen(pArgInf[3].m_pText);
// 		if(nLen==0)
// 			return NULL;
// 		return CloneTextData(pArgInf[3].m_pText,nLen);
// 
// 	}
// 	if(pArgInf[1].m_int > nLen || pArgInf[2].m_int <= 0)
// 		return CloneTextData(ArgInf.m_pText,nLen);
// 	INT nSubStr = 0;
// 	char* pSubStr = NULL;
// 	if(pArgInf[3].m_dtDataType != _SDT_NULL)
// 	{
// 		pSubStr = pArgInf[3].m_pText;
// 		nSubStr = mystrlen(pSubStr);
// 	}
// 	if(pArgInf[1].m_int <=0 )
// 		pArgInf[1].m_int = 1;
// 	INT nForce = pArgInf[1].m_int - 1;
// 	INT nBack = nLen - nForce;
// 	BOOL bStrcat;
// 	INT nCount ;
// 	if(nBack < pArgInf[2].m_int)
// 	{
// 		nCount = nForce + nSubStr;
// 		bStrcat = TRUE;
// 	}else{
// 
// 		nCount = nLen - pArgInf[2].m_int + nSubStr;
// 		bStrcat = FALSE;
// 	}
// 
// 	char *pText = (char*)E_MAlloc(nCount+1);
// 	if(bStrcat)
// 	{
// 		strncpy(pText,ArgInf.m_pText,nForce);
// 		pText[nForce]=0;
// 		if(pSubStr)
// 			strcat(pText,pSubStr);
// 	}
// 	else
// 	{
// 		strncpy(pText,ArgInf.m_pText,nForce);
// 		pText[nForce]=0;
// 		if(pSubStr)
// 			strcat(pText,pSubStr);
// 		pSubStr = ArgInf.m_pText + nForce + pArgInf[2].m_int;
// 		strcat(pText,pSubStr);
// 	}
// 	return pText;
// 
// }