#include "StdAfx.h"
#include "Myfunctions.h"

// ʹ��ָ���ı����ݽ����׳�����ʹ�õ��ı����ݡ�
//   nTextLen����ָ���ı����ֵĳ��ȣ������������㣩��
// ���Ϊ-1����ȡps��ȫ�����ȡ�
char* CloneTextData (char* ps, INT nTextLen)
{
	if (nTextLen <= 0)
		return NULL;
	
	char* pd = (char*)E_MAlloc_Nzero ((DWORD)(nTextLen + 1));
	memcpy (pd, ps, nTextLen);
	pd [nTextLen] = '\0';
	return pd;
}
// ʹ��ָ���ı����ݽ����׳�����ʹ�õ��ı����ݡ�
char* CloneTextData (char* ps)
{
    if (ps == NULL || *ps == '\0')
        return NULL;

    INT nTextLen = mystrlen (ps);
    char* pd = (char*)E_MAlloc_Nzero ((DWORD)(nTextLen + 1));
    memcpy (pd, ps, nTextLen);
    pd [nTextLen] = '\0';
    return pd;
}