#include "stdafx.h"

//���� - �����¼�
/*
    ���ø�ʽ�� ���޷���ֵ�� �����¼� ���� - ϵͳ����֧�ֿ�->����
    Ӣ�����ƣ�DoEvents
    ��ʱת�ÿ���Ȩ���Ա��� Windows ����ϵͳ�л��ᴦ�����������û����̻����������¼���ֱ������ϵͳ�����������������е������¼�������Ż᷵�ء�������Ϊ�м����
*/
LIBAPI(void, krnln_DoEvents)
{
	MSG Msg;
	while(PeekMessage(&Msg,NULL,NULL,NULL,PM_NOREMOVE))
	{
		if(Msg.message == WM_QUIT)
			break;
		GetMessage (&Msg, NULL, 0, 0);
		TranslateMessage (&Msg);
		DispatchMessage (&Msg);
	}
}
