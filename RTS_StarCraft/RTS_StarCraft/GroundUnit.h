#pragma once
#include "Object.h"
#include "Unit.h"

class GroundUnit : public Unit
{
public:
	GroundUnit(int posX, int posY, ePlayer playerIndex);
	~GroundUnit();

protected:
	// �̸�
	// �����
	// ��ĩ��

	// ����Ÿ��
	// ���ֻ�����

	// ���ݷ�
	// ���ݻ�Ÿ�
	// ������Ÿ��
	// ����
	// �̵��ӷ�
	// �þ�

public:
	// Unit �̵��Լ�
	// Unit �����Լ�
	bool IsPass();	// �� �� �ִ� ���ΰ�? �Ǻ��Լ�

	virtual void Update() override;
	virtual void Render(DRD2DEngine* pEngine) override;
};

