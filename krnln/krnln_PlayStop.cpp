#include "stdafx.h"
#pragma comment(lib,"winmm.lib") 
//ý�岥�� - ֹͣ����
/*
    ���ø�ʽ�� ���޷���ֵ�� ֹͣ���� ���� - ϵͳ����֧�ֿ�->ý�岥��
    Ӣ�����ƣ�PlayStop
    ֹͣ���ڲ��ŵ����֡�������Ϊ�������
*/
LIBAPI(void, krnln_PlayStop)
{
	PlaySound(NULL,NULL,SND_PURGE);
}
