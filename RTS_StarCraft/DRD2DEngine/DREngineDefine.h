#pragma once

#include <windows.h>

/// ��������Ʈ�� �߻����� ����
/// ���� ������ �ٸ� �� �ִ�.
class DRSprite
{
public:
	// ������ ����? ����Ƶ� �������� ���
	enum class eSpriteType
	{
		eBWType,	// ���� �������̹��� �����͸� ������ ����. DRSpiteŬ������ ��ӹ޾ƾ� ��
		ePickPos,	// ��ġ, ũ�⸸ ������ ������, �׸� �� �̸� �ε�� ��������Ʈ ��Ʈ���� �Ϻθ� Blit�Ѵ�.
	};

public:
	DRSprite();
	DRSprite(eSpriteType spriteType, int index, int width, int height, int keyColor, 
		int centerPosX, int centerPosY, int delayFrame, const RECT& collision1, const RECT& collision2, int damage);
	virtual ~DRSprite();




public:
	// ��������Ʈ ���� ���
	eSpriteType SpriteType;

	// ������ Ư�� �ε���(Ű)
	int Index;

	// ��������Ʈ�� ��, ����
	int Width;
	int Height;

	// Ű �÷� (TransparentBlit���� ���)
	int KeyColor;

	// �ִϸ��̼� ����
	int CenterPosX;		// ��Ʈ���� �߽� (ĳ������ �� ��ġ ��)
	int CenterPosY;
	int DelayFrame;		// �ִϸ��̼� ���� ������(������)

	// ���� ����
	RECT Collision1;	// �浹����1 (e.g. �ǰ�)
	RECT Collision2;	// �浹����2 (e.g. ����)
	int Damage;			// ��ݷ�
};

// ARGB�ε�
#define DRCOLOR_WHITE	0xFFFFFFFF
#define DRCOLOR_RED		0xFFFF0000
#define DRCOLOR_GREEN	0xFF00FF00
#define DRCOLOR_BLUE	0xFF0000FF
#define DRCOLOR_MAGENTA	0xFFFF00FF
#define DRCOLOR_YELLOW	0xFFFFFF00
#define DRCOLOR_CYAN	0xFF00FFFF
#define DRCOLOR_GRAY	0xFFCCCCCC
#define DRCOLOR_DARKGRAY 0xFF777777





