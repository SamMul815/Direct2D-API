#pragma once
#include "GameNode.h"
class LoadingStage : public GameNode
{
private:
	D2DImage* _image;
public:
	LoadingStage();
	~LoadingStage();

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();

};

