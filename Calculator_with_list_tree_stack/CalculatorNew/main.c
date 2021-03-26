#include "Base.h"
#include <conio.h>


/*---------------------------------------------------------------------------------------
#	������		������ (�ð�������)
#	����ȯ��		Visual Basic 2015   00322-50050-03552-AA166
				Visual C++	 2015	00322-50050-03552-AA166
#	���߽���		2018.11.07.
#	1 ���Ϸ�		2018.11.18. PM 1:52
#	�����Ϸ�		2019.11.22. AM 2:39
#	����			���α׷� ���� �� ����ڷκ��� ���� ������ '+', '-' �����ڸ� �Է¹ް�,
				��ȿ�� �˻縦 ���� �� �� ���� Ʈ���� �����ϰ� Post order�� �����͸� �н��ϴ�.
---------------------------------------------------------------------------------------*/




int main(int argc, char* argv[])
{
	// szBuffer�� �ε��������Դϴ�.
	size_t	nInputCount	= 0;

	// ����ڷκ��� �Է��� �޴� �迭�Դϴ�.
	char szBuffer[MAXIMUM_ARRAY_LENGTH] = { 0 };

	Input(szBuffer, nInputCount);
	

	LINKPIN *DummyHead = (LINKPIN *)calloc(1, sizeof(LINKPIN));
	LINKPIN *DummyTail = (LINKPIN *)calloc(1, sizeof(LINKPIN));

	// ���� ���� ����Ʈ�� �����ϱ����� �������� ���������� �����մϴ�.
	DummyHead->pNext = DummyTail;
	DummyHead->pPrev = NULL;

	DummyTail->pPrev = DummyHead;
	DummyTail->pNext = NULL;

	// �Է°��� ��ȿ���� �˻��ϰ� ��ȿ�� ���̸� ���� ���� ����Ʈ�� �߰��մϴ�.
	bool TrueOrFalse;
	TrueOrFalse = ParseInput(DummyHead, DummyTail, szBuffer);

	// ��ȿ���� ���� ���̸� ���α׷��� �����մϴ�.
	if (false == TrueOrFalse)
	{
		printf("��ȿ���� ���� ���Դϴ�. ���α׷��� �����մϴ�.\n");
		return 0;
	}

	// ���� ���� ����Ʈ Ȯ���� ���� ����մϴ�.
	PrintList(DummyHead, DummyTail);

	// ���� Ʈ���� �����մϴ�.
	TREEPIN *TreeResult = (TREEPIN *)calloc(1, sizeof(TREEPIN));
	TreeResult = MakeBinaryTree(DummyHead, DummyTail);

	// ���� Ʈ���� �������� �����ؼ� Ʈ���� ��Ʈ�� �ִ� �����ڿ� ���߾� ����մϴ�.
	Stack(TreeResult, DummyHead, DummyTail);

	// ��� ȭ���� Ȯ���ϱ� ���� _getch()�� ����մϴ�.
	printf("���α׷��� �����մϴ�. �ƹ� Ű�� �����ּ���.\n");
	_getch();

	// ���� �Ҵ� ������ ���� �Լ��Դϴ�.
	FreePin(DummyHead, DummyTail);
	free(DummyHead);
	free(DummyTail);
	free(TreeResult);

	return 0;
}