#include "stdafx.h"
/*
	���ø�ʽ�� ��˫����С���͡�ָ�뵽˫����С�� (������ �ڴ�����ָ��)
	Ӣ�����ƣ�p2double
	����ָ���ڴ�ָ����ָ���ַ����һ��˫����С��(DOUBLE)��ע����ñ�����ǰһ��Ҫȷ�����ṩ���ڴ��ַ����ʵ��Ч��
	����<1>������Ϊ���ڴ�����ָ�롱������Ϊ�������͡����������ṩָ��һ���ڴ��ַ��ָ��ֵ
*/
LIBAPI(void, krnln_p2double)
{
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_int!=0)
	{
		ArgInf.m_double = *(DOUBLE*)pArgInf [0].m_int;
	}else{
		ArgInf.m_double =0.0;
	}
	__asm
	{
		mov eax,ArgInf.m_unit.m_dwFormID;
		mov edx,ArgInf.m_unit.m_dwUnitID;
	}
}
