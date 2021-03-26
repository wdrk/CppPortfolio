#include "Base.h"


// ���� Ʈ���� Postorder�� �д� �Լ��Դϴ�.
TREEPIN *Postorder(TREEPIN *pSearchTree, LINKPIN *pDummyTail, LINKPIN *pFinishedRoot)
{
	// �� �׺��� ����Ʈ�� �۾� ����
	// ��Ʈ�� �� ���� NULL�� �ƴϸ�
	if (pSearchTree->pRoot->pPrev != NULL)
	{
		// ��Ʈ�� �� ���� �����ڰ� �ƴϸ�
		if (isdigit(pSearchTree->pRoot->pPrev->cData[0]) != 0)
		{
			TREEPIN *pNewPin = (TREEPIN *)calloc(1, sizeof(TREEPIN));
			pSearchTree->pLeft = pNewPin;
			pNewPin->pRoot = pSearchTree->pRoot->pPrev;
			printf("%d", atoi(pNewPin->pRoot->cData));
		}

		// �������̸�
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


	// ��Ʈ�� �� ���� NULL�� �ƴϸ�
	if (pSearchTree->pRoot->pNext != NULL)
	{
		// ��Ʈ�� �� ���� �����ڰ� �ƴϸ�
		if (isdigit(pSearchTree->pRoot->pNext->cData[0]) != 0)
		{
			TREEPIN *pNewPin = (TREEPIN *)calloc(1, sizeof(TREEPIN));
			pSearchTree->pRight = pNewPin;
			pNewPin->pRoot = pSearchTree->pRoot->pNext;
			printf("%d", atoi(pNewPin->pRoot->cData));
		}

		// �������̸�
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

	// ��Ʈ�� �� ���� NULL�̰ų� ��Ʈ�� pDummyTail�� ��������
	return pSearchTree;
}


// ���� Ʈ���� �����ϱ� ���� '+'�� '-' �������� ��ġ�� ã��,
// ���ȣ���� �ϴ� �Լ��Դϴ�.
// ���� ���� Ʈ���� DummyTail �ٷ� �� �����ͱ��� �����ϸ� ���ȣ���� ���߰�
// �Լ��� ��ȯ�մϴ�.
TREEPIN * MakeTreeCircle(TREEPIN *pSearchTree, LINKPIN * pDummyHead,
							LINKPIN * pDummyTail, LINKPIN * FinishedRoot)
{
	// '+' �� '-' �����ڸ� ã�´�
	if (pSearchTree->pRoot == pDummyTail->pPrev)
		return pSearchTree;
		

	pSearchTree->pRoot = pSearchTree->pRoot->pNext;
	while (pSearchTree->pRoot->cData[0] != '+' && pSearchTree->pRoot->cData[0] != '-' &&
		pSearchTree->pRoot->pNext != pDummyTail)
		pSearchTree->pRoot = pSearchTree->pRoot->pNext;

	// '+' �� '-'�� ã����

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
	

		// ��ã����
	else
	{
		printf("+, - �����ڰ� �����ϴ�.");
		return pSearchTree;
	}
	

	return pSearchTree;
}


// ���� Ʈ���� ��������� main���� ó�� ȣ���ϴ� �Լ��Դϴ�.
// ���� Ʈ�� �Լ����� �������Դϴ�.
TREEPIN * MakeBinaryTree(LINKPIN *pDummyHead, LINKPIN *pDummyTail)
{
	TREEPIN *pSearchTree = (TREEPIN *)calloc(1, sizeof(TREEPIN));
	TREEPIN * pTmp1 = pSearchTree;
	pSearchTree->pRoot = pDummyHead;
	

	LINKPIN *FinishedRoot = (LINKPIN *)calloc(1, sizeof(LINKPIN));
	LINKPIN * pTmp2 = FinishedRoot;

	printf("Post order������� Tree�� �����͸� ���� ��� : ");
	MakeTreeCircle(pSearchTree, pDummyHead, pDummyTail, FinishedRoot);

	pSearchTree->pRoot = pSearchTree->pRoot->pPrev;
	
	FinishedRoot = pTmp2;

	putchar('\n');
	return pSearchTree;
}