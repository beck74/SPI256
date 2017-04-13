#pragma once
#ifdef DLLINT_API
#else
#define DLLINT_API extern "C" _declspec(dllexport)
#endif

DLLINT_API void WINAPI SPIProgram(HANDLE h, PDEVICE p, PBYTE pBuf, PVOID pf[], BYTE &ChSel);
DLLINT_API void WINAPI SPIErase(HANDLE h, PDEVICE p, PBYTE pBuf, PVOID pf[], BYTE &ChSel);
DLLINT_API void WINAPI SPIRead(HANDLE h, PDEVICE p, PBYTE pBuf, PVOID pf[], BYTE &ChSel);
DLLINT_API void WINAPI SPIVerify(HANDLE h, PDEVICE p, PBYTE pBuf, PVOID pf[], BYTE &ChSel);
DLLINT_API void WINAPI SPIBlank(HANDLE h, PDEVICE p, PBYTE pBuf, PVOID pf[], BYTE &ChSel);
DLLINT_API void WINAPI SPICheckID(HANDLE h, PDEVICE p, PBYTE pBuf, PVOID pf[], BYTE &ChSel);
DLLINT_API ULONG WINAPI GetDllInfo();

//Ãû×Ö¸Ä±à
#pragma comment(linker, "/EXPORT:getinfo=_GetDllInfo@0")
#pragma comment(linker, "/EXPORT:Erase=_SPIErase@20")
#pragma comment(linker, "/EXPORT:Program=_SPIProgram@20")
#pragma comment(linker, "/EXPORT:Read=_SPIRead@20")
#pragma comment(linker, "/EXPORT:Verify=_SPIVerify@20")
#pragma comment(linker, "/EXPORT:IDCheck=_SPICheckID@20")
#pragma comment(linker, "/EXPORT:Blank=_SPIBlank@20")
