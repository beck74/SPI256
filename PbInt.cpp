#include <Windows.h>
#include <stdio.h>
#define _INT_SDK_LOADER_C_
#include "PbInt.h"
typedef struct {
	char *name;
	FARPROC *ptr;
}LIB_FUNCT;

static HINSTANCE g_hPbIntLibrary = NULL;

BOOL LoadPbIntDll()
{
	LIB_FUNCT Func[] = {
		{"PbInit",(FARPROC*)&PbInit},
		{"PbUpdate",(FARPROC*)&PbUpdate},
		{NULL,NULL}
	};
	LIB_FUNCT *f;

	if ((g_hPbIntLibrary = LoadLibrary(TEXT("pb.dll"))) == NULL)
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
		*(f->ptr) = GetProcAddress((HMODULE)g_hPbIntLibrary, f->name);
		if (*(f->ptr) == NULL)
		{
			TCHAR szBuffer[20];
			wsprintf(szBuffer, TEXT("Failed to load \"%s\" Function\n"), f->name);
			MessageBox(NULL, szBuffer, NULL, MB_ICONERROR);
		}
		f++;
	}
	return TRUE;
}

void UnloadPbIntDll(void)
{
	if (g_hPbIntLibrary != NULL)
	{
		FreeLibrary(g_hPbIntLibrary);
		g_hPbIntLibrary = NULL;
	}
}