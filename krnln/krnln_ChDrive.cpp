#include "stdafx.h"

//���̲��� - �ı�������
/*
    ���ø�ʽ�� ���߼��͡� �ı������� ���ı��� ���ı䵽���������� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�ChDrive
    �ı䵱ǰ��ȱʡ���������ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ�����ı䵽����������������Ϊ���ı��ͣ�text����������ֵָ��һ�����ڵ������������ơ�A������B������C���ȣ�ֻȡ�ø����ı��ĵ�һ���ַ������ʹ���㳤�ȵ��ı�����ǰ������������ı䡣
*/
LIBAPI(BOOL, krnln_ChDrive)
{
	char DirName [MAX_PATH];

	if(!*(ArgInf.m_pText))
		return FALSE;

	DirName[0]=*ArgInf.m_pText;
	DirName[1]=':';
	DirName[2]='\\';
	DirName[3]=0;

	return SetCurrentDirectory(DirName);
}
