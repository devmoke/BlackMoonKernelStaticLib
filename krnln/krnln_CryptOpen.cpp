#include "stdafx.h"
#include "md5t.h"
#include "Myfunctions.h"

// ���ø�ʽ�� �������͡� �򿪼����ļ� ���ı��� ���򿪵��ļ����ƣ��������� �򿪷�ʽ�ݣ��������� ����ʽ�ݣ����ı��� �ļ�����ݣ��������� ���������ȣݣ� - ϵͳ����֧�ֿ�->�ļ���д
// Ӣ�����ƣ�CryptOpen
// ��һ����ָ��������ܵ��ļ����ԶԴ��ļ����п��ٰ�ȫ���ʣ�֧�ִ�ߴ��ļ����ɹ����ر����ļ����ļ��ţ�ʧ�ܷ��� 0��������Ϊ�������
// ����<1>������Ϊ�����򿪵��ļ����ơ�������Ϊ���ı��ͣ�text������
// ����<2>������Ϊ���򿪷�ʽ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵ˵�����ļ��Ĳ�����ʽ�����ʡ�Ա�������Ĭ��Ϊ��#��д������ʽֵ����Ϊ���³���֮һ��
// 1��#���룺��ָ���ļ��������ݣ�������ļ���������ʧ�ܣ�
// 2��#д����д�����ݵ�ָ���ļ���������ļ���������ʧ�ܣ�
// 3��#��д�����ļ��ж������ݻ���д�����ݵ��ļ���������ļ���������ʧ�ܣ�
// 4��#��д��д�����ݵ�ָ���ļ���������ļ����������ȴ���һ�����ļ�������Ѿ����ھ���������е��������ݣ�
// 5��#��д��д�����ݵ�ָ���ļ���������ļ��������򴴽�һ�����ļ�������Ѿ����ھ�ֱ�Ӵ򿪣�
// 6��#�Ķ������ļ��ж������ݻ���д�����ݵ��ļ���������ļ��������򴴽�һ�����ļ�������Ѿ����ھ�ֱ�Ӵ򿪡�
// ����<3>������Ϊ������ʽ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵָ�������������̲������ļ��ķ�ʽ�����ʡ�Ա�������Ĭ��Ϊ��#�����ơ�����ʽֵ����Ϊ���³���֮һ��
// 1��#�����ƣ������������������д���ļ���
// 2��#��ֹ������ֹ�������̶����ļ���
// 3��#��ֹд����ֹ��������д���ļ���
// 4��#��ֹ��д����ֹ�������̶�д���ļ���
// ����<4>������Ϊ���ļ����롱������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ���������򿪵��ļ��в������κ����ݣ���Ϊ���ļ��򽫴��������ļ�����������ָ���������ļ�ʱ����ʹ�õ����룬�Ժ�����д����ļ��е����ݶ���ʹ�ô�������ܺ�д�롣�������볤������Ϊ6���ַ����ϣ�������û��ʹ�ú��֡���ĸ�����֡����ţ��Ա�֤���뱾��İ�ȫ�ԡ���������򿪵��ļ����Ѿ��������ݣ��������ṩ���ʴ���������ʱ����Ҫ����ȷ���룬���������û�м��ܣ����ṩ���ı��Ա�ʾ����Ҫ���롣ע��ϵͳ����ȥУ���������ȷ�ԣ�����ṩ��������룬��д�����ļ����ݽ��õ�����Ľ������ǧ��ע�⡣��������ҪУ�������Ƿ���ȷ�����ڼ��ܺ���ļ��б�����ȷ�������ı��������ı�������ժҪ��Ϣ�������ݲ���֧�ֿ�һ�еġ�ȡ����ժҪ�������Ȼ���ڴ򿪼����ļ����������Ϣ�����������֤��ϵͳ��ʹ�õļ����㷨�ǹ��ʱ�׼��RC4�㷨�����Ա�֤���ݵİ�ȫ�ԡ������������ʡ�ԣ���Ĭ��Ϊ���ı����������롣
// ����<5>������Ϊ�����������ȡ�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�������ָ�����ļ��ײ���ʼ��ϣ�������ܲ��ֵĳ��ȣ�ϵͳ�ڶ�д�������ڵ�����ʱ������ʹ�����������мӽ��ܲ������˲��������������ļ���Ϊ�������������������֣��Է���ĳЩӦ�ó���ͬʱ����һЩ�������ݡ�ע�⵱�����м������ݵ��ļ�ʱ���˲���ֵ�������½��˼����ļ�ʱ���ṩ�Ĳ���ֵһ�£������������ݷ��ʴ��������������ʡ�ԣ���Ĭ��ֵΪ0����û����������
// 
// ����ϵͳ���� Windows
LIBAPI(void*, krnln_CryptOpen) // δ��� 
{
	PMDATA_INF pArgInf = &ArgInf;
	DWORD dwDesiredAccess,dwShareMode,dwCreationDisposition;
	
	if(pArgInf[1].m_dtDataType == _SDT_NULL)
	{//#��д
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
	}
	else
	{
		switch (pArgInf[1].m_int)
		{
		case 1://#����
			dwDesiredAccess = GENERIC_READ;
			dwCreationDisposition = OPEN_EXISTING;
			break;
		case 2://#д��
			dwDesiredAccess = GENERIC_WRITE;
			dwCreationDisposition = OPEN_EXISTING;
			break;
		case 4://#��д
			dwDesiredAccess = GENERIC_WRITE;
			dwCreationDisposition = CREATE_ALWAYS;
			break;
		case 5://#��д
			dwDesiredAccess = GENERIC_WRITE;
			dwCreationDisposition = OPEN_ALWAYS;
			break;
		case 6://#�Ķ�
			dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			dwCreationDisposition = OPEN_ALWAYS;
			break;
		default://#��д
			dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			dwCreationDisposition = OPEN_EXISTING;
			break;
		}
	}
	
	if(pArgInf[2].m_dtDataType == _SDT_NULL)
		dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE );
	else
	{
		if(pArgInf[2].m_int ==2)
			dwShareMode = FILE_SHARE_WRITE ;
		else if(pArgInf[2].m_int ==3)
			dwShareMode = FILE_SHARE_READ ;
		else if(pArgInf[2].m_int ==4)
			dwShareMode = 0;
		else
			dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE );
	}
	
	HANDLE hFile = CreateFile(ArgInf.m_pText,
		dwDesiredAccess,
		dwShareMode,
		NULL,
		dwCreationDisposition,
		FILE_ATTRIBUTE_ARCHIVE,
		0);
	
	
	if(hFile != INVALID_HANDLE_VALUE)
	{
		PFILEELEMENT pFile = new FILEELEMENT;
		if (pArgInf[3].m_dtDataType == _SDT_NULL || !pArgInf[3].m_pText || !*(pArgInf[3].m_pText))
			pFile->nType = 1; // ��ͨ�������ļ�
		else
		{
			int nKeylen = mystrlen(pArgInf[3].m_pText);
			pFile->nType = 3; // �������ļ�

			GetBufMD5(pFile->strMD5, (unsigned char*)pArgInf[3].m_pText, nKeylen);
			swap_hex(pFile->strMD5, 32); //��תMD5

			memset(pFile->strTable,0,258);
			E_RC4_init(pFile->strTable, pArgInf[3].m_pText, nKeylen);

			//����������
			if(pArgInf[4].m_dtDataType == _SDT_NULL)
				pFile->nCryptStart = 0;
			else
				pFile->nCryptStart = pArgInf[4].m_int;
		}

		pFile->FileHandle = hFile;
		AddFileMangerList(pFile);
		return pFile;
	}
	return NULL;
}

