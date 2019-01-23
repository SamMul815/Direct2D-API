#pragma once
#include "GameNode.h"

class ClearStage : public GameNode
{
private:
	D2DImage*	_image;
	D2DText*	_text;
	Animation*	_ani;
public:
	ClearStage();
	~ClearStage();

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
};

