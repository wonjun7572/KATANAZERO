#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
}

void CLogo::Initialize(void)
{
	m_fSound = 1.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/title/new.bmp", L"NEW");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/title/re.bmp", L"RE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/title/option.bmp", L"OPTION");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/title/language.bmp", L"LANGUAGE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/title/end.bmp", L"END");
}

int CLogo::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"bgm_title.mp3", SOUND_BGM, m_fSound);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		m_iSceneCount += 1;
		if (m_iSceneCount > 5)
			m_iSceneCount = 4;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
	{
		m_iSceneCount -= 1;
		if (m_iSceneCount < -1)
			m_iSceneCount = 0;
	}

	if (m_iSceneCount == 0 && CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_1);
	}

	CKeyMgr::Get_Instance()->Key_Reset();

	return 0;
}

void CLogo::Late_Update(void)
{
	if (m_iSceneCount == 0)
	{
		m_pFrameKey = L"NEW";
	}
	else if (m_iSceneCount == 1)
	{
		m_pFrameKey = L"RE";
	}
	else if (m_iSceneCount == 2)
	{
		m_pFrameKey = L"OPTION";
	}
	else if (m_iSceneCount == 3)
	{
		m_pFrameKey = L"LANGUAGE";
	}
	else if (m_iSceneCount == 4)
	{
		m_pFrameKey = L"END";
	}
}

void CLogo::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release(void)
{
}