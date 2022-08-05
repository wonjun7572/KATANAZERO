#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*		CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_ePreScene(SC_END), m_eCurScene(SC_LOGO) // 바로 스테이지 시작
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_LOADING_1:
			m_pScene = new CLoading_1;
			break;

		case SC_LOADING_2:
			m_pScene = new CLoading_2;
			break;

		case SC_LOADING_3:
			m_pScene = new CLoading_3;
			break;

		case SC_STAGE_1:
			m_pScene = new CStage_1;
			break;

		case SC_STAGE_2:
			m_pScene = new CStage_2;
			break;

		case SC_PRE_STAGE_BOSS:
			m_pScene = new CPreBossStage;
			break;

		case SC_STAGE_BOSS:
			m_pScene = new CBossStage;
			break;
		}

		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update(void)
{
	if (m_pScene)
		m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	if (m_pScene)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	if (m_pScene)
		m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete<CScene*>(m_pScene);
}
