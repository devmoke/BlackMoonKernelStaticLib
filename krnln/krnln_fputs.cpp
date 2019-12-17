#include "stdafx.h"
#include <stdio.h>
#include "Myfunctions.h"
//����̨���� - ��׼���
/*
    ���ø�ʽ�� ���޷���ֵ�� ��׼��� ���������� �������ݣ�ͨ���� ��������ݣ�... �� - ϵͳ����֧�ֿ�->����̨����
    Ӣ�����ƣ�fputs
    �ڱ�׼����豸���׼�����豸�����ָ�������ݣ�ע�Ȿ����ֻ���ڿ���̨������ʹ�á�������Ϊ���������������������һ���������Ա��ظ���ӡ�
    ����<1>������Ϊ��������򡱣�����Ϊ�������ͣ�int���������Ա�ʡ�ԡ��������ṩ��������������豸������Ϊ���³���ֵ֮һ�� 1��#��׼����豸�� 2��#��׼�����豸�����ʡ�Ա�������Ĭ��Ϊ��#��׼����豸����
    ����<2>������Ϊ����������ݡ�������Ϊ��ͨ���ͣ�all������������ֻ��Ϊ�ı�����ֵ���߼�ֵ������ʱ�䡣�������Ϊ�ı��Ұ������У����ڸ���֮���ûس��� (�����ַ� (13)��)�����з� (�����ַ� (10)��) ��س����з������ (�������ַ� (13) + �ַ� (10)��) ���ָ���
*/
LIBAPI(void, krnln_fputs)
{
	PMDATA_INF pArgInf = &ArgInf;
	
	DWORD dwSdt = STD_OUTPUT_HANDLE;
	if(pArgInf[0].m_dtDataType != _SDT_NULL && pArgInf[0].m_int==2)
		dwSdt = STD_ERROR_HANDLE;
	HANDLE hCon = GetStdHandle(dwSdt);
	if(hCon==NULL)
			return;
/*	 _iobuf* hCon = stdout;
	if(pArgInf[0].m_dtDataType != _SDT_NULL && pArgInf[0].m_int==2)
		hCon = stderr;*/

	for(INT i=1;i < nArgCount;i++)
	{
		LPSTR pData;
		BOOL bNeedFree = FALSE;
		if(pArgInf[i].m_dtDataType == SDT_TEXT)
			pData = pArgInf[i].m_pText;
		else
		{
			pData = SDataToStr(&pArgInf[i]);
			if(pData == NULL)
				continue;
			bNeedFree = TRUE;
		}
		
		UINT nLen = mystrlen(pData);
		//char text[50];
		//itoa(nLen,text,10);
		//MessageBox(NULL,text,NULL,MB_OK);
		if(nLen>0)
		{
			LPSTR pStr = pData;
			while(nLen>0){
				DWORD dwSize=0;
				UINT nSize = 1024;
				if(nLen<1024)
					nSize = nLen;
				WriteFile(hCon,pStr,nSize,&dwSize,NULL);
				nLen-=dwSize;
				pStr+=dwSize;
			}
			
			//WriteConsole(hCon,pData,nLen,&dwSize,NULL);
			

			//fprintf(hCon, "%s",pData); 
		}
		
		if(bNeedFree)
			free(pData);

	}
	

}
