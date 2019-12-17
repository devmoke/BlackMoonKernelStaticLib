#include "stdafx.h"
#pragma comment(lib,"winmm.lib") 

//ý�岥�� - ��������
/*
    ���ø�ʽ�� ���߼��͡� �������� ��ͨ���� �����ŵ����֣����߼��� �Ƿ�ѭ�����ţݣ� - ϵͳ����֧�ֿ�->ý�岥��
    Ӣ�����ƣ�PlayMusic
    ���Բ��� .WAV��.MID �����ļ�����Ӧ��ʽ���ֽڼ��������ݡ�������Դ���ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ�������ŵ����֡�������Ϊ��ͨ���ͣ�all����������ֵ����Ϊ .WAV��.MID �����ļ����ƻ���Ӧ��ʽ���ֽڼ��������ݡ�������Դ��
    ����<2>������Ϊ���Ƿ�ѭ�����š�������Ϊ���߼��ͣ�bool���������Ա�ʡ�ԡ�Ϊ���ʾָ�����ֽ���ѭ�����ţ������ֻ����һ�Ρ������������ʡ�ԣ�Ĭ��Ϊ������һ�Ρ�
*/
extern HANDLE hBlackMoonInstanceHandle;

LIBAPI(BOOL, krnln_PlayMusic)
{
	DWORD dwSound = SND_ASYNC|SND_NODEFAULT;
	LPCSTR pszMusicData;
	HMODULE hmod = NULL;
	if(ArgInf.m_dtDataType == SDT_TEXT)
	{
		dwSound |= SND_FILENAME;
		pszMusicData = ArgInf.m_pText;

	}else if(ArgInf.m_dtDataType == SDT_BIN)
	{
		dwSound |= SND_MEMORY;

		pszMusicData = ArgInf.m_pText + 2*sizeof(INT);

	}else if(ArgInf.m_dtDataType == SDT_INT || ArgInf.m_dtDataType == SDT_BYTE || ArgInf.m_dtDataType == SDT_SHORT)
	{
		dwSound |=SND_RESOURCE;
		pszMusicData = MAKEINTRESOURCE(ArgInf.m_int);
		if(hBlackMoonInstanceHandle)
			hmod = (HMODULE)hBlackMoonInstanceHandle;
		else
			hmod = ::GetModuleHandle(NULL);
			

	}else
		return FALSE;

	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[1].m_dtDataType != _SDT_NULL && pArgInf[1].m_bool)
		dwSound |= SND_LOOP;

	return PlaySound(pszMusicData,hmod,dwSound);
}
