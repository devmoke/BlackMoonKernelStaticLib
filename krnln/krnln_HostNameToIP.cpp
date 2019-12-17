#include "stdafx.h"
#include "Myfunctions.h"

#pragma comment(lib,"WS2_32.LIB")
//����ͨ�� - ת��ΪIP��ַ
/*
    ���ø�ʽ�� ���ı��͡� ת��ΪIP��ַ ���ı��� ��ת���������� - ϵͳ����֧�ֿ�->����ͨ��
    Ӣ�����ƣ�HostNameToIP
    ��ָ����������ת��Ϊ�� IP ��ַ�����ʧ�ܷ��ؿ��ı���������Ϊ�������
    ����<1>������Ϊ����ת����������������Ϊ���ı��ͣ�text������
*/

DWORD MYGetIPbyname(char *HostName)
{
	DWORD retIP;
	hostent* heDestHost = gethostbyname (HostName);

	if(heDestHost)
		retIP=*(DWORD *)*heDestHost->h_addr_list;
	else
		retIP=0xFFFFFFFF;
	return retIP;
}

LIBAPI(char*, krnln_HostNameToIP)
{
	WSAData wsaData;
	LPSTR pText=NULL;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)==0)
	{
		DWORD retIP = MYGetIPbyname(ArgInf.m_pText);
		if(retIP !=0xFFFFFFFF)
		{
			sockaddr_in localaddr;
			localaddr.sin_addr.S_un.S_addr=retIP;
			LPSTR pIp = inet_ntoa(localaddr.sin_addr);
			pText=CloneTextData(pIp,mystrlen(pIp));

		}
		WSACleanup ();
	}
	return pText;
}
