#include "stdafx.h"
#include <math.h>
//�������� - �󷴶���
/*
    ���ø�ʽ�� ��˫����С���͡� �󷴶��� ��˫����С���� �����䷴��������ֵ�� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�exp
    ���� e����Ȼ�����ĵף���ĳ�η���������Ϊ�������
    ����<1>������Ϊ�������䷴��������ֵ��������Ϊ��˫����С���ͣ�double�������������ֵ���� 709.782712893�������¼��������
*/
LIBAPI(void, krnln_exp) // ֱ���޸�eax��edx��ֵ����������ָ������ֵ���͡�
{
	ArgInf.m_double = exp(ArgInf.m_double);
	__asm
	{
		mov eax,ArgInf.m_unit.m_dwFormID;
		mov edx,ArgInf.m_unit.m_dwUnitID;
	}
}
