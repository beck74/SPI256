#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef _INT_SDK_LOADER_C_
#define INT_EXTERN//��̬����ʱ����Ҫextern
#else
#define INT_EXTERN extern//��̬����ʱҪ��extern
#endif // _INT_SDK_LOADER_C_
	INT_EXTERN BOOL LoadPbIntDll(void);
	INT_EXTERN void UnloadPbIntDll(void);

	INT_EXTERN void(WINAPI *PbInit)(LPVOID pf, BYTE ChSel);
	INT_EXTERN void(WINAPI *PbUpdate)(LPVOID pf, LONG pbValue, BYTE ChSel);
#ifdef __cplusplus
}
#endif // __cplusplus
