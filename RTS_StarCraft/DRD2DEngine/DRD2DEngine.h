#pragma once

/// Direct2d 그래픽스 엔진
///
/// 인터페이스를 통해서, WinAPI 그래픽스 엔진과 교체 가능하다.
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
	/// 초기화 관련

	// 초기화 관련
	virtual void Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight) override;
	virtual void ChangeDisplay(int screenWidth, int screenHeight) override;
	virtual void RestoreDisplay() override;

	// Render 시작
	virtual void BeginRender() override;

	// Render 끝
	virtual void EndRender() override;

	// 엔진을 종료한다.
	virtual void Finalize() override;

private:
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

public:
	///--------------------------------------------------------------------------------
	/// 그리기 관련

	// 도형을 그리는 브러시 관련
	virtual void SetBrushColor(float r, float g, float b, float a) override;
	virtual void SetBrushColor(unsigned long dwRGBColor) override;

	// 지정된 좌표에 사각형을 출력한다.
	virtual void DrawRectangle(int x, int y, int x1, int y1, COLORREF crBrush) override;
	virtual void DrawRectangle(int x, int y, int x1, int y1) override;
	virtual void DrawLine(int x1, int y1, int x2, int y2) override;
	virtual void DrawLine(int x1, int y1, int x2, int y2, COLORREF crBrush, float thickness = 1.0f) override;
	virtual void DrawEllipse(int x, int y, int size) override;
	virtual void DrawEllipse(int left, int top, int right, int bottom) override;
	virtual void DrawSelectRectangle(int x1, int y1, int x2, int y2) override;
	virtual void DrawSelectedCircle(int x, int y, int size) override;

	// 화면에 문자를 출력
	virtual bool DrawText(int x, int y, const char* pch, ...) override;


	/// ----------------------------------------
	/// 그리기 관련 Sprite

	// 시트에서 로드하는 버전
	virtual int LoadSpriteSheet(const char* filePath) override;
	virtual int LoadSpriteSheet(const wchar_t* filePath) override;
	virtual DRSprite* LoadSpriteFromSheet(char* filePath) override;
	virtual DRSprite* LoadSpriteFromSheet(int sheetIndex, int oriX, int oriY, int width, int height, int delayFrame) override;


	// 바로 이미지 파일을 하나 읽는 버전
	///virtual DRSprite* LoadSprite(char* filePath) abstract;
	///virtual DRSprite* GetSprite(int index) abstract;


	// 스프라이트 출력
	// 원본 위치 등의 정보는 엔진별 구현이며 숨겨져 있다.
	virtual void DrawSprite(int spriteIndex, int dstX, int dstY) override;
	virtual void DrawSprite(DRSprite* sprite, int dstX, int dstY) override;


	// 모든 스프라이트/스프라이트 시트 제거
	virtual void RemoveAllSprites() override;
	virtual void RemoveAllSpriteSheets() override;



	// 비트맵 관련
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


	/// 정리 된 멤버들 (DRD2DEngine)
private:
	HWND m_hWnd;								// 그리기를 할 윈도 (1개라고 가정)

	// Device Independant Resources
	ID2D1Factory* m_pD2DFactory;				// D2D는 Factory를 생성하면서 시작한다.

	IWICImagingFactory* m_pWICFactory;
	IDWriteFactory* m_pDWriteFactory;
	
	IDWriteTextFormat* m_pTextFormat;


	// Device Dependant Resources
	ID2D1HwndRenderTarget* m_pRenderTarget;		// 그리기를 할 대상인 랜더 타겟

	// 비트맵. 자원으로 분리되어야한다.
	ID2D1Bitmap* m_pBitmap;

	// 브러시들
	ID2D1SolidColorBrush* m_pWhiteBrush;
	ID2D1SolidColorBrush* m_pYellowBrush;
	ID2D1SolidColorBrush* m_pTempBrush;			// 그리기 함수 내에서만 사용의 용도
	ID2D1SolidColorBrush* m_pNowBrush;			// 바꿔가면서 여러 번 재사용의 용도



	/// ----------------------------------------
	/// 정리해야 할 것들
	// render
	HRESULT m_IsDDResReady;		// 디바이스 종속적인 자원들이 준비되었는가?
	D2D1_SIZE_F m_RenderTargetSize;
	/// ----------------------------------------


	// 스프라이트 관련
	int m_SpriteCount;			// 스프라이트의 갯수 (인덱스는 0부터)
	int m_SpriteSheetCount;		// 스프라이트 시트의 갯수 (인덱스는 0부터)
	std::vector<D2DSprite*> m_SpriteInfos;		/// 스프라이트의 정보. 시트 로드 방식이라면 한 개의 클래스로 될 것도 같다. 스프라이트 클래스조차 상속받아서 2개의 구현으로 가는 이유는, 실제로 비트맵을 읽어서 스프라이트 클래스 내부에 내장하는 경우 때문이다.
	std::map<int, ID2D1Bitmap*> m_SpriteSheets;	// 스프라이트 시트



	/// 테스트 중
public:
	// 비트맵 랜더링
	void DrawBitmap_Test(int posX, int posY);


	/// 로케일 쪽으로 보낼 것
private:
	wchar_t* ConvertCStoWCS(const char* orig);

};



/*

2020.02.14
텍스트 출력을 만들었음.
비트맵을 연동중

2020.01.01
이전의 작업에 이어서, 2개의 엔진의 상위에 추상 클래스를 놓고, 인터페이스를 일치시키는 중이다.
엔진의 첫 번째 버전의 완성은, 돌아가는 게임을 하나 적용시켜보는 것이다. (아마도 겐쥬로)


2019.12.27
Direct2D 엔진 스펙에 대해서:
추상화를 통해서, WinAPI와 병행해서 쓸 수 있도록 하자.
사실 래퍼 클래스들일 뿐이지만, 잘 써보자.



기능:
초기화/소멸
랜더타겟 설정(더블버퍼링 등)

디버그용 텍스트 출력
UI용 텍스트 출력

비트맵 출력
	각종 이펙트 적용
비트맵 스프라이트 애니메이션

각종 리소스 로드
	비트맵, 폰트, 랜더타겟, 쉐이더, 메쉬 등 필요한 것은 모두


실제 적용은, 겐쥬로에 해 보면 될 듯.
그러기 위해서는, 겐쥬로를 C++로 포팅하고 WinAPI엔진도 C++로 포팅해야 한다.


*/