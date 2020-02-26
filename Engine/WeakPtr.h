#pragma once

namespace Engine
{
	template<class T>
	class WeakPtr
	{
	public:
		WeakPtr(T * i_ptr = NULL);

		WeakPtr(const WeakPtr & i_other);

		WeakPtr(T * i_ptr) :
			m_ptr(i_ptr)
		{
			m_RefCounts.WeakCounts++;
		}

		WeakPtr(const WeakPtr & i_other) :
			m_ptr(i_other.m_ptr), m_refCount(i_other.m_refCount)
		{
			m_refCount->WeakCounts++;
		}

		inline WeakPtr & operator =(const WeakPtr & i_other)
		{
			if (i_other.m_ptr == m_ptr)
			{
				return *this;
			}
			else
			{
				m_RefCounts.WeakCounts--;
				return i_other;
			}
		}

		~WeakPtr()
		{
			if (--m_RefCounts.WeakCount == 0 && m_RefCounts.SmartCount == 0)
			{
				delete m_RefCounts;
			}
		}

		SmartPtr AcquireOwnership()
		{
			if (m_RefCounts.SmartCount > 0)
			{
				return SmartPtr(m_ptr, m_RefCounts);
			}
			else
			{
				return SmartPtr(nullptr, nullptr);
			}
		}

		bool isValid() const { return m_pObject != nullptr; }
		operator bool() const { return isValid(); }

		inline T * operator -> ()
		{
			return m_ptr;
		}

		inline T & operator * ()
		{
			assert(m_ptr != nullptr);
			return *m_ptr;
		}

	private:
		T * m_ptr;
		RefCounts * m_RefCounts;
	};
}