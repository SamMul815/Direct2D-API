#include "stdafx.h"
#include "HeartBeat.h"


HeartBeat::HeartBeat()
{
}


HeartBeat::~HeartBeat()
{
}

HRESULT HeartBeat::Init(int y)
{

	for (_viNote = _vNote.begin(); _viNote != _vNote.end(); _viNote++)		//노트에 렉트생성
	{
		_viNote->rc = RectMake((WINSIZEX / 2) - ((_viNote->timing - _bgmPlayTime) / 5), _pointY+10, _noteImage->GetWidth(), _noteImage->GetHeight());
		if (((_viNote->timing - _bgmPlayTime) / 5) > 700) break;
	}
	_beatRectOut = RectMakeCenter(WINSIZEX / 2-20, _pointY, 300, 100);
	_beatRectIn = RectMakeCenter(WINSIZEX / 2 , _pointY, 150, 100);
	return S_OK;
}

void HeartBeat::Update()
{

}

void HeartBeat::Render()
{
	RECT rc;
	_black->UIRender(0,WINSIZEY - _black->GetHeight());
	for (_viNote = _vNote.begin(); _viNote != _vNote.end(); _viNote++)		//노트에 렉트생성
	{
		if(_viNote->rc.left < WINSIZEX/2)
			_noteImage->UIFrameRender(_viNote->rc.left, _viNote->rc.top, _vNote.size() < 100, 0);

		if (_viNote->rc.left < 0)break;
	}

	if (IntersectRect(&rc, &_vNote.begin()->rc, &_beatRectIn))
		_heartImage->UIFrameRender(WINSIZEX / 2 - _heartImage->GetFrameWidth() / 2, _pointY - 10, 0,0);
	else
		_heartImage->UIFrameRender(WINSIZEX / 2 - _heartImage->GetFrameWidth() / 2, _pointY - 10, 1, 0);
	
//	D2DMANAGER->DrawRectangle(_brush, &_beatRectOut, 1.0f);
//	D2DMANAGER->DrawRectangle(_brush, &_beatRectIn, 1.0f);

}

void HeartBeat::Release()
{

}

bool HeartBeat::NoteCheckPlayer()
{
	RECT rc;
	if ((IntersectRect(&rc, &_beatRectOut, &_vNote.begin()->rc)))
	{
		if (IntersectRect(&rc, &_beatRectIn, &_vNote.begin()->rc) && _vNote.begin()->live == TRUE)
		{
			_vNote.begin()->live = FALSE;
			return TRUE;
		}
		else
		{
			_vNote.begin()->live = FALSE;
		}
	}
	return FALSE;
}

bool HeartBeat::NoteCheckEnemy()
{
	if (_vNote.begin()->timing < _bgmPlayTime-200 || _vNote.begin()->live == FALSE)
	{
		_vNote.erase(_vNote.begin());	//시간이 지난 노트는 지워줌과 동시에 적들이 행동할수있게 TRUE값을 넘겨주자
		
		if (_vNote.size() <= 0)
			SCENEMANAGER->ChangeScene("End");
		return TRUE;
	}
	return FALSE;
}


void HeartBeat::NoteLoad()
{
}

