#include "stdafx.h"
#include "BossStage.h"
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
#include "Moon.h"

float g_BossStageSound = 1.f;

CBossStage::CBossStage()
{
}

CBossStage::~CBossStage()
{
	Release();
}

void CBossStage::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHUDUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CRBatteryGageUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CBBatteryGageUI>::Create());

	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
		CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create());
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400.f, 500.f);
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front()->Set_Pos(600.f, -1000.f);
	}

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
	{
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_EnvState(AIR);
		dynamic_cast<CBoss*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front())->Set_EnvState(AIR);
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400.f, -1000.f);
		CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front()->Set_Pos(600.f, -1000.f);
	}

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_SHADOW)->empty())
	{
		for (auto iter : *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SHADOW))
		{
			iter->Set_Pos(250, 500);
		}
	}

	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create(350, 500));
	}

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/stage5_bg_render.bmp", L"STAGE_BOSS_BACKGROUND");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/stage5_bg_render_slow.bmp", L"STAGE_BOSS_BACKGROUND_SLOW");
}

int CBossStage::Update(void)
{
	if (!m_bLoadLine)
	{
		CLineMgr::Get_Instance()->Initialize();
		m_bLoadLine = true;
	}

	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front()->Get_Dead() == true)
	{
		if (!m_bEnding)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
			m_bEnding = true;
		}
		CSoundMgr::Get_Instance()->PlaySound(L"bgm_ending.mp3", SOUND_BGM, g_BossStageSound);
	}

	return 0;
}

void CBossStage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CBossStage::Render(HDC hDC)
{
	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front()->Get_Dead() == false)
	{
		if (!m_bSlow)
		{
			HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"STAGE_BOSS_BACKGROUND");
			int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			BitBlt(hDC, iScrollX, iScrollY, 1344, 784, hMemDC, 0, 0, SRCCOPY);

			CObjMgr::Get_Instance()->Render(hDC); //[0] framekey ¹Þ´Â³ðÀÌ [1] 
		}
		else
		{
			HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"STAGE_BOSS_BACKGROUND_SLOW");

			int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			BitBlt(hDC, iScrollX, iScrollY, 1344, 784, hMemDC, 0, 0, SRCCOPY);

			CObjMgr::Get_Instance()->Render(hDC);
		}
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"STAGE_BOSS_BACKGROUND");

		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		BitBlt(hDC, iScrollX, iScrollY, 1344, 784, hMemDC, 0, 0, WHITENESS);


		CObjMgr::Get_Instance()->Render(hDC);
		if (!m_bReleaseUI)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMoon>::Create(640.f, 420.f));
			CObjMgr::Get_Instance()->Delete_OBJID(OBJ_UI);
			m_bReleaseUI = true;
		}
	}
}

void CBossStage::Release(void)
{
	if (g_iFinished == 1)
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_BULLET_ENEMY);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_EFFECT);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_KNIFE);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_SMOKE);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_BOTTLE);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_BOTTLE_WRECK);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_SMOKE_GAS);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_WALL);
	CLineMgr::Get_Instance()->Release();
}
