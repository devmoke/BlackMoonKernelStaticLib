#include "stdafx.h"
#include <math.h>
//�������� - ȡ��
/*
    ���ø�ʽ�� �������͡� ȡ�� ��˫����С���� ��ȡ����С���� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�int
    ����һ��С�����������֡��������롰����ȡ���������֮ͬ��Ϊ��
�������С��Ϊ�������������С�ڻ���ڸ�С���ĵ�һ������������������ȡ����������᷵�ش��ڻ���ڸ�С���ĵ�һ�������������磬����� -7.8 ת���� -8����������ȡ������� -7.8 ת���� -7��������Ϊ�������
    ����<1>������Ϊ����ȡ����С����������Ϊ��˫����С���ͣ�double������
*/
double __cdecl ProcessDouble(double a1)
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

LIBAPI(int, krnln_int)
{
	return floor(ProcessDouble(ArgInf.m_double));
}
