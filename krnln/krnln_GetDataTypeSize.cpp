#include "stdafx.h"

//���� - ȡ�������ͳߴ�
/*
    ���ø�ʽ�� �������͡� ȡ�������ͳߴ� �������� ��ȡ��ߴ���������ͣ� - ϵͳ����֧�ֿ�->����
    Ӣ�����ƣ�GetDataTypeSize
    ȡָ���������͵����ݳߴ磬���������Ͳ���Ϊ�ı����ֽڼ�������û��Զ����������͡�������Ϊ�������
    ����<1>������Ϊ����ȡ��ߴ���������͡�������Ϊ�������ͣ�int����������ֵ����Ϊ���³�����
	1��#�ֽ��ͣ� 2��#�������ͣ� 3��#�����ͣ� 4��#�������ͣ� 5��#С���ͣ� 6��#˫����С���ͣ� 7��#�߼��ͣ� 8��#����ʱ���ͣ� 9��#�ӳ���ָ���͡�
*/
LIBAPI(int, krnln_GetDataTypeSize)
{
	switch (ArgInf.m_int)
	{
	case 1://SDT_BYTE:
		return sizeof (BYTE);
	case 2://SDT_SHORT:
		ASSERT (sizeof (SHORT) == 2);
		return sizeof (SHORT);
	case 7://SDT_BOOL:
		ASSERT (sizeof (BOOL) == 4);
		return sizeof (BOOL);
	case 3://SDT_INT:
		ASSERT (sizeof (INT) == 4);
		return sizeof (INT);
	case 5://SDT_FLOAT:
		ASSERT (sizeof (FLOAT) == 4);
		return sizeof (FLOAT);
	case 9://SDT_SUB_PTR:    // ��¼�ӳ������ĵ�ַָ��
		return sizeof (DWORD);
	//case SDT_TEXT:    // �ı��ͺ��ֽڼ���Ϊһ��ָ��,���Ϊ�ĸ��ֽ�.
	//case SDT_BIN:
		//return sizeof (DWORD);
	case 4://SDT_INT64:
		ASSERT (sizeof (INT64) == 8);
		return sizeof (INT64);
	case 6://SDT_DOUBLE:
		ASSERT (sizeof (DOUBLE) == 8);
		return sizeof (DOUBLE);
	case 8://SDT_DATE_TIME:
		ASSERT (sizeof (DATE) == 8);
		return sizeof (DATE);
	default:
		ASSERT (FALSE);
		return 0;
	}
	
	return 0;



}
