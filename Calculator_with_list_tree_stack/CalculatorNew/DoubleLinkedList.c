#include "Base.h"


void AddLinkedList(LINKPIN * pDummyHead, LINKPIN * pDummyTail, LINKPIN * pNewPin)
{
	if (pDummyHead->pNext == pDummyTail)
	{
		pDummyHead->pNext = pNewPin;

		pNewPin->pPrev = pDummyHead;
		pNewPin->pNext = pDummyTail;

		pDummyTail->pPrev = pNewPin;
	}

	else
	{
		LINKPIN *pTmp = pDummyHead;

		while (pTmp->pNext != pDummyTail)
			pTmp = pTmp->pNext;

		pNewPin->pPrev = pTmp;
		pNewPin->pNext = pTmp->pNext;

		pTmp->pNext = pNewPin;

		pDummyTail->pPrev = pNewPin;
	}

}


void FreePin(LINKPIN *pDummyHead, LINKPIN *pDummyTail)
{
	LINKPIN *pFree = pDummyHead->pNext;
	LINKPIN *pMove = pFree;

	while (pFree != pDummyTail)
	{
		pMove = pMove->pNext;
		free(pFree);
		pFree = pMove;
	}
}