#include "stdafx.h"
#include "Myfunctions.h"

BOOL BlackMoonDeleteDir(LPSTR strDirName)
{
	
	char szName [MAX_PATH];
	char szFile [MAX_PATH];
	strcpy(szName,strDirName);
	INT nLen = mystrlen(szName);
	if(szName[nLen-1] != '\\')
		strcat(szName,"\\");

	strcpy(szFile,szName);//��\Ϊ��β�ĵ�ǰ����Ŀ¼
	strcat(szName,"*");//ͨ���Ŀ¼

	WIN32_FIND_DATA FindFileData;
	HANDLE hFile = FindFirstFile(szName,&FindFileData);
	if(hFile==NULL || hFile == INVALID_HANDLE_VALUE) 
		return FALSE;
	BOOL bOK = TRUE;
	do{
		if(strcmp(FindFileData.cFileName,".")!=0 &&
			strcmp(FindFileData.cFileName,"..")!=0)
		{

			strcpy(szName,szFile);
			strcat(szName,FindFileData.cFileName);//��������Ŀ���ļ���Ŀ¼��
			if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)//ΪĿ¼
			{
				bOK = BlackMoonDeleteDir(szName);//�ݹ�ѭ��
				if(bOK)
					bOK = RemoveDirectory(szName);//ɾ����Ŀ¼
				
			}else
				bOK = DeleteFile(szName);//ɾ���ļ�
		}
		if(bOK == FALSE)
			break;
	}while(FindNextFile(hFile,&FindFileData));

	FindClose(hFile); //�رվ�� 
	return bOK;

}

//���̲��� - ɾ��Ŀ¼
/*
    ���ø�ʽ�� ���߼��͡� ɾ��Ŀ¼ ���ı��� ��ɾ����Ŀ¼���ƣ� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�RmDir
    ɾ��һ�����ڵ�Ŀ¼�����е�������Ŀ¼�������ļ�������ؽ���ʹ�ñ�����ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ����ɾ����Ŀ¼���ơ�������Ϊ���ı��ͣ�text��������Ŀ¼Ӧʵ�ʴ��ڣ����Ŀ¼�д����ļ�����Ŀ¼������һ��ɾ�������ʹ�ñ�������ǧ�����ء�
*/
LIBAPI(BOOL, krnln_RmDir)
{
	if(ArgInf.m_pText == NULL)
		return FALSE;
	int nLen = mystrlen(ArgInf.m_pText);
	if(nLen==0)//��ֹɾ����ǰĿ¼�ĸ�Ŀ¼"\*"
		return FALSE;
	if(nLen ==1 && ArgInf.m_pText[0]=='\\')//��ֹɾ����ǰĿ¼�ĸ�Ŀ¼"\*"
		return FALSE;
	BOOL bOK = BlackMoonDeleteDir(ArgInf.m_pText);
	if(bOK)
		bOK = RemoveDirectory(ArgInf.m_pText);//ɾ����Ŀ¼
	return bOK;
}
