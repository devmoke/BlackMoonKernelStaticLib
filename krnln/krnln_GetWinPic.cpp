#include "stdafx.h"
#pragma comment(lib,"gdi32.lib")
#include <stdio.h>
//ϵͳ���� - ����
/*
    ���ø�ʽ�� ���ֽڼ��� ���� ���������� ���ھ���ݣ��������� �����ȣݣ��������� ����߶ȣݣ� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetWinPic
    ����ָ�����ڻ���Ļ������������ʾ���ݣ�������ӦͼƬ���ݡ����ʧ�ܣ����ؿ��ֽڼ���������Ϊ�߼����
    ����<1>������Ϊ�����ھ����������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�ָ������������ʾ���ݵĴ��ڡ������ʡ�ԣ�Ĭ��Ϊ������Ļ��ʾ���ݡ�
    ����<2>������Ϊ�������ȡ�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�ָ��ͼƬ�������ȡ����С��0������ֵָ����������ͼƬ�������������ȡ��ͼƬ��ȵİٷֱȣ���СΪ10%�����������0����ͼƬԭ���������������0��ָ�����ͼƬ�ľ��Կ�ȡ������������ʡ�ԣ�Ĭ��ֵΪ0��
    ����<3>������Ϊ������߶ȡ�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�ָ��ͼƬ������߶ȡ����С��0������ֵָ����������ͼƬ����߶��������ȡ��ͼƬ�߶ȵİٷֱȣ���СΪ10%�����������0����ͼƬԭ�߶�������������0��ָ�����ͼƬ�ľ��Ը߶ȡ������������ʡ�ԣ�Ĭ��ֵΪ0��
*/
LIBAPI(void*, krnln_GetWinPic)
{
	PMDATA_INF pArgInf = &ArgInf;
	HWND hWnd = (HWND)pArgInf[0].m_pCompoundData;
	HDC hdc = GetDC(hWnd);
	if(hdc==NULL)
		return NULL;
	RECT rect;

	HWND HObjWnd = hWnd;
	if(HObjWnd==NULL)
		HObjWnd = GetDesktopWindow();
	if(GetWindowRect(HObjWnd,&rect)==FALSE)
	{
		ReleaseDC(hWnd,hdc);
		return NULL;
	}

	SIZE sz; 
	sz.cx=rect.right-rect.left; 
	sz.cy=rect.bottom-rect.top; 
	int nWidth, nHeight;
	nWidth = sz.cx;
	nHeight = sz.cy;
	if(pArgInf[1].m_dtDataType != _SDT_NULL)
	{
		if(pArgInf[1].m_int > 0)
			nWidth = pArgInf[1].m_int;
		else if(pArgInf[1].m_int < 0)
		{
			if(pArgInf[1].m_int<-10)
				pArgInf[1].m_int=-10;
			nWidth = (sz.cx * -1* pArgInf[1].m_int)/100;
		}
	}
	if(pArgInf[2].m_dtDataType != _SDT_NULL)
	{
		if(pArgInf[2].m_int > 0)
			nHeight = pArgInf[2].m_int;
		else if(pArgInf[2].m_int < 0)
		{
			if(pArgInf[2].m_int<-10)
				pArgInf[2].m_int=-10;
			nHeight = (sz.cy * -1* pArgInf[2].m_int)/100;
		}
	}
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP   hBitmap,hOldBitmap;   
	hBitmap = CreateCompatibleBitmap(hdc, nWidth, nHeight);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	//StretchBlt(hMemDC, 0, 0, nWidth, nHeight,hdc, rect.left, rect.top,rect.right,rect.bottom, SRCCOPY);
	SetStretchBltMode(hMemDC, HALFTONE);//��ֹ����ʱʧ��
	StretchBlt(hMemDC, 0, 0, nWidth, nHeight,hdc, -8, 0, sz.cx, sz.cy, SRCCOPY);

	BITMAP bmp; 
	::GetObject(hBitmap, sizeof(BITMAP), &bmp);
	//�����ڴ汣��λͼ���� 

	DWORD dwSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER) + bmp.bmWidthBytes * bmp.bmHeight;
	LPBYTE pData = (LPBYTE)E_MAlloc(dwSize+2* sizeof(INT));
	LPBYTE pArry =pData;
	*(LPINT)pArry=1;
	pArry+=sizeof(INT);
	*(LPINT)pArry=dwSize;
	pArry+=sizeof(INT);

	LPBITMAPFILEHEADER pBfh = (LPBITMAPFILEHEADER)pArry;//λͼ�ļ�ͷ 
	memset(pBfh,0,sizeof(BITMAPFILEHEADER));
	pBfh->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//��λͼ���ݵ�ƫ���� 
	pBfh->bfSize = pBfh->bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//�ļ��ܵĴ�С 
	pBfh->bfType = (WORD)0x4d42; 

	pArry+=sizeof(BITMAPFILEHEADER);

	LPBITMAPINFOHEADER pBih = (LPBITMAPINFOHEADER)pArry;//λͼ��Ϣͷ 
	memset(pBih,0,sizeof(BITMAPINFOHEADER));
	pBih->biSize = sizeof(BITMAPINFOHEADER); 
	pBih->biWidth = bmp.bmWidth;//��� 
	pBih->biHeight = bmp.bmHeight;//�߶� 
	pBih->biPlanes = 1;
	pBih->biBitCount = bmp.bmBitsPixel;//ÿ�������ֽڴ�С 
	pBih->biCompression = BI_RGB; 
	pBih->biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//ͼ�����ݴ�С 
	pBih->biXPelsPerMeter = 0;
	pBih->biYPelsPerMeter = 0;
	pBih->biClrUsed = 0;
	pBih->biClrImportant = 0;
	pArry+=sizeof(BITMAPINFOHEADER);

	GetDIBits(hMemDC, hBitmap, 0, nHeight, pArry, 
	(LPBITMAPINFO)pBih, DIB_RGB_COLORS);//��ȡλͼ���� 
	

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd,hdc);
	DeleteObject(hBitmap);
	return pData;

}
