#pragma once
#include "SingletonBase.h"
#include <string>
#include <map>

class GameNode;

using namespace std;

class SceneManager : public SingletonBase < SceneManager >
{
public:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;		//���� �� 
	static GameNode* _loadingScene;		//�ε� ��
	static GameNode* _readyScene;		//��� ��

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	SceneManager();
	~SceneManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	//�� �߰�
	GameNode* AddScene(string sceneName, GameNode* scene);

	//�ε� �� �߰�
	GameNode* AddLoadingScene(string loadingSceneName, GameNode* scene);

	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	//private�� �� publicó�� ���ٰ����� ���� ĸ��ȭ ����
	friend DWORD CALLBACK loadingThread(LPVOID prc);

};

