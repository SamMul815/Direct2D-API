#include "stdafx.h"
#include "Stage2.h"


Stage2::Stage2()
{

}

Stage2::~Stage2()
{
}

HRESULT Stage2::Init(void)
{
	_beat = new Stage2Beat;	//비트 생성
	_beat->Init(WINSIZEY / 2 + 300);

	_enemyManager = new EnemyManager;
	_enemyManager->Init();
	_enemyManager->LinkEnemyTileData(*_tile);
	LoadMapData();

	_player->LinkBeat(_beat);
	_player->ImageInput();
	_player->Revision();
	_player->LinkTile(*_tile);
	_player->LinkEnemyManager(_enemyManager);
	//_enemyManager->LinkPlayer(_player);
	_renderHelper = new RenderHelper;
	_renderHelper->Init();
	_renderHelper->LinkeTileData(*_tile);
	_renderHelper->LinkePlayer(_player);
	_renderHelper->LinkEnemyManager(_enemyManager);

	return S_OK;
}
void Stage2::Release(void)
{
	SOUNDMANAGER->Stop("Stage2");
	SOUNDMANAGER->Stop("Stage2Shop");
}

void Stage2::Update(void)
{
	_beat->Update();
	_player->Update();

	_enemyManager->Update();

	if (_beat->NoteCheckEnemy())
	{
		_enemyManager->LinkEnemyTileData(*_tile);
		_enemyManager->Move();
	}

	CAMERA->SetXY(_player->GetPosX() - WINSIZEX / 6 - 12 + 15, _player->GetPosY() - WINSIZEY / 6 - 12 + 35);
	CAMERA->Update();
}

void Stage2::Render(void)
{
	_renderHelper->Render();
	_beat->Render();
	_player->UIRender();
}

void Stage2::LoadMapData()
{
	HANDLE file;
	char str[128];
	DWORD read;
	TileData   tile[MAPTILEX][MAPTILEY];

	//sprintf_s(str, "test.map");
	sprintf_s(str, "1.map");

	file = CreateFile(str, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, tile, sizeof(tile), &read, NULL);
	CloseHandle(file);

	for (int x = 0; x < MAPTILEX; x++)		//게임 내에서 사용할 형식으로 변경
	{
		for (int y = 0; y < MAPTILEY; y++)
		{
			_tile[y][x].objectType = tile[x][y].objectType;
			_tile[y][x].objectKind = tile[x][y].objectState;
			_tile[y][x].objectState = 0;
			_tile[y][x].tileType = tile[x][y].tileType;
			_tile[y][x].isEnemyUP = FALSE;
			_tile[y][x].isPlayerUP = FALSE;
		}
	}

	for (int x = 0; x < MAPTILEX; x++)		//플레이어 시작지점
	{
		for (int y = 0; y < MAPTILEY; y++)
		{
			if (_tile[y][x].objectType == OBJECT_POINT && _tile[y][x].objectKind == START_POINT)
			{
				_player->SetX(x);
				_player->SetY(y);
				_tile[y][x].objectType = OBJECT_NONE;
				_tile[y][x].objectKind = 0;
				_tile[y][x].isPlayerUP = TRUE;
			}
		}
	}
	_enemyManager->LinkPlayer(_player);
	//	몬스터 생성이 들어가야됨
	for (int x = 0; x < MAPTILEX; x++)		//게임 내에서 사용할 형식으로 변경
	{
		for (int y = 0; y < MAPTILEY; y++)
		{
			if (tile[x][y].isEnemyUP == TRUE)
			{
				switch (tile[x][y].objectState)
				{
				case ENEMY_SLIME_GREEN:
					_enemyManager->MakeSlimeGreen(x, y);
					_tile[y][x].isEnemyUP = TRUE;
					break;
				case ENEMY_SLIME_ICE:
					_enemyManager->MakeSlimeIce(x, y);
					_tile[y][x].isEnemyUP = TRUE;
					break;
				case ENEMY_SLIME_FIRE:
					_enemyManager->MakeSlimeFire(x, y);
					_tile[y][x].isEnemyUP = TRUE;
					break;

				case ENEMY_SKELETON_BASE:
					_enemyManager->MakeSkeletonBase(x, y);
					_tile[y][x].isEnemyUP = TRUE;
					break;
				case ENEMY_SKELETON_ARMORED:
					_enemyManager->MakeSkeletonArmored(x, y);
					_tile[y][x].isEnemyUP = TRUE;
					break;
				case ENEMY_DRAGON_GREEN:
					_enemyManager->MakeGreenDragon(x, y);
					_tile[y][x].isEnemyUP = TRUE;
					break;
				case ENEMY_SHOPKEEPER:
					_enemyManager->MakeShopKeeper(x, y, 2);
					_tile[y][x].isEnemyUP = TRUE;
					break;
				case ENEMY_CHEST_BASE:
					_enemyManager->MakeChest(x, y);
					_tile[y][x].isEnemyUP = TRUE;
					break;

				}
			}
		}
	}
	//


}
