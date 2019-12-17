#include "stdafx.h"
#include <stdio.h>
#include "mem.h"
#include "Myfunctions.h"
#pragma comment(lib,"comdlg32.lib") 

//ϵͳ���� - ���ļ��Ի���
/*
    ���ø�ʽ�� ���ı������页 ���ļ��Ի��� �����ı��� ����ݣ����ı��� �������ݣ��������� ��ʼ�������ݣ����ı��� ��ʼĿ¼�ݣ����߼��� ���ı�Ŀ¼�ݣ� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�OpenManyFileDialog
    ��ʾһ���ļ��򿪶Ի��������û�ѡ�������������Ҫ�򿪵��Ѵ����ļ��������û���ѡ��������Ľ���ı����顣����û�δ����򰴡�ȡ������ť�˳����򷵻�һ����Ա��Ϊ0�Ŀ��ı����顣������Ϊ�������
    ����<1>������Ϊ�����⡱������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ�ָ���ļ��򿪶Ի���ı��⣬�����ʡ�ԣ���Ĭ��Ϊ�����������򿪵��ļ�������
    ����<2>������Ϊ����������������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ��������ı��ɵ��������ɶԵ��ı�����ɣ�ÿ���ı����ĵ�һ��������ʾ��ʽ���磺���ı��ļ���*.txt�������ڶ���ָ��ʵ�ʵĹ���ƥ������磺��*.txt�������и��ı���֮���á�|���Ÿ����������ʡ�ԣ���Ĭ��û�й�������
    ����<3>������Ϊ����ʼ��������������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������һ�����ṩ����Ч�Ĺ������ı����򱾲�������ָ����ʼ�Ĺ�������0Ϊ��һ���������������ʡ�ԣ���Ĭ��ֵΪ0��
    ����<4>������Ϊ����ʼĿ¼��������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ�ָ�����򿪶Ի���ʱ���Զ���ת����Ŀ¼�������ʡ�ԣ���Ĭ��Ϊ��ǰĿ¼��
    ����<5>������Ϊ�����ı�Ŀ¼��������Ϊ���߼��ͣ�bool���������Ա�ʡ�ԡ�ָ���ڶԻ���رպ��Ƿ��Զ����ص�����Ի���ǰ���ļ�Ŀ¼�������ʡ�ԣ���Ĭ��ֵΪ�١�
    ����<6>������Ϊ�������ڡ�������Ϊ��ͨ���ͣ�all���������Ա�ʡ�ԡ�ָ���Ի���ĸ�����,������һ��"����"�������ݻ���һ�������ʹ��ھ��.�����ʡ��,Ĭ��Ϊ��.

*/
LIBAPI(void*, krnln_OpenManyFileDialog)
{
	PMDATA_INF pArgInf = &ArgInf;
	CMyDWordArray aryText;

	OPENFILENAME fileinfo;
	memset(&fileinfo,0,sizeof(OPENFILENAME));
	fileinfo.lpstrTitle = pArgInf[0].m_pText;
	if(pArgInf[1].m_dtDataType != _SDT_NULL && pArgInf[1].m_pText)
	{
		INT nLen = mystrlen(pArgInf[1].m_pText);
		if(nLen)
		{
			LPSTR pTemp = new char[nLen+2];
			strcpy(pTemp,pArgInf[1].m_pText);
			pTemp[nLen+1]=0;
			INT i=0;
			fileinfo.lpstrFilter=pTemp;
			while(i < nLen)
			{
				if(*pTemp=='|')
					*pTemp = 0;
				pTemp++;
				i++;
			}


		}

	}
	fileinfo.nFilterIndex = pArgInf[2].m_int + 1; //��1��ʼ�����״�0��ʼ
	if(pArgInf[3].m_dtDataType != _SDT_NULL && pArgInf[3].m_pText)
	{
		fileinfo.lpstrInitialDir = pArgInf[3].m_pText;
	}
	


	fileinfo.lStructSize = sizeof(OPENFILENAME);
	char pszFileName[8192];
	pszFileName[0]=0;
	fileinfo.nMaxFile = 8192;
	fileinfo.lpstrFile = pszFileName;
	fileinfo.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT |OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	char preDir [MAX_PATH];
	preDir[0]=0;
	if(pArgInf[4].m_dtDataType != _SDT_NULL && pArgInf[4].m_bool)
	{
		GetCurrentDirectory (MAX_PATH,preDir);
	}
	if(nArgCount>5) //������5.3��������"������"����
	{
		if(pArgInf[5].m_dtDataType != _SDT_NULL)
		{
			fileinfo.hwndOwner = (HWND)pArgInf[5].m_int;
		}
	}
	if(GetOpenFileName(&fileinfo))
	{
		LPSTR pText = pszFileName+fileinfo.nFileOffset;
		LPSTR pPath = pszFileName;

		INT nLen = mystrlen(pPath);
		if(pPath[nLen-1]=='\\')
			pPath[nLen-1]=0;
		nLen = mystrlen(pText);
		if(pText[nLen+1]==0)//ѡ�����ļ�
		{
			nLen = mystrlen(pPath);
			aryText.Add ((DWORD)CloneTextData (pPath, nLen));
		}else{//ѡ����ļ�
			LPSTR pEnd = pText + 8192;
			while(*pText !=0 && pText < pEnd)
			{
				char szFileName [MAX_PATH];
				sprintf(szFileName,"%s\\%s",pPath,pText);
				nLen = mystrlen(szFileName);
				aryText.Add ((DWORD)CloneTextData (szFileName, nLen));
				nLen = mystrlen(pText);
				
				pText+=(nLen+1);
			}

		}


		


		if(preDir[0] !=0)
			SetCurrentDirectory (preDir);



	}
	if(fileinfo.lpstrFilter)
		delete[] (LPSTR)fileinfo.lpstrFilter;

	
	// �����±����������ݡ�
	INT nSize = aryText.GetDWordCount () * sizeof (DWORD);
	LPSTR p = (LPSTR)E_MAlloc (sizeof (INT) * 2 + nSize);
	*(LPINT)p = 1;  // ����ά����
	*(LPINT)(p + sizeof (INT)) = aryText.GetDWordCount ();
	memcpy (p + sizeof (INT) * 2, aryText.GetPtr (), nSize);
	return  p;  // ��������д�ظ����������
}
