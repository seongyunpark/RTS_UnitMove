#include "Structure.h"

// 그래픽스 엔진
#include "../DRD2DEngine/DRD2DEngine.h"	

Structure::Structure(int posX, int posY, ePlayer playerIndex)
	:Object(posX, posY) 
{
}

Structure::~Structure()
{
}

void Structure::Update()
{
	Object::Update();
}

void Structure::Render(DRD2DEngine* pEngine)
{

	// 공통적인 그리기의 구현을 넣는다
	int _AnimationIndex = 0;

	// 현재 상태를 나타내준다
	DrawState(pEngine);

	// 이동 라인을 그려준다
	DrawMoveLine(pEngine);

}

void Structure::SProduce()
{
}

void Structure::SMove()
{
}

void Structure::SBuild()
{
}

void Structure::SUpgrade()
{
}
