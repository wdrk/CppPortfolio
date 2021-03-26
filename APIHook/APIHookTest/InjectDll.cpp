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


	// #1. dwPID를 이용하여 대상 프로세스의 HANDLE을 구한다.
	if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID)))
	{
		_tprintf(L"OpenProcess(%d) failed!!! [%d]\n", dwPID, GetLastError());
		return false;
	}

	if (NULL == hProcess)
		_tprintf(_T("hProcess is NULL.\n"));

	_tprintf(_T("hProcess value : %p\n"), hProcess);

	// #2. 대상 프로세스의 메모리에 szDllName 크기만큼 메모리를 할당한다.
	pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE);
	_tprintf(_T("VirtualAllocEx Memory Address [ pRemoteBuf : %p ]\n"), &pRemoteBuf);
	_tprintf(_T("VirtualAllocEx Memory Value [ pRemoteBuf : %p ]\n"), pRemoteBuf);

	// #3. 할당 받은 메모리에 Injection 할 DLL 경로를 쓴다.
	WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)szDllPath, dwBufSize, NULL);

	// #4. LoadLibraryW() API 주소를 구한다.
	hMod = GetModuleHandle(L"kernel32.dll");
	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryW");

	// #5. 프로세스에 스레드를 실행
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