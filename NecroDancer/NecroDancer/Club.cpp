#include "stdafx.h"
#include "Club.h"

#define MAX 50

Club::Club()
{
}


Club::~Club()
{
}

HRESULT Club::Init()
{
	GameNode::Init();

	_loading = new Loading;
	//_loading->Init();

	_player = new Player;			//플레이어 생성
	_player->Init();

	_stage1 = new Stage1;
	_stage1->LinkPlayer(_player);

	_stage2 = new Stage2;
	_stage2->LinkPlayer(_player);

	_stage3 = new Stage3;
	_stage3->LinkPlayer(_player);

	_endStage = new EndStage;

	_clearStage = new ClearStage;

	//_stage1->Init();


	SCENEMANAGER->AddScene("loading", _loading);
	SCENEMANAGER->AddScene("Stage1", _stage1);
	SCENEMANAGER->AddScene("Stage2", _stage2);
	SCENEMANAGER->AddScene("Stage3", _stage3);

	SCENEMANAGER->AddScene("End", _endStage);
	SCENEMANAGER->AddScene("Clear", _clearStage);

	SCENEMANAGER->ChangeScene("loading");

	//SCENEMANAGER->AddScene("stage1", new Stage1);
	//_player->LinkBeat(_beat);		//플레이어와 비트 연결

	_txt = new D2DText;
	_txt->Init(L"궁서", 20, D2D1::ColorF(0, 0, 0));

	return S_OK;
}

void Club::Release()
{
	GameNode::Release();

}

void Club::Update()
{
	GameNode::Update();
	SCENEMANAGER->Update();
	//_beat->Update();
	//_player->Update();
	/*if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
	{
		if (_beat->NoteCheckPlayer())
			_noteCheck++;
	}*/

	//_beat->NoteCheckEnemy(); 
}

void Club::Render()
{
	D2DMANAGER->BeginDraw();
	//D2DMANAGER->draw
	SCENEMANAGER->Render();

	TIMEMANAGER->Render();
	//_beat->Render();
	//WCHAR str[10];
	//wsprintfW(str, L"%d", _noteCheck);
	//_txt->Render(100, 200, 100, 250, str);
	D2DMANAGER->EndDraw();
}

