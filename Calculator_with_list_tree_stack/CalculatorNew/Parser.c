#include "Base.h"


// ����ڰ� �Է��� ���� ���α׷� ���࿡ ��ȿ���� �˻��ϴ� Parser�Դϴ�.
bool ParseInput(LINKPIN *pDummyHead, LINKPIN *pDummyTail, char *pszInput)
{
	int pszInputCount = 0;
	while (pszInput[pszInputCount] != '\n')
	{
		// 0. ȭ��Ʈ �����̽��ΰ�
		if (isspace(pszInput[pszInputCount]) == 0)
		{
			// ������� ù��°���� '(' Ȥ�� �ǿ����ڸ� �;� �ϹǷ�
			// ���� ���� ����Ʈ�� �����Ͱ� ���� �������� Ȯ���մϴ�.
			if (pDummyTail->pPrev == pDummyHead)
			{
				if (isdigit(pszInput[pszInputCount]) != 0)
				{
					puts("�ǿ�����");
					LINKPIN *NewPin = (LINKPIN *)calloc(1, sizeof(LINKPIN));
					NewPin->Identity = false;
					NewPin->cData[0] = pszInput[pszInputCount];
					// ���⼭ ���� ���� ����Ʈ�� �ֱ�
					AddLinkedList(pDummyHead, pDummyTail, NewPin);
				}

				// 2. ��Ģ�������ΰ�
				else if (pszInput[pszInputCount] == '+' ||
					pszInput[pszInputCount] == '-' ||
					pszInput[pszInputCount] == '*' ||
					pszInput[pszInputCount] == '/' ||
					pszInput[pszInputCount] == ')')
				{
					puts("���� ����Ʈ�� ó������ '(' Ȥ�� �ǿ����ڰ� �;� �մϴ�.");
					return false;
				}

				// 3. ��ȣ�ΰ�

				else if (pszInput[pszInputCount] == '(')
				{
					puts("��ȣ '('");
					LINKPIN *NewPin = (LINKPIN *)calloc(1, sizeof(LINKPIN));
					NewPin->Identity = true;
					NewPin->cData[0] = pszInput[pszInputCount];
					AddLinkedList(pDummyHead, pDummyTail, NewPin);
				}

				else if (pszInput[pszInputCount] == ')')
				{
					puts("���� ����Ʈ�� ó������ '(' Ȥ�� �ǿ����ڰ� �;� �մϴ�.");;
					return false;
				}
			} //

			else
			{
				// ���� ��ϵ��ִ� �����Ͱ� ���������� �ǿ������������� Ȯ���ϰ�
				// �����ؼ� ���� �Ѵ�.

				if (pDummyTail->pPrev->Identity == true)
				{
					if (pDummyTail->pPrev->cData[0] != ')')
					{
						if (isdigit(pszInput[pszInputCount]) != 0)
						{
							puts("�ǿ�����");
							LINKPIN *NewPin = (LINKPIN *)calloc(1, sizeof(LINKPIN));
							NewPin->Identity = false;
							NewPin->cData[0] = pszInput[pszInputCount];
							// ���⼭ ���� ���� ����Ʈ�� �ֱ�
							AddLinkedList(pDummyHead, pDummyTail, NewPin);
						}

						else if (pszInput[pszInputCount] == '+' ||
							pszInput[pszInputCount] == '-' ||
							pszInput[pszInputCount] == '*' ||
							pszInput[pszInputCount] == '/')
						{
							puts("������ �������δ� �ǿ����ڰ� ��ϵž� �մϴ�.");
						}

						else if (pszInput[pszInputCount] == '(' ||
							pszInput[pszInputCount] == ')')
						{
							puts("������ ������ ��ȣ�� �Խ��ϴ�.");
						}
					}

					else
					{
						if (isdigit(pszInput[pszInputCount]) != 0)
						{
							puts("�ǿ�����");
							LINKPIN *NewPin = (LINKPIN *)calloc(1, sizeof(LINKPIN));
							NewPin->Identity = false;
							NewPin->cData[0] = pszInput[pszInputCount];
							// ���⼭ ���� ���� ����Ʈ�� �ֱ�
							AddLinkedList(pDummyHead, pDummyTail, NewPin);
						}

						else if (pszInput[pszInputCount] == '+' ||
							pszInput[pszInputCount] == '-' ||
							pszInput[pszInputCount] == '*' ||
							pszInput[pszInputCount] == '/')
						{
							puts("������ �������δ� �ǿ����ڰ� ��ϵž� �մϴ�.");
						}

						else if (pszInput[pszInputCount] == '(' ||
							pszInput[pszInputCount] == ')')
						{
							puts("������ ������ ��ȣ�� �Խ��ϴ�.");
						}
					}

				}

				else
				{
					// 1. �ǿ������ΰ�
					if (isdigit(pszInput[pszInputCount]) != 0)
					{
						puts("�ǿ����� ����");
						int i = 0;
						while (pDummyTail->pPrev->cData[i] != '\0')
							++i;
						pDummyTail->pPrev->cData[i] = pszInput[pszInputCount];
					}

					// 2. ��Ģ�������ΰ�
					else if (pszInput[pszInputCount] == '+' ||
						pszInput[pszInputCount] == '-' ||
						pszInput[pszInputCount] == '*' ||
						pszInput[pszInputCount] == '/')
					{
						puts("��Ģ������");
						LINKPIN *NewPin = (LINKPIN *)calloc(1, sizeof(LINKPIN));
						NewPin->Identity = true;
						NewPin->cData[0] = pszInput[pszInputCount];
						AddLinkedList(pDummyHead, pDummyTail, NewPin);
					}

					// 3. ��ȣ�ΰ�

					else if (pszInput[pszInputCount] == '(' ||
						pszInput[pszInputCount] == ')')
					{
						puts("��ȣ");
					}
				}
			}
		}

		else if (isspace(pszInput[pszInputCount]) != 0)
		{
			printf("ȭ��Ʈ �����̽� ����\n");
			return false;
		}

		else
		{
			puts("�˻�� �̿��� �Է����� ���� �����Դϴ�.");
			return false;
		}

		++pszInputCount;
	}

	return true;
}