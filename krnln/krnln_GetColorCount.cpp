#include "stdafx.h"
#pragma comment(lib,"gdi32.lib") 
//ϵͳ���� - ȡ��ɫ��
/*
    ���ø�ʽ�� �������͡� ȡ��ɫ�� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetColorCount
    ���ص�ǰ��ʾ��ʽ���ṩ�������ɫ��ʾ��Ŀ��������Ϊ�������
*/
LIBAPI(int, krnln_GetColorCount)
{
	HDC hdc = ::GetDC(NULL);
	INT nRet = GetDeviceCaps(hdc,COLORRES);
	::ReleaseDC (NULL,hdc);
	return (1 << nRet);
}
