#include "stdafx.h"
#include "HUDUI.h"
#include "BmpMgr.h"

CHUDUI::CHUDUI()
{
}

CHUDUI::~CHUDUI()
{
}

void CHUDUI::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 1280.f, 50.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/HUD_UI.bmp", L"HUD_UI");
	m_pFrameKey = L"HUD_UI";
	m_eRenderGroup = UI;
}

int CHUDUI::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CHUDUI::Late_Update(void)
{
}

void CHUDUI::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"HUD_UI");

	BitBlt(hDC,
			0,				
			0,
			(int)m_tInfo.fCX,										
			(int)m_tInfo.fCY,
			hMemDC,
			0,		
			0,
			SRCCOPY);
}

void CHUDUI::Release(void)
{
}
