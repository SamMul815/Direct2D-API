#pragma once
#include "singletonBase.h"
//#include <map>
#include <unordered_map>
#include <vector>

//#include <hash_map>

//fmod.hpp 추가
#include "inc/fmod.hpp"
//lib링크
#pragma comment(lib, "lib/fmodex_vc.lib")

using namespace FMOD;
//using namespace stdext;
//채널 버퍼를 셋팅
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

	int GetPlayTotalTime(string keyName);					//전체 노래길이 알아오는 함수
	int GetPlayTime(string keyName);						//현재 노래위치 알아오는 함수
	void SetPlayTime(string keyName, unsigned int time);	//노래 위치 옮겨주는 함수
	void SetVolume(string keyName, float volume);
	arrSounds GetTotalSound() { return _mTotalSounds; }

	SoundManager();
	~SoundManager();
};

