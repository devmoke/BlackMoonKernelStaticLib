#include "stdafx.h"
/*
	���ø�ʽ�� ��С���͡�ָ�뵽С�� (������ �ڴ�����ָ��)
	Ӣ�����ƣ�p2float
	����ָ���ڴ�ָ����ָ���ַ����һ��С��(FLOAT)��ע����ñ�����ǰһ��Ҫȷ�����ṩ���ڴ��ַ����ʵ��Ч��
	����<1>������Ϊ���ڴ�����ָ�롱������Ϊ�������͡����������ṩָ��һ���ڴ��ַ��ָ��ֵ
*/
LIBAPI(void, krnln_p2float)
{
	float fRet=0.0f;
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_int!=0)
	{
		fRet=*((float*)pArgInf [0].m_int);
	}
	_asm mov eax, fRet;
}
