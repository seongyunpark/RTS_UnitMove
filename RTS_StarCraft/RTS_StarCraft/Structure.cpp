#include "Structure.h"

// �׷��Ƚ� ����
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

	// �������� �׸����� ������ �ִ´�
	int _AnimationIndex = 0;

	// ���� ���¸� ��Ÿ���ش�
	DrawState(pEngine);

	// �̵� ������ �׷��ش�
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
