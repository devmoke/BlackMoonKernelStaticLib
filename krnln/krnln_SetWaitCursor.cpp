#include "stdafx.h"

//ϵͳ���� - �õȴ����
/*
    ���ø�ʽ�� ���޷���ֵ�� �õȴ���� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�SetWaitCursor
    ��������������������״Ϊɳ©�Σ������ڼ�����ʱ��ִ�г���ǰ��ʾ�����ߡ�������Ϊ�������
*/
extern HCURSOR hCurOld;

LIBAPI(void, krnln_SetWaitCursor)
{
	if(hCurOld==NULL)
	{
		HCURSOR hCur =  LoadCursor(NULL,IDC_WAIT);
		hCurOld = SetCursor(hCur);
	}
}
