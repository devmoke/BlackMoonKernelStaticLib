#include "stdafx.h"
#include "MyMemFile.h"
#include "Myfunctions.h"
//�ļ���д - ɾ������
/*
    ���ø�ʽ�� ���߼��͡� ɾ������ �������� �ļ��ţ������� ��ɾ�����ݵ��ֽ����� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�RemoveData
    �������������ļ��е�ǰ��дλ�ô�ɾ��һ���ֽ����ݣ��ļ����������˳��ǰ�ơ����ļ�����ʱ�������"#��д"��"#�Ķ�"Ȩ�ޡ��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ���ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
    ����<2>������Ϊ����ɾ�����ݵ��ֽ�����������Ϊ�������ͣ�int������
*/
LIBAPI(BOOL, krnln_RemoveData)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return NULL;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return NULL;
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[1].m_int<=0)
		return FALSE;

	BOOL bRet = FALSE;

	if(pFile->nType ==1)//�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
		if(orgLoc == HFILE_ERROR)
			return FALSE;


		bRet = TRUE;
		DWORD dwNumOfByteRead;
		INT nBkLen = GetFileSize(hFile,NULL) - orgLoc - pArgInf[1].m_int;
		LPBYTE pBkData = NULL;
		if(nBkLen >0)//�в�������
		{
			pBkData = new BYTE[nBkLen];
			INT nLen = pArgInf[1].m_int;
			SetFilePointer(hFile,nLen,NULL,FILE_CURRENT);//���Ƶ�
			if( ReadFile(hFile, pBkData, nBkLen, &dwNumOfByteRead, 0)==FALSE)
			{
				delete[] pBkData;
				return FALSE;
			}
			SetFilePointer(hFile,orgLoc,NULL,FILE_BEGIN);//�ָ�ԭλ��
			if(WriteFile(hFile,pBkData,nBkLen,&dwNumOfByteRead,NULL))
			{
//				if(FlushFileBuffers(hFile)==FALSE)
//					bRet = FALSE;
			}
			else
				bRet = FALSE;
			delete[] pBkData;
		}
		if(bRet)
			SetEndOfFile(hFile);

	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;

		INT orgLoc = pMemFile->GetPosition();

		INT nBkLen = pMemFile->GetFileSize() - orgLoc - pArgInf[1].m_int;
		LPBYTE pBkData = NULL;

		bRet = TRUE;
		if(nBkLen >0)//�в�������
		{
			pMemFile->Seek(pArgInf[1].m_int,CMyMemFile::SeekPosition::current);
			pBkData = new BYTE[nBkLen];
			pMemFile->Read(pBkData,nBkLen);
			pMemFile->Seek(orgLoc,CMyMemFile::SeekPosition::begin);//�ָ�
			pMemFile->Write(pBkData, nBkLen);
			orgLoc = pMemFile->GetPosition();
			delete[] pBkData;
		}
		pMemFile->SetLength(orgLoc);
	}else if(pFile->nType ==3)//�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
		if(orgLoc == HFILE_ERROR)
			return FALSE;
		
		bRet = TRUE;
		DWORD dwNumOfByteRead;
		INT nBkLen = GetFileSize(hFile,NULL) - orgLoc - pArgInf[1].m_int;
		INT nPos;
		LPBYTE pBkData = NULL;
		if(nBkLen >0)//�в�������
		{
			pBkData = new BYTE[nBkLen];
			INT nLen = pArgInf[1].m_int;
			SetFilePointer(hFile,nLen,NULL,FILE_CURRENT);//���Ƶ�
			nPos = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
			if( ReadFile(hFile, pBkData, nBkLen, &dwNumOfByteRead, 0)==FALSE)
			{
				delete[] pBkData;
				return FALSE;
			}
			nBkLen = dwNumOfByteRead;
			E_RC4_Calc(nPos, (unsigned char*)pBkData, nBkLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);

			SetFilePointer(hFile,orgLoc,NULL,FILE_BEGIN);//�ָ�ԭλ��
			nPos = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
			E_RC4_Calc(nPos, (unsigned char*)pBkData, nBkLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
			if(!WriteFile(hFile,pBkData,nBkLen,&dwNumOfByteRead,NULL))
				bRet = FALSE;

			delete[] pBkData;
		}
		if(bRet)
			SetEndOfFile(hFile);
	}
	return bRet;
}
