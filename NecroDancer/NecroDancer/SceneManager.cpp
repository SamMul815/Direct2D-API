#include "stdafx.h"
#include "GameNode.h"
#include "SceneManager.h"

//private�� �� publicó�� ���ٰ����� ���� ĸ��ȭ ����
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//��ü�� init �Լ� ����
	SceneManager::_readyScene->Init();

	//���� ���� ��ü�� ������ �ٲ�
	SceneManager::_currentScene = SceneManager::_readyScene;

	//�ε����� ����
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

//�� �߰�
GameNode* SceneManager::AddScene(string sceneName, GameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//�ε� �� �߰�
GameNode* SceneManager::AddLoadingScene(string loadingSceneName, GameNode* scene)
{
	if (!scene) return NULL;

	_mLoadingSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	//ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	//�ٲٷ��� ������ �ʱ�Ȳ
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
	//ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if (findLoading == _mLoadingSceneList.end()) 
		return ChangeScene(loadingSceneName);


	//�ٲٷ��� ������ �ʱ�Ȳ
	if (SUCCEEDED(find->second->Init()))
	{
		//���� ������ ������
		if (_currentScene) _currentScene->Release();

		//�ε��� Ʋ��
		_loadingScene = findLoading->second;

		//�غ�� ���� �ٲܷ��� �� �־��� ����
		_readyScene = find->second;

		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadThreadID));
	}

	return E_FAIL;
}
