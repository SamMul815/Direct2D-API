#include "stdafx.h"
#include "EndStage.h"


EndStage::EndStage()
{
}

EndStage::~EndStage()
{
}

HRESULT EndStage::Init()
{
	_image = IMAGEMANAGER->FindImage("LoadingSkeletonBase");
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

void EndStage::Update()
{
	_ani->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	CAMERA->SetX(0);
	CAMERA->SetY(0);
}

void EndStage::Render()
{
	_text->Render(100, 100, 600, 400, L"FAIL");

	_text->Render(100, 300, 600, 400, L"Stage");

	_image->AniRender(800, 150, _ani);
	_image->AniRender(800, 300, _ani);
	_image->AniRender(800, 450, _ani);
	_image->AniRender(800, 600, _ani);
}