
// SortingForVisibleView.h : CSortingForVisibleView 클래스의 인터페이스
//

#pragma once
#include "MenuBG.h"
#include "Graph.h"


class CSortingForVisibleDoc;

class CSortingForVisibleView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSortingForVisibleView();
	DECLARE_DYNCREATE(CSortingForVisibleView)

// 특성입니다.
public:
	CSortingForVisibleDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSortingForVisibleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

	CMenuBG		m_wndMenu;
	CGraph		m_wndGraph;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// nRandomData 배열의 인덱스 변수입니다.
	int i;
	// nRandomData 배열에 무작위 값을 넣을때 사용하는 변수입니다.
	int j;
	int nRandomData[300] = { 0 };
	// 무작위 값을 저장하는 for 문에서 사용하는 임시 저장용 변수입니다.
	int nRand;
	afx_msg void OnPaint();
	// 프로그램을 처음 시작할때는 0, 버튼을 한번이라도 작동시킨다면 1로 값을 설정합니다.
	int nInitFlag;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// nRandomData2[]의 기준 인덱스를 나타내는데 쓰는 변수입니다.
	int i2;
	int nRandomData2[300] = { 0 };
	bool CheckArray[100] = { false };
	bool CheckArray2[100] = { false };
	// RGB 컬러중에 R 값의 변수입니다.
	int ColorR;
	// RGB 값 중에 G 값의 변수입니다.
	int ColorG;
	// RGB 값 중에 B 값의 변수입니다.
	int ColorB;
	// 화면 오른쪽에 표시하는 그래프의 RGB값 변수입니다.
	int ColorR2;
	int ColorG2;
	int ColorB2;
	// Club Mode 버튼으로 OnPaint()에 진입한 것을 알려주는 값입니다.
	bool ClubMode;
	// Auto 버튼을 눌러서 정렬을 수행하고 있는 상태인지를 나타냅니다.
	bool bAutoFlag = false;
	// 프로그램을 처음 시작할때는 FALSE, 그 후에는 TRUE를 나타냅니다.
	bool bInitFlag = false;
	int k;
};

#ifndef _DEBUG  // SortingForVisibleView.cpp의 디버그 버전
inline CSortingForVisibleDoc* CSortingForVisibleView::GetDocument() const
   { return reinterpret_cast<CSortingForVisibleDoc*>(m_pDocument); }
#endif

