#include "stdafx.h"
#include "LoadingStage.h"


LoadingStage::LoadingStage()
{
}

LoadingStage::~LoadingStage()
{
}

HRESULT LoadingStage::Init()
{
	_image = IMAGEMANAGER->AddImage("LoadingImage", L".\\Image\\GameUI\\mainmenu.png", WINSIZEX, WINSIZEY);
	return S_OK;
}

void LoadingStage::Update()
{

}

void LoadingStage::Render()
{
	_image->UIRender(0, 0);
}