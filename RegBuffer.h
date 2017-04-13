#pragma once
class CRegBuffer
{
public:
	CRegBuffer();
	~CRegBuffer();
	void Init();
	void Push(int addr, int value);
	int GetLength();
	char * GetData();
private:
	int index;
	char data[256];
};

