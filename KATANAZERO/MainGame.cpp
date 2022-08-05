#include "stdafx.h"
#include "MainGame.h"

#include "ObjMgr.h"

#include "AbstractFactory.h"
#include "Player.h"

#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "SceneMgr.h"
#include "SoundMgr.h"

int		 g_iFinished = 0;

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/Back.bmp", L"Back");
	CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE_1);
	CSoundMgr::Get_Instance()->Initialize();

#ifdef _DEBUG
	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}
#endif // _DEBUG
}


void CMainGame::Update(void)
{
	CSceneMgr::Get_Instance()->Update();
	CKeyMgr::Get_Instance()->Key_Reset();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainGame::Render(void)
{
	// fps
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CSceneMgr::Get_Instance()->Render(hMemDC);
}

void CMainGame::Release(void)
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	CSoundMgr::Get_Instance()->StopAll();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
