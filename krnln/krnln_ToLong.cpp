#include "stdafx.h"

//��ֵת�� - ��������
/*
    ���ø�ʽ�� ���������͡� �������� ��ͨ���� ��ת�����ı�����ֵ�� - ϵͳ����֧�ֿ�->��ֵת��
    Ӣ�����ƣ�ToLong
    ���ذ������ı��ڵĳ�����ֵ���ı�����һ���ʵ����͵���ֵ��֧��ȫ����д��ʽ��������Ҳ���������������͵�����ת��Ϊ��������������Ϊ�������
    ����<1>������Ϊ����ת�����ı�����ֵ��������Ϊ��ͨ���ͣ�all������
*/
LIBAPI(void, krnln_ToLong)
{
	INT64 nRet=0;
	switch(ArgInf.m_dtDataType)
	{
	case SDT_BYTE:
		{
// 			INT nVal = ArgInf.m_byte;
// 			ArgInf.m_int64 = nVal;
			nRet = ArgInf.m_byte;
		}
		break;
	case SDT_SHORT:
		{
// 			INT nVal = ArgInf.m_short;
// 			ArgInf.m_int64 = nVal;
			nRet = ArgInf.m_short;
		}
		break;
	case SDT_TEXT:
		{
			char* pStr = krnln_BJCase(1,ArgInf);
			if(pStr)
			{
				nRet = _atoi64(pStr);
				ArgInf.m_int64 = nRet;
				E_MFree(pStr);
			}
// 			else
// 				nRet = 0;
		}
		break;
	case SDT_FLOAT:
		nRet = ArgInf.m_float;
//		ArgInf.m_int64 = nRet;
		break;
	case SDT_DOUBLE:
		nRet = ArgInf.m_double;
//		ArgInf.m_int64 = nRet;
		break;
	default:
		break;
	}
	ArgInf.m_int64 = nRet;
	__asm{
		mov eax, ArgInf.m_unit.m_dwFormID;
		mov edx, ArgInf.m_unit.m_dwUnitID;
	}
}
