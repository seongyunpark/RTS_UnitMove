//
// DREngineDemo
//
// Direct2D ���� ����
// ��Ȱ�� ���Ӿ�ī������ ������ �ڷ�� ������
//
// Game Academy 2019/2020/2021
//
// [01/20/2021 LeHideHome]
//

#include "GameManager.h"

// ���� ����
HWND g_hWnd;
MSG g_Msg;

// ȭ���� ũ��
const int g_ScreenWidth = 1920;
const int g_ScreenHeight = 1080;

// GameManager ���� ����
GameManager* pGameManager;

// �ݹ� ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// ���α׷��� ��Ʈ�� ����Ʈ. ��Ƽ����Ʈ ������Ʈ ����
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	/// Win32 ����
		// ���� Ŭ����
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

	// ���� Ŭ���� ���
	RegisterClass(&wndclass);

	// ���� ����
	g_hWnd = CreateWindow(
		szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		0, 0, g_ScreenWidth, g_ScreenHeight,
		NULL, NULL, hInstance, NULL);

	if (!g_hWnd) return FALSE;

	// ������ ������ ȭ�鿡 ǥ��
	ShowWindow(g_hWnd, SW_SHOWNORMAL);
	UpdateWindow(g_hWnd);

	/// ���� ���̺귯��

	// �ð� ����
	//m_FPSController

	/// �׷��Ƚ� ���� ����

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

// �޽��� �ڵ鷯 (���� �ݹ�)
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
