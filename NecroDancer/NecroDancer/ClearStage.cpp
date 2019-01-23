#include "stdafx.h"
#include "ClearStage.h"

ClearStage::ClearStage()
{
}


ClearStage::~ClearStage()
{
}

HRESULT ClearStage::Init()
{
	_image = IMAGEMANAGER->FindImage("ClearSkeletonBase");
	_ani = new Animation;
	_ani->Init(_image->GetWidth(), _image->GetHeight(), _image->GetFrameWidth(), _image->GetFrameHeight());
	int arr[8] = { 0,1,2,3,4,5,6,7 };

	//_ani->SetDefPlayFrame(0, TRUE);
	_ani->SetPlayFrame(arr, 8, TRUE);
	_ani->Start();
	_ani->SetFPS(8);
	_text = new D2DText;
	_text->Init(L"Arial", 200, D2D1::ColorF(1.0f, 1.0f, 1.0f));

	return S_OK;
}

void ClearStage::Update()
{
	_ani->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	CAMERA->SetX(0);
	CAMERA->SetY(0);
}

void ClearStage::Render()
{
	_text->Render(100, 100, 600, 400, L"Clear");

	_text->Render(100, 350, 600, 400, L"Stage");

	_image->AniRender(800, 100, _ani);
	_image->AniRender(800, 260, _ani);
	_image->AniRender(800, 420, _ani);
	_image->AniRender(800, 580, _ani);
}