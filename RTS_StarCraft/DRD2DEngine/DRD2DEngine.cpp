#include "DRD2DEngine.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")	// writefactory
#pragma comment(lib, "windowscodecs.lib") // WIC


DRD2DEngine::DRD2DEngine()
	: m_hWnd(nullptr),
	m_pD2DFactory(nullptr),
	m_pWICFactory(nullptr), m_pDWriteFactory(nullptr),
	m_pTextFormat(nullptr),
	m_pRenderTarget(nullptr),
	m_pBitmap(nullptr),
	m_pWhiteBrush(nullptr), m_pYellowBrush(nullptr), m_pTempBrush(nullptr), m_pNowBrush(nullptr),
	m_IsDDResReady(S_FALSE), m_RenderTargetSize(D2D1_SIZE_F())
{

}

DRD2DEngine::~DRD2DEngine()
{
	// 각 자원들의 명시적인 릴리즈 타이밍을 Finalize()로 옮겼음.

	// 명시적인 Finalize() 호출 이후에 엔진 소멸 시 필요한 처리
}

void DRD2DEngine::Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight)
{
	/// Initializes the COM library on the current thread and identifies the concurrency model as single-thread apartment (STA).
	HRESULT _hResult = CoInitialize(NULL);
	//CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	m_hWnd = hWnd;

	HRESULT hr = S_OK;

	// 1. Direct2D Factory를 만든다.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	static const WCHAR msc_fontName[] = L"굴림";
	static const FLOAT msc_fontSize = 12;

	if (SUCCEEDED(hr))
	{
		// Create WIC factory.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&m_pWICFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite factory.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&m_pTextFormat
		);
	}

	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	}




	/// 상위 부분

	// 스프라이트 관련
	// 새로운 스프라이트 체계
	m_SpriteCount = 0;
	m_SpriteInfos.clear();
	m_SpriteSheets.clear();


	/// 리소스 로드 타이밍을 만들어주자.
	/// 어쨌든 여기에서 한번 랜더 타겟을 만든다.
	/// 그래야 이 이후 리소스 로드를 문제없이 할 수 있다.
	m_IsDDResReady = CreateDeviceResources();


	/*
	// 크로마키 테스트
	ComPtr<ID2D1Effect> chromakeyEffect;
	m_d2dContext->CreateEffect(CLSID_D2D1ChromaKey, &chromakeyEffect);

	chromakeyEffect->SetInput(0, bitmap);
	chromaKeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, { 0.0f, 1.0f, 0.0f, 0.0f });
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.2f);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	chromakeyEffect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);
	*/

}

void DRD2DEngine::ChangeDisplay(int screenWidth, int screenHeight)
{

}

void DRD2DEngine::RestoreDisplay()
{

}

void DRD2DEngine::BeginRender()
{
	m_IsDDResReady = CreateDeviceResources();

	// 디바이스 종속적 자원들이 문제 없고, 랜더링을 할 수 있는 상황일 때
	if (SUCCEEDED(m_IsDDResReady) && !(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		// Retrieve the size of the render target.
		m_RenderTargetSize = m_pRenderTarget->GetSize();

		m_pRenderTarget->BeginDraw();

		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	}
}

HRESULT DRD2DEngine::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	// 2. Create a Direct2D render target.
	if (m_pRenderTarget == nullptr)
	{
		RECT rc;
		GetClientRect(m_hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);

		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hWnd, size/*, D2D1_PRESENT_OPTIONS_IMMEDIATELY*/),
			&m_pRenderTarget);

		if (SUCCEEDED(hr))
		{
			m_RenderTargetSize = m_pRenderTarget->GetSize();

			// Create brushes.
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pWhiteBrush);
			hr = m_pRenderTarget->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 0.f), &m_pYellowBrush);
			hr = m_pRenderTarget->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 1.0f), &m_pNowBrush);
		}

		/*
		// Create a bitmap from an application resource.
		hr = LoadResourceBitmap(
			m_pRenderTarget,
			m_pWICFactory,
			L"SampleImage",
			L"Image",
			100,
			0,
			&m_pBitmap
		);
		*/

		if (SUCCEEDED(hr))
		{
			// Create a bitmap by loading it from a file.
			hr = LoadBitmapFromFile(
				m_pRenderTarget,
				m_pWICFactory,
				L".\\sample.jpg",
				100,
				0,
				&m_pBitmap
			);
		}

		/*
		if (SUCCEEDED(hr))
		{
			// Create a black brush.
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				&m_pBlackBrush
			);
		}
		if (SUCCEEDED(hr))
		{
			ID2D1GradientStopCollection* pGradientStops = NULL;
			// Create a linear gradient.
			static const D2D1_GRADIENT_STOP stops[] =
			{
				{   0.f,  { 0.f, 1.f, 1.f, 0.25f }  },
				{   1.f,  { 0.f, 0.f, 1.f, 1.f }  },
			};

			hr = m_pRenderTarget->CreateGradientStopCollection(
				stops,
				ARRAYSIZE(stops),
				&pGradientStops
			);
			if (SUCCEEDED(hr))
			{
				hr = m_pRenderTarget->CreateLinearGradientBrush(
					D2D1::LinearGradientBrushProperties(
						D2D1::Point2F(100, 0),
						D2D1::Point2F(100, 200)),
					D2D1::BrushProperties(),
					pGradientStops,
					&m_pLinearGradientBrush
				);
				pGradientStops->Release();
			}
		}

		// Create a bitmap from an application resource.
		hr = LoadResourceBitmap(
			m_pRenderTarget,
			m_pWICFactory,
			L"SampleImage",
			L"Image",
			100,
			0,
			&m_pBitmap
		);
		if (SUCCEEDED(hr))
		{
			// Create a bitmap by loading it from a file.
			hr = LoadBitmapFromFile(
				m_pRenderTarget,
				m_pWICFactory,
				L".\\sampleImage.jpg",
				100,
				0,
				&m_pAnotherBitmap
			);
		}
		if (SUCCEEDED(hr))
		{
			hr = CreateGridPatternBrush(m_pRenderTarget, &m_pGridPatternBitmapBrush);
		}
		*/
	}

	return hr;
}

void DRD2DEngine::DiscardDeviceResources()
{
	SafeRelease(&m_pRenderTarget);
	//SafeRelease(&m_pBitmap);
	//SafeRelease(&m_pBlackBrush);
	//SafeRelease(&m_pLinearGradientBrush);
	//SafeRelease(&m_pAnotherBitmap);
	//SafeRelease(&m_pGridPatternBitmapBrush);
}

void DRD2DEngine::EndRender()
{
	if (SUCCEEDED(m_IsDDResReady) && !(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		static const WCHAR sc_helloWorld[] = L"Hello, World!";

		// Retrieve the size of the render target.
		///D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();

		//
		// Reset back to the identity transform
		//
		///m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, renderTargetSize.height - 200));

		HRESULT hr = m_pRenderTarget->EndDraw();

		// 자원을 복구해야 할 경우
		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();
		}
	}
}

void DRD2DEngine::Finalize()
{
	SafeRelease(&m_pD2DFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pDWriteFactory);
	SafeRelease(&m_pTextFormat);
	SafeRelease(&m_pWhiteBrush);
	SafeRelease(&m_pYellowBrush);
	SafeRelease(&m_pTempBrush);
	SafeRelease(&m_pNowBrush);

	CoUninitialize();
}

void DRD2DEngine::SetBrushColor(float r, float g, float b, float a)
{
	SafeRelease(&m_pNowBrush);
	///D2D1_BRUSH_PROPERTIES

	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &m_pNowBrush);
}

void DRD2DEngine::SetBrushColor(unsigned long dwRGBColor)
{
	SafeRelease(&m_pNowBrush);

	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(dwRGBColor)), &m_pNowBrush);
}

void DRD2DEngine::DrawRectangle(int x, int y, int x1, int y1, COLORREF crBrush)
{
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(crBrush)), &m_pTempBrush);

	if (m_pTempBrush != NULL)
	{
		D2D1_RECT_F _rt;
		_rt.left = (float)x;
		_rt.top = (float)y;
		_rt.right = (float)x1;
		_rt.bottom = (float)y1;

		m_pRenderTarget->DrawRectangle(_rt, m_pTempBrush, 1.0f);
	}

	SafeRelease(&m_pTempBrush);
}

void DRD2DEngine::DrawRectangle(int x, int y, int x1, int y1)
{
	D2D1_RECT_F _rt;
	_rt.left = (float)x;
	_rt.top = (float)y;
	_rt.right = (float)x1;
	_rt.bottom = (float)y1;

	m_pRenderTarget->DrawRectangle(_rt, m_pNowBrush, 2.0f);
}

void DRD2DEngine::DrawLine(int x1, int y1, int x2, int y2)
{
	D2D1_POINT_2F _point;
	_point.x = (float)x1;
	_point.y = (float)y1;
	D2D1_POINT_2F _point2;
	_point2.x = (float)x2;
	_point2.y = (float)y2;

	m_pRenderTarget->DrawLine(_point, _point2, m_pNowBrush, 1.0f);
}

void DRD2DEngine::DrawLine(int x1, int y1, int x2, int y2, COLORREF crBrush, float thickness /*= 1.0f*/)
{
	SetBrushColor(crBrush);

	D2D1_POINT_2F _point;
	_point.x = (float)x1;
	_point.y = (float)y1;
	D2D1_POINT_2F _point2;
	_point2.x = (float)x2;
	_point2.y = (float)y2;

	m_pRenderTarget->DrawLine(_point, _point2, m_pNowBrush, thickness);
}

void DRD2DEngine::DrawEllipse(int x, int y, int size)
{
	this->DrawEllipse(x, y, x + size, y + size);
}

void DRD2DEngine::DrawEllipse(int left, int top, int right, int bottom)
{
	D2D1_ELLIPSE _region;
	_region.point.x = (float)left;
	_region.point.y = (float)top;
	_region.radiusX = (float)(right - left);
	_region.radiusY = (float)(bottom - top);

	m_pRenderTarget->DrawEllipse(_region, m_pNowBrush);
}

void DRD2DEngine::DrawSelectRectangle(int x1, int y1, int x2, int y2)
{
	this->DrawRectangle(x1, y1, x2, y2, COLORREF(RGB(0, 255, 0)));
}

void DRD2DEngine::DrawSelectedCircle(int x, int y, int size)
{
	this->DrawEllipse(x, y, x + size, y + size);
}

bool DRD2DEngine::DrawText(int x, int y, const char* pch, ...)
{
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(pch, ap) + 1;
	buffer = new char[len];

	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);


	//int nLen = lstrlenA(pch);
	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, lstrlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	if (unicodestr != NULL)
	{
		// 폰트별 차지하는 영역 계산 필요
		m_pRenderTarget->DrawText(unicodestr, wcslen(unicodestr), m_pTextFormat,
			//D2D1::RectF(x, y, m_RenderTargetSize.width, m_RenderTargetSize.height),
			D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
			m_pNowBrush);
	}

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	return true;
}


/// ----------------------------------------
/// 그리기 관련 Sprite

/// 시트에서 로드하는 버전

// 스프라이트 시트를 로드한다.
int DRD2DEngine::LoadSpriteSheet(const char* filePath)
{
	wchar_t* _wcstring = this->ConvertCStoWCS(filePath);

	int _result = LoadSpriteSheet(_wcstring);

	delete[] _wcstring;

	return _result;
}

int DRD2DEngine::LoadSpriteSheet(const wchar_t* filePath)
{
	HRESULT hr;
	ID2D1Bitmap* pNewBitmap;

	// Create a bitmap by loading it from a file.
	hr = LoadBitmapFromFile(
		m_pRenderTarget,
		m_pWICFactory,
		filePath,
		0,
		0,
		&pNewBitmap
	);

	if (SUCCEEDED(hr))
	{
		m_SpriteSheets.insert(std::pair<int, ID2D1Bitmap*>(m_SpriteSheetCount, pNewBitmap));
		m_SpriteSheetCount++;

		return (m_SpriteSheetCount - 1);
	}

	return -1;
}

DRSprite* DRD2DEngine::LoadSpriteFromSheet(char* filePath)
{
	return nullptr;
}

// 이건 스프라이트 시트로부터 로드하는 것은 아니고, 그렇게 사용 할 용도로 스프라이트 클래스를 만들어서
// 내부 자료 구조에 넣어주는 것에 가깝다. 
DRSprite* DRD2DEngine::LoadSpriteFromSheet(int sheetIndex, int oriX, int oriY, int width, int height, int delayFrame)
{
	D2DSprite* _newSprite = new D2DSprite(sheetIndex, oriX, oriY, m_SpriteCount, width, height,
		0, 0, 0, delayFrame, RECT(), RECT(), 1);
	m_SpriteInfos.push_back(_newSprite);
	m_SpriteCount++;

	return _newSprite;
}

void DRD2DEngine::DrawSprite(int spriteIndex, int dstX, int dstY)
{
	D2DSprite* _D2DSprite = m_SpriteInfos[spriteIndex];

	if (_D2DSprite != NULL)
	{
		ID2D1Bitmap* _sheet = m_SpriteSheets[_D2DSprite->m_SheetIndex];	// 인덱스 접근 시 실패체크도 해야 함
		if (_sheet != NULL)
		{
			D2D1_SIZE_F size = m_pBitmap->GetSize();

			// Draw a bitmap in the upper-left corner of the window.
// 			m_pRenderTarget->DrawBitmap(_sheet,
// 				D2D1::RectF((float)dstX, (float)dstY, (float)(dstX + _D2DSprite->Width), (float)(dstY + _D2DSprite->Height)),
// 				1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
// 				D2D1::RectF(0, 0, 1.0f, 1.0f)
//  				);

			m_pRenderTarget->DrawBitmap(_sheet,
				D2D1::RectF((float)dstX, (float)dstY, (float)(dstX + _D2DSprite->Width), (float)(dstY + _D2DSprite->Height)),
				1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				D2D1::RectF(0, 0, (float)_D2DSprite->Width, (float)_D2DSprite->Height)
			);

			//m_pRenderTarget->DrawBitmap(_sheet);
		}
	}
}

void DRD2DEngine::DrawSprite(DRSprite* sprite, int dstX, int dstY)
{
	D2DSprite* _D2DSprite = dynamic_cast<D2DSprite*>(sprite);

	if (_D2DSprite != NULL)
	{
		ID2D1Bitmap* _sheet = m_SpriteSheets[_D2DSprite->m_SheetIndex];	// 인덱스 접근 시 실패체크도 해야 함
		if (_sheet != NULL)
		{
			m_pRenderTarget->DrawBitmap(_sheet,
				D2D1::RectF((float)dstX, (float)dstY, (float)(dstX + _D2DSprite->Width), (float)(dstY + _D2DSprite->Height)),
				1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				D2D1::RectF((float)_D2DSprite->m_OriX, (float)_D2DSprite->m_OriY, (float)(_D2DSprite->m_OriX + _D2DSprite->Width), (float)(_D2DSprite->m_OriY + _D2DSprite->Height))
			);
		}
	}
}

void DRD2DEngine::RemoveAllSprites()
{

}

void DRD2DEngine::RemoveAllSpriteSheets()
{

}

HRESULT DRD2DEngine::LoadResourceBitmap(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR resourceName, PCWSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void* pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);

	hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = pIWICFactory->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
					if (SUCCEEDED(hr))
					{
						hr = pConverter->Initialize(
							pScaler,
							GUID_WICPixelFormat32bppPBGRA,
							WICBitmapDitherTypeNone,
							NULL,
							0.f,
							WICBitmapPaletteTypeMedianCut
						);
					}
				}
			}
		}
		else
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

HRESULT DRD2DEngine::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

void DRD2DEngine::DrawBitmap_Test(int posX, int posY)
{

}

wchar_t* DRD2DEngine::ConvertCStoWCS(const char* orig)
{
	// newsize describes the length of the
	// wchar_t string called wcstring in terms of the number
	// of wide characters, not the number of bytes.
	size_t newsize = strlen(orig) + 1;

	// The following creates a buffer large enough to contain
	// the exact number of characters in the original string
	// in the new format. If you want to add more characters
	// to the end of the string, increase the value of newsize
	// to increase the size of the buffer.
	wchar_t* wcstring = new wchar_t[newsize];

	// Convert char* string to a wchar_t* string.
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);

	return wcstring;
}
