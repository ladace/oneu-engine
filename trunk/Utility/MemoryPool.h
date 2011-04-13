#include "../Base/Base.h"
#include <boost/pool/pool_alloc.hpp>
//�ڴ�ع�����
namespace OneU
{
	//ʹ��BOOST POOL���
	namespace Memory
	{
#ifndef ONEU_NO_BOOST
		template<class T>
		inline T* Allocate()
		{
			return boost::pool_allocator<T>::allocate(sizeof(T));
		}
		template<class T>
		inline void Deallocate(T* ptr)
		{
			boost::pool_allocator<T>::deallocate(ptr, sizeof(T));
		}
#else
		template<class T>
		inline T* Allocate()
		{
			return new T();
		}
		template<class T>
		inline void Deallocate(T* ptr)
		{
			delete ptr;
		}
#endif
	}
}