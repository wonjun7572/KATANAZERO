#include "stdafx.h"
#include "Stage_1.h"
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
#include "GoUI.h"
#include "GoArrowUI.h"
#include "Door.h"
#include "Curtain.h"
#include "WeaponUI.h"
#include "KnifeUI.h"
#include "BottelUI.h"
#include "SmokeUI.h"
#include "Lazer.h"
#include "LazerLong.h"

float	g_fSound = 1.f;

CStage_1::CStage_1()
{
}

CStage_1::~CStage_1()
{
	Release();
}

void CStage_1::Initialize(void)
{
	CScrollMgr::Get_Instance()->Initialize(10.f, -390.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHUDUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CRBatteryGageUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CBBatteryGageUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CWeaponUI>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CSmokeUI>::Create(1290.f, 745.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CKnifeUI>::Create(1876.f, 745.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CBottelUI>::Create(2471.f, 493.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CLazer>::Create(1695.f, 703.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_TRAP, CAbstractFactory<CLazerLong>::Create(2368.f, 420.f));

	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	}

	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_SHADOW)->empty())
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_SHADOW, CAbstractFactory<CShadow>::Create_Shadow(15 , 170));
		CObjMgr::Get_Instance()->Add_Object(OBJ_SHADOW, CAbstractFactory<CShadow>::Create_Shadow(25 , 150));
		CObjMgr::Get_Instance()->Add_Object(OBJ_SHADOW, CAbstractFactory<CShadow>::Create_Shadow(35 , 130));
		CObjMgr::Get_Instance()->Add_Object(OBJ_SHADOW, CAbstractFactory<CShadow>::Create_Shadow(45 , 110));
		CObjMgr::Get_Instance()->Add_Object(OBJ_SHADOW, CAbstractFactory<CShadow>::Create_Shadow(55 , 90));
		CObjMgr::Get_Instance()->Add_Object(OBJ_SHADOW, CAbstractFactory<CShadow>::Create_Shadow(65 , 70));
		CObjMgr::Get_Instance()->Add_Object(OBJ_SHADOW, CAbstractFactory<CShadow>::Create_Shadow(75 , 50));
		CObjMgr::Get_Instance()->Add_Object(OBJ_SHADOW, CAbstractFactory<CShadow>::Create_Shadow(85 , 30));
		CObjMgr::Get_Instance()->Add_Object(OBJ_SHADOW, CAbstractFactory<CShadow>::Create_Shadow(95 , 10));
	}

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_1>::Create(562.f, 700.f, DIR_RIGHT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_1>::Create(685.f, 700.f, DIR_RIGHT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(750.f, 700.f, DIR_LEFT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_1>::Create(850.f, 700.f, DIR_RIGHT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(915.f, 700.f, DIR_LEFT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_1>::Create(1220.f, 700.f, DIR_RIGHT));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create(1838.f, 420.f, DIR_RIGHT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create(2255.f, 420.f, DIR_LEFT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_1>::Create(3503.f, 420.f, DIR_RIGHT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_2>::Create(3302.f, 700.f, DIR_LEFT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_3>::Create(3943.f, 700.f, DIR_RIGHT));
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(385.f,708.f, DIR_RIGHT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(1090.f, 708.f, DIR_RIGHT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(2625.f, 451.f, DIR_RIGHT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(3363.f, 451.f, DIR_RIGHT));
	CObjMgr::Get_Instance()->Add_Object(OBJ_DOOR, CAbstractFactory<CDoor>::Create(3363.f, 708.f, DIR_RIGHT));
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_CURTAIN, CAbstractFactory<CCurtain>::Create());

	//m_dwSoundTimer = GetTickCount();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/stage2_bg_render.bmp", L"STAGE_2_BACKGROUND");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/stage2_bg_render_slow.bmp", L"STAGE_2_BACKGROUND_SLOW");
	CLineMgr::Get_Instance()->Initialize();
	m_iMonCount = 12;
}

int CStage_1::Update(void)
{
	CLineMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	if (!m_bCurtain)
	{
		if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR)->empty())
		{
			float fDistance = CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR)->front()->Get_Info().fX - CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;
			if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR)->front()->Get_Info().fX < CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX)
			{
				dynamic_cast<CCurtain*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_CURTAIN)->front())->Set_Dead(true);
				m_bCurtain = true;
			}
			else if (fDistance < 255)
			{
				dynamic_cast<CCurtain*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_CURTAIN)->front())->Set_Alpha((int)fDistance);
			}
		}
	}

	CSoundMgr::Get_Instance()->PlaySound(L"bgm_bunker.mp3", SOUND_BGM, g_fSound);

	//일단 obj 몬스터 해결해야함
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
			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CGoUI>::Create(4189.f,645.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CGoArrowUI>::Create(4189.f,694.f)); 
			m_bGoUI = true;																		
		}
	}

	if (m_bMonClear && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX > 4288.f)
	{
		dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_ListClear();
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_2);
	}

	return 0;
}

void CStage_1::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage_1::Render(HDC hDC)
{
	if (!m_bSlow)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"STAGE_2_BACKGROUND");
		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
		BitBlt(hDC, iScrollX, iScrollY, 4288, 1200, hMemDC, 0, 0, SRCCOPY);

		CObjMgr::Get_Instance()->Render(hDC); //[0] framekey 받는놈이 [1] 
	}
	else
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"STAGE_2_BACKGROUND_SLOW");

		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		BitBlt(hDC, iScrollX, iScrollY, 4288, 1200, hMemDC, 0, 0, SRCCOPY);

		CObjMgr::Get_Instance()->Render(hDC);
	}
}

void CStage_1::Release(void)
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

