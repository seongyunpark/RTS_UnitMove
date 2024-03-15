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

	// 화면의 크기
	int m_ScreenWidth = 1024;
	int m_ScreenHeight = 768;

	// 윈도 관련
	HWND m_hWnd;

	// 그래픽스 엔진
	DRD2DEngine* m_pDREngine;
	DRSprite* m_pBackGround;

	// 유닛 매니저
	UnitManager* m_pUnitManager;

	/// 키 입력
	bool m_KeyUp;
	bool m_KeyDown;
	bool m_KeyLeft;
	bool m_KeyRight;

	//// 프레임 제어
	//DRTimer m_FPSController;


};

