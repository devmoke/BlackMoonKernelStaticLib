#include "stdafx.h"
#include "Myfunctions.h"
//���� - д���ڴ�
/*
   ���ø�ʽ�� ���޷���ֵ�� д���ڴ� ��ͨ��������/������ ��д���ڴ�����ݣ������� �ڴ�����ָ�룬�������� �ڴ�����ߴ�ݣ� - ϵͳ����֧�ֿ�->����
    Ӣ�����ƣ�WriteMem
    ������д����ָ�����ڴ�����ע����ñ�����ǰһ��Ҫȷ�����ṩ���ڴ�������ʵ��Ч������������ʹ�ó��Ͼ����������Իص��ӳ����������DLL�����ӳ�������������������ݡ�������Ϊ�߼����
    ����<1>������Ϊ����д���ڴ�����ݡ�������Ϊ��ͨ���ͣ�all�������ṩ��������ʱ����ͬʱ�ṩ�������������ݡ�����ֵֻ��Ϊ���������������ݻ��ֽ����顣
    ����<2>������Ϊ���ڴ�����ָ�롱������Ϊ�������ͣ�int�������������ṩ��д���ڴ������׵�ַ��ָ��ֵ��
    ����<3>������Ϊ���ڴ�����ߴ硱������Ϊ�������ͣ�int���������Ա�ʡ�ԡ��������ṩ���ڴ��������Ч�ߴ磬�����д�����ݳ����˳ߴ�ֵ�������Զ��г�������ֵ���Ϊ -1 �����ʾ���ڴ�����ߴ粻�����ơ������������ʡ�ԣ���Ĭ��ֵΪ -1��
*/
LIBAPI(void, krnln_WriteMem)
{
	PMDATA_INF pArgInf = &ArgInf;
	LPBYTE pData;
	DWORD dwLen;
	if((pArgInf[0].m_dtDataType & DT_IS_ARY) == DT_IS_ARY)//������
	{
		pArgInf[0].m_dtDataType &=~DT_IS_ARY; //ȥ�������־
		if(pArgInf[0].m_dtDataType == SDT_BYTE)//�ֽ�����
		{
			pData = (LPBYTE)GetAryElementInf(pArgInf[0].m_pAryData,dwLen);
			if(dwLen==0)
				return;
		}else
			return;
	}
	else 
	{
		if(pArgInf[0].m_dtDataType==SDT_TEXT)
		{
			if(pArgInf[0].m_pText==NULL)
				return;
			
			dwLen = mystrlen(pArgInf[0].m_pText);
			if(dwLen==0)
				return;
			dwLen++;
			pData = (LPBYTE)pArgInf[0].m_pText;
			
		}else if(pArgInf[0].m_dtDataType==SDT_BIN)
		{
			if(pArgInf[0].m_pBin==NULL)
				return;

			LPINT p = (LPINT)pArgInf[0].m_pBin;
			dwLen = p[1];
			p+=2;
			pData = (LPBYTE)p;

			
		}else{
			
			dwLen = GetSysDataTypeDataSize(pArgInf[0].m_dtDataType);
			if(dwLen==0)//��֧�ֵ���������
				return;
			pData = (LPBYTE)&pArgInf[0].m_int;
		}

	}
	if(pArgInf[2].m_dtDataType != _SDT_NULL && pArgInf[2].m_int>0)
	{
		if(pArgInf[2].m_int<(INT)dwLen)
			dwLen = pArgInf[2].m_int;
	}
	memcpy(pArgInf[1].m_pCompoundData,pData,dwLen);
	


}
