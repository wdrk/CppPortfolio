#include "Base.h"


// 스택 헤드와 테일을 동적할당하고 TreeToStack 함수로 넘깁니다.
void Stack(TREEPIN * pTreeResult, LINKPIN *pDummyHead, LINKPIN *pDummyTail)
{
	// 스택을 구성하기 위해 pHead와 pTail을 동적할당하고
	// 연결해서 스택을 만듭니다.
	STACKPIN *StackHead = (STACKPIN *)calloc(1, sizeof(STACKPIN));
	STACKPIN *StackTail = (STACKPIN *)calloc(1, sizeof(STACKPIN));

	StackHead->Lowside = StackTail;
	StackTail->Highside = StackHead;
	
	//////////////////////////////////////////////////////////
	int nResult = 0;
	nResult = PushStack(pTreeResult, StackHead, nResult);
	//////////////////////////////////////////////////////////
		

	printf("계산 결과 : %d\n", nResult);
}


int PushStack(TREEPIN *pTreeResult, STACKPIN *pStackHead, int pnResult)
{

	// 루트의 좌 항이 정수가 아니면
	if (isdigit(pTreeResult->pLeft->pRoot->cData[0]) == 0)
	{
		// PushStack을 재귀호출합니다.
		PushStack(pTreeResult->pLeft, pStackHead, pnResult);
			
	}

	// 루트의 좌 항이 정수이면
	else
	{
		// 새로운 메모리를 동적 할당하고 스택에 Push합니다.
		STACKPIN *pNewStack = (STACKPIN *)calloc(1, sizeof(STACKPIN));
		pNewStack->nData = atoi(pTreeResult->pLeft->pRoot->cData);

		pNewStack->Lowside = pStackHead->Lowside;
		pStackHead->Lowside = pNewStack;
	}

	// 루트의 우 항이 연산자이면
	if (isdigit(pTreeResult->pRight->pRoot->cData[0]) == 0)
	{
		// 중복되지 않게 if문 설정해야함.
		if (pnResult != 0)
		{
			// PushStack을 재귀호출합니다.
			PushStack(pTreeResult->pRight, pStackHead, pnResult);
		}
	}

	// 루트의 좌 항이 정수이면
	else
	{
		// 스택에 Push합니다.
		STACKPIN *pNewStack = (STACKPIN *)calloc(1, sizeof(STACKPIN));
		pNewStack->nData = atoi(pTreeResult->pRight->pRoot->cData);

		pNewStack->Lowside = pStackHead->Lowside;
		pStackHead->Lowside = pNewStack;
	}

	// Push한 값으로 루트 항의 연산자에 맞는 연산을 합니다.

	pnResult += PopStack(pTreeResult, pStackHead, pnResult);

	return pnResult;
}




int PopStack(TREEPIN *pTreeResult, STACKPIN *pStackHead, int pnResult)
{

	// 스택에서 2개의 값을 POP 하여 현재 루트 노드의 연산자에 맞게 연산합니다.
	switch (pTreeResult->pRoot->cData[0])
	{
	case PLUS: 
		// putchar('+');
		pStackHead->Lowside->Lowside->nData = pStackHead->Lowside->Lowside->nData + pStackHead->Lowside->nData;
		break;

	case MINUS:
		// putchar('-');
		pStackHead->Lowside->Lowside->nData = pStackHead->Lowside->Lowside->nData - pStackHead->Lowside->nData;
		break;

	case MULTIPLY:
		//putchar('*');
		pStackHead->Lowside->Lowside->nData = pStackHead->Lowside->Lowside->nData * pStackHead->Lowside->nData;
		break;

	case DIVIDE:
		//putchar('/');
		pStackHead->Lowside->Lowside->nData = pStackHead->Lowside->Lowside->nData / pStackHead->Lowside->nData;
		break;
	}


	STACKPIN *pTmpForFree = pStackHead->Lowside;

	pStackHead->Lowside = pStackHead->Lowside->Lowside;
	pnResult = pStackHead->Lowside->nData;
	
	return pnResult;
}