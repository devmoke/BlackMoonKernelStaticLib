#include "stdafx.h"
#include <math.h>
//�������� - ����ȡ��
/*
    ���ø�ʽ�� �������͡� ����ȡ�� ��˫����С���� ��ȡ����С���� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�fix
    ����һ��С�����������֡��������롰ȡ���������֮ͬ��Ϊ��
�������С��Ϊ������������ش��ڻ���ڸ�С���ĵ�һ��������������ȡ����������᷵��С�ڻ���ڸ�С���ĵ�һ�������������磬����� -7.8 ת���� -7������ȡ������� -7.8 ת���� -8��������Ϊ�������
    ����<1>������Ϊ����ȡ����С����������Ϊ��˫����С���ͣ�double������
*/
double __cdecl ProcessDouble2(double a1)
{
  double v1; // st7@1
  double result; // st7@6
  double v3; // [sp+0h] [bp-8h]@1
  signed int v4; // [sp+Ch] [bp+4h]@4

  v1 = modf(a1, &v3);
  if ( v1 < 0.0 )
    v1 = -v1;
  if ( v1 <= 0.999999999999 )
  {
    result = a1;
  }
  else
  {
    v4 = -1;
    if ( v3 >= 0.0 )
      v4 = 1;
    result = (double)v4 + v3;
  }
  return result;
}

LIBAPI(int, krnln_fix)
{
	INT nRet;
/*	if(0<ArgInf.m_double)
		nRet = floor(ArgInf.m_double);
	else
		nRet = ceil(ArgInf.m_double);*/
	double v5;
	modf(ProcessDouble2(ArgInf.m_double), &v5);
	nRet = v5;
	return nRet;
}
