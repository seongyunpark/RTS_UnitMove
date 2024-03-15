#include "AirUnit.h"

// �׷��Ƚ� ����
#include "../DRD2DEngine/DRD2DEngine.h"	

AirUnit::AirUnit(int posX, int posY, ePlayer playerIndex)
	:Unit(posX, posY, ePlayer::player1)
{
}

AirUnit::~AirUnit()
{
}

bool AirUnit::IsPass()
{
	return false;
}

void AirUnit::Update()
{
	Object::Update();

}

void AirUnit::Render(DRD2DEngine* pEngine)
{
	// ���������� �ؾ� �ϴ� ��
	//Object::Render(pEngine);

	// �������� �׸����� ������ �ִ´�
	int _AnimationIndex = 0;

	if (m_NowState == eUnitState::eStandBy)
	{
		_AnimationIndex = 0;
	}
	else if (m_NowState == eUnitState::eMoving)
	{
		_AnimationIndex = 1;
	}

	pEngine->DrawSprite(m_pAnimations[_AnimationIndex][m_NowSpriteIndex],
		m_Position.x, m_Position.y);

	// ���� ���¸� ��Ÿ���ش�
	DrawState(pEngine);

	// �̵� ������ �׷��ش�
	DrawMoveLine(pEngine);

	// ������ ��ٸ� ������ ���׶�̷� �׷��ֱ�
	
	//Object::DrawSelectedCircle(pEngine);
	
	if (m_IsSelected)
	{ 
		pEngine->SetBrushColor(DRCOLOR_MAGENTA);
		pEngine->DrawEllipse(m_Position.x + m_pSprite->Width * 0.5f,
			m_Position.y + m_pSprite->Height * 0.5f, m_pSprite->Width * 0.5f);
	}

	// HP�ٸ� �׸���.
	DrawHPBar(pEngine, (float)m_HP / (float)m_HPMax);
}
