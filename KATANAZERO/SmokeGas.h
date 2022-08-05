#pragma once
#include "Obj.h"
class CSmokeGas :
	public CObj
{
public:
	CSmokeGas();
	virtual ~CSmokeGas();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	bool Check_Sphere(CObj* pDest, INFO* pSour);
private:
	BLENDFUNCTION m_BlendFunction;

	HDC		m_AlphaDC;
};