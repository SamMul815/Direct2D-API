#include "stdafx.h"
#include "Club.h"

#define MAX 50

Club::Club()
{
}


Club::~Club()
{
}

HRESULT Club::Init()
{
	GameNode::Init();

	_tileImage = new D2DImage;
	_tileImage->Init(L".\\Image\\TILE\\Stage1_TILE.png", 78, 52, 3, 2);					//이미지 불러오기

	_blockImage = new D2DImage;
	_blockImage->Init(L".\\Image\\OBJECT\\Stage1_BLOCK.png", 504, 48, 21, 1);			//블럭 불러오기

	_altaImage = new D2DImage;
	_altaImage->Init(L".\\Image\\OBJECT\\Stage1_ALTAR.png", 140, 48, 4, 1);				//제단

	_trapImage = new D2DImage;
	_trapImage->Init(L".\\Image\\OBJECT\\Stage1_TRAP.png", 84, 16, 6, 1);				//함정

	_trapNeedleImage = new D2DImage;
	_trapNeedleImage->Init(L".\\Image\\OBJECT\\spiketrap.png", 34, 20);					//가시함정

	_deleteImage = new D2DImage;
	_deleteImage->Init(L".\\Image\\x.png", 24, 48);										//취소버튼


	for (int i = ENEMY_SLIME_GREEN; i < ENEMY_END; i++)									//적들
		_enemyImage[i] = new D2DImage;

	_enemyImage[ENEMY_SLIME_GREEN]->Init(L".\\Image\\ENEMY\\slime_green.png",26,26);
	_enemyImage[ENEMY_SLIME_ICE]->Init(L".\\Image\\ENEMY\\slime_ice.png",26,26);
	_enemyImage[ENEMY_SLIME_FIRE]->Init(L".\\Image\\ENEMY\\slime_fire.png",26,26);
	_enemyImage[ENEMY_SKELETON_BASE]->Init(L".\\Image\\ENEMY\\skeleton.png",24,25);
	_enemyImage[ENEMY_SKELETON_ARMORED]->Init(L".\\Image\\ENEMY\\skeletonarmored.png",24,24);
	_enemyImage[ENEMY_SKELETON_KINGHT]->Init(L".\\Image\\ENEMY\\skeletonknight.png",36,42);
	_enemyImage[ENEMY_MONKEY_BASE]->Init(L".\\Image\\ENEMY\\monkey.png",25,24);
	_enemyImage[ENEMY_MONKEY_YELLOW]->Init(L".\\Image\\ENEMY\\monkey_yellow.png",25,24);
	_enemyImage[ENEMY_BAT_BASE]->Init(L".\\Image\\ENEMY\\bat.png",24,24);
	_enemyImage[ENEMY_GOBLIN_BASE]->Init(L".\\Image\\ENEMY\\goblin_bomber.png",26,36);
	_enemyImage[ENEMY_MINOTAUR_BASE]->Init(L".\\Image\\ENEMY\\minotaur.png",50,49);
	_enemyImage[ENEMY_DRAGON_GREEN]->Init(L".\\Image\\ENEMY\\dragon_green.png",54,51);
	_enemyImage[ENEMY_DRAGON_BLUE]->Init(L".\\Image\\ENEMY\\dragon_blue.png",61,51);
	_enemyImage[ENEMY_CHEST_BASE]->Init(L".\\Image\\ENEMY\\chest.png", 24, 24);
	_enemyImage[ENEMY_SHOPKEEPER]->Init(L".\\Image\\ENEMY\\shopkeeper.png",47,38);

	_upButton = new D2DImage;								//저장관련 버튼
	_upButton->Init(L".\\Image\\UP.png",56,64);
	_downButton = new D2DImage;
	_downButton->Init(L".\\Image\\DOWN.png",56,64);
	_saveButton = new D2DImage;
	_saveButton->Init(L".\\Image\\S.png",60,60);
	_loadButton = new D2DImage;
	_loadButton->Init(L".\\Image\\L.png",60,60);
	_pointImage = new D2DImage;
	_pointImage->Init(L".\\Image\\OBJECT\\Point.png", 72, 24, 3, 1);				//제단

	_tileRect   = RectMake(700, 0, _tileImage->GetWidth(), _tileImage->GetHeight());
	_deleteRect = RectMake(_tileRect.right + 20, 0, _deleteImage->GetWidth(), _deleteImage->GetHeight());
	_blockRect  = RectMake(700, _tileRect.bottom + 10, _blockImage->GetWidth(), _blockImage->GetHeight());
	_altaRect   = RectMake(700, _blockRect.bottom + 10, _altaImage->GetWidth(), _altaImage->GetHeight());
	_trapRect   = RectMake(700, _altaRect.bottom + 20, _trapImage->GetWidth(), _trapImage->GetHeight());
	_trapNeedleRect = RectMake(_trapRect.right + 10, _trapRect.top, _trapNeedleImage->GetWidth(), _trapNeedleImage->GetHeight());
	_upRect		= RectMake(1100,150,_upButton->GetWidth(),_upButton->GetHeight());
	_downRect	= RectMake(_upRect.left,_upRect.bottom + 10 ,_downButton->GetWidth(),_downButton->GetHeight());	
	_saveRect	= RectMake(_downRect.left,_downRect.bottom + 10, _saveButton->GetWidth(),_saveButton->GetHeight());
	_loadRect	= RectMake(_saveRect.left,_saveRect.bottom + 10, _loadButton->GetWidth(), _loadButton->GetHeight());
	_pointRect  = RectMake(1000, 150, _pointImage->GetWidth(), _pointImage->GetHeight());

	for (int i = ENEMY_SLIME_GREEN; i < ENEMY_END; i++)
		_enemyRect[i] = RectMake(700+(i % 3) * 65 ,250+(i/3)*55, _enemyImage[i]->GetWidth(), +_enemyImage[i]->GetHeight());


	for (int i = 0; i < MAPTILEX; i++)									//타일맵 기본 셋팅
	{
		for (int j = 0; j < MAPTILEY; j++)
		{
			if(j%2 == 0)
				_tile[i][j].tileType = i%2;
			else
				_tile[i][j].tileType = (i+1) % 2;

			_tile[i][j].isEnemyUP = FALSE;
			_tile[i][j].objectType  = OBJECT_NONE;
			_tile[i][j].objectState = 0;
			_tile[i][j].x = i * TILESIZEX;
			_tile[i][j].y = j * TILESIZEY;
		}
	}

	_txt = new D2DText;
	_txt->Init(L"돋움", 30, D2D1::ColorF(0, 0, 0));

	_mouseState.type = MOUSE_TYPE_NONE;
	_brush = D2DMANAGER->MakeBrush(D2D1::ColorF(1.0f, 0, 0));

	return S_OK;
}

void Club::Release()
{
	GameNode::Release();
}

void Club::Update()
{
	GameNode::Update();

	if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_upRect, _ptMouse))	//위쪽 클릭
		{
			_saveLoadNumber++;
		}
		else if (PtInRect(&_downRect, _ptMouse))	//아래쪽 클릭
		{
			_saveLoadNumber--;
		}
		else if (PtInRect(&_saveRect, _ptMouse))	//아래쪽 클릭
		{
			Save();
		}
		else if (PtInRect(&_loadRect, _ptMouse))	//아래쪽 클릭
		{
			Load();
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x < 600 && _ptMouse.y < 600)
		{
			int x = _ptMouse.x / TILESIZEX;
			int y = _ptMouse.y / TILESIZEY;

			if (_mouseState.type == MOUSE_TYPE_TILE)			//타일 설치
			{
				_tile[x][y].tileType = _mouseState.state;
			}
			else if (_mouseState.type == MOUSE_TYPE_OBJECT)		//오브젝트 설치
			{
				_tile[x][y].objectType = _mouseState.objectType;
				_tile[x][y].objectState = _mouseState.state;
			}
			else if (_mouseState.type == MOUSE_TYPE_NONE)		//오브젝트 삭제
			{
				_tile[x][y].objectType = _mouseState.objectType;
				_tile[x][y].objectState = _mouseState.state;
				_tile[x][y].isEnemyUP = FALSE;
			}
			if (_mouseState.type == MOUSE_TYPE_ENEMY && _tile[x][y].isEnemyUP == FALSE)	
			{
				_tile[x][y].isEnemyUP = TRUE;		//몬스터 설치
				_tile[x][y].objectState = _mouseState.state;
			}
		}

		if (PtInRect(&_tileRect, _ptMouse))		//타일 클릭했을경우
		{
			_mouseState.type  = MOUSE_TYPE_TILE;
			_mouseState.state = ((_ptMouse.x - _tileRect.left) / (int)_tileImage->GetFrameWidth()) + ((_ptMouse.y - _tileRect.top) / (int)_tileImage->GetFrameHeight() * 3);
			_mouseState.rc = RectMake(_mouseState.state % (_tileImage->GetMaxFrameX() + 1)*_tileImage->GetFrameWidth() + _tileRect.left, (_tileRect.top + (_mouseState.state / (_tileImage->GetMaxFrameX() + 1)*_tileImage->GetFrameHeight())), _tileImage->GetFrameWidth(), _tileImage->GetFrameHeight());
			//_mouseState.rc = RectMake(((_mouseState.state%(_tileImage->GetMaxFrameX()+1))*_tileImage->GetFrameWidth() + _tileRect.left, (_tileRect.top + (_mouseState.state / (_tileImage->GetMaxFrameX()+1))*_tileImage->GetFrameHeight()) , _tileImage->GetFrameWidth(), _tileImage->GetFrameHeight());
		}
		else if (PtInRect(&_blockRect, _ptMouse))	//블럭 클릭했을경우
		{
			_mouseState.type = MOUSE_TYPE_OBJECT;
			_mouseState.objectType = OBJECT_BLOCK;
			_mouseState.state = (_ptMouse.x - _blockRect.left) / (_blockImage->GetFrameWidth());
			_mouseState.rc = RectMake(_mouseState.state*_blockImage->GetFrameWidth() + _blockRect.left, _blockRect.top, _blockImage->GetFrameWidth(), _blockImage->GetFrameHeight());
		}
		else if (PtInRect(&_altaRect, _ptMouse))	//제단 클릭했을경우
		{
			_mouseState.type = MOUSE_TYPE_OBJECT;
			_mouseState.objectType = OBJECT_ALTAR;
			_mouseState.state = (_ptMouse.x - _altaRect.left) / (_altaImage->GetFrameWidth());
			_mouseState.rc = RectMake(_mouseState.state*_altaImage->GetFrameWidth() + _altaRect.left, _altaRect.top, _altaImage->GetFrameWidth(), _altaImage->GetFrameHeight());
		}
		else if (PtInRect(&_trapRect, _ptMouse))	//함정 클릭했을경우
		{
			_mouseState.type = MOUSE_TYPE_OBJECT;
			_mouseState.objectType = OBJECT_TRAP;
			_mouseState.state = (_ptMouse.x - _trapRect.left) / (_trapImage->GetFrameWidth());
			_mouseState.rc = RectMake(_mouseState.state*_trapImage->GetFrameWidth() + _trapRect.left, _trapRect.top, _trapImage->GetFrameWidth(), _trapImage->GetFrameHeight());
		}
		else if (PtInRect(&_trapNeedleRect, _ptMouse))	//까시 함정..
		{
			_mouseState.type = MOUSE_TYPE_OBJECT;
			_mouseState.objectType = OBJECT_TRAP;
			_mouseState.state = TRAP_NEEDLE;
			_mouseState.rc = _trapNeedleRect;

		}
		else if (PtInRect(&_pointRect, _ptMouse))	//각종 지점 클릭
		{
			_mouseState.type = MOUSE_TYPE_OBJECT;
			_mouseState.objectType = OBJECT_POINT;
			_mouseState.state = (_ptMouse.x - _pointRect.left) / (_pointImage->GetFrameWidth());
			_mouseState.rc = RectMake(_mouseState.state*_pointImage->GetFrameWidth() + _pointRect.left, _pointRect.top, _pointImage->GetFrameWidth(), _pointImage->GetFrameHeight());
		}
		else if (PtInRect(&_deleteRect, _ptMouse))	//삭제 클릭했을 경우
		{
			_mouseState.type = MOUSE_TYPE_NONE;
			_mouseState.objectType = OBJECT_NONE;
			_mouseState.state = 0;
			_mouseState.rc = _deleteRect;
		}
		for (int i = ENEMY_SLIME_GREEN; i < ENEMY_END; i++) //몬스터 클릭시
		{
			if (PtInRect(&_enemyRect[i], _ptMouse))		
			{
				_mouseState.type = MOUSE_TYPE_ENEMY;
				_mouseState.state = i;
				_mouseState.rc = _enemyRect[i];
			}
		}
	}
}

void Club::Render()
{
	D2DMANAGER->BeginDraw();

	//타일 렌더
	for (int i = 0; i < MAPTILEX; i++)
	{
		for (int j = 0; j < MAPTILEY; j++)
		{
			_tileImage->FrameRender(i * TILESIZEX -1, j * TILESIZEY -1,_tile[i][j].tileType);
		}
	}

	for (int j = 0; j < MAPTILEY; j++)
		{
			for (int i = 0; i < MAPTILEX; i++)
			{
			if (_tile[i][j].objectType == OBJECT_BLOCK)
				_blockImage->FrameRender(i * TILESIZEX - 1, j * TILESIZEY - (_blockImage->GetFrameHeight() - TILESIZEY )+8, _tile[i][j].objectState, 0);
			else if (_tile[i][j].objectType == OBJECT_ALTAR)
				_altaImage->FrameRender(i*TILESIZEX - 4, j*TILESIZEY - 24, _tile[i][j].objectState, 0);
			else if (_tile[i][j].objectType == OBJECT_TRAP)
			{
				if(_tile[i][j].objectState == TRAP_NEEDLE)
					_trapNeedleImage->Render(i * TILESIZEX - 5, j * TILESIZEY);
				else
					_trapImage->FrameRender(i * TILESIZEX + _trapImage->GetFrameWidth() / 2 - 2, j * TILESIZEY + _trapImage->GetFrameHeight() / 2 - 5, _tile[i][j].objectState, 0);

			}
			else if (_tile[i][j].objectType == OBJECT_POINT)
				_pointImage->FrameRender(i * TILESIZEX , j * TILESIZEY , _tile[i][j].objectState, 0);
			if (_tile[i][j].isEnemyUP == TRUE)
			{
				_enemyImage[_tile[i][j].objectState]->Render(i*TILESIZEX - (_enemyImage[_tile[i][j].objectState]->GetWidth() - TILESIZEX)/2 ,
															 j*TILESIZEY - (_enemyImage[_tile[i][j].objectState]->GetHeight() - TILESIZEY) - (TILESIZEY/2));
			}
		
		}
	}

	_tileImage->Render(_tileRect.left, _tileRect.top);
	_blockImage->Render(_blockRect.left, _blockRect.top);
	_altaImage->Render(_altaRect.left, _altaRect.top);
	_trapImage->Render(_trapRect.left, _trapRect.top);
	_trapNeedleImage->Render(_trapNeedleRect.left, _trapNeedleRect.top);
	_deleteImage->Render(_deleteRect.left, _deleteRect.top);

	_upButton->Render(_upRect.left, _upRect.top);
	_downButton->Render(_downRect.left, _downRect.top);
	_saveButton->Render(_saveRect.left, _saveRect.top);
	_loadButton->Render(_loadRect.left, _loadRect.top);
	_pointImage->Render(_pointRect.left, _pointRect.top);
	
	WCHAR str[10];
	wsprintfW(str, L"%d",_saveLoadNumber);
	_txt->Render(1050, 200, 1100, 250, str);

	for (int i = ENEMY_SLIME_GREEN; i < ENEMY_END; i++)
		_enemyImage[i]->Render(_enemyRect[i].left, _enemyRect[i].top);

	D2DMANAGER->DrawRectangle(_brush, &_mouseState.rc, 2.0f);

	if (_ptMouse.x < 600 && _ptMouse.y < 600)
	{
		int x = _ptMouse.x / TILESIZEX;
		int y = _ptMouse.y / TILESIZEY;

		D2DMANAGER->DrawRectangle(_brush, &RectMake(x*TILESIZEX,y*TILESIZEY,TILESIZEX,TILESIZEY), 2.0f);
	}


	TIMEMANAGER->Render();
	//this->GetBackBuffer()->Render(GetHDC(), 0, 0);

	D2DMANAGER->EndDraw();
}

void Club::Save()
{
	HANDLE file;
	char str[128];
	DWORD  write;
	sprintf_s(str, "%d.map", _saveLoadNumber);

	file = CreateFile(str, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tile, sizeof(_tile), &write, NULL);

	CloseHandle(file);
}

void Club::Load()
{
	HANDLE file;
	char str[128];
	DWORD read;

	sprintf_s(str, "%d.map", _saveLoadNumber);

	file = CreateFile(str, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tile, sizeof(_tile), &read, NULL);
	CloseHandle(file);

}