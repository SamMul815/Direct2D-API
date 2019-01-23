#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>

class TxtData : public SingletonBase<TxtData>
{
public:
	HRESULT Init();
	void Release();

	//���̺�
	void TxtSave(const char* saveFileName, vector<string> vStr);
	char* VectorArrayCombine(vector<string> vArray);

	//�ε�
	vector<string> TxtLoad(const char* loadFileName);
	vector<string> CharArraySeparation(char charArray[]);


	TxtData();
	~TxtData();
};

