// DefaultWindow.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "KATANAZERO.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;
DWORD	g_dwTimer;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);		// 창 스타일을 제어하기 위한 함수
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// 메모리에 할당되는 실체. 즉 객체, apiㅇ에서 현재 구동되고 있는 프로그램을 의미
	_In_opt_ HINSTANCE hPrevInstance,	// 전에 실행되었던 인스턴스의 핸들이 전달 됨, 없을 경우 자동으로 NULL값으로 채워짐
	_In_ LPWSTR    lpCmdLine,			// 문자열 포인터를 의미
	_In_ int       nCmdShow)			// 창 출력에 대한 단축키 명령

{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_KATANAZERO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KATANAZERO));

	MSG msg;
	msg.message = WM_NULL;

	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// GetTickCount() : 운영체제가 시작하면 내부적으로 흐른 시간을 정수 형태로 반환
	// 1초라는 시간의 값을 대략 1000정도 값이 증가했을 때로 판단

	//		1000
	DWORD	dwOldTime = GetTickCount();
	CMainGame*		pMainGame = new CMainGame;;
	pMainGame->Initialize();

	// 기본 메시지 루프입니다.
	while (true)
	{
		//	PeekMessage : 메세지를 읽어오면 true, 메세지가 없다면 false를 반환

		// PM_REMOVE : 메세지를 메세지 큐로부터 읽어옴과 동시에 메세지 큐에서 제거
		// PM_NOREMOVE : 메세지 큐에 메세지가 있는지 존재만 파악
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			// 메뉴 기능의 단축키가 제대로 작동하는지 검사하는 함수
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				// 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 해주는 함수
				TranslateMessage(&msg);

				// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램의 메세지 처리(wndproc)함수로 전달하는 함수
				DispatchMessage(&msg);
			}
		}

		else
		{
			// 1020 + 10     1011
			if (dwOldTime + g_dwTimer < GetTickCount())
			{
				pMainGame->Update();
				pMainGame->Late_Update();
				pMainGame->Render();

				// 1020
				dwOldTime = GetTickCount();
			}
		}
	}

	if (nullptr != pMainGame)
	{
		delete pMainGame;
		pMainGame = nullptr;
	}

	GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KATANAZERO));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	RECT	rc{ 0, 0, WINCX, WINCY };


	// rc = rc크기 + 기본 창 스타일 + 메뉴 바 사이즈 고려 여부
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		200, 100,		// 생성한 창을 출력할 위치
		rc.right - rc.left, rc.bottom - rc.top,		// 생성한 창의 가로, 세로 사이즈
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			break;
		case IDM_EXIT:
			DestroyWindow(g_hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

