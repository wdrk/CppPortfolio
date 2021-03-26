#pragma once

template <typename T>
class CVector
{
public:
	CVector() = delete;
	explicit CVector(int);
	CVector(const CVector &);
	CVector(CVector &&);
	virtual ~CVector();

	CVector<T>& operator=(const CVector &rhs);
	CVector<T>& operator=(const CVector &&rhs);

private:
	const int m_maximumsize;

public:
	// 사용자가 직접 멤버 변수에 접근하여 변경하면 기존의 벡터 코드가 오동작할 확률이 매우 높음.
	// 멤버 변수는 되도록 private로...
	// 변수 목록입니다.
	int m_arraysize;
	int m_allocsize;
	T *m_vectorarray;

	// 함수 목록입니다.
	T AddBack(T);
	T Insert(T, int);
	int Delete(T);
	T Search(T) const;
	T GetAt(int) const;
	void PrintAll(void) const;
	void Release(void);

	// AllocFunc 함수에서 수행하는 기능은 벡터 내부에서 사용될 기능으로
	// 사용자가 직접 호출해서 사용하는 함수로 보이지 않습니다.
	// 다시말하면 인터페이스가 아닌 상세 구현의 내용으로 굳이 public으로 접근할 수 있게
	// 할 필요는 없어보입니다.
	T *AllocFunc(T*);

};

