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
		15,				// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		5,
		(int)m_tInfo.fCX,										// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,												// ��Ʈ���� ������ �ִ� dc	
		0,		// 1050 ���� 0����
		0,
		(int)m_tInfo.fCX,										// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(0, 0, 0));
}

void CRBatteryGageUI::Release(void)
{
}
