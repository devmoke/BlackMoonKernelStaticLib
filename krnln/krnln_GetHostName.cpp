#include "stdafx.h"
#include "Myfunctions.h"

#pragma comment(lib,"WS2_32.LIB")
//����ͨ�� - ȡ������
/*
    ���ø�ʽ�� ���ı��͡� ȡ������ ���� - ϵͳ����֧�ֿ�->����ͨ��
    Ӣ�����ƣ�GetHostName
    ���ر�����������������������ͨѶ�б�־������ַ��������Ϊ�������
*/
LIBAPI(void*, krnln_GetHostName)
{
	WSAData wsaData;
	LPSTR pText=NULL;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)==0)
	{
		char hst[MAX_PATH];
		if(gethostname(hst,MAX_PATH)==0)
		{
			pText=CloneTextData(hst,mystrlen(hst));
		}
		WSACleanup ();
	}
	return pText;
}
