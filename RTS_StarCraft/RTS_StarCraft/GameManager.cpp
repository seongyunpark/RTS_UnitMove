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

	// �׷��Ƚ� ���� �ʱ�ȭ
	m_pDREngine = new DRD2DEngine();
	m_pDREngine->Initialize(nullptr, hWnd, m_ScreenWidth, m_ScreenHeight);

	// ��Ÿũ����Ʈ�� ��������Ʈ ��Ʈ�� �ε��Ѵ�. // ��������Ʈ ������ ���⼭ �ȴ�
	m_pDREngine->LoadSpriteSheet("./Images/BackGround.png");		// 0��

	m_pDREngine->LoadSpriteSheet("./Images/CarrigunSheet.png");		// 1��
	m_pDREngine->LoadSpriteSheet("./Images/DroneSheet.png");		// 2��
	m_pDREngine->LoadSpriteSheet("./Images/LavaSheet.png");			// 3��
	m_pDREngine->LoadSpriteSheet("./Images/BroodlingSheet.png");	// 4�� 
	m_pDREngine->LoadSpriteSheet("./Images/ZerglingSheet.png");		// 5��

	// �ǹ� sprite �� �ε��Ѵ�
	m_pDREngine->LoadSpriteSheet("./Images/MutaliskSheet.png");		// 6��
	m_pDREngine->LoadSpriteSheet("./Images/GuardianSheet.png");		// 7��
	m_pDREngine->LoadSpriteSheet("./Images/ScourgeSheet.png");		// 8��	
	m_pDREngine->LoadSpriteSheet("./Images/OverloadSheet.png");		// 9��
	//m_pDREngine->LoadSpriteSheet("./Images/.png");

	//// �� sprite �� �ε��Ѵ�
	m_pBackGround = m_pDREngine->LoadSpriteFromSheet(0, 0, 0, m_ScreenWidth, m_ScreenHeight, 1);


	//// ���� ����
	m_pUnitManager = new UnitManager(m_pDREngine, hWnd);

	// ���
	m_pUnitManager->CreateUnit(eUnitType::Lava, 100, 100, ePlayer::player1, 100);
	// ���
	m_pUnitManager->CreateUnit(eUnitType::Drone, 300, 100, ePlayer::player1, 200);
	// ĳ����
	m_pUnitManager->CreateUnit(eUnitType::Carrigun, 500, 100, ePlayer::player1, 300);
	// ���鸵
	m_pUnitManager->CreateUnit(eUnitType::Broodling, 700, 100, ePlayer::player1, 500);
	// ��Ż����ũ
	m_pUnitManager->CreateUnit(eUnitType::Muatalisk, 100, 900, ePlayer::player2, 400);
	// �����
	m_pUnitManager->CreateUnit(eUnitType::Guardian, 300, 900, ePlayer::player2, 500);
	// ��Ŀ��
	m_pUnitManager->CreateUnit(eUnitType::Scourge, 500, 900, ePlayer::player2, 400);
	// �����ε�
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

	// ��� ������ ���鼭, �׸��� �׷��ش�
	m_pUnitManager->RenderAllUnit();
	m_pUnitManager->RenderStatus();

	m_pDREngine->EndRender();
}
