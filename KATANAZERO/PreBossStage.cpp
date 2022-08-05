#include "stdafx.h"
#include "PreBossStage.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "HUDUI.h"
#include "RBatteryGageUI.h"
#include "BBatteryGageUI.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"
#include "Boss.h"
#include "SceneMgr.h"
#include "Explosion.h"
#include "Monster_1.h"
#include "Monster_2.h"
#include "Monster_3.h"

float g_BossStageSound2 = 1.f;

CPreBossStage::CPreBossStage()
{
}

CPreBossStage::~CPreBossStage()
{
	Release();
}

void CPreBossStage::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHUDUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CRBatteryGageUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CBBatteryGageUI>::Create());

	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	}

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
	{
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(250, 0);
	}

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_SHADOW)->empty())
	{
		for (auto iter : *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SHADOW))
		{
			iter->Set_Pos(250, 0);
		}
	}

	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create(600.f, 0));
	}

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/BossStage_slow.bmp", L"PRE_STAGE_BOSS_BACKGROUND_SLOW");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/BossStage1.bmp", L"PRE_STAGE_BOSS_BACKGROUND");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/BossStage2.bmp", L"PRE_STAGE_BOSS_BACKGROUND_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/Down.bmp", L"PRE_STAGE_BOSS_DOWN");

	CLineMgr::Get_Instance()->Initialize();
	for (int i = 0; i < 2; ++i)
	{
		m_dwT[i] = GetTickCount();
	}
	m_dwTimer = GetTickCount();
}

int CPreBossStage::Update(void)
{
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (m_dwT[1] + 5000 < GetTickCount())
	{
		int iSpotX = rand() % 1115 + 235;
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create((float)iSpotX, 0.f, DIR_RIGHT));
		m_dwT[1] = GetTickCount();
	}
	else if (m_dwT[0] + 3000 < GetTickCount())
	{
		int iSpotX = rand() % 1115 + 235;
		int iSpotX2 = rand() % 1115 + 235;
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_1>::Create((float)iSpotX, 0.f, DIR_RIGHT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create((float)iSpotX2, 0.f, DIR_LEFT));
		m_dwT[0] = GetTickCount();
	}

	if (m_iNum > 20) // 보스 몇대 때리면
	{
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_EnvState(GROUND_DOWN);
		dynamic_cast<CBoss*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front())->Set_EnvState(GROUND_DOWN);
		CScrollMgr::Get_Instance()->Set_Lock(true);
		m_bDown = true;
	}

	if (m_bExplosion)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"explosion3.wav", SOUND_PRESTAGE, g_BossStageSound2);
		CScrollMgr::Get_Instance()->Set_ScrollX(sinf((float)GetTickCount()) * 10);
		CScrollMgr::Get_Instance()->Set_ScrollY(cosf((float)GetTickCount()) * 10);
	}

	if (!m_bSlow)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"bgm_stage5_full.mp3", SOUND_BGM, g_BossStageSound2);
	}

	if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY > 2500.f) // 플레이어가 어느정도 내려가면 리얼 보스씬 실행
	{
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_ListClear();
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_BOSS);
		m_dwTimer = GetTickCount();
	}

	return 0;
}

void CPreBossStage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->empty())
	{
		if (dynamic_cast<CBoss*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front())->Get_HP() < 7)
		{
			m_iNum++;
			if (m_iNum < 30)
			{
				m_bExplosion = true;
				CObjMgr::Get_Instance()->Add_Object(OBJ_EXPLOSION, CAbstractFactory<CExplosion>::Create(m_iNum * 50.f, 740.f));
				m_dwTimer = GetTickCount();
			}
		}
	}
}

void CPreBossStage::Render(HDC hDC)
{
	if (!m_bSlow && !m_bDown)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"PRE_STAGE_BOSS_BACKGROUND");
		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		GdiTransparentBlt(hDC,
			iScrollX,				// 복사 받을 위치의 좌표 전달(x,y 순서)
			iScrollY + 200,
			1580,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			987,
			hMemDC,												// 비트맵을 가지고 있는 dc	
			0,								// 1050 부터 0으로
			0,
			1580,									// 복사 할 비트맵 의 가로, 세로 사이즈
			987,
			RGB(255, 0, 255));										// 제거할 픽셀의 색상

		CObjMgr::Get_Instance()->Render(hDC); //[0] framekey 받는놈이 [1] 
	}
	else if (m_bDown)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"PRE_STAGE_BOSS_DOWN");

		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		GdiTransparentBlt(hDC,
			iScrollX,				// 복사 받을 위치의 좌표 전달(x,y 순서)
			iScrollY + 200,
			10000,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			10000,
			hMemDC,												// 비트맵을 가지고 있는 dc	
			0,								// 1050 부터 0으로
			0,
			10000,									// 복사 할 비트맵 의 가로, 세로 사이즈
			10000,
			RGB(255, 0, 255));										// 제거할 픽셀의 색상

		CObjMgr::Get_Instance()->Render(hDC);
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"PRE_STAGE_BOSS_BACKGROUND_SLOW");

		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		GdiTransparentBlt(hDC,
			iScrollX,													// 복사 받을 위치의 좌표 전달(x,y 순서)
			iScrollY + 200,
			1580,														// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			987,
			hMemDC,													// 비트맵을 가지고 있는 dc	
			0,																// 1050 부터 0으로
			0,
			1580,														// 복사 할 비트맵 의 가로, 세로 사이즈
			987,
			RGB(255, 0, 255));										// 제거할 픽셀의 색상

		CObjMgr::Get_Instance()->Render(hDC);
	}
}

void CPreBossStage::Release(void)
{
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_BULLET_ENEMY);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_EFFECT);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_KNIFE);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_SMOKE);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_BOTTLE);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_EXPLOSION);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_BOTTLE_WRECK);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_SMOKE_GAS);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_WALL);
	CLineMgr::Get_Instance()->Release();
}
