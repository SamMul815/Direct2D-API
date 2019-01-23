#pragma once
#include "HeartBeat.h"
class Stage2Beat : public HeartBeat
{
public:
	Stage2Beat();
	~Stage2Beat();

	virtual HRESULT Init(int y);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	virtual void NoteLoad();


};

