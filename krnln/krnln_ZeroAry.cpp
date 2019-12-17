#include "stdafx.h"

/*
    ���ø�ʽ�� ���޷���ֵ�� �������� ��ͨ���ͱ������� ��ֵ��������� - ϵͳ����֧�ֿ�->�������
    Ӣ�����ƣ�ZeroAry
    ��ָ����ֵ��������ڵ����г�Աֵȫ������Ϊ�㣬��Ӱ�������ά������Ϣ��������Ϊ�������
    ����<1>������Ϊ����ֵ���������������Ϊ��ͨ���ͣ�all�������ṩ��������ʱֻ���ṩ�������顣
*/

LIBAPI(void, krnln_ZeroAry)
{
	
	if(ArgInf.m_ppAryData==NULL)//������
		return;

	
	if(ArgInf.m_dtDataType==SDT_TEXT || ArgInf.m_dtDataType==SDT_BIN)
	{
		DWORD dwSize;
		LPSTR* pAryData = (LPSTR*)GetAryElementInf(*ArgInf.m_ppAryData,dwSize);

		for(UINT n=0;n<dwSize;n++)
		{
			if(pAryData[n])
				E_MFree(pAryData[n]);
			pAryData[n] = NULL;

		}

	}else{

		INT nLen = GetSysDataTypeDataSize(ArgInf.m_dtDataType);
		if(nLen==0)//��֧�ֵ���������
			return;
		DWORD dwSize=0;
		void* pData = GetAryElementInf(*ArgInf.m_ppAryData,dwSize);
		if(pData==NULL || dwSize==0)
			return;
		nLen *= dwSize;
		memset(pData,0,nLen);
					
	}

}