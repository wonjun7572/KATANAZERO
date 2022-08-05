#include "stdafx.h"
#include "Stage_2.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "Monster_1.h"
#include "Monster_2.h"
#include "Monster_3.h"
#include "CollisionMgr.h"
#include "Shadow.h"
#include "Wall.h"
#include "SceneMgr.h"
#include "HUDUI.h"
#include "RBatteryGageUI.h"
#include "BBatteryGageUI.h"
#include "GoArrowUI.h"
#include "GoUI.h"
#include "Door.h"
#include "WeaponUI.h"
#include "KnifeUI.h"
#include "BottelUI.h"
#include "SmokeUI.h"
#include "Lazer.h"
#include "LazerLong.h"

float g_Stage2Sound = 1.f;

CStage_2::CStage_2()
{
}

CStage_2::~CStage_2()
{
	Release();
}

void CStage_2::Initialize(void)
{
	CScrollMgr::Get_Instance()->Initialize(10.f, -390.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHUDUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CRBatteryGageUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CBBatteryGageUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CWeaponUI>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CKnifeUI>::Create(337.f, 910.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CSmokeUI>::Create(400.f, 650.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CBottelUI>::Create(1904.f, 650.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CKnifeUI>::Create(2731.f, 650.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CSmokeUI>::Create(2976.f, 910.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CKnifeUI>::Create(2067.f, 1200.f));

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
	{
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(70,855);
	}

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_SHADOW)->empty())
	{
		for (auto iter : *CObjMgr::Get_Instance()->Get_ObjList(OBJ_SHADOW))
		{
			iter->Set_Pos(70, 855);
		}
	}

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create(600.f, 850.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(3050.f, 850.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create(1315.f, 1120.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(1420.f, 1120.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create(2740.f, 1120.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(2958.f, 1120.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(3345.f, 1120.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_1>::Create(300.f, 580.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(810.f, 580.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create(1080.f, 580.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create(1850.f, 580.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create(2065.f, 580.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(3150.f, 580.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(3527.f, 580.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create(3150.f, 313.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(3282.f, 313.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(3396.f, 313.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_1>::Create(3508.f, 313.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(738.f, 609.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(1729.f, 609.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(2143.f, 609.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(2879.f, 609.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(417.f, 865.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(3104.f, 865.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(1572.f, 1152.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(2465.f, 1152.f));

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/stage3_bg_render.bmp", L"STAGE_3_BACKGROUND");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/stage3_bg_render_slow.bmp", L"STAGE_3_BACKGROUND_SLOW");
	CLineMgr::Get_Instance()->Initialize();
	m_iMonCount = 18;
}

int CStage_2::Update(void)
{
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CSoundMgr::Get_Instance()->PlaySound(L"bgm_stage4.mp3", SOUND_BGM, g_Stage2Sound);

	for (auto iter : *CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER))
	{
		if (iter->Get_Dead() == true)
			m_iMonCount--;
	}

	if (m_iMonCount <= 0)
	{
		m_bMonClear = true;
		if (!m_bGoUI)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CGoUI>::Create(3900.f,800.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CGoArrowUI>::Create(3900.f, 840.f));
			m_bGoUI = true;
		}
	}

	if (m_bMonClear && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX > 4000.f)
	{
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_ListClear();
		CSceneMgr::Get_Instance()->Scene_Change(SC_PRE_STAGE_BOSS);
	}
	return 0;
}

void CStage_2::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage_2::Render(HDC hDC)
{
		if (!m_bSlow)
		{
			HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"STAGE_3_BACKGROUND");
			int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			BitBlt(hDC, iScrollX, iScrollY, 4000, 1492, hMemDC, 0, 0, SRCCOPY);

			CObjMgr::Get_Instance()->Render(hDC);
		}
		else
		{
			HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"STAGE_3_BACKGROUND_SLOW");

			int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

			BitBlt(hDC, iScrollX, iScrollY, 4000, 1492, hMemDC, 0, 0, SRCCOPY);

			CObjMgr::Get_Instance()->Render(hDC);
		}
}

void CStage_2::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_TRAP);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_ITEM);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_DOOR);
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
