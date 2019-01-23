#include "stdafx.h"
#include "Stage3Beat.h"


Stage3Beat::Stage3Beat()
{
}


Stage3Beat::~Stage3Beat()
{
}

HRESULT Stage3Beat::Init(int y)
{
	_pointY = y;
	NoteLoad();
	_brush = D2DMANAGER->MakeBrush(D2D1::ColorF(1.0f, 0, 0));
	_noteImage = IMAGEMANAGER->FindImage("BeatNote");			//��Ʈ �̹���
	_heartImage = IMAGEMANAGER->FindImage("Heart");				//��Ʈ �̹��� �ҷ�����
	_black = IMAGEMANAGER->FindImage("BlackBar");

	SOUNDMANAGER->Play("Stage3", 0.7);
	_bgmPlayTime = SOUNDMANAGER->GetPlayTime("Stage3");												//�����̶� ����� �����ϱ����� �����ϳ� ���� �װɷ� ���پ���.

	HeartBeat::Init(y);

	return S_OK;
}
void Stage3Beat::Update()
{
	_bgmPlayTime = SOUNDMANAGER->GetPlayTime("Stage3");						//�����̶� ����� �����ϱ����� �����ϳ� ���� �װɷ� ���پ���.

	for (_viNote = _vNote.begin(); _viNote != _vNote.end(); _viNote++)		//��Ʈ�� ��Ʈ����
	{
		_viNote->rc = RectMake((WINSIZEX / 2) - ((_viNote->timing - _bgmPlayTime) / 3), _pointY + 10, _noteImage->GetWidth(), _noteImage->GetHeight());
		if (((_viNote->timing - _bgmPlayTime) / 5) > 700) break;
	}
}
void Stage3Beat::Render()
{
	HeartBeat::Render();
}
void Stage3Beat::Release()
{

}


void Stage3Beat::NoteLoad()
{
	vector<string>	vString;
	vString = TXTDATA->TxtLoad(".\\Sound\\Stage\\zone1_3.txt");

	for (int i = 0; i < vString.size(); i++)
	{
		Note note;
		note.timing = stoi(vString[i], 0, 10);

		_vNote.push_back(note);
	}
}