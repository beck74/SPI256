#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef _INT_SDK_LOADER_C_
#define INT_EXTERN//动态调用时不需要extern
#else
#define INT_EXTERN extern//静态调用时要有extern
#endif // _INT_SDK_LOADER_C_
	INT_EXTERN BOOL LoadPbIntDll(void);
	INT_EXTERN void UnloadPbIntDll(void);

	INT_EXTERN void(WINAPI *PbInit)(LPVOID pf, BYTE ChSel);
	INT_EXTERN void(WINAPI *PbUpdate)(LPVOID pf, LONG pbValue, BYTE ChSel);
#ifdef __cplusplus
}
#endif // __cplusplus
