#include "stdafx.h"
#include "BitMap.h"

CBitMap::CBitMap()
{
}


CBitMap::~CBitMap()
{
	Release();
}

void CBitMap::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(nullptr,		// ���α׷� �ν��Ͻ� �ڵ�(�츮�� �̹����� ���α׷����� ������ ���� �ƴ϶� ���Ϸκ��� �о�� ���̱� ������ NULL ����)				
		pFilePath,	// �̹��� ������ �ִ� ���
		IMAGE_BITMAP,	// �̹��� Ÿ��(Ȯ���ڸ� �ǹ��ϴ� ���� �ƴ϶� �ڵ� Ÿ��)
		0,				// 4,5 ���� : ����, ���� ������, ���Ͽ��� ���� �о���� ���̱� ������ ������ ������ �ʿ䰡 ����
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : ���Ͽ��� �̹����� �ҷ����ڴ�. LR_CREATEDIBSECTION : �о�� ������ DIB ���·� ��ȯ�ϰڴ�.

												// SelectObject : GDI ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������Ʈ�� ��ȯ
	
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CBitMap::Release(void)
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}