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
	// ����ڰ� ���� ��� ������ �����Ͽ� �����ϸ� ������ ���� �ڵ尡 �������� Ȯ���� �ſ� ����.
	// ��� ������ �ǵ��� private��...
	// ���� ����Դϴ�.
	int m_arraysize;
	int m_allocsize;
	T *m_vectorarray;

	// �Լ� ����Դϴ�.
	T AddBack(T);
	T Insert(T, int);
	int Delete(T);
	T Search(T) const;
	T GetAt(int) const;
	void PrintAll(void) const;
	void Release(void);

	// AllocFunc �Լ����� �����ϴ� ����� ���� ���ο��� ���� �������
	// ����ڰ� ���� ȣ���ؼ� ����ϴ� �Լ��� ������ �ʽ��ϴ�.
	// �ٽø��ϸ� �������̽��� �ƴ� �� ������ �������� ���� public���� ������ �� �ְ�
	// �� �ʿ�� ����Դϴ�.
	T *AllocFunc(T*);

};

