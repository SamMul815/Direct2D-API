#include "stdafx.h"
#include "Stage1Beat.h"


Stage1Beat::Stage1Beat()
{
}


Stage1Beat::~Stage1Beat()
{
}

HRESULT Stage1Beat::Init(int y)
{
	_pointY = y;
	NoteLoad();
	_brush = D2DMANAGER->MakeBrush(D2D1::ColorF(1.0f, 0, 0));
	_noteImage = IMAGEMANAGER->FindImage("BeatNote");			//노트 이미지
	_heartImage = IMAGEMANAGER->FindImage("Heart");				//하트 이미지 불러오기
	_black = IMAGEMANAGER->FindImage("BlackBar");

	SOUNDMANAGER->Play("Stage1",0.7);
	_bgmPlayTime = SOUNDMANAGER->GetPlayTime("Stage1");												//조금이라도 계산을 빨리하기위해 변수하나 만들어서 그걸로 갖다쓰자.

	HeartBeat::Init(y);

	return S_OK;
}
void Stage1Beat::Update()
{
	_bgmPlayTime = SOUNDMANAGER->GetPlayTime("Stage1");						//조금이라도 계산을 빨리하기위해 변수하나 만들어서 그걸로 갖다쓰자.

	for (_viNote = _vNote.begin(); _viNote != _vNote.end(); _viNote++)		//노트에 렉트생성
	{
		_viNote->rc = RectMake((WINSIZEX / 2) - ((_viNote->timing - _bgmPlayTime) / 3), _pointY+10, _noteImage->GetWidth(), _noteImage->GetHeight());
		if (((_viNote->timing - _bgmPlayTime) / 5) > 700) break;
	}
}
void Stage1Beat::Render()
{
	HeartBeat::Render();
}
void Stage1Beat::Release()
{

}


void Stage1Beat::NoteLoad()
{
	vector<string>	vString;
	vString = TXTDATA->TxtLoad(".\\Sound\\Stage\\zone1_1.txt");

	for (int i = 0; i < vString.size(); i++)
	{
		Note note;
		note.timing = stoi(vString[i], 0, 10);

		_vNote.push_back(note);
	}
}