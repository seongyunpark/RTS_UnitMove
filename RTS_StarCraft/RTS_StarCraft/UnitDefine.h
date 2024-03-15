#pragma once

enum class eAttackType
{
	SSnormal,
	SSbombed,
};

enum class eArmorType
{
	SSsmall,
	SSmiddle,
	SSlarge,
};

class CPoint
{
public:
	CPoint();
	CPoint(float px, float py);
	~CPoint();

	CPoint operator+(const CPoint& r);
	CPoint operator-(const CPoint& r);
	CPoint operator*(const float& f);


	void Normalize();
	float Length();

	float x;
	float y;
};

enum class eUnitSize
{
	eSmallSize,
	eMiddleSize,
	eLargeSize,
};

enum class eUnitAttackType
{
	eNormal,
	eBomb,
};

enum class eUnitState
{
	eStandBy,		// ������ ��� ����
	eMoving,			// �̵� ���� ����
	eDead,
	eAttacking,		// ���� ���� ����
	eHolding,		// ���� ���� ���� ����
	//Stop,
};

enum class ePlayer
{
	// GroundUnit
	player1,
	// AirUnit
	player2,
	// Structure
	player3,
};

enum class eUnitType
{
	// GroundUnit
	Lava, Drone, Broodling, Carrigun, Zergling,
	// AirUnit
	Muatalisk, Guardian, Scourge, Overload,
	// Structure
	structure,
};