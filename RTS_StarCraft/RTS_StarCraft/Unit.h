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
	// �̸�
	// �����
	// ��ĩ��

	eUnitAttackType m_AttackType;		// ����Ÿ��
	eUnitSize m_NowUnitSize;			// ���ֻ�����

	//int m_AttackPower;		// ���ݷ�
	//int m_AttackRange;		// ���ݻ�Ÿ�
	int m_AttackSpeed;		// ������Ÿ��
	int m_DefensePower;		// ����
	
	//int m_Range;			// ��Ÿ�
	int m_SightRange;		// �þ�

private:
	// ���� ���� ���� �κ�--------------------------------
	ePlayer GetPlayerIndex() const { return m_playerIndex; }
	void SetPlayerIndex(ePlayer val) { m_playerIndex = val; }
	//float GetRange() const { return m_Range; }
	//void SetRange(float val) { m_Range = val; }
	//----------------------------------------------------

public:
	virtual void uMove(int x, int y);		// Unit �̵��Լ�
	virtual void Skill();					// Unit �����Լ�
};

