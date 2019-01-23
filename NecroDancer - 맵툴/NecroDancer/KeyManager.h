#pragma once
#include "singletonBase.h"
#include <bitset>

//눌려질 수 있는 키는 죄다 등록
#define KEYMAX 256

using namespace std;

class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	HRESULT Init(void);
	void Release(void);

	bool IsOnceKeyDown(int key);

	bool IsOnceKeyUp(int key);

	bool IsStayKeyDown(int key);

	bool IsToggleKey(int key);

	bitset<KEYMAX> GetKeyUp() { return _keyUp; }
	bitset<KEYMAX> GetKeyDown() { return _keyDown; }

	void SetKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { _keyUp.set(key, state); }

	KeyManager();
	~KeyManager();
};

