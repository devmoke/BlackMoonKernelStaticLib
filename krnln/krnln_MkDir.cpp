#include "stdafx.h"

//���̲��� - ����Ŀ¼
/*
    ���ø�ʽ�� ���߼��͡� ����Ŀ¼ ���ı��� ��������Ŀ¼���ƣ� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�MkDir
    ����һ���µ�Ŀ¼���ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ����������Ŀ¼���ơ�������Ϊ���ı��ͣ�text������
*/
LIBAPI(BOOL, krnln_MkDir)
{
	SECURITY_ATTRIBUTES SecAttrib;
	SecAttrib.nLength=sizeof(SECURITY_ATTRIBUTES);
	SecAttrib.lpSecurityDescriptor = NULL;
	SecAttrib.bInheritHandle = FALSE;
	
	return CreateDirectory(ArgInf.m_pText,&SecAttrib);//����Ŀ¼
}
