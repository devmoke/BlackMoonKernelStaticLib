#include "stdafx.h"

//���̲��� - �ƶ��ļ�
/*
    ���ø�ʽ�� ���߼��͡� �ƶ��ļ� ���ı��� ���ƶ����ļ����ı��� �ƶ�����λ�ã� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�FileMove
    ���ļ���һ��λ���ƶ�������һ��λ�á��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ�����ƶ����ļ���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ���ƶ�����λ�á�������Ϊ���ı��ͣ�text������
*/
LIBAPI(BOOL, krnln_FileMove)
{
	PMDATA_INF pArgInf = &ArgInf;
	BOOL result = MoveFile(pArgInf[0].m_pText,pArgInf[1].m_pText);
	if(!result){
		result = CopyFile(pArgInf[0].m_pText,pArgInf[1].m_pText, 0);
		if (result)
			result = DeleteFile(pArgInf[0].m_pText);

	}
	return result;
}
