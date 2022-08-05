#pragma once
#include "Obj.h"
class CDoor :
	public CObj
{
public:
	CDoor();
	virtual ~CDoor();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void InfoToRect();

	bool Get_Dooropen() { return m_bDooropen; }

private:
	bool m_bDooropen = false;
	INFO m_renderInfo;
	RECT m_renderRect;

	bool m_bOpened = false;
};

