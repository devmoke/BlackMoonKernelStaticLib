#include "stdafx.h"

//���̲��� - �ļ�����
/*
    ���ø�ʽ�� ���߼��͡� �ļ����� ���ı��� ��������ԭ�ļ���Ŀ¼�����ı��� ������Ϊ�����ļ���Ŀ¼���� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�name
    ��������һ���ļ���Ŀ¼���ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ����������ԭ�ļ���Ŀ¼����������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ��������Ϊ�����ļ���Ŀ¼����������Ϊ���ı��ͣ�text������
*/
LIBAPI(BOOL, krnln_name)
{
	PMDATA_INF pArgInf = &ArgInf;
	return MoveFile(pArgInf[0].m_pText,pArgInf[1].m_pText);
}