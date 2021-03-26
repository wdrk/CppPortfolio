#include "Base.h"


// 사용자가 입력한 값이 프로그램 실행에 유효한지 검사하는 Parser입니다.
bool ParseInput(LINKPIN *pDummyHead, LINKPIN *pDummyTail, char *pszInput)
{
	int pszInputCount = 0;
	while (pszInput[pszInputCount] != '\n')
	{
		// 0. 화이트 스페이스인가
		if (isspace(pszInput[pszInputCount]) == 0)
		{
			// 연산식의 첫번째에는 '(' 혹은 피연산자만 와야 하므로
			// 현재 연결 리스트가 데이터가 없는 상태인지 확인합니다.
			if (pDummyTail->pPrev == pDummyHead)
			{
				if (isdigit(pszInput[pszInputCount]) != 0)
				{
					puts("피연산자");
					LINKPIN *NewPin = (LINKPIN *)calloc(1, sizeof(LINKPIN));
					NewPin->Identity = false;
					NewPin->cData[0] = pszInput[pszInputCount];
					// 여기서 이중 연결 리스트에 넣기
					AddLinkedList(pDummyHead, pDummyTail, NewPin);
				}

				// 2. 사칙연산자인가
				else if (pszInput[pszInputCount] == '+' ||
					pszInput[pszInputCount] == '-' ||
					pszInput[pszInputCount] == '*' ||
					pszInput[pszInputCount] == '/' ||
					pszInput[pszInputCount] == ')')
				{
					puts("연결 리스트의 처음에는 '(' 혹은 피연산자가 와야 합니다.");
					return false;
				}

				// 3. 괄호인가

				else if (pszInput[pszInputCount] == '(')
				{
					puts("괄호 '('");
					LINKPIN *NewPin = (LINKPIN *)calloc(1, sizeof(LINKPIN));
					NewPin->Identity = true;
					NewPin->cData[0] = pszInput[pszInputCount];
					AddLinkedList(pDummyHead, pDummyTail, NewPin);
				}

				else if (pszInput[pszInputCount] == ')')
				{
					puts("연결 리스트의 처음에는 '(' 혹은 피연산자가 와야 합니다.");;
					return false;
				}
			} //

			else
			{
				// 먼저 등록돼있는 데이터가 연산자인지 피연산자인지부터 확인하고
				// 교차해서 들어가게 한다.

				if (pDummyTail->pPrev->Identity == true)
				{
					if (pDummyTail->pPrev->cData[0] != ')')
					{
						if (isdigit(pszInput[pszInputCount]) != 0)
						{
							puts("피연산자");
							LINKPIN *NewPin = (LINKPIN *)calloc(1, sizeof(LINKPIN));
							NewPin->Identity = false;
							NewPin->cData[0] = pszInput[pszInputCount];
							// 여기서 이중 연결 리스트에 넣기
							AddLinkedList(pDummyHead, pDummyTail, NewPin);
						}

						else if (pszInput[pszInputCount] == '+' ||
							pszInput[pszInputCount] == '-' ||
							pszInput[pszInputCount] == '*' ||
							pszInput[pszInputCount] == '/')
						{
							puts("연산자 다음으로는 피연산자가 등록돼야 합니다.");
						}

						else if (pszInput[pszInputCount] == '(' ||
							pszInput[pszInputCount] == ')')
						{
							puts("연산자 다음에 괄호가 왔습니다.");
						}
					}

					else
					{
						if (isdigit(pszInput[pszInputCount]) != 0)
						{
							puts("피연산자");
							LINKPIN *NewPin = (LINKPIN *)calloc(1, sizeof(LINKPIN));
							NewPin->Identity = false;
							NewPin->cData[0] = pszInput[pszInputCount];
							// 여기서 이중 연결 리스트에 넣기
							AddLinkedList(pDummyHead, pDummyTail, NewPin);
						}

						else if (pszInput[pszInputCount] == '+' ||
							pszInput[pszInputCount] == '-' ||
							pszInput[pszInputCount] == '*' ||
							pszInput[pszInputCount] == '/')
						{
							puts("연산자 다음으로는 피연산자가 등록돼야 합니다.");
						}

						else if (pszInput[pszInputCount] == '(' ||
							pszInput[pszInputCount] == ')')
						{
							puts("연산자 다음에 괄호가 왔습니다.");
						}
					}

				}

				else
				{
					// 1. 피연산자인가
					if (isdigit(pszInput[pszInputCount]) != 0)
					{
						puts("피연산자 연속");
						int i = 0;
						while (pDummyTail->pPrev->cData[i] != '\0')
							++i;
						pDummyTail->pPrev->cData[i] = pszInput[pszInputCount];
					}

					// 2. 사칙연산자인가
					else if (pszInput[pszInputCount] == '+' ||
						pszInput[pszInputCount] == '-' ||
						pszInput[pszInputCount] == '*' ||
						pszInput[pszInputCount] == '/')
					{
						puts("사칙연산자");
						LINKPIN *NewPin = (LINKPIN *)calloc(1, sizeof(LINKPIN));
						NewPin->Identity = true;
						NewPin->cData[0] = pszInput[pszInputCount];
						AddLinkedList(pDummyHead, pDummyTail, NewPin);
					}

					// 3. 괄호인가

					else if (pszInput[pszInputCount] == '(' ||
						pszInput[pszInputCount] == ')')
					{
						puts("괄호");
					}
				}
			}
		}

		else if (isspace(pszInput[pszInputCount]) != 0)
		{
			printf("화이트 스페이스 오류\n");
			return false;
		}

		else
		{
			puts("검사식 이외의 입력으로 인한 오류입니다.");
			return false;
		}

		++pszInputCount;
	}

	return true;
}