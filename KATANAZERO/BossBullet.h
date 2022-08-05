#pragma once
#include "Obj.h"
class CBossBullet :
	public CObj
{
public:
	CBossBullet();
	virtual ~CBossBullet();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void RotationCheck();
	bool Check_Sphere(CObj* pDest, INFO* pSour);

	POINT		m_tPoint[3];
	float		m_fRotAngle = 0.f;
	bool		m_bReflect = false;
	bool		m_bEffect = false;
};

