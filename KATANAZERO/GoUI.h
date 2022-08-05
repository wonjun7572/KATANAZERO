#pragma once
#include "Obj.h"
class CGoUI :
	public CObj
{
public:
	CGoUI();
	virtual ~CGoUI();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	BLENDFUNCTION m_BlendFunction;
	int			  m_iAlpha;

	HDC		m_AlphaDC;
};

