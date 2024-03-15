#pragma once
#include <vector>
#include <windows.h>
#include "UnitDefine.h"

class Object;
class DRD2DEngine;

// 게임 내의 모든 유닛들을 생성, 삭제, 관리하는 클래스
class UnitManager
{
public:
	UnitManager(DRD2DEngine* pEngine, HWND hwnd);
	~UnitManager();

private:
	// 게임 내의 존재하는 모든 유닛(+건물)의 부모의 포인터
	std::vector<Object*> m_UnitPool;

	// 게임 내의 존재하는 모든 건물의 부모의 포인터
	std::vector<Object*> m_StructPool;

	// 그래픽스 엔진을 가지고 있는다
	DRD2DEngine* m_pEngine;

	// 윈도 핸들도 가지고 있는다
	HWND m_hWnd;


	// 마우스 위치
	POINT m_NowMousePos;
	POINT m_DragStartPos;

	// 버튼이 눌렸는지 안눌렸는지 플래그
	bool m_LeftButtonDown;
	bool m_RightButtonDown;

	// 드래그 플래그
	bool m_IsLeftDragging;

private:
	// 유저 입력 받는다
	void UserInput();

	void DrawSelectBox();

public:
	// 전체 유닛 처리를 해 준다.
	void UpdateAllUnit();		// 업데이트
	void RenderAllUnit();		// 그리기
	void RenderStatus();		// 유닛 매니저의 상태를 그린다

	// 하나의 함수로 다른 유닛을 생성한다
	void CreateUnit(eUnitType type, int posX, int posY, ePlayer playerIndex, int hp);

private:
	// 배경 만들어주기
	Object* CreateBackGround(int posX, int posY);

	Object* CreateTownHall(int posX, int posY);

	// 유닛 생성해준다. 수동으로 하나하나
	// Ground Unit
	Object* CreateCarrigun(int posX, int posY);
	Object* CreateDrone(int posX, int posY);
	Object* CreateLava(int posX, int posY);
	Object* CreateBroodling(int posX, int posY);
	// Air Unit
	Object* CreateMutal(int posX, int posY);
	Object* CreateGuardian(int posX, int posY);
	Object* CreateScourge(int posX, int posY);
	Object* CreateOverload(int posX, int posY);
	//Object* CreateDevourer(int posX, int posY);
	//Object* Create(int posX, int posY);


	void SetPlayerIndex(Object* unit, ePlayer index);

	// 사거리 안에 적이 들어왔는가를 체크한다
	Object* CheckEnemyIsSpotted();

	void RemoveDeadUnits();
	void RemoveDeadUnits2();

public:
	// 유닛들을 선택한다 (특정 범위에 들어온)
	void SelectUnits_Area(int left, int top, int right, int bottom);
	void MoveToDestination(int x, int y);
	void SelectUnits_All();

private:
	// 마우스포인터대로 사각형 그릴 때 좌상단시작이 아니어도 가능하도록 스왑해주는 함수
	void Swap(int& a, int& b);
	int GetRand(int base, int randfactor);		//	이건 뭐지
};

