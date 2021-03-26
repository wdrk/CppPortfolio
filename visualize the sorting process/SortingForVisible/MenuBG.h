#pragma once


// CMenuBG 대화 상자입니다.

UINT WorkerThread(LPVOID pParam);
#define MAXIMUM_LENGTH_OF_ARRAY	300
#define MAXIMUM_NUMBER_OF_MIXING 590

class CMenuBG : public CDialog
{
	DECLARE_DYNAMIC(CMenuBG)

public:
	CMenuBG(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMenuBG();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENUBG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedAuto();
	afx_msg void OnBnClickedManual();
	afx_msg void OnBnClickedReset();
	int i;
	int j;
	// 무작위 생성 값을 임시 저장하는 변수입니다.
	int nRand;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedClubmode();
	int u;
	int nTmp;
};
