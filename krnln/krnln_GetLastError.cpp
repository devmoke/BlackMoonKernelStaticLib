#include "stdafx.h"

//ϵͳ���� - ȡ������
/*
    ���ø�ʽ�� �������͡� ȡ������ ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetLastError
    ���ò���ϵͳ��GetLastError����,���ظ�API���������ú�ķ���ֵ.������Ϊ�������
	
	����ϵͳ���� Windows
*/
LIBAPI(INT, krnln_GetLastError)
{
	return GetLastError();
}