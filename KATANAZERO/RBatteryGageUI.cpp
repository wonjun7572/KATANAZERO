#include "stdafx.h"
#include "RBatteryGageUI.h"
#include "BmpMgr.h"

CRBatteryGageUI::CRBatteryGageUI()
{
}


CRBatteryGageUI::~CRBatteryGageUI()
{
}

void CRBatteryGageUI::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 180.f, 40.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/BatteryRedGage.bmp", L"RBATTERY_GAGE");
	m_pFrameKey = L"RBATTERY_GAGE";
	m_eRenderGroup = UI;
}

int CRBatteryGageUI::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CRBatteryGageUI::Late_Update(void)
{
}

void CRBatteryGageUI::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"RBATTERY_GAGE");
	
	GdiTransparentBlt(hDC,
		15,				// 복사 받을 위치의 좌표 전달(x,y 순서)
		5,
		(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,												// 비트맵을 가지고 있는 dc	
		0,		// 1050 부터 0으로
		0,
		(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(0, 0, 0));
}

void CRBatteryGageUI::Release(void)
{
}
