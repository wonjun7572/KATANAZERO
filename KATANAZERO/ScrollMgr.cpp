#include "stdafx.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_1)
	{
		// ���� ������ ��ŭ ��ũ�� �� �ϴ� �κ�
		if (WINCX - 4288.f > m_fScrollX)
			m_fScrollX = WINCX - 4288.f;

		if (WINCY - 1200.f > m_fScrollY)
			m_fScrollY = WINCY - 1200.f;
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_2)
	{
		// ���� ������ ��ŭ ��ũ�� �� �ϴ� �κ�
		if (WINCX - 4000.f > m_fScrollX)
			m_fScrollX = WINCX - 4000.f;

		if (WINCY - 1492.f > m_fScrollY)
			m_fScrollY = WINCY - 1492.f;
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS)
	{
		// ���� ������ ��ŭ ��ũ�� �� �ϴ� �κ�
		if (WINCX - 1344.f > m_fScrollX)
			m_fScrollX = WINCX - 1344.f;

		if (WINCY - 784.f > m_fScrollY)
			m_fScrollY = WINCY - 784.f;
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_PRE_STAGE_BOSS)
	{
		// ���� ������ ��ŭ ��ũ�� �� �ϴ� �κ�
		if (WINCX - 1580.f > m_fScrollX)
			m_fScrollX = WINCX - 1580.f;

		if (!m_bLock)
		{
			if (WINCY - 988.f > m_fScrollY)
				m_fScrollY = WINCY - 988.f;
		}
	}
}
