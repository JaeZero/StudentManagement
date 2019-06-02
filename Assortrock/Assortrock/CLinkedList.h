#pragma once

#include <assert.h>

template <typename T>
class CNode
{

	template <typename T>
	friend class CLinkedList;

	// iterator �� node�� ������ �� �־�� �Ѵ�.

	template <typename T>
	friend class CListIterator;

	template <typename T>
	friend class CListReverseIterator;

private:
	typedef CNode<T>* PNODE;
	typedef CNode<T> NODE;

private:
	CNode()
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	~CNode()
	{

	}


private:
	PNODE	m_pNext;
	PNODE	m_pPrev;
	T		m_Data;


};


template<typename T>
class CListReverseIterator
{

private:

	// ����Ʈ�� ���ٱ����� �ش�.

	template <typename T>
	friend class CLinkedList;


private:
	typedef CNode<T>* PNODE;
	typedef CNode<T> NODE;

public:
	CListReverseIterator()
	{
		m_pNode = nullptr;
	}

	~CListReverseIterator()
	{

	}

	bool operator ==(const CListReverseIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator !=(const CListReverseIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}


	void operator ++()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	void operator --()
	{
		m_pNode = m_pNode->m_pNext;
	}

	T& operator *()
	{
		return m_pNode->m_Data;
	}



private:
	PNODE m_pNode;


};


template<typename T>
class CListIterator
{

private:

	// ����Ʈ�� ���ٱ����� �ش�.

	template <typename T>
	friend class CLinkedList;


private:
	typedef CNode<T>* PNODE;
	typedef CNode<T> NODE;

public:
	CListIterator()
	{
		m_pNode = nullptr;
	}

	~CListIterator()
	{

	}

	bool operator ==(const CListIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator !=(const CListIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}


	void operator ++()
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator --()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	T& operator *()
	{
		return m_pNode->m_Data;
	}

	

private:
	PNODE m_pNode;


};


template <typename T>
class CLinkedList
{


private:
	typedef CNode<T> NODE;
	typedef CNode<T>* PNODE;


public:
	typedef CListIterator<T> iterator;
	typedef CListReverseIterator<T> reverse_iterator;


public:
	CLinkedList()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}	

	~CLinkedList()
	{
		clear();
		
		delete m_pBegin;
		delete m_pEnd;
	}

	iterator begin() const
	{
		iterator iter;
		iter.m_pNode = m_pBegin->m_pNext;

		return iter;
	}

	iterator end() const
	{
		iterator iter;
		iter.m_pNode = m_pEnd; // != iterEnd�� ǥ���İ� ���缭 ����Ϸ��� end�� �־�� �Ѵ�.

		return iter;
	}
	// rbegin end�� ������� ���� ����.
	reverse_iterator rbegin() const
	{
		reverse_iterator iter;
		iter.m_pNode = m_pEnd->m_pPrev;
		
		return iter;
	}

	// rend�� ��� ���۳��

	reverse_iterator rend() const
	{
		reverse_iterator iter;
		iter.m_pNode = m_pBegin;

		return iter;
	}

	iterator erase(const iterator& iter)
	{
		if (iter.m_pNode == nullptr || iter.m_pNode == m_pEnd || iter.m_pNode == m_pBegin)
			assert(false);


		// iter�� ����Ű�� ��带 �����ϰ�, ���� ����� �ּҸ� �ѱ��.
		
		PNODE pDelete = iter.m_pNode;
		PNODE pPrev = pDelete->m_pPrev;
		PNODE pNext = pDelete->m_pNext;
		
		// ���� ����� ������ ���� ���
		pPrev->m_pNext = pNext;

		// ���� ����� ������ ���� ���
		pNext->m_pPrev = pPrev;

		delete pDelete;
		--m_iSize;

		iterator result;

		result.m_pNode = pNext;

		return result;
	}

	reverse_iterator erase(const reverse_iterator& iter)
	{
		if (iter.m_pNode == nullptr || iter.m_pNode == m_pEnd || iter.m_pNode == m_pBegin)
			assert(false);


		PNODE pDelete = iter.m_pNode;
		PNODE pPrev = pDelete->m_pPrev;
		PNODE pNext = pDelete->m_pNext;

		pPrev->m_pNext = pNext;

		pNext->m_pPrev = pPrev;

		delete pDelete;
		--m_iSize;

		reverse_iterator result;

		result.m_pNode = pPrev;

		return result;
	}

	int size() const
	{
		return m_iSize;
	}

	void push_back(const T& data)
	{
		PNODE pNode = new NODE;

		pNode->m_Data = data;

		PNODE pPrev = m_pEnd->m_pPrev; // end�� �������

		// ���� ���� ����� ���� ���� end
		// end�� ���� ���� ���� ������ ���

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		// end�� ��������� ������ ���� ������ ���
		// ���� ������ ����� ������ end�� �������

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		++m_iSize;
	}

	void push_front(const T& data)
	{
		PNODE pNode = new NODE;

		pNode->m_Data = data;

		PNODE pNext = m_pBegin->m_pNext; // Begin�� �� ���

		// push_front �� begin ���� begin�� �� ��� ���̿� �����Ѵ�.

		// begin�� �ճ��� ���� ������ ���
		// ���� ������ ����� ���� ���� begin���

		m_pBegin->m_pNext = pNode;
		pNode->m_pPrev = m_pBegin;

		// ���� ������ ����� �� ���� begin�� �ճ��
		// begin�� �ճ���� ������ ���� ������ ���

		pNode->m_pNext = pNext;
		pNext->m_pPrev = pNode;

		++m_iSize;
	}

	bool empty()
	{
		return m_iSize == 0;
	}

	void clear()
	{
		// begin�� end�� �����ϰ� �����͸� ������ ����.

		PNODE pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			PNODE pNext = pNode->m_pNext;

			delete pNode;

			pNode = pNext;
		}

		m_iSize = 0;
		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	void pop_front()
	{
		
		if (empty())
			assert(false);

		// �����Ϸ��� ���
		PNODE pDelete = m_pBegin->m_pNext;
		
		// �����Ϸ��� ����� ���� ���
		PNODE pNext = pDelete->m_pNext;


		// begin�� ���� ���� �����Ϸ��� ����� ���� ���
		// �����Ϸ��� ����� ���� ����� ������ begin���
		m_pBegin->m_pNext = pNext;
		pNext->m_pPrev = m_pBegin;

		delete pDelete;

		--m_iSize;

	}

	void pop_back()
	{
		if (empty())
			assert(false);


		PNODE pDelete = m_pEnd->m_pPrev;
		PNODE pPrev = pDelete->m_pPrev;

		// �����Ϸ��� ����� ��������� ������ end
		pPrev->m_pNext = m_pEnd;
		// end�� �������� ���� ���
		m_pEnd->m_pPrev = pPrev;


		delete pDelete;

		--m_iSize;
	}


	T front() const
	{
		if (empty())
			assert(false);

		return m_pBegin->m_pNext->m_Data;
	}

	T back() const
	{
		if (empty())
			assert(false);

		return m_pEnd->m_pNext->m_Data;
	}

	void sort(bool(*func)(const T& src, const T& dest))
	{
		// func �� �������� ����.

		for (PNODE pFirst = m_pBegin->m_pNext; pFirst != m_pEnd->m_pPrev; pFirst = pFirst->m_pNext)
		{
			for (PNODE pSecond = pFirst->m_pNext; pSecond != m_pEnd; pSecond = pSecond->m_pNext)
			{
				if (func(pFirst->m_Data, pSecond->m_Data))
				{
					// �����͸� ����

					T temp = pFirst->m_Data;
					pFirst->m_Data = pSecond->m_Data;
					pSecond->m_Data = temp;

					// �ڸ���� (���������̶��...) ���� ����� ������ ���� ���� ���� ã�Ƽ� �� �ڸ��� �ְ�
					// �ٽ� �ڸ���� �ݺ�...

				}
			}
		}

	}

private:
	PNODE	m_pBegin;
	PNODE	m_pEnd;
	int		m_iSize;



};

