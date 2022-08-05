#pragma once
#include "Obj.h"
class CGoArrowUI :
	public CObj
{
public:
	CGoArrowUI();
	virtual ~CGoArrowUI();

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

