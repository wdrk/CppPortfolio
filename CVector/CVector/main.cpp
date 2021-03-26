#include <iostream>
#include <conio.h>
#include "Vector.h"


#define ALLOCSIZE 4



/**************************************************************************************

#	������		:	������
#	����ȯ��		:	Visual Studio 2017
#	���߱Ⱓ		:	2019.2.19. AM 9:00 ~ PM 17:00
#	�����Ϸ�		:	2019.11.22. AM 3:39
#	���߸�ǥ		:	CVector(�ڵ����� �޸𸮸� �������� �Ҵ��ϴ� �����̳�)�� ���ø� �������� �����ϱ�

**************************************************************************************/



/////////////////////////////////////////////////////////////////////////////////////////////
auto main(void) -> int
{

	/*
	main()�� �ڵ�� CVector�� �� �۵��ϴ��� Ȯ���ϴ� Test�� �ڵ��Դϴ�.
																*/

	std::cout << "<double> �ν��Ͻ��� ����ϴ�." << std::endl;
	CVector<double> vector(4);

	// ������ ����
	std::cout << "������ push_back : " << vector.AddBack(1.1) << std::endl;

	// 0�� �ε����� �� ��������
	std::cout << "[0] �� �ε����� �� �������� : " << vector.GetAt(0) << std::endl;

	// ������ ����
	std::cout << "������ push_back : " << vector.AddBack(2.1) << std::endl;
	std::cout << "������ push_back : " << vector.AddBack(3.1) << std::endl;
	std::cout << "������ push_back : " << vector.AddBack(4.1) << std::endl;

	// 3�� ����� �� ��������
	std::cout << "[3] �� �ε����� �� �������� : " << vector.GetAt(3) << std::endl;

	// ���� �迭�� �˸��� ���� �ε����� ���� �����ϸ� �ڵ����� ������ ����� ���� �ε��� ������ �����ؼ� �����͸� �߰��մϴ�.
	vector.Insert(5.1, 7);
	std::cout << "[7] �� �ε����� '5.1' ���� �߰���" << std::endl;

	// 3�� ����� ���� ����� ���� �ε����� ��带 �����մϴ�.
	vector.Delete(3);
	std::cout << "[3] �� �ε����� ���� ������" << std::endl;
	std::cout << "���� �� ���� [3] �� �ε����� �� �������� : " << vector.GetAt(3) << std::endl;

	std::cout << "���� Vector�� ��ü ������ ���" << std::endl;
	vector.PrintAll();

	std::cout << "vector<double> �迭 ��� ���� : " << vector.m_arraysize << std::endl;
	std::cout << std::endl;
	std::cout << "********************************************************" << std::endl;
	std::cout << std::endl;
	//////////////////////////////////////////////////////////////////////////////////

	std::cout << "<int> �ν��Ͻ��� ����ϴ�." << std::endl;
	CVector<int> vectorint(8);

	std::cout << "������ push_back : " << vectorint.AddBack(1) << std::endl;
	std::cout << "[0] �� �ε����� �� �������� : " << vectorint.GetAt(0) << std::endl;

	std::cout << "������ push_back : " << vectorint.AddBack(2) << std::endl;
	std::cout << "������ push_back : " << vectorint.AddBack(3) << std::endl;
	std::cout << "������ push_back : " << vectorint.AddBack(4) << std::endl;
	std::cout << "[3] �� �ε����� �� �������� : " << vectorint.GetAt(3) << std::endl;

	vectorint.Insert(5, 7);
	std::cout << "[7] �� �ε����� '5' ���� �߰���" << std::endl;

	//std::cout << "������ push_back : " << vectorint.AddBack(5) << std::endl;
	std::cout << "������ push_back : " << vectorint.AddBack(6) << std::endl;
	std::cout << "������ push_back : " << vectorint.AddBack(8) << std::endl;

	vectorint.Delete(5);
	std::cout << "[5] �� �ε����� ���� ������" << std::endl;
	std::cout << "���� �� ���� [5] �� �ε����� �� �������� : " << vectorint.GetAt(5) << std::endl;
	std::cout << "���� Vector�� ��ü ������ ���" << std::endl;
	vectorint.PrintAll();

	std::cout << "vector<int> �迭 ��� ���� : " << vectorint.m_arraysize << std::endl;
	std::cout << "********************************************************" << std::endl;

	//////////////////////////////////////////////////////////////////////////////////////////

	std::cout << "����� �Ϸ��߽��ϴ�. �ƹ� Ű�� �����ּ���." << std::endl;
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

	// ���� nParam�� -1�̰ų� 0 ������ ���� ��� ����ó��
	else if (nParam <= 0)
		nParam = 1;

	m_vectorarray = new T[nParam];
#ifdef _DEBUG
	std::cout << "CVector(int)�� ȣ��Ǿ����ϴ�." << std::endl;
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
	std::cout << "CVector(CVector&)�� ȣ��Ǿ����ϴ�." << std::endl;
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
	std::cout << "CVector(CVector&&)�� ȣ��Ǿ����ϴ�." << std::endl;
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
	std::cout << "operator=(&rhs) ȣ��Ǿ����ϴ�." << std::endl;
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
	std::cout << "operator=(&&rhs) ȣ��Ǿ����ϴ�." << std::endl;
#endif

	m_vectorarray = rhs.m_vectorarray;
	rhs.m_vectorarray = nullptr;

	return *this;

}

/////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void CVector<T>::Release(void)
{
	// m_vectorarray�� nullptr�� �ƴ� ��쿡�� delete�� �����մϴ�.
	if (nullptr != m_vectorarray)
		delete[] m_vectorarray;

	// m_vectorarray�� ���� �ʱ�ȭ�մϴ�.
	m_vectorarray = nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
T CVector<T>::AddBack(T dParam)
{
	// ���� ���� ����
	if (m_arraysize == m_allocsize)
	{
		// new �������� ���� ���� �����
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

	// tParam���� �ε��� ���� �Ѿ���� ����Դϴ�.
	if (0 == (tParam - (int)tParam))
		if (tParam < m_arraysize)
		{
			for (i = (int)tParam; i < m_arraysize - 1; ++i)
				m_vectorarray[i] = m_vectorarray[i + 1];

			--m_arraysize;
		}
		else
		{
			puts("�ùٸ��� ���� �ε����Դϴ�.");
			_getch();
			return 0;
		}

	// tParam���� ������ ���� �Ѿ���� ����Դϴ�.
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
			puts("�����Ϳ� ���� ���Դϴ�.");
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

	// tParam�� �ε��� ���� ����Դϴ�.
	if ( 0 == (tParam - (int)tParam) )
		if (tParam >= 0 && tParam < m_arraysize)
			return m_vectorarray[(int)tParam];

	// tParam�� ������ ���� ����Դϴ�.
		else if ((tParam - (int)tParam) != 0)
			while (tParam != dTmp && i != m_arraysize)
			{
				dTmp = m_vectorarray[i];
				++i;
			}

	if (tParam == dTmp)
	{
		printf("%f�� %d�� �ε����� �ֽ��ϴ�.\n", (double)tParam, i);
		_getch();
	}

	else
	{
		printf("�����Ϳ� �����ϴ�.\n");
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
