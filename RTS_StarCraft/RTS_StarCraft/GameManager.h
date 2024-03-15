#pragma once

#include <windows.h>
#include "../DRD2DEngine/DRD2DEngine.h"
//#include "../DRCommonLib/DRTimer.h"

#pragma comment(lib, "../Debug/DRD2DEngine.lib")
//#pragma comment(lib, "../Debug/DRCommonLib.lib")

//#pragma comment(lib, "winmm.lib")

// #include "Object.h"
#include "UnitDefine.h"
#include "UnitManager.h"


class GameManager
{
public:
	GameManager();
	~GameManager();;

	void Initialize(HWND hWnd, int screenWidth, int screenHeight);

	void Update();

	void Render();

private:

	// ȭ���� ũ��
	int m_ScreenWidth = 1024;
	int m_ScreenHeight = 768;

	// ���� ����
	HWND m_hWnd;

	// �׷��Ƚ� ����
	DRD2DEngine* m_pDREngine;
	DRSprite* m_pBackGround;

	// ���� �Ŵ���
	UnitManager* m_pUnitManager;

	/// Ű �Է�
	bool m_KeyUp;
	bool m_KeyDown;
	bool m_KeyLeft;
	bool m_KeyRight;

	//// ������ ����
	//DRTimer m_FPSController;


};

