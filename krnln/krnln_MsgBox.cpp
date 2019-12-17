#include "stdafx.h"
#include <stdio.h>
#include "LTrimZeroChr.h"

//#pragma comment(lib,"oleaut32.lib") 

//ϵͳ���� - ��Ϣ��
/*
    ���ø�ʽ�� �������͡� ��Ϣ�� ��ͨ���� ��ʾ��Ϣ�������� ��ť�����ı��� ���ڱ���ݣ� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�MsgBox
    �ڶԻ�������ʾ��Ϣ���ȴ��û�������ť��������һ�����������û�������һ����ť��������Ϊ���³���ֵ֮һ�� 0��#ȷ��ť�� 1��#ȡ��ť�� 2��#����ť�� 3��#����ť�� 4��#����ť�� 5��#��ť�� 6��#��ť������Ի����С�ȡ������ť������ ESC ���뵥����ȡ������ť��Ч����ͬ��������Ϊ�������
    ����<1>������Ϊ����ʾ��Ϣ��������Ϊ��ͨ���ͣ�all��������ʾ��Ϣֻ��Ϊ�ı�����ֵ���߼�ֵ������ʱ�䡣�����ʾ��ϢΪ�ı��Ұ������У����ڸ���֮���ûس��� (�����ַ� (13)��)�����з� (�����ַ� (10)��) ��س����з������ (�������ַ� (13) + �ַ� (10)��) ���ָ���
    ����<2>������Ϊ����ť��������Ϊ�������ͣ�int��������ʼֵΪ��0��������ֵ�����¼��鳣��ֵ��ɣ��ڽ���Щ����ֵ��������ɲ���ֵʱ��ÿ��ֵֻ��ȡ��һ�����֣���������⣩�� 
  ��һ�飨�����Ի�������ʾ��ť����������Ŀ����
    0��#ȷ��ť�� 1��#ȷ��ȡ��ť�� 2��#�������Ժ���ť�� 3��#ȡ���Ƿ�ť��     4��#�Ƿ�ť�� 5��#����ȡ��ť
  �ڶ��飨����ͼ�����ʽ����
    16��#����ͼ�ꣻ 32��#ѯ��ͼ�ꣻ 48��#����ͼ�ꣻ 64��#��Ϣͼ��
  �����飨˵����һ����ť��ȱʡĬ��ֵ����
    0��#Ĭ�ϰ�ťһ�� 256��#Ĭ�ϰ�ť���� 512��#Ĭ�ϰ�ť���� 768��#Ĭ�ϰ�ť��
  �����飨������εȴ���Ϣ���������
    0��#����ȴ��� 4096��#ϵͳ�ȴ�
  �����飨��������
    65536��#λ��ǰ̨�� 524288��#�ı��Ҷ���

    ����<3>������Ϊ�����ڱ��⡱������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ�����ֵָ����ʾ�ڶԻ���������е��ı������ʡ�ԣ�Ĭ��Ϊ�ı�����Ϣ������
*/

LIBAPI(int, krnln_MsgBox)
{
	char str [MAX_PATH];
    HWND hWnd=NULL;
	LPCSTR lpText=NULL;
	LPCSTR lpCaption="��Ϣ";
    UINT uType=MB_OK;

	if((ArgInf.m_dtDataType & DT_IS_ARY) == 0)//������
	{
		
		
		switch(ArgInf.m_dtDataType)
		{
		case SDT_TEXT:
			lpText = ArgInf.m_pText;
			break;
		case SDT_BYTE:
			{
				INT nVal = ArgInf.m_byte;
				sprintf(str,"%d",nVal);
				lpText = str;
			}
			break;
		case SDT_SHORT:
			{
				INT nVal = ArgInf.m_short;
				sprintf(str,"%d",nVal);
				lpText = str;
			}
			break;
		case SDT_INT:
		case SDT_SUB_PTR:
			sprintf(str,"%d",ArgInf.m_int);
			lpText = str;
			break;
		case SDT_INT64:
			sprintf(str,"%I64d",ArgInf.m_int64);
			lpText = str;
			break;
		case SDT_FLOAT:
			sprintf(str,"%f",ArgInf.m_float);
			LTrimZeroChr(str);
			lpText = str;
			break;
		case SDT_DOUBLE:
			sprintf(str,"%lf",ArgInf.m_double);
			LTrimZeroChr(str);
			lpText = str;
			break;
		case SDT_BOOL:
			if(ArgInf.m_bool)
				strcpy(str,"��");
			else
				strcpy(str,"��");
			lpText = str;
			break;

		case SDT_DATE_TIME:
			DateTimeFormat(str,ArgInf.m_double);
			lpText = str;
		}

	}
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[1].m_dtDataType!=_SDT_NULL)
	{
		uType=pArgInf[1].m_int;
	}
	if(pArgInf[2].m_dtDataType!=_SDT_NULL)
	{
		lpCaption=pArgInf[2].m_pText;
	}
	if(nArgCount>3)//������5.3��������"������"����
	{
		if(pArgInf[3].m_dtDataType==SDT_INT)
		{
			hWnd=(HWND)pArgInf[3].m_int;
		}
	}
	INT nRet = MessageBox(hWnd,lpText,lpCaption,uType);
	return (nRet-1);
}
