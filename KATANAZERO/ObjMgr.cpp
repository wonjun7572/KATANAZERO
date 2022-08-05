#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& Obj : m_ObjList[i])
		{
			Obj->Late_Update();
			
			if (m_ObjList[i].empty())
				break;

			RENDERID		eID = Obj->Get_RenderID();
			m_RenderSort[eID].push_back(Obj);
		}
	}

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_SWORD], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_SWORD], m_ObjList[OBJ_BULLET_ENEMY]);
	
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET_ENEMY]);

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET_PLAYER]);
	
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_SWORD], m_ObjList[OBJ_DOOR]);

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_KNIFE]);

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BOTTLE]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_WALL], m_ObjList[OBJ_BOTTLE]);

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_BULLET_PLAYER], m_ObjList[OBJ_DOOR]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_BULLET_ENEMY], m_ObjList[OBJ_DOOR]);

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_SMOKE]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_WALL], m_ObjList[OBJ_SMOKE]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_KNIFE], m_ObjList[OBJ_DOOR]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_SMOKE], m_ObjList[OBJ_DOOR]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_BOTTLE], m_ObjList[OBJ_DOOR]);

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_KNIFE], m_ObjList[OBJ_BULLET_ENEMY]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_SMOKE], m_ObjList[OBJ_BULLET_ENEMY]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_BOTTLE], m_ObjList[OBJ_BULLET_ENEMY]);

	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_DOOR]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_DOOR]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_WALL]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_WALL]);

}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CObj*>); 
		
		for (auto& Obj : m_RenderSort[i])
			Obj->Render(hDC);

		m_RenderSort[i].clear();
	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_OBJID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;

	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = abs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = abs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);


		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}
	return pTarget;
}
