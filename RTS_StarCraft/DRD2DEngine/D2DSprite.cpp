#include "D2DSprite.h"

D2DSprite::D2DSprite()
	: DRSprite(),
	m_SheetIndex(0), m_OriX(0), m_OriY(0)
{
}

D2DSprite::D2DSprite(int spriteSheetIndex, int oriX, int oriY, int index, int width, int height,
	int keyColor, int centerPosX, int centerPosY, int delayFrame, const RECT& collision1, const RECT& collision2, int damage)
	: DRSprite(eSpriteType::ePickPos, index, width, height, keyColor, centerPosX, centerPosY, delayFrame, collision1, collision2, damage),
	m_SheetIndex(spriteSheetIndex), m_OriX(oriX), m_OriY(oriY)
{

}

D2DSprite::~D2DSprite()
{

}
