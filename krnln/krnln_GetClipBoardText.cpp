#include "stdafx.h"
#include "Myfunctions.h"
//ϵͳ���� - ȡ�������ı�
/*
    ���ø�ʽ�� ���ı��͡� ȡ�������ı� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetClipBoardText
    ���ش���ڵ�ǰ Windows ϵͳ�������е��ı��������ǰ�����������ı����ݣ������ؿ��ı���������Ϊ�������
*/
LIBAPI(char*, krnln_GetClipBoardText)
{

	char* pText = NULL;
	if(OpenClipboard(NULL))
	{
		HANDLE hClip =  GetClipboardData(CF_TEXT);
		if(hClip)
		{
			LPSTR pStr = (LPSTR)GlobalLock(hClip);
			pText = CloneTextData(pStr,mystrlen(pStr));
			GlobalUnlock(hClip);
		}
		CloseClipboard();
	}
	return pText;
}
