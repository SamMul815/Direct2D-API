#pragma once
#include "HeartBeat.h"
class Stage1Beat : public HeartBeat
{
public:
	Stage1Beat();
	~Stage1Beat();

	virtual HRESULT Init(int y);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	virtual void NoteLoad();


};

