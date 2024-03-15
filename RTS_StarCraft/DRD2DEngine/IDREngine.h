#pragma once
#include <windows.h>
#include "DREngineDefine.h"

/// Darong 2D Engine Interface
///
/// ����ؼ� WinAPI, Direct2D���� ��� �����ϴ�.
/// ��� �߻�ȭ�� �Ǿ� ������, windows.h������ ����Ѵ�.
///
/// [12/27/2019 LeHide]
///

class IDREngine abstract
{
protected:
	static IDREngine* m_Instance;

public:
	//IDREngine();
	//~IDREngine();

	static IDREngine* GetInstance() { return m_Instance; }

	///--------------------------------------------------------------------------------
	/// �ʱ�ȭ, �׸���, ������

	// �ʱ�ȭ ����
	virtual void Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight) abstract;
	virtual void ChangeDisplay(int screenWidth, int screenHeight) abstract;
	virtual void RestoreDisplay() abstract;

	// Render ����
	virtual void BeginRender() abstract;

	// Render ��
	virtual void EndRender() abstract;

	// ������ �����Ѵ�.
	virtual void Finalize() abstract;


	///--------------------------------------------------------------------------------
	/// �׸��� ���� Primitive
	
	// ������ �׸��� �귯�� ����
	virtual void SetBrushColor(float r, float g, float b, float a) abstract;
	virtual void SetBrushColor(unsigned long dwRGBColor) abstract;

	// ������ ��ǥ�� �簢���� ����Ѵ�.
	virtual void DrawRectangle(int x, int y, int x1, int y1, COLORREF crBrush) abstract;
	virtual void DrawRectangle(int x, int y, int x1, int y1) abstract;
	virtual void DrawLine(int x1, int y1, int x2, int y2) abstract;
	virtual void DrawLine(int x1, int y1, int x2, int y2, COLORREF crBrush, float thickness = 1.0f) abstract;
	virtual void DrawEllipse(int x, int y, int size) abstract;
	virtual void DrawEllipse(int left, int top, int right, int bottom) abstract;
	virtual void DrawSelectRectangle(int x1, int y1, int x2, int y2) abstract;
	virtual void DrawSelectedCircle(int x, int y, int size) abstract;

	// ȭ�鿡 ���ڸ� ���
	virtual bool DrawText(int x, int y, const char* pch, ...) abstract;


	/// ----------------------------------------
	/// �׸��� ���� Sprite

	// ��Ʈ���� �ε��ϴ� ����
	virtual int LoadSpriteSheet(const char* filePath) abstract;
	virtual int LoadSpriteSheet(const wchar_t* filePath) abstract;
	virtual DRSprite* LoadSpriteFromSheet(char* filePath) abstract;
	virtual DRSprite* LoadSpriteFromSheet(int sheetIndex, int oriX, int oriY, int width, int height, int delayFrame) abstract;


	// �ٷ� �̹��� ������ �ϳ� �д� ����
	///virtual DRSprite* LoadSprite(char* filePath) abstract;
	///virtual DRSprite* GetSprite(int index) abstract;

	
	// ��������Ʈ ���
	// ���� ��ġ ���� ������ ������ �����̸� ������ �ִ�.
	virtual void DrawSprite(int spriteIndex, int dstX, int dstY) abstract;
	virtual void DrawSprite(DRSprite* sprite, int dstX, int dstY) abstract;


	// ��� ��������Ʈ/��������Ʈ ��Ʈ ����
	virtual void RemoveAllSprites() abstract;
	virtual void RemoveAllSpriteSheets() abstract;
};

/// ����� CPP���Ϸ�
/// IDREngine* IDREngine::m_Instance = nullptr;


/// virtual DRSprite* LoadSprite(char* filePath) abstract;
// �������� �ٸ��� ���� �� �� �ִ�. Direct2D���� ���, �ٷ� �ϳ��� �̹��� ������ ���� ���� �ְ�,
// WinAPI���� ��� ��������Ʈ ��Ʈ�� �ε�����, ������� ��ġ�� �˾Ƶ� �ȴ�.
// �� ���, �� ������ ���� ������ �ε��ϴ� ���ϼ��� �ְ�.. ���

