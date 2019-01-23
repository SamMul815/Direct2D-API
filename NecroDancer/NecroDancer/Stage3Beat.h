#pragma once
#include "HeartBeat.h"
class Stage3Beat : public HeartBeat
{
public:
	Stage3Beat();
	~Stage3Beat();
	virtual HRESULT Init(int y);
	virtual void Update();
	virtual void Render();
	virtual void Release();
	virtual void NoteLoad();
};

