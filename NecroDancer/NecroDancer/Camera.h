#pragma once
#include "SingletonBase.h"
class Camera : public SingletonBase<Camera>
{
private:
	int _x;
	int _y;
	RECT _cameraRC;

	bool _StrongShake;
	int _StrongTime;

	bool _WeakShake;
	int _WeakTime;

public:
	HRESULT Init();
	void Update();

	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
	void SetCenterXY(int x, int y);
	void SetXY(int x, int y);
	int GetX() { return _x; }
	int GetY() { return _y; }

	long GetLeft() { return _cameraRC.left; }
	long GetRight() { return _cameraRC.right; }
	long GetTop() { return _cameraRC.top; }
	long GetBottom() { return _cameraRC.bottom; }

	void StrongShake() { _StrongShake = TRUE; }
	void WeakShake() { _WeakShake = TRUE; }
	Camera();
	~Camera();
};

