#include "stdafx.h"
#include "Myfunctions.h"
//ʱ����� - ��ʱ��
/*
    ���ø�ʽ�� ������ʱ���͡� ��ʱ�� ��ͨ���� ��ת�����ı��� - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�ToTime
    ��ָ���ı�ת��Ϊʱ�䲢���ء���������ı���������д��ʽҪ�����ʱ��ֵ�����²��ܽ���ת����������100��1��1�ա�������������������ʱ�����ݣ���ֱ�ӷ��ظ�ʱ�䡣������Ϊ�������
    ����<1>������Ϊ����ת�����ı���������Ϊ��ͨ���ͣ�all�������ı�����Ӧ�����¸�ʽ֮һ�ṩ����ݺ��ʱ�䲿�ֿ���ʡ�ԣ�
  1��1973��11��15��12ʱ30��25��
  2��1973/11/15 12:30:25
  3��1973/11/15/12/30/25
  4��1973/11/15/12:30:25
  5��1973-11-15-12-30-25
  6��1973-11-15-12:30:25
  7��1973.11.15 12:30:25
  8��19731115123025
*/
//1899��12��30��0ʱ00��00�� Ϊ0��׼,��λΪ������С��ֵ
BOOL StrToTime (double& dbDateTime,LPCSTR pStr)
{
	INT nLen = mystrlen(pStr);
	if(nLen < 8) return FALSE;

	char* pStrSrc = new char[nLen + 1];
	strcpy(pStrSrc,pStr);
	LPSTR sDtArry[6]={0};
	LPSTR pStart = pStrSrc;
	LPSTR pEnd = pStrSrc + nLen;
	INT nIDX = 0;
	LPSTR pTemp = pStart;
	BOOL spliteChn = FALSE;
	BOOL spliteEng = FALSE;
	INT spliteChr = 0;
	while(pStart < pEnd)
	{
		if(*pStart < 0)//����
		{
			if(spliteEng==FALSE && pStart > pStrSrc)//�Ѿ��ҵ�һЩ����
			{
				if(strncmp(pStart,"��",2)==0)
				{
					if(nIDX !=0)//�겻�ǰ�˳�����
						break;
					*pStart = 0;
					pStart+=2;
					sDtArry[0] = pTemp;
					pTemp = pStart;
					nIDX++;//����
					spliteChn = TRUE;
				}else if(strncmp(pStart,"��",2)==0)
				{
					if(nIDX !=1)//�²��ǰ�˳�����
						break;
					*pStart = 0;
					pStart+=2;
					sDtArry[1] = pTemp;
					pTemp = pStart;
					nIDX++;//����
				}else if(strncmp(pStart,"��",2)==0)
				{
					if(nIDX !=2)//�ղ��ǰ�˳�����
						break;
					*pStart = 0;
					pStart+=2;
					sDtArry[2] = pTemp;
					pTemp = pStart;
					nIDX++;
				}else if(strncmp(pStart,"ʱ",2)==0)
				{
					if(nIDX !=3)//�ղ��ǰ�˳�����
						break;
					*pStart = 0;
					pStart+=2;
					sDtArry[3] = pTemp;
					pTemp = pStart;
					nIDX++;
				}else if(strncmp(pStart,"��",2)==0)
				{
					if(nIDX !=4)//�ղ��ǰ�˳�����
						break;
					*pStart = 0;
					pStart+=2;
					sDtArry[4] = pTemp;
					pTemp = pStart;
					nIDX++;
				}else if(strncmp(pStart,"��",2)==0)
				{
					if(nIDX !=5)//�ղ��ǰ�˳�����
						break;
					*pStart = 0;
					pStart+=2;
					sDtArry[5] = pTemp;
					nIDX++;
				}else
					break;


			}
			else
				break;//�Ƿ�����
		}
		else
		{
			if(48 <= *pStart && *pStart <= 57)//' ���ַ�Χ��48--57
			{
				pStart++;
				if(0 == *pStart)//�������
				{
					sDtArry[nIDX] = pTemp;
					nIDX++;
				}
			}
			else if(nIDX ==0 && spliteChr == 0)//ȷ��Ӣ�ķָ���
			{
				if(spliteChn)//�Ѿ��Ǻ��ָ�ʽ��
					break;
				if(*pStart =='/' || *pStart =='-' || *pStart =='.')
				{
					spliteChr = *pStart;
					spliteEng = TRUE;
					*pStart = 0;
					pStart++;
					sDtArry[0] = pTemp;
					pTemp = pStart;
					nIDX++;



				}
				else
					break; //�ǺϷ��ָ���

			}
			else if(nIDX ==3 && spliteChr == 0)//ȷ��ʱ��ָ���
			{
				if(spliteChn)//�Ѿ��Ǻ��ָ�ʽ��
					break;
				if(*pStart =='/' || *pStart =='-' || *pStart ==':')
				{
					spliteChr = *pStart;
					*pStart = 0;
					pStart++;
					sDtArry[3] = pTemp;
					pTemp = pStart;
					nIDX++;

				}
				else
					break; //�ǺϷ��ָ���
			}
			else if(nIDX ==2 && (*pStart==' ' || *pStart =='/' || *pStart =='-' || *pStart==0))//�����ָ���
			{
				*pStart = 0;
				pStart++;
				sDtArry[2] = pTemp;
				pTemp = pStart;
				nIDX++;
				spliteChr = 0;
			}
			else if(spliteChr == *pStart)//�Ϸ��ָ���
			{
				*pStart = 0;
				pStart++;
				sDtArry[nIDX] = pTemp;
				pTemp = pStart;
				nIDX++;
			}else
				break; //�ǺϷ��ַ�

		}

	}

	if(pStart >= pEnd)//ȫ��ɨ����ϲŽ�����,��ʽ��ȷ
	{
		if(nIDX==1)//ȫ�����ִ���ʽ
		{
			delete [] pStrSrc;
			pStrSrc = new char[256];
			memset(pStrSrc,0,20);
			pStart = pStrSrc;
			INT nMax = 0;
			nIDX = 0;

			while(nMax < nLen)
			{
				if(nIDX==0)
				{
					strncpy(pStart,pStr,4);
					sDtArry[0] = pStart;
					pStart+=5;
					nIDX++;
					nMax +=4;
				}
				else
				{
					strncpy(pStart,pStr+nMax,2);
					sDtArry[nIDX] = pStart;
					pStart+=3;
					nIDX++;
					nMax +=2;
				}

			}


		}
		else if(nIDX < 2) //���ڲ��ֲ�ȫ
		{
			delete [] pStrSrc;
			return FALSE;
		}
		INT nYear, nMonth, nDay, nHour, nMinute, nSecond;//���ʱ���Ƿ���ȷ
		nHour = nMinute = nSecond = 0;
		BOOL bError = FALSE;
		for(INT i=0; i < nIDX;i++)
		{
			INT nValue = atoi(sDtArry[i]);
			switch(i)
			{
			case 0://��
				
				if(nValue==0)
				{
					bError = TRUE;
					break;
				}
				nYear = nValue;
				break;
			case 1://��
				
				if(nValue < 1 || nValue > 12)
				{
					bError = TRUE;
					break;
				}
				nMonth = nValue;
				break;
			case 2://��
				{
					DWORD nMonDay [12] = {31,28,31,30,31,30,31,31,30,31,30,31};
					if((nYear % 400==0) || (nYear % 100 != 0) && (nYear %4 ==0))//����
						nMonDay [1] = 29; //����				
					if(nValue < 1 || nValue > (INT)(nMonDay [nMonth-1]))
					{
						bError = TRUE;
						break;
					}
					nDay = nValue;
					break;
				}
			case 3://ʱ
				
				if(nValue > 23)
				{
					bError = TRUE;
					break;
				}
				nHour = nValue;
				break;
			case 4://��
				
				if(nValue > 59)
				{
					bError = TRUE;
					break;
				}
				nMinute = nValue;
				break;
			case 5://��
				
				if(nValue > 59)
				{
					bError = TRUE;
					break;
				}
				nSecond = nValue;
				break;
			}
		}
		delete [] pStrSrc;
		if(bError)
			return FALSE;

		dbDateTime = GetSpecDateTime(nYear, nMonth, nDay, nHour, nMinute, nSecond);//���ʱ��
		return TRUE;
	}

	delete [] pStrSrc;
	return FALSE;

}

LIBAPI(void, krnln_ToTime)
{

	switch(ArgInf.m_dtDataType)
	{
	case SDT_TEXT:
		{
			double dbDateTime;
			if(StrToTime(dbDateTime,ArgInf.m_pText)==FALSE)
				dbDateTime = -657434;//100��1��1��
			ArgInf.m_double = dbDateTime;
		}
		break;
	case SDT_DATE_TIME:
	case SDT_DOUBLE:
	case SDT_INT64:
		break;
	default:
		ArgInf.m_double = -657434;//100��1��1��
	}
	__asm{
		mov eax, ArgInf.m_unit.m_dwFormID;
		mov edx, ArgInf.m_unit.m_dwUnitID;
	}
}
