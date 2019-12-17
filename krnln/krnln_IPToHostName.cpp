#include "stdafx.h"
#include "Myfunctions.h"

#pragma comment(lib,"WS2_32.LIB")
//����ͨ�� - ת��Ϊ������
/*
    ���ø�ʽ�� ���ı��͡� ת��Ϊ������ ���ı��� ��ת��IP��ַ�� - ϵͳ����֧�ֿ�->����ͨ��
    Ӣ�����ƣ�IPToHostName
    ��ָ���� IP ��ַת��Ϊ�������������ʧ�ܷ��ؿ��ı���������Ϊ�������
    ����<1>������Ϊ����ת��IP��ַ��������Ϊ���ı��ͣ�text������
*/

LIBAPI(char*, krnln_IPToHostName)
{
	WSAData wsaData;
	LPSTR pText=NULL;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)==0)
	{
		DWORD retIP = inet_addr(ArgInf.m_pText);
		if(retIP !=0xFFFFFFFF)
		{
			hostent* hostinfo=gethostbyaddr((char*)&retIP,sizeof(retIP),AF_INET);
			pText=CloneTextData(hostinfo->h_name,mystrlen(hostinfo->h_name));
		
		}
		WSACleanup ();
	}
	return pText;

}
