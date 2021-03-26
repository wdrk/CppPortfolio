#include "Base.h"


// ���� ���� ������ �����Ҵ��ϰ� TreeToStack �Լ��� �ѱ�ϴ�.
void Stack(TREEPIN * pTreeResult, LINKPIN *pDummyHead, LINKPIN *pDummyTail)
{
	// ������ �����ϱ� ���� pHead�� pTail�� �����Ҵ��ϰ�
	// �����ؼ� ������ ����ϴ�.
	STACKPIN *StackHead = (STACKPIN *)calloc(1, sizeof(STACKPIN));
	STACKPIN *StackTail = (STACKPIN *)calloc(1, sizeof(STACKPIN));

	StackHead->Lowside = StackTail;
	StackTail->Highside = StackHead;
	
	//////////////////////////////////////////////////////////
	int nResult = 0;
	nResult = PushStack(pTreeResult, StackHead, nResult);
	//////////////////////////////////////////////////////////
		

	printf("��� ��� : %d\n", nResult);
}


int PushStack(TREEPIN *pTreeResult, STACKPIN *pStackHead, int pnResult)
{

	// ��Ʈ�� �� ���� ������ �ƴϸ�
	if (isdigit(pTreeResult->pLeft->pRoot->cData[0]) == 0)
	{
		// PushStack�� ���ȣ���մϴ�.
		PushStack(pTreeResult->pLeft, pStackHead, pnResult);
			
	}

	// ��Ʈ�� �� ���� �����̸�
	else
	{
		// ���ο� �޸𸮸� ���� �Ҵ��ϰ� ���ÿ� Push�մϴ�.
		STACKPIN *pNewStack = (STACKPIN *)calloc(1, sizeof(STACKPIN));
		pNewStack->nData = atoi(pTreeResult->pLeft->pRoot->cData);

		pNewStack->Lowside = pStackHead->Lowside;
		pStackHead->Lowside = pNewStack;
	}

	// ��Ʈ�� �� ���� �������̸�
	if (isdigit(pTreeResult->pRight->pRoot->cData[0]) == 0)
	{
		// �ߺ����� �ʰ� if�� �����ؾ���.
		if (pnResult != 0)
		{
			// PushStack�� ���ȣ���մϴ�.
			PushStack(pTreeResult->pRight, pStackHead, pnResult);
		}
	}

	// ��Ʈ�� �� ���� �����̸�
	else
	{
		// ���ÿ� Push�մϴ�.
		STACKPIN *pNewStack = (STACKPIN *)calloc(1, sizeof(STACKPIN));
		pNewStack->nData = atoi(pTreeResult->pRight->pRoot->cData);

		pNewStack->Lowside = pStackHead->Lowside;
		pStackHead->Lowside = pNewStack;
	}

	// Push�� ������ ��Ʈ ���� �����ڿ� �´� ������ �մϴ�.

	pnResult += PopStack(pTreeResult, pStackHead, pnResult);

	return pnResult;
}




int PopStack(TREEPIN *pTreeResult, STACKPIN *pStackHead, int pnResult)
{

	// ���ÿ��� 2���� ���� POP �Ͽ� ���� ��Ʈ ����� �����ڿ� �°� �����մϴ�.
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