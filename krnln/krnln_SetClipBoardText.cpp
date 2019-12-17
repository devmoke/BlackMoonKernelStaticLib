#include "stdafx.h"
#include "Myfunctions.h"

//ϵͳ���� - �ü������ı�
/*
    ���ø�ʽ�� ���߼��͡� �ü������ı� ���ı��� ׼�������������ı��� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�SetClipBoardText
    ��ָ���ı���ŵ���ǰ Windows ϵͳ��������ȥ���������е�ԭ�����ݱ����ǡ��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ��׼�������������ı���������Ϊ���ı��ͣ�text������

*/
LIBAPI(BOOL, krnln_SetClipBoardText)
{
	BOOL bRet = FALSE;
	if(ArgInf.m_pText && OpenClipboard(NULL))
	{
		EmptyClipboard();
		INT nLen = mystrlen(ArgInf.m_pText)+1;
		HGLOBAL hClip = GlobalAlloc(0x42,nLen);
		if(hClip)
		{
			LPSTR pStr = (LPSTR)GlobalLock(hClip);
			strcpy(pStr,ArgInf.m_pText);
			GlobalUnlock(hClip);
			SetClipboardData(CF_TEXT,hClip);
			bRet = TRUE;
		}
		CloseClipboard();
	}
	return bRet;

}
