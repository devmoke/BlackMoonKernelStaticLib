#include "stdafx.h"

//���̲��� - �����ļ�
/*
    ���ø�ʽ�� ���߼��͡� �����ļ� ���ı��� �����Ƶ��ļ������ı��� ���Ƶ����ļ����� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�FileCopy
    �ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ�������Ƶ��ļ�����������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ�����Ƶ����ļ�����������Ϊ���ı��ͣ�text������

*/
LIBAPI(BOOL, krnln_FileCopy)
{
	PMDATA_INF pArgInf = &ArgInf;
	return CopyFile(pArgInf[0].m_pText,pArgInf[1].m_pText,FALSE);
}
