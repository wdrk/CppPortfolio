
// SortingForVisibleView.cpp : CSortingForVisibleView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SortingForVisible.h"
#endif

#include "SortingForVisibleDoc.h"
#include "SortingForVisibleView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSortingForVisibleView

IMPLEMENT_DYNCREATE(CSortingForVisibleView, CView)

BEGIN_MESSAGE_MAP(CSortingForVisibleView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CSortingForVisibleView 생성/소멸

CSortingForVisibleView::CSortingForVisibleView()
	: i(0)
	, j(0)
	, nRand(0)
	, nInitFlag(FALSE)
	, i2(0)
	, ColorR(0)
	, ColorG(0)
	, ColorB(0)
	, ColorR2(0)
	, ColorG2(0)
	, ColorB2(0)
	, ClubMode(false)
	, k(0)
{
}

CSortingForVisibleView::~CSortingForVisibleView()
{
}

BOOL CSortingForVisibleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSortingForVisibleView 그리기

void CSortingForVisibleView::OnDraw(CDC* /*pDC*/)
{
	CSortingForVisibleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}


// CSortingForVisibleView 인쇄

BOOL CSortingForVisibleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSortingForVisibleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSortingForVisibleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSortingForVisibleView 진단

#ifdef _DEBUG
void CSortingForVisibleView::AssertValid() const
{
	CView::AssertValid();
}

void CSortingForVisibleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSortingForVisibleDoc* CSortingForVisibleView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSortingForVisibleDoc)));
	return (CSortingForVisibleDoc*)m_pDocument;
}
#endif //_DEBUG


// CSortingForVisibleView 메시지 처리기


void CSortingForVisibleView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_wndMenu.MoveWindow(20, 695, 310, cy);
}


int CSortingForVisibleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_wndMenu.Create(IDD_MENUBG, this);
	m_wndMenu.ShowWindow(SW_SHOW);

	return 0;
}



void CSortingForVisibleView::OnPaint()
{
	/*-------------------------------------------------------------------------------------------
	#	개발자		정재형
	#	개발환경		Visual Basic 2017   
					Visual C++	 2017
	#	개발시작		2018.12.21.
	#	1 차완료		2019.01.05. PM 2:17
	#	최종완료		2019.11.22. AM 12:11
	#	설명			MFC로 버블 정렬과 선택 정렬을 시각화 한 프로그램입니다.
					UI Thread와 정렬 Thread를 분리하였으므로 정렬 도중에 창을 드래그해서 움직여도
					정렬 과정이 멈추지 않습니다.
	--------------------------------------------------------------------------------------------*/

	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	
	// 화면에 안보이는 Memory DC 선언
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	
	// bmp를 위해 rect를 생성합니다.
	CRect rect;
	GetClientRect(&rect);
	
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	CBitmap* pOldbmp = (CBitmap*)memdc.SelectObject(bmp);

	memdc.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	// y 시작좌표를 순차적으로 늘리기 위한 변수입니다.
	int j = 0;

	ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	if (true == ClubMode)
	{
		// nRandomData[]의 값들을 네모로 그립니다.
		for (i = 0; i < MAXIMUM_LENGTH_OF_ARRAY; ++i)
		{
			// 화면 왼쪽에 그래프를 그리는 코드입니다.
			memdc.FillSolidRect(0, j,
				nRandomData[i] * (5 / 2), 5 / 2,
				RGB(ColorR, ColorG, ColorB));

			// 화면 오른쪽에 그래프를 그리는 코드입니다.
			memdc.FillSolidRect(840, j,
				nRandomData2[i] * (5 / 2), 5 / 2,
				RGB(ColorR2, ColorG2, ColorB2));
			j += (5 / 2);

			ColorR = rand() % 255 + 1;
			ColorG = rand() % 255 + 1;
			ColorB = rand() % 255 + 1;

			ColorR2 = rand() % 255 + 1;
			ColorG2 = rand() % 255 + 1;
			ColorB2 = rand() % 255 + 1;
		}
	}
	else
	{
		// nRandomData[]의 값들을 네모로 그립니다.
		for (i = 0; i < MAXIMUM_LENGTH_OF_ARRAY; ++i)
		{
			// 화면 왼쪽에 그래프를 그리는 코드입니다.
			memdc.FillSolidRect( 0, j, 
			nRandomData[i] * (5 / 2), 5 / 2,
			RGB(ColorR, ColorG, ColorB));

			// 화면 오른쪽에 그래프를 그리는 코드입니다.
			memdc.FillSolidRect( 840, j, 
			nRandomData2[i] * (5 / 2), 5 / 2,
			RGB(ColorR2, ColorG2, ColorB2));
			j += (5 / 2);
		}
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);

	memdc.DeleteDC();
}


BOOL CSortingForVisibleView::OnEraseBkgnd(CDC* pDC)
{
	
	// return을 FALSE로 하던 TRUE로 하던 상관이 없고,
	// 더블 버퍼링을 수행하기 위해서 OnEraseBkgnd()가 작동하지 않도록
	// 기본 return 코드는 주석처리합니다.
	// return CView::OnEraseBkgnd(pDC);

	return FALSE;
}
