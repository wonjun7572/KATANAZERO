#include "stdafx.h"
#include "Loading_3.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Boss.h"

CLoading_3::CLoading_3()
{
}

CLoading_3::~CLoading_3()
{
	Release();
}

void CLoading_3::Initialize(void)
{
}

int CLoading_3::Update(void)
{
	return 0;
}

void CLoading_3::Late_Update(void)
{
}

void CLoading_3::Render(HDC hDC)
{
	CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_BOSS);
}

void CLoading_3::Release(void)
{
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_EFFECT);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_BOSS);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_WALL);
}
