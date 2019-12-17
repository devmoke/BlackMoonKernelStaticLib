#include "stdafx.h"

//ϵͳ���� - ����
/*
    ���ø�ʽ�� ���߼��͡� ���� ���ı��� �����е������У��߼��� �Ƿ�ȴ�����������ϣ��������� �����г��򴰿���ʾ��ʽ�ݣ� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�run
    ����������ָ���Ŀ�ִ���ļ������ⲿ�������ɹ��������棬���򷵻ؼ١�������Ϊ�������
    ����<1>������Ϊ�������е������С�������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ���Ƿ�ȴ�����������ϡ�������Ϊ���߼��ͣ�bool��������ʼֵΪ���١���
    ����<3>������Ϊ�������г��򴰿���ʾ��ʽ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵ����Ϊ���³���֮һ��
	1��#���ش��ڣ� 2��#��ͨ��� 3��#��С����� 4��#��󻯼�� 5��#��ͨ����� 6��#��С����������ʡ�Ա�������Ĭ��Ϊ����ͨ�����ʽ��
*/
LIBAPI(BOOL, krnln_run)
{
	PMDATA_INF pArgInf = &ArgInf;

	STARTUPINFO startupinfo;
	PROCESS_INFORMATION pinfo;

	startupinfo.cb=sizeof(STARTUPINFO);
	GetStartupInfo(&startupinfo);
	startupinfo.hStdOutput=NULL;
	startupinfo.hStdError=NULL;
	startupinfo.dwFlags=STARTF_USESHOWWINDOW;

	if(pArgInf[2].m_dtDataType != _SDT_NULL)
	{

		switch(pArgInf[2].m_int)
		{
		case 1:
			startupinfo.wShowWindow=SW_HIDE;
			break;
		case 3:
			startupinfo.wShowWindow = SW_SHOWMINIMIZED;
			break;
		case 4:
			startupinfo.wShowWindow = SW_SHOWMAXIMIZED;
			break;	
		case 5:
			startupinfo.wShowWindow = SW_SHOWNOACTIVATE;
			break;	
		case 6:
			startupinfo.wShowWindow = SW_SHOWMINNOACTIVE;
			break;		
		default:
			startupinfo.wShowWindow = SW_SHOW;
			
		}
	}
	else
		startupinfo.wShowWindow = SW_SHOW;

	
	// Create process
	BOOL bRet = CreateProcess(NULL,pArgInf->m_pText,NULL,NULL,TRUE,NULL,NULL,NULL,&startupinfo,&pinfo);
	if(bRet)
	{
		if(pArgInf[1].m_bool)
			WaitForSingleObject(pinfo.hProcess, INFINITE);
		CloseHandle(pinfo.hProcess);
		CloseHandle(pinfo.hThread);
	}

	return bRet;
}
