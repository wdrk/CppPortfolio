#include "Base.h"
#include <conio.h>


/*---------------------------------------------------------------------------------------
#	개발자		정재형 (시간여행자)
#	개발환경		Visual Basic 2015   00322-50050-03552-AA166
				Visual C++	 2015	00322-50050-03552-AA166
#	개발시작		2018.11.07.
#	1 차완료		2018.11.18. PM 1:52
#	최종완료		2019.11.22. AM 2:39
#	설명			프로그램 시작 시 사용자로부터 양의 정수와 '+', '-' 연산자를 입력받고,
				유효성 검사를 거쳐 그 후 이진 트리를 구성하고 Post order로 데이터를 읽습니다.
---------------------------------------------------------------------------------------*/




int main(int argc, char* argv[])
{
	// szBuffer의 인덱스역할입니다.
	size_t	nInputCount	= 0;

	// 사용자로부터 입력을 받는 배열입니다.
	char szBuffer[MAXIMUM_ARRAY_LENGTH] = { 0 };

	Input(szBuffer, nInputCount);
	

	LINKPIN *DummyHead = (LINKPIN *)calloc(1, sizeof(LINKPIN));
	LINKPIN *DummyTail = (LINKPIN *)calloc(1, sizeof(LINKPIN));

	// 이중 연결 리스트를 구성하기위해 더미헤드와 더미테일을 연결합니다.
	DummyHead->pNext = DummyTail;
	DummyHead->pPrev = NULL;

	DummyTail->pPrev = DummyHead;
	DummyTail->pNext = NULL;

	// 입력값의 유효성을 검사하고 유효한 값이면 이중 연결 리스트에 추가합니다.
	bool TrueOrFalse;
	TrueOrFalse = ParseInput(DummyHead, DummyTail, szBuffer);

	// 유효하지 않은 값이면 프로그램을 종료합니다.
	if (false == TrueOrFalse)
	{
		printf("유효하지 않은 값입니다. 프로그램을 종료합니다.\n");
		return 0;
	}

	// 이중 연결 리스트 확인을 위해 출력합니다.
	PrintList(DummyHead, DummyTail);

	// 이진 트리를 구성합니다.
	TREEPIN *TreeResult = (TREEPIN *)calloc(1, sizeof(TREEPIN));
	TreeResult = MakeBinaryTree(DummyHead, DummyTail);

	// 이진 트리를 스택으로 구현해서 트리의 루트에 있는 연산자에 맞추어 계산합니다.
	Stack(TreeResult, DummyHead, DummyTail);

	// 결과 화면을 확인하기 위해 _getch()를 사용합니다.
	printf("프로그램을 종료합니다. 아무 키나 눌러주세요.\n");
	_getch();

	// 동적 할당 해제를 위한 함수입니다.
	FreePin(DummyHead, DummyTail);
	free(DummyHead);
	free(DummyTail);
	free(TreeResult);

	return 0;
}