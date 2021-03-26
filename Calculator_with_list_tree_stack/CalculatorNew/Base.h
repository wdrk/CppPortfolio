#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct LINKPIN
{
	bool Identity;
	char cData[16];
	struct LINKPIN *pPrev;
	struct LINKPIN *pNext;
	struct TREEPIN *TreeHead;
	struct TREEPIN *TreeTail;
} LINKPIN;


typedef struct TREEPIN
{
	struct LINKPIN *pRoot;

	struct TREEPIN *pLeft;
	struct TREEPIN *pRight;
}TREEPIN;


typedef struct STACKPIN
{
	struct TREEPIN *pTreeData;
	struct LINKPIN *pLinkData;
	int nData;
	struct STACKPIN *Lowside;
	struct STACKPIN *Highside;
}STACKPIN;



#define MAXIMUM_ARRAY_LENGTH	512
#define INPUT_BOUNDARY			510




#define PLUS		'+'
#define MINUS		'-'
#define	MULTIPLY	'*'
#define DIVIDE		'/'




bool Input			(char *, size_t);
bool ParseInput		(LINKPIN *, LINKPIN *, char *);
void PrintList		(LINKPIN *, LINKPIN *);
void AddLinkedList	(LINKPIN *, LINKPIN *, LINKPIN *);

TREEPIN * MakeBinaryTree(LINKPIN *, LINKPIN *);

void Stack(TREEPIN *, LINKPIN *, LINKPIN *);
int PushStack(TREEPIN *, STACKPIN *, int);
int PopStack(TREEPIN *, STACKPIN *, int);

void FreePin		(LINKPIN *, LINKPIN *);