#include "stdafx.h"
#include "Sight.h"
#include "Player.h"

Sight::Sight()
{
}


Sight::~Sight()
{
}

HRESULT Sight::Init()
{
	_sight = IMAGEMANAGER->FindImage("Sight");

	return S_OK;
}

void Sight::Render(int torch)
{
	int	x = _player->GetPosX();
	int	y = _player->GetPosY();

	int calcX;
	int calcY;
	double sight;

	for (int i = -10; i < 10; i++)
	{
		for (int j = -6; j < 6; j++)
		{
			calcX = abs(i);
			calcY = abs(j);
			
			sight = sqrt((calcX*calcX) + (calcY * calcY));

			switch (torch)
			{
			case TORCH_NONE:
				sight = (sight / 50) * 5;
				sight = sight * 2 + 0.1;
				break;
			case TORCH_1:
				sight = (sight / 50) * 5;
				if (sight < 0.2)
					sight = 0;
				else
				sight = sight * 1.5 + 0.1;
				break;
			case TORCH_2:
				sight = (sight / 50) * 5;
				if (sight < 0.35)
					sight = 0;
				else
					sight = sight * 1.35 + 0.1;
				break;
			case TORCH_3:
				sight = (sight / 50) * 5;
				if (sight < 0.5)
					sight = 0;
				else
					sight = sight*1.1 + 0.1;
				break;
			case 4:
				sight = (sight / 50) * 5;
				if (sight < 0.8)
					sight = 0;
				else
					sight = sight;
				break;
				break;
			default:
				sight = (sight / 50) * 5;
				sight = sight * 2 + 0.1;
				break;
			}

			//sight = (sight / 50) * 5;
			//sight = sight * 2 + 0.1;

			_sight->Render( x+ i*TILESIZEX, y + j*TILESIZEY,sight);
		}
	}


}