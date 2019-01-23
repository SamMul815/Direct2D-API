#pragma once
#include "singletonBase.h"
//#include <map>
#include <unordered_map>
#include <vector>

//#include <hash_map>

//fmod.hpp �߰�
#include "inc/fmod.hpp"
//lib��ũ
#pragma comment(lib, "lib/fmodex_vc.lib")

using namespace FMOD;
//using namespace stdext;
//ä�� ���۸� ����
#define SOUNDBUFFER 50
#define EXTRACHANNELBUFFER 25 

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class SoundManager : public SingletonBase<SoundManager>
{
private:

	typedef vector<pair<string, Sound**>> arrSounds;
	typedef vector<pair<string, Sound**>>::iterator arrSoundsIter;
	typedef vector<pair<string, Channel**>> arrChannels;
	typedef vector<pair<string, Channel**>>::iterator arrChannelsIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;
	arrSounds _mTotalSounds;

public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);

	void AddSound(string keyName, string soundName, bool bgm, bool loop);
	void Play(string keyName, float volume = 1.0f); // 0.0 ~ 1.0f  0 ~ 255
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);
	bool IsPlaySound(string keyName);
	bool IsPauseSound(string keyName);

	int GetPlayTotalTime(string keyName);					//��ü �뷡���� �˾ƿ��� �Լ�
	int GetPlayTime(string keyName);						//���� �뷡��ġ �˾ƿ��� �Լ�
	void SetPlayTime(string keyName, unsigned int time);	//�뷡 ��ġ �Ű��ִ� �Լ�
	void SetVolume(string keyName, float volume);
	arrSounds GetTotalSound() { return _mTotalSounds; }

	SoundManager();
	~SoundManager();
};

