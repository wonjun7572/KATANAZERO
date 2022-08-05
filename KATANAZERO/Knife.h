#pragma once
#include "Obj.h"
class CKnife :
	public CObj
{
public:
	CKnife();
	virtual ~CKnife();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	POINT		m_tPoint[3];
	float		m_fRotAngle = 0.f;
};

