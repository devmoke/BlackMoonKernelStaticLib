#include "stdafx.h"

//ϵͳ���� - ȡ��Ļ�߶�
/*
    ���ø�ʽ�� �������͡� ȡ��Ļ�߶� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetScreenHeight
    ������Ļ��ǰ��ʾ����ĸ߶ȣ���λΪ���ص㡣������Ϊ�������
*/

LIBAPI(int, krnln_GetScreenHeight)
{
	return GetSystemMetrics(SM_CYSCREEN);
}
