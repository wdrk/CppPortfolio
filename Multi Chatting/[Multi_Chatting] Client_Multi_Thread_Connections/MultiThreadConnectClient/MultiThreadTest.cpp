#include <iostream>
#include <conio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")
#include <WS2tcpip.h>
#include <tchar.h>
#pragma warning(disable : 4996)

// 메세지를 몇 번 보낼지 설정하는 상수입니다.
#define LOOP_COUNT 10

// 접속할 서버의 IP 주소를 설정하는 상수입니다.
#define IP_ADDRESS "192.168.0.0"

DWORD WINAPI Thread1(LPVOID pParam)
{
	SOCKET hSocket1 = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	::connect(hSocket1, (SOCKADDR*)&svraddr, sizeof(svraddr));

	int i = 0;
	char szMessage[32] = "11111111111111111111";
	int nLength = strlen(szMessage);
	++nLength;

	for (i = 0; i < LOOP_COUNT; ++i)
	{
		::send(hSocket1, szMessage, nLength, 0);
		Sleep(1);
	}

	_tprintf(_T("Thread [ 1 ] Count : %d\n"), i);
	OutputDebugStringA("[ Thread1 Send Complete ]\n");
	return 0;
}

DWORD WINAPI Thread2(LPVOID pParam)
{
	SOCKET hSocket2 = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	::connect(hSocket2, (SOCKADDR*)&svraddr, sizeof(svraddr));

	int i = 0;
	char szMessage[32] = "22222222222222222222";
	int nLength = strlen(szMessage);
	++nLength;

	for (i = 0; i < LOOP_COUNT; ++i)
	{
		::send(hSocket2, szMessage, strlen(szMessage) + 1, 0);
	}
 
	_tprintf(_T("Thread [ 2 ] Count : %d\n"), i);
	OutputDebugStringA("[ Thread2 Send Complete ]\n");
	return 0;
}

DWORD WINAPI Thread3(LPVOID pParam)
{
	SOCKET hSocket3 = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	::connect(hSocket3, (SOCKADDR*)&svraddr, sizeof(svraddr));

	int i = 0;
	char szMessage[32] = "33333333333333333333";
	int nLength = strlen(szMessage);
	++nLength;

	for (i = 0; i < LOOP_COUNT; ++i)
	{
		::send(hSocket3, szMessage, strlen(szMessage) + 1, 0);
	}

	_tprintf(_T("Thread [ 3 ] Count : %d\n"), i);
	OutputDebugStringA("[ Thread3 Send Complete ]\n");
	return 0;
}

DWORD WINAPI Thread4(LPVOID pParam)
{
	SOCKET hSocket1 = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	::connect(hSocket1, (SOCKADDR*)&svraddr, sizeof(svraddr));

	int i = 0;
	char szMessage[32] = "44444444444444444444";
	int nLength = strlen(szMessage);
	++nLength;

	for (i = 0; i < LOOP_COUNT; ++i)
	{
		::send(hSocket1, szMessage, strlen(szMessage) + 1, 0);
	}

	_tprintf(_T("Thread [ 4 ] Count : %d\n"), i);
	OutputDebugStringA("[ Thread4 Send Complete ]\n");
	return 0;
}

DWORD WINAPI Thread5(LPVOID pParam)
{
	SOCKET hSocket2 = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	::connect(hSocket2, (SOCKADDR*)&svraddr, sizeof(svraddr));

	int i = 0;
	char szMessage[32] = "55555555555555555555";
	int nLength = strlen(szMessage);
	++nLength;

	for (i = 0; i < LOOP_COUNT; ++i)
	{
		::send(hSocket2, szMessage, strlen(szMessage) + 1, 0);
	}
 
	_tprintf(_T("Thread [ 5 ] Count : %d\n"), i);
	OutputDebugStringA("[ Thread5 Send Complete ]\n");
	return 0;
}

DWORD WINAPI Thread6(LPVOID pParam)
{
	SOCKET hSocket3 = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	::connect(hSocket3, (SOCKADDR*)&svraddr, sizeof(svraddr));

	int i = 0;
	char szMessage[32] = "66666666666666666666";
	int nLength = strlen(szMessage);
	++nLength;

	for (i = 0; i < LOOP_COUNT; ++i)
	{
		::send(hSocket3, szMessage, strlen(szMessage) + 1, 0);
	}

	_tprintf(_T("Thread [ 6 ] Count : %d\n"), i);
	OutputDebugStringA("[ Thread6 Send Complete ]\n");
	return 0;
}
DWORD WINAPI Thread7(LPVOID pParam)
{
	SOCKET hSocket1 = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	::connect(hSocket1, (SOCKADDR*)&svraddr, sizeof(svraddr));

	int i = 0;
	char szMessage[32] = "77777777777777777777";

	int nLength = strlen(szMessage);
	++nLength;
	for (i = 0; i < LOOP_COUNT; ++i)
	{
		::send(hSocket1, szMessage, strlen(szMessage) + 1, 0);
	}

	_tprintf(_T("Thread [ 7 ] Count : %d\n"), i);
	OutputDebugStringA("[ Thread7 Send Complete ]\n");
	return 0;
}

DWORD WINAPI Thread8(LPVOID pParam)
{
	SOCKET hSocket2 = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	::connect(hSocket2, (SOCKADDR*)&svraddr, sizeof(svraddr));

	int i = 0;
	char szMessage[32] = "88888888888888888888";

	int nLength = strlen(szMessage);
	++nLength;
	for (i = 0; i < LOOP_COUNT; ++i)
	{
		::send(hSocket2, szMessage, strlen(szMessage) + 1, 0);
	}
 
	_tprintf(_T("Thread [ 8 ] Count : %d\n"), i);
	OutputDebugStringA("[ Thread8 Send Complete ]\n");
	return 0;
}

DWORD WINAPI Thread9(LPVOID pParam)
{
	SOCKET hSocket3 = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	::connect(hSocket3, (SOCKADDR*)&svraddr, sizeof(svraddr));

	int i = 0;
	char szMessage[32] = "99999999999999999999";

	int nLength = strlen(szMessage);
	++nLength;
	for (i = 0; i < LOOP_COUNT; ++i)
	{
		::send(hSocket3, szMessage, strlen(szMessage) + 1, 0);
	}

	_tprintf(_T("Thread [ 9 ] Count : %d\n"), i);
	OutputDebugStringA("[ Thread9 Send Complete ]\n");
	return 0;
}

DWORD WINAPI Thread10(LPVOID pParam)
{
	SOCKET hSocket3 = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(25000);
	svraddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	::connect(hSocket3, (SOCKADDR*)&svraddr, sizeof(svraddr));

	int i = 0;
	char szMessage[32] = "1111111111000000000";

	int nLength = strlen(szMessage);
	++nLength;
	for (i = 0; i < LOOP_COUNT; ++i)
	{
		::send(hSocket3, szMessage, strlen(szMessage) + 1, 0);
	}

	_tprintf(_T("Thread [ 10 ] Count : %d\n"), i);
	OutputDebugStringA("[ Thread10 Send Complete ]\n");
	return 0;
}

auto __cdecl main(int argc, char* argv[]) -> int
{
	WSADATA wsa = { 0 };
	::WSAStartup(0x0202, &wsa);

	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0);

	printf("Input Any Key");
	_getch();
	putchar('\n');

	HANDLE hThreadArray[10] = { nullptr };

	hThreadArray[0] = ::CreateThread(NULL, 0, Thread1, (LPVOID)hSocket, 0, NULL);
	char szBuffer[32] = "**** Thread [ 1 ] Running ****";
	OutputDebugStringA(szBuffer);

	hThreadArray[1] = ::CreateThread(NULL, 0, Thread2, (LPVOID)hSocket, 0, NULL);
	strcpy_s(szBuffer, sizeof(szBuffer), "**** Thread [ 2 ] Running ****");
	OutputDebugStringA(szBuffer);

	hThreadArray[2] = ::CreateThread(NULL, 0, Thread3, (LPVOID)hSocket, 0, NULL);
	strcpy_s(szBuffer, sizeof(szBuffer), "**** Thread [ 3 ] Running ****");
	OutputDebugStringA(szBuffer);

	hThreadArray[3] = ::CreateThread(NULL, 0, Thread4, (LPVOID)hSocket, 0, NULL);
	strcpy_s(szBuffer, sizeof(szBuffer), "**** Thread [ 4 ] Running ****");
	OutputDebugStringA(szBuffer);

	hThreadArray[4] = ::CreateThread(NULL, 0, Thread5, (LPVOID)hSocket, 0, NULL);
	strcpy_s(szBuffer, sizeof(szBuffer), "**** Thread [ 5 ] Running ****");
	OutputDebugStringA(szBuffer);

	hThreadArray[5] = ::CreateThread(NULL, 0, Thread6, (LPVOID)hSocket, 0, NULL);
	strcpy_s(szBuffer, sizeof(szBuffer), "**** Thread [ 6 ] Running ****");
	OutputDebugStringA(szBuffer);

	hThreadArray[6] = ::CreateThread(NULL, 0, Thread7, (LPVOID)hSocket, 0, NULL);
	strcpy_s(szBuffer, sizeof(szBuffer), "**** Thread [ 7 ] Running ****");
	OutputDebugStringA(szBuffer);

	hThreadArray[7] = ::CreateThread(NULL, 0, Thread8, (LPVOID)hSocket, 0, NULL);
	strcpy_s(szBuffer, sizeof(szBuffer), "**** Thread [ 8 ] Running ****");
	OutputDebugStringA(szBuffer);

	hThreadArray[8] = ::CreateThread(NULL, 0, Thread9, (LPVOID)hSocket, 0, NULL);
	strcpy_s(szBuffer, sizeof(szBuffer), "**** Thread [ 9 ] Running ****");
	OutputDebugStringA(szBuffer);

	hThreadArray[9] = ::CreateThread(NULL, 0, Thread10, (LPVOID)hSocket, 0, NULL);
	strcpy_s(szBuffer, sizeof(szBuffer), "**** Thread [ 10 ] Running ****");
	OutputDebugStringA(szBuffer);

	DWORD dwTemp = WaitForMultipleObjects(10, hThreadArray, true, INFINITE);
	
	::shutdown(hSocket, SD_BOTH);
	::closesocket(hSocket);
	::Sleep(100);
	::WSACleanup();
//	_tprintf(_T("dwTemp : %d\n"), dwTemp);
	OutputDebugStringA("[[[[[[[[[[ Good Bye ]]]]]]]]]]]");

	return 0;
}