#include "stdafx.h"

//ϵͳ���� - ���������
/*
    ���ø�ʽ�� ���޷���ֵ�� ��������� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�ClearClipBoard
    �����ǰ Windows ϵͳ�������е��������ݡ�������Ϊ�������
*/
LIBAPI(void, krnln_ClearClipBoard)
{
	if(OpenClipboard(NULL))
	{
		EmptyClipboard();
		CloseClipboard();
	}
}
