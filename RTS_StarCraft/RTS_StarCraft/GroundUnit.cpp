#include "GroundUnit.h"

// �׷��Ƚ� ����
#include "../DRD2DEngine/DRD2DEngine.h"	

GroundUnit::GroundUnit(int posX, int posY, ePlayer playerIndex)
	:Unit(posX, posY, ePlayer::player2)
{
}

GroundUnit::~GroundUnit()
{
}

bool GroundUnit::IsPass()
{
	return false;
}

void GroundUnit::Update()
{
	Object::Update();

	//// �����ߴ��� üũ�Ѵ�
	//CheckIsArrived();

	//switch (m_NowState)
	//{
	//case eUnitState::eStandBy:
	//{
	//	// ���ڸ����� �����ϸ� �����ϰ� �����δ�
	//	//m_Position.x += (rand() % 10 - rand() % 10);
	//	//m_Position.y += (rand() % 10 - rand() % 10);
	//}
	//break;
	//case eUnitState::eMoving:
	//{
	//	// ���� ��ġ���� �������� �̵��Ѵ�
	//	CPoint _moveVec = m_Destination - m_Position;

	//	// �븻����� �Ѵ�
	//	_moveVec.Normalize();

	//	// ���� �������� �̵����͸� ���Ѵ�
	//	m_Position = m_Position + (_moveVec * m_Speed);
	//}
	//break;
	//default:
	//{

	//}
	//break;
	//}
}

void GroundUnit::Render(DRD2DEngine* pEngine)
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
	if (m_IsSelected)
	{
		pEngine->SetBrushColor(DRCOLOR_BLUE);
		pEngine->DrawEllipse(m_Position.x + m_pSprite->Width * 0.5f,
			m_Position.y + m_pSprite->Height * 0.5f, m_pSprite->Width * 0.5f);
	}

	// HP�ٸ� �׸���.
	DrawHPBar(pEngine, (float)m_HP / (float)m_HPMax);
}
