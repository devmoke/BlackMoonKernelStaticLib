#include "stdafx.h"

//�ļ���д - �ر��ļ�
/*
    ���ø�ʽ�� ���޷���ֵ�� �ر��ļ� �������� ���رյ��ļ��ţ� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�close
    �رձ��򿪵ĸ��������ļ���������Ϊ�������
    ����<1>������Ϊ�����رյ��ļ��š�������Ϊ�������ͣ�int����������ֵָ�����رյ��ļ��ţ����ļ����ɡ����ļ������������ء�
*/
LIBAPI(void, krnln_close)
{
	if(ArgInf.m_pCompoundData)
		CloseEfile((PFILEELEMENT)ArgInf.m_pCompoundData);
}
