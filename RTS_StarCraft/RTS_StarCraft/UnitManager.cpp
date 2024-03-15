#include "UnitManager.h"
#include "UnitDefine.h"

// ���� ���ֵ�
#include "Unit.h"
#include "GroundUnit.h"
#include "AirUnit.h"
#include "Structure.h"

// �׷��Ƚ� ����
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
	// Unit�� ����ִ� �ڷᱸ���� ��ȸ �Ѵ�
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

	// ���� ��Ÿ� �ȿ� ���Դ°��� üũ�Ѵ�
	CheckEnemyIsSpotted();

	for (unsigned int i = 0; i < m_UnitPool.size(); i++)
	{
		// �θ��� �����ͷ� ������ �ִ�.
		Object* _nowUnit = m_UnitPool[i];
		_nowUnit->Update();
	}

	// ���� ���ֵ��� �����Ѵ�
	RemoveDeadUnits();
}

void UnitManager::RenderAllUnit()
{
	/// �������� �̿��ؼ� �׸��⸦ �Ѵ�.
	for (unsigned int i = 0; i < m_UnitPool.size(); i++)
	{
		// �θ��� �����ͷ� ������ �ִ�
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
	// ĳ����
	GroundUnit* _Carrigun = new GroundUnit(posX, posY, ePlayer::player2);
	_Carrigun->SetSpeed(2.0f);

#pragma region ANIMATION
	// ��� �ִϸ��̼�

	// �迭���ٰ� ��������Ʈ ������ �ְ� ���ͷδ� 
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

	// �ȱ� �ִϸ��̼�
	_Carrigun->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(1, 50, 35, 35, 38, 1);
	_Carrigun->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(1, 179, 35, 36, 58, 1);
	_Carrigun->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(1, 309, 34, 35, 58, 1);
	_Carrigun->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(1, 439, 32, 36, 60, 1);
	_Carrigun->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(1, 569, 30, 38, 61, 1);

	_Carrigun->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(1, 699, 28, 39, 62, 1);
	_Carrigun->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(1, 830, 27, 39, 62, 1);
	_Carrigun->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(1, 962, 25, 37, 63, 1);
	_Carrigun->m_pAnimations[1][8] = m_pEngine->LoadSpriteFromSheet(1, 1093, 24, 36, 62, 1);

	// ���� �����ϴ�  �ڵ�....?
	_Carrigun->m_pSprite = _Carrigun->m_pAnimations[0][0];
#pragma endregion

	return _Carrigun;
}

Object* UnitManager::CreateDrone(int posX, int posY)
{
	GroundUnit* _Drone = new GroundUnit(posX, posY, ePlayer::player2);
	_Drone->SetSpeed(5.0f);

#pragma region ANIMATION
	// ��� �ִϸ��̼�
	_Drone->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(2, 85, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(2, 345, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(2, 610, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(2, 870, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(2, 1135, 90, 100, 90, 1);

	_Drone->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(2, 85, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(2, 345, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(2, 610, 90, 100, 90, 1);
	_Drone->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(2, 870, 90, 100, 90, 1);

	// �ȱ� �ִϸ��̼�
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
	// ���
	GroundUnit* _Lava = new GroundUnit(posX, posY, ePlayer::player2);
	_Lava->SetSpeed(5.0f);

#pragma region ANIMATION
	// ��� �ִϸ��̼�
	_Lava->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(3, 0, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(3, 80, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(3, 150, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(3, 230, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(3, 305, 10, 70, 45, 1); // ���

	_Lava->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(3, 0, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(3, 80, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(3, 150, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(3, 230, 10, 70, 45, 1); // ���

	// �ȱ� �ִϸ��̼�
	_Lava->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(3, 0, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(3, 80, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(3, 150, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(3, 230, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(3, 305, 10, 70, 45, 1); // ���

	_Lava->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(3, 385, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(3, 460, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(3, 538, 10, 70, 45, 1); // ���
	_Lava->m_pAnimations[1][8] = m_pEngine->LoadSpriteFromSheet(3, 615, 10, 70, 45, 1); // ���

	_Lava->m_pSprite = _Lava->m_pAnimations[0][0];

#pragma endregion

	return _Lava;
}

Object* UnitManager::CreateBroodling(int posX, int posY)
{
	// ���鸵
	GroundUnit* _Broodling = new GroundUnit(posX, posY, ePlayer::player2);
	_Broodling->SetSpeed(4.0f);

#pragma region ANIMATION

	// ��� �ִϸ��̼�
	_Broodling->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(4, 35, 27, 55, 55, 1); // ���鸵
	_Broodling->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(4, 159, 24, 53, 58, 1); // ���鸵
	_Broodling->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(4, 279, 22, 54, 58, 1); // ���鸵
	_Broodling->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(4, 394, 21, 58, 57, 1); // ���鸵
	_Broodling->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(4, 509, 22, 62, 53, 1); // ���鸵

	_Broodling->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(4, 35, 27, 55, 55, 1); // ���鸵
	_Broodling->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(4, 159, 24, 53, 58, 1); //���鸵
	_Broodling->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(4, 279, 22, 54, 58, 1); //���鸵
	_Broodling->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(4, 394, 21, 58, 57, 1); //���鸵

	// �ȱ� �ִϸ��̼�																		 
	_Broodling->m_pAnimations[1][0] = m_pEngine->LoadSpriteFromSheet(4, 35, 27, 55, 55, 1); // ���鸵
	_Broodling->m_pAnimations[1][1] = m_pEngine->LoadSpriteFromSheet(4, 159, 24, 53, 58, 1); //���鸵
	_Broodling->m_pAnimations[1][2] = m_pEngine->LoadSpriteFromSheet(4, 279, 22, 54, 58, 1); //���鸵
	_Broodling->m_pAnimations[1][3] = m_pEngine->LoadSpriteFromSheet(4, 394, 21, 58, 57, 1); //���鸵
	_Broodling->m_pAnimations[1][4] = m_pEngine->LoadSpriteFromSheet(4, 509, 22, 62, 53, 1); //���鸵

	_Broodling->m_pAnimations[1][5] = m_pEngine->LoadSpriteFromSheet(4, 626, 23, 62, 48, 1); // ���
	_Broodling->m_pAnimations[1][6] = m_pEngine->LoadSpriteFromSheet(4, 743, 25, 62, 48, 1); // ���
	_Broodling->m_pAnimations[1][7] = m_pEngine->LoadSpriteFromSheet(4, 861, 28, 65, 46, 1); // ���
	_Broodling->m_pAnimations[1][8] = m_pEngine->LoadSpriteFromSheet(4, 980, 29, 71, 47, 1); // ���

	_Broodling->m_pSprite = _Broodling->m_pAnimations[0][0];

#pragma endregion

	return _Broodling;
}

Object* UnitManager::CreateMutal(int posX, int posY)
{
	AirUnit* _Mutal = new AirUnit(posX, posY, ePlayer::player2);
	_Mutal->SetSpeed(4.0f);

#pragma region ANIMATION
	// ��� �ִϸ��̼�
	_Mutal->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(6, 73, 76, 122, 80, 1);
	_Mutal->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(6, 337, 70, 122, 87, 1);
	_Mutal->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(6, 602, 64, 122, 94, 1);
	_Mutal->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(6, 869, 59, 118, 99, 1);
	_Mutal->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(6, 1130, 55, 106, 102, 1);

	_Mutal->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(6, 73, 76, 122, 80, 1);
	_Mutal->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(6, 337, 70, 122, 87, 1);
	_Mutal->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(6, 602, 64, 122, 94, 1);
	_Mutal->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(6, 869, 59, 118, 99, 1);


	// �ȱ� �ִϸ��̼�											 
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
	// ���ִϸ��̼�
	_Guardian->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(7, 1302, 1538, 133, 76, 1);
	_Guardian->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(7, 1106, 1543, 134, 82, 1);
	_Guardian->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(7, 894, 1540, 137, 89, 1);
	_Guardian->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(7, 685, 1538, 138, 96, 1);
	_Guardian->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(7, 3204, 279, 138, 90, 1);

	_Guardian->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(7, 1302, 1538, 133, 76, 1);
	_Guardian->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(7, 1106, 1543, 134, 82, 1);
	_Guardian->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(7, 894, 1540, 137, 89, 1);
	_Guardian->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(7, 685, 1538, 138, 96, 1);

	// �ȱ� �ִϸ��̼�
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
	// ���ִϸ��̼�
	_Scourge->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(8, 416, 484, 51, 38, 1);
	_Scourge->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(8, 320, 482, 51, 40, 1);
	_Scourge->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(8, 224, 481, 50, 40, 1);
	_Scourge->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(8, 125, 481, 51, 41, 1);
	_Scourge->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(8, 26, 481, 51, 42, 1);

	_Scourge->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(8, 416, 484, 51, 38, 1);
	_Scourge->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(8, 320, 482, 51, 40, 1);
	_Scourge->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(8, 224, 481, 50, 40, 1);
	_Scourge->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(8, 125, 481, 51, 41, 1);

	// �ȱ� �ִϸ��̼�
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
	// ���ִϸ��̼�
	_Overload->m_pAnimations[0][0] = m_pEngine->LoadSpriteFromSheet(9, 1302, 1538, 133, 76, 1);
	_Overload->m_pAnimations[0][1] = m_pEngine->LoadSpriteFromSheet(9, 1106, 1543, 134, 82, 1);
	_Overload->m_pAnimations[0][2] = m_pEngine->LoadSpriteFromSheet(9, 894, 1540, 137, 89, 1);
	_Overload->m_pAnimations[0][3] = m_pEngine->LoadSpriteFromSheet(9, 685, 1538, 138, 96, 1);
	_Overload->m_pAnimations[0][4] = m_pEngine->LoadSpriteFromSheet(9, 3204, 279, 138, 90, 1);

	_Overload->m_pAnimations[0][5] = m_pEngine->LoadSpriteFromSheet(9, 1302, 1538, 133, 76, 1);
	_Overload->m_pAnimations[0][6] = m_pEngine->LoadSpriteFromSheet(9, 1106, 1543, 134, 82, 1);
	_Overload->m_pAnimations[0][7] = m_pEngine->LoadSpriteFromSheet(9, 894, 1540, 137, 89, 1);
	_Overload->m_pAnimations[0][8] = m_pEngine->LoadSpriteFromSheet(9, 685, 1538, 138, 96, 1);

	// �ȱ� �ִϸ��̼�
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
	// ��ü ������ ���鼭
	for (Object* nowUnit : m_UnitPool)
	{
		// ���� ���� ���°� �������̾��ٸ� �н�
		if (nowUnit->GetNowState() == eUnitState::eAttacking) continue;

		// ��ü ��� ������ ���鼭
		for (Object* targetUnit : m_UnitPool)
		{
			// ��� ������ ���� ���
			if (nowUnit->GetPlayerIndex() != targetUnit->GetPlayerIndex())
			{
				// ���� ������ ��ġ���Ϳ� ���� ��ġ���͸� ���� ������ ���
				CPoint _disVec = nowUnit->GetPosition() - targetUnit->GetPosition();
				float _distance = abs(_disVec.Length());

				// ���� ������ ������ ���
				if (_distance <= nowUnit->GetRange())
				{
					// ���� ���¸� ���� ������ �ٲ�
					nowUnit->SetNowState(eUnitState::eAttacking);

					// �� ���� �����͸� ������������ �ٷ� �ο���
					nowUnit->SetTarget(targetUnit);
				}
			}
		}
	}
	//��� ���Ҵµ� �� ã���� ���
	//nullptr ����!
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
			/// ���� �Ҵ�� Unitbase ��ü�� delete
			delete m_UnitPool[i];

			/// �� �����͸� �����ϴ� �����̳ʿ��� �ϳ��� ��Ҹ� ����
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
	// ��..������Ʈ ���� Unit���� ������ٸ� ����� Unit���� ���൵ �ǳ�

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
	// ���� ������ ���� ����ũ�� �ε����� �ο����ش�.
	static int _count = 0;
	_pUnit->SetIndex(_count);
	_count++;

	// �ѹ��� ���ֵ� �־��ش�
	m_UnitPool.push_back(_pUnit);
}

void UnitManager::SelectUnits_Area(int left, int top, int right, int bottom)
{
	// �巡�׸� �»󿡼� ���Ϸθ� ���� ���� ��찡 �ִ�. �̰��� left �� top �� �������� �����ϱ� ����
	if (right < left) { Swap(left, right); }
	if (bottom < top) { Swap(top, bottom); }

	// �������� ����
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
	// ���콺 �Է��� �޴´�
	GetCursorPos(&m_NowMousePos);

	RECT rt;
	GetWindowRect(m_hWnd, &rt);
	m_NowMousePos.x -= rt.left + 5;
	m_NowMousePos.y -= rt.top + 23;

	if (GetAsyncKeyState('1') & 0x8001)
	{								// ��Ÿ� ���� ����
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
	// �ε��� ������ �Ѿ�� ������ ����.
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
		// Unit�� ����ִ� �ڷᱸ���� ��ȸ
		for (unsigned int i = 0; i < m_UnitPool.size(); i++)
		{
			Object* _nowUnit = m_UnitPool[i];
			_nowUnit->SetPosition(300, 300);
		}
	}

	if (::GetAsyncKeyState(VK_RETURN) & 0x8001)
	{
		// Unit �� ����ִ� �ڷᱸ���� ��ȸ
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

	// ���콺 ���� ��ư
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		// ���õ� ���ֵ鸸 �̵��� �� �ش�.
		MoveToDestination(m_NowMousePos.x, m_NowMousePos.y);
	}

	// ���콺 �Է��� �� �� ����ȭ �Ѵ�
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		// ���� ����
		// ������ �ȴ����� �ִٰ�, �̹� �����ӿ� ���� ��
		if (m_RightButtonDown == false)
		{
		}

		m_RightButtonDown = true;
	}
	else
	{
		// �ȴ��� ����
		// ������ ������ �ִٰ�, �̹� �����ӿ� ������ 
		if (m_RightButtonDown == true)
		{
		}

		m_RightButtonDown = false;
	}

	// ���콺 �Է��� �� �� ����ȭ �Ѵ�
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		// ���� ����

		// ������ �� ������ �ִٰ�, �̹� �����ӿ� ���� ��
		if (m_LeftButtonDown == false)
		{
			m_DragStartPos = m_NowMousePos;
			m_IsLeftDragging = true;
		}
		m_LeftButtonDown = true;
	}
	else
	{
		// �ȴ��� ����

		// ������ ������ �ִٰ�, �̹� �����ӿ� ������ ��
		if (m_LeftButtonDown == true)
		{
			SelectUnits_Area(m_DragStartPos.x, m_DragStartPos.y,
				m_NowMousePos.x, m_NowMousePos.y);
		}
		m_LeftButtonDown = false;

		m_IsLeftDragging = false;
	}
}
