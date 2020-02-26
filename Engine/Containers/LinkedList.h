#pragma once
#include <type_traits>
#include "assert.h"

namespace Engine
{
	template<typename T>
	struct listNode
	{
		T value;
		listNode<T> *next;
		listNode()
		{
			next = nullptr;
		}
	};

	template<class T>
	class LinkedList
	{
	public:
		LinkedList()
		{
			head = nullptr;
		}

		int Count();
	
		T GetAt(int pos);

		void RemoveAt(int pos);

		bool Remove(T item);

		bool Contains(const T item);

		void Add(const T);

		void DeleteList();

	private:
		listNode<T> *head;
		int count = 0;
	};

	template<class T>
	inline int LinkedList<T>::Count()
	{
		return count;
	}

	template<class T>
	inline T LinkedList<T>::GetAt(int pos)
	{
		if (pos > count-1 || pos < 0)
		{
			return head->value;
		}

		listNode<T> * curPos = head;
		int i = 0;
		while (i < pos)
		{
			curPos = curPos->next;
			i++;
		}
		return curPos->value;
	}

	template<class T>
	inline void LinkedList<T>::RemoveAt(int pos)
	{
		if (pos > count-1 || pos < 0)
		{
			return;
		}

		assert(head);

		listNode<T> * curPos = head;
		count--;

		if (pos == 0)
		{
			head = head->next;
			delete curPos;
			return;
		}

		int i = 0;
		pos--;
		while (i < pos)
		{
			curPos = curPos->next;
			i++;
		}

		listNode<T> * temp = curPos->next;
		curPos->next = curPos->next->next;
		delete temp;
	}

	template<class T>
	inline bool LinkedList<T>::Remove(T item)
	{
		if (item == nullptr)
		{
			return false;
		}

		assert(head);

		listNode<T> * curPos = head;
		listNode<T> * prevPos = head;
		listNode<T> * temp;
		while (curPos != nullptr)
		{
			temp = curPos;
			curPos = curPos->next;
			if (temp->value == item)
			{
				delete temp;
				prevPos->next = curPos;
				return true;
			}
		}
		return false;
	}

	template<class T>
	inline bool LinkedList<T>::Contains(const T item)
	{
		if (item == nullptr)
		{
			return false;
		}

		assert(head);

		listNode<T> * curPos = head;
		while (curPos != nullptr)
		{
			if (curPos->value == item)
			{
				return true;
			}
			curPos = curPos->next;
		}
		return false;
	}

	template<class T>
	inline void LinkedList<T>::Add(const T obj)
	{
		listNode<T> * temp = new listNode<T>;
		if (head == nullptr)
		{
			head = temp;
			head->next = nullptr;
			head->value = obj;
		}
		else
		{
			temp->next = head;
			temp->value = obj;
			head = temp;
		}
		count++;
	}

	template<class T>
	inline void LinkedList<T>::DeleteList()
	{
		listNode<T> * temp;
		while (head != nullptr)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}
}