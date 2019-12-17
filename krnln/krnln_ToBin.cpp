#include "stdafx.h"
#include "Myfunctions.h"
//�ֽڼ����� - ���ֽڼ�
/*
    ���ø�ʽ�� ���ֽڼ��� ���ֽڼ� ��ͨ��������/������ ��ת��Ϊ�ֽڼ������ݣ� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�ToBin
    ��ָ������ת��Ϊ�ֽڼ��󷵻�ת�������������Ϊ�������
    ����<1>������Ϊ����ת��Ϊ�ֽڼ������ݡ�������Ϊ��ͨ���ͣ�all�������ṩ��������ʱ����ͬʱ�ṩ�������������ݡ�����ֵֻ��Ϊ���������������ݻ���ֵ�����顣
*/
        // ��������
LPBYTE GetMDataPtr (PMDATA_INF pInf, LPINT pnDataSize)
{
//	ASSERT (GetDataTypeType (pInf->m_dtDataType) == DTT_IS_SYS_DATA_TYPE);
	
	switch (pInf->m_dtDataType)
	{
	case SDT_BYTE:
		*pnDataSize = sizeof (BYTE);
		return (LPBYTE)&pInf->m_byte;
	case SDT_SHORT:
		*pnDataSize = sizeof (SHORT);
		return (LPBYTE)&pInf->m_short;
	case SDT_INT:
		*pnDataSize = sizeof (INT);
		return (LPBYTE)&pInf->m_int;
	case SDT_INT64:
		*pnDataSize = sizeof (INT64);
		return (LPBYTE)&pInf->m_int64;
	case SDT_FLOAT:
		*pnDataSize = sizeof (FLOAT);
		return (LPBYTE)&pInf->m_float;
	case SDT_DOUBLE:
		*pnDataSize = sizeof (DOUBLE);
		return (LPBYTE)&pInf->m_double;
	case SDT_BOOL:
		*pnDataSize = sizeof (BOOL);
		return (LPBYTE)&pInf->m_bool;
	case SDT_DATE_TIME:
		*pnDataSize = sizeof (DATE);
		return (LPBYTE)&pInf->m_date;
	case SDT_SUB_PTR:
		*pnDataSize = sizeof (DWORD);
		return (LPBYTE)&pInf->m_dwSubCodeAdr;
	case SDT_TEXT:
		*pnDataSize = mystrlen (pInf->m_pText) + 1;
		return (LPBYTE)pInf->m_pText;
	case SDT_BIN: {
		LPBYTE pBinData = pInf->m_pBin + sizeof (INT) * 2;
		*pnDataSize = *(LPINT)(pBinData - sizeof (INT));
		return pBinData; }
	default:
//		ASSERT (FALSE);
		return NULL;
	}
}
int __cdecl IsNumDataType2(DWORD a1)
{
  int result; // eax@1

  result = GetDataTypeType(a1);
  if ( result != 1 || (BYTE)a1 != 1 )
    result = 0;
  return result;
}
int __cdecl GetSysDataTypeDataSize2( int a1)
{
  if ( (DWORD)a1 <= 0x80000101 )
  {
    if ( a1 == -2147483391 )
      return 1;
    switch ( a1 )
    {
      case -2147483645:
      case -2147483640:
        return 8;
      case -2147483646:
      case -2147483644:
      case -2147483643:
      case -2147483642:
        return 4;
      default:
        return 0;
    }
    return 0;
  }
  if ( (unsigned int)a1 <= 0x80000401 )
  {
    if ( a1 != -2147482623 )
    {
      if ( a1 == -2147483135 )
        return 2;
      if ( a1 == -2147482879 )
        return 4;
      return 0;
    }
    return 8;
  }
  if ( a1 == -2147482367 )
    return 4;
  if ( a1 == -2147482111 )
    return 8;
  return 0;
}

LIBAPI(void*, krnln_ToBin)
{
            //!!! ���ھ��� AS_RECEIVE_VAR_OR_ARRAY �� AS_RECEIVE_ALL_TYPE_DATA ��־�Ĳ�����
            // �����������п��ܴ���DT_IS_ARY�����־�����������·�ʽ��������������ͺ������־��

	PMDATA_INF pArgInf = &ArgInf;
	DATA_TYPE dtDataType = pArgInf [0].m_dtDataType & ~DT_IS_ARY;
	BOOL blIsAry = (pArgInf [0].m_dtDataType & DT_IS_ARY) != 0;
	
	LPBYTE pData;
	INT nDataSize;
	if (IsNumDataType2(dtDataType) && blIsAry == TRUE)
	{
		DWORD dwSize;
		pData = (LPBYTE)GetAryElementInf(pArgInf [0].m_pAryData,dwSize);
		nDataSize = dwSize * GetSysDataTypeDataSize2(dtDataType);
	}
	else if (blIsAry == TRUE || GetDataTypeType (dtDataType) != DTT_IS_SYS_DATA_TYPE)
	{
		return NULL;
	}
	else if (dtDataType == SDT_TEXT)
	{
		pData = (LPBYTE)pArgInf->m_pText;
		nDataSize = mystrlen (pArgInf->m_pText);
	}
	else
		pData = GetMDataPtr (pArgInf, &nDataSize);
	
	return CloneBinData (pData, nDataSize);
}
