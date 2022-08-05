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
		1100,				// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		0,
		(int)m_tInfo.fCX,										// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,												// ��Ʈ���� ������ �ִ� dc	
		0,		// 1050 ���� 0����
		0,
		(int)m_tInfo.fCX,										// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(31, 31, 31));
}

void CWeaponUI::Release(void)
{
}
