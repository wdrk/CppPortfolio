#include <iostream>
#include <wchar.h>
#include <Windows.h>
#include <tchar.h>
#include <string>
#pragma comment(lib, "Ws2_32")


#define DEF_SRC_DLL				("Ws2_32.dll")
#define DEF_SRC_FUNCTION		("send")

typedef BOOL(WINAPI *pfsend)(SOCKET S, const char *buf, int len, int flags);

// 전역 변수
BYTE g_pOrgBytes[5] = { 0 };

BOOL HookFunction(LPCSTR szDllName, LPCSTR szFuncName, PROC pfNew)
{
	PROC pfOrg = nullptr;
	DWORD dwOldProtect, dwAddress;
	BYTE pBuf[5] = { 0xE9, 0, };

	// Hooking의 대상인 API의 주소를 구한다.
	pfOrg = (PROC)GetProcAddress(GetModuleHandleA(szDllName), szFuncName);
	if (nullptr != pfOrg)
		OutputDebugString(_T("GetProcAddress 성공"));

	PBYTE pByte = (PBYTE)pfOrg;
	
	// 이미 Hooking 상태라면
	if (0xE9 == pByte[0])
	{
		OutputDebugString(_T("이미 Hooking 상태입니다."));
		return false;
	}

	// 5 byte 패치를 위하여 메모리에 Write 속성을 추가한다.
	if( VirtualProtect((LPVOID)pfOrg, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect) )
		OutputDebugString(_T("VirtualProtect로 Process에 Write 속성 추가 성공"));

	// 기존의 어셈블리 코드 (5byte) 백업한다.
	memcpy(g_pOrgBytes, pfOrg, 5);
	if (NULL != g_pOrgBytes)
		OutputDebugString(_T("기존의 어셈블리 코드 백업 성공"));

	// jmp 하는 주소를 계산한다.
	// '입력할 주소' = '점프할 주소' - 'JMP 명령을 입력할 주소' - '명령어 길이 5'
	dwAddress = (DWORD)pfNew - (DWORD)pfOrg - 5;
	memcpy(&pBuf[1], &dwAddress, 4);

	// Hook - 5byte 패치 (jmp XXXX)
	memcpy(pfOrg, pBuf, 5);
	OutputDebugString(_T("jmp 패치 후 값 : "));
	char szBuffer[6] = { 0 };
	memcpy_s(szBuffer, sizeof(char) * 5, (char*)pfOrg, sizeof(char) * 5);
	_tprintf(L"%p\n", szBuffer);
	_tprintf(L"%p\n", pfOrg);

	// 메모리 속성을 원래대로 바꾼다.
	VirtualProtect((LPVOID)pfOrg, 5, dwOldProtect, &dwOldProtect);
	OutputDebugString(_T("VirtualProtect 함수로 메모리 속성을 읽기전용으로 변경했습니다.\n"));

	return true;
}

BOOL UnHookFunction(LPCSTR szDllName, LPCSTR szFuncName)
{
	PROC pFunc;
	DWORD dwOldProtect;

	// API 주소를 구한다.
	if (pFunc = GetProcAddress(GetModuleHandleA(szDllName), szFuncName))
		OutputDebugString(_T("[ UnHook ] GetProcAddress Success"));

	PBYTE pByte = (PBYTE)pFunc;
	
	if (0xE9 != pByte[0])
		return false;

	// 원래 코드(5byte)를 덮어쓰기 위해서 메모리에 Write 속성을 추가한다.
	if (VirtualProtect((LPVOID)pFunc, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect))
		OutputDebugString(_T("[ UnHook ] VirtualProtect Write 속성 추가 성공"));

	// UnHook을 하기 위해 예전 명령어를 입력한다.
	memcpy(pFunc, g_pOrgBytes, 5);
	char szBuffer[6] = { 0 };
	memcpy_s(szBuffer, sizeof(char) * 5, pFunc, sizeof(char) * 5);
	OutputDebugStringA(szBuffer);

	// 메모리 권한을 복원한다.
	if (VirtualProtect((LPVOID)pFunc, 5, dwOldProtect, &dwOldProtect))
		OutputDebugString(_T("[ UnHook ] VirtualProtect로 메모리 권한 복원 성공"));

	
	return true;
}

BOOL WINAPI MySend(SOCKET s, const char *buf, int len, int flags)
{
	OutputDebugString(_T("MySend 진입했습니다."));

	// Hook이 걸린 상태로 send를 호출하면 다시 MySend로 진입하므로
	// send 함수를 UnHook해야 send 함수가 원래대로 작동합니다.
	UnHookFunction(DEF_SRC_DLL, DEF_SRC_FUNCTION);

	char szBuffer[128] = { 0 };

	memcpy_s(szBuffer, sizeof(char) * len, buf, sizeof(char) * len);
	OutputDebugStringA(buf);

	::send(s, buf, len, flags);

	// send 함수를 정상작동 시킨 후 다시 Hook을 겁니다.
	HookFunction(DEF_SRC_DLL, DEF_SRC_FUNCTION, (PROC)MySend);
	return true;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		OutputDebugString(_T("Run HookFunction\n"));
		HookFunction(DEF_SRC_DLL, DEF_SRC_FUNCTION, (PROC)MySend);
		OutputDebugString(_T("End HookFunction\n"));
		break;
	case DLL_PROCESS_DETACH:
		OutputDebugString(_T("Run UnHook Function"));
		UnHookFunction(DEF_SRC_DLL, DEF_SRC_FUNCTION);
		OutputDebugString(_T("End UnHook Function"));
		break;
	}

	return true;
}