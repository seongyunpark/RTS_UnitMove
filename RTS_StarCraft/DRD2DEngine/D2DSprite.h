#pragma once

/// D2D Engine에서 사용하는
/// 구조체, define, enum등
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
	// DR엔진은
	// A. 스프라이트 시트를 로드 해 놓고,
	// 1. 거기에서 특정 위치/사이즈만을 보관, 그릴 때 사용하는 식으로 구현한다.
	// 2. 실제 이미지를 로드하고 비트맵 클래스를 가지고 있도록 구현한다.
	// 
	// B. 각각의 스프라이트를 모두 다른 이미지 파일로 읽어서 실제 가지고 있도록 구현한다.


	// 스프라이트 시트의 인덱스
	int m_SheetIndex;

	// 원본에서의 위치
	int m_OriX;
	int m_OriY;
};

