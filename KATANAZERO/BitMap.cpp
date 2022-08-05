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

	m_hBitmap = (HBITMAP)LoadImage(nullptr,		// 프로그램 인스턴스 핸들(우리는 이미지를 프로그램에서 얻어오는 것이 아니라 파일로부터 읽어올 것이기 때문에 NULL 전달)				
		pFilePath,	// 이미지 파일이 있는 경로
		IMAGE_BITMAP,	// 이미지 타입(확장자를 의미하는 것이 아니라 핸들 타입)
		0,				// 4,5 인자 : 가로, 세로 사이즈, 파일에서 직접 읽어들일 것이기 때문에 별도로 지정할 필요가 없음
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : 파일에서 이미지를 불러오겠다. LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환하겠다.

												// SelectObject : GDI 오브젝트를 선택하기 전에 기존에 가지고 있던 오브젝트를 반환
	
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CBitMap::Release(void)
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}