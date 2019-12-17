#include "stdafx.h"
#include "MyMemFile.h"
#include "Myfunctions.h"
//�ļ���д - �Ƿ����ļ�β
/*
    ���ø�ʽ�� ���߼��͡� �Ƿ����ļ�β �������� �ļ��ţ����߼��� �Ƿ�Ϊ�ж��ı��Ѷ���ݣ� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�feof
    ���ָ�������ļ��Ķ�дλ���Ѿ����ڸ��ļ����ݵ�β�����򷵻��棬���򷵻ؼ١�������Ϊ�������
    ����<1>������Ϊ���ļ��š�������Ϊ�������ͣ�int����������ֵָ�����������ļ��ţ����ļ��ű����ɡ����ļ������������ء�
    ����<2>������Ϊ���Ƿ�Ϊ�ж��ı��Ѷ��ꡱ������Ϊ���߼��ͣ�bool���������Ա�ʡ�ԡ����������ֵΪ�������һ����������ֽ�Ϊ�ֽ�ֵ 0 �� 26 ���ı���ֹ��Ƿ����ߵ�ǰ��дλ���Ѵ��ڸ��ļ����ݵ�β������������档�����������ʡ�Ի�Ϊ�٣��������д˼�顣

*/
LIBAPI(BOOL, krnln_feof)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return TRUE;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return TRUE;
	PMDATA_INF pArgInf = &ArgInf;
	INT nRet = TRUE;

	if(pFile->nType ==1 || pFile->nType == 3)//�����ļ� �����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwHi;
		UINT nLen = ::GetFileSize(hFile,&dwHi);
		UINT nLoc = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
		if(nLoc != HFILE_ERROR)
		{
			if(nLoc < nLen)
			{
				nRet = FALSE;
				
				if(pArgInf[1].m_dtDataType != _SDT_NULL && pArgInf[1].m_bool)
				{
					INT nData;
					LPSTR pStr = (LPSTR)&nData;
					DWORD dwByteTop;
					BOOL bRet = ReadFile(hFile, pStr, sizeof(BYTE), &dwByteTop, 0);
					SetFilePointer(hFile,nLoc,NULL,FILE_BEGIN);
					if (pFile->nType==3) //�����ļ�
						E_RC4_Calc(nLoc, (unsigned char*)pStr, sizeof(BYTE), pFile->strTable, pFile->nCryptStart, pFile->strMD5);

					if(bRet && (*pStr==0 || *pStr == 26))
						nRet = TRUE;
				}
			}
		}
	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;
		UINT nLen = pMemFile->GetFileSize();
		UINT nLoc = pMemFile->GetPosition();
		if(nLoc < nLen)
		{
			nRet = FALSE;
			
			if(pArgInf[1].m_dtDataType != _SDT_NULL && pArgInf[1].m_bool)
			{
				INT nData;
				LPSTR pStr = (LPSTR)&nData;
				BOOL bRet = pMemFile->Read (pStr, sizeof(BYTE));
				pMemFile->Seek(nLoc,CMyMemFile::SeekPosition::begin);
				if(bRet && (*pStr==0 || *pStr == 26))
					nRet = TRUE;
			}
		}
	}
	return nRet;
}
