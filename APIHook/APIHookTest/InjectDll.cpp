#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <string>

BOOL InjectDll(DWORD dwPID, LPCTSTR szDllPath)
{
	HANDLE hProcess = NULL, hThread = NULL;
	HMODULE hMod = NULL;
	LPVOID pRemoteBuf = NULL;
	DWORD dwBufSize = (DWORD)(_tcslen(szDllPath) + 1) * sizeof(TCHAR);
	LPTHREAD_START_ROUTINE pThreadProc;

	_tprintf(_T("PID : %d\n"), dwPID);
	_tprintf(_T("DLL Path : %s\n"), szDllPath);
	_tprintf(_T("Length of DLL Path [ dwBufSize : %d ]\n"), dwBufSize);


	// #1. dwPID�� �̿��Ͽ� ��� ���μ����� HANDLE�� ���Ѵ�.
	if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID)))
	{
		_tprintf(L"OpenProcess(%d) failed!!! [%d]\n", dwPID, GetLastError());
		return false;
	}

	if (NULL == hProcess)
		_tprintf(_T("hProcess is NULL.\n"));

	_tprintf(_T("hProcess value : %p\n"), hProcess);

	// #2. ��� ���μ����� �޸𸮿� szDllName ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE);
	_tprintf(_T("VirtualAllocEx Memory Address [ pRemoteBuf : %p ]\n"), &pRemoteBuf);
	_tprintf(_T("VirtualAllocEx Memory Value [ pRemoteBuf : %p ]\n"), pRemoteBuf);

	// #3. �Ҵ� ���� �޸𸮿� Injection �� DLL ��θ� ����.
	WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)szDllPath, dwBufSize, NULL);

	// #4. LoadLibraryW() API �ּҸ� ���Ѵ�.
	hMod = GetModuleHandle(L"kernel32.dll");
	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryW");

	// #5. ���μ����� �����带 ����
	hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pRemoteBuf, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return true;
}

int _tmain(int argc, TCHAR* argv[])
{
	if (3 != argc)
	{
		_tprintf(L"USAGE : %s pid dll_path\n", argv[0]);
		return 1;
	}

	// Inject DLL
	if (InjectDll((DWORD)_tstol(argv[1]), argv[2]))
		_tprintf(L"InjectDll(\"%s\") success!!!\n", argv[2]);
	else
		_tprintf(L"InjectDll(\"%s\") failed!!!\n", argv[2]);

	return 0;
}