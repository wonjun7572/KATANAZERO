#pragma once
#include "Include.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	Late_Update(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

	void	Set_Slow(bool _slow) { m_bSlow = _slow; }

protected:
	bool	m_bSlow = false;
};

