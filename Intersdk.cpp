#include <Windows.h>
#define _INT_SDK_LOADER_C_

#include "Intersdk.h"
#include <stdio.h>

#define __DLL_FILE_FULL_PATH__ (TEXT("INTER.dll"))

typedef struct {
	char *name;
	FARPROC *ptr;
}LIB_FUNCT;

static HINSTANCE g_hInterLibrary = NULL;//¶¯Ì¬Á´½Ó¿â¾ä±ú

bool LoadInterDll(void)
{
	LIB_FUNCT Func[] = {
		{ "WriteFPGA",(FARPROC*)&WriteFPGA },
		{ "WriteCPLD",(FARPROC*)&WriteCPLD },
		{ "ReadDMA",(FARPROC*)&ReadDMA },
		{ "ReadCPLD",(FARPROC*)&ReadCPLD },
		{ "WriteDMA",(FARPROC*)&WriteDMA },
		{ "WriteDMANotSetLength",(FARPROC*)&WriteDMANotSetLength },
		{ NULL, NULL }
	};
	LIB_FUNCT *f;

	if ((g_hInterLibrary = LoadLibrary(TEXT("INTER.dll"))) == NULL)
	{
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL
		);
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, NULL, MB_ICONERROR);
		LocalFree(lpMsgBuf);
		return FALSE;
	}

	f = &Func[0];
	while (f->ptr != NULL)
	{
		*(f->ptr) = GetProcAddress((HMODULE)g_hInterLibrary, f->name);
		if (*(f->ptr) == NULL)
		{
			TCHAR szBuffer[30];
			wsprintf(szBuffer, TEXT("Failed to load \"%s\" Function\n"), f->name);
			MessageBox(NULL, szBuffer,NULL,MB_ICONERROR);
		}
		f++;
	}
	return true;
}

void UnloadInterDll(void)
{
	if (g_hInterLibrary != NULL)
	{
		FreeLibrary(g_hInterLibrary);
		g_hInterLibrary = NULL;
	}
}
