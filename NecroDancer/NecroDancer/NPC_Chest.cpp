#include "stdafx.h"
#include "NPC_Chest.h"


NPC_Chest::NPC_Chest()
{
}

NPC_Chest::~NPC_Chest()
{
}

HRESULT NPC_Chest::Init()
{
	_maxHP = 1;
	_currentHP = 1;
	_atk = 0;
	_image = IMAGEMANAGER->FindImage("ChestBase");
	_atkCheck = FALSE;
	return S_OK;
}
void NPC_Chest::Update()
{

}
void NPC_Chest::Render()
{
	_image->FrameRender(_posX, _posY,0,0);
}

void NPC_Chest::Revision()
{
	_posX = _x * TILESIZEX;
	_posY = _y * TILESIZEY - 6;
}

void NPC_Chest::Move()
{

}

void NPC_Chest::DyingMessage()
{
	int count = 0;
	int item = RND->GetInt(ITEM_STATE_END);
	for (int i = 0; i < MAPTILEX; i++)
	{
		for (int j = 0; j < MAPTILEY; j++)
		{
			if (_tile[i * MAPTILEX + j].objectType == OBJECT_ITEM && _tile[i * MAPTILEX + j].objectState == item)
			{
				i = 0;
				count++;
				item = RND->GetInt(ITEM_STATE_END);
				if (count > 10)
					break;
			}
		}
	}
	_tile[_y * MAPTILEX + _x].objectType  = OBJECT_ITEM;
	_tile[_y * MAPTILEX + _x].objectState = item;


	SOUNDMANAGER->Play("ChestOpen");
}