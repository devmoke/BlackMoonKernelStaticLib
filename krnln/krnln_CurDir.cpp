#include "stdafx.h"
#include "Myfunctions.h"
//���̲��� - ȡ��ǰĿ¼
/*
    ���ø�ʽ�� ���ı��͡� ȡ��ǰĿ¼ ���� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�CurDir
    ����һ���ı�����������ǰ��Ŀ¼�����ʧ�ܣ����ؿ��ı���������Ϊ�������
*/
LIBAPI(char*, krnln_CurDir)
{
	char DirName [MAX_PATH];
	char* pText = NULL;

	if(GetCurrentDirectory(MAX_PATH,DirName))
	{
		INT nLen = mystrlen(DirName);
		pText = CloneTextData(DirName,nLen);
	}
	return pText;
}
