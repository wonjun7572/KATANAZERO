#pragma once
#include "Obj.h"
class CBottelUI :
	public CObj
{
public:
	CBottelUI();
	virtual ~CBottelUI();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	bool Check_Sphere(CObj* pDest, INFO* pSour);

	bool Get_Item() { return m_bItem; }


private:
	bool m_bItem = false;
	CObj* m_pPlayer;
};

