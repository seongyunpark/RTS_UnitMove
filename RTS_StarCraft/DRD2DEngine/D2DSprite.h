#pragma once

/// D2D Engine���� ����ϴ�
/// ����ü, define, enum��
/// [2/14/2020 LeHideHome]

#include "DREngineDefine.h"

class D2DSprite : public DRSprite
{
public:
	D2DSprite();
	D2DSprite(int spriteSheetIndex, int oriX, int oriY, int index, int width, int height, int keyColor,
		int centerPosX, int centerPosY, int delayFrame, const RECT& collision1, const RECT& collision2, int damage);
	virtual ~D2DSprite();


public:
	// DR������
	// A. ��������Ʈ ��Ʈ�� �ε� �� ����,
	// 1. �ű⿡�� Ư�� ��ġ/������� ����, �׸� �� ����ϴ� ������ �����Ѵ�.
	// 2. ���� �̹����� �ε��ϰ� ��Ʈ�� Ŭ������ ������ �ֵ��� �����Ѵ�.
	// 
	// B. ������ ��������Ʈ�� ��� �ٸ� �̹��� ���Ϸ� �о ���� ������ �ֵ��� �����Ѵ�.


	// ��������Ʈ ��Ʈ�� �ε���
	int m_SheetIndex;

	// ���������� ��ġ
	int m_OriX;
	int m_OriY;
};

