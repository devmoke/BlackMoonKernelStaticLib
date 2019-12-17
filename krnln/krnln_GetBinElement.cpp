#include "stdafx.h"
#include "mem.h"
#include "Myfunctions.h"

//�ֽڼ����� - ȡ�ֽڼ�����
/*
    ���ø�ʽ�� ��ͨ���͡� ȡ�ֽڼ����� ���ֽڼ� ��ȡ���������ݵ��ֽڼ��������� ��ȡ�����ݵ����ͣ��������� ��ʼ����λ�ãݣ� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�GetBinElement
    ȡ���ֽڼ���ָ��λ��ָ���������͵����ݡ�������Ϊ�������
    ����<1>������Ϊ����ȡ���������ݵ��ֽڼ���������Ϊ���ֽڼ���bin������
    ����<2>������Ϊ����ȡ�����ݵ����͡�������Ϊ�������ͣ�int����������ֵ����Ϊ���³����� 1��#�ֽ��ͣ� 2��#�������ͣ� 3��#�����ͣ� 4��#�������ͣ� 5��#С���ͣ� 6��#˫����С���ͣ� 7��#�߼��ͣ� 8��#����ʱ���ͣ� 9��#�ӳ���ָ���ͣ� 10��#�ı��͡�ת��������ݽ��Զ�������Ч��У�鼰ת������
    ����<3>������Ϊ����ʼ����λ�á�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�ָ�����ֽڼ���ʲô�ط���ʼȡ���ݣ�����ֵ��1��ʼ�������ʡ�ԣ�Ĭ��Ϊ��ֵ1�����Ϊ�������ṩһ�������ͱ�����������ִ�к��Զ��޸ĸñ������ݣ���������ֵ�ƶ�����һ������λ�á�����ƶ��󵽴��ֽڼ���ĩβ�����޸ĸñ���������Ϊ-1��
*/
// ��������
void SetMDataValue (PMDATA_INF pRetData, LPBYTE pData, INT nDataSize)
{
	switch (pRetData->m_dtDataType)
	{
	case SDT_BYTE:
		pRetData->m_byte = *pData;
		break;
	case SDT_SHORT:
		pRetData->m_short = *(SHORT*)pData;
		break;
	case SDT_INT:
		pRetData->m_int = *(INT*)pData;
		break;
	case SDT_INT64:
		pRetData->m_int64 = *(INT64*)pData;
		break;
	case SDT_FLOAT:
		pRetData->m_float = *(FLOAT*)pData;
		break;
	case SDT_DOUBLE:
		pRetData->m_double = *(DOUBLE*)pData;
		break;
	case SDT_BOOL:
		pRetData->m_bool = (*(BOOL*)pData != FALSE);
		break;
	case SDT_DATE_TIME:
		pRetData->m_date = *(DATE*)pData;//max (MIN_DATE, min (MAX_DATE, *(DATE*)pData));
		break;
	case SDT_SUB_PTR:
		pRetData->m_dwSubCodeAdr = *(LPDWORD)pData;
		break;
	case SDT_TEXT: {
		INT nEndPos = FindByte (pData, nDataSize, 0);
		pRetData->m_pText = CloneTextData ((char*)pData,
			(nEndPos != -1 ? nEndPos : nDataSize));
		
		break; }
	case SDT_BIN:
		pRetData->m_pBin = CloneBinData (pData, nDataSize);
		break;
//		DEFAULT_FAILD;
	}
}

LIBAPI(void, krnln_GetBinElement) // ֱ���޸�eax,edx,ecx�����Բ���Ҫָ������ֵ����
{
	PMDATA_INF pArgInf = &ArgInf;

	INT nType = pArgInf [1].m_int;
	if (nType < 1 || nType > 10)
		E_ReportError(100,0,0);

	//!!! �������Ϊ���� _SDT_ALL �����������ݣ����������
	// pRetData->m_dtDataType Ϊ���������ݵ� DATA_TYPE ��
	MDATA_INF RetData;
	memset(&RetData,0,sizeof(MDATA_INF));
	RetData.m_dtDataType =
		nType == 1 ? SDT_BYTE :
	nType == 2 ? SDT_SHORT :
	nType == 3 ? SDT_INT :
	nType == 4 ? SDT_INT64 :
	nType == 5 ? SDT_FLOAT :
	nType == 6 ? SDT_DOUBLE :
	nType == 7 ? SDT_BOOL :
	nType == 8 ? SDT_DATE_TIME :
	nType == 9 ? SDT_SUB_PTR :
	SDT_TEXT;

	if(pArgInf [0].m_pBin==NULL) 
	{
		__asm{
			mov eax, RetData.m_unit.m_dwFormID;
			mov edx, RetData.m_unit.m_dwUnitID;
			mov ecx, RetData.m_dtDataType;
		}
		return;
	}


	LPBYTE pData = pArgInf [0].m_pBin + sizeof (INT) * 2;
	INT nDataSize = *(LPINT)(pData - sizeof (INT));
	

	INT nOffset;
	LPINT pOffset = NULL;
	if(pArgInf[2].m_dtDataType == _SDT_NULL)
		nOffset = 0;
	else
	{
		if(pArgInf[2].m_dtDataType == VAR_INT)//�Ǳ���
		{
			nOffset = *pArgInf[2].m_pInt - 1;
			pOffset = pArgInf[2].m_pInt;

		}
		else
			nOffset = pArgInf[2].m_int - 1;

	}



	INT nNeedSize = GetSysDataTypeDataSize (RetData.m_dtDataType);
	pData += nOffset;
	nDataSize -= nOffset;
	if(nOffset < 0 || nDataSize <=0)
	{
		if(pOffset)*pOffset = -1;
		goto end;
	}
	
	DWORD dwbuf [2];
	
	if (nType != 10 && nDataSize < nNeedSize)
	{
		ASSERT (nDataSize < sizeof (dwbuf));
		dwbuf [0] = dwbuf [1] = 0;
		memcpy (dwbuf, pData, nDataSize);
		pData = (LPBYTE)dwbuf;
		nDataSize = nNeedSize;
	}
	SetMDataValue (&RetData, pData, nDataSize);
	if(pOffset)
	{
		if(nType == 10){
			if(RetData.m_pText)
				*pOffset+=(mystrlen(RetData.m_pText)+1);
			else
				*pOffset+=1;//strlenȡ���ı�ָ��NULLʱ�����
		}else
			*pOffset+=nNeedSize;
		if(*pOffset > pArgInf [0].m_pInt[1])
			*pOffset = -1;//�������ݳ�����
	}

end:
	__asm{
		mov eax, RetData.m_unit.m_dwFormID;
		mov edx, RetData.m_unit.m_dwUnitID;
		mov ecx, RetData.m_dtDataType;
	}
}
