#include "stdafx.h"
#include <conio.h>
//����̨���� - ��׼����
/*
    ���ø�ʽ�� ���ı��͡� ��׼���� �����߼��� �Ƿ���ԣݣ� - ϵͳ����֧�ֿ�->����̨����
    Ӣ�����ƣ�fgets
    �ڱ�׼�����豸����������������2048���ַ���һ���ı��������û�����������ݡ�ע�Ȿ����ֻ���ڿ���̨������ʹ�á�������Ϊ�������
    ����<1>������Ϊ���Ƿ���ԡ�������Ϊ���߼��ͣ�bool���������Ա�ʡ�ԡ���������������ʱ�Ƿ���ʾ�������ַ���Ϊ�ٲ���ʾ��Ϊ����ʾ�������ʡ�ԣ�Ĭ��ֵΪ�棬�����ԡ�����ͨ��������������Ϊ�������������������Ϣ��
*/
LIBAPI(char*, krnln_fgets)
{
	if(ArgInf.m_dtDataType == _SDT_NULL || ArgInf.m_bool){

		HANDLE hCon = GetStdHandle(STD_INPUT_HANDLE);
		if(hCon==NULL)
			return NULL;
		char Buff[2048];
		DWORD dwSize;
		LPSTR pText = NULL;
		if(ReadConsole(hCon,Buff,2048,&dwSize,NULL))
		//if(ReadFile(hCon,Buff,2048,&dwSize,NULL))
		{
			
			
			if(dwSize>2)
			{
				for(INT i=0;i<(INT)dwSize;i++)
				{
					if(Buff[i]==0)
						break;
					else if(Buff[i]=='\r')
					{
						Buff[i]=0;
						break;
					} else if(Buff[i]=='\n')
					{
						Buff[i]=0;
						break;
					}
					
				}
			}
			pText = CloneTextData(Buff,dwSize);
			
		}
		return pText ;
	}else{
		char Buff[2049];
		INT nIdx = 0;
		Buff[2048]=0;
		do
		{
			INT nChr = getch();
			Buff[nIdx] = (char)nChr;
			if ( nChr == 13 )
				break;
			++nIdx;
		}
		while ( nIdx < 2048 );
		return CloneTextData(Buff,nIdx);
	}
}
