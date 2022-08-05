#pragma once

#include "Logo.h"
#include "Stage_1.h"
#include "Stage_2.h"
#include "Loading_1.h"
#include "Loading_2.h"
#include "Loading_3.h"
#include "PreBossStage.h"
#include "BossStage.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	void	Scene_Change(SCENEID eID);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

	CScene*		Get_Scene() { return m_pScene; }

	SCENEID		Get_SceneID() { return m_eCurScene; }

public:
	static CSceneMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

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
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene;

	SCENEID					m_ePreScene;
	SCENEID					m_eCurScene;

};

