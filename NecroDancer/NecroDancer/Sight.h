#pragma once
#include "EnumStruct.h"

class Player;

class Sight
{
private:
	InGameTileData* _tile;
	Player*	_player;
	D2DImage*	_sight;
public:
	Sight();
	~Sight();

	void LinkTile(InGameTileData* tile) { _tile = tile; }
	void LinkPlayer(Player* player) { _player = player; }

	HRESULT Init();
	void Update();
	void Render(int torch);

};

