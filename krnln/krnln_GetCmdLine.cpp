#include "stdafx.h"
#include "mem.h"

//#pragma comment(lib,"shell32.lib") 

//������ȡ - ȡ������
/*
    ���ø�ʽ�� ���޷���ֵ�� ȡ������ ���ı��ͱ������� ��ű�ȡ���������ı������������ - ϵͳ����֧�ֿ�->������ȡ
    Ӣ�����ƣ�GetCmdLine
    ���������ȡ���������׳���ʱ���������ִ���ļ�������������Կո�ָ����������ı��Ρ�������Ϊ�������
    ����<1>������Ϊ����ű�ȡ���������ı������������������Ϊ���ı��ͣ�text�������ṩ��������ʱֻ���ṩ�������顣������ִ����Ϻ󣬱����������ڱ�˳�������������׳���ʱ���������ִ���ļ���������Կո�ָ����������ı��Ρ�����������ԭ�����ݱ�ȫ�����٣����������ά�����Զ�����Ϊ�������ı�������
*/
/*
char* BMUnicodeToAnsi(LPWSTR lpWstr)
{
	INT nLen = WideCharToMultiByte(0, 0, lpWstr, -1, NULL, NULL, 0, 0);
	if(nLen==0)return NULL;
	char* pText = (char*)E_MAlloc(nLen +1);
	WideCharToMultiByte (0, 0, lpWstr, -1,pText, nLen, 0, 0);
	return pText;

}
*/
#define IS_CC(p) p<0

LIBAPI(void, krnln_GetCmdLine)
{
	LPWSTR *szArglist;
	int nArgs, i;
	int al;
	char *pSrc;
	LPSTR p;
	CMyDWordArray aryText;

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (szArglist)
	{
		for (i=1; i<nArgs; i++)
		{
			//��UNICDOEת��ANSI
			al = WideCharToMultiByte(936, NULL, szArglist[i], -1, NULL, NULL, NULL, NULL);
			pSrc = NULL;
			if (al > 0)
			{
				pSrc = (char*)E_MAlloc_Nzero(al + 1);
				if (pSrc)
				{
					al = WideCharToMultiByte(936, NULL, szArglist[i], -1, pSrc, al, NULL, NULL);
					pSrc[al] = 0;
				}
				aryText.Add ((DWORD)pSrc);
			}
		}
	}

	//!!! �������ͷ�ԭ����������������ݡ�
	void * pArry = *ArgInf.m_ppAryData;
	if(pArry)
		FreeAryElement(pArry);
	
	// �����±����������ݡ�
	INT nSize = aryText.GetDWordCount () * sizeof (DWORD);
	p = (LPSTR)E_MAlloc_Nzero (sizeof (INT) * 2 + nSize);
	*(LPINT)p = 1;  // ����ά����
	*(LPINT)(p + sizeof (INT)) = aryText.GetDWordCount ();
	memcpy (p + sizeof (INT) * 2, aryText.GetPtr (), nSize);
	*ArgInf.m_ppAryData =  p;  // ��������д�ظ����������
}

/*
extern "C" void _cdecl krnln_GetCmdLine (INT nArgCount,MDATA_INF ArgInf,...)
{
/*
	void * pArry = *ArgInf.m_ppAryData;
	if(pArry)
		FreeAryElement(pArry);

	int argCount = 0;
	LPWSTR* lpArgv = ::CommandLineToArgvW(::GetCommandLineW(), &argCount);
	LPINT pArryData;
	if(argCount < 2 )
	{
		pArryData = (LPINT)E_MAlloc(2 * sizeof(INT));
		pArryData[0]=1;
		pArryData[1]=0;
		*ArgInf.m_ppAryData = pArryData;
	}
	else
	{
		argCount --;
		pArryData = (LPINT)E_MAlloc((2+argCount) * sizeof(INT));
		pArryData[0]=1;
		pArryData[1]=argCount;
		LPSTR* pArryText = (LPSTR*)(pArryData+2);

		for(INT i=0;i < argCount;i++)
		{
			pArryText[i] = BMUnicodeToAnsi(lpArgv[i+1]);
			//MessageBox(NULL,pArryText[i],NULL,MB_OK);
		}
		

	}
	*ArgInf.m_ppAryData = pArryData;

	GlobalFree(lpArgv);
*/

/*
	LPSTR p = GetCommandLine (), pb;
	// �������ó�������
	char ch = ' ';
	if (*p++ == '\"')
		ch = '\"';
	while (*p++ != ch);
	if (ch != ' ' && *p == ' ')  p++;    // ������һ���ո�
	
	CMyDWordArray aryText;
	
	while (*p != '\0')
	{
		if (*p == '\"')
		{
			p++;
			pb = p;
			while (*pb != '\0' && *pb != '\"')
			{
				if (IS_CC (*pb) == TRUE)
				{
					if (pb [1] == 0)  break;
					pb++;
				}
				pb++;
			}
			
			aryText.Add ((DWORD)CloneTextData ((char*)p, pb - p));
			
			p = pb;
			if (*p != '\0')  p++;
		}
		else if (*p > ' ' || *pb<0)
		{
			pb = p;
			while (*pb != '\0' && *pb != '\"' && (*pb > ' ' || *pb<0))
			{
				if (IS_CC (*pb) == TRUE)
				{
					if (pb [1] == 0)  break;
					pb++;
				}
				pb++;
			}
			
			aryText.Add ((DWORD)CloneTextData ((char*)p, pb - p));
			
			p = pb;
		}
		else
			p++;
	}
	
	//!!! �������ͷ�ԭ����������������ݡ�
	void * pArry = *ArgInf.m_ppAryData;
	if(pArry)
		FreeAryElement(pArry);
	
	// �����±����������ݡ�
	INT nSize = aryText.GetDWordCount () * sizeof (DWORD);
	p = (LPSTR)E_MAlloc_Nzero (sizeof (INT) * 2 + nSize);
	*(LPINT)p = 1;  // ����ά����
	*(LPINT)(p + sizeof (INT)) = aryText.GetDWordCount ();
	A_memcpy (p + sizeof (INT) * 2, aryText.GetPtr (), nSize);
	*ArgInf.m_ppAryData =  p;  // ��������д�ظ����������
}
*/