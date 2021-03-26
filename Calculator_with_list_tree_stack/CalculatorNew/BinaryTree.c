#include "Base.h"


// 이진 트리를 Postorder로 읽는 함수입니다.
TREEPIN *Postorder(TREEPIN *pSearchTree, LINKPIN *pDummyTail, LINKPIN *pFinishedRoot)
{
	// 왼 항부터 이진트리 작업 시작
	// 루트의 좌 항이 NULL이 아니면
	if (pSearchTree->pRoot->pPrev != NULL)
	{
		// 루트의 좌 항이 연산자가 아니면
		if (isdigit(pSearchTree->pRoot->pPrev->cData[0]) != 0)
		{
			TREEPIN *pNewPin = (TREEPIN *)calloc(1, sizeof(TREEPIN));
			pSearchTree->pLeft = pNewPin;
			pNewPin->pRoot = pSearchTree->pRoot->pPrev;
			printf("%d", atoi(pNewPin->pRoot->cData));
		}

		// 연산자이면
		else
		{
			TREEPIN *pNewPin = (TREEPIN *)calloc(1, sizeof(TREEPIN));
			pNewPin->pLeft = pSearchTree->pLeft;
			pNewPin->pRight = pSearchTree->pRight;
			pSearchTree->pLeft = pNewPin;
			pNewPin->pRoot = pSearchTree->pRoot->pPrev;

			if (pFinishedRoot->Identity != false)
			{
				Postorder(pNewPin, pDummyTail, pFinishedRoot);
			}
			else
				printf("%c", pNewPin->pRoot->cData[0]);
		}
	}


	// 루트의 우 항이 NULL이 아니면
	if (pSearchTree->pRoot->pNext != NULL)
	{
		// 루트의 우 항이 연산자가 아니면
		if (isdigit(pSearchTree->pRoot->pNext->cData[0]) != 0)
		{
			TREEPIN *pNewPin = (TREEPIN *)calloc(1, sizeof(TREEPIN));
			pSearchTree->pRight = pNewPin;
			pNewPin->pRoot = pSearchTree->pRoot->pNext;
			printf("%d", atoi(pNewPin->pRoot->cData));
		}

		// 연산자이면
		else
		{
			TREEPIN *pNewPin = (TREEPIN *)calloc(1, sizeof(TREEPIN));
			pSearchTree->pRight = pNewPin;
			pNewPin->pRoot = pSearchTree->pRoot->pNext;

			if (pNewPin->pRoot != pSearchTree->pRoot->pNext->pNext);
			{
				Postorder(pNewPin, pDummyTail, pFinishedRoot);
				printf("%c", pNewPin->pRoot->cData[0]);
			}
		}
	}
	LINKPIN *Tmp = pSearchTree->pRoot;

	pSearchTree->pRoot = pSearchTree->pRoot->pNext;
	while (pSearchTree->pRoot->cData[0] != '+' && pSearchTree->pRoot->cData[0] != '-' &&
		pSearchTree->pRoot->pNext != pDummyTail)
		pSearchTree->pRoot = pSearchTree->pRoot->pNext;

	if (pSearchTree->pRoot != pDummyTail)
	{
		if (pSearchTree->pRoot->cData[0] == '+' || pSearchTree->pRoot->cData[0] == '-')
		{
			pSearchTree->pRoot->pPrev = Tmp;
			pSearchTree->pRoot = Tmp;
			pFinishedRoot->Identity = false;
		}
	}

	else
		pSearchTree->pRoot = Tmp;

	// 루트의 우 항이 NULL이거나 루트가 pDummyTail과 같아지면
	return pSearchTree;
}


// 이진 트리를 구성하기 위해 '+'나 '-' 연산자의 위치를 찾고,
// 재귀호출을 하는 함수입니다.
// 이중 연결 트리의 DummyTail 바로 전 데이터까지 도착하면 재귀호출을 멈추고
// 함수를 반환합니다.
TREEPIN * MakeTreeCircle(TREEPIN *pSearchTree, LINKPIN * pDummyHead,
							LINKPIN * pDummyTail, LINKPIN * FinishedRoot)
{
	// '+' 나 '-' 연산자를 찾는다
	if (pSearchTree->pRoot == pDummyTail->pPrev)
		return pSearchTree;
		

	pSearchTree->pRoot = pSearchTree->pRoot->pNext;
	while (pSearchTree->pRoot->cData[0] != '+' && pSearchTree->pRoot->cData[0] != '-' &&
		pSearchTree->pRoot->pNext != pDummyTail)
		pSearchTree->pRoot = pSearchTree->pRoot->pNext;

	// '+' 나 '-'를 찾으면

	if (pSearchTree->pRoot->cData[0] == '+' || pSearchTree->pRoot->cData[0] == '-')
	{
		while (pSearchTree->pRoot != pDummyTail->pPrev)
		{
			if (pSearchTree->pRoot->cData[0] == '+' || pSearchTree->pRoot->cData[0] == '-')
			{
				pSearchTree = Postorder(pSearchTree, pDummyTail, FinishedRoot);

				if (pSearchTree->pRoot == pDummyTail->pPrev)
				{
					printf("%c", pSearchTree->pRoot->pPrev->cData[0]);
					return pSearchTree;
				}

				else
					MakeTreeCircle(pSearchTree, pDummyHead, pDummyTail, FinishedRoot);
			}
		}
	}
	

		// 못찾으면
	else
	{
		printf("+, - 연산자가 없습니다.");
		return pSearchTree;
	}
	

	return pSearchTree;
}


// 이진 트리를 만들기위해 main에서 처음 호출하는 함수입니다.
// 이진 트리 함수들의 시작점입니다.
TREEPIN * MakeBinaryTree(LINKPIN *pDummyHead, LINKPIN *pDummyTail)
{
	TREEPIN *pSearchTree = (TREEPIN *)calloc(1, sizeof(TREEPIN));
	TREEPIN * pTmp1 = pSearchTree;
	pSearchTree->pRoot = pDummyHead;
	

	LINKPIN *FinishedRoot = (LINKPIN *)calloc(1, sizeof(LINKPIN));
	LINKPIN * pTmp2 = FinishedRoot;

	printf("Post order방식으로 Tree의 데이터를 읽은 결과 : ");
	MakeTreeCircle(pSearchTree, pDummyHead, pDummyTail, FinishedRoot);

	pSearchTree->pRoot = pSearchTree->pRoot->pPrev;
	
	FinishedRoot = pTmp2;

	putchar('\n');
	return pSearchTree;
}