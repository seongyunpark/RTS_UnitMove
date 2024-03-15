#include "Object.h"
#include <math.h>

// 그래픽스 엔진
#include "../DRD2DEngine/DRD2DEngine.h"	

Object::Object(int posX, int posY)
	:m_Index(0), m_Name(""), m_playerIndex(ePlayer::player1),
	m_HP(0), m_HPMax(0), m_NowState(eUnitState::eStandBy), m_PrevState(eUnitState::eStandBy),								// 기본정보
	m_Speed(0), m_Position(posX, posY), m_Destination(posX, posY),							// 이동정보
	m_pTarget(nullptr), m_Range(0), m_AttackPower(0),
	m_IsSelected(false), m_pSprite(nullptr), m_NowSpriteIndex(0), m_pAnimations()
{
	//ZeroMemory(m_pAnimations, sizeof())
}

Object::~Object()
{
}

void Object::Update()
{
	// 0~8까지(총 9장) 스프라이트 인덱스를 정해준다
	if (rand() % 20 == 0)
	{
		m_NowSpriteIndex++;
	}

	if (9 <= m_NowSpriteIndex)
	{
		m_NowSpriteIndex = 0;
	}
	CheckDead();

	// 유닛이 도착했는지 체크
	CheckIsArrived(); 

	// Finite state Machine
	switch (m_NowState)
	{
		case eUnitState::eStandBy:
		{
			//  랜덤하게 이동한다.
			//m_Position.x += (rand() % 10 - rand() % 10);
			//m_Position.y += (rand() % 10 - rand() % 10);
		}
		break;
		case eUnitState::eMoving:
		{
			// 현재 위치에서 목적지로 이동한다
			CPoint _moveVec = m_Destination - m_Position;

			// 노말라이즈를 한다
			_moveVec.Normalize();

			// 현재 포지션에 이동벡터를 구한다
			m_Position = m_Position + (_moveVec * (float)m_Speed);
		}
		break;
		case eUnitState::eAttacking:
		{
			// 공격중 상태인데, 타겟이 있다면 실제로 공격
			if (m_pTarget != nullptr)
			{
				// 대충 1/2 확률?로 때려!
				if (rand() % 2 == 0)
				{
					Attack(m_pTarget);
				}
			}
		}
		default:
		{

		}
		break;
	}
	// 죽음을 체크
	CheckDead();
}

void Object::Render(DRD2DEngine* pEngine)
{
	// 공통적인 그리기 구현 넣는다
	pEngine->DrawSprite(m_pSprite, m_Position.x, m_Position.y);

	// 현재 상태를 나타내준다
	DrawState(pEngine);

	// 이동 라인을 그려준다
	DrawMoveLine(pEngine);

	// 선택된 상태인가? 를 그려준다. 
	DrawSelectedCircle(pEngine);

	// Hp 바를 그린다
	DrawHPBar(pEngine, (float)m_HP / (float)m_HPMax);
}

// object 에서 unit SelectedCircle색 조절시 사용
void Object::DrawSelectedCircle(DRD2DEngine* pEngine)
{
	// 선택된 상태인가?를 그려준다
	if (m_IsSelected)
	{
		pEngine->SetBrushColor(DRCOLOR_MAGENTA);
		pEngine->DrawEllipse(m_Position.x + m_pSprite->Width * 0.5f,
			m_Position.y + m_pSprite->Height * 0.5f, m_pSprite->Width * 0.5f);
	}
}

void Object::DrawHPBar(DRD2DEngine* pEngine, float value)
{
	float _widthHPBar = (float)m_pSprite->Width * value;

	pEngine->DrawRectangle(m_Position.x, m_Position.y - 32.0f,
		m_Position.x + _widthHPBar, m_Position.y - 30.0f, RGB(0, 255, 0));

	pEngine->DrawRectangle(m_Position.x, m_Position.y - 35.0f,
		m_Position.x + _widthHPBar, m_Position.y - 33.0f, RGB(0, 255, 0));
}

void Object::SetDestination(int x, int y)
{
	m_Destination.x = x;
	m_Destination.y = y;
}

void Object::SetPosition(int x, int y)
{
	m_Position.x = x;
	m_Position.y = y;
}

CPoint Object::GetPosition()
{
	return m_Position;
}

void Object::SetNowState(eUnitState val)
{
	m_PrevState = m_NowState;
	m_NowState = val;
}

void Object::DrawState(DRD2DEngine* pEngine)
{
	// 몇 번째 플레이어인가?
	if (m_playerIndex == ePlayer::player1)
	{
		pEngine->DrawText(m_Position.x, m_Position.y - 18.0f, "P1");
	}
	else if (m_playerIndex == ePlayer::player2)
	{
		pEngine->DrawText(m_Position.x, m_Position.y - 18.0f, "P2");
	}

	switch (m_NowState)
	{
		case eUnitState::eStandBy:
		{
			pEngine->DrawText(m_Position.x + 20.0f, m_Position.y - 18.0f, "대기!");
		}
		break;
		case eUnitState::eMoving:
		{
			pEngine->DrawText(m_Position.x + 20.0f, m_Position.y - 18.0f, "이동!");
		}
		case eUnitState::eAttacking:
		{
			pEngine->DrawText(m_Position.x + 20.0f, m_Position.y - 18.0f, "공격중!");
		}
		break;
	}
}

void Object::DrawMoveLine(DRD2DEngine* pEngine)
{
	pEngine->DrawLine(m_Position.x, m_Position.y, m_Destination.x, m_Destination.y, RGB(0, 255, 0));
}

void Object::CheckIsArrived()
{
	// 현재 위치와 목적지의 위치를 차를 계산한다
	CPoint _moveVec = m_Destination - m_Position;

	// 시간 이하로 도착하면 대기상태를 확인한다
	// 내 유닛 최고속도가 10이어서 2.0일 때는 그냥 통과?해서 계속 체크중인것임
	// 시간을 늦춰주면 정상적으로 작동할것임
	if (m_NowState == eUnitState::eMoving && abs(_moveVec.Length()) < 2.0f)
	{
		this->SetNowState(eUnitState::eStandBy);
	}
}

void Object::CheckDead()
{
	// 일정 확률로 체력을 깎는다
	//if (rand() % 3 == 0)
	//{
	//	m_HP--;
	//}

	if (m_HP < 0)
	{
		m_HP = 0;
		SetNowState(eUnitState::eDead);
	}
}

void Object::Attack(Object* target)
{
	// 타겟의 HP
	int _targetHP = target->GetHP();

	// 타겟의 HP에서 내 공격력을 뺀다. (타겟의 잔여 HP)
	// 단, HP는 0보다 아래로 내려가면 안된다.
	int _remainHP = max(0, _targetHP - m_AttackPower);

	// 타겟의 HP를 설정해준다.
	target->SetHP(_targetHP - m_AttackPower);

	// 적이 죽었다면 타겟을 리셋해준다.
	if (target->GetNowState() == eUnitState::eDead)
	{
		m_pTarget = nullptr;

		// 이전 상태로 복귀한다.
		m_NowState = m_PrevState;
	}
}
