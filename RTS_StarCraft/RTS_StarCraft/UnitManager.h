#pragma once
#include <vector>
#include <windows.h>
#include "UnitDefine.h"

class Object;
class DRD2DEngine;

// ���� ���� ��� ���ֵ��� ����, ����, �����ϴ� Ŭ����
class UnitManager
{
public:
	UnitManager(DRD2DEngine* pEngine, HWND hwnd);
	~UnitManager();

private:
	// ���� ���� �����ϴ� ��� ����(+�ǹ�)�� �θ��� ������
	std::vector<Object*> m_UnitPool;

	// ���� ���� �����ϴ� ��� �ǹ��� �θ��� ������
	std::vector<Object*> m_StructPool;

	// �׷��Ƚ� ������ ������ �ִ´�
	DRD2DEngine* m_pEngine;

	// ���� �ڵ鵵 ������ �ִ´�
	HWND m_hWnd;


	// ���콺 ��ġ
	POINT m_NowMousePos;
	POINT m_DragStartPos;

	// ��ư�� ���ȴ��� �ȴ��ȴ��� �÷���
	bool m_LeftButtonDown;
	bool m_RightButtonDown;

	// �巡�� �÷���
	bool m_IsLeftDragging;

private:
	// ���� �Է� �޴´�
	void UserInput();

	void DrawSelectBox();

public:
	// ��ü ���� ó���� �� �ش�.
	void UpdateAllUnit();		// ������Ʈ
	void RenderAllUnit();		// �׸���
	void RenderStatus();		// ���� �Ŵ����� ���¸� �׸���

	// �ϳ��� �Լ��� �ٸ� ������ �����Ѵ�
	void CreateUnit(eUnitType type, int posX, int posY, ePlayer playerIndex, int hp);

private:
	// ��� ������ֱ�
	Object* CreateBackGround(int posX, int posY);

	Object* CreateTownHall(int posX, int posY);

	// ���� �������ش�. �������� �ϳ��ϳ�
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

	// ��Ÿ� �ȿ� ���� ���Դ°��� üũ�Ѵ�
	Object* CheckEnemyIsSpotted();

	void RemoveDeadUnits();
	void RemoveDeadUnits2();

public:
	// ���ֵ��� �����Ѵ� (Ư�� ������ ����)
	void SelectUnits_Area(int left, int top, int right, int bottom);
	void MoveToDestination(int x, int y);
	void SelectUnits_All();

private:
	// ���콺�����ʹ�� �簢�� �׸� �� �»�ܽ����� �ƴϾ �����ϵ��� �������ִ� �Լ�
	void Swap(int& a, int& b);
	int GetRand(int base, int randfactor);		//	�̰� ����
};

