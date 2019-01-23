#pragma once
#include "GameNode.h"

//게임에 사용될 이미지랑 사운드랑 그냥 다 불러옵시다 

class Loading : public GameNode
{
private:
	int _count;
	D2DImage _image;
	Animation* _ani;
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	Loading();
	~Loading();
};

