#pragma once

/// Direct2d �׷��Ƚ� ����
///
/// �������̽��� ���ؼ�, WinAPI �׷��Ƚ� ������ ��ü �����ϴ�.
///
/// [11/16/2019 LeHideHome]

#include "D2DSprite.h"
#include "IDREngine.h"
#include <vector>
#include <map>
#include <string>
#include "DRMacro.h"
#include <d2d1.h>
#include <d2d1_1.h>
#include "d2d1helper.h"		// ColorF
#include <dwrite.h>			// writefactory
#include <wincodec.h>		// WIC
#include "d2d1effects_2.h"	// 

using namespace D2D1;

class DRD2DEngine : public IDREngine
{
public:
	DRD2DEngine();
	virtual ~DRD2DEngine();

	/// IDREngine override
public:
	///--------------------------------------------------------------------------------
	/// �ʱ�ȭ ����

	// �ʱ�ȭ ����
	virtual void Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight) override;
	virtual void ChangeDisplay(int screenWidth, int screenHeight) override;
	virtual void RestoreDisplay() override;

	// Render ����
	virtual void BeginRender() override;

	// Render ��
	virtual void EndRender() override;

	// ������ �����Ѵ�.
	virtual void Finalize() override;

private:
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

public:
	///--------------------------------------------------------------------------------
	/// �׸��� ����

	// ������ �׸��� �귯�� ����
	virtual void SetBrushColor(float r, float g, float b, float a) override;
	virtual void SetBrushColor(unsigned long dwRGBColor) override;

	// ������ ��ǥ�� �簢���� ����Ѵ�.
	virtual void DrawRectangle(int x, int y, int x1, int y1, COLORREF crBrush) override;
	virtual void DrawRectangle(int x, int y, int x1, int y1) override;
	virtual void DrawLine(int x1, int y1, int x2, int y2) override;
	virtual void DrawLine(int x1, int y1, int x2, int y2, COLORREF crBrush, float thickness = 1.0f) override;
	virtual void DrawEllipse(int x, int y, int size) override;
	virtual void DrawEllipse(int left, int top, int right, int bottom) override;
	virtual void DrawSelectRectangle(int x1, int y1, int x2, int y2) override;
	virtual void DrawSelectedCircle(int x, int y, int size) override;

	// ȭ�鿡 ���ڸ� ���
	virtual bool DrawText(int x, int y, const char* pch, ...) override;


	/// ----------------------------------------
	/// �׸��� ���� Sprite

	// ��Ʈ���� �ε��ϴ� ����
	virtual int LoadSpriteSheet(const char* filePath) override;
	virtual int LoadSpriteSheet(const wchar_t* filePath) override;
	virtual DRSprite* LoadSpriteFromSheet(char* filePath) override;
	virtual DRSprite* LoadSpriteFromSheet(int sheetIndex, int oriX, int oriY, int width, int height, int delayFrame) override;


	// �ٷ� �̹��� ������ �ϳ� �д� ����
	///virtual DRSprite* LoadSprite(char* filePath) abstract;
	///virtual DRSprite* GetSprite(int index) abstract;


	// ��������Ʈ ���
	// ���� ��ġ ���� ������ ������ �����̸� ������ �ִ�.
	virtual void DrawSprite(int spriteIndex, int dstX, int dstY) override;
	virtual void DrawSprite(DRSprite* sprite, int dstX, int dstY) override;


	// ��� ��������Ʈ/��������Ʈ ��Ʈ ����
	virtual void RemoveAllSprites() override;
	virtual void RemoveAllSpriteSheets() override;



	// ��Ʈ�� ����
private:
	HRESULT LoadResourceBitmap(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	// Create a bitmap by loading it from a file.
	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);


	/// ���� �� ����� (DRD2DEngine)
private:
	HWND m_hWnd;								// �׸��⸦ �� ���� (1����� ����)

	// Device Independant Resources
	ID2D1Factory* m_pD2DFactory;				// D2D�� Factory�� �����ϸ鼭 �����Ѵ�.

	IWICImagingFactory* m_pWICFactory;
	IDWriteFactory* m_pDWriteFactory;
	
	IDWriteTextFormat* m_pTextFormat;


	// Device Dependant Resources
	ID2D1HwndRenderTarget* m_pRenderTarget;		// �׸��⸦ �� ����� ���� Ÿ��

	// ��Ʈ��. �ڿ����� �и��Ǿ���Ѵ�.
	ID2D1Bitmap* m_pBitmap;

	// �귯�õ�
	ID2D1SolidColorBrush* m_pWhiteBrush;
	ID2D1SolidColorBrush* m_pYellowBrush;
	ID2D1SolidColorBrush* m_pTempBrush;			// �׸��� �Լ� �������� ����� �뵵
	ID2D1SolidColorBrush* m_pNowBrush;			// �ٲ㰡�鼭 ���� �� ������ �뵵



	/// ----------------------------------------
	/// �����ؾ� �� �͵�
	// render
	HRESULT m_IsDDResReady;		// ����̽� �������� �ڿ����� �غ�Ǿ��°�?
	D2D1_SIZE_F m_RenderTargetSize;
	/// ----------------------------------------


	// ��������Ʈ ����
	int m_SpriteCount;			// ��������Ʈ�� ���� (�ε����� 0����)
	int m_SpriteSheetCount;		// ��������Ʈ ��Ʈ�� ���� (�ε����� 0����)
	std::vector<D2DSprite*> m_SpriteInfos;		/// ��������Ʈ�� ����. ��Ʈ �ε� ����̶�� �� ���� Ŭ������ �� �͵� ����. ��������Ʈ Ŭ�������� ��ӹ޾Ƽ� 2���� �������� ���� ������, ������ ��Ʈ���� �о ��������Ʈ Ŭ���� ���ο� �����ϴ� ��� �����̴�.
	std::map<int, ID2D1Bitmap*> m_SpriteSheets;	// ��������Ʈ ��Ʈ



	/// �׽�Ʈ ��
public:
	// ��Ʈ�� ������
	void DrawBitmap_Test(int posX, int posY);


	/// ������ ������ ���� ��
private:
	wchar_t* ConvertCStoWCS(const char* orig);

};



/*

2020.02.14
�ؽ�Ʈ ����� �������.
��Ʈ���� ������

2020.01.01
������ �۾��� �̾, 2���� ������ ������ �߻� Ŭ������ ����, �������̽��� ��ġ��Ű�� ���̴�.
������ ù ��° ������ �ϼ���, ���ư��� ������ �ϳ� ������Ѻ��� ���̴�. (�Ƹ��� �����)


2019.12.27
Direct2D ���� ���忡 ���ؼ�:
�߻�ȭ�� ���ؼ�, WinAPI�� �����ؼ� �� �� �ֵ��� ����.
��� ���� Ŭ�������� ��������, �� �Ẹ��.



���:
�ʱ�ȭ/�Ҹ�
����Ÿ�� ����(������۸� ��)

����׿� �ؽ�Ʈ ���
UI�� �ؽ�Ʈ ���

��Ʈ�� ���
	���� ����Ʈ ����
��Ʈ�� ��������Ʈ �ִϸ��̼�

���� ���ҽ� �ε�
	��Ʈ��, ��Ʈ, ����Ÿ��, ���̴�, �޽� �� �ʿ��� ���� ���


���� ������, ����ο� �� ���� �� ��.
�׷��� ���ؼ���, ����θ� C++�� �����ϰ� WinAPI������ C++�� �����ؾ� �Ѵ�.


*/