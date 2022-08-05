#pragma once
#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	// 사각 충돌 체크
	static void	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	// 원 충돌 체크
	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);
	// 사각 충돌 후 밀어주기
	static void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour);
	// 사각 렉트 체크
	static bool Check_Rect(CObj* pDest, CObj* pSour, float* pX, float* pY);
	// 원형 렉트 체크
	static bool Check_Sphere(CObj* pDest, CObj* pSour);
};
