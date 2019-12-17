#include "stdafx.h"
//��ֵת�� - ��С��
/*
    ���ø�ʽ�� ��С���͡� ��С�� ��ͨ���� ��ת�����ı�����ֵ�� - ϵͳ����֧�ֿ�->��ֵת��
    Ӣ�����ƣ�ToFloat
    ���ذ������ı��ڵ�С��ֵ���ı�����һ���ʵ����͵���ֵ��֧��ȫ����д��ʽ��������Ҳ���������������͵�����ת��ΪС����������Ϊ�������
    ����<1>������Ϊ����ת�����ı�����ֵ��������Ϊ��ͨ���ͣ�all������
*/
LIBAPI(void, krnln_ToFloat)
{
	float nRet=0;
	switch(ArgInf.m_dtDataType)
	{
	case SDT_TEXT:
		{
			char* pStr = krnln_BJCase(1,ArgInf);
			if(pStr)
			{
				nRet = (float)atof(pStr);
				E_MFree(pStr);
			}
		}
		break;
	case SDT_BYTE:
		nRet = ArgInf.m_byte;
		break;
	case SDT_SHORT:
		nRet = ArgInf.m_short;
		break;
	case SDT_INT:
	case SDT_SUB_PTR:
	case SDT_BOOL:
		nRet = ArgInf.m_int;
		break;
	case SDT_FLOAT:
		nRet = ArgInf.m_float;
		break;
	case SDT_DOUBLE:
		nRet = ArgInf.m_double;
		break;
	case SDT_INT64:
		nRet = ArgInf.m_int64;
		break;
	default:
		break;

	}
	_asm mov eax, nRet;
	_asm xor edx, edx;
	//return nRet;
}
