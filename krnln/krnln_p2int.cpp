#include "stdafx.h"
/*
	���ø�ʽ�� �������͡�ָ�뵽���� (������ �ڴ�����ָ��)
	Ӣ�����ƣ�p2int
	����ָ���ڴ�ָ����ָ���ַ����һ������(INT)��ע����ñ�����ǰһ��Ҫȷ�����ṩ���ڴ��ַ����ʵ��Ч��
	����<1>������Ϊ���ڴ�����ָ�롱������Ϊ�������͡����������ṩָ��һ���ڴ��ַ��ָ��ֵ
*/	
LIBAPI(int, krnln_p2int)
{
	PMDATA_INF pArgInf = &ArgInf;
	//if(!IsBadReadPtr((LPVOID)pArgInf[0].m_int,sizeof(int)))
	if(pArgInf[0].m_int!=0)
	{
		return *((int*)pArgInf [0].m_int);
	}
	return 0;
}
