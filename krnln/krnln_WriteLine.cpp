#include "stdafx.h"
#include "MyMemFile.h"
#include "Myfunctions.h"

//�ļ���д - д�ı���
/*
    ���ø�ʽ�� ���߼��͡� д�ı��� �������� ��д���ı����ļ��ţ�ͨ���� ��д�����ı���... �� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�WriteLine
    ����������д��һ�л�����ı����ݵ��ļ��е�ǰ��дλ�ô���ÿ�е�β�������Զ����ϻس������з����ɹ������棬ʧ�ܷ��ؼ١�������Ϊ���������������������һ���������Ա��ظ���ӡ�
    ����<1>������Ϊ����д���ı����ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
    ����<2>������Ϊ����д�����ı���������Ϊ��ͨ���ͣ�all����������ֵ�����Ϊ�ı��������ݣ����Զ�����ת��������޷�ת��������������Ϊ�ֽڼ����ӳ���ָ�롢����û��Զ����������ͣ�����д�������ݡ�
*/


LIBAPI(BOOL, krnln_WriteLine)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return NULL;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return NULL;
	PMDATA_INF pArgInf = &ArgInf;

	BOOL bRet = FALSE;

	if(pFile->nType ==1)//�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		bRet = TRUE;
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
				{
					WriteFile(hFile,"\r\n",2,&dwNumOfByteRead,NULL);
//					FlushFileBuffers(hFile);
					continue;
				}
				bNeedFree = TRUE;
			}

			INT nLen = mystrlen(pData);
			if(nLen>0)
			{
				if(WriteFile(hFile,pData,nLen,&dwNumOfByteRead,NULL))
				{
					WriteFile(hFile,"\r\n",2,&dwNumOfByteRead,NULL);
					//if(FlushFileBuffers(hFile)==FALSE)
						//bRet = FALSE;
				}
				else
					bRet = FALSE;
			}

			if(bNeedFree)
				free(pData);

			if(bRet == FALSE)
				break;
		}
	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;
		bRet = TRUE;
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

			INT nLen = mystrlen(pData);
			if(nLen>0)
				pMemFile->Write(pData,nLen);
			pMemFile->Write("\r\n",2);

			if(bNeedFree)
				free(pData);
		}
	}else if(pFile->nType ==3) //�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		unsigned char pszRN[2] = {2};
		int nPos = 0;
		bRet = TRUE;
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
				{
					nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
					pszRN[0] = '\r';
					pszRN[1] = '\n';
					E_RC4_Calc(nPos, pszRN, 2, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
					WriteFile(hFile, pszRN, 2, &dwNumOfByteRead, NULL);
					continue;
				}
				bNeedFree = TRUE;
			}
			
			INT nLen = mystrlen(pData);
			if(nLen>0)
			{
				nPos = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
				E_RC4_Calc(nPos, (unsigned char*)pData, nLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
				if(WriteFile(hFile, (unsigned char*)pData, nLen, &dwNumOfByteRead, NULL))
				{
					nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
					pszRN[0] = '\r';
					pszRN[1] = '\n';
					E_RC4_Calc(nPos, pszRN, 2, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
					WriteFile(hFile, pszRN, 2, &dwNumOfByteRead, NULL);
				}
				else
					bRet = FALSE;
			}
			
			if(bNeedFree)
				free(pData);
			
			if(bRet == FALSE)
				break;
		}
	}
	return bRet;
}
