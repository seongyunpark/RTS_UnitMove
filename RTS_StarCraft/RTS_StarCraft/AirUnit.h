#pragma once
#include "Object.h"
#include "Unit.h"

class AirUnit : public Unit
{
public:
	AirUnit(int posX, int posY, ePlayer playerIndex);
	~AirUnit();

protected:
	//

public:
	bool IsPass(); // �� �� �ִ� ���ΰ�?�Ǻ��Լ�

	virtual void Update() override;
	virtual void Render(DRD2DEngine* pEngine) override;
};

