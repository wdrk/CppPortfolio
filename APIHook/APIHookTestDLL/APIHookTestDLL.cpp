#include <iostream>
#include <wchar.h>
#include <Windows.h>
#include <tchar.h>
#include <string>
#pragma comment(lib, "Ws2_32")


#define DEF_SRC_DLL				("Ws2_32.dll")
#define DEF_SRC_FUNCTION		("send")

typedef BOOL(WINAPI *pfsend)(SOCKET S, const char *buf, int len, int flags);

// ���� ����
BYTE g_pOrgBytes[5] = { 0 };

BOOL HookFunction(LPCSTR szDllName, LPCSTR szFuncName, PROC pfNew)
{
	PROC pfOrg = nullptr;
	DWORD dwOldProtect, dwAddress;
	BYTE pBuf[5] = { 0xE9, 0, };

	// Hooking�� ����� API�� �ּҸ� ���Ѵ�.
	pfOrg = (PROC)GetProcAddress(GetModuleHandleA(szDllName), szFuncName);
	if (nullptr != pfOrg)
		OutputDebugString(_T("GetProcAddress ����"));

	PBYTE pByte = (PBYTE)pfOrg;
	
	// �̹� Hooking ���¶��
	if (0xE9 == pByte[0])
	{
		OutputDebugString(_T("�̹� Hooking �����Դϴ�."));
		return false;
	}

	// 5 byte ��ġ�� ���Ͽ� �޸𸮿� Write �Ӽ��� �߰��Ѵ�.
	if( VirtualProtect((LPVOID)pfOrg, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect) )
		OutputDebugString(_T("VirtualProtect�� Process�� Write �Ӽ� �߰� ����"));

	// ������ ����� �ڵ� (5byte) ����Ѵ�.
	memcpy(g_pOrgBytes, pfOrg, 5);
	if (NULL != g_pOrgBytes)
		OutputDebugString(_T("������ ����� �ڵ� ��� ����"));

	// jmp �ϴ� �ּҸ� ����Ѵ�.
	// '�Է��� �ּ�' = '������ �ּ�' - 'JMP ����� �Է��� �ּ�' - '��ɾ� ���� 5'
	dwAddress = (DWORD)pfNew - (DWORD)pfOrg - 5;
	memcpy(&pBuf[1], &dwAddress, 4);

	// Hook - 5byte ��ġ (jmp XXXX)
	memcpy(pfOrg, pBuf, 5);
	OutputDebugString(_T("jmp ��ġ �� �� : "));
	char szBuffer[6] = { 0 };
	memcpy_s(szBuffer, sizeof(char) * 5, (char*)pfOrg, sizeof(char) * 5);
	_tprintf(L"%p\n", szBuffer);
	_tprintf(L"%p\n", pfOrg);

	// �޸� �Ӽ��� ������� �ٲ۴�.
	VirtualProtect((LPVOID)pfOrg, 5, dwOldProtect, &dwOldProtect);
	OutputDebugString(_T("VirtualProtect �Լ��� �޸� �Ӽ��� �б��������� �����߽��ϴ�.\n"));

	return true;
}

BOOL UnHookFunction(LPCSTR szDllName, LPCSTR szFuncName)
{
	PROC pFunc;
	DWORD dwOldProtect;

	// API �ּҸ� ���Ѵ�.
	if (pFunc = GetProcAddress(GetModuleHandleA(szDllName), szFuncName))
		OutputDebugString(_T("[ UnHook ] GetProcAddress Success"));

	PBYTE pByte = (PBYTE)pFunc;
	
	if (0xE9 != pByte[0])
		return false;

	// ���� �ڵ�(5byte)�� ����� ���ؼ� �޸𸮿� Write �Ӽ��� �߰��Ѵ�.
	if (VirtualProtect((LPVOID)pFunc, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect))
		OutputDebugString(_T("[ UnHook ] VirtualProtect Write �Ӽ� �߰� ����"));

	// UnHook�� �ϱ� ���� ���� ��ɾ �Է��Ѵ�.
	memcpy(pFunc, g_pOrgBytes, 5);
	char szBuffer[6] = { 0 };
	memcpy_s(szBuffer, sizeof(char) * 5, pFunc, sizeof(char) * 5);
	OutputDebugStringA(szBuffer);

	// �޸� ������ �����Ѵ�.
	if (VirtualProtect((LPVOID)pFunc, 5, dwOldProtect, &dwOldProtect))
		OutputDebugString(_T("[ UnHook ] VirtualProtect�� �޸� ���� ���� ����"));

	
	return true;
}

BOOL WINAPI MySend(SOCKET s, const char *buf, int len, int flags)
{
	OutputDebugString(_T("MySend �����߽��ϴ�."));

	// Hook�� �ɸ� ���·� send�� ȣ���ϸ� �ٽ� MySend�� �����ϹǷ�
	// send �Լ��� UnHook�ؾ� send �Լ��� ������� �۵��մϴ�.
	UnHookFunction(DEF_SRC_DLL, DEF_SRC_FUNCTION);

	char szBuffer[128] = { 0 };

	memcpy_s(szBuffer, sizeof(char) * len, buf, sizeof(char) * len);
	OutputDebugStringA(buf);

	::send(s, buf, len, flags);

	// send �Լ��� �����۵� ��Ų �� �ٽ� Hook�� �̴ϴ�.
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