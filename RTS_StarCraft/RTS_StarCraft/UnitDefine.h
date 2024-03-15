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
	eStandBy,		// 유닛의 대기 상태
	eMoving,			// 이동 중인 상태
	eDead,
	eAttacking,		// 공격 중인 상태
	eHolding,		// 공격 멈춤 중인 상태
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