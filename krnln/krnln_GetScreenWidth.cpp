#include "stdafx.h"

//ϵͳ���� - ȡ��Ļ���
/*
    ���ø�ʽ�� �������͡� ȡ��Ļ��� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetScreenWidth
    ������Ļ��ǰ��ʾ����Ŀ�ȣ���λΪ���ص㡣������Ϊ�������
*/
LIBAPI(int, krnln_GetScreenWidth)
{
	return GetSystemMetrics(SM_CXSCREEN);
}
