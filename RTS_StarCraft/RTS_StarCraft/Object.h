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
	// �⺻����
protected:
	int m_Index;			// ����ũ�� �ε���?�̰� ����
	std::string	m_Name;		// �̸�
	ePlayer m_playerIndex;	// �� ��° �÷��̾��ΰ�?
	int m_HP;				// ����ü��
	int m_HPMax;			// Ǯ ����. ���� �ʿ��Ѱ�? Unit �� Structure �� ������ �ִµ��ѹ��� �ϴ°� ���ϱ� �ѵ� ���� ������ ���µ�
	// POSITION m_Pos;		// ����ü�� �ʱ�ȭ ��� �ؾ������������ int �� ��ü��

	// FSM�� ���̴� State
	eUnitState m_NowState;	// ���� (�̵�) ����
public:
	eUnitState m_PrevState;	// ���� ����
	///----------------------------------------

	///------------------------------------
	// �̵�����
	float m_Speed;		// �̵��ӷ�
	CPoint m_Position;		// ��ġ
	CPoint m_Destination;	// ������
	///------------------------------------

	//----------------------------------------
	// ���ּ��ð��� �κ�
	bool m_IsSelected;

	// ���ݰ���
	Object* m_pTarget;		// ������ �� ���
	float m_Range;			// ��Ÿ�
	int m_AttackPower;		// ���ݷ�

public:
	//
	CPoint GetPosition() const {return m_Position;	}
	void SetPosition(CPoint val) { m_Position = val; }

	int GetIndex() const { return m_Index; }
	void SetIndex(int val) { m_Index = val; }
	// �÷��̾� 1, 2 ����
	ePlayer GetPlayerIndex() const { return m_playerIndex; }
	void SetPlayerIndex(ePlayer val) { m_playerIndex = val; }
	// ���콺 �����ͷ� ������ �����ߴ���
	bool GetIsSelected() const { return m_IsSelected; }
	void SetIsSelected(bool val) { m_IsSelected = val; }
	// ���� ���� HP 
	int GetHP() const { return m_HP; }
	void SetHP(int val) { m_HP = val; }
	// ���� �ִ� HP
	int GetHPMax() const { return m_HPMax; }
	void SetHPMax(int val) { m_HPMax = val; m_HP = m_HPMax; }
	// ��Ÿ�
	float GetRange() const { return m_Range; }
	void SetRange(float val) { m_Range = val; }
	// ������ Ÿ��
	Object* GetTarget() const { return m_pTarget; }
	void SetTarget(Object* val) { m_pTarget = val; }
	// ���ݷ�
	int GetAttackPower() const { return m_AttackPower; }
	void SetAttackPower(int val) { m_AttackPower = val; }
	
	//----------------------------------------


	///-------------------------------------
	// �׸��⸦ ���� �κ�
public:
	DRSprite* m_pSprite;	// ��������Ʈ
	
	// ��������Ʈ�� ���Ϳ� ����
	std::vector<DRSprite*> m_pAnimation;

	// �迭�� �Ŵ��� �ӿ� ��������� �־ �ǰ���?
	DRSprite* m_pAnimations[3][9]; // ��������Ʈ�� �̷���� �ִϸ��̼�
	int m_NowSpriteIndex;		// �ִϸ��̼��� ���� ��������Ʈ �ε���

public:
	virtual void Update();
	virtual void Render(DRD2DEngine* pEngine);
	///--------------------------------------
	void DrawSelectedCircle(DRD2DEngine* pEngine);
	void DrawHPBar(DRD2DEngine* pEngine, float value);

	///--------------------------------------
	// �̵��� ���� �κ�
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
	// ������ ���� �κ�
	void Attack(Object* target);
};

