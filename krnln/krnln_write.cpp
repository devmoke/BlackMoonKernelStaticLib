#include "stdafx.h"
#include "MyMemFile.h"
#include "Myfunctions.h"

//�ļ���д - д������
/*
    ���ø�ʽ�� ���߼��͡� д������ �������� ��д�����ݵ��ļ��ţ�ͨ��������/������ ��д�������ݣ�... �� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�write
    ������Ӧ���롰���롱�������ʹ�ã�����д��һϵ�б�������������ĸ�ʽ���ݵ��ļ��е�ǰ��дλ�ô����ɹ������棬ʧ�ܷ��ؼ١�
������������������ݵ�д����ʽΪ��
  1����ֵ�͡��߼��͡�����ʱ���͡��ӳ���ָ���ͣ� Ϊ������Ӧ��ʵ�����ݣ�
  2���ı��ͣ�   Ϊ�ı����� + �ֽ� 0 ��
  3���ֽڼ��ͣ� Ϊ�ֽڼ����ݳ��ȣ������� + �ֽڼ�ʵ�����ݣ�
  4�����ϸ����������͵����������ݣ� Ϊ��������������ݸ�ʽ��˳�����С�������Ϊ�м������������������һ���������Ա��ظ���ӡ�
    ����<1>������Ϊ����д�����ݵ��ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
    ����<2>������Ϊ����д�������ݡ�������Ϊ��ͨ���ͣ�all�������ṩ��������ʱ����ͬʱ�ṩ�������������ݡ������д�����ݵ���������Ϊ�û��Զ����ⶨ���������ͣ������ʧ�ܡ�
*/
LIBAPI(BOOL, krnln_write)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return NULL;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return NULL;
	PMDATA_INF pArgInf = &ArgInf;

	BOOL bRet = FALSE;

	if(pFile->nType ==1 || pFile->nType == 3)//�����ļ� �����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		bRet = TRUE;
		INT nPos;
		for(INT i=1;i < nArgCount;i++)
		{
			if(bRet == FALSE)
				break;
			if((pArgInf[i].m_dtDataType & DT_IS_ARY) == DT_IS_ARY)//������
			{
				pArgInf[i].m_dtDataType &=~DT_IS_ARY; //ȥ�������־
				if(pArgInf[i].m_dtDataType==SDT_TEXT)
				{
					DWORD dwSize;
					LPSTR* pAryData = (LPSTR*)GetAryElementInf(pArgInf[i].m_pAryData,dwSize);
					INT nData = 0;
					for(UINT n=0;n<dwSize;n++)
					{
						INT nLen;
						void* pData;
						if(pAryData[n]==NULL)
						{
							nLen = 1;
							pData = &nData;
						}
						else
						{
							nLen = mystrlen(pAryData[n])+1;
							pData = pAryData[n];
						}
						void *pTMP = NULL;
						if (pFile->nType == 3) //�����ļ�
						{
							pTMP = malloc(nLen);
							memcpy(pTMP, pData, nLen);
							nPos = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
							E_RC4_Calc(nPos, (unsigned char*)pTMP, nLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
							pData = pTMP;
						}
						if(WriteFile(hFile,pData,nLen,&dwNumOfByteRead,NULL))
						{
//							if(FlushFileBuffers(hFile)==FALSE)
//								bRet = FALSE;
						}
						else
							bRet = FALSE;
						
						if (pTMP)
						{
							free(pTMP);
							pTMP = NULL;
						}

						if(bRet == FALSE)
							break;
					}


				}else if(pArgInf[i].m_dtDataType==SDT_BIN)
				{
					DWORD dwSize;
					LPINT* pAryData = (LPINT*)GetAryElementInf(pArgInf[i].m_pAryData,dwSize);
					INT nData = 0;
					for(UINT n=0;n<dwSize;n++)
					{
						void* pData;
						INT nLen;
						if(pAryData[n]==NULL)
						{
							pData = &nData;
							nLen = sizeof(INT);
						}
						else
						{
							LPINT p = pAryData[n];
							nLen = p[1]+sizeof(INT);
							p++;
							pData = p;
						}
						void *pTMP = NULL;
						if (pFile->nType == 3) //�����ļ�
						{
							pTMP = malloc(nLen);
							memcpy(pTMP, pData, nLen);
							nPos = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
							E_RC4_Calc(nPos, (unsigned char*)pTMP, nLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
							pData = pTMP;
						}
						if(WriteFile(hFile,pData,nLen,&dwNumOfByteRead,NULL))
						{
//							if(FlushFileBuffers(hFile)==FALSE)
//								bRet = FALSE;
						}
						else
							bRet = FALSE;

						if (pTMP)
						{
							free(pTMP);
							pTMP = NULL;
						}

						if(bRet == FALSE)
							break;
					}

				}else{

					INT nLen = GetSysDataTypeDataSize(pArgInf[i].m_dtDataType);
					if(nLen==0)//��֧�ֵ���������
						continue;
					DWORD dwSize;
					void* pData = GetAryElementInf(pArgInf[i].m_pAryData,dwSize);
					nLen *= dwSize;

					void *pTMP = NULL;
					if (pFile->nType == 3) //�����ļ�
					{
						pTMP = malloc(nLen);
						memcpy(pTMP, pData, nLen);
						nPos = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
						E_RC4_Calc(nPos, (unsigned char*)pTMP, nLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
						pData = pTMP;
					}
					if(WriteFile(hFile,pData,nLen,&dwNumOfByteRead,NULL))
					{
//						if(FlushFileBuffers(hFile)==FALSE)
//							bRet = FALSE;
					}
					else
						bRet = FALSE;

					if (pTMP)
					{
						free(pTMP);
						pTMP = NULL;
					}

					if(bRet == FALSE)
						break;
				}
			}
			else
			{//������
				INT nLen;
				void* pData;
				INT nData = 0;
				if(pArgInf[i].m_dtDataType==SDT_TEXT)
				{
					if(pArgInf[i].m_pText==NULL)
					{
						nLen = 1;
						pData = &nData;

					}
					else
					{
						nLen = mystrlen(pArgInf[i].m_pText)+1;
						pData = pArgInf[i].m_pText;
					}

				}else if(pArgInf[i].m_dtDataType==SDT_BIN)
				{
					if(pArgInf[i].m_pBin==NULL)
					{
						nLen = sizeof(INT);
						pData = &nData;
					}
					else
					{
						LPINT p = (LPINT)pArgInf[i].m_pBin;
						nLen = p[1]+sizeof(INT);
						p++;
						pData = p;
					}

				}else{

					nLen = GetSysDataTypeDataSize(pArgInf[i].m_dtDataType);
					if(nLen==0)//��֧�ֵ���������
						continue;
					pData = &pArgInf[i].m_int;
				}
				void *pTMP = NULL;
				if (pFile->nType == 3) //�����ļ�
				{
					pTMP = malloc(nLen);
					memcpy(pTMP, pData, nLen);
					nPos = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
					E_RC4_Calc(nPos, (unsigned char*)pTMP, nLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
					pData = pTMP;
				}
				if(WriteFile(hFile,pData,nLen,&dwNumOfByteRead,NULL))
				{
//					if(FlushFileBuffers(hFile)==FALSE)
//						bRet = FALSE;
				}
				else
					bRet = FALSE;

				if (pTMP)
				{
					free(pTMP);
					pTMP = NULL;
				}

				if(bRet == FALSE)
					break;
			}
		}
		

	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;
		bRet = TRUE;
		for(INT i=1;i < nArgCount;i++)
		{

			if((pArgInf[i].m_dtDataType & DT_IS_ARY) == DT_IS_ARY)//������
			{
				pArgInf[i].m_dtDataType &=~DT_IS_ARY; //ȥ�������־
				if(pArgInf[i].m_dtDataType==SDT_TEXT)
				{
					DWORD dwSize;
					LPSTR* pAryData = (LPSTR*)GetAryElementInf(pArgInf[i].m_pAryData,dwSize);
					INT nData = 0;
					for(UINT n=0;n<dwSize;n++)
					{
						INT nLen;
						void* pData;
						if(pAryData[n]==NULL)
						{
							nLen = 1;
							pData = &nData;
						}
						else
						{
							nLen = mystrlen(pAryData[n])+1;
							pData = pAryData[n];
						}
						pMemFile->Write(pData,nLen);

					}


				}else if(pArgInf[i].m_dtDataType==SDT_BIN)
				{
					DWORD dwSize;
					LPINT* pAryData = (LPINT*)GetAryElementInf(pArgInf[i].m_pAryData,dwSize);
					INT nData = 0;
					for(UINT n=0;n<dwSize;n++)
					{
						void* pData;
						INT nLen;
						if(pAryData[n]==NULL)
						{
							pData = &nData;
							nLen = sizeof(INT);
						}
						else
						{
							LPINT p = pAryData[n];
							nLen = p[1]+sizeof(INT);
							p++;
							pData = p;
						}
						pMemFile->Write(pData,nLen);

					}

				}else{

					INT nLen = GetSysDataTypeDataSize(pArgInf[i].m_dtDataType);
					if(nLen==0)//��֧�ֵ���������
						continue;
					DWORD dwSize;
					void* pData = GetAryElementInf(pArgInf[i].m_pAryData,dwSize);
					nLen *= dwSize;
					pMemFile->Write(pData,nLen);

				}
			}
			else
			{//������
				INT nLen;
				void* pData;
				INT nData = 0;
				if(pArgInf[i].m_dtDataType==SDT_TEXT)
				{
					if(pArgInf[i].m_pText==NULL)
					{
						nLen = 1;
						pData = &nData;

					}
					else
					{
						nLen = mystrlen(pArgInf[i].m_pText)+1;
						pData = pArgInf[i].m_pText;
					}

				}else if(pArgInf[i].m_dtDataType==SDT_BIN)
				{
					if(pArgInf[i].m_pBin==NULL)
					{
						nLen = sizeof(INT);
						pData = &nData;
					}
					else
					{
						LPINT p = (LPINT)pArgInf[i].m_pBin;
						nLen = p[1]+sizeof(INT);
						p++;
						pData = p;
					}

				}else{

					nLen = GetSysDataTypeDataSize(pArgInf[i].m_dtDataType);
					if(nLen==0)//��֧�ֵ���������
						continue;
					pData = &pArgInf[i].m_int;
				}

				pMemFile->Write(pData,nLen);

			}
		}


	}
	return bRet;
}
