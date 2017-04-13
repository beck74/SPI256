#include <stdio.h>
#include <Windows.h>
#include "RegBuffer.h"



CRegBuffer::CRegBuffer()
{
	index = 0;
	memset(data, 0, sizeof(data));
}


CRegBuffer::~CRegBuffer()
{
}

void CRegBuffer::Init()
{
	index = 0;
}

void CRegBuffer::Push(int addr, int value)
{
	if (index >= 256)
	{
		index = 0;
		MessageBox(NULL, "error: regBuf overflow.", NULL, MB_ICONERROR);
		return;
	}
	memcpy(&data[index], &addr, 2);
	memcpy(&data[index + 2], &value, 2);
	index += 4;
}

int CRegBuffer::GetLength()
{
	return index;
}

char * CRegBuffer::GetData()
{
	return data;
}
