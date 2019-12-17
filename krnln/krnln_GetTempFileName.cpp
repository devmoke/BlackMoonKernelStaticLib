#include "stdafx.h"
#include <SHLWAPI.h>
#include "Myfunctions.h"
#pragma comment(lib,"SHLWAPI.lib") 
//���̲��� - ȡ��ʱ�ļ���
/*
    ���ø�ʽ�� ���ı��͡� ȡ��ʱ�ļ��� �����ı��� Ŀ¼���ݣ� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�GetTempFileName
    ����һ����ָ��Ŀ¼��ȷ�������ڵ� .TMP ȫ·���ļ����ơ�������Ϊ�������
    ����<1>������Ϊ��Ŀ¼����������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ����ʡ�Ա�������Ĭ�Ͻ�ʹ��ϵͳ�ı�׼��ʱĿ¼��
*/
LIBAPI(char*, krnln_GetTempFileName)
{
	char DirName [MAX_PATH];
	if(ArgInf.m_dtDataType == _SDT_NULL)
	{
		if(GetTempPath(MAX_PATH,DirName)==FALSE)
			DirName[0]=0;
	}
	else
		strcpy(DirName,ArgInf.m_pText);

	char* pText = NULL;
	char TempFileName [MAX_PATH];
	INT nLen = mystrlen(DirName);
	if(DirName[nLen-1]!='\\')
		DirName[nLen]='\\';
	do{
		wsprintf(TempFileName, "%s%x.tmp", DirName,GetTickCount());
	}while(PathFileExists(TempFileName));


//	if(GetTempFileName(DirName,"14f",0,TempFileName))
//	{
		nLen = mystrlen(TempFileName);
		pText = (char*)E_MAlloc_Nzero(nLen+1);
		strcpy(pText,TempFileName);
//	}
	return pText;
}
