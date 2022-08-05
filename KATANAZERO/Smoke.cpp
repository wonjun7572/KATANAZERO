#include "stdafx.h"
#include "Smoke.h"
#include "Scene.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SmokeGas.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CSmoke::CSmoke()
{
}

CSmoke::~CSmoke()
{
	Release();
}

void CSmoke::Initialize(void)
{
	m_tInfo.fCX = 42.f;
	m_tInfo.fCY = 42.f;
	m_fSpeed = 30.f;

	m_fDiagonal = 20.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/smoke.bmp", L"SMOKE_ITEM");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/knife_reset.bmp", L"KNIFE_ITEM_RESET");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/knife_plg.bmp", L"KNIFE_ITEM_PLG");
	m_pFrameKey = L"SMOKE_ITEM";
	m_eRenderGroup = GAMEOBJECT;
	m_dwTimer = GetTickCount();
}

int CSmoke::Update(void)
{
	if (m_bDead && m_bRealDead)
	{
		return OBJ_DEAD;
	}
	if (m_bDead && !m_bRealDead)
	{
		m_bDamaged = false;
		int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
		int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());

		m_tPlayerCheck = { m_tInfo.fX , m_tInfo.fY , 200.f, 130.f };
		InfoToRect();

		if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
			m_pPlayer = CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->front();

		if (Check_Sphere(m_pPlayer, &m_tPlayerCheck))
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Hide(true);
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Render(2);
		}
		else
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Hide(false);
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Render(1);
		}
		if (!m_bGas)
		{
			for (int i = 0; i < 3; ++i)
			{
				int fWidthRand = rand() % 100;
				int fWidthRand1 = rand() % 100;
				int fWidthRand2 = rand() % 100;
				int fWidthRand3 = rand() % 100;
		
				int fHeightRand = rand() % 65;
				int fHeightRand1 = rand() % 65;
				int fHeightRand2 = rand() % 65;
				int fHeightRand3 = rand() % 65;

				int	  iAlphaRand = rand() % 255;
				int	  iAlphaRand1 = rand() % 255;
				int	  iAlphaRand2 = rand() % 255;
				int	  iAlphaRand3 = rand() % 255;

				CObjMgr::Get_Instance()->Add_Object(OBJ_SMOKE_GAS, CAbstractFactory<CSmokeGas>::Create_Gas(m_tPlayerCheck.fX + fWidthRand, m_tPlayerCheck.fY + fHeightRand, iAlphaRand));
				CObjMgr::Get_Instance()->Add_Object(OBJ_SMOKE_GAS, CAbstractFactory<CSmokeGas>::Create_Gas(m_tPlayerCheck.fX + fWidthRand2, m_tPlayerCheck.fY - fHeightRand3, iAlphaRand1));
				CObjMgr::Get_Instance()->Add_Object(OBJ_SMOKE_GAS, CAbstractFactory<CSmokeGas>::Create_Gas(m_tPlayerCheck.fX - fWidthRand1, m_tPlayerCheck.fY + fHeightRand2, iAlphaRand2));
				CObjMgr::Get_Instance()->Add_Object(OBJ_SMOKE_GAS, CAbstractFactory<CSmokeGas>::Create_Gas(m_tPlayerCheck.fX - fWidthRand3, m_tPlayerCheck.fY - fHeightRand1, iAlphaRand3));
			}
			m_bGas = true;
		}
	
		if (m_dwTimer + 10000 < GetTickCount())
		{
			m_bRealDead = true;
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Hide(false);
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Render(1);
			CObjMgr::Get_Instance()->Delete_OBJID(OBJ_SMOKE_GAS);
		}
	}
	else
	{
		if (m_tInfo.fX > 5000.f)
		{
			m_bDead = true;
		}
		else if (m_tInfo.fX < -100.f)
		{
			m_bDead = true;
		}
		else if (m_tInfo.fY < -100.f)
		{
			m_bDead = true;
		}
		else if (m_tInfo.fY > 1500.f)
		{
			m_bDead = true;
		}

		m_tInfo.fX -= cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;

		float	fDiagonal = sqrtf((m_tInfo.fCX * 0.5f) * (m_tInfo.fCX * 0.5f) + (m_tInfo.fCY * 0.5f) * (m_tInfo.fCY * 0.5f));

		m_fRotAngle -= 60.f;

		// 좌 상단
		m_tPoint[0].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 135.f) * (PI / 180.f)));
		m_tPoint[0].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 135.f) * (PI / 180.f)));

		// 우 상단
		m_tPoint[1].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 45.f) * (PI / 180.f)));
		m_tPoint[1].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 45.f) * (PI / 180.f)));

		// 좌 하단						
		m_tPoint[2].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 225.f) * (PI / 180.f)));
		m_tPoint[2].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 225.f) * (PI / 180.f)));

		Update_Rect();
	}

	return OBJ_NOEVENT;
}

void CSmoke::Late_Update(void)
{
}

void CSmoke::Render(HDC hDC)
{
	if (!m_bDead)
	{
		int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
		int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());

		HDC hRotaionDC = CBmpMgr::Get_Instance()->Find_Img(L"KNIFE_ITEM_PLG");
		HDC hResetDC = CBmpMgr::Get_Instance()->Find_Img(L"KNIFE_ITEM_RESET");
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"SMOKE_ITEM");

		PlgBlt(hRotaionDC, // 회전 시킬 이미지를 어디에 그릴 것인가
			m_tPoint,	// 그림을 그릴 사각형의 좌표  POINT 변수 3개, 배열의 순서는 좌 상단, 우 상단, 좌 하단 순
			hMemDC,		// 어디에 있는 이미지를 그릴 것인가
			0,			// 그릴 이미지 X,Y 좌표
			0,
			(int)m_tInfo.fCX, // 이미지 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			NULL,
			NULL,
			NULL);

		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,				// 복사 받을 위치의 좌표 전달(x,y 순서)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			(int)m_tInfo.fCY,
			hRotaionDC,												// 비트맵을 가지고 있는 dc	
			0,
			0,
			(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));

		BitBlt(hRotaionDC,
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hResetDC,
			0,
			0,
			SRCCOPY);
	}
}

void CSmoke::Release(void)
{
}

void CSmoke::InfoToRect()
{
	m_rtPlayerRectCheck.left = LONG(m_tPlayerCheck.fX - (m_tPlayerCheck.fCX * 0.5f));
	m_rtPlayerRectCheck.top = LONG(m_tPlayerCheck.fY - (m_tPlayerCheck.fCY * 0.5f));
	m_rtPlayerRectCheck.right = LONG(m_tPlayerCheck.fX + (m_tPlayerCheck.fCX * 0.5f));
	m_rtPlayerRectCheck.bottom = LONG(m_tPlayerCheck.fY + (m_tPlayerCheck.fCY * 0.5f));
}

bool CSmoke::Check_Sphere(CObj* pDest, INFO* pSour)
{
	// c^2 = a^2 + b^2

	// fabs : 절대값을 구해주는 함수
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->fY);

	// sqrtf : 루트를 씌워 값을 구해주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->fCX) * 0.5f;

	return fRadius >= fDiagonal;
}