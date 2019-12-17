#include "stdafx.h"

// ���ø�ʽ�� �������͡� ȡ�ֽڼ������� ���ֽڼ� ��������ֽڼ��������� ����ȡ��������ƫ�ƣ����߼��� �Ƿ�ת�ֽ���ݣ� - ϵͳ����֧�ֿ�->�ֽڼ�����
// Ӣ�����ƣ�GetIntInsideBin
// �����ֽڼ�����ָ��λ�ô���������������Ϊ�������
// ����<1>������Ϊ����������ֽڼ���������Ϊ���ֽڼ���bin�������ṩ��������ֽڼ���
// ����<2>������Ϊ������ȡ��������ƫ�ơ�������Ϊ�������ͣ�int�������ṩ������ȡ������ֵ���ֽڼ��е�ƫ��λ�á�
// ����<3>������Ϊ���Ƿ�ת�ֽ��򡱣�����Ϊ���߼��ͣ�bool���������Ա�ʡ�ԡ�ָ���Ƿ�����ȡ����ֵ���ֽ�����з�ת,Ʃ��ʮ����������0x12345678,��ת��Ϊ0x78563412. ��������������Java���������Խ������ݽ���ʱ�����ô�. ���������ʡ�ԣ�Ĭ��ֵΪ��.
// 
// ����ϵͳ���� Windows��Linux

LIBAPI(int, krnln_GetIntInsideBin)
{
	PMDATA_INF pArgInf = &ArgInf;
	
	LPBYTE pSrc = pArgInf[0].m_pBin;
	if (!pSrc) return 0;
	
	int nLen = pArgInf[0].m_pInt[1];
	int off = pArgInf[1].m_int;
	if (nLen - off < 4) return 0;
	
	int nValue = *(LPINT)(pSrc + off + 2*sizeof(int));
	if (pArgInf[2].m_dtDataType != _SDT_NULL && pArgInf[2].m_bool)
	{
		int nTmp = nValue;
		nValue = nTmp >> 24;
		nValue |= ((nTmp & 0x00FF0000) >> 8);
		nValue |= ((nTmp & 0x0000FF00) << 8);
		nValue |= ((nTmp & 0x000000FF) << 24);
	}
	return nValue;
}