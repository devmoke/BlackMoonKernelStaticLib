#include "stdafx.h"
#include "MyMemFile.h"

PFILEELEMENT pFileList = NULL;
extern "C" PDESTROY HFileDestroyAddress;

CRITICAL_SECTION csFileMan;
BOOL bIsCSinit = FALSE;

void enterfm()
{
	if (!bIsCSinit)
	{
		InitializeCriticalSection(&csFileMan);
		bIsCSinit = TRUE;
	}
	EnterCriticalSection(&csFileMan);
}

void leavefm()
{
	if (bIsCSinit)
		LeaveCriticalSection(&csFileMan);
}

void ResetFileIO()
{
	enterfm();
	PFILEELEMENT pObjFile = pFileList;
	pFileList = NULL;
	HFileDestroyAddress = NULL;

	while(pObjFile)
	{

		if(pObjFile->FileHandle)
		{
			if(pObjFile->nType ==1 || pObjFile->nType ==3)
				CloseHandle((HANDLE)pObjFile->FileHandle);
			else if(pObjFile->nType ==2)
				delete (CMyMemFile*)pObjFile->FileHandle;
		}

		PFILEELEMENT pPreFile = pObjFile;
		pObjFile = (PFILEELEMENT)pObjFile->pLast;
		memset(pPreFile,0,sizeof(FILEELEMENT));
		delete pPreFile;
	}
	leavefm();
}
void CloseEfile(PFILEELEMENT pFile)
{
	PFILEELEMENT pObjFile = pFileList;
	PFILEELEMENT pPreFile = NULL;
	
	enterfm();
	while(pObjFile)
	{
		if(pObjFile == pFile)
		{
			if(pPreFile)
			{//�ڱ���
				pPreFile->pLast = pObjFile->pLast;
			}
			else
			{ //����
				pFileList = (PFILEELEMENT)pObjFile->pLast;
				if(pFileList==NULL)
					HFileDestroyAddress = NULL;

			}
			if(pObjFile->FileHandle)
			{
				if(pObjFile->nType ==1 || pObjFile->nType == 3)
					CloseHandle((HANDLE)pObjFile->FileHandle);
				else if(pObjFile->nType ==2)
					delete (CMyMemFile*)pObjFile->FileHandle;
			}
			memset(pObjFile,0,sizeof(FILEELEMENT));
			delete pObjFile;
			break;

		}
		pPreFile = pObjFile;
		pObjFile = (PFILEELEMENT)pObjFile->pLast;
	}
	leavefm();
}


void AddFileMangerList(PFILEELEMENT pFile)
{
	enterfm();
	if(pFileList==NULL)//�׸�
		HFileDestroyAddress = (PDESTROY)ResetFileIO;
	pFile->pLast = pFileList;
	pFileList = pFile;
	leavefm();
}