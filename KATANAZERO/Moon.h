#pragma once
#include "Obj.h"
class CMoon :
	public CObj
{
public:
	CMoon();
	virtual ~CMoon();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	Gdiplus::Bitmap* m_pTexture;
	Gdiplus::Graphics* m_pGraphics = nullptr;
	
	bool m_bFinished = false;
};

