#include "stdafx.h"

//������� - ��������
/*
    ���ø�ʽ�� ���޷���ֵ�� �������� ��ͨ���ͱ������� ��ֵ������������߼��� �������Ƿ�Ϊ��С����ݣ� - ϵͳ����֧�ֿ�->�������
    Ӣ�����ƣ�SortAry
    ��ָ����ֵ��������ڵ����������Ա���п������򣬲�Ӱ�������ά������Ϣ����������Żظ����������������Ϊ�������
    ����<1>������Ϊ����ֵ���������������Ϊ��ͨ���ͣ�all�������ṩ��������ʱֻ���ṩ�������顣
    ����<2>������Ϊ���������Ƿ�Ϊ��С���󡱣�����Ϊ���߼��ͣ�bool���������Ա�ʡ�ԡ��������ֵΪ�棬������Ϊ��С���󣬷���Ϊ�Ӵ�С�������������ʡ�ԣ�Ĭ��ֵΪ�档
*/
extern DWORD dwBlackMoonPESizeOfImage;
extern DWORD dwBlackMoonPEAddrrStart;
extern DWORD dwBlackMoonPEAddrrEnd;
extern void GetBlackMoonPESizeOfImage();

int __cdecl krnl_MACopyConstAry(int a1, void **a2)
{
  int result; // eax@1
  void *v3; // esi@1
  int v4; // eax@2
  int v5; // edx@2
  int v6; // ecx@2
  int v7; // edi@3
  unsigned int v8; // edi@4
  int v9; // eax@4
  char v10; // zf@4
	
  if(dwBlackMoonPESizeOfImage==0)
	  GetBlackMoonPESizeOfImage();


  v3 = *a2;
  if(dwBlackMoonPEAddrrStart <= (DWORD)v3 && (DWORD)v3 <= dwBlackMoonPEAddrrEnd)
  {
    v5 = *(DWORD *)v3;
    v6 = (int)((char *)v3 + 4);
    v4 = 1;
    if ( *(DWORD *)v3 > 0 )
    {
      do
      {
        v7 = *(DWORD *)v6;
        v6 += 4;
        v4 *= v7;
        --v5;
      }
      while ( v5 );
    }
    v9 = a1 * v4 - (DWORD)v3;
    v10 = v6 + v9 == 0;
    result = v6 + v9;
    v8 = result;
    if ( !v10 )
    {
      result = (int)E_MAlloc_Nzero(result);
      memcpy((void *)result, v3, v8);
      *a2 = (void *)result;
    }
  }
  return result;
}
/*
int __cdecl GetDataTypeType(DWORD a1)
{
  DWORD result; // eax@1

  result = a1;
  if ( a1 )
  {
    if ( (a1 & 0xC0000000) == 0x80000000 )
      result = 1;
    else
      result = DWORD(((a1 & 0xC0000000) != 0x40000000) + 2);
  }
  return result;
}*/

int __cdecl IsNumDataType(DWORD a1)
{
  int result; // eax@1

  result = GetDataTypeType(a1);
  if ( result != 1 || (BYTE)a1 != 1 )
    result = 0;
  return result;
}

int __cdecl GetSysDataTypeDataSize( int a1)
{
  if ( (DWORD)a1 <= 0x80000101 )
  {
    if ( a1 == -2147483391 )
      return 1;
    switch ( a1 )
    {
      case -2147483645:
      case -2147483640:
        return 8;
      case -2147483646:
      case -2147483644:
      case -2147483643:
      case -2147483642:
        return 4;
      default:
        return 0;
    }
    return 0;
  }
  if ( (unsigned int)a1 <= 0x80000401 )
  {
    if ( a1 != -2147482623 )
    {
      if ( a1 == -2147483135 )
        return 2;
      if ( a1 == -2147482879 )
        return 4;
      return 0;
    }
    return 8;
  }
  if ( a1 == -2147482367 )
    return 4;
  if ( a1 == -2147482111 )
    return 8;
  return 0;
}
DWORD s_dtDataType=0;
BOOL s_blIsInc =0;
LPBYTE GetAryElementInf (void* pAryData, LPINT pnElementCount);
int __cdecl SortCompare(float *a1, unsigned int *a2)
{
  signed int v2; // edi@1
  char v3; // zf@6
  signed int v4; // eax@12
  unsigned int v5; // edx@12
  unsigned int v6; // ecx@12
  unsigned int v7; // esi@12
  char v8; // zf@14
  int result; // eax@31

  v2 = 1;
  if ( s_dtDataType > 0x80000401 )
  {
    if ( (int)s_dtDataType == -2147482367 )
    {
      if ( *a1 < (double)*(float *)a2 )
      {
        v2 = -1;
        goto LABEL_31;
      }
      if ( *a1 == *(float *)a2 )
        goto LABEL_30;
    }
    else
    {
      if ( (int)s_dtDataType != -2147482111 )
        goto LABEL_30;
      if ( *(double *)a1 < *(double *)a2 )
      {
        v2 = -1;
        goto LABEL_31;
      }
      if ( *(double *)a1 == *(double *)a2 )
        goto LABEL_30;
    }
  }
  else
  {
    if ( (int)s_dtDataType != -2147482623 )
    {
      if ( (int)s_dtDataType == -2147483391 )
      {
        v3 = *(BYTE *)a1 == *(BYTE *)a2;
        if ( *(BYTE *)a1 < *(BYTE *)a2 )
        {
          v2 = -1;
          goto LABEL_31;
        }
      }
      else
      {
        if ((int) s_dtDataType == -2147483135 )
        {
          v3 = *(WORD *)a1 == *(WORD *)a2;
          if ( *(WORD *)a1 < *(WORD *)a2 )
          {
            v2 = -1;
            goto LABEL_31;
          }
        }
        else
        {
          if ((int) s_dtDataType != -2147482879 )
          {
LABEL_30:
            v2 = 0;
            goto LABEL_31;
          }
          v3 = *(DWORD *)a1 == *a2;
          if ( *(DWORD *)a1 < (signed int)*a2 )
          {
            v2 = -1;
            goto LABEL_31;
          }
        }
      }
LABEL_19:
      if ( !v3 )
        goto LABEL_31;
      goto LABEL_30;
    }
    v5 = *(DWORD *)a1;
    v7 = *a2;
    v4 = *((DWORD *)a1 + 1);
    v6 = a2[1];
    if ( v4 > (int)v6 )
    {
      v8 = v5 == v7;
    }
    else
    {
      if ( v4 < (int)v6 || (v8 = v5 == v7, v5 < v7) )
      {
        v2 = -1;
        goto LABEL_31;
      }
    }
    if ( v8 )
    {
      v3 = v4 == (int)v6;
      goto LABEL_19;
    }
  }
LABEL_31:
  result = v2;
  if ( !s_blIsInc )
    result = -v2;
  return result;
}

LIBAPI(void, krnln_SortAry)
{
	PMDATA_INF pArgInf = &ArgInf;
  void** v3; // esi@1
  int v4; // edi@5
  LPBYTE v5; // eax@5

  v3 = pArgInf->m_ppAryData;
  s_dtDataType = pArgInf->m_dtDataType;//*(_DWORD *)(NumOfElements + 8);
  if ( IsNumDataType(s_dtDataType) )
  {
    if (pArgInf[1].m_dtDataType !=_SDT_NULL )
      s_blIsInc = pArgInf[1].m_bool;
    else
      s_blIsInc = 1;
    v4 = GetSysDataTypeDataSize((int)s_dtDataType);
    krnl_MACopyConstAry(v4, v3);
	INT NumOfElements =0;
    v5 = GetAryElementInf(*v3, &NumOfElements);
    qsort(v5, NumOfElements, v4, (int (__cdecl *)(const void *, const void *))SortCompare);
  }
}
