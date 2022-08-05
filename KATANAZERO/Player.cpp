#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "SwordEffect.h"
#include "SwordBox.h"
#include "Shadow.h"
#include "DustEffect.h"
#include "JumpDustEffect.h"
#include "Knife.h"
#include "Bottle.h"
#include "Smoke.h"
#include "KnifeUI.h"
#include "BackToPastEffect.h"
#include "Curtain.h"
#include "Boss.h"

float	g_fPlaySound = 1.f;

CPlayer::CPlayer()
	: m_eCurState(IDLE), m_ePreState(MOTION_END), m_bReset(false)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 100.f, 650.f, 70.f, 70.f };
	m_fSpeed = 10.f;
	m_fDiagonal = 100.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_idle_11x2.bmp", L"PLAYER_IDLE"); // IDLE 상태
	m_pFrameKey = L"PLAYER_IDLE";

	m_pTexture[0] = Gdiplus::Bitmap::FromFile(L"../image/player/player_idle_11x2.bmp");
	m_pTexture[1] = Gdiplus::Bitmap::FromFile(L"../image/player/player_run_10x2.bmp");
	m_pTexture[2] = Gdiplus::Bitmap::FromFile(L"../image/player/player_jump_4x2.bmp");
	m_pTexture[3] = Gdiplus::Bitmap::FromFile(L"../image/player/player_fall_4x2.bmp");
	m_pTexture[4] = Gdiplus::Bitmap::FromFile(L"../image/player/player_run_to_idle_5x2.bmp");
	m_pTexture[5] = Gdiplus::Bitmap::FromFile(L"../image/player/player_idle_to_run_4x2.bmp");
	m_pTexture[6] = Gdiplus::Bitmap::FromFile(L"../image/player/player_attack_7x2.bmp");
	m_pTexture[7] = Gdiplus::Bitmap::FromFile(L"../image/player/player_roll_7x2.bmp");
	m_pTexture[8] = Gdiplus::Bitmap::FromFile(L"../image/player/player_hurtground_6x2.bmp");
	m_pTexture[9] = Gdiplus::Bitmap::FromFile(L"../image/player/player_grab_wall_4x2.bmp");
	m_pTexture[10] = Gdiplus::Bitmap::FromFile(L"../image/player/player_flip_11x2.bmp");

	m_pTexture_BossDead[0] = Gdiplus::Bitmap::FromFile(L"../image/player/player_idle_11x2.bmp");
	m_pTexture_BossDead[1] = Gdiplus::Bitmap::FromFile(L"../image/player/player_attack_7x2.bmp");

	Gdiplus::Color Magenta(255, 0, 255);
	Gdiplus::Color Alpha(0, 0, 0, 0);

	for (int k = 0; k < 11; ++k)
	{
		for (UINT i = 0; i < m_pTexture[k]->GetHeight(); ++i)
		{
			for (UINT j = 0; j < m_pTexture[k]->GetWidth(); ++j)
			{
				Gdiplus::Color color;
				m_pTexture[k]->GetPixel(j, i, &color);

				if (color.GetR() == 255 && color.GetG() == 0 && color.GetB() == 255)
					m_pTexture[k]->SetPixel(j, i, Alpha);
				else
					m_pTexture[k]->SetPixel(j, i, Gdiplus::Color::Gray);
			}
		}
	}

	for (int k = 0; k < 2; ++k)
	{
		for (UINT i = 0; i < m_pTexture_BossDead[k]->GetHeight(); ++i)
		{
			for (UINT j = 0; j < m_pTexture_BossDead[k]->GetWidth(); ++j)
			{
				Gdiplus::Color color;
				m_pTexture_BossDead[k]->GetPixel(j, i, &color);

				if (color.GetR() == 255 && color.GetG() == 0 && color.GetB() == 255)
					m_pTexture_BossDead[k]->SetPixel(j, i, Alpha);
				else
					m_pTexture_BossDead[k]->SetPixel(j, i, Gdiplus::Color::Black);
			}
		}
	}

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_eLookDir = LOOK_RIGHT;
	m_tFrame.iMotion = m_eLookDir;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	//Player
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_run_10x2.bmp", L"PLAYER_RUN"); // RUN 상태
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_jump_4x2.bmp", L"PLAYER_JUMP"); // JUMP 상태
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_fall_4x2.bmp", L"PLAYER_FALL"); // JUMP 끝 상태
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_run_to_idle_5x2.bmp", L"PLAYER_RUNTOIDLE"); // RUNTOIDLE 상태
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_idle_to_run_4x2.bmp", L"PLAYER_IDLETORUN"); // IDLETORUN 상태
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_attack_7x2.bmp", L"PLAYER_ATTACK");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_roll_7x2.bmp", L"PLAYER_ROLL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_hurtground_6x2.bmp", L"PLAYER_GROUND_DEAD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/crouch.bmp", L"PLAYER_CROUCH");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_grab_wall_4x2.bmp", L"PLAYER_GRAB_WALL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_flip_11x2.bmp", L"PLAYER_FLIP");

	//Cursor
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player_aim.bmp", L"PLAYER_AIM");

	m_eRenderGroup = GAMEOBJECT;

	m_pt = {};
	ShowCursor(false);
	m_iPass = 1;
}

int CPlayer::Update(void)
{
	// 마우스
	// tan 나와 마우스포인터와의 각도 0~180  -180~0
	GetCursorPos(&m_pt);
	ScreenToClient(g_hWnd, &m_pt);
	m_pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	m_pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_bSlowInSound)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"slow_in.mp3", SOUND_SLOW_IN, g_fPlaySound);
		m_bSlowInSound = false;
	}

	if (m_bSlowOutSound)
	{	
		CSoundMgr::Get_Instance()->PlaySound(L"slow_out.mp3", SOUND_SLOW_OUT, g_fPlaySound);
		m_bSlowOutSound = false;
	}

	if (m_bDead)
	{
		if (!m_bDeadSound)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"dead.wav", SOUND_PLAYER, g_fPlaySound);
			m_bDeadSound = true;
		}
		m_eCurState = DEAD;
		m_bReset = true;
	}

	Reset();

	if (m_bDead && CKeyMgr::Get_Instance()->Key_Pressing('R'))
	{
		m_bKeyRPressing = true;
	
		BackToPast();
	}

	if (!m_bDead)
	{
		Key_Input();
		CKeyMgr::Get_Instance()->Key_Reset();
	}

	if (m_iShakeCamera < 20)
	{
		m_iShakeCamera++;
		CScrollMgr::Get_Instance()->Set_ScrollX((sinf((float)GetTickCount()) * 10));
		CScrollMgr::Get_Instance()->Set_ScrollY((cosf((float)GetTickCount()) * 10));
	}

	EnvCheck();
	Rolling();
	Attacking();
	WallJumping();
	Motion_Change();
	Move_Frame();
	Update_Rect();
	Offset();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	switch (m_iPass)
	{
	case 1:
		GeneralRender(hDC);
		break;

	case 2:
		AlphaRender(hDC);
		break;
	}
}

void CPlayer::Release(void)
{
	//if(m_pTexture)
	//	delete[] m_pTexture;

	if (m_pGraphics)
		delete m_pGraphics;
}

void CPlayer::Key_Input(void)
{
	if (m_iAniCount <= 0)
	{
		if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->empty())
		{
			Set_Frame(10);
		}
		else if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->empty())
		{
			if (dynamic_cast<CBoss*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front())->Get_RealDead() == true)
			{
				Set_Frame(100);
			}
			else
			{
				Set_Frame(10);
			}
		}
		CSceneMgr::Get_Instance()->Get_Scene()->Set_Slow(false);
	}

	if (m_iAniCount <= 0 && m_eEevState == GROUND)
	{
		m_eCurState = IDLE;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SHIFT))
		m_bSlowInSound = true;
	if (CKeyMgr::Get_Instance()->Key_Up(VK_SHIFT))
		m_bSlowOutSound = true;

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SHIFT))
	{
		Set_Frame(50);
		CSceneMgr::Get_Instance()->Get_Scene()->Set_Slow(true);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S') && m_eEevState == GROUND)
	{
		if (!m_bRoll)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"roll.wav", SOUND_PLAYER, g_fPlaySound);
			m_bRoll = true;
			m_iRollCnt = 0;
			m_eCurState = ROLL;
			m_dwRollWaitTime = GetTickCount();
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('D') && m_eEevState == AIR)
	{
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('A') && m_eEevState == AIR)
	{
		m_tInfo.fX -= cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		if (m_eEevState == GROUND)
		{
			if (!m_bJump)
			{
				m_eCurState = JUMP;
				m_fCurJumpSpeed = m_fInitJumpSpeed;
				m_eEevState = AIR;
				m_fPreFootY = m_tInfo.fY + m_tInfo.fCY * 0.5f;
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CJumpDustEffect>::Create(m_tInfo.fX, m_tInfo.fY));
			}
		}
		else if (m_eEevState == WALL)
		{
			if (!m_bWallJump)
			{
				m_fCurJumpSpeed = m_fInitJumpSpeed;
				m_bWallJump = true;
				m_eEevState = AIR;
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		if (m_eEevState == WALL)
		{
			if (!m_bWallJump)
			{
				m_fCurJumpSpeed = m_fInitJumpSpeed;
				m_bWallJump = true;
				m_eEevState = AIR;
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
#ifdef _DEBUG
		cout << "플레이어 좌표 : " << m_tInfo.fX << "\t" << m_tInfo.fY << endl;
		cout << "마우스  좌표 : " << m_pt.x << "\t" << m_pt.y << endl;
		cout << "환경 조건: " << m_eEevState << endl;
		int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
		int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());
		cout << "스크롤 좌표: " << iScrollX << "\t" << iScrollY;
#endif // _DEBUG
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A') && m_eEevState == GROUND)
	{
		m_eEevState = GROUND;
		m_eLookDir = LOOK_LEFT;
		m_eCurState = IDLETORUN;
	}
	else if (CKeyMgr::Get_Instance()->Key_Up('A') && m_iAniCount <= 1 && m_eEevState == GROUND)
	{
		m_eEevState = GROUND;
		m_eLookDir = LOOK_LEFT;
		m_eCurState = RUNTOIDLE;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A') && m_iAniCount <= 1 && m_eEevState == GROUND)
	{
		m_eEevState = GROUND;
		m_tInfo.fX -= m_fSpeed;
		m_eLookDir = LOOK_LEFT;
		m_eCurState = RUN;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('D') && m_eEevState == GROUND)
	{
		m_eEevState = GROUND;
		m_eLookDir = LOOK_RIGHT;
		m_eCurState = IDLETORUN;
	}
	else if (CKeyMgr::Get_Instance()->Key_Up('D') && m_iAniCount <= 1 && m_eEevState == GROUND)
	{
		m_eEevState = GROUND;
		m_eLookDir = LOOK_RIGHT;
		m_eCurState = RUNTOIDLE;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D') && m_iAniCount <= 1 && m_eEevState == GROUND)
	{
		m_eEevState = GROUND;
		m_tInfo.fX += m_fSpeed;
		m_eLookDir = LOOK_RIGHT;
		m_eCurState = RUN;
	}

	float	fAngle = atan2f((m_tInfo.fY - m_pt.y), (m_tInfo.fX - m_pt.x)) / (PI / 180.f);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		int iRand = rand() % 3;
		if (iRand == 0)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"slash1.wav", SOUND_EFFECT, g_fPlaySound);
		}
		else if (iRand == 1)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"slash2.wav", SOUND_EFFECT, g_fPlaySound);
		}
		else if (iRand == 2)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"slash3.wav", SOUND_EFFECT, g_fPlaySound);
		}
		// tan 나와 마우스포인터와의 각도 0~180  -180~0
		float	fDiagonal = sqrtf((m_tInfo.fCX * 0.5f) * (m_tInfo.fCX * 0.5f) + (m_tInfo.fCY * 0.5f) * (m_tInfo.fCY * 0.5f));
		
		if (!m_bSwordMove)
		{
			if (fAngle >= -90 && fAngle <= 90)
			{
				m_tInfo.fX -= long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((fAngle) * (PI / 180.f)));
			}
			else
			{
				m_tInfo.fX += long((m_tInfo.fCX * 0.5f) - fDiagonal * cosf((fAngle) * (PI / 180.f)));
			}
		}
		

		if (fAngle <= -80.f && fAngle >= -110)
		{
			m_tInfo.fY += 50.f;
		}

		m_bAttack = true;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"throw.wav", SOUND_EFFECT, g_fPlaySound);
		if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM)->empty())
		{
			if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM)->front()->Get_ID() == 1 && m_bItem == true)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_KNIFE, CAbstractFactory<CKnife>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_END, fAngle));
				m_bItem = false;
				CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM)->front()->Kill_Obj();
			}
			else if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM)->front()->Get_ID() == 2 && m_bItem == true)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_BOTTLE, CAbstractFactory<CBottle>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_END, fAngle));
				m_bItem = false;
				CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM)->front()->Kill_Obj();
			}
			else if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM)->front()->Get_ID() == 3 && m_bItem == true)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_SMOKE, CAbstractFactory<CSmoke>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, DIR_END, fAngle));
				m_bItem = false;
				CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM)->front()->Kill_Obj();
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		m_eEevState = GROUND;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('M'))
	{
		m_bDead = true;
	}
}

void CPlayer::Offset(void)
{
	int	iOffsetMinX = 480;
	int	iOffsetMaxX = 600;

	int	iOffsetMinY = 300;
	int	iOffsetMaxY = 500;

	int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
	int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_PRE_STAGE_BOSS || CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS)
	{
		if (iOffsetMinX > m_tInfo.fX + iScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed * 2);

		if (iOffsetMaxX < m_tInfo.fX + iScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed * 2);

		if (iOffsetMinY > m_tInfo.fY + iScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed * 2);

		if (iOffsetMaxY < m_tInfo.fY + iScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed * 2);
	}
	else
	{
		if (iOffsetMinX > m_tInfo.fX + iScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

		if (iOffsetMaxX < m_tInfo.fX + iScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

		if (iOffsetMinY > m_tInfo.fY + iScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

		if (iOffsetMaxY < m_tInfo.fY + iScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
	}
}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iMotion = m_eLookDir;
		if (!m_bDead)
		{
			switch (m_eCurState)
			{
			case IDLE:
				m_pFrameKey = L"PLAYER_IDLE";
				m_tInfo.fCX = 70.f;
				m_tInfo.fCY = 70.f;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.dwFrameSpeed = 200;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case RUN:
				m_pFrameKey = L"PLAYER_RUN";
				m_tInfo.fCX = 88.f;
				m_tInfo.fCY = 64.f;
				m_iAniCount = 1;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 9;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case JUMP:
				m_pFrameKey = L"PLAYER_JUMP";
				m_tInfo.fCX = 60.f;
				m_tInfo.fCY = 84.f;
				m_iAniCount = 3;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case FALL:
				m_pFrameKey = L"PLAYER_FALL";
				m_tInfo.fCX = 82.f;
				m_tInfo.fCY = 86.f;
				m_iAniCount = 3;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case RUNTOIDLE:
				m_pFrameKey = L"PLAYER_RUNTOIDLE";
				m_tInfo.fCX = 80.f;
				m_tInfo.fCY = 70.f;
				m_iAniCount = 4;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 4;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case IDLETORUN:
				m_pFrameKey = L"PLAYER_IDLETORUN";
				m_tInfo.fCX = 84.f;
				m_tInfo.fCY = 64.f;
				m_iAniCount = 3;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case ATTACK:
				m_pFrameKey = L"PLAYER_ATTACK";
				m_tInfo.fCX = 120.f;
				m_tInfo.fCY = 82.f;
				m_iAniCount = 6;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case FLIP:
				m_pFrameKey = L"PLAYER_FLIP";
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 88.f;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 10;
				m_tFrame.dwFrameSpeed = 100;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case GRAB_WALL:
				m_pFrameKey = L"PLAYER_GRAB_WALL";
				m_tInfo.fCX = 78.f;
				m_tInfo.fCY = 100.f;
				m_iAniCount = 3;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.dwFrameSpeed = 200;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case ROLL:
				m_pFrameKey = L"PLAYER_ROLL";
				m_tInfo.fCX = 94.f;
				m_tInfo.fCY = 64.f;
				m_iAniCount = 6;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.dwFrameSpeed = 50;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case HIT:
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 1;
				m_tFrame.iMotion = 3;
				m_tFrame.dwFrameSpeed = 200;
				m_tFrame.dwFrameTime = GetTickCount();
				break;

			case DEAD:
				m_pFrameKey = L"PLAYER_GROUND_DEAD";
				m_tInfo.fCX = 114.f;
				m_tInfo.fCY = 46.f;
				m_iAniCount = 5;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.dwFrameSpeed = 200;
				m_tFrame.dwFrameTime = GetTickCount();
				break;
			}
		}
		else
		{
			switch (m_eCurState)
			{
			case IDLE:
				m_pFrameKey = L"PLAYER_IDLE";
				m_tInfo.fCX = 70.f;
				m_tInfo.fCY = 70.f;
				break;

			case RUN:
				m_pFrameKey = L"PLAYER_RUN";
				m_tInfo.fCX = 88.f;
				m_tInfo.fCY = 64.f;
				break;

			case JUMP:
				m_pFrameKey = L"PLAYER_JUMP";
				m_tInfo.fCX = 60.f;
				m_tInfo.fCY = 84.f;
				break;

			case FALL:
				m_pFrameKey = L"PLAYER_FALL";
				m_tInfo.fCX = 82.f;
				m_tInfo.fCY = 86.f;
				break;

			case RUNTOIDLE:
				m_pFrameKey = L"PLAYER_RUNTOIDLE";
				m_tInfo.fCX = 80.f;
				m_tInfo.fCY = 70.f;
				break;

			case IDLETORUN:
				m_pFrameKey = L"PLAYER_IDLETORUN";
				m_tInfo.fCX = 84.f;
				m_tInfo.fCY = 64.f;
				break;

			case ATTACK:
				m_pFrameKey = L"PLAYER_ATTACK";
				m_tInfo.fCX = 120.f;
				m_tInfo.fCY = 82.f;
				break;

			case FLIP:
				m_pFrameKey = L"PLAYER_FLIP";
				m_tInfo.fCX = 96.f;
				m_tInfo.fCY = 88.f;
				break;

			case GRAB_WALL:
				m_pFrameKey = L"PLAYER_GRAB_WALL";
				m_tInfo.fCX = 78.f;
				m_tInfo.fCY = 100.f;
				break;

			case ROLL:
				m_pFrameKey = L"PLAYER_ROLL";
				m_tInfo.fCX = 94.f;
				m_tInfo.fCY = 64.f;
				break;

			case DEAD:
				m_pFrameKey = L"PLAYER_GROUND_DEAD";
				m_tInfo.fCX = 114.f;
				m_tInfo.fCY = 46.f;
				m_iAniCount = 5;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.dwFrameSpeed = 200;
				m_tFrame.dwFrameTime = GetTickCount();
				break;
			}
		}

		m_ePreState = m_eCurState;
	}
}

void CPlayer::EnvCheck(void)
{
	if (m_fFootY != 0)
		m_fPreFootY = m_fFootY;

	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &m_fFootY);

	float fCurFootY = m_tInfo.fY + m_tInfo.fCY * 0.5f;

	if (m_fPreFootY + 0.1f < m_fFootY)
		m_eEevState = GROUND_DOWN;

	switch (m_eEevState)
	{
	case AIR:
		m_tInfo.fY -= m_fCurJumpSpeed;
		if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
			m_fCurJumpSpeed -= GRAVITY;
		m_bJump = true;
		break;

	case GROUND_DOWN:
		m_eCurState = FALL;
		m_tInfo.fY -= m_fCurJumpSpeed * 0.7f;
		if (fabs(m_fCurJumpSpeed) < m_fMaxAbsJumpSpeed) // limit max speed
			m_fCurJumpSpeed -= GRAVITY;
		break;

	case WALL:
		m_eCurState = GRAB_WALL;
		m_fCurJumpSpeed = 0.f;
		if (fCurFootY < m_fFootY)
		{
			m_tInfo.fY += m_fWallSpeed;
		}
		m_bWallJump = false;
		m_iWallJumpCnt = 0;
		break;

	case GROUND:
		m_fCurJumpSpeed = 0.f;
		m_tInfo.fY = m_fFootY - m_tInfo.fCY * 0.5f;
		m_bJump = false;
		m_bWallJump = false;
		m_iWallJumpCnt = 0;
		break;

	default:
		break;
	}

	fCurFootY = m_tInfo.fY + m_tInfo.fCY * 0.5f;

	if (bLineCol && abs(m_fFootY - fCurFootY) < m_fMaxAbsJumpSpeed * 0.5f)
	{
		m_eEevState = GROUND;
	}
	else
		m_eEevState = AIR;
}

void CPlayer::Attacking(void)
{
	if (m_bAttack)
	{
		m_iCount++;
		if (m_iCount % 3 == 0)
		{
			m_iShakeCamera = 0;
		}
		CObjMgr::Get_Instance()->Add_Object(OBJ_SWORD, CAbstractFactory<CSwordBox>::Create(m_tInfo.fX, m_tInfo.fY));

		m_eCurState = ATTACK;

		if (m_pt.x < m_tInfo.fX)
			m_eLookDir = LOOK_LEFT;
		else if (m_pt.x > m_tInfo.fX)
			m_eLookDir = LOOK_RIGHT;

		m_bAttack = false;
	}
}

void CPlayer::Rolling(void)
{
	if (m_dwRollWaitTime + m_fRollCoolTime * 1000 < GetTickCount())
	{
		m_bRoll = false;
	}

	if (m_bRoll && m_iRollCnt++ < m_iRollMaxCnt)
	{
		if (m_eLookDir == LOOK_RIGHT)
			m_tInfo.fX += m_fRollSpeed;
		else if (m_eLookDir == LOOK_LEFT)
			m_tInfo.fX -= m_fRollSpeed;
	}
}

void CPlayer::WallJumping()
{
	if (m_bWallJump)
	{
		m_eCurState = FLIP;
		if (m_iWallJumpCnt++ < m_iWallJumpMaxCnt)
		{
			if (m_eLookDir == LOOK_RIGHT)
			{
				m_tInfo.fX += -m_iWallJumpTickSpeed;
			}
			else if (m_eLookDir == LOOK_LEFT)
			{
				m_tInfo.fX += m_iWallJumpTickSpeed;
			}
		}
	}
}

void CPlayer::BackToPast()
{
	Set_Frame(-3);
	m_bReset = true;
	CScrollMgr::Get_Instance()->Set_ScrollX((sinf((float)GetTickCount()) * 10));
	CScrollMgr::Get_Instance()->Set_ScrollY((cosf((float)GetTickCount()) * 10));
	if (!m_bPast)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CBackToPastEffect>::Create(m_tInfo.fX, m_tInfo.fY));
		m_bPast = true;
	}

	if (!m_tInfoList.empty())
	{
		m_tInfo.fX = m_tInfoList.back().fX;
		m_tInfo.fY = m_tInfoList.back().fY;
		m_tInfoList.pop_back();
		m_bTurnBackTime = true;
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

	Motion_Change();
	Move_Frame();

	if (m_tInfoList.empty())
	{
		m_bReset = false;
		m_bDead = false;
		m_bTurnBackTime = false;
		m_bKeyRPressing = false;
		EnvCheck();
		if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_1)
		{
			m_bPast = false;
			Set_ListClear();
			CSceneMgr::Get_Instance()->Scene_Change(SC_LOADING_1);
		}
		else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_2)
		{
			m_bPast = false;
			Set_ListClear();
			CSceneMgr::Get_Instance()->Scene_Change(SC_LOADING_2);
		}
		else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS)
		{
			m_bPast = false;
			Set_ListClear();
			CSceneMgr::Get_Instance()->Scene_Change(SC_LOADING_3);
			g_iFinished = 1;
		}
	}
}

void CPlayer::Reset(void)
{
	if (m_bReset == false)
	{
		if (m_tInfoList.empty())
		{
			m_tInfoList.push_back(m_tInfo);
			m_ePreStateList.push_back(m_eCurState);
			m_tFrameList.push_back(m_tFrame);
		}
		else if (m_tInfoList.back().fX != m_tInfo.fX || m_ePreStateList.back() != m_eCurState)
		{
			m_tInfoList.push_back(m_tInfo);
			m_ePreStateList.push_back(m_eCurState);
			m_tFrameList.push_back(m_tFrame);
		}
	}
}

void CPlayer::GeneralRender(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	HDC	hMouseDC = CBmpMgr::Get_Instance()->Find_Img(L"PLAYER_AIM");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_eCurState == IDLETORUN)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CDustEffect>::Create(m_tInfo.fX, m_tInfo.fY + 35.f));
	}

	// 중점 맞춰주기 위해 -31, -29로 조정함 마우스
	GdiTransparentBlt(hDC,
		m_pt.x + iScrollX - 31,
		m_pt.y + iScrollY - 29,
		62,
		58,
		hMouseDC,
		0,
		0,
		62,
		58,
		RGB(255, 0, 255));
	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->empty())
	{
		if (m_eLookDir == LOOK_LEFT && m_eCurState == ROLL)
		{
			GdiTransparentBlt(hDC,
				m_tRect.left + iScrollX,					// 복사 받을 위치의 좌표 전달(x,y 순서)
				m_tRect.top + iScrollY,
				(int)m_tInfo.fCX,							// 복사 받을 이미지의 길이 전달(가로, 세로순서)
				(int)m_tInfo.fCY,
				hMemDC,										// 비트맵을 가지고 있는 dc
				658 - ((int)m_tInfo.fCX * m_tFrame.iFrameStart),	// 출력할 비트맵 시작 좌표(x,y 순서)
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,							// 복사 할 비트맵 의 가로, 세로 사이즈
				(int)m_tInfo.fCY,
				RGB(255, 0, 255));							// 제거할 픽셀의 색상

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
	}
	else if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->empty())
	{
		if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front()->Get_Dead())
		{
			m_bSwordMove = true;
		}

		if (dynamic_cast<CBoss*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front())->Get_RealDead() == true)
		{
			if (m_pGraphics == nullptr)
				m_pGraphics = Gdiplus::Graphics::FromHDC(hDC);

			if (m_eCurState == IDLE)
			{
				m_pGraphics->DrawImage(m_pTexture_BossDead[0],
					m_tRect.left + iScrollX, m_tRect.top + iScrollY,
					(int)m_tInfo.fCX * m_tFrame.iFrameStart,
					(int)m_tInfo.fCY * m_tFrame.iMotion,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					UnitPixel);
			}
			else if (m_eCurState == ATTACK)
			{
				m_pGraphics->DrawImage(m_pTexture_BossDead[1],
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
			if (m_eLookDir == LOOK_LEFT && m_eCurState == ROLL)
			{
				GdiTransparentBlt(hDC,
					m_tRect.left + iScrollX,					// 복사 받을 위치의 좌표 전달(x,y 순서)
					m_tRect.top + iScrollY,
					(int)m_tInfo.fCX,							// 복사 받을 이미지의 길이 전달(가로, 세로순서)
					(int)m_tInfo.fCY,
					hMemDC,										// 비트맵을 가지고 있는 dc
					658 - ((int)m_tInfo.fCX * m_tFrame.iFrameStart),	// 출력할 비트맵 시작 좌표(x,y 순서)
					(int)m_tInfo.fCY * m_tFrame.iMotion,
					(int)m_tInfo.fCX,							// 복사 할 비트맵 의 가로, 세로 사이즈
					(int)m_tInfo.fCY,
					RGB(255, 0, 255));							// 제거할 픽셀의 색상

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
		}
	}
	// player 왼쪽 롤은 애니메이션 다르게 해야함
	
}

void CPlayer::AlphaRender(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	HDC	hMouseDC = CBmpMgr::Get_Instance()->Find_Img(L"PLAYER_AIM");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_eCurState == IDLETORUN)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CDustEffect>::Create(m_tInfo.fX, m_tInfo.fY + 35.f));
	}

	// 중점 맞춰주기 위해 -31, -29로 조정함 마우스
	GdiTransparentBlt(hDC,
		m_pt.x + iScrollX - 31,
		m_pt.y + iScrollY - 29,
		62,
		58,
		hMouseDC,
		0,
		0,
		62,
		58,
		RGB(255, 0, 255));

	// player 왼쪽 롤은 애니메이션 다르게 해야함
	if (m_eLookDir == LOOK_LEFT && m_eCurState == ROLL)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,					// 복사 받을 위치의 좌표 전달(x,y 순서)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,							// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			(int)m_tInfo.fCY,
			hMemDC,										// 비트맵을 가지고 있는 dc
			658 - ((int)m_tInfo.fCX * m_tFrame.iFrameStart),	// 출력할 비트맵 시작 좌표(x,y 순서)
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,							// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));							// 제거할 픽셀의 색상

	}
	else
	{
		if (m_pGraphics == nullptr)
			m_pGraphics = Gdiplus::Graphics::FromHDC(hDC);

		if (m_eCurState == IDLE)
		{
			m_pGraphics->DrawImage(m_pTexture[0],
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				UnitPixel);
		}
		else if (m_eCurState == RUN)
		{
			m_pGraphics->DrawImage(m_pTexture[1],
				m_tRect.left + iScrollX, m_tRect.top+iScrollY,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				UnitPixel);
		}
		else if (m_eCurState == RUNTOIDLE)
		{
			m_pGraphics->DrawImage(m_pTexture[4],
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				UnitPixel);
		}
		else if (m_eCurState == IDLETORUN)
		{
			m_pGraphics->DrawImage(m_pTexture[5],
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				UnitPixel);
		}
		else if (m_eCurState == ATTACK)
		{
			m_pGraphics->DrawImage(m_pTexture[6],
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				UnitPixel);
		}
		else if (m_eCurState == FLIP)
		{
			m_pGraphics->DrawImage(m_pTexture[10],
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				UnitPixel);
		}
		else if (m_eCurState == GRAB_WALL)
		{
			m_pGraphics->DrawImage(m_pTexture[9],
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				UnitPixel);
		}
		else if (m_eCurState == ROLL)
		{
			m_pGraphics->DrawImage(m_pTexture[7],
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				UnitPixel);
		}
		else if (m_eCurState == DEAD)
		{
			m_pGraphics->DrawImage(m_pTexture[8],
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				UnitPixel);
		}
		else if (m_eCurState == JUMP)
		{
			m_pGraphics->DrawImage(m_pTexture[2],
				m_tRect.left + iScrollX, m_tRect.top + iScrollY,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				UnitPixel);
		}
	}
}
