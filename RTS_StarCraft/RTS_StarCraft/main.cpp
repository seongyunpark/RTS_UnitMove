//
// DREngineDemo
//
// Direct2D 엔진 데모
// 부활한 게임아카데미의 교육용 자료로 생성함
//
// Game Academy 2019/2020/2021
//
// [01/20/2021 LeHideHome]
//

#include "GameManager.h"

// 윈도 관련
HWND g_hWnd;
MSG g_Msg;

// 화면의 크기
const int g_ScreenWidth = 1920;
const int g_ScreenHeight = 1080;

// GameManager 전역 선언
GameManager* pGameManager;

// 콜백 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// 프로그램의 엔트리 포인트. 멀티바이트 프로젝트 기준
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	/// Win32 관련
		// 윈도 클래스
	char szAppName[] = "GameAcademy 2021 Direct2D Demo";
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	// 윈도 클래스 등록
	RegisterClass(&wndclass);

	// 윈도 생성
	g_hWnd = CreateWindow(
		szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		0, 0, g_ScreenWidth, g_ScreenHeight,
		NULL, NULL, hInstance, NULL);

	if (!g_hWnd) return FALSE;

	// 생성된 윈도를 화면에 표시
	ShowWindow(g_hWnd, SW_SHOWNORMAL);
	UpdateWindow(g_hWnd);

	/// 공통 라이브러리

	// 시간 관련
	//m_FPSController

	/// 그래픽스 엔진 관련

	pGameManager = new GameManager();
	pGameManager->Initialize(g_hWnd, g_ScreenWidth, g_ScreenHeight);

	while (true)
	{
		if (PeekMessage(&g_Msg, NULL, 0, 0, PM_REMOVE))
		{
			if (g_Msg.message == WM_QUIT) break;

			DispatchMessage(&g_Msg);
		}
		else
		{
			pGameManager->Update();
			pGameManager->Render();
		}
	}
	return S_OK;
}

// 메시지 핸들러 (윈도 콜백)
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
