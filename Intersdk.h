#pragma once
#include <Windows.h>
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef _INT_SDK_LOADER_C_
#define	INT_EXTERN
#else
#define INT_EXTERN extern
#endif

	INT_EXTERN bool LoadInterDll(void);
	INT_EXTERN void UnloadInterDll(void);

	INT_EXTERN bool (WINAPI *WriteFPGA)(HANDLE h, PVOID buf, ULONG len);
	INT_EXTERN bool (WINAPI *WriteCPLD)(HANDLE h, WORD address, WORD data);
	INT_EXTERN bool (WINAPI *ReadDMA)(HANDLE h, PVOID p, ULONG len);
	INT_EXTERN bool (WINAPI *ReadCPLD)(HANDLE h, WORD address, BYTE &val);
	INT_EXTERN void (WINAPI *WriteDMA)(HANDLE h, PVOID buf, ULONG len, BYTE transferType);
	INT_EXTERN void (WINAPI *WriteDMANotSetLength)(HANDLE h, PVOID buf, INT len);

#ifdef __cplusplus
}
#endif // __cplusplus