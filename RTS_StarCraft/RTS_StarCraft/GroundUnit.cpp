#include "GroundUnit.h"

// 그래픽스 엔진
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

	//// 도착했는지 체크한다
	//CheckIsArrived();

	//switch (m_NowState)
	//{
	//case eUnitState::eStandBy:
	//{
	//	// 그자리에서 덜덜하며 랜덤하게 움직인다
	//	//m_Position.x += (rand() % 10 - rand() % 10);
	//	//m_Position.y += (rand() % 10 - rand() % 10);
	//}
	//break;
	//case eUnitState::eMoving:
	//{
	//	// 현재 위치에서 목적지로 이동한다
	//	CPoint _moveVec = m_Destination - m_Position;

	//	// 노말라이즈를 한다
	//	_moveVec.Normalize();

	//	// 현재 포지션의 이동벡터를 구한다
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
	// 공통적으로 해야 하는 일
	//Object::Render(pEngine);
	
	
	// 공통적인 그리기의 구현을 넣는다
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

	// 현재 상태를 나타내준다
	DrawState(pEngine);

	// 이동 라인을 그려준다
	DrawMoveLine(pEngine);

	// 선택이 됬다면 유닛을 동그라미로 그려주기
	if (m_IsSelected)
	{
		pEngine->SetBrushColor(DRCOLOR_BLUE);
		pEngine->DrawEllipse(m_Position.x + m_pSprite->Width * 0.5f,
			m_Position.y + m_pSprite->Height * 0.5f, m_pSprite->Width * 0.5f);
	}

	// HP바를 그린다.
	DrawHPBar(pEngine, (float)m_HP / (float)m_HPMax);
}
