#include "stdafx.h"

//ϵͳ���� - ȡ����ʱ��
/*
    ���ø�ʽ�� �������͡� ȡ����ʱ�� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetTickCount
    ������ Windows ϵͳ����������Ϊֹ���������ĺ�������������Ϊ�������
*/
LIBAPI(int, krnln_GetTickCount)
{
	return GetTickCount();
}
