#include "stdafx.h"

//ϵͳ���� - ȡ���ˮƽλ��
/*
    ���ø�ʽ�� �������͡� ȡ���ˮƽλ�� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetCursorHorzPos
    �������ָ��ĵ�ǰˮƽλ�ã���λΪ���ص㣬�������Ļ��ߡ�������Ϊ�������
*/
LIBAPI(int, krnln_GetCursorHorzPos)
{
	POINT point;
	if(GetCursorPos(&point))
		return point.x;
	return 0;
}
