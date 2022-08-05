#pragma once

#include "Include.h"

class CBitMap
{
public:
	CBitMap();
	~CBitMap();

public:
	HDC		Get_MemDC(void) { return m_hMemDC; }
	void	Load_Bmp(const TCHAR* pFilePath);
	void	Release(void);

private:

	HDC					m_hMemDC;
	HBITMAP				m_hBitmap;
	HBITMAP				m_hOldBmp;
};

