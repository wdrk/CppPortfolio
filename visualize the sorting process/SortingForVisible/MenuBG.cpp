// MenuBG.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SortingForVisible.h"
#include "MenuBG.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "SortingForVisibleView.h"

// CMenuBG 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMenuBG, CDialog)

CMenuBG::CMenuBG(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MENUBG, pParent)
	, i(0)
	, j(0)
	, nRand(0)
	, u(0)
	, nTmp(0)
{
}

CMenuBG::~CMenuBG()
{
}

void CMenuBG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMenuBG, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_AUTO, &CMenuBG::OnBnClickedAuto)
	ON_BN_CLICKED(IDC_MANUAL, &CMenuBG::OnBnClickedManual)
	ON_BN_CLICKED(IDC_RESET, &CMenuBG::OnBnClickedReset)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLUBMODE, &CMenuBG::OnBnClickedClubmode)
END_MESSAGE_MAP()


// CMenuBG 메시지 처리기입니다.

// 메뉴 버튼이 있는 Form을 그립니다.
void CMenuBG::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(&rect, RGB(255, 255, 255));
}

CCriticalSection g_cs;


// WorkerThread는 Critical Section Lock을 사용하며 정렬을 수행합니다.
UINT WorkerThread(LPVOID pParam)
{
	CMainFrame *pFrame = (CMainFrame*)theApp.m_pMainWnd;
	CSortingForVisibleView *pView = (CSortingForVisibleView*)pFrame->GetActiveView();

	// 데이터에 접근하는 동안 Critical Section을 사용해서 Lock을 겁니다.
	g_cs.Lock();

	// 버블 정렬 인덱스 변수들입니다.
	int i = 0;
	int j = 0;

	// 선택 정렬 인덱스 변수들입니다.
	int nMinimum_Data_Index = 0;
	int k = 0;

	// 값을 교환할때 임시로 값을 저장하는 변수입니다.
	int nTmp = 0;

	for (i = MAXIMUM_LENGTH_OF_ARRAY; i > 0; --i)
	{
		// 버블 정렬 구간입니다.
		for (j = 0; j < i; ++j)
		{
			if (pView->nRandomData[j] > pView->nRandomData[j + 1])
			{
				nTmp = pView->nRandomData[j];
				pView->nRandomData[j] = pView->nRandomData[j + 1];
				pView->nRandomData[j + 1] = nTmp;
			}
		}

		// 선택 정렬 구간입니다.
		for (j = 0; j < MAXIMUM_LENGTH_OF_ARRAY; ++j)
		{
			nMinimum_Data_Index = j;
	
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			// 가장 최소값이 있는 인덱스를 구합니다.
			for (k = nMinimum_Data_Index + 1; k < MAXIMUM_LENGTH_OF_ARRAY; ++k)
			{
				if (pView->nRandomData2[nMinimum_Data_Index] > pView->nRandomData2[k])
					nMinimum_Data_Index = k;
			}
	
			// i와 u의 값이 다르다면 i번 인덱스에 있는 값보다 작은 값을 발견했다는 것이므로
			// i 인덱스와 u 인덱스의 값을 교환합니다.
			if (nMinimum_Data_Index != j)
			{
				nTmp = pView->nRandomData2[nMinimum_Data_Index];
				pView->nRandomData2[nMinimum_Data_Index] = pView->nRandomData2[j];
				pView->nRandomData2[j] = nTmp;

				// break를 없애면 눈 깜짝할 새에 정렬이 끝나버립니다.
				break;
			}
		}
		pView->RedrawWindow();

		if (false == pView->bAutoFlag)
			break;

		Sleep(10);
	}

	// 정렬 작업을 모두 수행한 다음엔 플래그들의 값을 초기화합니다.
	pView->bAutoFlag = false;
	pView->bInitFlag = false;
	pView->ClubMode = false;

	// Lock을 해제합니다.
	g_cs.Unlock();


	return 0;
}

// 'Auto' 버튼을 클릭했을때 처리하는 코드입니다.
void CMenuBG::OnBnClickedAuto()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame *pFrame = (CMainFrame*)theApp.m_pMainWnd;
	CSortingForVisibleView *pView = (CSortingForVisibleView*)pFrame->GetActiveView();

	if (true == pView->bAutoFlag)
		return;


	if (false == pView->bInitFlag)
		OnBnClickedReset();

	else
	{
		pView->bAutoFlag = true;
		AfxBeginThread(WorkerThread, NULL);
	}
}


// 'Manual' 버튼을 클릭했을때 처리하는 코드입니다.
void CMenuBG::OnBnClickedManual()
{
	CMainFrame *pFrame = (CMainFrame*)theApp.m_pMainWnd;
	CSortingForVisibleView *pView = (CSortingForVisibleView*)pFrame->GetActiveView();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (true == pView->bAutoFlag)
		return;

	//else if (false == pView->bInitFlag)
		//return;

	else
		AfxBeginThread(WorkerThread, NULL);
}


// 'Reset' 버튼을 클릭했을때 처리하는 코드입니다.
void CMenuBG::OnBnClickedReset()
{
	CMainFrame *pFrame = (CMainFrame*)theApp.m_pMainWnd;
	CSortingForVisibleView *pView = (CSortingForVisibleView*)pFrame->GetActiveView();

	// Auto로 정렬 작업중일때는 작동하지 않도록 합니다.
	if (true == pView->bAutoFlag)
		return;

	srand((unsigned)time(NULL));

	// Auto 버튼을 눌러서 작동중인지를 확인하는 플래그를 초기화합니다.
	pView->bAutoFlag = false;

	// 데이터를 뒤섞은 상태인지를 확인하는 플래그를 true로 설정합니다.
	// 처음 프로그램을 시작해서 아무 데이터도 없을때만 필요한 플래그입니다.
	pView->bInitFlag = true;
	i = 0;
	j = 0;

	// 데이터를 섞을 때마다 색이 변하게 하는 코드입니다.
	pView->ColorR = rand() % 255 + 1;
	pView->ColorG = rand() % 255 + 1;
	pView->ColorB = rand() % 255 + 1;

	pView->ColorR2 = rand() % 255 + 1;
	pView->ColorG2 = rand() % 255 + 1;
	pView->ColorB2 = rand() % 255 + 1;

	// 값을 무작위로 섞은 배열을 만들기 위해 먼저 배열에 차례대로 값을 채웁니다.
	for (i = 0; i < MAXIMUM_LENGTH_OF_ARRAY; ++i)
	{
		pView->nRandomData[i] = i + 1;
	}

	// x와 y는 배열의 인덱스 값으로 쓰는 변수들입니다.
	int x = 0;
	int y = 0;

	// 배열의 값이 적당히 골고루 섞일 수 있을만큼 다음 과정을 반복합니다.
	for (i = 0; i < MAXIMUM_NUMBER_OF_MIXING; ++i)
	{
		// x와 y에 최대 배열길이 이내의 값을 무작위로 대입하고,
		x = rand() % MAXIMUM_LENGTH_OF_ARRAY;
		y = rand() % MAXIMUM_LENGTH_OF_ARRAY;

		// x와 y가 같은 값이 아니면 해당 값을 인덱스로 하여 두 인덱스의 값을 교차합니다.
		if (x != y)
		{
			int nTmp = pView->nRandomData[x];
			pView->nRandomData[x] = pView->nRandomData[y];
			pView->nRandomData[y] = nTmp;
		}
	}

	// nRandomData2 배열에 위의 과정을 동일하게 수행합니다.
	for (i = 0; i < MAXIMUM_LENGTH_OF_ARRAY; ++i)
	{
		pView->nRandomData2[i] = i + 1;
	}

	for (i = 0; i < MAXIMUM_NUMBER_OF_MIXING; ++i)
	{
		x = rand() % MAXIMUM_LENGTH_OF_ARRAY;
		y = rand() % MAXIMUM_LENGTH_OF_ARRAY;

		if (x != y)
		{
			int nTmp = pView->nRandomData2[x];
			pView->nRandomData2[x] = pView->nRandomData2[y];
			pView->nRandomData2[y] = nTmp;
		}
	}

	// 모든 작업을 마치고 윈도우를 새로 그립니다.
	pView->RedrawWindow();
}

BOOL CMenuBG::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return TRUE;
}

void CMenuBG::OnBnClickedClubmode()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CSortingForVisibleView *pView = (CSortingForVisibleView*)pFrame->GetActiveView();

	if (false == pView->bInitFlag)
		OnBnClickedReset();

	else if (true == pView->bAutoFlag)
		return;

	else
	{
		pView->ClubMode = true;
		OnBnClickedAuto();
	}
}
