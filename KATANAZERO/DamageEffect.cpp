#include "stdafx.h"
#include "DamageEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CDamageEffect::CDamageEffect()
{
}

CDamageEffect::~CDamageEffect()
{
}

void CDamageEffect::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 1600.f, 1600.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/Plg.bmp", L"Plg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect_hit_lazer.bmp", L"HIT_LAZER_EFFECT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/Reset.bmp", L"Reset");
	m_pFrameKey = L"HIT_LAZER_EFFECT";
	m_fSpeed = 100.f;
	m_eRenderGroup = EFFECT;
	m_dwOldTime = GetTickCount();
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	// 이 각도가 텍스처 생성되는 가로와 마우스 포인터와의 각도
}

int CDamageEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bGetAngle)
	{
		// tan 나와 마우스포인터와의 각도 0~180  -180~0
		m_fAngle = atan2f((dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().y - m_tInfo.fY), (m_tInfo.fX - dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().x)) / (PI / 180.f);
		//m_fAngle = 45.f;
		float	fDiagonal = sqrtf((m_tInfo.fCX * 0.5f) * (m_tInfo.fCX * 0.5f) + (m_tInfo.fCY * 0.5f) * (m_tInfo.fCY * 0.5f));

		// 좌 상단
		m_tPoint[0].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fAngle + 135.f) * (PI / 180.f)));
		m_tPoint[0].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fAngle + 135.f) * (PI / 180.f)));

		// 우 상단
		m_tPoint[1].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fAngle + 45.f) * (PI / 180.f)));
		m_tPoint[1].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fAngle + 45.f) * (PI / 180.f)));

		// 좌 하단						
		m_tPoint[2].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fAngle + 225.f) * (PI / 180.f)));
		m_tPoint[2].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fAngle + 225.f) * (PI / 180.f)));
		float fAngle = atan2f(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Info().fY - dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().y, dynamic_cast<CPlayer*>(m_pPlayer)->Get_Info().fX - (dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().x)) * (180.f / PI);
	
		m_tInfo.fX -= cosf(fAngle * (PI / 180.f)) * m_fSpeed;
		m_tInfo.fY -= sinf(fAngle * (PI / 180.f)) * m_fSpeed;
		m_bGetAngle = true;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CDamageEffect::Late_Update(void)
{
}

void CDamageEffect::Render(HDC hDC)
{
	HDC hRotaionDC = CBmpMgr::Get_Instance()->Find_Img(L"Plg");
	HDC hResetDC = CBmpMgr::Get_Instance()->Find_Img(L"Reset");
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

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
		m_tRect.left + iScrollX,	// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,		// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hRotaionDC,					// 비트맵을 가지고 있는 dc
		0, 						// 출력할 비트맵 시작 좌표(x,y 순서)
		0,
		(int)m_tInfo.fCX,			// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(31, 31, 31));	// 제거할 픽셀의 색상

	BitBlt(hRotaionDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hResetDC,
		0,
		0,
		SRCCOPY);

	if (m_dwOldTime + 200 < GetTickCount())
	{
		m_bDead = true;

		m_dwOldTime = GetTickCount();
	}
}

void CDamageEffect::Release(void)
{
}
