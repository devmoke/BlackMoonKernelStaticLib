#include "stdafx.h"
#include "Myfunctions.h"

extern "C" {

	char*  _cdecl E_FindFile (LPCSTR strFile,UINT nAttrib,BOOL bIsMissing,HANDLE* phFile){
//12�ź���,EAXΪ 0
		HANDLE hFile = *phFile;

		WIN32_FIND_DATA FindFileData;
		BOOL bFind = FALSE;
	//	nAttrib &= 55;//���������
		if(strFile != NULL && mystrlen(strFile)>0)//��һ�β���
		{
			
			
			if(hFile && hFile != INVALID_HANDLE_VALUE) //�ر��ϴξɵľ�� 
				FindClose(hFile); 

				
			
			hFile = FindFirstFile(strFile,&FindFileData);
			*phFile = hFile;
			if(hFile ==INVALID_HANDLE_VALUE)
				return NULL;
					
			

			if(bIsMissing)
			{
			//char ErrorString [255];
	  		//wsprintf(ErrorString, "(0x%Xh) (0x%Xh)", FindFileData.dwFileAttributes,(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
			//MessageBox(0, ErrorString, FindFileData.cFileName, MB_OK);

				if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)//������Ŀ¼����
					bFind = TRUE;

			}else {

				if ((FindFileData.dwFileAttributes & nAttrib) != 0)//��������
					bFind = TRUE;
			}

		}

		if(hFile==NULL || hFile == INVALID_HANDLE_VALUE) return NULL;

		if(bFind==FALSE)
		{
			if(bIsMissing)
			{
				while(FindNextFile(hFile,&FindFileData))
				{
					if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)//������Ŀ¼����
					{
						bFind = TRUE;
						break;
					}
					
				}				
			}else {

				while(FindNextFile(hFile,&FindFileData))
				{
					if((FindFileData.dwFileAttributes & nAttrib) != 0)//��������
					{
						bFind = TRUE;
						break;
					}
					
				}				
				
			}
		}

		if(bFind)
		{
			//	MessageBox(0, FindFileData.cFileName, "FILE", MB_OK);
			INT nLen = mystrlen(FindFileData.cFileName);
			char* str = (char*)E_MAlloc_Nzero(nLen+1);
			strcpy(str,FindFileData.cFileName);
			return str;
		}
		return NULL;

	}
	void  _cdecl E_CloseFindFile (HANDLE hFile){
		//12�ź���,EAXΪ 1
		//char t[12];
		//itoa((int)hFile,t,16);

		//MessageBox(NULL,t,"file2",MB_OK);
		//HANDLE hFile = *phFile;
		if(hFile==NULL || hFile == INVALID_HANDLE_VALUE) return ;
		
		FindClose(hFile); //�ر��ϴξɵľ�� 
		//*phFile = NULL;
		
	}

}