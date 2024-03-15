#include "Object.h"
#include <math.h>

// �׷��Ƚ� ����
#include "../DRD2DEngine/DRD2DEngine.h"	

Object::Object(int posX, int posY)
	:m_Index(0), m_Name(""), m_playerIndex(ePlayer::player1),
	m_HP(0), m_HPMax(0), m_NowState(eUnitState::eStandBy), m_PrevState(eUnitState::eStandBy),								// �⺻����
	m_Speed(0), m_Position(posX, posY), m_Destination(posX, posY),							// �̵�����
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
	// 0~8����(�� 9��) ��������Ʈ �ε����� �����ش�
	if (rand() % 20 == 0)
	{
		m_NowSpriteIndex++;
	}

	if (9 <= m_NowSpriteIndex)
	{
		m_NowSpriteIndex = 0;
	}
	CheckDead();

	// ������ �����ߴ��� üũ
	CheckIsArrived(); 

	// Finite state Machine
	switch (m_NowState)
	{
		case eUnitState::eStandBy:
		{
			//  �����ϰ� �̵��Ѵ�.
			//m_Position.x += (rand() % 10 - rand() % 10);
			//m_Position.y += (rand() % 10 - rand() % 10);
		}
		break;
		case eUnitState::eMoving:
		{
			// ���� ��ġ���� �������� �̵��Ѵ�
			CPoint _moveVec = m_Destination - m_Position;

			// �븻����� �Ѵ�
			_moveVec.Normalize();

			// ���� �����ǿ� �̵����͸� ���Ѵ�
			m_Position = m_Position + (_moveVec * (float)m_Speed);
		}
		break;
		case eUnitState::eAttacking:
		{
			// ������ �����ε�, Ÿ���� �ִٸ� ������ ����
			if (m_pTarget != nullptr)
			{
				// ���� 1/2 Ȯ��?�� ����!
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
	// ������ üũ
	CheckDead();
}

void Object::Render(DRD2DEngine* pEngine)
{
	// �������� �׸��� ���� �ִ´�
	pEngine->DrawSprite(m_pSprite, m_Position.x, m_Position.y);

	// ���� ���¸� ��Ÿ���ش�
	DrawState(pEngine);

	// �̵� ������ �׷��ش�
	DrawMoveLine(pEngine);

	// ���õ� �����ΰ�? �� �׷��ش�. 
	DrawSelectedCircle(pEngine);

	// Hp �ٸ� �׸���
	DrawHPBar(pEngine, (float)m_HP / (float)m_HPMax);
}

// object ���� unit SelectedCircle�� ������ ���
void Object::DrawSelectedCircle(DRD2DEngine* pEngine)
{
	// ���õ� �����ΰ�?�� �׷��ش�
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
	// �� ��° �÷��̾��ΰ�?
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
			pEngine->DrawText(m_Position.x + 20.0f, m_Position.y - 18.0f, "���!");
		}
		break;
		case eUnitState::eMoving:
		{
			pEngine->DrawText(m_Position.x + 20.0f, m_Position.y - 18.0f, "�̵�!");
		}
		case eUnitState::eAttacking:
		{
			pEngine->DrawText(m_Position.x + 20.0f, m_Position.y - 18.0f, "������!");
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
	// ���� ��ġ�� �������� ��ġ�� ���� ����Ѵ�
	CPoint _moveVec = m_Destination - m_Position;

	// �ð� ���Ϸ� �����ϸ� �����¸� Ȯ���Ѵ�
	// �� ���� �ְ�ӵ��� 10�̾ 2.0�� ���� �׳� ���?�ؼ� ��� üũ���ΰ���
	// �ð��� �����ָ� ���������� �۵��Ұ���
	if (m_NowState == eUnitState::eMoving && abs(_moveVec.Length()) < 2.0f)
	{
		this->SetNowState(eUnitState::eStandBy);
	}
}

void Object::CheckDead()
{
	// ���� Ȯ���� ü���� ��´�
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
	// Ÿ���� HP
	int _targetHP = target->GetHP();

	// Ÿ���� HP���� �� ���ݷ��� ����. (Ÿ���� �ܿ� HP)
	// ��, HP�� 0���� �Ʒ��� �������� �ȵȴ�.
	int _remainHP = max(0, _targetHP - m_AttackPower);

	// Ÿ���� HP�� �������ش�.
	target->SetHP(_targetHP - m_AttackPower);

	// ���� �׾��ٸ� Ÿ���� �������ش�.
	if (target->GetNowState() == eUnitState::eDead)
	{
		m_pTarget = nullptr;

		// ���� ���·� �����Ѵ�.
		m_NowState = m_PrevState;
	}
}
