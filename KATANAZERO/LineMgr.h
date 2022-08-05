#pragma once

#include "Line.h"
#include "Wall.h"
#include "AbstractFactory.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	float		Get_Current_Line_Angle(float& fX);
	bool		Collision_Line(float& fX, float& fY, float* pY);

	void		Save_Line(void);
	void		Load_Line(void);


public:
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);

	void		Render(HDC hDC);
	void		Release(void);

public:
	static CLineMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	LINEPOINT				m_tLinePoint[LOOK_END];
	static CLineMgr*		m_pInstance;
	list<CLine*>			m_LineList;
	list<CObj*>			m_WallList;
};

