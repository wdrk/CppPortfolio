// Graph.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SortingForVisible.h"
#include "Graph.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "SortingForVisibleView.h"

// CGraph 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGraph, CDialog)

CGraph::CGraph(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GRAPH, pParent)
{

}

CGraph::~CGraph()
{
}

void CGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGraph, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGraph 메시지 처리기입니다.


void CGraph::OnPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}
