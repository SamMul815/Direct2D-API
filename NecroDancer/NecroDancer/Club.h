#pragma once
#include "GameNode.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Player.h"
#include "Loading.h"
#include "EndStage.h"
#include "ClearStage.h"
#include "EnumStruct.h"
#include <vector>



class Club : public GameNode
{
private:
	//int _noteCheck;
	Stage1*			_stage1;
	Stage2*			_stage2;
	Stage3*			_stage3;
	Loading*		_loading;
	EndStage*		_endStage;
	ClearStage*		_clearStage;
	D2DText*		 _txt;
	Player*			 _player;
public:

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	Club();
	~Club();
};

