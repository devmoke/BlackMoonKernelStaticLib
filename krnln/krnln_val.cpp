#include "stdafx.h"

//��ֵת�� - ����ֵ
/*
    ���ø�ʽ�� ��˫����С���͡� ����ֵ ��ͨ���� ��ת�����ı�����ֵ�� - ϵͳ����֧�ֿ�->��ֵת��
    Ӣ�����ƣ�val
    ���ذ������ı��ڵ���ֵ���ı�����һ���ʵ����͵���ֵ��֧��ȫ����д��ʽ��������Ҳ���������������͵�����ת��Ϊ˫����С����������Ϊ�������
    ����<1>������Ϊ����ת�����ı�����ֵ��������Ϊ��ͨ���ͣ�all������
*/
LIBAPI(void, krnln_val)
{
	switch(ArgInf.m_dtDataType)
	{
	case SDT_BYTE:
		{
			INT nVal = ArgInf.m_byte;
			ArgInf.m_double = nVal;
		}
		break;
	case SDT_SHORT:
		{
			INT nVal = ArgInf.m_short;
			ArgInf.m_double = nVal;
		}
		break;
	case SDT_TEXT:
		{
			char* pStr = krnln_BJCase(1,ArgInf);
			if(pStr)
			{
				ArgInf.m_double = strtod(pStr,NULL);
				E_MFree(pStr);
			}
			else
				ArgInf.m_double = 0;
			//ArgInf.m_double = strtod(ArgInf.m_pText,NULL);
		}
		break;
	case SDT_DATE_TIME:
	case SDT_DOUBLE:
		break;
	case SDT_FLOAT:
		{
			FLOAT floatval = ArgInf.m_float;
			ArgInf.m_double = floatval;
		}
		break;
	case SDT_INT64:
		{
			INT64 int64 = ArgInf.m_int64;
			ArgInf.m_double = int64;
		}
		break;
	default:
		{
			INT nVal = ArgInf.m_int;
			ArgInf.m_double = nVal;//100��1��1��
		}
	}
	__asm{
		mov eax, ArgInf.m_unit.m_dwFormID;
		mov edx, ArgInf.m_unit.m_dwUnitID;
	}
}
