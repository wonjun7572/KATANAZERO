#include "stdafx.h"
#include "Monster_2.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "HitEffect.h"
#include "HitEffect_1.h" 
#include "GunSparkEffect.h"

CMonster_2::CMonster_2()
	: m_eCurState(IDLE), m_ePreState(MOTION_END)
{
	m_pPlayer = nullptr;
	ZeroMemory(&m_rtPlayerRectCheck, sizeof(m_rtPlayerRectCheck));
	ZeroMemory(&m_tPlayerCheck, sizeof(m_tPlayerCheck));
}

CMonster_2::~CMonster_2()
{
	Release();
}

void CMonster_2::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 72.f, 74.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/enemy/enemy_cop_idle_8x2.bmp", L"ENEMY_COP_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/enemy/enemy_cop_hurt_14x2.bmp", L"ENEMY_COP_DEAD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/enemy/enemy_cop_walk_8x2.bmp", L"ENEMY_COP_WALK");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/enemy/enemy_cop_run_10x2.bmp", L"ENEMY_COP_RUN");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/enemy/ememy_exclamation_mark.bmp", L"ENEMY_EXCLAMATION_MARK");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/enemy/enemy_question_mark.bmp", L"ENEMY_QUESTION_MARK");

	m_pFrameKey = L"ENEMY_COP_IDLE";
	m_eCurState = IDLE;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	if (m_eDir == DIR_RIGHT)
	{
		m_eLookDir = LOOK_RIGHT;
	}
	else
		m_eLookDir = LOOK_LEFT;
	m_tFrame.iMotion = m_eLookDir;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_dwOldTime = GetTickCount();

	m_fSpeed = 0.5f;
	m_fJumpPower = 15.f;

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
	{
		m_pPlayer = CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->front();
	}
	m_eRenderGroup = ENEMY;
}

int CMonster_2::Update(void)
{

	RECT rt{};
	if (m_bDead)
	{
		if (!m_bRealJump)
		{
			m_bJump = true;
			m_bRealJump = true;
		}
		m_bWalk = false;
		m_bAttack = false;
		m_eCurState = DEAD;
		if (m_bHitEffect == false)
		{
			if (m_eLookDir == LOOK_LEFT)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CHitEffect>::Create(m_tInfo.fX, m_tInfo.fY - 70.f, DIR_RIGHT));
			}
			else if (m_eLookDir == LOOK_RIGHT)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CHitEffect>::Create(m_tInfo.fX, m_tInfo.fY - 70.f, DIR_LEFT));
			}
			m_bHitEffect = true;
		}
	}
	else if ((IntersectRect(&rt, &m_pPlayer->Get_Rect(), &m_rtPlayerRectCheck) && dynamic_cast<CPlayer*>(m_pPlayer)->Get_Hide() == false) || m_bFindPlayer)
	{
		if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_Hide() == true)
		{
			m_eCurState = IDLE;
		}
		else if (m_tInfo.fX > m_pPlayer->Get_Info().fX)
		{
			m_bWalk = false;
			m_eLookDir = LOOK_LEFT;
			if (fabsf(m_tInfo.fX - m_pPlayer->Get_Info().fX) < 500.f)
			{
				m_bAttack = true;
				m_eCurState = ATTACK_L;
			}
			else
			{
				m_bAttack = false;
				m_eCurState = RUN_L;
				m_tInfo.fX -= m_fSpeed * 2.f;
			}
		}
		else if (m_tInfo.fX < m_pPlayer->Get_Info().fX)
		{
			m_eLookDir = LOOK_RIGHT;
			if (fabsf(m_tInfo.fX - m_pPlayer->Get_Info().fX) < 500.f)
			{
				m_bAttack = true;
				m_eCurState = ATTACK_R;
			}
			else
			{
				m_bAttack = false;
				m_eCurState = RUN_R;
				m_tInfo.fX += m_fSpeed * 2.f;
			}
		}
		m_bFindPlayer = true;
	}
	else if (!m_bFindPlayer)
	{
		m_bAttack = false;
		m_bWalk = true;
		Walking();
	}

	Graviting();

	if (m_bDead && m_fJumpTime <= 0.f)
	{
		if (m_bHitEffect_1 == false)
		{
			if (m_eLookDir == LOOK_LEFT)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CHitEffect_1>::Create(m_tInfo.fX, m_tInfo.fY - 70.f, DIR_RIGHT));
			}
			else if (m_eLookDir == LOOK_RIGHT)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CHitEffect_1>::Create(m_tInfo.fX, m_tInfo.fY - 70.f, DIR_LEFT));
			}
			m_bHitEffect_1 = true;
		}
	}

	if (!m_bAniStop)
	{
		Attack();
		Motion_Change();
		Move_Frame();
	}

	m_tPlayerCheck = { m_tInfo.fX, m_tInfo.fY, 1200.f, 130.f };
	InfoToRect();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_2::Late_Update(void)
{
	if (m_iAniCount <= 0 && m_bDead)
		m_bAniStop = true;
}

void CMonster_2::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	HDC	hExclamationDC = CBmpMgr::Get_Instance()->Find_Img(L"ENEMY_EXCLAMATION_MARK");
	HDC hQuestionDC = CBmpMgr::Get_Instance()->Find_Img(L"ENEMY_QUESTION_MARK");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_eCurState == DEAD && m_eLookDir == LOOK_LEFT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,				// 복사 받을 위치의 좌표 전달(x,y 순서)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			(int)m_tInfo.fCY,
			hMemDC,												// 비트맵을 가지고 있는 dc	
			1066 - ((int)m_tInfo.fCX * m_tFrame.iFrameStart),		// 1050 부터 0으로
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));										// 제거할 픽셀의 색상
	}
	else if (m_eCurState == RUN_L && m_eLookDir == LOOK_LEFT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,								// 복사 받을 위치의 좌표 전달(x,y 순서)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			(int)m_tInfo.fCY,
			hMemDC,													// 비트맵을 가지고 있는 dc	
			810 - (int)(m_tInfo.fCX * m_tFrame.iFrameStart),		// 1680 부터 0으로
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));										// 제거할 픽셀의 색상
	}
	else
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,					// 복사 받을 위치의 좌표 전달(x,y 순서)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,							// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			(int)m_tInfo.fCY,
			hMemDC,										// 비트맵을 가지고 있는 dc
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,	// 출력할 비트맵 시작 좌표(x,y 순서)
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,							// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));							// 제거할 픽셀의 색상
	}

	if (!m_bDead)
	{
		if (m_bFindPlayer && dynamic_cast<CPlayer*>(m_pPlayer)->Get_Hide() == true)
		{
			GdiTransparentBlt(hDC,
				m_tRect.left + iScrollX + 20,					// 복사 받을 위치의 좌표 전달(x,y 순서)
				m_tRect.top + iScrollY - 20,
				23,							// 복사 받을 이미지의 길이 전달(가로, 세로순서)
				34,
				hQuestionDC,										// 비트맵을 가지고 있는 dc
				0,	// 출력할 비트맵 시작 좌표(x,y 순서)
				0,
				23,							// 복사 할 비트맵 의 가로, 세로 사이즈
				34,
				RGB(255, 0, 255));							// 제거할 픽셀의 색상
		}
		else if (m_bFindPlayer)
		{
			GdiTransparentBlt(hDC,
				m_tRect.left + iScrollX + 20,					// 복사 받을 위치의 좌표 전달(x,y 순서)
				m_tRect.top + iScrollY - 20,
				6,							// 복사 받을 이미지의 길이 전달(가로, 세로순서)
				34,
				hExclamationDC,										// 비트맵을 가지고 있는 dc
				0,	// 출력할 비트맵 시작 좌표(x,y 순서)
				0,
				6,							// 복사 할 비트맵 의 가로, 세로 사이즈
				34,
				RGB(255, 0, 255));							// 제거할 픽셀의 색상
		}
	}
}

void CMonster_2::Release(void)
{
}

void CMonster_2::Graviting(void)
{
	float	fY = 0;
	float	fX = m_tInfo.fX;

	m_bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (m_bJump)
	{
		if (m_eLookDir == LOOK_LEFT)
		{
			m_tInfo.fX += 10.f;
			m_tInfo.fY -= m_fJumpPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
		}
		else
		{
			m_tInfo.fX -= 10.f;
			m_tInfo.fY -= m_fJumpPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
		}
		m_fJumpTime += 0.2f;

		if (m_bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (m_bLineCol)
	{
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;

	}
	else
	{
		m_tInfo.fY -= 5.f;
	}
}

void CMonster_2::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iMotion = m_eLookDir;
		switch (m_eCurState)
		{
		case IDLE:
			m_pFrameKey = L"ENEMY_COP_IDLE";
			m_tInfo.fCX = 72.f;
			m_tInfo.fCY = 74.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_L:
			m_pFrameKey = L"ENEMY_COP_WALK";
			m_tInfo.fCX = 54.f;
			m_tInfo.fCY = 76.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_R:
			m_pFrameKey = L"ENEMY_COP_WALK";
			m_tInfo.fCX = 54.f;
			m_tInfo.fCY = 76.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case RUN_L:
			m_pFrameKey = L"ENEMY_COP_RUN";
			m_tInfo.fCX = 90.f;
			m_tInfo.fCY = 80.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case RUN_R:
			m_pFrameKey = L"ENEMY_COP_RUN";
			m_tInfo.fCX = 90.f;
			m_tInfo.fCY = 80.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK_L: 
			m_pFrameKey = L"ENEMY_COP_IDLE";
			m_tInfo.fCX = 72.f;
			m_tInfo.fCY = 74.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK_R: 
			m_pFrameKey = L"ENEMY_COP_IDLE";
			m_tInfo.fCX = 72.f;
			m_tInfo.fCY = 74.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEAD:
			m_pFrameKey = L"ENEMY_COP_DEAD";
			m_tInfo.fCX = 82.f;
			m_tInfo.fCY = 68.f;
			m_iAniCount = 13;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.dwFrameSpeed = 150;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CMonster_2::Attack(void)
{
	if (m_bAttack && m_bFindPlayer)
	{
		if (m_eLookDir == LOOK_LEFT)
		{
			m_eCurState = ATTACK_L;
		}
		else if (m_eLookDir == LOOK_RIGHT)
		{
			m_eCurState = ATTACK_R;
		}
		if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_Hide() == false)
		{
			if (m_dwOldTime + 3000 < GetTickCount())
			{
				if (m_eLookDir == LOOK_LEFT)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CGunSparkEffect>::Create(m_tInfo.fX - 60.f, m_tInfo.fY - 10.f, DIR_LEFT));
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET_ENEMY, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
				}
				else if (m_eLookDir == LOOK_RIGHT)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CGunSparkEffect>::Create(m_tInfo.fX + 60.f, m_tInfo.fY - 10.f, DIR_RIGHT));
					CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET_ENEMY, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));
				}
				m_dwOldTime = GetTickCount();
			}
		}
	}
}

void CMonster_2::Walking(void)
{
	if (m_bWalk)
	{
		m_fWalkCount += m_fSpeed;
		if (m_fWalkCount < 150.f)
		{
			m_eLookDir = LOOK_LEFT;
			m_eCurState = WALK_L;
			m_tInfo.fX -= m_fSpeed;
		}
		else if (m_fWalkCount > 150.f)
		{
			m_eLookDir = LOOK_RIGHT;
			m_eCurState = WALK_R;
			m_tInfo.fX += m_fSpeed;
			if (m_fWalkCount > 300.f)
				m_fWalkCount = 0.f;
		}
	}
}

void CMonster_2::InfoToRect()
{
	m_rtPlayerRectCheck.left = LONG(m_tPlayerCheck.fX - (m_tPlayerCheck.fCX * 0.5f));
	m_rtPlayerRectCheck.top = LONG(m_tPlayerCheck.fY - (m_tPlayerCheck.fCY * 0.5f));
	m_rtPlayerRectCheck.right = LONG(m_tPlayerCheck.fX + (m_tPlayerCheck.fCX * 0.5f));
	m_rtPlayerRectCheck.bottom = LONG(m_tPlayerCheck.fY + (m_tPlayerCheck.fCY * 0.5f));
}


bool CMonster_2::Check_Sphere(CObj* pDest, INFO* pSour)
{
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->fCX) * 0.5f;

	return fRadius >= fDiagonal;
}
