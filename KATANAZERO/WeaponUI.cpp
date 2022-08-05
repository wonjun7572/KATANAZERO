#include "stdafx.h"
#include "WeaponUI.h"
#include "BmpMgr.h"

CWeaponUI::CWeaponUI()
{
}


CWeaponUI::~CWeaponUI()
{
}

void CWeaponUI::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 112.f, 48.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/hud_subweapon.bmp", L"WEAPON_UI");
	m_pFrameKey = L"WEAPON_UI";
	m_eRenderGroup = UI;
}

int CWeaponUI::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CWeaponUI::Late_Update(void)
{
}

void CWeaponUI::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"WEAPON_UI");

	GdiTransparentBlt(hDC,
		1100,				// 복사 받을 위치의 좌표 전달(x,y 순서)
		0,
		(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,												// 비트맵을 가지고 있는 dc	
		0,		// 1050 부터 0으로
		0,
		(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(31, 31, 31));
}

void CWeaponUI::Release(void)
{
}
