#include "stdafx.h"
#include "BBatteryGageUI.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CBBatteryGageUI::CBBatteryGageUI()
{
}

CBBatteryGageUI::~CBBatteryGageUI()
{
}

void CBBatteryGageUI::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 180.f, 40.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/BatteryBlueGage.bmp", L"BBATTERY_GAGE");
	m_pFrameKey = L"BBATTERY_GAGE";
	m_eRenderGroup = UI;
	m_dwTimer = GetTickCount();
}

int CBBatteryGageUI::Update(void)
{
	if (m_iWeight < 20)
		m_iWeight = 20;

	if (m_iWeight > 200)
		m_iWeight = 200;

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SHIFT))
	{
		if (m_dwTimer + 1000 < GetTickCount())
		{
			m_iWeight += 14;
			m_dwTimer = GetTickCount();
		}
	}
	else if (m_dwTimer + 500 < GetTickCount())
	{
		m_iWeight -= 14;
		m_dwTimer = GetTickCount();
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBBatteryGageUI::Late_Update(void)
{
}

void CBBatteryGageUI::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BBATTERY_GAGE");

	GdiTransparentBlt(hDC,
		15,			// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		5,
		(int)m_tInfo.fCX - m_iWeight,										// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,														// ��Ʈ���� ������ �ִ� dc	
		0,												
		0,
		(int)m_tInfo.fCX - m_iWeight,
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
	// 30 ~ 130
}

void CBBatteryGageUI::Release(void)
{
}
