#include "stdafx.h"
#pragma comment(lib,"WS2_32.LIB")
#pragma comment(lib,"icmp.lib")

//����ͨ�� - ͨ�Ų���
/*
    ���ø�ʽ�� �������͡� ͨ�Ų��� ���ı��� ������������ַ���������� ��ȴ�ʱ��ݣ� - ϵͳ����֧�ֿ�->����ͨ��
    Ӣ�����ƣ�ping
    ������ָ�������Ƿ��ܹ�����ͨѶ�����ر�����������ͨѶ��Ӧʱ�䡣����޷�ͨѶ���߲���ʧ�ܣ����� -1��������Ϊ�������
    ����<1>������Ϊ��������������ַ��������Ϊ���ı��ͣ�text����������Ϊ��������IP��ַ�ȡ�
    ����<2>������Ϊ����ȴ�ʱ�䡱������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�ָ����ȴ�������������Ӧ��ʱ�䣬��λΪ���롣������ʱ�伴��Ϊ�޷��뱻��������ͨѶ�����ʡ�Ա���������Ĭ��Ϊ 10 * 1000 ���룬�� 10 �롣
*/
#pragma pack (push, old_value)   // ����VC++�������ṹ�����ֽ�����
#pragma pack (1)    // ����Ϊ��һ�ֽڶ��롣

typedef struct tagIPINFO 
{ 
u_char Ttl; // TTL 
u_char Tos; // �������� 
u_char IPFlags; // IP��־ 
u_char OptSize; // ��ѡ���ݴ�С 
u_char *Options; // ��ѡ����buffer 
} IPINFO, *PIPINFO; 

typedef struct tagICMPECHO 
{ 
u_long Source; // Դ��ַ 
u_long Status; // IP״̬ 
u_long RTTime; // RTT 
u_short DataSize; // �ظ����ݴ�С 
u_short Reserved; // ���� 
void *pData; // �ظ�����buffer 
IPINFO ipInfo; // �ظ�IPѡ�� 
char Data [250];
} ICMPECHO, *PICMPECHO; 

#pragma pack (pop, old_value)    // �ָ�VC++�������ṹ�����ֽ�����

extern "C"
{
HANDLE _cdecl IcmpCreateFile(void);//�����򿪸�ICMP Echo������ʹ�õľ���� 
BOOL _cdecl IcmpCloseHandle(HANDLE IcmpHandle);//�رողŴ򿪵ľ�� 
DWORD _cdecl IcmpSendEcho(HANDLE,DWORD,LPVOID,WORD,PIPINFO,LPVOID,DWORD,DWORD);//����Echo���󲢵�
}

DWORD BMGetIPbyname(char *HostName)
{
	hostent* heDestHost;
	DWORD retIP = inet_addr(HostName);
	if(retIP==0xFFFFFFFF)
	{
		heDestHost=gethostbyname (HostName);
		if(heDestHost)
			retIP=*(DWORD *)*heDestHost->h_addr_list;
	}

	return retIP;
}

LIBAPI(int, krnln_ping)
{
	PMDATA_INF pArgInf = &ArgInf;
	WSAData wsaData;
	INT nRet = -1;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)==0)
	{
		DWORD dwAddress = BMGetIPbyname(pArgInf[0].m_pText);
		if(dwAddress != 0xFFFFFFFF)
		{
			DWORD dwPingTimeOut = 10000;
			if(pArgInf[1].m_dtDataType != _SDT_NULL)
				dwPingTimeOut = pArgInf[1].m_int;

			FARPROC (__stdcall *IcmpCreateFilefun)(void);
			*(FARPROC *)&IcmpCreateFilefun = (FARPROC)IcmpCreateFile;

			HANDLE hICmp = IcmpCreateFilefun();
			if(hICmp)
			{
				ICMPECHO icmp;
				FARPROC (__stdcall *IcmpSendEchofun)(HANDLE,DWORD,LPVOID,WORD,PIPINFO,LPVOID,DWORD,DWORD);
				*(FARPROC *)&IcmpSendEchofun = (FARPROC)IcmpSendEcho;

				if(IcmpSendEchofun (hICmp,
					dwAddress,
					"BlackMoonPing",
					13,
					0,
					&icmp,
					sizeof(icmp),
					dwPingTimeOut))
				{
					nRet = icmp.RTTime;
				}
				FARPROC (__stdcall *IcmpCloseHandlefun)(HANDLE);
				*(FARPROC *)&IcmpCloseHandlefun = (FARPROC)IcmpCloseHandle;
				IcmpCloseHandlefun(hICmp);
			}

		}

		WSACleanup ();
	}
	return nRet;
}
