#include "stdafx.h"
#include "Loading_2.h"
#include "SceneMgr.h"
#include "ObjMgr.h"

CLoading_2::CLoading_2()
{
}

CLoading_2::~CLoading_2()
{
	Release();
}

void CLoading_2::Initialize(void)
{
}

int CLoading_2::Update(void)
{
	return 0;
}

void CLoading_2::Late_Update(void)
{
}

void CLoading_2::Render(HDC hDC)
{
	CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_2);
}

void CLoading_2::Release(void)
{
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_EFFECT);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_WALL);
}
