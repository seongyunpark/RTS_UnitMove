#pragma once
#include "Object.h"
#include "Unit.h"

class GroundUnit : public Unit
{
public:
	GroundUnit(int posX, int posY, ePlayer playerIndex);
	~GroundUnit();

protected:
	// 이름
	// 생명력
	// 위칫값

	// 공격타입
	// 유닛사이즈

	// 공격력
	// 공격사거리
	// 공격쿨타임
	// 방어력
	// 이동속력
	// 시야

public:
	// Unit 이동함수
	// Unit 공격함수
	bool IsPass();	// 갈 수 있는 길인가? 판별함수

	virtual void Update() override;
	virtual void Render(DRD2DEngine* pEngine) override;
};

