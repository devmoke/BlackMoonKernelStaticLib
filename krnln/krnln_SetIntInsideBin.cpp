#include "stdafx.h"

// ���ø�ʽ�� ���޷���ֵ�� ���ֽڼ������� ���ֽڼ� ��������ֽڼ��������� ��������������ƫ�ƣ������� �����õ�����ֵ�����߼��� �Ƿ�ת�ֽ���ݣ� - ϵͳ����֧�ֿ�->�ֽڼ�����
// Ӣ�����ƣ�SetIntInsideBin
// �����ֽڼ�����ָ��λ�ô�������ֵ��������Ϊ�������
// ����<1>������Ϊ����������ֽڼ���������Ϊ���ֽڼ���bin�������ṩ��������ֽڼ���
// ����<2>������Ϊ����������������ƫ�ơ�������Ϊ�������ͣ�int�������ṩ�������õ�����ֵ���ֽڼ��е�ƫ��λ�á�
// ����<3>������Ϊ�������õ�����ֵ��������Ϊ�������ͣ�int�������ṩ�������õľ�������ֵ��
// ����<4>������Ϊ���Ƿ�ת�ֽ��򡱣�����Ϊ���߼��ͣ�bool���������Ա�ʡ�ԡ�ָ���Ƿ��������������ֽ�����з�ת,Ʃ��ʮ����������0x12345678,��ת��Ϊ0x78563412. ��������������Java���������Խ������ݽ���ʱ�����ô�. ���������ʡ�ԣ�Ĭ��ֵΪ��.
// 
// ����ϵͳ���� Windows��Linux
LIBAPI(void, krnln_SetIntInsideBin)
{
	PMDATA_INF pArgInf = &ArgInf;

	LPBYTE pSrc = pArgInf[0].m_pBin;
	if (!pSrc) return;

	int nLen = pArgInf[0].m_pInt[1];
	int off = pArgInf[1].m_int;
	if (nLen - off < 4) return;

	int nValue = pArgInf[2].m_int;
	if (pArgInf[3].m_dtDataType != _SDT_NULL && pArgInf[3].m_bool)
	{
		int nTmp = nValue;
		nValue = nTmp >> 24;
		nValue |= ((nTmp & 0x00FF0000) >> 8);
		nValue |= ((nTmp & 0x0000FF00) << 8);
		nValue |= ((nTmp & 0x000000FF) << 24);
	}
	*(LPINT)(pSrc + off + 2*sizeof(int)) = nValue;
}
