#pragma once
#include <string>
#include <windows.h>
#include "UnitDefine.h"
#include <vector>

//struct POSITION
//{
//	int x;
//	int y;
//};

class DRSprite;
class DRD2DEngine;

class Object
{
public:
	Object(int posX, int posY);
	~Object();

	///--------------------------------------
	// 기본정보
protected:
	int m_Index;			// 유니크한 인덱스?이게 뭐지
	std::string	m_Name;		// 이름
	ePlayer m_playerIndex;	// 몇 번째 플레이어인가?
	int m_HP;				// 현재체력
	int m_HPMax;			// 풀 생명. 여기 필요한가? Unit 도 Structure 도 생명이 있는데한번에 하는게 편하긴 한데 맵은 생명이 없는데
	// POSITION m_Pos;		// 구조체는 초기화 어떻게 해야하지으으어어 int 로 대체함

	// FSM에 쓰이는 State
	eUnitState m_NowState;	// 현재 (이동) 상태
public:
	eUnitState m_PrevState;	// 이전 상태
	///----------------------------------------

	///------------------------------------
	// 이동관련
	float m_Speed;		// 이동속력
	CPoint m_Position;		// 위치
	CPoint m_Destination;	// 목적지
	///------------------------------------

	//----------------------------------------
	// 유닛선택관련 부분
	bool m_IsSelected;

	// 공격관련
	Object* m_pTarget;		// 공격을 할 대상
	float m_Range;			// 사거리
	int m_AttackPower;		// 공격력

public:
	//
	CPoint GetPosition() const {return m_Position;	}
	void SetPosition(CPoint val) { m_Position = val; }

	int GetIndex() const { return m_Index; }
	void SetIndex(int val) { m_Index = val; }
	// 플레이어 1, 2 나눔
	ePlayer GetPlayerIndex() const { return m_playerIndex; }
	void SetPlayerIndex(ePlayer val) { m_playerIndex = val; }
	// 마우스 포인터로 유닛을 선택했는지
	bool GetIsSelected() const { return m_IsSelected; }
	void SetIsSelected(bool val) { m_IsSelected = val; }
	// 현재 유닛 HP 
	int GetHP() const { return m_HP; }
	void SetHP(int val) { m_HP = val; }
	// 유닛 최대 HP
	int GetHPMax() const { return m_HPMax; }
	void SetHPMax(int val) { m_HPMax = val; m_HP = m_HPMax; }
	// 사거리
	float GetRange() const { return m_Range; }
	void SetRange(float val) { m_Range = val; }
	// 공격할 타겟
	Object* GetTarget() const { return m_pTarget; }
	void SetTarget(Object* val) { m_pTarget = val; }
	// 공격력
	int GetAttackPower() const { return m_AttackPower; }
	void SetAttackPower(int val) { m_AttackPower = val; }
	
	//----------------------------------------


	///-------------------------------------
	// 그리기를 위한 부분
public:
	DRSprite* m_pSprite;	// 스프라이트
	
	// 스프라이트를 벡터에 넣자
	std::vector<DRSprite*> m_pAnimation;

	// 배열은 매니저 속에 멤버변수로 넣어도 되겠지?
	DRSprite* m_pAnimations[3][9]; // 스프라이트로 이루어진 애니메이션
	int m_NowSpriteIndex;		// 애니메이션을 위한 스프라이트 인덱스

public:
	virtual void Update();
	virtual void Render(DRD2DEngine* pEngine);
	///--------------------------------------
	void DrawSelectedCircle(DRD2DEngine* pEngine);
	void DrawHPBar(DRD2DEngine* pEngine, float value);

	///--------------------------------------
	// 이동을 위한 부분
	void SetDestination(int x, int y);

	void SetPosition(int x, int y);
	CPoint GetPosition();

	eUnitState GetNowState() const { return m_NowState; }
	void SetNowState(eUnitState val);

	int GetSpeed() const { return m_Speed; }
	void SetSpeed(float val) { m_Speed = val; }

protected:
	void DrawState(DRD2DEngine* pEngine);

	void DrawMoveLine(DRD2DEngine* pEngine);

	void CheckIsArrived();
	void CheckDead();
	///----------------------------------------
	// 공격을 위한 부분
	void Attack(Object* target);
};

