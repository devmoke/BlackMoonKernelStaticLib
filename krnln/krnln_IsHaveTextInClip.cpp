#include "stdafx.h"

//ϵͳ���� - �������п����ı�
/*
    ���ø�ʽ�� ���߼��͡� �������п����ı� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�IsHaveTextInClip
    �����ǰ Windows ϵͳ�����������ı����ݣ��򷵻��棬���򷵻ؼ١�������Ϊ�������
*/
LIBAPI(BOOL, krnln_IsHaveTextInClip)
{
	BOOL bRet = FALSE;
	if(OpenClipboard(NULL))
	{
		HANDLE hClip =  GetClipboardData(CF_TEXT);
		if(hClip)
			bRet = TRUE;
		CloseClipboard();
	}
	return bRet;
}
