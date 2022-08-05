#include "stdafx.h"
#include "Shadow.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "BitMap.h"

CShadow::CShadow()
{
}


CShadow::~CShadow()
{
	Release();
}

void CShadow::Initialize(void)
{
	m_tInfo = { 0,0,70.f, 70.f };
	m_eRenderGroup = ENEMY;
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_fall_shadow_4x2.bmp", L"PLAYER_FALL_SHADOW");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_flip_shadow_11x2.bmp", L"PLAYER_FLIP_SHADOW");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_roll_shadow_7x2.bmp", L"PLAYER_ROLL_SHADOW");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_attack_shadow_7x21.bmp", L"PLAYER_ATTACK_SHADOW");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_jump_shadow_4x2.bmp", L"PLAYER_JUMP_SHADOW");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_run_shadow_10x2.bmp", L"PLAYER_RUN_SHADOW");
	m_BlendFunction.BlendOp = AC_SRC_OVER;
	m_BlendFunction.BlendFlags = 0;
	m_BlendFunction.AlphaFormat = 0;
	
	m_OldTime = GetTickCount();
}

int CShadow::Update(void)
{
	m_BlendFunction.SourceConstantAlpha--;

	if(!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
		m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	
	if (m_pPlayer != nullptr)
	{
		if (m_OldTime + m_PlusTime < GetTickCount())
		{
			m_tInfo.fX = m_pPlayer->Get_Info().fX;
			m_tInfo.fY = m_pPlayer->Get_Info().fY;
			m_tInfo.fCX = m_pPlayer->Get_Info().fCX;
			m_tInfo.fCY = m_pPlayer->Get_Info().fCY;
			m_eCurState = dynamic_cast<CPlayer*>(m_pPlayer)->Get_CurState();
			m_eLookDir = dynamic_cast<CPlayer*>(m_pPlayer)->Get_playerLook();
			m_OldTime = GetTickCount();
		}
	}

	Motion_Change();
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CShadow::Late_Update(void)
{
}

void CShadow::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	
	HDC AlphaDC = CreateCompatibleDC(hMemDC);
	HBITMAP TempDC = CreateCompatibleBitmap(hMemDC, WINCX, WINCY);
	HBITMAP	OldTempDC = (HBITMAP)SelectObject(AlphaDC, TempDC);
	m_BlendFunction.SourceConstantAlpha = m_iAlpha; // 0 ~ 255
	
	if (!m_bRender)
	{ 
		GdiTransparentBlt(AlphaDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));

		GdiTransparentBlt(AlphaDC, 
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

		GdiAlphaBlend(hDC,
			m_tRect.left + iScrollX, 
			m_tRect.top + iScrollY, 
			(int)m_tInfo.fCX, 
			(int)m_tInfo.fCY, AlphaDC, 
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX, 
			(int)m_tInfo.fCY,
			m_BlendFunction);
	}
	DeleteObject(SelectObject(AlphaDC, OldTempDC));
	DeleteDC(AlphaDC);
}

void CShadow::Release(void)
{
}

void CShadow::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iMotion = m_eLookDir;
		switch (m_eCurState)
		{
		case RUN:
			m_bRender = false;
			m_pFrameKey = L"PLAYER_RUN_SHADOW";
			m_iAniCount = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case JUMP:
			m_bRender = false;
			m_pFrameKey = L"PLAYER_JUMP_SHADOW";
			m_iAniCount = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case FALL:
			m_bRender = false;
			m_pFrameKey = L"PLAYER_FALL_SHADOW";
			m_iAniCount = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK:
			m_bRender = false;
			m_pFrameKey = L"PLAYER_ATTACK_SHADOW";
			m_iAniCount = 6;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case FLIP:
			m_bRender = false;
			m_pFrameKey = L"PLAYER_FLIP_SHADOW";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case GRAB_WALL:
			m_bRender = false;
			m_pFrameKey = L"PLAYER_GRAB_WALL";
			m_iAniCount = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ROLL:
			m_bRender = false;
			m_pFrameKey = L"PLAYER_ROLL_SHADOW";
			m_iAniCount = 6;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		default:
			m_bRender = true;
			break;
		}
		m_ePreState = m_eCurState;
	}
}
