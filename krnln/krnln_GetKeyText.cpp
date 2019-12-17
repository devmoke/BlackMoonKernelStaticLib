#include "stdafx.h"
#include "Myfunctions.h"

//ϵͳ���� - ��������
/*
    ���ø�ʽ�� ���ı��͡� �������� ���ı��� �����ļ������ı��� �����ƣ��ı��� ���������ƣ����ı��� Ĭ���ı��ݣ� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetKeyText
    ��ȡָ�������ļ���ָ����Ŀ���ı����ݡ�������Ϊ�������
    ����<1>������Ϊ�������ļ�����������Ϊ���ı��ͣ�text������ָ�������ļ������ƣ�ͨ����.ini��Ϊ�ļ�����׺��
    ����<2>������Ϊ�������ơ�������Ϊ���ı��ͣ�text���������������������������ڵ����ơ�
    ����<3>������Ϊ�����������ơ�������Ϊ���ı��ͣ�text����������ֵָ��������������������е����ơ�
    ����<4>������Ϊ��Ĭ���ı���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ����ָ����������ڣ������ش�Ĭ���ı������ָ������������ұ�������ʡ�ԣ������ؿ��ı���
*/
LIBAPI(char*, krnln_GetKeyText)
{
	PMDATA_INF pArgInf = &ArgInf;
	LPSTR pBuff = NULL;
	INT nLen = 1024;
	do
	{

		pBuff = new char[nLen];
		INT nRet = GetPrivateProfileString (pArgInf[1].m_pText, pArgInf[2].m_pText, pArgInf[3].m_pText, pBuff, nLen, pArgInf[0].m_pText);

		if(nRet < nLen-1)
			break;
		nLen = nRet+1024;
		delete[] pBuff;
	}while(1);

	LPSTR pText = NULL;
	nLen = mystrlen(pBuff);
	if(nLen)
	{
		pText = CloneTextData(pBuff,nLen);
	}
	delete[] pBuff;
	return pText;
}
