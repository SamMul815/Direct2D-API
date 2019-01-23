#pragma once
#include <vector>
using namespace std;
//================================
// ## Animation ## 2016. 01. 07 ##
//================================

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

//void* <--- 보이드포인터 == 형태가 없이 가르킬 수 있기 때문에
//어떤 형이든 다 담을 수가 있다. 단지 불편함이라면 캐스팅을 해서 써야한다능거!

class Animation
{
public:
	//프레임에 임의접근가능케하려고 뻐블릭!!!
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

private:
	int _frameNum;

	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameWidth;
	int _frameHeight;

	BOOL _loop;

	float _frameUpdateSec;
	float _elapsedSec;

	DWORD _nowPlayIdx;
	BOOL _play;

	void* _obj;
	CALLBACK_FUNCTION _callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	Animation();
	~Animation();

	HRESULT Init(int totalW, int totalH, int frameW, int frameH);

	void Release(void);

	//default 애니메이션
	void SetDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void SetDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void SetDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//배열로 돌리는 애니메이션
	void SetPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void SetPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void SetPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//시작과 끝 번호로 돌리는 애니메이션(구간 재생)
	void SetPlayFrame(int Start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void SetPlayFrame(int Start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);
	void SetPlayFrame(int Start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);

	void SetFPS(int framePerSec);

	void FrameUpdate(float elapsedTime);

	void Start(void);
	void Stop(void);
	void Pause(void);
	void Resume(void);

	inline vector<int> GetVPlayList(void) { return _playList; }

	inline DWORD GetNowPlayIdx(void) { return _nowPlayIdx; }

	inline BOOL IsPlay(void) { return _play; }

	inline POINT GetFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	inline int GetFrameWidth(void) { return _frameWidth; }

	inline int GetFrameHeight(void) { return _frameHeight; }
};


