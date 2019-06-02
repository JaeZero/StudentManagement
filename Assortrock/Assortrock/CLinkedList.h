#pragma once

#include <assert.h>

template <typename T>
class CNode
{

	template <typename T>
	friend class CLinkedList;

	// iterator 는 node에 접근할 수 있어야 한다.

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

	// 리스트에 접근권한을 준다.

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

	// 리스트에 접근권한을 준다.

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
		iter.m_pNode = m_pEnd; // != iterEnd의 표현식과 맞춰서 사용하려면 end를 넣어야 한다.

		return iter;
	}
	// rbegin end의 이전노드 부터 시작.
	reverse_iterator rbegin() const
	{
		reverse_iterator iter;
		iter.m_pNode = m_pEnd->m_pPrev;
		
		return iter;
	}

	// rend의 경우 시작노드

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


		// iter가 가리키는 노드를 삭제하고, 다음 노드의 주소를 넘긴다.
		
		PNODE pDelete = iter.m_pNode;
		PNODE pPrev = pDelete->m_pPrev;
		PNODE pNext = pDelete->m_pNext;
		
		// 이전 노드의 다음은 다음 노드
		pPrev->m_pNext = pNext;

		// 다음 노드의 이전은 이전 노드
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

		PNODE pPrev = m_pEnd->m_pPrev; // end의 이전노드

		// 새로 생긴 노드의 다음 노드는 end
		// end의 이전 노드는 새로 생성한 노드

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		// end의 이전노드의 다음은 새로 생성한 노드
		// 새로 생성한 노드의 이전은 end의 이전노드

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		++m_iSize;
	}

	void push_front(const T& data)
	{
		PNODE pNode = new NODE;

		pNode->m_Data = data;

		PNODE pNext = m_pBegin->m_pNext; // Begin의 앞 노드

		// push_front 는 begin 노드와 begin의 앞 노드 사이에 존재한다.

		// begin의 앞노드는 새로 생성한 노드
		// 새로 생성한 노드의 이전 노드는 begin노드

		m_pBegin->m_pNext = pNode;
		pNode->m_pPrev = m_pBegin;

		// 새로 생성한 노드의 앞 노드는 begin의 앞노드
		// begin의 앞노드의 이전은 새로 생성한 노드

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
		// begin과 end를 제외하고 데이터를 날리는 과정.

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

		// 삭제하려는 노드
		PNODE pDelete = m_pBegin->m_pNext;
		
		// 삭제하려는 노드의 다음 노드
		PNODE pNext = pDelete->m_pNext;


		// begin의 다음 노드는 삭제하려는 노드의 다음 노드
		// 삭제하려는 노드의 다음 노드의 이전은 begin노드
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

		// 삭제하려는 노드의 이전노드의 다음은 end
		pPrev->m_pNext = m_pEnd;
		// end의 이전노드는 이전 노드
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
		// func 를 기준으로 정렬.

		for (PNODE pFirst = m_pBegin->m_pNext; pFirst != m_pEnd->m_pPrev; pFirst = pFirst->m_pNext)
		{
			for (PNODE pSecond = pFirst->m_pNext; pSecond != m_pEnd; pSecond = pSecond->m_pNext)
			{
				if (func(pFirst->m_Data, pSecond->m_Data))
				{
					// 데이터를 스왑

					T temp = pFirst->m_Data;
					pFirst->m_Data = pSecond->m_Data;
					pSecond->m_Data = temp;

					// 자리잡고 (오름차순이라면...) 다음 노드의 값에서 가장 작은 값을 찾아서 이 자리에 넣고
					// 다시 자리잡고 반복...

				}
			}
		}

	}

private:
	PNODE	m_pBegin;
	PNODE	m_pEnd;
	int		m_iSize;



};

