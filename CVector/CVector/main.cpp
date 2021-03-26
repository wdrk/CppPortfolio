#include <iostream>
#include <conio.h>
#include "Vector.h"


#define ALLOCSIZE 4



/**************************************************************************************

#	개발자		:	정재형
#	개발환경		:	Visual Studio 2017
#	개발기간		:	2019.2.19. AM 9:00 ~ PM 17:00
#	최종완료		:	2019.11.22. AM 3:39
#	개발목표		:	CVector(자동으로 메모리를 선형으로 할당하는 컨테이너)를 템플릿 형식으로 구현하기

**************************************************************************************/



/////////////////////////////////////////////////////////////////////////////////////////////
auto main(void) -> int
{

	/*
	main()의 코드는 CVector가 잘 작동하는지 확인하는 Test용 코드입니다.
																*/

	std::cout << "<double> 인스턴스를 만듭니다." << std::endl;
	CVector<double> vector(4);

	// 데이터 삽입
	std::cout << "데이터 push_back : " << vector.AddBack(1.1) << std::endl;

	// 0번 인덱스의 값 가져오기
	std::cout << "[0] 번 인덱스의 값 가져오기 : " << vector.GetAt(0) << std::endl;

	// 데이터 삽입
	std::cout << "데이터 push_back : " << vector.AddBack(2.1) << std::endl;
	std::cout << "데이터 push_back : " << vector.AddBack(3.1) << std::endl;
	std::cout << "데이터 push_back : " << vector.AddBack(4.1) << std::endl;

	// 3번 노드의 값 가져오기
	std::cout << "[3] 번 인덱스의 값 가져오기 : " << vector.GetAt(3) << std::endl;

	// 현재 배열에 알맞지 않은 인덱스에 값을 삽입하면 자동으로 마지막 노드의 다음 인덱스 값으로 조정해서 데이터를 추가합니다.
	vector.Insert(5.1, 7);
	std::cout << "[7] 번 인덱스에 '5.1' 값을 추가함" << std::endl;

	// 3번 노드의 값을 지우면 다음 인덱스의 노드를 연결합니다.
	vector.Delete(3);
	std::cout << "[3] 번 인덱스의 값을 삭제함" << std::endl;
	std::cout << "삭제 후 현재 [3] 번 인덱스의 값 가져오기 : " << vector.GetAt(3) << std::endl;

	std::cout << "현재 Vector의 전체 데이터 출력" << std::endl;
	vector.PrintAll();

	std::cout << "vector<double> 배열 요소 갯수 : " << vector.m_arraysize << std::endl;
	std::cout << std::endl;
	std::cout << "********************************************************" << std::endl;
	std::cout << std::endl;
	//////////////////////////////////////////////////////////////////////////////////

	std::cout << "<int> 인스턴스를 만듭니다." << std::endl;
	CVector<int> vectorint(8);

	std::cout << "데이터 push_back : " << vectorint.AddBack(1) << std::endl;
	std::cout << "[0] 번 인덱스의 값 가져오기 : " << vectorint.GetAt(0) << std::endl;

	std::cout << "데이터 push_back : " << vectorint.AddBack(2) << std::endl;
	std::cout << "데이터 push_back : " << vectorint.AddBack(3) << std::endl;
	std::cout << "데이터 push_back : " << vectorint.AddBack(4) << std::endl;
	std::cout << "[3] 번 인덱스의 값 가져오기 : " << vectorint.GetAt(3) << std::endl;

	vectorint.Insert(5, 7);
	std::cout << "[7] 번 인덱스에 '5' 값을 추가함" << std::endl;

	//std::cout << "데이터 push_back : " << vectorint.AddBack(5) << std::endl;
	std::cout << "데이터 push_back : " << vectorint.AddBack(6) << std::endl;
	std::cout << "데이터 push_back : " << vectorint.AddBack(8) << std::endl;

	vectorint.Delete(5);
	std::cout << "[5] 번 인덱스의 값을 삭제함" << std::endl;
	std::cout << "삭제 후 현재 [5] 번 인덱스의 값 가져오기 : " << vectorint.GetAt(5) << std::endl;
	std::cout << "현재 Vector의 전체 데이터 출력" << std::endl;
	vectorint.PrintAll();

	std::cout << "vector<int> 배열 요소 갯수 : " << vectorint.m_arraysize << std::endl;
	std::cout << "********************************************************" << std::endl;

	//////////////////////////////////////////////////////////////////////////////////////////

	std::cout << "출력을 완료했습니다. 아무 키나 눌러주세요." << std::endl;
	_getch();

	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
CVector<T>::CVector(int nParam)
	: m_maximumsize(4096)
	, m_arraysize(0)
	, m_allocsize(nParam)
{
	if (nParam >= m_maximumsize)
		nParam = m_maximumsize - 1;

	// 만약 nParam이 -1이거나 0 이하의 수일 경우 예외처리
	else if (nParam <= 0)
		nParam = 1;

	m_vectorarray = new T[nParam];
#ifdef _DEBUG
	std::cout << "CVector(int)가 호출되었습니다." << std::endl;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
CVector<T>::CVector(const CVector &rhs)
	: m_maximumsize(rhs.m_maximumsize)
	, m_arraysize(rhs.m_arraysize)
	, m_allocsize(rhs.m_allocsize)
{
	m_vectorarray = new T[m_allocsize];

	memcpy_s(m_vectorarray, sizeof(T) * m_arraysize,
			rhs.m_vectorarray, sizeof(T) * rhs.m_arraysize);

#ifdef _DEBUG
	std::cout << "CVector(CVector&)가 호출되었습니다." << std::endl;
#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
CVector<T>::CVector(CVector &&rhs)
	: m_maximumsize(rhs.m_maximumsize)
	, m_arraysize(rhs.m_arraysize)
	, m_allocsize(rhs.m_allocsize)
{
	m_vectorarray = rhs.m_vectorarray;

	rhs.m_vectorarray = nullptr;

#ifdef _DEBUG
	std::cout << "CVector(CVector&&)가 호출되었습니다." << std::endl;
#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
CVector<T>::~CVector()
{
	Release();
}

/////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
CVector<T>& CVector<T>::operator=(const CVector & rhs)
{
#ifdef _DEBUG
	std::cout << "operator=(&rhs) 호출되었습니다." << std::endl;
#endif

	if (this == &rhs)
		return *this;

	else
		memcpy_s(m_vectorarray, sizeof(T) * m_arraysize,
				rhs.m_vectorarray, sizeof(T) * rhs.m_arraysize);

	m_arraysize = rhs.m_arraysize;
	m_allocsize = rhs.m_allocsize;

	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
CVector<T>& CVector<T>::operator=(const CVector && rhs)
{
#ifdef _DEBUG
	std::cout << "operator=(&&rhs) 호출되었습니다." << std::endl;
#endif

	m_vectorarray = rhs.m_vectorarray;
	rhs.m_vectorarray = nullptr;

	return *this;

}

/////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void CVector<T>::Release(void)
{
	// m_vectorarray가 nullptr가 아닐 경우에만 delete를 수행합니다.
	if (nullptr != m_vectorarray)
		delete[] m_vectorarray;

	// m_vectorarray의 값을 초기화합니다.
	m_vectorarray = nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
T CVector<T>::AddBack(T dParam)
{
	// 가변 길이 구현
	if (m_arraysize == m_allocsize)
	{
		// new 연산으로 가변 길이 만들기
		m_vectorarray = AllocFunc(m_vectorarray);
		
	}
	m_vectorarray[m_arraysize] = dParam;

	++m_arraysize;

	return m_vectorarray[m_arraysize - 1];
}

/////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
T CVector<T>::Insert(T dParam, int nIndex)
{
	if (m_arraysize < nIndex)
		AddBack(dParam);

	else
	{
		if ( (m_arraysize - 1) == m_allocsize )
			m_vectorarray = AllocFunc(m_vectorarray);

		for (int i = m_arraysize - 1; i > nIndex; --i)
		{
			m_vectorarray[i] = m_vectorarray[i - 1];
		}

		m_vectorarray[nIndex] = dParam;

		++m_arraysize;
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
int CVector<T>::Delete(T tParam)
{
	int i = 0;
	double dTmp = 0;

	// tParam으로 인덱스 값이 넘어왔을 경우입니다.
	if (0 == (tParam - (int)tParam))
		if (tParam < m_arraysize)
		{
			for (i = (int)tParam; i < m_arraysize - 1; ++i)
				m_vectorarray[i] = m_vectorarray[i + 1];

			--m_arraysize;
		}
		else
		{
			puts("올바르지 않은 인덱스입니다.");
			_getch();
			return 0;
		}

	// tParam으로 데이터 값이 넘어왔을 경우입니다.
	else if (0 != (tParam - (int)tParam))
	{
		while (tParam != dTmp && i != m_arraysize)
		{
			dTmp = m_vectorarray[i];
			++i;
		}

		if (dTmp == tParam)
		{
			for (; i < m_arraysize - 1; ++i)
				m_vectorarray[i] = m_vectorarray[i + 1];

			--m_arraysize;
		}

		else
		{
			puts("데이터에 없는 값입니다.");
			_getch();
		}

	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
T CVector<T>::Search(T tParam) const
{
	int i = 0;
	double dTmp = 0;

	// tParam이 인덱스 값일 경우입니다.
	if ( 0 == (tParam - (int)tParam) )
		if (tParam >= 0 && tParam < m_arraysize)
			return m_vectorarray[(int)tParam];

	// tParam이 데이터 값일 경우입니다.
		else if ((tParam - (int)tParam) != 0)
			while (tParam != dTmp && i != m_arraysize)
			{
				dTmp = m_vectorarray[i];
				++i;
			}

	if (tParam == dTmp)
	{
		printf("%f는 %d번 인덱스에 있습니다.\n", (double)tParam, i);
		_getch();
	}

	else
	{
		printf("데이터에 없습니다.\n");
		_getch();
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
T CVector<T>::GetAt(int nIndex) const
{
	int i = 0;
	int dTmp = 0;

	if (nIndex >= 0 && nIndex < m_arraysize)
		return m_vectorarray[nIndex];

	return 0;
}

template <typename T>
void CVector<T>::PrintAll(void) const
{
	for (int i = 0; i < m_arraysize; ++i)
		std::cout << "Vector[" << i << "] : " << m_vectorarray[i] << std::endl;

	std::cout << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
T *CVector<T>::AllocFunc(T *pArray)
{
	T *pTmp = pArray;
	m_allocsize += ALLOCSIZE;
	
	T *pNewArray = new T[m_allocsize];
	pArray = pNewArray;
	pNewArray = nullptr;
	memcpy_s( pArray, sizeof(T) * m_allocsize, pTmp, sizeof(T) * (m_allocsize - ALLOCSIZE) );

	delete pTmp;

	return pArray;
}

/////////////////////////////////////////////////////////////////////////////////////////////
