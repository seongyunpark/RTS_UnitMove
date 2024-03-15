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
	bool IsPass(); // 갈 수 있는 길인가?판별함수

	virtual void Update() override;
	virtual void Render(DRD2DEngine* pEngine) override;
};

