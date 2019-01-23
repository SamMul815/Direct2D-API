#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

HRESULT Player::Init()
{
	_move = new MoveHelper<Player>;
	_move->LinkObject(this);
	_move->Init();
	_keyStack = 0;
	_keycheck = 0;

	_sight = new Sight;
	_sight->LinkPlayer(this);
	_sight->LinkTile(_tile);


	//플레이어 장비 초기화
	_playerInven.body = BODY_NONE;
	_playerInven.bomb = 1;
	_playerInven.head = HEAD_NONE;
	_playerInven.shovel = SHOVEL_BASE;
	_playerInven.spell1 = SPELL_NONE;
	_playerInven.spell2 = SPELL_NONE;
	_playerInven.torch = TORCH_NONE;
	_playerInven.weapon = WEAPON_DAGGER_BASE;

	//플레이어 스텟 초기화
	_playerStat.atk = 1;			//공격력
	_playerStat.def = 0;			//방어력
	_playerStat.shv = 1;			//삽질력
	_playerStat.maxHP = 10;	
	_playerStat.currentHP = 10;

	int headAni[8] = { 0,1,2,3,4,5,6,7 };
	int bodyAni[8] = { 0,1,2,3,0,1,2,3 };

	_playerHeadAni = new Animation;
	_playerHeadAni->Init(96, 48, 24, 24);
	_playerHeadAni->SetPlayFrame(headAni, 8,TRUE);

	_playerBodyAni = new Animation;
	_playerBodyAni->Init(96, 240, 24, 24);
	_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);

	_playerHeadAni->SetFPS(10);
	_playerBodyAni->SetFPS(10);

	_playerHeadAni->Start();
	_playerBodyAni->Start();

	_isLeft = FALSE;
	_attackCheck = 0;
	_attackEffect = FALSE;
	_digEffect = FALSE;
	_upStair = FALSE;
	_fireEffect = FALSE;
	_killStack = 10;
	_EffectFrameCount = 0;
	_digEffectFrame = 0;
	_fireEffectFrame = 0;
	_stage = 0;
	_live = TRUE;
	return S_OK;
}

void Player::ImageInput()
{
	_head = IMAGEMANAGER->FindImage("PlayerHead");
	_body = IMAGEMANAGER->FindImage("PlayerBody");

	_effectImage1[0] = IMAGEMANAGER->FindImage("Effect_dagger1");
	_effectImage1[1] = IMAGEMANAGER->FindImage("Effect_dagger_blood1");
	_effectImage1[2] = IMAGEMANAGER->FindImage("Effect_broadsword1");
	_effectImage1[3] = IMAGEMANAGER->FindImage("Effect_broadsword_blood1");
	_effectImage1[4] = IMAGEMANAGER->FindImage("Effect_longsword1");
	_effectImage1[5] = IMAGEMANAGER->FindImage("Effect_longsword_blood1");

	_effectImage2[0] = IMAGEMANAGER->FindImage("Effect_dagger2");
	_effectImage2[1] = IMAGEMANAGER->FindImage("Effect_dagger_blood2");
	_effectImage2[2] = IMAGEMANAGER->FindImage("Effect_broadsword2");
	_effectImage2[3] = IMAGEMANAGER->FindImage("Effect_broadsword_blood2");
	_effectImage2[4] = IMAGEMANAGER->FindImage("Effect_longsword2");
	_effectImage2[5] = IMAGEMANAGER->FindImage("Effect_longsword_blood2");

	_sight->Init();
}

void Player::Render()
{
	if (_isLeft)
	{
		_body->FlipAniRender(_posX, _posY, _playerBodyAni);
		_head->FlipAniRender(_posX, _posY, _playerHeadAni);
	}
	else
	{
		_body->AniRender(_posX, _posY, _playerBodyAni);
		_head->AniRender(_posX, _posY, _playerHeadAni);
	}
}

void Player::UIRender()
{
	//char str[10];

	D2DMANAGER->GetD2DRenderTarget()->SetTransform(D2D1::Matrix3x2F::Matrix3x2F(3, 0, 0, 3, 0, 0));
	
	//삽 이미지
	switch (_playerInven.shovel)
	{
	case SHOVEL_BASE:
		IMAGEMANAGER->FindImage("Shovel_Base")->UIFrameRender(10,10,0,0);
	break;
	case SHOVEL_BLOOD:
		IMAGEMANAGER->FindImage("Shovel_Blood")->UIFrameRender(10, 10, 0, 0);
	break;
	case SHOVEL_CRYSTAL:
		IMAGEMANAGER->FindImage("Shovel_Crystal")->UIFrameRender(10, 10, 0, 0);
	break;
	case SHOVEL_TITANIUM:
		IMAGEMANAGER->FindImage("Shovel_titanium")->UIFrameRender(10, 10, 0, 0);
	break;
	default:
	break;
	}

	IMAGEMANAGER->FindImage("Slot_Shovel")->UIRender(5, 5);

	switch (_playerInven.weapon)
	{
	case WEAPON_NONE:
		break;
	case WEAPON_DAGGER_BASE:
		IMAGEMANAGER->FindImage("Weapon_dagger")->UIFrameRender(10, 45,0,0);
		break;
	case WEAPON_DAGGER_BLOOD:
		IMAGEMANAGER->FindImage("Weapon_dagger_blood")->UIFrameRender(10, 45,0,0);
		break;
	case WEAPON_BROAD_BASE:
		IMAGEMANAGER->FindImage("Weapon_broadsword")->UIFrameRender(10, 45,0,0);
		break;
	case WEAPON_BROAD_BLOOD:
		IMAGEMANAGER->FindImage("Weapon_broadsword_blood")->UIFrameRender(10, 45,0,0);
		break;
	case WEAPON_LONG_BASE:
		IMAGEMANAGER->FindImage("Weapon_longsword")->UIFrameRender(10, 45,0,0);
		break;
	case WEAPON_LONG_BLOOD:
		IMAGEMANAGER->FindImage("Weapon_longsword_blood")->UIFrameRender(10, 45,0,0);
		break;
	}
	IMAGEMANAGER->FindImage("Slot_Weapon")->UIRender(5, 40);

	switch (_playerInven.body)
	{
	case BODY_NONE:
		break;
	case BODY_1:
		IMAGEMANAGER->FindImage("Body_1")->UIFrameRender(45, 10, 0, 0);
		break;
	case BODY_2:
		IMAGEMANAGER->FindImage("Body_2")->UIFrameRender(45, 10, 0, 0);
		break;
	case BODY_3:
		IMAGEMANAGER->FindImage("Body_3")->UIFrameRender(45, 10, 0, 0);
		break;
	case BODY_4:
		IMAGEMANAGER->FindImage("Body_4")->UIFrameRender(45, 10, 0, 0);
		break;
	case BODY_5:
		IMAGEMANAGER->FindImage("Body_5")->UIFrameRender(45, 10, 0, 0);
		break;
	default:
		break;
	}
	IMAGEMANAGER->FindImage("Slot_Body")->UIRender(40, 5);

	switch (_playerInven.head)
	{
	case HEAD_NONE:
		break;
	case HEAD_HELMET:
		IMAGEMANAGER->FindImage("Head_Helmet")->UIFrameRender(80, 10, 0, 0);
		break;
	case HEAD_MINERS:
		IMAGEMANAGER->FindImage("Head_Miners")->UIFrameRender(80, 10, 0, 0);
		break;
	case HEAD_CROWN:
		IMAGEMANAGER->FindImage("Head_Crown")->UIFrameRender(80, 10, 0, 0);
		break;
	case HEAD_BLAST:
		IMAGEMANAGER->FindImage("Head_Blast")->UIFrameRender(80, 10, 0, 0);
		break;

	}
	IMAGEMANAGER->FindImage("Slot_Head")->UIRender(75, 5);

	switch (_playerInven.torch)
	{
	case TORCH_NONE:
		break;
	case TORCH_1:
		IMAGEMANAGER->FindImage("Torch_1")->UIFrameRender(10, 80,0,0);
		break;
	case TORCH_2:
		IMAGEMANAGER->FindImage("Torch_2")->UIFrameRender(10, 80,0,0);
		break;
	case TORCH_3:
		IMAGEMANAGER->FindImage("Torch_3")->UIFrameRender(10, 80,0,0);
		break;
	}
	IMAGEMANAGER->FindImage("Slot_Torch")->UIRender(5, 75);

	IMAGEMANAGER->FindImage("Spell_Fire")->UIFrameRender(365, 35,0,0);
	IMAGEMANAGER->FindImage("Slot_Spell1")->UIRender(360, 30);
	
	IMAGEMANAGER->FindImage("Spell_Heal")->UIFrameRender(365, 75,0,0);
	IMAGEMANAGER->FindImage("Slot_Spell2")->UIRender(360, 70);

	if (_playerInven.head == HEAD_CROWN)
	{
		if (_killStack < 5)
		{
			//_text->Render(672, 8, 100, 100, L"10Kill");
			//_text->Render(672, 48, 100, 100, L"10Kill");
			IMAGEMANAGER->FindImage("5Kill")->UIRender(365, 52);
			IMAGEMANAGER->FindImage("5Kill")->UIRender(365, 92);
		}
	}
	else
	{
		if (_killStack < 10)
		{
			//_text->Render(672, 8, 100, 100, L"10Kill");
			//_text->Render(672, 48, 100, 100, L"10Kill");
			IMAGEMANAGER->FindImage("10Kill")->UIRender(365, 52);
			IMAGEMANAGER->FindImage("10Kill")->UIRender(365, 92);
		}
	}



	D2DMANAGER->GetD2DRenderTarget()->SetTransform(D2D1::Matrix3x2F::Matrix3x2F(2, 0, 0, 2, 0, 0));

	int hp;
	hp = _playerStat.currentHP;
	for (int i = 0; i < _playerStat.maxHP; i += 2)
	{
		if (hp > 0 && hp != 1)
		{
			IMAGEMANAGER->FindImage("Heart_Full")->UIRender(400 + i * 20, 5);
			hp = hp - 2;
		}
		else if (hp == 1)
		{
			IMAGEMANAGER->FindImage("Heart_Half")->UIRender(400 + i * 20, 5);
			hp = hp - 2;
		}
		else
		{
			IMAGEMANAGER->FindImage("Heart_Empty")->UIRender(400 + i * 20, 5);
		}
	}
	D2DMANAGER->GetD2DRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Player::Update()
{
	_playerHeadAni->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	_playerBodyAni->FrameUpdate(TIMEMANAGER->GetElapsedTime());

	int keyState;
	keyState = KeyCheck();

	if (keyState != 0)
	{
		_keyStack += keyState;
		_keycheck = 0;
	}
	
	if (keyState == 0)
		_keycheck++;

	if (_keycheck > 2 && _keyStack != 0)
	{
		if (_beat->NoteCheckPlayer())
		{
			bool attackCheck;
			switch (_keyStack)
			{
			case 1:				//UP
				cout << "UP" << endl;
				attackCheck = AttackCheck(UP);
				if (_tile[(_y-1) * MAPTILEX + _x].objectType == OBJECT_NONE &&		//아무런 오브젝트도 없는상황
					_tile[(_y-1) * MAPTILEX + _x].isEnemyUP == FALSE &&
					attackCheck == FALSE)
				{
					_tile[_y * MAPTILEX + _x].isPlayerUP = FALSE;
					_move->MoveUp();
					_tile[_y * MAPTILEX + _x].isPlayerUP = TRUE;
				}
				else if (_tile[(_y - 1) * MAPTILEX + _x].objectType == OBJECT_BLOCK)
				{
					BlockCheck((_y - 1) * MAPTILEX + _x);
					_digEffect = TRUE;
					_EffectArrow = UP;
				}
				else if (_tile[(_y - 1) * MAPTILEX + _x].objectType == OBJECT_TRAP)		//함정 있어여~
				{
					_move->MoveUp();
					TrapCheck();
				}
				else if (attackCheck == TRUE)
				{
					Attack(UP);
					_attackEffect = TRUE;
					_EffectArrow = UP;
				}
				else if (_tile[(_y - 1) * MAPTILEX + _x].objectType == OBJECT_ITEM)		//함정 있어여~
				{
					ItemCheck(_x, _y - 1);
					_move->MoveUp();
				}
				else if (_tile[(_y - 1) * MAPTILEX + _x].objectType == OBJECT_POINT)		//함정 있어여~
				{
					if (_enemyManager->GetStageClear())
						_upStair = TRUE;
					_move->MoveUp();
				}

				break;
			case 2:				//DOWN
				cout << "DOWN" << endl;
				attackCheck = AttackCheck(DOWN);
				if (_tile[(_y+1) * MAPTILEX + _x].objectType == OBJECT_NONE &&
					_tile[(_y+1) * MAPTILEX + _x].isEnemyUP == FALSE&&
					attackCheck == FALSE)
				{
					_tile[_y * MAPTILEX + _x].isPlayerUP = FALSE;
					_move->MoveDown();
					_tile[_y * MAPTILEX + _x].isPlayerUP = TRUE;
				}
				else if (_tile[(_y + 1) * MAPTILEX + _x].objectType == OBJECT_BLOCK)
				{
					BlockCheck((_y + 1) * MAPTILEX + _x);
					_digEffect = TRUE;
					_EffectArrow = DOWN;
				}
				else if(_tile[(_y + 1) * MAPTILEX + _x].objectType == OBJECT_TRAP)
				{
					_move->MoveDown();
					TrapCheck();
				}
				else if (attackCheck == TRUE)
				{
					Attack(DOWN);
					_attackEffect = TRUE;
					_EffectArrow = DOWN;
				}
				else if (_tile[(_y + 1) * MAPTILEX + _x].objectType == OBJECT_ITEM)
				{
					ItemCheck(_x,_y+1);
					_move->MoveDown();
					
				}
				else if (_tile[(_y + 1) * MAPTILEX + _x].objectType == OBJECT_POINT)		//함정 있어여~
				{
					if (_enemyManager->GetStageClear())
						_upStair = TRUE;
					_move->MoveDown();
				}

				break;
			case 3:				//UP && DOWN
				cout << "UP DOWN" << endl;
				break;
			case 4:				//LEFT
				cout << "LEFT" << endl;
				attackCheck = AttackCheck(LEFT);
				_isLeft = TRUE;
				if (_tile[_y * MAPTILEX + _x-1].objectType == OBJECT_NONE &&
					_tile[_y * MAPTILEX + _x-1].isEnemyUP == FALSE&&
					attackCheck == FALSE)
				{
					_tile[_y * MAPTILEX + _x].isPlayerUP = FALSE;
					_move->MoveLeft();
					_tile[_y * MAPTILEX + _x].isPlayerUP = TRUE;
				}
				else if (_tile[(_y) * MAPTILEX + _x-1].objectType == OBJECT_BLOCK)
				{
					BlockCheck((_y)* MAPTILEX + _x - 1);
					_digEffect = TRUE;
					_EffectArrow = LEFT;
				}
				else if (_tile[(_y)* MAPTILEX + _x - 1].objectType == OBJECT_TRAP)
				{
					_move->MoveLeft();
					TrapCheck();
				}
				else if (attackCheck == TRUE)
				{
					Attack(LEFT);
					_attackEffect = TRUE;
					_EffectArrow = LEFT;
				}
				else if (_tile[(_y)* MAPTILEX + _x - 1].objectType == OBJECT_ITEM)
				{
					ItemCheck(_x - 1, _y);
					_move->MoveLeft();
				}
				else if (_tile[(_y)* MAPTILEX + _x - 1].objectType == OBJECT_POINT)
				{
					if (_enemyManager->GetStageClear())
						_upStair = TRUE;

					_move->MoveLeft();
				}


				break;
			case 5:				//LEFT && UP
				cout << "LEFT UP" << endl;
				break;
			case 6:				//LEFT && DOWN
				cout << "LEFT DOWN" << endl;
				SpellFire();
				break;
			case 8:				//RIGHT
				cout << "RIGHT" << endl;
				attackCheck = AttackCheck(RIGHT);
				_isLeft = FALSE;
				if (_tile[_y * MAPTILEX + _x+1].objectType == OBJECT_NONE &&
					_tile[_y * MAPTILEX + _x+1].isEnemyUP == FALSE &&
					attackCheck == FALSE)
				{
					_tile[_y * MAPTILEX + _x].isPlayerUP = FALSE;
					_move->MoveRight();
					_tile[_y * MAPTILEX + _x].isPlayerUP = TRUE;
				}
				else if (_tile[(_y)* MAPTILEX + _x + 1].objectType == OBJECT_BLOCK)
				{
					BlockCheck((_y)* MAPTILEX + _x + 1);
					_digEffect = TRUE;
					_EffectArrow = RIGHT;
				}
				else if(_tile[_y * MAPTILEX + _x + 1].objectType == OBJECT_TRAP)
				{
					_move->MoveRight();
					TrapCheck();
				}
				else if (attackCheck == TRUE)
				{
					Attack(RIGHT);
					_attackEffect = TRUE;
					_EffectArrow = RIGHT;
				}
				else if (_tile[_y * MAPTILEX + _x + 1].objectType == OBJECT_ITEM)
				{
					ItemCheck(_x+1,_y);
					_move->MoveRight();
				}
				else if (_tile[_y * MAPTILEX + _x + 1].objectType == OBJECT_POINT)
				{
					if (_enemyManager->GetStageClear())
						_upStair = TRUE;
					_move->MoveRight();
				}


				break;
			case 9:				//RIGHT && UP
				cout << "RIGHT UP" << endl;
				break;
			case 10:			//RIGHT && DOWN
				cout << "RIGHT DOWN" << endl;
					SpellHeal();				//힐
				break;
			case 12:			//RIGHT && LEFT
				cout << "RIGHT LEFT" << endl;
				break;
			default:			//잘못 입력 또는 입력없음
								//	cout << "DEFAULT" << endl;
				break;
			}
		}
		_keyStack = 0;
		_keycheck = 0;

	}
	_move->Update();
}

void Player::Release()
{

}

void Player::Revision()
{
	_posX = _x * TILESIZEX;
	_posY = _y * TILESIZEY-6;

		if(_upStair == TRUE)
		{
			_upStair = FALSE;
			switch (_stage)
			{
			case 0:
				SCENEMANAGER->ChangeScene("Stage2");
			break;
			case 1:
				SCENEMANAGER->ChangeScene("Stage3");
			break;
			case 2:
				SCENEMANAGER->ChangeScene("Clear");
			break;
			}

			_stage++;
		}

}

int Player:: KeyCheck()
{
	_keyBit.reset();
	if (KEYMANAGER->IsOnceKeyDown(VK_UP))    _keyBit[UP]    = 1;		//1
	if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))  _keyBit[DOWN]  = 1;		//2
	if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))  _keyBit[LEFT]  = 1;		//4
	if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT)) _keyBit[RIGHT] = 1;		//8

	return _keyBit.to_ulong();

}

void Player::TrapCheck()
{
	switch (_tile[(_y)* MAPTILEX + _x].objectKind)
	{
	case TRAP_MOVEUP:
		_tile[_y * MAPTILEX + _x].isPlayerUP = FALSE;
		_move->MoveUp();
		_tile[_y * MAPTILEX + _x].isPlayerUP = TRUE;
		break;
	case TRAP_MOVERIGHT:
		_tile[_y * MAPTILEX + _x].isPlayerUP = FALSE;
		_move->MoveRight();
		_tile[_y * MAPTILEX + _x].isPlayerUP = TRUE;
		break;
	case TRAP_MOVEDOWN:
		_tile[_y * MAPTILEX + _x].isPlayerUP = FALSE;
		_move->MoveDown();
		_tile[_y * MAPTILEX + _x].isPlayerUP = TRUE;
		break;
	case TRAP_MOVELEFT:
		_tile[_y * MAPTILEX + _x].isPlayerUP = FALSE;
		_move->MoveLeft();
		_tile[_y * MAPTILEX + _x].isPlayerUP = TRUE;
		break;
	case TRAP_BOOM:
		break;
	case TRAP_TELEPORT:
		break;
	case TRAP_NEEDLE:
		Hit(1);
		break;
	default:
		break;
	}

}

void Player::ItemCheck(int x, int y)
{
	switch (_tile[y * MAPTILEX + x].objectState)
	{
	case ITEM_HEAD_HELMET:
		switch (_playerInven.head)
		{
		case HEAD_NONE:
			_playerInven.head = HEAD_HELMET;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case HEAD_HELMET:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_HELMET;
			_playerInven.head = HEAD_HELMET;
			break;
		case HEAD_MINERS:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_MINERS;
			_playerInven.head = HEAD_HELMET;
			break;
		case HEAD_CROWN:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_CROWN;
			_playerInven.head = HEAD_HELMET;
			break;
		case HEAD_BLAST:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_BLAST;
			_playerInven.head = HEAD_HELMET;
			break;
		}
		break;
	case ITEM_HEAD_MINERS:
		switch (_playerInven.head)
		{
		case HEAD_NONE:
			_playerInven.head = HEAD_MINERS;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case HEAD_HELMET:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_HELMET;
			_playerInven.head = HEAD_MINERS;
			break;
		case HEAD_MINERS:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_MINERS;
			_playerInven.head = HEAD_MINERS;
			break;
		case HEAD_CROWN:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_CROWN;
			_playerInven.head = HEAD_MINERS;
			break;
		case HEAD_BLAST:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_BLAST;
			_playerInven.head = HEAD_MINERS;
			break;
		}
		break;
	case ITEM_HEAD_CROWN:
		switch (_playerInven.head)
		{
		case HEAD_NONE:
			_playerInven.head = HEAD_CROWN;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case HEAD_HELMET:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_HELMET;
			_playerInven.head = HEAD_CROWN;
			break;
		case HEAD_MINERS:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_MINERS;
			_playerInven.head = HEAD_CROWN;
			break;
		case HEAD_CROWN:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_CROWN;
			_playerInven.head = HEAD_CROWN;
			break;
		case HEAD_BLAST:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_BLAST;
			_playerInven.head = HEAD_CROWN;
			break;
		}
		break;
	case ITEM_HEAD_BLAST:
		switch (_playerInven.head)
		{
		case HEAD_NONE:
			_playerInven.head = HEAD_BLAST;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case HEAD_HELMET:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_HELMET;
			_playerInven.head = HEAD_BLAST;
			break;
		case HEAD_MINERS:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_MINERS;
			_playerInven.head = HEAD_BLAST;
			break;
		case HEAD_CROWN:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_CROWN;
			_playerInven.head = HEAD_BLAST;
			break;
		case HEAD_BLAST:
			_tile[y * MAPTILEX + x].objectState = ITEM_HEAD_BLAST;
			_playerInven.head = HEAD_BLAST;
			break;
		}
		break;
	case ITEM_BODY_1:
		switch (_playerInven.body)
		{
		case BODY_NONE:											
		{
			_playerInven.body = BODY_1;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;

			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 4,5,6,7,4,5,6,7 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_1:
		{
			_playerInven.body = BODY_1;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_1;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 4,5,6,7,4,5,6,7 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_2:
		{
			_playerInven.body = BODY_1;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_2;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 4,5,6,7,4,5,6,7 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_3:
		{
			_playerInven.body = BODY_1;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_3;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 4,5,6,7,4,5,6,7 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_4:
		{
			_playerInven.body = BODY_1;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_4;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 4,5,6,7,4,5,6,7 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_5:
		{
			_playerInven.body = BODY_1;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_5;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 4,5,6,7,4,5,6,7 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		default:
			break;
		}
		break;
	case ITEM_BODY_2:
		switch (_playerInven.body)
		{
		case BODY_NONE:
		{
			_playerInven.body = BODY_2;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 8,9,10, 11,8,9,10,11 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_1:
		{
			_playerInven.body = BODY_2;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_1;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 8,9,10, 11,8,9,10,11 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_2:
		{
			_playerInven.body = BODY_2;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_2;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 8,9,10, 11,8,9,10,11 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_3:
		{
			_playerInven.body = BODY_2;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_3;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 8,9,10, 11,8,9,10,11 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_4:
		{
			_playerInven.body = BODY_2;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_4;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 8,9,10, 11,8,9,10,11 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_5:
		{
			_playerInven.body = BODY_2;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_5;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 8,9,10, 11,8,9,10,11 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		default:
			break;
		}
		break;
	case ITEM_BODY_3:
		switch (_playerInven.body)
		{
		case BODY_NONE:
		{
			_playerInven.body = BODY_3;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 12,13,14, 15,12,13,14,15 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_1:
		{
			_playerInven.body = BODY_3;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_1;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 12,13,14, 15,12,13,14,15 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_2:
		{
			_playerInven.body = BODY_3;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_2;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 12,13,14, 15,12,13,14,15 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_3:
		{
			_playerInven.body = BODY_3;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_3;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 12,13,14, 15,12,13,14,15 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_4:
		{
			_playerInven.body = BODY_3;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_4;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 12,13,14, 15,12,13,14,15 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_5:
		{
			_playerInven.body = BODY_3;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_5;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 12,13,14, 15,12,13,14,15 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		default:
			break;
		}
		break;
	case ITEM_BODY_4:
		switch (_playerInven.body)
		{
		case BODY_NONE:
		{
			_playerInven.body = BODY_4;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 16,17,18, 19,16,17,18,19 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_1:
		{
			_playerInven.body = BODY_4;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_1;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 16,17,18, 19,16,17,18,19 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_2:
		{
			_playerInven.body = BODY_4;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_2;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 16,17,18, 19,16,17,18,19 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_3:
		{
			_playerInven.body = BODY_4;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_3;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 16,17,18, 19,16,17,18,19 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_4:
		{
			_playerInven.body = BODY_4;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_4;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 16,17,18, 19,16,17,18,19 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_5:
		{
			_playerInven.body = BODY_4;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_5;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 16,17,18, 19,16,17,18,19 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		default:
			break;
		}
		break;
	case ITEM_BODY_5:
		switch (_playerInven.body)
		{
		case BODY_NONE:
		{
			_playerInven.body = BODY_5;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 20,21,22, 23,20,21,22,23 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_1:
		{
			_playerInven.body = BODY_5;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_1;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 20,21,22, 23,20,21,22,23 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_2:
		{
			_playerInven.body = BODY_5;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_2;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 20,21,22, 23,20,21,22,23 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_3:
		{
			_playerInven.body = BODY_5;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_3;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 20,21,22, 23,20,21,22,23 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_4:
		{
			_playerInven.body = BODY_5;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_4;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 20,21,22, 23,20,21,22,23 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		case BODY_5:
		{
			_playerInven.body = BODY_5;
			_tile[y * MAPTILEX + x].objectState = ITEM_BODY_5;
			int headAni[8] = { 0,1,2,3,4,5,6,7 };
			int bodyAni[8] = { 20,21,22, 23,20,21,22,23 };
			_playerHeadAni->SetPlayFrame(headAni, 8, TRUE);
			_playerBodyAni->SetPlayFrame(bodyAni, 8, TRUE);
		}
			break;
		default:
			break;
		}
		break;
	case ITEM_WEAPON_DAGGER_BASE:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			_playerInven.weapon = WEAPON_DAGGER_BASE;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case WEAPON_DAGGER_BASE:
			_playerInven.weapon = WEAPON_DAGGER_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BASE;
			break;
		case WEAPON_DAGGER_BLOOD:
			_playerInven.weapon = WEAPON_DAGGER_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BLOOD;
			break;
		case WEAPON_BROAD_BASE:
			_playerInven.weapon = WEAPON_DAGGER_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BASE;
			break;
		case WEAPON_BROAD_BLOOD:
			_playerInven.weapon = WEAPON_DAGGER_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BLOOD;
			break;
		case WEAPON_LONG_BASE:
			_playerInven.weapon = WEAPON_DAGGER_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BASE;
			break;
		case WEAPON_LONG_BLOOD:
			_playerInven.weapon = WEAPON_DAGGER_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BLOOD;
			break;
		}
		break;
	case ITEM_WEAPON_DAGGER_BLOOD:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			_playerInven.weapon = WEAPON_DAGGER_BLOOD;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case WEAPON_DAGGER_BASE:
			_playerInven.weapon = WEAPON_DAGGER_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BASE;
			break;
		case WEAPON_DAGGER_BLOOD:
			_playerInven.weapon = WEAPON_DAGGER_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BLOOD;
			break;
		case WEAPON_BROAD_BASE:
			_playerInven.weapon = WEAPON_DAGGER_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BASE;
			break;
		case WEAPON_BROAD_BLOOD:
			_playerInven.weapon = WEAPON_DAGGER_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BLOOD;
			break;
		case WEAPON_LONG_BASE:
			_playerInven.weapon = WEAPON_DAGGER_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BASE;
			break;
		case WEAPON_LONG_BLOOD:
			_playerInven.weapon = WEAPON_DAGGER_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BLOOD;
			break;
		}
		break;
	case ITEM_WEAPON_BROAD_BASE:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			_playerInven.weapon = WEAPON_BROAD_BASE;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case WEAPON_DAGGER_BASE:
			_playerInven.weapon = WEAPON_BROAD_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BASE;
			break;
		case WEAPON_DAGGER_BLOOD:
			_playerInven.weapon = WEAPON_BROAD_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BLOOD;
			break;
		case WEAPON_BROAD_BASE:
			_playerInven.weapon = WEAPON_BROAD_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BASE;
			break;
		case WEAPON_BROAD_BLOOD:
			_playerInven.weapon = WEAPON_BROAD_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BLOOD;
			break;
		case WEAPON_LONG_BASE:
			_playerInven.weapon = WEAPON_BROAD_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BASE;
			break;
		case WEAPON_LONG_BLOOD:
			_playerInven.weapon = WEAPON_BROAD_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BLOOD;
			break;
		}
		break;
	case ITEM_WEAPON_BROAD_BLOOD:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			_playerInven.weapon = WEAPON_BROAD_BLOOD;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case WEAPON_DAGGER_BASE:
			_playerInven.weapon = WEAPON_BROAD_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BASE;
			break;
		case WEAPON_DAGGER_BLOOD:
			_playerInven.weapon = WEAPON_BROAD_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BLOOD;
			break;
		case WEAPON_BROAD_BASE:
			_playerInven.weapon = WEAPON_BROAD_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BASE;
			break;
		case WEAPON_BROAD_BLOOD:
			_playerInven.weapon = WEAPON_BROAD_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BLOOD;
			break;
		case WEAPON_LONG_BASE:
			_playerInven.weapon = WEAPON_BROAD_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BASE;
			break;
		case WEAPON_LONG_BLOOD:
			_playerInven.weapon = WEAPON_BROAD_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BLOOD;
			break;
		}
		break;
	case ITEM_WEAPON_LONG_BASE:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			_playerInven.weapon = WEAPON_LONG_BASE;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case WEAPON_DAGGER_BASE:
			_playerInven.weapon = WEAPON_LONG_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BASE;
			break;
		case WEAPON_DAGGER_BLOOD:
			_playerInven.weapon = WEAPON_LONG_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BLOOD;
			break;
		case WEAPON_BROAD_BASE:
			_playerInven.weapon = WEAPON_LONG_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BASE;
			break;
		case WEAPON_BROAD_BLOOD:
			_playerInven.weapon = WEAPON_LONG_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BLOOD;
			break;
		case WEAPON_LONG_BASE:
			_playerInven.weapon = WEAPON_LONG_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BASE;
			break;
		case WEAPON_LONG_BLOOD:
			_playerInven.weapon = WEAPON_LONG_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BLOOD;
			break;
		}
		break;
	case ITEM_WEAPON_LONG_BLOOD:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			_playerInven.weapon = WEAPON_LONG_BLOOD;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case WEAPON_DAGGER_BASE:
			_playerInven.weapon = WEAPON_LONG_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BASE;
			break;
		case WEAPON_DAGGER_BLOOD:
			_playerInven.weapon = WEAPON_LONG_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_DAGGER_BLOOD;
			break;
		case WEAPON_BROAD_BASE:
			_playerInven.weapon = WEAPON_LONG_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BASE;
			break;
		case WEAPON_BROAD_BLOOD:
			_playerInven.weapon = WEAPON_LONG_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_BROAD_BLOOD;
			break;
		case WEAPON_LONG_BASE:
			_playerInven.weapon = WEAPON_LONG_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BASE;
			break;
		case WEAPON_LONG_BLOOD:
			_playerInven.weapon = WEAPON_LONG_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_WEAPON_LONG_BLOOD;
			break;
		}
		break;
	case ITEM_SHOVEL_BASE:
		switch (_playerInven.shovel)
		{
		case SHOVEL_BASE:
			_playerInven.shovel = SHOVEL_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_BASE;
			break;
		case SHOVEL_BLOOD:
			_playerInven.shovel = SHOVEL_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_BLOOD;
			break;
		case SHOVEL_CRYSTAL:
			_playerInven.shovel = SHOVEL_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_CRYSTAL;
			break;
		case SHOVEL_TITANIUM:
			_playerInven.shovel = SHOVEL_BASE;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_TITANIUM;
			break;
		default:
			break;
		}
		break;
	case ITEM_SHOVEL_BLOOD:
		switch (_playerInven.shovel)
		{
		case SHOVEL_BASE:
			_playerInven.shovel = SHOVEL_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_BASE;
			break;
		case SHOVEL_BLOOD:
			_playerInven.shovel = SHOVEL_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_BLOOD;
			break;
		case SHOVEL_CRYSTAL:
			_playerInven.shovel = SHOVEL_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_CRYSTAL;
			break;
		case SHOVEL_TITANIUM:
			_playerInven.shovel = SHOVEL_BLOOD;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_TITANIUM;
			break;
		default:
			break;
		}
		break;
	case ITEM_SHOVEL_CRYSTAL:
		switch (_playerInven.shovel)
		{
		case SHOVEL_BASE:
			_playerInven.shovel = SHOVEL_CRYSTAL;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_BASE;
			break;
		case SHOVEL_BLOOD:
			_playerInven.shovel = SHOVEL_CRYSTAL;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_BLOOD;
			break;
		case SHOVEL_CRYSTAL:
			_playerInven.shovel = SHOVEL_CRYSTAL;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_CRYSTAL;
			break;
		case SHOVEL_TITANIUM:
			_playerInven.shovel = SHOVEL_CRYSTAL;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_TITANIUM;
			break;
		default:
			break;
		}
		break;
	case ITEM_SHOVEL_TITANIUM:
		switch (_playerInven.shovel)
		{
		case SHOVEL_BASE:
			_playerInven.shovel = SHOVEL_TITANIUM;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_BASE;
			break;
		case SHOVEL_BLOOD:
			_playerInven.shovel = SHOVEL_TITANIUM;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_BLOOD;
			break;
		case SHOVEL_CRYSTAL:
			_playerInven.shovel = SHOVEL_TITANIUM;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_CRYSTAL;
			break;
		case SHOVEL_TITANIUM:
			_playerInven.shovel = SHOVEL_TITANIUM;
			_tile[y * MAPTILEX + x].objectState = ITEM_SHOVEL_TITANIUM;
			break;
		default:
			break;
		}
		break;
	case ITEM_TORCH_1:
		switch (_playerInven.torch)
		{
		case TORCH_NONE:
			_playerInven.torch = TORCH_1;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case TORCH_1:
			_playerInven.torch = TORCH_1;
			_tile[y * MAPTILEX + x].objectState = ITEM_TORCH_1;
			break;
		case TORCH_2:
			_playerInven.torch = TORCH_1;
			_tile[y * MAPTILEX + x].objectState = ITEM_TORCH_2;
			break;
		case TORCH_3:
			_playerInven.torch = TORCH_1;
			_tile[y * MAPTILEX + x].objectState = ITEM_TORCH_3;
			break;
		}
		break;
	case ITEM_TORCH_2:
		switch (_playerInven.torch)
		{
		case TORCH_NONE:
			_playerInven.torch = TORCH_2;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case TORCH_1:
			_playerInven.torch = TORCH_2;
			_tile[y * MAPTILEX + x].objectState = ITEM_TORCH_1;
			break;
		case TORCH_2:
			_playerInven.torch = TORCH_2;
			_tile[y * MAPTILEX + x].objectState = ITEM_TORCH_2;
			break;
		case TORCH_3:
			_playerInven.torch = TORCH_2;
			_tile[y * MAPTILEX + x].objectState = ITEM_TORCH_3;
			break;
		}
		break;
	case ITEM_TORCH_3:
		switch (_playerInven.torch)
		{
		case TORCH_NONE:
			_playerInven.torch = TORCH_3;
			_tile[y * MAPTILEX + x].objectType = OBJECT_NONE;
			_tile[y * MAPTILEX + x].objectState = 0;
			break;
		case TORCH_1:
			_playerInven.torch = TORCH_3;
			_tile[y * MAPTILEX + x].objectState = ITEM_TORCH_1;
			break;
		case TORCH_2:
			_playerInven.torch = TORCH_3;
			_tile[y * MAPTILEX + x].objectState = ITEM_TORCH_2;
			break;
		case TORCH_3:
			_playerInven.torch = TORCH_3;
			_tile[y * MAPTILEX + x].objectState = ITEM_TORCH_3;
			break;
		}
		break;
	case ITEM_STATE_END:
		break;
	default:
		break;
	}
}

void Player::BlockCheck(int tileNum)
{
	switch (_tile[tileNum].objectKind)
	{
	case BLOCK_BASE1:
	case BLOCK_BASE2:
	case BLOCK_BASE3:
	case BLOCK_BASE4:
	case BLOCK_BASE5:
	case BLOCK_BASE6:
	case BLOCK_BASE7:
	case BLOCK_BASE8:
	case BLOCK_BASE9:
	case BLOCK_BASE10:
	case BLOCK_BASE11:
	case BLOCK_BASE12:
	case BLOCK_BASE13:
	case BLOCK_BASE14:
	case BLOCK_BASE15:
	case BLOCK_BASE16:
	case BLOCK_DOORFRONT:
	case BLOCK_DOORTURN:
		_tile[tileNum].objectKind = NULL;
		_tile[tileNum].objectType = OBJECT_NONE;
		CAMERA->WeakShake();
		SOUNDMANAGER->Play("DigOK");
	break;
	case BLOCK_STONE:	//2
		if (_playerInven.shovel == SHOVEL_BLOOD)
		{
			_tile[tileNum].objectKind = NULL;
			_tile[tileNum].objectType = OBJECT_NONE;
			Hit(1);
			CAMERA->WeakShake();
			SOUNDMANAGER->Play("DigOK");
		}
		else if (_playerInven.shovel > SHOVEL_BLOOD)
		{
			_tile[tileNum].objectKind = NULL;
			_tile[tileNum].objectType = OBJECT_NONE;
			CAMERA->WeakShake();
			SOUNDMANAGER->Play("DigOK");
		}
		else
			SOUNDMANAGER->Play("DigFail");
	break;
	case BLOCK_GOLD:	//3
		if (_playerInven.shovel == SHOVEL_BLOOD)
		{
			Hit(2);
			_tile[tileNum].objectKind = NULL;
			_tile[tileNum].objectType = OBJECT_NONE;
			CAMERA->WeakShake();
			SOUNDMANAGER->Play("DigOK");
		}
		else if (_playerInven.shovel > SHOVEL_CRYSTAL)
		{
			_tile[tileNum].objectKind = NULL;
			_tile[tileNum].objectType = OBJECT_NONE;
			CAMERA->WeakShake();
			SOUNDMANAGER->Play("DigOK");
			//아이템 생성
		}
		else
		SOUNDMANAGER->Play("DigFail");
	break;
	case BLOCK_STEEL:	//못부심
		SOUNDMANAGER->Play("DigFail");
	break;
	
	default:
		break;
	}
}

bool Player::AttackCheck(int arrow)
{
	switch (arrow)
	{
	case UP:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			_attackCheck = 0;
			return FALSE;
			break;
		case WEAPON_DAGGER_BASE:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_DAGGER_BLOOD:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}

				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_BROAD_BASE:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE ||
				_tile[(_y - 1)*MAPTILEX + _x + 1].isEnemyUP == TRUE ||
				_tile[(_y - 1)*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}

			break;
		case WEAPON_BROAD_BLOOD:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE ||
				_tile[(_y - 1)*MAPTILEX + _x + 1].isEnemyUP == TRUE ||
				_tile[(_y - 1)*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_LONG_BASE:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE ||
				_tile[(_y - 2)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_LONG_BLOOD:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE ||
				_tile[(_y - 2)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
			break;
		default:
			break;
		}
	break;
	case DOWN:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			break;
		case WEAPON_DAGGER_BASE:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_DAGGER_BLOOD:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_BROAD_BASE:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE ||
				_tile[(_y + 1)*MAPTILEX + _x + 1].isEnemyUP == TRUE ||
				_tile[(_y + 1)*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_BROAD_BLOOD:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE ||
				_tile[(_y + 1)*MAPTILEX + _x + 1].isEnemyUP == TRUE ||
				_tile[(_y + 1)*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_LONG_BASE:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE ||
				_tile[(_y + 2)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_LONG_BLOOD:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE ||
				_tile[(_y + 2)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
			break;
		default:
			break;
		}
	break;
	case LEFT:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			break;
		case WEAPON_DAGGER_BASE:
			if (_tile[_y*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_DAGGER_BLOOD:
			if (_tile[_y*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_BROAD_BASE:
			if (_tile[(_y + 1) * MAPTILEX + _x - 1].isEnemyUP == TRUE ||
				_tile[_y * MAPTILEX + _x - 1].isEnemyUP == TRUE ||
				_tile[(_y - 1) * MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
		break;
		case WEAPON_BROAD_BLOOD:
			if (_tile[(_y + 1) * MAPTILEX + _x - 1].isEnemyUP == TRUE ||
				_tile[_y * MAPTILEX + _x - 1].isEnemyUP == TRUE ||
				_tile[(_y - 1) * MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
		break;
		case WEAPON_LONG_BASE:
			if (_tile[_y*MAPTILEX + _x - 1].isEnemyUP == TRUE ||
				_tile[_y*MAPTILEX + _x - 2].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
		break;
		case WEAPON_LONG_BLOOD:
			if (_tile[_y*MAPTILEX + _x - 1].isEnemyUP == TRUE ||
				_tile[_y*MAPTILEX + _x - 2].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
			break;
		}
	break;
	case RIGHT:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			break;
		case WEAPON_DAGGER_BASE:
			if (_tile[_y*MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_DAGGER_BLOOD:
			if (_tile[_y*MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_BROAD_BASE:
			if (_tile[(_y + 1) * MAPTILEX + _x + 1].isEnemyUP == TRUE ||
				_tile[_y * MAPTILEX + _x + 1].isEnemyUP == TRUE ||
				_tile[(_y - 1) * MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_BROAD_BLOOD:
			if (_tile[(_y + 1) * MAPTILEX + _x + 1].isEnemyUP == TRUE ||
				_tile[_y * MAPTILEX + _x + 1].isEnemyUP == TRUE ||
				_tile[(_y - 1) * MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_LONG_BASE:
			if (_tile[_y*MAPTILEX + _x + 1].isEnemyUP == TRUE ||
				_tile[_y*MAPTILEX + _x + 2].isEnemyUP == TRUE)
			{
				_attackCheck++;
				return TRUE;
			}
			break;
		case WEAPON_LONG_BLOOD:
			if (_tile[_y*MAPTILEX + _x + 1].isEnemyUP == TRUE ||
				_tile[_y*MAPTILEX + _x + 2].isEnemyUP == TRUE)
			{
				if (RND->GetInt(10) == 5)
				{
					SOUNDMANAGER->Play("PlayerBat", 0.5f);
					_playerStat.currentHP += 1;
					if (_playerStat.currentHP > _playerStat.maxHP)
						_playerStat.currentHP = _playerStat.maxHP;
				}
				_attackCheck++;
				return TRUE;
			}
			break;
		default:
			break;
		}
	break;
	default:
		
	break;
	}
	_attackCheck = 0;
	return FALSE;
}

void Player::Attack(int arrow)
{
	//std::cout << _attackCheck << endl;
	if (_attackCheck > 4)
		_attackCheck = 4;

	switch (_attackCheck)
	{
	case 0:
		SOUNDMANAGER->Play("PlayerAttack1");
	break;
	case 1:
		SOUNDMANAGER->Play("PlayerAttack2");
	break;
	case 2:
		SOUNDMANAGER->Play("PlayerAttack3");
	break;
	case 3:
		SOUNDMANAGER->Play("PlayerAttack4");
	break;
	case 4:
		SOUNDMANAGER->Play("PlayerAttack5");
	break;
	}

	switch (arrow)
	{
	case UP:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			break;
		case WEAPON_DAGGER_BASE:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE)
				_enemyManager->AttackEnemy(_x, _y - 1,_playerStat.atk);
			break;
		case WEAPON_DAGGER_BLOOD:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y - 1, _playerStat.atk*2);
			}				
			break;
		case WEAPON_BROAD_BASE:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y - 1, _playerStat.atk);
			}
			if (_tile[(_y - 1)*MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x+1, _y - 1, _playerStat.atk);
			}
			if (_tile[(_y - 1)*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x-1, _y - 1, _playerStat.atk);
			}
			break;
		case WEAPON_BROAD_BLOOD:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y - 1, _playerStat.atk);
			}
			if (_tile[(_y - 1)*MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y - 1, _playerStat.atk);
			}
			if (_tile[(_y - 1)*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y - 1, _playerStat.atk);
			}
			break;
		case WEAPON_LONG_BASE:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y - 1, _playerStat.atk);
			}
			if (_tile[(_y - 2)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y - 2, _playerStat.atk);
			}

			break;
		case WEAPON_LONG_BLOOD:
			if (_tile[(_y - 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y - 1, _playerStat.atk);
			}
			if (_tile[(_y - 2)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y - 2, _playerStat.atk);
			}
			break;
		default:
			break;
		}
		break;
	case DOWN:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			break;
		case WEAPON_DAGGER_BASE:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y + 1, _playerStat.atk);
			}
			break;
		case WEAPON_DAGGER_BLOOD:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y + 1, _playerStat.atk*2);
			}
			break;
		case WEAPON_BROAD_BASE:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y + 1, _playerStat.atk);
			}
			if (_tile[(_y + 1)*MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y + 1, _playerStat.atk);
			}
			if (_tile[(_y + 1)*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y + 1, _playerStat.atk);
			}
			break;
		case WEAPON_BROAD_BLOOD:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y + 1, _playerStat.atk);
			}
			if (_tile[(_y + 1)*MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y + 1, _playerStat.atk);
			}
			if (_tile[(_y + 1)*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y + 1, _playerStat.atk);
			}
			break;
		case WEAPON_LONG_BASE:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y + 1, _playerStat.atk);
			}
			if (_tile[(_y + 2)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y + 2, _playerStat.atk);
			}
			break;
		case WEAPON_LONG_BLOOD:
			if (_tile[(_y + 1)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y + 1, _playerStat.atk);
			}
			if (_tile[(_y + 2)*MAPTILEX + _x].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x, _y + 2, _playerStat.atk);
			}
			break;
		default:
			break;
		}
		break;
	case LEFT:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			break;
		case WEAPON_DAGGER_BASE:
			if (_tile[_y*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y, _playerStat.atk);
			}
			break;
		case WEAPON_DAGGER_BLOOD:
			if (_tile[_y*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y, _playerStat.atk*2);
			}
			break;
		case WEAPON_BROAD_BASE:
			if (_tile[(_y + 1) * MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y+1, _playerStat.atk);
			}
			if (_tile[_y * MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y, _playerStat.atk);
			}
			if (_tile[(_y - 1) * MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y-1, _playerStat.atk);
			}
			break;
		case WEAPON_BROAD_BLOOD:
			if (_tile[(_y + 1) * MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y + 1, _playerStat.atk);
			}
			if (_tile[_y * MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y, _playerStat.atk);
			}
			if (_tile[(_y - 1) * MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y - 1, _playerStat.atk);
			}
			break;
		case WEAPON_LONG_BASE:
			if (_tile[_y*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y, _playerStat.atk);
			}
			if (_tile[_y*MAPTILEX + _x - 2].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 2, _y, _playerStat.atk);
			}
			break;
		case WEAPON_LONG_BLOOD:
			if (_tile[_y*MAPTILEX + _x - 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 1, _y, _playerStat.atk);
			}
			if (_tile[_y*MAPTILEX + _x - 2].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x - 2, _y, _playerStat.atk);
			}
			break;
		}
		break;
	case RIGHT:
		switch (_playerInven.weapon)
		{
		case WEAPON_NONE:
			break;
		case WEAPON_DAGGER_BASE:
			if (_tile[_y*MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x+1, _y, _playerStat.atk);
			}
			break;
		case WEAPON_DAGGER_BLOOD:
			if (_tile[_y*MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y, _playerStat.atk*2);
			}
			break;
		case WEAPON_BROAD_BASE:
			if (_tile[(_y + 1) * MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y+1, _playerStat.atk);
			}
			if (_tile[_y * MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y, _playerStat.atk);
			}
			if (_tile[(_y - 1) * MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y-1, _playerStat.atk);
			}
			break;
		case WEAPON_BROAD_BLOOD:
			if (_tile[(_y + 1) * MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y + 1, _playerStat.atk);
			}
			if (_tile[_y * MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y, _playerStat.atk);
			}
			if (_tile[(_y - 1) * MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y - 1, _playerStat.atk);
			}
			break;
		case WEAPON_LONG_BASE:
			if (_tile[_y*MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y, _playerStat.atk);
			}
			if (_tile[_y*MAPTILEX + _x + 2].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 2, _y, _playerStat.atk);
			}
			break;
		case WEAPON_LONG_BLOOD:
			if (_tile[_y*MAPTILEX + _x + 1].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 1, _y, _playerStat.atk);
			}
			if (_tile[_y*MAPTILEX + _x + 2].isEnemyUP == TRUE)
			{
				_enemyManager->AttackEnemy(_x + 2, _y, _playerStat.atk);
			}
			break;
		default:
			break;
		}
		break;
	default:

		break;
	}
}

void Player::Hit(int damage)
{
	float fdamage;
	fdamage = damage;

	CAMERA->StrongShake();

	if (_playerInven.body != BODY_NONE)
		fdamage = fdamage * 0.8;

	if(_playerInven.head == HEAD_BLAST || 
		_playerInven.head == HEAD_HELMET)
		fdamage = fdamage * 0.8;

	if (fdamage < 1)
		damage = 1;
	else
		damage = fdamage;

	_playerStat.currentHP -= damage; 


	switch (RND->GetInt(3))
	{
	case 0:
		SOUNDMANAGER->Play("PlayerHit1");
		break;
	case 1:
		SOUNDMANAGER->Play("PlayerHit2");
		break;
	case 2:
		SOUNDMANAGER->Play("PlayerHit3");
		break;
	default:
		break;
	}
	SOUNDMANAGER->Play("PlayerHitSFX");

	if (_playerStat.currentHP <= 0)
	{
		SOUNDMANAGER->Play("PlayerDeath", 1.0f);
		SCENEMANAGER->ChangeScene("End");
	}
}

void Player::PlayerEffectRender()
{
	bool check;

	if (_attackEffect)
	{

		int revisionX;
		int revisionY;
		switch (_EffectArrow)
		{
		case UP:

			if (_playerInven.weapon == WEAPON_BROAD_BASE || _playerInven.weapon == WEAPON_BROAD_BLOOD)
			{
				revisionX = (_effectImage2[_playerInven.weapon - 1]->GetFrameWidth() / 2);
				revisionY = (_effectImage2[_playerInven.weapon - 1]->GetFrameHeight());
			}
			else
			{
				revisionX = 0;
				revisionY = (_effectImage2[_playerInven.weapon - 1]->GetFrameHeight());
			}


			_effectImage2[_playerInven.weapon - 1]->ReverseFrameRender(_posX - revisionX,_posY - revisionY, _EffectFrameCount / 2);
			check = FALSE;
			break;
		case DOWN:

			if (_playerInven.weapon == WEAPON_BROAD_BASE || _playerInven.weapon == WEAPON_BROAD_BLOOD)
			{
				revisionX = (_effectImage2[_playerInven.weapon - 1]->GetFrameWidth() / 2);
				revisionY = -(_effectImage2[_playerInven.weapon - 1]->GetFrameHeight()/2);
			}
			else
			{
				revisionX = 0;
				revisionY = -(_effectImage2[_playerInven.weapon - 1]->GetFrameHeight() / 2);
			}
			_effectImage2[_playerInven.weapon - 1]->FrameRender(_posX - revisionX, _posY - revisionY, _EffectFrameCount / 2);
			check = FALSE;
			break;
		case LEFT:
			if (_playerInven.weapon != WEAPON_BROAD_BASE && _playerInven.weapon != WEAPON_BROAD_BLOOD)
			{
				revisionX = _effectImage1[_playerInven.weapon - 1]->GetFrameWidth();
				revisionY = 0;
			}
			else
			{
				revisionX = _effectImage1[_playerInven.weapon - 1]->GetFrameWidth();
				revisionY = (_effectImage1[_playerInven.weapon - 1]->GetFrameHeight()/2);
			}
			_effectImage1[_playerInven.weapon - 1]->FlipFrameRender(_posX - revisionX, _posY - revisionY, _EffectFrameCount / 2);
			check = TRUE;
			break;
		case RIGHT:
			if (_playerInven.weapon != WEAPON_BROAD_BASE && _playerInven.weapon != WEAPON_BROAD_BLOOD)
			{
				revisionX = -(_effectImage1[_playerInven.weapon - 1]->GetFrameWidth() / 2);
				revisionY = 0;
			}
			else
			{
				revisionX = -(_effectImage1[_playerInven.weapon - 1]->GetFrameWidth() / 2);
				revisionY = (_effectImage1[_playerInven.weapon - 1]->GetFrameHeight()/2);
			}
			_effectImage1[_playerInven.weapon - 1]->FrameRender(_posX - revisionX, _posY - revisionY, _EffectFrameCount / 2);
			check = TRUE;
			break;
		}

		_EffectFrameCount++;
		if (check)
		{
			if (_EffectFrameCount > _effectImage1[_playerInven.weapon - 1]->GetMaxFrameX() * 2)
			{
				_EffectFrameCount = 0;
				_attackEffect = FALSE;
			}
		}
		else
		{
			if (_EffectFrameCount > _effectImage2[_playerInven.weapon - 1]->GetMaxFrameY() * 2)
			{
				_EffectFrameCount = 0;
				_attackEffect = FALSE;
			}
		}



	}



	if (_fireEffect)
	{

		for (int i = 1; i < 5; i++)
		{
			if (_x + i >= MAPTILEX) break;
			if (_tile[(_y)*MAPTILEX + _x + i].objectType == OBJECT_BLOCK) break;
			if (_tile[(_y)*MAPTILEX + _x + i].isEnemyUP == TRUE) break;
			//이펙트 렌더
			IMAGEMANAGER->FindImage("Spell_Fire_Effect")->FrameRender((_x + i)*TILESIZEX, _y*TILESIZEY, _fireEffectFrame/3);
		}
		for (int i = 1; i < 5; i++)
		{
			if (_x - i < 0) break;
			if (_tile[(_y)*MAPTILEX + _x - i].objectType == OBJECT_BLOCK) break;
			if (_tile[(_y)*MAPTILEX + _x - i].isEnemyUP == TRUE) break;
			//이펙트 렌더
			IMAGEMANAGER->FindImage("Spell_Fire_Effect")->FrameRender((_x - i)*TILESIZEX, _y*TILESIZEY, _fireEffectFrame/3);

		}

		_fireEffectFrame++;
		if (_fireEffectFrame > 21)
		{
			_fireEffectFrame = 0;
			_fireEffect = FALSE;
		}
	}




}

void Player::SightRender()
{
	if (_playerInven.head == HEAD_MINERS)
	{
		_sight->Render(4);
	}
	else
	{
		_sight->Render(_playerInven.torch);
	}

	if (_digEffect)
	{
		int x;
		int y;

		switch (_EffectArrow)
		{
		case UP:
			x = (_x)* TILESIZEX;
			y = (_y - 1) * TILESIZEY;
			break;
		case DOWN:
			x = (_x)* TILESIZEX;
			y = (_y + 1) * TILESIZEY;
			break;
		case LEFT:
			x = (_x - 1) * TILESIZEX;
			y = (_y)* TILESIZEY;
			break;
		case RIGHT:
			x = (_x + 1) * TILESIZEX;
			y = (_y)* TILESIZEY;
			break;
		}

		switch (_playerInven.shovel)
		{
		case SHOVEL_BASE:
			IMAGEMANAGER->FindImage("Shovel_Base")->FrameRender(x, y - 12, 0, 0);
			break;
		case SHOVEL_BLOOD:
			IMAGEMANAGER->FindImage("Shovel_Blood")->FrameRender(x, y - 12, 0, 0);
			break;
		case SHOVEL_CRYSTAL:
			IMAGEMANAGER->FindImage("Shovel_Crystal")->FrameRender(x, y - 12, 0, 0);
			break;
		case SHOVEL_TITANIUM:
			IMAGEMANAGER->FindImage("Shovel_titanium")->FrameRender(x, y - 12, 0, 0);
			break;
		default:
			break;
		}

		if (_digEffectFrame > 5)
		{
			_digEffect = FALSE;
			_digEffectFrame = 0;
		}
		_digEffectFrame++;
	}

}

void Player::SpellHeal()
{
	if (_playerInven.head == HEAD_CROWN)
	{
		if (_killStack >= 5)
		{
			_killStack = 0;
			SOUNDMANAGER->Play("SpellHeal_voice", 0.5f);
			SOUNDMANAGER->Play("SpellHeal");
			_playerStat.currentHP += 2;
			if (_playerStat.currentHP > _playerStat.maxHP)
				_playerStat.currentHP = _playerStat.maxHP;
		}
	}
	else
	{
		if (_killStack >= 10)
		{
			_killStack = 0;
			SOUNDMANAGER->Play("SpellHeal_voice", 0.5f);
			SOUNDMANAGER->Play("SpellHeal");
			_playerStat.currentHP += 2;
			if (_playerStat.currentHP > _playerStat.maxHP)
				_playerStat.currentHP = _playerStat.maxHP;
		}
	}

}

void Player::SpellFire()
{
	if (_playerInven.head == HEAD_CROWN)
	{
		if (_killStack >= 5)
		{

			for (int i = 1; i < 5; i++)
			{
				if (_x + i >= MAPTILEX) break;
				if (_tile[(_y)*MAPTILEX + _x + i].objectType == OBJECT_BLOCK) break;

				if (_tile[(_y)*MAPTILEX + _x + i].isEnemyUP == TRUE)
				{
					_enemyManager->AttackEnemy(_x + i, _y, 2);
					break;
				}
			}

			for (int i = 1; i < 5; i++)
			{
				if (_x - i < 0) break;
				if (_tile[(_y)*MAPTILEX + _x - i].objectType == OBJECT_BLOCK) break;

				if (_tile[(_y)*MAPTILEX + _x - i].isEnemyUP == TRUE)
				{
					_enemyManager->AttackEnemy(_x - i, _y, 2);
					break;
				}
			}
			SOUNDMANAGER->Play("SpellFire_voice");
			SOUNDMANAGER->Play("SpellFire");
			CAMERA->StrongShake();
			_fireEffect = TRUE;
			_killStack = 0;
		}
	}
	else
	{
		if (_killStack >= 10)
		{

			for (int i = 1; i < 5; i++)
			{
				if (_x + i >= MAPTILEX) break;
				if (_tile[(_y)*MAPTILEX + _x + i].objectType == OBJECT_BLOCK) break;

				if (_tile[(_y)*MAPTILEX + _x + i].isEnemyUP == TRUE)
				{

					_enemyManager->AttackEnemy(_x + i, _y, 2);
					break;
				}
			}

			for (int i = 1; i < 5; i++)
			{
				if (_x - i < 0) break;
				if (_tile[(_y)*MAPTILEX + _x - i].objectType == OBJECT_BLOCK) break;

				if (_tile[(_y)*MAPTILEX + _x - i].isEnemyUP == TRUE)
				{
					_enemyManager->AttackEnemy(_x - i, _y, 2);
					break;
				}
			}
			SOUNDMANAGER->Play("SpellFire_voice");
			SOUNDMANAGER->Play("SpellFire");
			CAMERA->StrongShake();
			_fireEffect = TRUE;
			_killStack = 0;
		}
	}

}