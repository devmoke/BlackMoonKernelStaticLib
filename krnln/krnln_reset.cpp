#include "stdafx.h"

//�ļ���д - �ر������ļ�
/*
    ���ø�ʽ�� ���޷���ֵ�� �ر������ļ� ���� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�reset
    �ر��������б��򿪵��ļ���������Ϊ�������
*/
extern PFILEELEMENT pFileList;

LIBAPI(void, krnln_reset)
{
	if(pFileList)
		ResetFileIO();
}
