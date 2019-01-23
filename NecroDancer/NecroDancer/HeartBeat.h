#pragma once
#include "GameNode.h"
struct Note
{
	int timing;
	RECT rc;
	bool live;
	Note()
	{
		//rc = NULL;
		timing = 0;
		live = TRUE;
	}
};

class HeartBeat : public GameNode
{
protected:
	int _bgmPlayTime;		//타이밍 계산
	int _pointY;			//시작 높이 지정
	//HBRUSH	brush;
	ID2D1SolidColorBrush*   _brush;
	vector<Note>			_vNote;
	vector<Note>::iterator	_viNote;
	D2DImage*	_noteImage;
	D2DImage*	_heartImage;
	D2DImage*	_black;
	RECT _beatRectIn;
	RECT _beatRectOut;
public:
	
	virtual HRESULT Init(int y);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	virtual void NoteLoad();
	virtual bool NoteCheckPlayer();
	virtual bool NoteCheckEnemy();

	HeartBeat();
	~HeartBeat();
};

