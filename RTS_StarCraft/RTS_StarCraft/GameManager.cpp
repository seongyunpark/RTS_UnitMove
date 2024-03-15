#include "GameManager.h"
#include "UnitManager.h"

GameManager::GameManager()
	:m_ScreenWidth(0), m_ScreenHeight(0),
	m_hWnd(nullptr), m_pDREngine(nullptr), m_pBackGround(nullptr),
	m_pUnitManager(nullptr),
	m_KeyUp(false), m_KeyDown(false), m_KeyLeft(false), m_KeyRight(false)
{
}

GameManager::~GameManager()
{
}

void GameManager::Initialize(HWND hWnd, int screenWidth, int screenHeight)
{
	m_hWnd = hWnd;
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;

	// 그래픽스 엔진 초기화
	m_pDREngine = new DRD2DEngine();
	m_pDREngine->Initialize(nullptr, hWnd, m_ScreenWidth, m_ScreenHeight);

	// 스타크래프트의 스프라이트 시트를 로드한다. // 스프라이트 순서도 여기서 된다
	m_pDREngine->LoadSpriteSheet("./Images/BackGround.png");		// 0번

	m_pDREngine->LoadSpriteSheet("./Images/CarrigunSheet.png");		// 1번
	m_pDREngine->LoadSpriteSheet("./Images/DroneSheet.png");		// 2번
	m_pDREngine->LoadSpriteSheet("./Images/LavaSheet.png");			// 3번
	m_pDREngine->LoadSpriteSheet("./Images/BroodlingSheet.png");	// 4번 
	m_pDREngine->LoadSpriteSheet("./Images/ZerglingSheet.png");		// 5번

	// 건물 sprite 를 로드한다
	m_pDREngine->LoadSpriteSheet("./Images/MutaliskSheet.png");		// 6번
	m_pDREngine->LoadSpriteSheet("./Images/GuardianSheet.png");		// 7번
	m_pDREngine->LoadSpriteSheet("./Images/ScourgeSheet.png");		// 8번	
	m_pDREngine->LoadSpriteSheet("./Images/OverloadSheet.png");		// 9번
	//m_pDREngine->LoadSpriteSheet("./Images/.png");

	//// 맵 sprite 를 로드한다
	m_pBackGround = m_pDREngine->LoadSpriteFromSheet(0, 0, 0, m_ScreenWidth, m_ScreenHeight, 1);


	//// 유닛 관련
	m_pUnitManager = new UnitManager(m_pDREngine, hWnd);

	// 라바
	m_pUnitManager->CreateUnit(eUnitType::Lava, 100, 100, ePlayer::player1, 100);
	// 드론
	m_pUnitManager->CreateUnit(eUnitType::Drone, 300, 100, ePlayer::player1, 200);
	// 캐리건
	m_pUnitManager->CreateUnit(eUnitType::Carrigun, 500, 100, ePlayer::player1, 300);
	// 브루들링
	m_pUnitManager->CreateUnit(eUnitType::Broodling, 700, 100, ePlayer::player1, 500);
	// 뮤탈리스크
	m_pUnitManager->CreateUnit(eUnitType::Muatalisk, 100, 900, ePlayer::player2, 400);
	// 가디언
	m_pUnitManager->CreateUnit(eUnitType::Guardian, 300, 900, ePlayer::player2, 500);
	// 스커지
	m_pUnitManager->CreateUnit(eUnitType::Scourge, 500, 900, ePlayer::player2, 400);
	// 오버로드
	m_pUnitManager->CreateUnit(eUnitType::Overload, 700, 900, ePlayer::player2, 600);
}

void GameManager::Update()
{
	m_pUnitManager->UpdateAllUnit();
}

void GameManager::Render()
{
	m_pDREngine->BeginRender();

	m_pDREngine->DrawSprite(m_pBackGround, 0, 0);

	// 모든 유닛을 돌면서, 그림을 그려준다
	m_pUnitManager->RenderAllUnit();
	m_pUnitManager->RenderStatus();

	m_pDREngine->EndRender();
}
