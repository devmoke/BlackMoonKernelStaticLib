#include "stdafx.h"
#include "midi.h"
#include "Myfunctions.h"

struct MIDIFILEDATAINFO
{
	LPBYTE pData;
    DWORD	dwSize;			
};

extern "C" PDESTROY DestroyMidiPlayer;

CMIDI* pMidiPlayer = NULL;
MIDIFILEDATAINFO* pMidiFileData = NULL;
INT nLoopNum;
INT nPlayWaitTime;
INT nMidiArrySize = 0;
HANDLE	hLoopPlayEvent = NULL;
HANDLE  hMidiPlayerThrd = NULL; 
void CloseMidiPlayer()
{
	DestroyMidiPlayer = NULL;
	if(hMidiPlayerThrd)
	{
		TerminateThread(hMidiPlayerThrd,0);//ǿ����ֹ�߳�
		::CloseHandle(hMidiPlayerThrd);
		hMidiPlayerThrd = NULL;
	}

	if(hLoopPlayEvent)
	{
		SetEvent(hLoopPlayEvent);
		::CloseHandle(hLoopPlayEvent);
		hLoopPlayEvent = NULL;
	}
	

	if(pMidiPlayer)
	{
		delete pMidiPlayer;
		pMidiPlayer=NULL;
	}
	if(pMidiFileData)
	{
		for(INT i=0;i<nMidiArrySize;i++)
		{
			if(pMidiFileData[i].pData)
			{
				delete [] pMidiFileData[i].pData;
				pMidiFileData[i].pData=NULL;
				pMidiFileData[i].dwSize=0;
			}
		}
		delete [] pMidiFileData;
		pMidiFileData=NULL;
		nMidiArrySize = 0;
	}
	

}
BOOL IsValidMidiDataPtr(LPBYTE pData)
{
	if(pData==NULL)return FALSE;
	LPINT pInt = (LPINT)pData;


	if(pInt[1] > (3*sizeof(WORD)+2*sizeof(DWORD)))
		return TRUE;
	return FALSE;

}
BOOL IsValidMidiFileName(LPSTR pStr)
{
	if(pStr==NULL)return FALSE;
	INT nLen = mystrlen(pStr);
	if(nLen >=4)
		return TRUE;
	return FALSE;

}

INT GetMidiDataCount(PMDATA_INF pArgInf,INT nArg)
{
	INT nCount = 0;
	for(INT i=0;i<nArg;i++)
	{
		if((pArgInf[i].m_dtDataType & DT_IS_ARY) == 0)//������
		{

			if(pArgInf[i].m_dtDataType == SDT_BIN)
			{

				if(IsValidMidiDataPtr(pArgInf[i].m_pBin))
					nCount++;
				
			}else if(pArgInf[i].m_dtDataType == SDT_TEXT){

				if(IsValidMidiFileName(pArgInf[i].m_pText))
					nCount++;
			
			}
			
		}else{
			INT nDataType = pArgInf[i].m_dtDataType & ~DT_IS_ARY;

			if(nDataType == SDT_BIN)
			{
				if(pArgInf[i].m_pAryData)
				{
					DWORD dwMax = 0;
					LPBYTE* pArry = (LPBYTE*)GetAryElementInf(pArgInf[i].m_pAryData,dwMax);
					for(DWORD j=0;j<dwMax;j++)
					{
						if(IsValidMidiDataPtr(pArry[j]))
							nCount++;
					}

				}

				
			}else if(nDataType == SDT_TEXT){

				if(pArgInf[i].m_pAryData)
				{
					DWORD dwMax = 0;
					LPSTR* pArry = (LPSTR*)GetAryElementInf(pArgInf[i].m_pAryData,dwMax);
					for(DWORD j=0;j<dwMax;j++)
					{
						if(IsValidMidiFileName(pArry[j]))
							nCount++;
					}

				}
			
			}
			
			
		}
	}

	return nCount;


}

BOOL GetMidiDataFromPtr(LPBYTE pData,INT nIDX)
{
	LPINT pInt = (LPINT)pData;
	pMidiFileData[nIDX].dwSize = pInt[1];
	pMidiFileData[nIDX].pData = new BYTE[pInt[1]];
	if(pMidiFileData[nIDX].pData==NULL)return FALSE;
	pInt+=2;
	memcpy(pMidiFileData[nIDX].pData,pInt,pMidiFileData[nIDX].dwSize);
	return TRUE;

}
BOOL GetMidiDataFromFile(LPSTR pStr,INT nIDX)
{
	HANDLE hFile = CreateFile(pStr,
		GENERIC_READ,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_ARCHIVE,
		0);
	

	if(hFile != INVALID_HANDLE_VALUE)
	{

		DWORD dwNumOfByteRead;
		INT nLen = GetFileSize(hFile, &dwNumOfByteRead);
		pMidiFileData[nIDX].dwSize = nLen;
		pMidiFileData[nIDX].pData =  new BYTE[nLen];
		if(pMidiFileData[nIDX].pData)
		{
			if(ReadFile(hFile, pMidiFileData[nIDX].pData, nLen, &dwNumOfByteRead, 0))
			{
				CloseHandle(hFile);
				return TRUE;
			}
		}
		CloseHandle(hFile);
		
	}
	pMidiFileData[nIDX].dwSize = 0;
	pMidiFileData[nIDX].pData = NULL;
	return FALSE;

}

INT GetMidiDataFromArg(PMDATA_INF pArgInf,INT nArg)
{
	INT nCount = 0;
	INT nArry =0;
	for(INT i=0;i<nArg;i++)
	{
		if((pArgInf[i].m_dtDataType & DT_IS_ARY) == 0)//������
		{

			if(pArgInf[i].m_dtDataType == SDT_BIN)
			{

				if(IsValidMidiDataPtr(pArgInf[i].m_pBin))
				{
					if(GetMidiDataFromPtr(pArgInf[i].m_pBin,nArry))
						nArry++;

					nCount++;
				}
				
			}else if(pArgInf[i].m_dtDataType == SDT_TEXT){

				if(IsValidMidiFileName(pArgInf[i].m_pText))
				{
					if(GetMidiDataFromFile(pArgInf[i].m_pText,nArry))
						nArry++;
					nCount++;
				}
			
			}
			
		}else{
			INT nDataType = pArgInf[i].m_dtDataType & ~DT_IS_ARY;

			if(nDataType == SDT_BIN)
			{
				if(pArgInf[i].m_pAryData)
				{
					DWORD dwMax = 0;
					LPBYTE* pArry = (LPBYTE*)GetAryElementInf(pArgInf[i].m_pAryData,dwMax);
					for(DWORD j=0;j<dwMax;j++)
					{
						if(IsValidMidiDataPtr(pArry[j]))
						{
					
							if(GetMidiDataFromPtr(pArry[j],nArry))
								nArry++;
							nCount++;
						}
					}

				}

				
			}else if(nDataType == SDT_TEXT){

				if(pArgInf[i].m_pAryData)
				{
					DWORD dwMax = 0;
					LPSTR* pArry = (LPSTR*)GetAryElementInf(pArgInf[i].m_pAryData,dwMax);
					for(DWORD j=0;j<dwMax;j++)
					{
						if(IsValidMidiFileName(pArry[j]))
						{					
							if(GetMidiDataFromFile(pArry[j],nArry))
								nArry++;
							nCount++;
						}
					}

				}
			
			}
			
			
		}
	}

	return nArry;


}

DWORD WINAPI  PlayMidiManager(PVOID pParam)
{
	/*
INT nLoopNum;
INT nPlayWaitTime;
INT nMidiArrySize = 0;
HANDLE	hLoopPlayEvent = NULL;
HANDLE  hMidiPlayerThrd = NULL; 
*/
	for(INT n=0;n<nLoopNum;n++)
	{
		for(INT i=0;i<nMidiArrySize;i++)
		{
			if(pMidiFileData[i].pData)
			{
				if(pMidiPlayer)
					delete  pMidiPlayer;
				pMidiPlayer = new CMIDI();
				pMidiPlayer->m_hhLoopPlayEvent = hLoopPlayEvent; 
				BOOL bRet = pMidiPlayer->Create(pMidiFileData[i].pData,pMidiFileData[i].dwSize);
				if(bRet)
				{
					
					bRet = pMidiPlayer->Play();
					if(bRet)
					{
						ResetEvent(hLoopPlayEvent);
						WaitForSingleObject(hLoopPlayEvent,INFINITE);
						Sleep(nPlayWaitTime);
					}

				}else{
					delete [] pMidiFileData[i].pData;
					pMidiFileData[i].pData=NULL;
					pMidiFileData[i].dwSize=0;
				}
			}
		}

	}
	::CloseHandle(hMidiPlayerThrd);
	hMidiPlayerThrd = NULL;
	CloseMidiPlayer();
	return 1;
}

//ý�岥�� - ����MID
/*
    ���ø�ʽ�� ���޷���ֵ�� ����MID ���������� ���Ŵ����ݣ��������� ���ʱ��ݣ�ͨ��������/������ �����ŵ�MIDI���֣�... �� - ϵͳ����֧�ֿ�->ý�岥��
    Ӣ�����ƣ�PlayMID
    �����Զ��������Ŷ�� MIDI �����ļ���ע�ⲻ֧�� WAV ������Ӧ��ʽ���ֽڼ��������ݡ�������Դ��������Ϊ���������������������һ���������Ա��ظ���ӡ�
    ����<1>������Ϊ�����Ŵ�����������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�Ϊ -1 ��ʾָ�����ֽ���ѭ�����ţ������ֻ����ָ���Ĵ����������������ʡ�ԣ�Ĭ��ֵΪ 1 ��
    ����<2>������Ϊ�����ʱ�䡱������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�ָ�� MIDI ����֮��Ĳ��ż��ʱ�䣬��λΪ 0.1 �롣�����������ʡ�ԣ�Ĭ��ֵΪ 0 ��
    ����<3>������Ϊ�������ŵ�MIDI���֡�������Ϊ��ͨ���ͣ�all�������ṩ��������ʱ����ͬʱ�ṩ�������������ݡ�����ֵ����Ϊ MIDI �����ļ����ƻ���Ӧ��ʽ���ֽڼ��������ݡ�������Դ��
*/
LIBAPI(void, krnln_PlayMID)
{
	//������ֹ�����߳�
	CloseMidiPlayer();

	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_dtDataType==_SDT_NULL)
		nLoopNum = 1;
	else
	{
		nLoopNum = pArgInf[0].m_int;

		if(nLoopNum == -1)
			nLoopNum = 2147483647;
		else if(nLoopNum <=0)
			return;
	}
	if(pArgInf[1].m_dtDataType==_SDT_NULL)
		nPlayWaitTime = 0;
	else
	{
		nPlayWaitTime = pArgInf[1].m_int;

		if(nPlayWaitTime <0)
			nPlayWaitTime = 0;
	}
	nPlayWaitTime = nPlayWaitTime *100;
	INT nArg = nArgCount-2;

	INT nCount = GetMidiDataCount(&pArgInf[2],nArg);
	if(nCount==0)
		return;
	pMidiFileData = new MIDIFILEDATAINFO[nCount];
	nCount = GetMidiDataFromArg(&pArgInf[2],nArg);
	if(nCount==0)
	{
		delete [] pMidiFileData;
		pMidiFileData = NULL;
		return;
	}
	nMidiArrySize = nCount;
	
	hLoopPlayEvent = ::CreateEvent(0, FALSE, FALSE, TEXT("Wait For Midi Play End"));

	DWORD dwThreadId;
	HANDLE  hMidiPlayerThrd = CreateThread(NULL,
                0,
                PlayMidiManager,
                0,
                0,
               &dwThreadId);
	if(hMidiPlayerThrd==NULL)
	{
		CloseMidiPlayer();
		return;
	}
	//char tt[16];
	//itoa(nCount,tt,10);
	//MessageBox(NULL,tt,"nMidiArrySize",MB_OK);
	DestroyMidiPlayer=(PDESTROY)CloseMidiPlayer;



}
