#include "stdafx.h"

//ʱ����� - ȡĳ������
/*
    ���ø�ʽ�� �������͡� ȡĳ������ �������� ��ݣ������� �·ݣ� - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�GetDaysOfSpecMonth
    ����ָ���·�������������������������·���Ч������0��������Ϊ�������
    ����<1>������Ϊ����ݡ�������Ϊ�������ͣ�int����������ֵ�� 100 �� 9999��
    ����<2>������Ϊ���·ݡ�������Ϊ�������ͣ�int����������ֵ�� 1 �� 12��
*/
LIBAPI(int, krnln_GetDaysOfSpecMonth)
{
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[1].m_int <=0 || pArgInf[1].m_int >12 || pArgInf[0].m_int <100 || pArgInf[1].m_int>9999)
		return 0;
	return GetDaysOfSpecMonth(pArgInf[0].m_int,pArgInf[1].m_int);

}
