#include "stdafx.h"
#include <SHLWAPI.h>
#pragma comment(lib,"SHLWAPI.lib") 
//���̲��� - �ļ��Ƿ����
/*
    ���ø�ʽ�� ���߼��͡� �ļ��Ƿ���� ���ı��� �����Ե��ļ����ƣ� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�IsFileExist
    �ж�ָ���Ĵ����ļ��Ƿ���ʵ���ڡ�����ڷ����棬���򷵻ؼ١�������Ϊ�������
    ����<1>������Ϊ�������Ե��ļ����ơ�������Ϊ���ı��ͣ�text������
*/
LIBAPI(BOOL, krnln_IsFileExist)
{
	return PathFileExists(ArgInf.m_pText);
}
