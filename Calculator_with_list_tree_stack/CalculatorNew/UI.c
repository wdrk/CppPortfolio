#include "Base.h"


bool Input(char *pszBuffer, size_t nInputCount)
{
	printf("양의 정수와 '+', '-' 연산자를 사용하여 계산식을 입력하세요 : ");

	// 사용자 입력값의 갯수가 szBuffer의 경계를 넘어가면 프로그램을 종료합니다.
	do
	{
		pszBuffer[nInputCount] = getchar();
		++nInputCount;

	} while (pszBuffer[nInputCount - 1] != '\n' && nInputCount != INPUT_BOUNDARY);

	// 사용자가 szBuffer의 경계를 초과하는 입력을 한 경우
	if (nInputCount == INPUT_BOUNDARY)
	{
		printf("[ ERROR 01 : 입력 범위 초과로 종료 ]");
		while ('\0' != stdin)
			getchar();

		return false;
	}
	return true;
}

void PrintList(LINKPIN *pDummyHead, LINKPIN *pDummyTail)
{
	LINKPIN *pTmpHead = pDummyHead->pNext;
	printf("이중 연결 리스트 확인 : ");

	int i = 0;

	while (pTmpHead != pDummyTail)
	{
		while (pTmpHead->cData[i] != '\0')
		{
			printf("%c ", pTmpHead->cData[i]);
			++i;
		}

		pTmpHead = pTmpHead->pNext;
		i = 0;
	}

	putchar('\n');
}