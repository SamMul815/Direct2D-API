#include "stdafx.h"
#include "TxtData.h"


TxtData::TxtData()
{
}


TxtData::~TxtData()
{
}

HRESULT TxtData::Init() { return S_OK; }
void TxtData::Release() {}

//세이브
void TxtData::TxtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[128];
	DWORD write;

	strncpy_s(str, 128, VectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

char* TxtData::VectorArrayCombine(vector<string> vArray)
{
	char str[128];

	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray.size()) strcat(str, ",");
	}

	return str;
}

//로드
vector<string> TxtData::TxtLoad(const char* loadFileName)
{
	HANDLE file;

	char str[2500];
//	char *str;
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 2500, &read, NULL);

	//ReadFile(file, str,, &read, NULL);
	CloseHandle(file);

	return CharArraySeparation(str);
}

vector<string> TxtData::CharArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	char* separator = ",";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
