#include "Base.h"


bool Input(char *pszBuffer, size_t nInputCount)
{
	printf("���� ������ '+', '-' �����ڸ� ����Ͽ� ������ �Է��ϼ��� : ");

	// ����� �Է°��� ������ szBuffer�� ��踦 �Ѿ�� ���α׷��� �����մϴ�.
	do
	{
		pszBuffer[nInputCount] = getchar();
		++nInputCount;

	} while (pszBuffer[nInputCount - 1] != '\n' && nInputCount != INPUT_BOUNDARY);

	// ����ڰ� szBuffer�� ��踦 �ʰ��ϴ� �Է��� �� ���
	if (nInputCount == INPUT_BOUNDARY)
	{
		printf("[ ERROR 01 : �Է� ���� �ʰ��� ���� ]");
		while ('\0' != stdin)
			getchar();

		return false;
	}
	return true;
}

void PrintList(LINKPIN *pDummyHead, LINKPIN *pDummyTail)
{
	LINKPIN *pTmpHead = pDummyHead->pNext;
	printf("���� ���� ����Ʈ Ȯ�� : ");

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