#include "stdafx.h"

//ϵͳ���� - ȡĬ�ϵ�ɫ
/*
    ���ø�ʽ�� �������͡� ȡĬ�ϵ�ɫ ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetBackColor
    ȡ��Windowsϵͳ��Ĭ�ϴ��ڱ�����ɫ��������Ϊ�������
*/
LIBAPI(int, krnln_GetBackColor)
{
	return GetSysColor(0xF);
}
