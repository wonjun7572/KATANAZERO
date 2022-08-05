#pragma once
#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	// �簢 �浹 üũ
	static void	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	// �� �浹 üũ
	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);
	// �簢 �浹 �� �о��ֱ�
	static void	Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour);
	// �簢 ��Ʈ üũ
	static bool Check_Rect(CObj* pDest, CObj* pSour, float* pX, float* pY);
	// ���� ��Ʈ üũ
	static bool Check_Sphere(CObj* pDest, CObj* pSour);
};
