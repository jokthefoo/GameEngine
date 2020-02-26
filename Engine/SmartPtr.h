#pragma once
#include <stdint.h>

namespace Engine
{
	struct RefCounts
	{
		uint32_t SmartCounts;
		uint32_t WeakCounts;

		RefCounts(uint32_t i_SmartCount, uint32_t i_WeakCount) :
			SmartCounts(i_SmartCount), WeakCounts(i_WeakCount)
		{}
	};

	template<class T>
	class SmartPtr
	{
		template<Class U>
		friend class SmartPtr;
	public:
		SmartPtr(T * i_ptr) :
			m_ptr(i_ptr), m_refCount (new RefCounts(1,0))
		{
		}

		SmartPtr(const SmartPtr & i_other) :
			m_ptr(i_other.m_ptr), m_refCount(i_other.m_refCount)
		{
			m_refCount->SmartCount++;
		}

		template<class U>
		SmartPtr(const SmartPtr<U> & i_other) :
			m_ptr(i_other.m_ptr), m_refCount(i_other.m_refCount)
		{
			m_refCount->SmartCount++;
		}

		~SmartPtr()
		{
			if (--(m_refCount.SmartCounts) == 0)
			{
				delete m_ptr;
				if (m_refCount.WeakCounts == 0)
				{
					delete m_refCount;
				}
			}
		}

		inline SmartPtr & operator =(const SmartPtr & i_other)
		{
			if (i_other.m_ptr == m_ptr)
			{
				return *this;
			}
			else
			{
				if (--(m_refCount.SmartCounts) == 0)
				{
					delete m_ptr;
					if (m_refCount.WeakCounts == 0)
					{
						delete m_refCount;
					}
				}
				return i_other;
			}
		}

		inline T * operator -> ()
		{
			return m_ptr;
		}

		inline T & operator * ()
		{
			assert(m_ptr != nullptr);
			return *m_ptr;
		}

		inline bool operator == (T * i_ptr)
		{
			return m_ptr == i_ptr;
		}

		inline bool operator != (T * i_ptr)
		{
			return m_ptr != i_ptr;
		}

		operator bool ()
		{
			return m_ptr != nullptr;
		}
	
	private:
		T * m_ptr;
		RefCounts * m_refCount;
	};
}