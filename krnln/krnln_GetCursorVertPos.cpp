#include "stdafx.h"

//ϵͳ���� - ȡ��괹ֱλ��
/*
    ���ø�ʽ�� �������͡� ȡ��괹ֱλ�� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetCursorVertPos
    �������ָ��ĵ�ǰ��ֱλ�ã���λΪ���ص㣬�������Ļ���ߡ�������Ϊ�������
*/
LIBAPI(int, krnln_GetCursorVertPos)
{
	POINT point;
	if(GetCursorPos(&point))
		return point.y;
	return 0;
}
