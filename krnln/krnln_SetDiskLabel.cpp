#include "stdafx.h"
#include "Myfunctions.h"

//���̲��� - �ô��̾��
/*
    ���ø�ʽ�� ���߼��͡� �ô��̾�� �����ı��� �����������ַ��ݣ��ı��� ������ľ���ı��� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�SetDiskLabel
    ����ָ�����̵ľ���ı����ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ�������������ַ���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ����ơ�A������B������C���ȣ�ֻȡ�ø����ı��ĵ�һ���ַ��������������ʡ�ԣ�Ĭ��ʹ�õ�ǰ��������
    ����<2>������Ϊ��������ľ���ı���������Ϊ���ı��ͣ�text������
*/
LIBAPI(BOOL, krnln_SetDiskLabel)
{
	char DirName [MAX_PATH];
	if(ArgInf.m_dtDataType == _SDT_NULL)
	{
		if(GetCurrentDirectory(MAX_PATH,DirName)==0)
			return FALSE;
		DirName[3]=0;

	}
	else
	{
		if(mystrlen(ArgInf.m_pText)==0)
			return FALSE;

		DirName[0]=*ArgInf.m_pText;
		DirName[1]=':';
		DirName[2]='\\';
		DirName[3]=0;

	}

	PMDATA_INF pArgInf = &ArgInf;

	return SetVolumeLabel (DirName,pArgInf[1].m_pText);
}
