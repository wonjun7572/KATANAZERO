#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;


CLineMgr::CLineMgr()
{
	ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
}


CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::Collision_Line(float& fX, float& fY, float* pY)
{
	if (m_LineList.empty())
		return false;

	bool bCheck = true;

	float fHighest_Y = 0.f;

	for (auto& iter : m_LineList)
	{
		if (fX >= iter->Get_LineInfo().tLeftPt.fX  &&
			fX <= iter->Get_LineInfo().tRightPt.fX)
		{
			float x1 = iter->Get_LineInfo().tLeftPt.fX;
			float x2 = iter->Get_LineInfo().tRightPt.fX;
			float y1 = iter->Get_LineInfo().tLeftPt.fY;
			float y2 = iter->Get_LineInfo().tRightPt.fY;

			float fCheck_Y = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

			if ((fCheck_Y >= fY) && (fHighest_Y > fCheck_Y) || (bCheck && fCheck_Y >= fY))
			{
				fHighest_Y = fCheck_Y;
				bCheck = false;
			}
		}
	}

	if (!bCheck)
	{
		*pY = fHighest_Y;
		return true;
	}

	return false;
}

void CLineMgr::Save_Line(void)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_1)
	{
		HANDLE		hFile = CreateFile(L"../Data/Line_1.dat",		// 파일의 경로와 이름
			GENERIC_WRITE,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
			NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
			NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
			CREATE_ALWAYS,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
			FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
			NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
			return;
		}

		DWORD	dwByte = 0;

		for (auto& iter : m_LineList)
			WriteFile(hFile, &(iter->Get_LineInfo()), sizeof(LINE), &dwByte, nullptr);

		CloseHandle(hFile);

		MessageBox(g_hWnd, _T("Save 완료"), L"Success", MB_OK);
	}
	else if(CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_2)
	{
		HANDLE		hFile = CreateFile(L"../Data/Line_2.dat",		// 파일의 경로와 이름
			GENERIC_WRITE,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
			NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
			NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
			CREATE_ALWAYS,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
			FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
			NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
			return;
		}

		DWORD	dwByte = 0;

		for (auto& iter : m_LineList)
			WriteFile(hFile, &(iter->Get_LineInfo()), sizeof(LINE), &dwByte, nullptr);

		CloseHandle(hFile);

		MessageBox(g_hWnd, _T("Save 완료"), L"Success", MB_OK);
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS)
	{
		HANDLE		hFile = CreateFile(L"../Data/Line_Boss.dat",		// 파일의 경로와 이름
			GENERIC_WRITE,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
			NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
			NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
			CREATE_ALWAYS,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
			FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
			NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
			return;
		}

		DWORD	dwByte = 0;

		for (auto& iter : m_LineList)
			WriteFile(hFile, &(iter->Get_LineInfo()), sizeof(LINE), &dwByte, nullptr);

		CloseHandle(hFile);

		MessageBox(g_hWnd, _T("Save 완료"), L"Success", MB_OK);
	}

}

void CLineMgr::Load_Line(void)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_1)
	{
		{
			HANDLE		hFile = CreateFile(L"../Data/Line_1.dat",		// 파일의 경로와 이름
				GENERIC_READ,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
				NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
				NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
				OPEN_EXISTING,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
				FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
				NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

			if (INVALID_HANDLE_VALUE == hFile)
			{
				MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
				return;
			}

			DWORD	dwByte = 0;

			LINE	tInfo{};

			while (true)
			{
				ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				m_LineList.push_back(new CLine(tInfo));
			}

			CloseHandle(hFile);
		}
		{
			HANDLE		hFile = CreateFile(L"../Data/Wall_1.dat",		// 파일의 경로와 이름
				GENERIC_READ,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
				NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
				NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
				OPEN_EXISTING,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
				FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
				NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

			if (INVALID_HANDLE_VALUE == hFile)
			{
				MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
				return;
			}

			DWORD	dwByte = 0;

			INFO	tWInfo{};

			while (true)
			{
				ReadFile(hFile, &tWInfo, sizeof(INFO), &dwByte, nullptr);

				if (0 == dwByte)
					break;
				m_WallList.push_back(new CWall(tWInfo));
			}

			for (auto iter : m_WallList)
				CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, iter);

			CloseHandle(hFile);
		}
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_2)
	{
		{
			HANDLE		hFile = CreateFile(L"../Data/Line_2.dat",		// 파일의 경로와 이름
				GENERIC_READ,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
				NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
				NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
				OPEN_EXISTING,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
				FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
				NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

			if (INVALID_HANDLE_VALUE == hFile)
			{
				MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
				return;
			}

			DWORD	dwByte = 0;

			LINE	tInfo{};

			while (true)
			{
				ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				m_LineList.push_back(new CLine(tInfo));
			}

			CloseHandle(hFile);
		}
		{
			HANDLE		hFile = CreateFile(L"../Data/Wall_2.dat",		// 파일의 경로와 이름
				GENERIC_READ,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
				NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
				NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
				OPEN_EXISTING,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
				FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
				NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

			if (INVALID_HANDLE_VALUE == hFile)
			{
				MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
				return;
			}

			DWORD	dwByte = 0;

			INFO	tWInfo{};

			while (true)
			{
				ReadFile(hFile, &tWInfo, sizeof(INFO), &dwByte, nullptr);

				if (0 == dwByte)
					break;
				m_WallList.push_back(new CWall(tWInfo));
			}

			for (auto iter : m_WallList)
				CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, iter);

			CloseHandle(hFile);
		}
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS)
	{
		{
			HANDLE		hFile = CreateFile(L"../Data/Line_3.dat",		// 파일의 경로와 이름
				GENERIC_READ,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
				NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
				NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
				OPEN_EXISTING,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
				FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
				NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

			if (INVALID_HANDLE_VALUE == hFile)
			{
				MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
				return;
			}

			DWORD	dwByte = 0;

			LINE	tInfo{};

			while (true)
			{
				ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				m_LineList.push_back(new CLine(tInfo));
			}

			CloseHandle(hFile);
		}
		{
			HANDLE		hFile = CreateFile(L"../Data/Wall_3.dat",		// 파일의 경로와 이름
				GENERIC_READ,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
				NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
				NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
				OPEN_EXISTING,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
				FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
				NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

			if (INVALID_HANDLE_VALUE == hFile)
			{
				MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
				return;
			}

			DWORD	dwByte = 0;

			INFO	tWInfo{};

			while (true)
			{
				ReadFile(hFile, &tWInfo, sizeof(INFO), &dwByte, nullptr);

				if (0 == dwByte)
					break;
				m_WallList.push_back(new CWall(tWInfo));
			}

			for (auto iter : m_WallList)
				CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, iter);

			CloseHandle(hFile);
		}
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_PRE_STAGE_BOSS)
	{
		{
			HANDLE		hFile = CreateFile(L"../Data/Line_4.dat",		// 파일의 경로와 이름
				GENERIC_READ,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
				NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
				NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
				OPEN_EXISTING,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
				FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
				NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

			if (INVALID_HANDLE_VALUE == hFile)
			{
				MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
				return;
			}

			DWORD	dwByte = 0;

			LINE	tInfo{};

			while (true)
			{
				ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

				if (0 == dwByte)
					break;

				m_LineList.push_back(new CLine(tInfo));
			}

			CloseHandle(hFile);
		}
		{
			HANDLE		hFile = CreateFile(L"../Data/Wall_4.dat",		// 파일의 경로와 이름
				GENERIC_READ,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
				NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
				NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
				OPEN_EXISTING,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
				FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
				NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

			if (INVALID_HANDLE_VALUE == hFile)
			{
				MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
				return;
			}

			DWORD	dwByte = 0;

			INFO	tWInfo{};

			while (true)
			{
				ReadFile(hFile, &tWInfo, sizeof(INFO), &dwByte, nullptr);

				if (0 == dwByte)
					break;
				m_WallList.push_back(new CWall(tWInfo));
			}

			for (auto iter : m_WallList)
				CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, iter);

			CloseHandle(hFile);
		}
	}
}

void CLineMgr::Initialize(void)
{
	Load_Line();
}

int CLineMgr::Update(void)
{
	return 0;
}

void CLineMgr::Late_Update(void)
{

}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();

	m_WallList.clear();
}
