#include "stdafx.h"

//ϵͳ���� - �ָ����
/*
    ���ø�ʽ�� ���޷���ֵ�� �ָ���� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�RestroeCursor
    ������ָ���������ԭ����״�������롰�õȴ���ꡱ�������ʹ�á�������Ϊ�������
*/
HCURSOR hCurOld = NULL;

LIBAPI(void, krnln_RestroeCursor)
{

	if(hCurOld)
	{
		SetCursor(hCurOld);
		hCurOld = NULL;
	}
}
