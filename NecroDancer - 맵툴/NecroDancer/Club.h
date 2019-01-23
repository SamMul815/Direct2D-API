#pragma once
#include "GameNode.h"
#include "D2DImage.h"
#include <vector>

#define MAPTILEX 25
#define MAPTILEY 25
#define TILESIZEX 24
#define TILESIZEY 24


enum tagTILE
{
	TILE_BASE1,
	TILE_BASE2,
	TILE_BASE3,
	TILE_BASE4,
	TILE_BASE5,
	TILE_BASE6
};
enum tagBLOCK
{
	BLOCK_BASE1,
	BLOCK_BASE2,
	BLOCK_BASE3,
	BLOCK_BASE4,
	BLOCK_BASE5,
	BLOCK_BASE6,
	BLOCK_BASE7,
	BLOCK_BASE8,
	BLOCK_BASE9,
	BLOCK_BASE10,
	BLOCK_BASE11,
	BLOCK_BASE12,
	BLOCK_BASE13,
	BLOCK_BASE14,
	BLOCK_BASE15,
	BLOCK_BASE16,
	BLOCK_STONE,
	BLOCK_GOLD,
	BLOCK_STEEL,
	BLOCK_DOORFRONT,
	BLOCK_DOORTURN,
	BLOCK_END
};
enum tagTRAP
{
	TRAP_MOVEUP,
	TRAP_MOVERIGHT,
	TRAP_MOVEDOWN,
	TRAP_MOVELEFT,
	TRAP_BOOM,
	TRAP_TELEPORT,
	TRAP_NEEDLE
};
enum tagSTIPOINT
{
	START_POINT,
	END_POINT,
	ITEM_POINT
};
enum tagMOUSETYPE
{
	MOUSE_TYPE_NONE,
	MOUSE_TYPE_TILE,
	MOUSE_TYPE_OBJECT,
	MOUSE_TYPE_ENEMY,
};
enum tagOBJECTTYPE
{
	OBJECT_NONE,		//없음
	OBJECT_BLOCK,		//블럭
	OBJECT_TRAP,		//함정
	OBJECT_ITEM,		//아이템
	OBJECT_ALTAR,		//제단
	OBJECT_POINT		//시작지점 끝지점
};
enum tagENEMY
{
	ENEMY_SLIME_GREEN,
	ENEMY_SLIME_ICE,
	ENEMY_SLIME_FIRE,
	ENEMY_SKELETON_BASE,
	ENEMY_SKELETON_ARMORED,
	ENEMY_SKELETON_KINGHT,
	ENEMY_MONKEY_BASE,
	ENEMY_MONKEY_YELLOW,
	ENEMY_BAT_BASE,
	ENEMY_GOBLIN_BASE,
	ENEMY_MINOTAUR_BASE,
	ENEMY_DRAGON_GREEN,
	ENEMY_DRAGON_BLUE,
	ENEMY_CHEST_BASE,
	ENEMY_SHOPKEEPER,
	ENEMY_END
	
};

struct TileData
{
	int tileType;		//타일 타입
	int objectType;		//오브젝트 타입
	int objectState;	//오브젝트 속성

	int x;	
	int y;	

	bool isEnemyUP;
};
struct EnemyData
{
	int type;
	int x;
	int y; 
};
struct MouseState
{
	RECT rc;
	int type;
	int objectType;
	int state;
};

class Club : public GameNode
{
private:
	
	D2DText *_txt;
	int _saveLoadNumber;
	ID2D1SolidColorBrush	*_brush;
	TileData _tile[MAPTILEX][MAPTILEY];
	MouseState _mouseState;
	//vector<EnemyData> _vEnemyData;
	//vector<EnemyData>::iterator _viEnemyData;



	D2DImage *_tileImage;
	D2DImage *_blockImage;
	D2DImage *_altaImage;
	D2DImage *_trapImage;
	D2DImage *_trapNeedleImage;

	D2DImage *_deleteImage;
	D2DImage *_enemyImage[ENEMY_END];
	D2DImage *_upButton;
	D2DImage *_downButton;
	D2DImage *_saveButton;
	D2DImage *_loadButton;
	D2DImage *_pointImage;


	RECT _tileRect;
	RECT _blockRect;
	RECT _altaRect;
	RECT _trapRect;
	RECT _trapNeedleRect;
	RECT _deleteRect;
	RECT _enemyRect[ENEMY_END];

	RECT _upRect;
	RECT _downRect;
	RECT _saveRect;
	RECT _loadRect;
	RECT _pointRect;

public:

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	void Save();
	void Load();

	Club();
	~Club();
};

