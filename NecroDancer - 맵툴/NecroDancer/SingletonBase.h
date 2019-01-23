#pragma once
template<typename T>
class SingletonBase
{
protected:
	static T* singleton;

	SingletonBase(void) {};
	~SingletonBase(void) {};

public:
	static T* GetSingleton(void);
	void ReleaseSingleton(void);

};

//�̱��� �ʱ�ȭ
template <typename T>
T* SingletonBase<T>::singleton = 0;

template <typename T>
T* SingletonBase<T>::GetSingleton(void)
{
	if (!singleton) singleton = new T;

	return singleton;
}

//�̱��� �޸� ����
template <typename T>
void SingletonBase<T>::ReleaseSingleton(void)
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}