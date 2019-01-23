#pragma once
#include "GameNode.h"
class EndStage : public GameNode
{
private:
	D2DImage*	_image;
	D2DText*	_text;
	Animation*	_ani;
public:
	EndStage();
	~EndStage();

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();

};

