#pragma once
#include "Obj.h"
class CCurtain :
	public CObj
{
public:
	CCurtain();
	virtual ~CCurtain();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Set_Alpha(int _alpha) { m_iAlpha = _alpha; }
	void	Set_Dead(bool _dead) { m_bDead = _dead; }
private:
	BLENDFUNCTION m_BlendFunction;
	int			  m_iAlpha;

	HDC		m_AlphaDC;
};

