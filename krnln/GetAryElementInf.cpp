#include "stdafx.h"

void* GetAryElementInf(void* pAryData ,DWORD& AryElementCount)
{
    LPINT pnData;
    INT nArys;
    UINT nElementCount;
    
    pnData = (LPINT)pAryData;
    
    nArys=*pnData; //ȡ��ά����
    pnData +=1;

     // �����Ա��Ŀ��
    nElementCount = 1;
    while (nArys > 0)
	{
        nElementCount *= pnData[0];
        pnData ++;
        nArys--;
    }

    AryElementCount = nElementCount;
    return pnData;
}