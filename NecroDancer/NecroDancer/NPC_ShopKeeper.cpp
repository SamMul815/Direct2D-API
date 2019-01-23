#include "stdafx.h"
#include "NPC_ShopKeeper.h"


NPC_ShopKeeper::NPC_ShopKeeper()
{
}


NPC_ShopKeeper::~NPC_ShopKeeper()
{

}
HRESULT NPC_ShopKeeper::Init(int stage)
{
	_image = IMAGEMANAGER->FindImage("ShopKeeper");
	_stage = stage;
	_maxHP = 5;
	_currentHP = 5;
	_atk = 1;
	_atkCheck = FALSE;
	switch (_stage)
	{
	case 1:
		SOUNDMANAGER->Play("Stage1Shop");
	break;
	case 2:
		SOUNDMANAGER->Play("Stage2Shop");
	break;
	case 3:
		SOUNDMANAGER->Play("Stage3Shop");
	break;
	}
	return S_OK;
}
void NPC_ShopKeeper::Update()
{
	switch (_stage)
	{
	case 1:
		SOUNDMANAGER->SetVolume("Stage1Shop", _songPower);
		break;
	case 2:
		SOUNDMANAGER->SetVolume("Stage2Shop", _songPower);
		break;
	case 3:
		SOUNDMANAGER->SetVolume("Stage3Shop", _songPower);
		break;
	}

}
void NPC_ShopKeeper::Render()
{
	_image->FrameRender(_posX, _posY, 0, 0);
	Enemy::UIRender();
}
void NPC_ShopKeeper::Revision()
{
	_posX = _x * TILESIZEX - 12;
	_posY = _y * TILESIZEY - 16;
}
void NPC_ShopKeeper::Move()
{
	int calcX = abs(_player->GetX() - _x);
	int calcY = abs(_player->GetY() - _y);

	_distance = (calcX*calcX) + (calcY * calcY);

	_songPower = sqrt(_distance);
	//_songPower = _songPower / 10;
	_songPower = (8 - _songPower) / 5;

	cout << _songPower << endl;

	if (_songPower < 0)
		_songPower = 0;

}

void NPC_ShopKeeper::DyingMessage()
{
	switch (_stage)
	{
	case 1:
		SOUNDMANAGER->Stop("Stage1Shop");
		break;
	case 2:
		SOUNDMANAGER->Stop("Stage2Shop");
		break;
	case 3:
		SOUNDMANAGER->Stop("Stage3Shop");
		break;
	}

	int item;
	item = RND->GetInt(3);

	_tile[_y * MAPTILEX + _x].objectType = OBJECT_ITEM;
	_tile[_y * MAPTILEX + _x].objectState = ITEM_TORCH_1 + item;

}