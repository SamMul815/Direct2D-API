#include "stdafx.h"
#include "RenderHelper.h"


RenderHelper::RenderHelper()
{
}

RenderHelper::~RenderHelper()
{

}
HRESULT RenderHelper::Init()
{
	_blockImage = IMAGEMANAGER->FindImage("Block");
	_tileImage =  IMAGEMANAGER->FindImage("Tile");
	_tileStair = IMAGEMANAGER->FindImage("Stair");

	_altarImage[ALTAR_BLOOD] = IMAGEMANAGER->FindImage("BloodAltar");
	_altarImage[ALTAR_DICE] =  IMAGEMANAGER->FindImage("DiceAltar");
	_altarImage[ALTAR_SKULL] = IMAGEMANAGER->FindImage("SkullAltar");
	_altarImage[ALTAR_GLASS] = IMAGEMANAGER->FindImage("GlassAltar");

	_ItemImage[ITEM_HEAD_HELMET]		= IMAGEMANAGER->FindImage("Head_Helmet");
	_ItemImage[ITEM_HEAD_MINERS]		= IMAGEMANAGER->FindImage("Head_Miners");
	_ItemImage[ITEM_HEAD_CROWN]			= IMAGEMANAGER->FindImage("Head_Crown");
	_ItemImage[ITEM_HEAD_BLAST]			= IMAGEMANAGER->FindImage("Head_Blast");
	_ItemImage[ITEM_BODY_1]				= IMAGEMANAGER->FindImage("Body_1");
	_ItemImage[ITEM_BODY_2]				= IMAGEMANAGER->FindImage("Body_2");
	_ItemImage[ITEM_BODY_3]				= IMAGEMANAGER->FindImage("Body_3");
	_ItemImage[ITEM_BODY_4]				= IMAGEMANAGER->FindImage("Body_4");
	_ItemImage[ITEM_BODY_5]				= IMAGEMANAGER->FindImage("Body_5");
	_ItemImage[ITEM_WEAPON_DAGGER_BASE]	= IMAGEMANAGER->FindImage("Weapon_dagger");
	_ItemImage[ITEM_WEAPON_DAGGER_BLOOD]= IMAGEMANAGER->FindImage("Weapon_dagger_blood");
	_ItemImage[ITEM_WEAPON_BROAD_BASE]	= IMAGEMANAGER->FindImage("Weapon_broadsword");
	_ItemImage[ITEM_WEAPON_BROAD_BLOOD]	= IMAGEMANAGER->FindImage("Weapon_broadsword_blood");
	_ItemImage[ITEM_WEAPON_LONG_BASE]	= IMAGEMANAGER->FindImage("Weapon_longsword");
	_ItemImage[ITEM_WEAPON_LONG_BLOOD]	= IMAGEMANAGER->FindImage("Weapon_longsword_blood");
	_ItemImage[ITEM_SHOVEL_BASE]		= IMAGEMANAGER->FindImage("Shovel_Base");
	_ItemImage[ITEM_SHOVEL_BLOOD]		= IMAGEMANAGER->FindImage("Shovel_Blood");
	_ItemImage[ITEM_SHOVEL_CRYSTAL]		= IMAGEMANAGER->FindImage("Shovel_Crystal");
	_ItemImage[ITEM_SHOVEL_TITANIUM]	= IMAGEMANAGER->FindImage("Shovel_titanium");
	_ItemImage[ITEM_TORCH_1]			= IMAGEMANAGER->FindImage("Torch_1");
	_ItemImage[ITEM_TORCH_2]			= IMAGEMANAGER->FindImage("Torch_2");
	_ItemImage[ITEM_TORCH_3]			= IMAGEMANAGER->FindImage("Torch_3");
	//_ItemImage[ITEM_POTION_APPLE]		= IMAGEMANAGER->FindImage("");
	//_ItemImage[ITEM_POTION_CHEESE]	= IMAGEMANAGER->FindImage("");
	//_ItemImage[ITEM_POTION_CHICKEN]	= IMAGEMANAGER->FindImage("");
	//_ItemImage[ITEM_POTION_MEAT]		= IMAGEMANAGER->FindImage("");
	//_ItemImage[ITEM_SPELL_BOMB]		= IMAGEMANAGER->FindImage("");
	//_ItemImage[ITEM_SPELL_FIREBALL]	= IMAGEMANAGER->FindImage("");
	//_ItemImage[ITEM_SPELL_HEAL]		= IMAGEMANAGER->FindImage("");
	//_ItemImage[ITEM_SPELL_SHIELD]		= IMAGEMANAGER->FindImage("");

	_trapMoveImage   = IMAGEMANAGER->FindImage("MoveTrap");
	_trapBombImage   = IMAGEMANAGER->FindImage("BombTrap");
	_trapNeedleImage = IMAGEMANAGER->FindImage("NeedleTrap");
	_trapTeleportImage = IMAGEMANAGER->FindImage("TeleportTrap");
	
	return S_OK;
}

void RenderHelper::Render()
{
	//D2DMANAGER->GetD2DRenderTarget()->SetTransform(D2D1::Matrix3x2F::Matrix3x2F(1, 0, 0, 1, 0, 0));
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(D2D1::Matrix3x2F::Matrix3x2F(3, 0, 0, 3, 0, 0));
	for (int x = 0; x < MAPTILEX; x++)	//타일
	{
		for (int y = 0; y < MAPTILEY; y++)
		{
			if(_enemyManager->GetBeatCheck())
				_tileImage->FrameRender(x*TILESIZEX, y*TILESIZEY, _tile[y* MAPTILEX + x].tileType==0);
			else
				_tileImage->FrameRender(x*TILESIZEX, y*TILESIZEY, _tile[y* MAPTILEX + x].tileType==1);
		}
	}

	for (int y = 0; y < MAPTILEY; y++)
	{
		for (int x = 0; x < MAPTILEX; x++)
		{
			int posX = x*TILESIZEX;
			int posY = y*TILESIZEY;
			int revisionX;
			int revisionY;

			switch (_tile[y* MAPTILEX + x].objectType)
			{
			case OBJECT_NONE:

			break;
			case OBJECT_BLOCK:		
				revisionX = 0;
				revisionY = _blockImage->GetFrameHeight() - TILESIZEY - 8;
				_blockImage->FrameRender(posX + revisionX, posY - revisionY, _tile[y*MAPTILEX + x].objectKind);
				//_blockImage->FrameRender(i * TILESIZEX - 1, j * TILESIZEY - (_blockImage->GetFrameHeight() - TILESIZEY) + 8, _tile[i][j].objectState, 0);
			break;
			case OBJECT_TRAP:	
				switch (_tile[y*MAPTILEX + x].objectKind)
				{
				case TRAP_MOVEUP:
					revisionX = 5;
					revisionY = 3;
					_trapMoveImage->FrameRender(posX + revisionX, posY + revisionY,_tile[y*MAPTILEX+x].objectState,0);
				break;
				case TRAP_MOVERIGHT:
					revisionX = 5;
					revisionY = 3;
					_trapMoveImage->FlipFrameRender(posX + revisionX, posY + revisionY, _tile[y*MAPTILEX + x].objectState,1);
				break;
				case TRAP_MOVEDOWN:
					revisionX = 5;
					revisionY = 3;
					_trapMoveImage->FrameRender(posX + revisionX, posY + revisionY, _tile[y*MAPTILEX + x].objectState,2);
				break;
				case TRAP_MOVELEFT:
					revisionX = 5;
					revisionY = 3;
					_trapMoveImage->FrameRender(posX + revisionX, posY + revisionY, _tile[y*MAPTILEX + x].objectState,1);
				break;
				case TRAP_BOOM:
					revisionX = 5;
					revisionY = 3;
					_trapBombImage->FrameRender(posX + revisionX, posY + revisionY, _tile[y*MAPTILEX + x].objectState);
				break;
				case TRAP_TELEPORT:
					revisionX = 5;
					revisionY = 3;
					_trapTeleportImage->FrameRender(posX + revisionX, posY + revisionY, _tile[y*MAPTILEX + x].objectState);
				break;
				case TRAP_NEEDLE:
					revisionX = 3;
					revisionY = 0;
					_trapNeedleImage->FrameRender(posX - revisionX, posY + revisionY, _tile[y*MAPTILEX + x].objectState);
				break;

				}
			break;
			case OBJECT_ITEM:
			
				revisionX = 0;
				revisionY = 6;
				_ItemImage[_tile[y*MAPTILEX + x].objectState]->FrameRender(posX + revisionX, posY - revisionY, 0, 0);
			
			break;
			case OBJECT_ALTAR:	
				switch (_tile[y*MAPTILEX + x].objectKind)
				{
				case ALTAR_BLOOD:
					revisionX = 3;
					revisionY = _altarImage[ALTAR_BLOOD]->GetFrameHeight() - TILESIZEY;
					_altarImage[ALTAR_BLOOD]->FrameRender(posX-revisionX,posY-revisionY, _tile[y*MAPTILEX + x].objectState,1.0f);
				break;
				case ALTAR_DICE:
					revisionX = 5;
					revisionY = _altarImage[ALTAR_DICE]->GetFrameHeight() - TILESIZEY;
					_altarImage[ALTAR_DICE]->FrameRender(posX-revisionX, posY - revisionY, _tile[y*MAPTILEX + x].objectState,1.0f);
				break;
				case ALTAR_SKULL:
					revisionX = 5;
					revisionY = _altarImage[ALTAR_SKULL]->GetFrameHeight() - TILESIZEY;
					_altarImage[ALTAR_SKULL]->FrameRender(posX-revisionX, posY - revisionY, _tile[y*MAPTILEX + x].objectState,1.0f);
				break;
				case ALTAR_GLASS:
					revisionX = 5;
					revisionY = _altarImage[ALTAR_GLASS]->GetFrameHeight() - TILESIZEY;
					_altarImage[ALTAR_GLASS]->FrameRender(posX - revisionX, posY - revisionY, _tile[y*MAPTILEX + x].objectState,1.0f);
				break;
				default:
				
				break;
				}
			break;
			case OBJECT_POINT:		
				_tileStair->FrameRender(posX, posY, _enemyManager->GetStageClear());
			break;
			}
			if(_tile[y*MAPTILEX + x].isEnemyUP)
			_enemyManager->Render(x, y);
			if (_player->GetX() == x && _player->GetY() == y)
			{
				_player->Render();
				_player->PlayerEffectRender();
			}
		}


	}	  //블럭 및 오브젝트들

	_player->SightRender();

	//for (int x = 0; x < MAPTILEX; x++)	//타일
	//{
	//	for (int y = 0; y < MAPTILEY; y++)
	//	{
	//		WCHAR str[128];
	//		wsprintfW(str, L"%d,%d", _tile[y* MAPTILEX + x].isEnemyUP, _tile[y* MAPTILEX + x].objectType);
	//		_text->Render(x*TILESIZEX, y*TILESIZEY, x*TILESIZEX + 24, y*TILESIZEY + 24, str);
	//		
	//	}
	//}

	D2DMANAGER->GetD2DRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
}