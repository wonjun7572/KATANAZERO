#include "stdafx.h"
#include "Boss.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "GroundLazer.h"
#include "AirLazer.h"
#include "SoundMgr.h"
#include "BossBullet.h"
#include "SceneMgr.h"
#include "BossHead.h"
#include "HitEffect_1.h"

float	g_BossEffectSound = 1.f;
CBoss::CBoss()
	: m_eCurState(STATE_BOSS::IDLE), m_ePreState(STATE_BOSS::MOTION_END)
{
}

CBoss::~CBoss()
{
	Release();
}

void CBoss::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 44.f, 88.f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_headhunter_idle_12x2.bmp", L"BOSS_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_teleport_ground_8x2.bmp", L"BOSS_GROUND_ATTACK");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_teleport_8x2.bmp", L"BOSS_TELEPORT_ATTACK");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_wallgrab_3x2.bmp", L"BOSS_WALL_GRAB");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_walljump_7x2.bmp", L"BOSS_WALL_ATTACK");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_dieground_8x2.bmp", L"BOSS_DEAD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_dead_19x2.bmp", L"BOSS_DEAD_AFTER");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_headhunter_hurt_recover_10x2.bmp", L"BOSS_HURT_RECOVER");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_in_pattern_4x2.bmp", L"BOSS_PATTERN");

	m_pTexture = Gdiplus::Bitmap::FromFile(L"../image/boss/boss_nohead_6x2.bmp");

	Gdiplus::Color Magenta(255, 0, 255);
	Gdiplus::Color Alpha(0, 0, 0, 0);

	for (UINT i = 0; i < m_pTexture->GetHeight(); ++i)
	{
		for (UINT j = 0; j < m_pTexture->GetWidth(); ++j)
		{
			Gdiplus::Color color;
			m_pTexture->GetPixel(j, i, &color);

			if (color.GetR() == 255 && color.GetG() == 0 && color.GetB() == 255)
				m_pTexture->SetPixel(j, i, Alpha);
			else
				m_pTexture->SetPixel(j, i, Gdiplus::Color::Black);
		}
	}


	m_pFrameKey = L"BOSS_IDLE";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iMotion = m_eLookDir;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	for (int i = 0; i < 20; ++i)
	{
		m_dwAttackTimer[i] = GetTickCount();
	}
	m_dwHitTimer = GetTickCount();

	m_fSpeed = 0.5f;
	m_eRenderGroup = ENEMY;
	m_dwResetTimer = GetTickCount();
}

int CBoss::Update(void)
{
	if (m_pPlayer == nullptr)
		m_pPlayer = CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->front();

	Reset();

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS && m_bDown == false)
	{
		if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_EnvState() == GROUND)
		{
			m_bReset = false;
			m_eEevState = GROUND;
			m_bDown = true;
			m_bPatternFinish = false;
		}
	}

	if (m_iHp <= 2 && g_iFinished == 0)
	{
		m_bReset = true;

		if (m_dwResetTimer + 2000 < GetTickCount())
		{
			if (!m_tInfoList.empty())
			{
				m_tInfo.fX = m_tInfoList.back().fX;
				m_tInfo.fY = m_tInfoList.back().fY;
				m_tInfoList.pop_back();
			}

			if (!m_ePreStateList.empty())
			{
				m_eCurState = m_ePreStateList.back();
				m_ePreStateList.pop_back();
			}

			if (!m_tFrameList.empty())
			{
				m_tFrame.iFrameStart = m_tFrameList.back().iFrameStart;
				m_tFrame.iMotion = m_tFrameList.back().iMotion;
				m_tFrameList.pop_back();
			}

			if (m_tInfoList.empty())
			{
				m_bReset = false;
				EnvCheck();
			}
		}

		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->BackToPast();
	
		if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_List().empty())
		{
			m_bDead = false;
			if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS)
			{
				Set_ListClear();
			}
		}
	}
	else if (m_iHp <= 0)
	{
		if (!m_bDead)
		{
			m_eCurState = STATE_BOSS::BOSS_DEAD;
			m_bDead = true;
		}

		Motion_Change();
		Move_Frame();

		if (!m_bRealDead)
		{
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_eCurState = STATE_BOSS::BOSS_DEAD_AFTER;
				m_dwTimer = GetTickCount();
			}

			if (m_eCurState == STATE_BOSS::BOSS_DEAD_AFTER)
			{
				if (m_tInfo.fX < WINCX / 2)
				{
						m_eLookDir = LOOK_LEFT;
						m_tInfo.fX -= m_fSpeed * 0.5f;
				}
				else
				{
						m_eLookDir = LOOK_RIGHT;
						m_tInfo.fX += m_fSpeed * 0.5f;
				}
			}
		}
		else
		{
			m_eCurState = STATE_BOSS::BOSS_NO_HEAD;
			if (m_eLookDir == LOOK_LEFT)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CHitEffect_1>::Create(m_tInfo.fX, m_tInfo.fY - 30.f, DIR_RIGHT));
			}
			else
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CHitEffect_1>::Create(m_tInfo.fX + 40.f, m_tInfo.fY - 30.f, DIR_LEFT));
			}

			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				m_bFinished = true;
			}
		}
	
		m_eEevState = FINISH;
		EnvCheck();
		Update_Rect();
		return 0;
	}

	if (m_pPlayer != nullptr)
	{
		if (m_tInfo.fX > m_pPlayer->Get_Info().fX)
			m_eLookDir = LOOK_LEFT;
		else if (m_tInfo.fX < m_pPlayer->Get_Info().fX)
			m_eLookDir = LOOK_RIGHT;
	}
	
	if (!m_bStart)
	{
		m_eEevState = GROUND;
		m_eCurState = STATE_BOSS::IDLE;
		m_bGroundAttack = true;
		m_bStart = true;
	}

	if (!m_bReset)
	{
		if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_PRE_STAGE_BOSS)
		{
			if (!m_bPatternFinish && m_bStart &&  m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"teleport.wav", SOUND_BOSS, g_BossEffectSound);
				m_eCurState = STATE_BOSS::BOSS_PATTERN_IN;
				m_eEevState = GROUND;
				EnvCheck();
				m_eEevState = BOSS_PATTERN;
				m_bPatternFinish = true;
			}
			else	if (m_dwAttackTimer[2] + 1500 < GetTickCount() && m_bWallAttack  && m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_bPatternFinish && m_eEevState == BOSS_PATTERN && m_iAniCount <= 1)
			{
				WallAttack();
				m_dwAttackTimer[2] = GetTickCount();
			}
			else if (m_dwAttackTimer[1] + 1000 < GetTickCount() && m_bTeleportAttack && m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_bPatternFinish && m_eEevState == BOSS_PATTERN&& m_iAniCount <= 1)
			{
				AirAttack();
				m_dwAttackTimer[1] = GetTickCount();
			}
			else if (m_dwAttackTimer[0] + 500 < GetTickCount() && m_bGroundAttack && m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_bPatternFinish && m_eEevState == BOSS_PATTERN && m_iAniCount <= 1)
			{
				int i = rand() % 2 + 1;
				GroundAttack(i);
				m_dwAttackTimer[0] = GetTickCount();
			}
		}
		else
		{
			if (!m_bPatternFinish && m_bStart &&  m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"teleport.wav", SOUND_BOSS, g_BossEffectSound);
				m_eCurState = STATE_BOSS::BOSS_PATTERN_IN;
				m_eEevState = GROUND;
				EnvCheck();
				m_eEevState = BOSS_PATTERN;
				m_bPatternFinish = true;
			}
			else	if (m_dwAttackTimer[2] + 1500 < GetTickCount() && m_bWallAttack  && m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_bPatternFinish && m_eEevState == BOSS_PATTERN && m_iAniCount <= 1)
			{
				WallAttack();
				m_dwAttackTimer[2] = GetTickCount();
			}
			else if (m_dwAttackTimer[1] + 1000 < GetTickCount() && m_bTeleportAttack && m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_bPatternFinish && m_eEevState == BOSS_PATTERN&& m_iAniCount <= 1)
			{
				AirAttack();
				m_dwAttackTimer[1] = GetTickCount();
			}
			else if (m_dwAttackTimer[0] + 500 < GetTickCount() && m_bGroundAttack && m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_bPatternFinish && m_eEevState == BOSS_PATTERN && m_iAniCount <= 1)
			{
				int i = rand() % 2 + 1;
				GroundAttack(i);
				m_dwAttackTimer[0] = GetTickCount();
			}
		}
	}

	EnvCheck();
	Motion_Change();
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBoss::Late_Update(void)
{
	if (!m_bDead)
	{
		if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_SWORD)->empty())
		{
			for (auto iter : *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SWORD))
			{
				if (Check_Sphere(iter, &m_tInfo))
				{
					if (m_dwHitTimer + 300 < GetTickCount())
					{
						m_iHp--;
						m_eCurState = STATE_BOSS::HURT_RECOVER;
						m_dwHitTimer = GetTickCount();
					}
				}
			}
		}
	}
	else
	{
		if (m_dwTimer + 3000 < GetTickCount())
		{
			if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_SWORD)->empty())
			{
				for (auto iter : *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SWORD))
				{
					if (Check_Sphere(iter, &m_tInfo))
					{
						m_bRealDead = true;
						m_eCurState = STATE_BOSS::BOSS_NO_HEAD;
					}
				}
			}
		}
	}
}

void CBoss::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_eCurState == BOSS_NO_HEAD)
	{
		if (!m_bFinished)
		{
			if (m_pGraphics == nullptr)
				m_pGraphics = Gdiplus::Graphics::FromHDC(hDC);

			if (m_eLookDir == LOOK_LEFT)
			{
				if (!m_bBossHead)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossHead>::Create(m_tInfo.fX - 80.f, m_tInfo.fY +15.f, DIR_LEFT));
					m_bBossHead = true;
				}
				m_pGraphics->DrawImage(m_pTexture,
					m_tRect.left + iScrollX, m_tRect.top + iScrollY,
					600 - (int)m_tInfo.fCX * m_tFrame.iFrameStart,
					(int)m_tInfo.fCY * m_tFrame.iMotion,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					UnitPixel);
			}
			else
			{
				if (!m_bBossHead)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossHead>::Create(m_tInfo.fX + 80.f, m_tInfo.fY + 15.f, DIR_RIGHT));
					m_bBossHead = true;
				}
				m_pGraphics->DrawImage(m_pTexture,
					m_tRect.left + iScrollX, m_tRect.top + iScrollY,
					(int)m_tInfo.fCX * m_tFrame.iFrameStart,
					(int)m_tInfo.fCY * m_tFrame.iMotion,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					UnitPixel);
			}
		}
		else
		{
			if (m_pGraphics == nullptr)
				m_pGraphics = Gdiplus::Graphics::FromHDC(hDC);

			if (m_eLookDir == LOOK_LEFT)
			{
				m_pGraphics->DrawImage(m_pTexture,
					m_tRect.left + iScrollX, m_tRect.top + iScrollY,
					600 - (int)m_tInfo.fCX * m_tFrame.iFrameEnd,
					(int)m_tInfo.fCY * m_tFrame.iMotion,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					UnitPixel);
			}
			else
			{
				m_pGraphics->DrawImage(m_pTexture,
					m_tRect.left + iScrollX, m_tRect.top + iScrollY,
					(int)m_tInfo.fCX * m_tFrame.iFrameEnd,
					(int)m_tInfo.fCY * m_tFrame.iMotion,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					UnitPixel);
			}
		}

		return;
	}

	if (m_eCurState == STATE_BOSS::GROUND_ANI && m_eLookDir == LOOK_LEFT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,											// 복사 받을 위치의 좌표 전달(x,y 순서)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,													// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			(int)m_tInfo.fCY,
			hMemDC,																// 비트맵을 가지고 있는 dc
			574 - (int)m_tInfo.fCX * m_tFrame.iFrameStart,						// 출력할 비트맵 시작 좌표(x,y 순서)
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,													// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));													// 제거할 픽셀의 색상
	}
	else if (m_eCurState == STATE_BOSS::TELEPORT_ANI && m_eLookDir == LOOK_LEFT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			392 - (int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	else if (m_eCurState == STATE_BOSS::BOSS_DEAD && m_eLookDir == LOOK_LEFT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			812 - (int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	else if (m_eCurState == STATE_BOSS::HURT_RECOVER && m_eLookDir == LOOK_LEFT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			1260 - (int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	else if (m_eCurState == STATE_BOSS::BOSS_PATTERN_IN && m_eLookDir == LOOK_LEFT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			216 - (int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	else
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	

}

void CBoss::Release(void)
{
}

void CBoss::EnvCheck(void)
{
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &m_fFootY);

	switch (m_eEevState)
	{
	case AIR:
		m_tInfo.fY -= m_fCurJumpSpeed;
		if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
			m_fCurJumpSpeed -= GRAVITY;
		m_bJump = true;
		break;

	case GROUND_DOWN:
		m_tInfo.fY -= m_fCurJumpSpeed * 0.7f;
		if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
			m_fCurJumpSpeed -= GRAVITY;
		break;

	case GROUND:
		m_fCurJumpSpeed = 0.f;
		m_tInfo.fY = m_fFootY - m_tInfo.fCY * 0.5f;
		m_bJump = false;
		m_bWallJump = false;
		m_iWallJumpCnt = 0;
		break;

	case FINISH:
		m_fCurJumpSpeed = 0.f;
		m_tInfo.fY = m_fFootY - m_tInfo.fCY * 0.5f;
		m_bJump = false;
		m_bWallJump = false;
		m_iWallJumpCnt = 0;
		break;

	case BOSS_PATTERN:
		break;

	default:
		break;
	}
}

void CBoss::Motion_Change()
{
	m_tFrame.iMotion = m_eLookDir;
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE_BOSS::IDLE:
			m_pFrameKey = L"BOSS_IDLE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case STATE_BOSS::GROUND_ANI:
			m_pFrameKey = L"BOSS_GROUND_ATTACK";
			m_tInfo.fCX = 82.f;
			m_tInfo.fCY = 70.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case STATE_BOSS::TELEPORT_ANI:
			if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_PRE_STAGE_BOSS)
			{
				m_tInfo.fY = 400.f;
			}
			else
			{
				m_tInfo.fY = 200.f;
			}
			m_pFrameKey = L"BOSS_TELEPORT_ATTACK";
			m_tInfo.fCX = 56.f;
			m_tInfo.fCY = 90.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case STATE_BOSS::WALL_ANI:
			if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_PRE_STAGE_BOSS)
			{
				m_tInfo.fY = 400.f;
			}
			else
			{
				m_tInfo.fY = 200.f;
			}
			m_pFrameKey = L"BOSS_WALL_ATTACK";
			m_tInfo.fCX = 108.f;
			m_tInfo.fCY = 124.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case STATE_BOSS::WALL_GRAB:
			if (m_tInfo.fX <= 640.f)
			{
				m_tInfo.fX = 148.f;
				m_tFrame.iMotion = 1;
			}
			else
			{
				m_tInfo.fX = 1183.f;
				m_tFrame.iMotion = 0;
			}
			m_tInfo.fY = 300.f;
			m_pFrameKey = L"BOSS_WALL_GRAB";
			m_tInfo.fCX = 60.f;
			m_tInfo.fCY = 86.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case STATE_BOSS::HURT_RECOVER:
			m_pFrameKey = L"BOSS_HURT_RECOVER";
			m_tInfo.fCX = 140.f;
			m_tInfo.fCY = 106.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case STATE_BOSS::BOSS_DEAD_AFTER:
			m_pFrameKey = L"BOSS_DEAD_AFTER";
			if (m_eLookDir == LOOK_LEFT)
				m_eLookDir = LOOK_RIGHT;
			else
				m_eLookDir = LOOK_LEFT;
			m_tInfo.fCX = 112.f;
			m_tInfo.fCY = 42.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 18;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case STATE_BOSS::BOSS_DEAD:
			m_pFrameKey = L"BOSS_DEAD";
			if (m_eLookDir == LOOK_LEFT)
				m_eLookDir = LOOK_RIGHT;
			else
				m_eLookDir = LOOK_LEFT;
			m_tFrame.iMotion = m_eLookDir;
			m_tInfo.fCX = 116.f;
			m_tInfo.fCY = 82.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case STATE_BOSS::BOSS_PATTERN_IN:
			m_pFrameKey = L"BOSS_PATTERN";
			m_tFrame.iMotion = m_eLookDir;
			m_iAniCount = 6;
			m_tInfo.fCX = 72.f;
			m_tInfo.fCY = 62.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case STATE_BOSS::BOSS_NO_HEAD:
			m_tFrame.iMotion = m_eLookDir;
			m_iAniCount = 4;
			m_tInfo.fCX = 120.f;
			m_tInfo.fCY = 44.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameSpeed = 500;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

bool CBoss::Check_Sphere(CObj* pDest, INFO* pSour)
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

void CBoss::GroundAttack(int _dir)
{
	CSoundMgr::Get_Instance()->PlaySound(L"aimground.wav", SOUND_BOSS2, g_BossEffectSound);
	m_eEevState = GROUND;
	m_eCurState = STATE_BOSS::GROUND_ANI;
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_PRE_STAGE_BOSS)
	{
		if (_dir == 1)
		{
			m_tInfo.fX = 1215.f;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CGroundLazer>::Create(465.f - m_tInfo.fCX * 0.5f, 730.f));
			CSoundMgr::Get_Instance()->PlaySound(L"lazer.wav", SOUND_BOSS, g_BossEffectSound);
		}
		else if (_dir == 2)
		{
			m_tInfo.fX = 375.f;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CGroundLazer>::Create(1125.f + m_tInfo.fCX * 0.5f, 730.f));
			CSoundMgr::Get_Instance()->PlaySound(L"lazer.wav", SOUND_BOSS, g_BossEffectSound);
		}
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS)
	{
		if (_dir == 1)
		{
			m_tInfo.fX = 1070.f;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CGroundLazer>::Create(1070.f - 750.f - m_tInfo.fCX * 0.5f, 520.f));
			CSoundMgr::Get_Instance()->PlaySound(L"lazer.wav", SOUND_BOSS, g_BossEffectSound);
		}
		else if (_dir == 2)
		{
			m_tInfo.fX = 270.f;
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CGroundLazer>::Create(270.f + 750.f + m_tInfo.fCX * 0.5f, 520.f));
			CSoundMgr::Get_Instance()->PlaySound(L"lazer.wav", SOUND_BOSS, g_BossEffectSound);
		}
	}
	m_bTeleportAttack = true;
	m_bGroundAttack = false;
	m_bWallAttack = false;
	m_bPatternFinish = false;
	m_dwAttackTimer[2] = GetTickCount();
}

void CBoss::AirAttack()
{
	int iSpotX = 0;

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_PRE_STAGE_BOSS)
		iSpotX = rand() % 1115 + 235;
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS)
		iSpotX = rand() % 910 + 210;

	CSoundMgr::Get_Instance()->PlaySound(L"aimtop.wav", SOUND_BOSS2, g_BossEffectSound);
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_PRE_STAGE_BOSS)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CAirLazer>::Create((float)iSpotX, 400.f + 750.f + m_tInfo.fCY * 0.5f));
		CSoundMgr::Get_Instance()->PlaySound(L"lazer.wav", SOUND_BOSS, g_BossEffectSound);
	}
	else
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CAirLazer>::Create((float)iSpotX, 200.f + 750.f + m_tInfo.fCY * 0.5f));
		CSoundMgr::Get_Instance()->PlaySound(L"lazer.wav", SOUND_BOSS, g_BossEffectSound);
	}
	m_tInfo.fX = (float)iSpotX;
	m_eCurState = STATE_BOSS::TELEPORT_ANI;
	m_bWallAttack = true;
	m_bTeleportAttack = false;
	m_bGroundAttack = false;
	m_bPatternFinish = false;
	m_dwAttackTimer[1] = GetTickCount();
	m_dwAttackTimer[3] = GetTickCount();
}

void CBoss::WallAttack()
{
	CSoundMgr::Get_Instance()->PlaySound(L"shoot.wav", SOUND_BOSS, g_BossEffectSound);

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_PRE_STAGE_BOSS)
	{
		m_tInfo.fX = 810;
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, -9.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, -18.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, -27.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, -36.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, -45.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, -54.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, -63.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, -72.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, -81.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, -90.f));
																								   
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, 180.f + 9.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, 180.f + 18.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, 180.f + 27.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, 180.f + 36.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, 180.f + 45.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, 180.f + 54.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, 180.f + 63.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, 180.f + 72.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(810, 400, DIR_END, 180.f + 81.f));
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS)
	{
		m_tInfo.fX = 670;
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, -9.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, -18.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, -27.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, -36.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, -45.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, -54.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, -63.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, -72.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, -81.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, -90.f));

		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, 180.f + 9.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, 180.f + 18.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, 180.f + 27.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, 180.f + 36.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, 180.f + 45.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, 180.f + 54.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, 180.f + 63.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, 180.f + 72.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBossBullet>::Create(670, 200, DIR_END, 180.f + 81.f));
	}

	m_eCurState = STATE_BOSS::WALL_ANI;
	m_bGroundAttack = true;
	m_bTeleportAttack = false;
	m_bWallAttack = false;
	m_bPatternFinish = false;
	m_dwAttackTimer[0] = GetTickCount();
}

void CBoss::Reset(void)
{
	if (m_bReset == false)
	{
		if (m_tInfoList.empty())
		{
			m_tInfoList.push_back(m_tInfo);
			m_ePreStateList.push_back(m_eCurState);
			m_tFrameList.push_back(m_tFrame);
		}
		else if (m_tInfoList.back().fX != m_tInfo.fX || m_ePreStateList.back() != m_eCurState || m_tInfoList.back().fY != m_tInfo.fY || m_tInfoList.back().fCX != m_tInfo.fCX )
		{
			m_tInfoList.push_back(m_tInfo);
			m_ePreStateList.push_back(m_eCurState);
			m_tFrameList.push_back(m_tFrame);
		}
	}
}