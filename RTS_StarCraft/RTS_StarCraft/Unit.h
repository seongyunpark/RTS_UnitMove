#pragma once
#include "Object.h"
#include <string>
#include <windows.h>
#include "UnitDefine.h"

class Unit : public Object
{
public:
	Unit(int posX, int posY, ePlayer playerIndex);
	~Unit();

protected:
	// 이름
	// 생명력
	// 위칫값

	eUnitAttackType m_AttackType;		// 공격타입
	eUnitSize m_NowUnitSize;			// 유닛사이즈

	//int m_AttackPower;		// 공격력
	//int m_AttackRange;		// 공격사거리
	int m_AttackSpeed;		// 공격쿨타임
	int m_DefensePower;		// 방어력
	
	//int m_Range;			// 사거리
	int m_SightRange;		// 시야

private:
	// 유닛 선택 관련 부분--------------------------------
	ePlayer GetPlayerIndex() const { return m_playerIndex; }
	void SetPlayerIndex(ePlayer val) { m_playerIndex = val; }
	//float GetRange() const { return m_Range; }
	//void SetRange(float val) { m_Range = val; }
	//----------------------------------------------------

public:
	virtual void uMove(int x, int y);		// Unit 이동함수
	virtual void Skill();					// Unit 공격함수
};

