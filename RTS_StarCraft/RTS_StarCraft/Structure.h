#pragma once
#include "Object.h"

class Structure : public Object
{
public:
	Structure(int posX, int posY, ePlayer playerIndex);
	~Structure();

protected:
	// 이름
	// 생명력
	// 위칫값

public:
	virtual void Update() override;
	virtual void Render(DRD2DEngine* pEngine) override;


	virtual void SProduce();	// 건물 기능수행 함수
	virtual void SMove();		// 건물 이동 함수
	virtual void SBuild();		// 건물 짓는 함수. 이건 SCV가 하는 일인데 여기 있어도 되나??????
	virtual void SUpgrade();	// 건물 업그레이드. 이건 여기 있는게 맞는거같아. 근데 그냥 만들어지는것도있고 SCV가 만드는것도 있는데 뭐지? 혼란스럽다
};

// rebuild = scv가 다시 짓는거 / upgrade = 건물 자체가 업글되는거. 클래스를 만들어야 하나? 아니면 그냥 함수로 둬야하나?