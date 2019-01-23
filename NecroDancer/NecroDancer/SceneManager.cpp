#include "stdafx.h"
#include "GameNode.h"
#include "SceneManager.h"

//private도 걍 public처럼 접근가능케 해줌 캡슐화 무시
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//교체될 init 함수 실행
	SceneManager::_readyScene->Init();

	//현재 씬을 교체될 씬으로 바꿈
	SceneManager::_currentScene = SceneManager::_readyScene;

	//로딩씬을 해제
	SceneManager::_loadingScene->Release();
	SceneManager::_loadingScene = NULL;
	SceneManager::_readyScene = NULL;

	return 0;
}

GameNode* SceneManager::_currentScene = NULL;
GameNode* SceneManager::_loadingScene = NULL;
GameNode* SceneManager::_readyScene = NULL;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void SceneManager::Release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->Release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else
		{
			++miSceneList;
		}
	}

	_mSceneList.clear();

}

void SceneManager::Update(void)
{
	if (_currentScene) _currentScene->Update();
}

void SceneManager::Render(void)
{
	if (_currentScene) _currentScene->Render();
}

//씬 추가
GameNode* SceneManager::AddScene(string sceneName, GameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//로딩 씬 추가
GameNode* SceneManager::AddLoadingScene(string loadingSceneName, GameNode* scene)
{
	if (!scene) return NULL;

	_mLoadingSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	//찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	//바꾸려는 씬으로 초기황
	if (SUCCEEDED(find->second->Init()))
	{
		if (_currentScene) _currentScene->Release();
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	//찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if (findLoading == _mLoadingSceneList.end()) 
		return ChangeScene(loadingSceneName);


	//바꾸려는 씬으로 초기황
	if (SUCCEEDED(find->second->Init()))
	{
		//씬이 있으면 릴리즈
		if (_currentScene) _currentScene->Release();

		//로딩씬 틀고
		_loadingScene = findLoading->second;

		//준비된 씬에 바꿀려는 씬 넣어줌 ㅇㅇ
		_readyScene = find->second;

		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadThreadID));
	}

	return E_FAIL;
}
