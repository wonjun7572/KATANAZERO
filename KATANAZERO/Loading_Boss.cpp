#include "stdafx.h"
#include "Loading_Boss.h"
#include "SceneMgr.h"
#include "ObjMgr.h"

CLoading_Boss::CLoading_Boss()
{
}

CLoading_Boss::~CLoading_Boss()
{
	Release();
}

void CLoading_Boss::Initialize(void)
{
}

int CLoading_Boss::Update(void)
{
	return 0;
}

void CLoading_Boss::Late_Update(void)
{
}

void CLoading_Boss::Render(HDC hDC)
{
	CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_BOSS);
}

void CLoading_Boss::Release(void)
{
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_EFFECT);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_WALL);
}
