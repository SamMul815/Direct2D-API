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
	static GameNode* _currentScene;		//ÇöÀç ¾À 
	static GameNode* _loadingScene;		//·Îµù ¾À
	static GameNode* _readyScene;		//´ë±â ¾À

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

	//¾À Ãß°¡
	GameNode* AddScene(string sceneName, GameNode* scene);

	//·Îµù ¾À Ãß°¡
	GameNode* AddLoadingScene(string loadingSceneName, GameNode* scene);

	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	//privateµµ °Á publicÃ³·³ Á¢±Ù°¡´ÉÄÉ ÇØÁÜ Ä¸½¶È­ ¹«½Ã
	friend DWORD CALLBACK loadingThread(LPVOID prc);

};

