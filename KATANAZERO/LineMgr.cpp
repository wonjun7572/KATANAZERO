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
		HANDLE		hFile = CreateFile(L"../Data/Line_1.dat",		// ������ ��ο� �̸�
			GENERIC_WRITE,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
			NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
			NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
			CREATE_ALWAYS,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
			FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
			NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
			return;
		}

		DWORD	dwByte = 0;

		for (auto& iter : m_LineList)
			WriteFile(hFile, &(iter->Get_LineInfo()), sizeof(LINE), &dwByte, nullptr);

		CloseHandle(hFile);

		MessageBox(g_hWnd, _T("Save �Ϸ�"), L"Success", MB_OK);
	}
	else if(CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_2)
	{
		HANDLE		hFile = CreateFile(L"../Data/Line_2.dat",		// ������ ��ο� �̸�
			GENERIC_WRITE,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
			NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
			NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
			CREATE_ALWAYS,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
			FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
			NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
			return;
		}

		DWORD	dwByte = 0;

		for (auto& iter : m_LineList)
			WriteFile(hFile, &(iter->Get_LineInfo()), sizeof(LINE), &dwByte, nullptr);

		CloseHandle(hFile);

		MessageBox(g_hWnd, _T("Save �Ϸ�"), L"Success", MB_OK);
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_BOSS)
	{
		HANDLE		hFile = CreateFile(L"../Data/Line_Boss.dat",		// ������ ��ο� �̸�
			GENERIC_WRITE,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
			NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
			NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
			CREATE_ALWAYS,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
			FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
			NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
			return;
		}

		DWORD	dwByte = 0;

		for (auto& iter : m_LineList)
			WriteFile(hFile, &(iter->Get_LineInfo()), sizeof(LINE), &dwByte, nullptr);

		CloseHandle(hFile);

		MessageBox(g_hWnd, _T("Save �Ϸ�"), L"Success", MB_OK);
	}

}

void CLineMgr::Load_Line(void)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE_1)
	{
		{
			HANDLE		hFile = CreateFile(L"../Data/Line_1.dat",		// ������ ��ο� �̸�
				GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
				NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
				NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
				OPEN_EXISTING,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
				FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
				NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

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
			HANDLE		hFile = CreateFile(L"../Data/Wall_1.dat",		// ������ ��ο� �̸�
				GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
				NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
				NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
				OPEN_EXISTING,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
				FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
				NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

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
			HANDLE		hFile = CreateFile(L"../Data/Line_2.dat",		// ������ ��ο� �̸�
				GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
				NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
				NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
				OPEN_EXISTING,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
				FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
				NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

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
			HANDLE		hFile = CreateFile(L"../Data/Wall_2.dat",		// ������ ��ο� �̸�
				GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
				NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
				NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
				OPEN_EXISTING,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
				FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
				NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

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
			HANDLE		hFile = CreateFile(L"../Data/Line_3.dat",		// ������ ��ο� �̸�
				GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
				NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
				NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
				OPEN_EXISTING,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
				FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
				NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

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
			HANDLE		hFile = CreateFile(L"../Data/Wall_3.dat",		// ������ ��ο� �̸�
				GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
				NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
				NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
				OPEN_EXISTING,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
				FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
				NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

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
			HANDLE		hFile = CreateFile(L"../Data/Line_4.dat",		// ������ ��ο� �̸�
				GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
				NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
				NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
				OPEN_EXISTING,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
				FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
				NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

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
			HANDLE		hFile = CreateFile(L"../Data/Wall_4.dat",		// ������ ��ο� �̸�
				GENERIC_READ,			// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
				NULL,					// ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)	 
				NULL,					// ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
				OPEN_EXISTING,			// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
				FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
				NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

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
