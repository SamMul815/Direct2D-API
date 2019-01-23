#pragma once
#include "GameNode.h"

//���ӿ� ���� �̹����� ����� �׳� �� �ҷ��ɽô� 

class Loading : public GameNode
{
private:
	int _count;
	D2DImage _image;
	Animation* _ani;
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	Loading();
	~Loading();
};

