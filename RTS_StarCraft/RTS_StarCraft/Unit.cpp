#include "Unit.h"

Unit::Unit(int posX, int posY, ePlayer playerIndex)
:Object(posX, posY), m_AttackType(eUnitAttackType::eNormal), m_NowUnitSize(eUnitSize::eSmallSize),
 m_AttackSpeed(0), m_DefensePower(0),
 m_SightRange(0)
{
}

Unit::~Unit()
{
}

void Unit::uMove(int x, int y)
{
}

void Unit::Skill()
{
}