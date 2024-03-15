#include "AirUnit.h"

// 그래픽스 엔진
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
	
	//Object::DrawSelectedCircle(pEngine);
	
	if (m_IsSelected)
	{ 
		pEngine->SetBrushColor(DRCOLOR_MAGENTA);
		pEngine->DrawEllipse(m_Position.x + m_pSprite->Width * 0.5f,
			m_Position.y + m_pSprite->Height * 0.5f, m_pSprite->Width * 0.5f);
	}

	// HP바를 그린다.
	DrawHPBar(pEngine, (float)m_HP / (float)m_HPMax);
}
