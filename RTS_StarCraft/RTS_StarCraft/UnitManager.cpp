#include "UnitManager.h"
#include "UnitDefine.h"

// 지상 유닛들
#include "Unit.h"
#include "GroundUnit.h"
#include "AirUnit.h"
#include "Structure.h"

// 그래픽스 엔진
#include "../DRD2DEngine/DRD2DEngine.h"

UnitManager::UnitManager(DRD2DEngine* pEngine, HWND hwnd)
	: m_pEngine(pEngine), m_hWnd(hwnd), m_NowMousePos(), m_DragStartPos(),
	m_LeftButtonDown(false), m_RightButtonDown(false), m_IsLeftDragging(false)
{
	//m_pEngine = pEngine;
	//m_hwnd = hwnd;
}

UnitManager::~UnitManager()
{
}

void UnitManager::MoveToDestination(int x, int y)
{
	// Unit이 들어있는 자료구조를 순회 한다
	for (Object* unit : m_UnitPool)
	{
		if (unit->GetIsSelected() == true)
		{
			unit->SetDestination(x + rand() % 100 - rand() % 100,
				y + rand() % 100 - rand() % 100);

			unit->SetNowState(eUnitState::eMoving);
		}
	}
}

void UnitManager::SelectUnits_All()
{
	for (Object* unit : m_UnitPool)
	{
		unit->SetIsSelected(true);
	}
}

void UnitManager::DrawSelectBox()
{
	if (m_IsLeftDragging == true)
	{
		m_pEngine->DrawRectangle(m_DragStartPos.x, m_DragStartPos.y,
			m_NowMousePos.x, m_NowMousePos.y, RGB(0, 255, 0));
	}
}

void UnitManager::UpdateAllUnit()
{
	UserInput();

	// 적이 사거리 안에 들어왔는가를 체크한다
	CheckEnemyIsSpotted();

	for (unsigned int i = 0; i < m_UnitPool.size(); i++)
	{
		// 부모의 포인터로 가지고 있다.
		Object* _nowUnit = m_UnitPool[i];
		_nowUnit->Update();
	}

	// 죽은 유닛들을 제거한다
	RemoveDeadUnits();
}

void UnitManager::RenderAllUnit()
{
	/// 다형성을 이용해서 그리기를 한다.
	for (unsigned int i = 0; i < m_UnitPool.size(); i++)
	{
		// 부모의 포인터로 가지고 있다
		Object* _nowUnit = m_UnitPool[i];
		_nowUnit->Render(m_pEngine);
		m_pEngine->DrawSprite(_nowUnit->m_pSprite, _nowUnit->GetPosition().x, _nowUnit->GetPosition().y);
	}
	this->DrawSelectBox();
}

void UnitManager::RenderStatus()
{
	m_pEngine->DrawText(0, 0, "UnitPool : %d", m_UnitPool.size());
}

Object* UnitManager::CreateBackGround(int posX, int posY)
{
	return nullptr;
}

Object* UnitManager::CreateCarrigun(int posX, int posY)
{
	// 캐리건
	GroundUnit* _Carrigun = new GroundUnit(posX, posY, ePlayer::player2);
	_Carrigun->SetSpeed(2.0f);

#pragma region ANIMATION
	// 대기 애니메이션

	// 배열에다가 스프라이트 갯수만 넣고 벡터로는 
	//_Carrigun->m_pAnimation.push_back(_Carrigun->m_pAnimations[0]);

	_Carrigun->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(1, 50, 35, 35, 58, 1);
	_Carrigun->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(1, 179, 35, 36, 58, 1);
	_Carrigun->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(1, 309, 34, 35, 58, 1);
	_Carrigun->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(1, 439, 32, 36, 60, 1);
	_Carrigun->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(1, 569, 30, 38, 61, 1);

	_Carrigun->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(1, 50, 35, 35, 58, 1);
	_Carrigun->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(1, 179, 35, 36, 58, 1);
	_Carrigun->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(1, 309, 34, 35, 58, 1);
	_Carrigun->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(1, 439, 32, 36, 60, 1);

	// 걷기 애니메이션
	_Carrigun->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(1, 50, 35, 35, 38, 1);
	_Carrigun->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(1, 179, 35, 36, 58, 1);
	_Carrigun->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(1, 309, 34, 35, 58, 1);
	_Carrigun->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(1, 439, 32, 36, 60, 1);
	_Carrigun->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(1, 569, 30, 38, 61, 1);

	_Carrigun->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(1, 699, 28, 39, 62, 1);
	_Carrigun->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(1, 830, 27, 39, 62, 1);
	_Carrigun->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(1, 962, 25, 37, 63, 1);
	_Carrigun->m_pAnimations[1][8] = m_pEngine->LoadSpriteFromSheet(1, 1093, 24, 36, 62, 1);

	// 대충 수슶하는  코드....?
	_Carrigun->m_pSprite = _Carrigun->m_pAnimations[0][0];
#pragma endregion

	return _Carrigun;
}

Object* UnitManager::CreateDrone(int posX, int posY)
{
	GroundUnit* _Drone = new GroundUnit(posX, posY, ePlayer::player2);
	_Drone->SetSpeed(5.0f);

#pragma region ANIMATION
	// 대기 애니메이션
	_Drone->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(2, 85, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(2, 345, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(2, 610, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(2, 870, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(2, 1135, 90, 100, 90, 1);

	_Drone->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(2, 85, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(2, 345, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(2, 610, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(2, 870, 90, 100, 90, 1);

	// 걷기 애니메이션
	_Drone->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(2, 85, 90, 100, 90, 1);
	_Drone->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(2, 345, 90, 100, 90, 1);
	_Drone->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(2, 610, 90, 100, 90, 1);
	_Drone->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(2, 870, 90, 100, 90, 1);
	_Drone->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(2, 1135, 90, 100, 90, 1);

	_Drone->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(2, 1395, 90, 100, 90, 1);
	_Drone->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(2, 1660, 90, 100, 90, 1);
	_Drone->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(2, 1923, 90, 100, 90, 1);
	_Drone->m_pAnimations[1][8] = m_pEngine->LoadSpriteFromSheet(2, 2183, 90, 100, 90, 1);

	_Drone->m_pSprite = _Drone->m_pAnimations[0][0];

#pragma endregion

	return _Drone;
}

Object* UnitManager::CreateLava(int posX, int posY)
{
	// 라바
	GroundUnit* _Lava = new GroundUnit(posX, posY, ePlayer::player2);
	_Lava->SetSpeed(5.0f);

#pragma region ANIMATION
	// 대기 애니메이션
	_Lava->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(3, 0, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(3, 80, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(3, 150, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(3, 230, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(3, 305, 10, 70, 45, 1); // 라바

	_Lava->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(3, 0, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(3, 80, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(3, 150, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(3, 230, 10, 70, 45, 1); // 라바

	// 걷기 애니메이션
	_Lava->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(3, 0, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(3, 80, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(3, 150, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(3, 230, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(3, 305, 10, 70, 45, 1); // 라바

	_Lava->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(3, 385, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(3, 460, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(3, 538, 10, 70, 45, 1); // 라바
	_Lava->m_pAnimations[1][8] = m_pEngine->LoadSpriteFromSheet(3, 615, 10, 70, 45, 1); // 라바

	_Lava->m_pSprite = _Lava->m_pAnimations[0][0];

#pragma endregion

	return _Lava;
}

Object* UnitManager::CreateBroodling(int posX, int posY)
{
	// 브루들링
	GroundUnit* _Broodling = new GroundUnit(posX, posY, ePlayer::player2);
	_Broodling->SetSpeed(4.0f);

#pragma region ANIMATION

	// 대기 애니메이션
	_Broodling->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(4, 35, 27, 55, 55, 1); // 브루들링
	_Broodling->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(4, 159, 24, 53, 58, 1); // 브루들링
	_Broodling->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(4, 279, 22, 54, 58, 1); // 브루들링
	_Broodling->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(4, 394, 21, 58, 57, 1); // 브루들링
	_Broodling->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(4, 509, 22, 62, 53, 1); // 브루들링

	_Broodling->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(4, 35, 27, 55, 55, 1); // 브루들링
	_Broodling->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(4, 159, 24, 53, 58, 1); //브루들링
	_Broodling->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(4, 279, 22, 54, 58, 1); //브루들링
	_Broodling->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(4, 394, 21, 58, 57, 1); //브루들링

	// 걷기 애니메이션																		 
	_Broodling->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(4, 35, 27, 55, 55, 1); // 브루들링
	_Broodling->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(4, 159, 24, 53, 58, 1); //브루들링
	_Broodling->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(4, 279, 22, 54, 58, 1); //브루들링
	_Broodling->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(4, 394, 21, 58, 57, 1); //브루들링
	_Broodling->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(4, 509, 22, 62, 53, 1); //브루들링

	_Broodling->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(4, 626, 23, 62, 48, 1); // 라바
	_Broodling->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(4, 743, 25, 62, 48, 1); // 라바
	_Broodling->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(4, 861, 28, 65, 46, 1); // 라바
	_Broodling->m_pAnimations[1][8] = m_pEngine->LoadSpriteFromSheet(4, 980, 29, 71, 47, 1); // 라바

	_Broodling->m_pSprite = _Broodling->m_pAnimations[0][0];

#pragma endregion

	return _Broodling;
}

Object* UnitManager::CreateMutal(int posX, int posY)
{
	AirUnit* _Mutal = new AirUnit(posX, posY, ePlayer::player2);
	_Mutal->SetSpeed(4.0f);

#pragma region ANIMATION
	// 대기 애니메이션
	_Mutal->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(6, 73, 76, 122, 80, 1);
	_Mutal->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(6, 337, 70, 122, 87, 1);
	_Mutal->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(6, 602, 64, 122, 94, 1);
	_Mutal->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(6, 869, 59, 118, 99, 1);
	_Mutal->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(6, 1130, 55, 106, 102, 1);

	_Mutal->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(6, 73, 76, 122, 80, 1);
	_Mutal->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(6, 337, 70, 122, 87, 1);
	_Mutal->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(6, 602, 64, 122, 94, 1);
	_Mutal->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(6, 869, 59, 118, 99, 1);


	// 걷기 애니메이션											 
	_Mutal->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(6, 73, 76, 122, 80, 1);
	_Mutal->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(6, 337, 70, 122, 87, 1);
	_Mutal->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(6, 602, 64, 122, 94, 1);
	_Mutal->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(6, 869, 59, 118, 99, 1);
	_Mutal->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(6, 1130, 55, 106, 102, 1);

	_Mutal->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(6, 1391, 52, 100, 104, 1);
	_Mutal->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(6, 1658, 51, 80, 105, 1);
	_Mutal->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(6, 1918, 50, 80, 107, 1);
	_Mutal->m_pAnimations[1][8] = m_pEngine->LoadSpriteFromSheet(6, 2179, 57, 77, 101, 1);

	_Mutal->m_pSprite = _Mutal->m_pAnimations[0][0];

#pragma endregion

	return _Mutal;
}

Object* UnitManager::CreateGuardian(int posX, int posY)
{
	AirUnit* _Guardian = new AirUnit(posX, posY, ePlayer::player2);
	_Guardian->SetSpeed(2.0f);

#pragma region ANIMATION
	// 대기애니메이션
	_Guardian->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(7, 1302, 1538, 133, 76, 1);
	_Guardian->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(7, 1106, 1543, 134, 82, 1);
	_Guardian->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(7, 894, 1540, 137, 89, 1);
	_Guardian->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(7, 685, 1538, 138, 96, 1);
	_Guardian->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(7, 3204, 279, 138, 90, 1);

	_Guardian->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(7, 1302, 1538, 133, 76, 1);
	_Guardian->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(7, 1106, 1543, 134, 82, 1);
	_Guardian->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(7, 894, 1540, 137, 89, 1);
	_Guardian->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(7, 685, 1538, 138, 96, 1);

	// 걷기 애니메이션
	_Guardian->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(7, 1302, 1538, 133, 76, 1);
	_Guardian->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(7, 1106, 1543, 134, 82, 1);
	_Guardian->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(7, 894, 1540, 137, 89, 1);
	_Guardian->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(7, 685, 1538, 138, 96, 1);
	_Guardian->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(7, 3204, 279, 138, 90, 1);

	_Guardian->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(7, 2995, 277, 139, 98, 1);
	_Guardian->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(7, 2787, 276, 136, 102, 1);
	_Guardian->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(7, 2580, 270, 129, 103, 1);
	_Guardian->m_pAnimations[1][8] = m_pEngine->LoadSpriteFromSheet(7, 2374, 270, 118, 104, 1);

	_Guardian->m_pSprite = _Guardian->m_pAnimations[0][0];

#pragma endregion

	return _Guardian;
}

Object* UnitManager::CreateScourge(int posX, int posY)
{
	AirUnit* _Scourge = new AirUnit(posX, posY, ePlayer::player2);
	_Scourge->SetSpeed(3.0f);

#pragma region ANIMATION
	// 대기애니메이션
	_Scourge->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(8, 416, 484, 51, 38, 1);
	_Scourge->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(8, 320, 482, 51, 40, 1);
	_Scourge->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(8, 224, 481, 50, 40, 1);
	_Scourge->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(8, 125, 481, 51, 41, 1);
	_Scourge->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(8, 26, 481, 51, 42, 1);

	_Scourge->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(8, 416, 484, 51, 38, 1);
	_Scourge->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(8, 320, 482, 51, 40, 1);
	_Scourge->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(8, 224, 481, 50, 40, 1);
	_Scourge->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(8, 125, 481, 51, 41, 1);

	// 걷기 애니메이션
	_Scourge->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(8, 416, 484, 51, 38, 1);
	_Scourge->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(8, 320, 482, 51, 40, 1);
	_Scourge->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(8, 224, 481, 50, 40, 1);
	_Scourge->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(8, 125, 481, 51, 41, 1);
	_Scourge->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(8, 26, 481, 51, 42, 1);

	_Scourge->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(8, 1495, 391, 51, 42, 1);
	_Scourge->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(8, 1398, 392, 47, 41, 1);
	_Scourge->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(8, 1301, 391, 44, 41, 1);
	_Scourge->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(8, 1204, 399, 44, 41, 1);

	_Scourge->m_pSprite = _Scourge->m_pAnimations[0][0];

#pragma endregion

	return _Scourge;
}

Object* UnitManager::CreateOverload(int posX, int posY)
{
	AirUnit* _Overload = new AirUnit(posX, posY, ePlayer::player2);
	_Overload->SetSpeed(2.0f);

#pragma region ANIMATION
	// 대기애니메이션
	_Overload->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(9, 1302, 1538, 133, 76, 1);
	_Overload->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(9, 1106, 1543, 134, 82, 1);
	_Overload->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(9, 894, 1540, 137, 89, 1);
	_Overload->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(9, 685, 1538, 138, 96, 1);
	_Overload->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(9, 3204, 279, 138, 90, 1);

	_Overload->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(9, 1302, 1538, 133, 76, 1);
	_Overload->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(9, 1106, 1543, 134, 82, 1);
	_Overload->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(9, 894, 1540, 137, 89, 1);
	_Overload->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(9, 685, 1538, 138, 96, 1);

	// 걷기 애니메이션
	_Overload->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(9, 538, 751, 82, 109, 1);
	_Overload->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(9, 377, 748, 84, 116, 1);
	_Overload->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(9, 210, 746, 90, 121, 1);
	_Overload->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(9, 41, 745, 97, 125, 1);
	_Overload->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(9, 2512, 562, 103, 127, 1);

	_Overload->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(9, 2340, 562, 114, 126, 1);
	_Overload->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(9, 2170, 562, 121, 124, 1);
	_Overload->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(9, 2001, 564, 125, 120, 1);
	_Overload->m_pAnimations[1][8] = m_pEngine->LoadSpriteFromSheet(9, 1835, 566, 126, 121, 1);

	_Overload->m_pSprite = _Overload->m_pAnimations[0][0];

#pragma endregion

	return _Overload;
}

Object* UnitManager::CreateTownHall(int posX, int posY)
{
	return nullptr;
}

void UnitManager::SetPlayerIndex(Object* unit, ePlayer index)
{
	unit->SetPlayerIndex(index);
}

Object* UnitManager::CheckEnemyIsSpotted()
{
	// 전체 유닛을 돌면서
	for (Object* nowUnit : m_UnitPool)
	{
		// 만약 나의 상태가 공격중이었다면 패스
		if (nowUnit->GetNowState() == eUnitState::eAttacking) continue;

		// 전체 대상 유닛을 돌면서
		for (Object* targetUnit : m_UnitPool)
		{
			// 대상 유닛이 적일 경우
			if (nowUnit->GetPlayerIndex() != targetUnit->GetPlayerIndex())
			{
				// 현재 유닛의 위치벡터와 적의 위치벡터를 빼서 간격을 잰다
				CPoint _disVec = nowUnit->GetPosition() - targetUnit->GetPosition();
				float _distance = abs(_disVec.Length());

				// 일정 이하의 간격일 경우
				if (_distance <= nowUnit->GetRange())
				{
					// 나의 상태를 공격 중으로 바꿈
					nowUnit->SetNowState(eUnitState::eAttacking);

					// 그 적의 포인터를 리턴하지말고 바로 싸워라
					nowUnit->SetTarget(targetUnit);
				}
			}
		}
	}
	//모두 돌았는데 못 찾았을 경우
	//nullptr 리턴!
	return nullptr;
}

void UnitManager::RemoveDeadUnits()
{
	std::vector<Object*>::iterator it_unit;
	it_unit = m_UnitPool.begin();

	for (unsigned int i = 0; i < m_UnitPool.size();)
	{
		if (m_UnitPool[i]->GetNowState() == eUnitState::eDead)
		{
			/// 힙에 할당된 Unitbase 객체를 delete
			delete m_UnitPool[i];

			/// 그 포인터를 보관하던 컨테이너에서 하나의 요소를 제거
			m_UnitPool.erase(m_UnitPool.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void UnitManager::RemoveDeadUnits2()
{
	std::vector<Object*>::iterator it_unit;

	for (it_unit = m_UnitPool.begin(); it_unit != m_UnitPool.end();)
	{
		Object* _nowUnit = *it_unit;
		if (_nowUnit->GetNowState() == eUnitState::eDead)
		{
			delete _nowUnit;

			it_unit = m_UnitPool.erase(it_unit);
		}
		else
		{
			it_unit++;
		}
	}
}

void UnitManager::CreateUnit(eUnitType type, int posX, int posY, ePlayer playerIndex, int hp)
{
	Object* _pUnit = nullptr;
	// 음..오브젝트 말고 Unit에서 만들었다면 여기다 Unit으로 해줘도 되나

	switch (type)
	{
	case eUnitType::Lava:
	{
		_pUnit = CreateLava(posX, posY);
		_pUnit->SetPlayerIndex(playerIndex);
		_pUnit->SetHPMax(hp);
		_pUnit->SetRange(100.0f);
		_pUnit->SetAttackPower(100);
	}
	break;
	case eUnitType::Drone:
	{
		_pUnit = CreateDrone(posX, posY);
		_pUnit->SetPlayerIndex(playerIndex);
		_pUnit->SetHPMax(hp);
		_pUnit->SetRange(100.0f);
		_pUnit->SetAttackPower(40);
	}
	break;
	case eUnitType::Muatalisk:
	{
		_pUnit = CreateMutal(posX, posY);
		_pUnit->SetPlayerIndex(playerIndex);
		_pUnit->SetHPMax(hp);
		_pUnit->SetRange(100.0f);
		_pUnit->SetAttackPower(50);
	}
	break;
	case eUnitType::Broodling:
	{
		_pUnit = CreateBroodling(posX, posY);
		_pUnit->SetPlayerIndex(playerIndex);
		_pUnit->SetHPMax(hp);
		_pUnit->SetRange(100.0f);
		_pUnit->SetAttackPower(30);
	}
	break;
	case eUnitType::Carrigun:
	{
		_pUnit = CreateCarrigun(posX, posY);
		_pUnit->SetPlayerIndex(playerIndex);
		_pUnit->SetHPMax(hp);
		_pUnit->SetRange(100.0f);
		_pUnit->SetAttackPower(10);
	}
	break;
	case eUnitType::Guardian:
	{
		_pUnit = CreateGuardian(posX, posY);
		_pUnit->SetPlayerIndex(playerIndex);
		_pUnit->SetHPMax(hp);
		_pUnit->SetRange(100.0f);
		_pUnit->SetAttackPower(40);
	}
	break;
	case eUnitType::Scourge:
	{
		_pUnit = CreateScourge(posX, posY);
		_pUnit->SetPlayerIndex(playerIndex);
		_pUnit->SetHPMax(hp);
		_pUnit->SetRange(100.0f);
		_pUnit->SetAttackPower(30);
	}
	break;
	case eUnitType::Overload:
	{
		_pUnit = CreateOverload(posX, posY);
		_pUnit->SetPlayerIndex(playerIndex);
		_pUnit->SetHPMax(hp);
		_pUnit->SetRange(100.0f);
		_pUnit->SetAttackPower(60);
	}
	break;
	default:
	{
	}
	break;
	}
	// 생성 순서에 따라서 유니크한 인덱스를 부여해준다.
	static int _count = 0;
	_pUnit->SetIndex(_count);
	_count++;

	// 한번에 유닛들 넣어준다
	m_UnitPool.push_back(_pUnit);
}

void UnitManager::SelectUnits_Area(int left, int top, int right, int bottom)
{
	// 드래그를 좌상에서 우하로만 하지 않을 경우가 있다. 이경우는 left 와 top 이 작은것을 방지하기 위해
	if (right < left) { Swap(left, right); }
	if (bottom < top) { Swap(top, bottom); }

	// 전통적인 버전
	for (unsigned int i = 0; i < m_UnitPool.size(); i++)
	{
		Object* unit = m_UnitPool[i];

		if (left <= unit->GetPosition().x && unit->GetPosition().x <= right
			&& top <= unit->GetPosition().y && unit->GetPosition().y <= bottom)
		{
			unit->SetIsSelected(true);
		}
		else
		{
			unit->SetIsSelected(false);
		}
	}
}

void UnitManager::Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int UnitManager::GetRand(int base, int randfactor)
{
	return base - (rand() % randfactor) + (rand() % randfactor);
}

void UnitManager::UserInput()
{
	// 마우스 입력을 받는다
	GetCursorPos(&m_NowMousePos);

	RECT rt;
	GetWindowRect(m_hWnd, &rt);
	m_NowMousePos.x -= rt.left + 5;
	m_NowMousePos.y -= rt.top + 23;

	if (GetAsyncKeyState('1') & 0x8001)
	{								// 사거리 범위 지정
		CreateUnit(eUnitType::Lava, GetRand(200, 100), GetRand(500, 100),
			ePlayer::player1, 1000);
	}
	if (GetAsyncKeyState('2') & 0x8001)
	{
		CreateUnit(eUnitType::Drone, GetRand(300, 100), GetRand(500, 100),
			ePlayer::player1, 1000);
	}
	if (GetAsyncKeyState('3') & 0x8001)
	{
		CreateUnit(eUnitType::Carrigun, GetRand(400, 100), GetRand(600, 300),
			ePlayer::player1, 400);
	}
	if (GetAsyncKeyState('4') & 0x8001)
	{
		CreateUnit(eUnitType::Broodling, GetRand(500, 100), GetRand(100, 300),
			ePlayer::player1, 300);
	}
	// 인덱스 범위를 넘어서서 오류가 난다.
	// if (GetAsyncKeyState('5') & 0x8001)
	// {
	// 	CreateUnit(eUnitType::Zergling, GetRand(600, 100), GetRand(200, 300),
	// 		ePlayer::player1, 200);
	// }

	if (GetAsyncKeyState('6') & 0x8001)
	{
		CreateUnit(eUnitType::Muatalisk, GetRand(100, 900), GetRand(700, 300),
			ePlayer::player2, 600);
	}
	if (GetAsyncKeyState('7') & 0x8001)
	{
		CreateUnit(eUnitType::Guardian, GetRand(200, 900), GetRand(700, 300),
			ePlayer::player2, 600);
	}
	if (GetAsyncKeyState('8') & 0x8001)
	{
		CreateUnit(eUnitType::Scourge, GetRand(300, 900), GetRand(700, 300),
			ePlayer::player2, 600);
	}
	if (GetAsyncKeyState('9') & 0x8001)
	{
		CreateUnit(eUnitType::Overload, GetRand(400, 900), GetRand(700, 300),
			ePlayer::player2, 600);
	}

	if (::GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		// Unit이 들어있는 자료구조를 순회
		for (unsigned int i = 0; i < m_UnitPool.size(); i++)
		{
			Object* _nowUnit = m_UnitPool[i];
			_nowUnit->SetPosition(300, 300);
		}
	}

	if (::GetAsyncKeyState(VK_RETURN) & 0x8001)
	{
		// Unit 이 들어있는 자료구조를 순회
		for (unsigned int i = 0; i < m_UnitPool.size(); i++)
		{
			Object* _nowUnit = m_UnitPool[i];
			_nowUnit->SetPosition(100, 100);
		}
	}

	if (GetAsyncKeyState(VK_F2) & 0x8001)
	{
		SelectUnits_All();
	}

	// 마우스 우측 버튼
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		// 선택된 유닛들만 이동을 해 준다.
		MoveToDestination(m_NowMousePos.x, m_NowMousePos.y);
	}

	// 마우스 입력을 좀 더 세분화 한다
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		// 눌린 상태
		// 이전에 안눌려져 있다가, 이번 프레임에 눌린 것
		if (m_RightButtonDown == false)
		{
		}

		m_RightButtonDown = true;
	}
	else
	{
		// 안눌린 상태
		// 이전에 눌려져 있다가, 이번 프레임에 떨어진 
		if (m_RightButtonDown == true)
		{
		}

		m_RightButtonDown = false;
	}

	// 마우스 입력을 좀 더 세분화 한다
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		// 눌린 상태

		// 이전에 안 눌려져 있다가, 이번 프레임에 눌린 것
		if (m_LeftButtonDown == false)
		{
			m_DragStartPos = m_NowMousePos;
			m_IsLeftDragging = true;
		}
		m_LeftButtonDown = true;
	}
	else
	{
		// 안눌린 상태

		// 이전에 눌려져 있다가, 이번 프레임에 떨어진 것
		if (m_LeftButtonDown == true)
		{
			SelectUnits_Area(m_DragStartPos.x, m_DragStartPos.y,
				m_NowMousePos.x, m_NowMousePos.y);
		}
		m_LeftButtonDown = false;

		m_IsLeftDragging = false;
	}
}
