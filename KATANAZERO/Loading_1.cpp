#include "stdafx.h"
#include "Loading_1.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

CLoading_1::CLoading_1()
{
}


CLoading_1::~CLoading_1()
{
	Release();
}

void CLoading_1::Initialize(void)
{
}

int CLoading_1::Update(void)
{
	return 0;
}

void CLoading_1::Late_Update(void)
{
}

void CLoading_1::Render(HDC hDC)
{
	CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_1);
}

void CLoading_1::Release(void)
{
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_EFFECT);
	CObjMgr::Get_Instance()->Delete_OBJID(OBJ_WALL);
}
