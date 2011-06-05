/*
This source file is part of OneU Engine.
Copyright (c) 2011 Ladace

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
/**
 * @file Memory.h
 * @brief �ڴ����
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
//level 0
#include "OneUPreDef.h"
#include <new>
namespace OneU
{
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief �ڴ�������ӿ�
	 *
	 * @remarks ������ʵ��Interface��ȵĻ�ʯ������޷���Interface����
	 */
	/* ----------------------------------------------------------------------------*/
	class IAllocator
		//: public Interface
	{
	private:
		//��ֹ����
		IAllocator(const IAllocator&);
		IAllocator& operator=(const IAllocator&);
	public:
		IAllocator(){}
		virtual ~IAllocator(){}
	public:
		virtual void* alloc(size_t count) = 0;
		virtual void* alloc(size_t count, const char* filename, const int Line, const wchar* comment = NULL) = 0;
		virtual void dealloc(void* _ptr) = 0;
		virtual void destroy() = 0;
		//���԰汾�߱�����ڴ�й¶����
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ����Ƿ����ڴ�й¶
		 *
		 * һ����˵ֻ�е��԰汾�������á�
		 *
		 * @todo Ŀǰ�ú���ʱ���Ĭ���ڴ������ʵ�ֵġ�Ӧ�ý�������������ڴ�й¶���ߴ�����룬���ܹ��Զ����ڴ����������������������Ƿ���Ҫ�д���֤��
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void checkLeaks() = 0;
	};
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief Ĭ���ڴ����������
	 *
	 * @return �ڴ�������ӿ�
	 */
	/* ----------------------------------------------------------------------------*/
	extern "C" ONEU_BASE_API IAllocator* Allocator_create();
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief �����ڴ����������
	 *
	 * @param af �ڴ����������
	 */
	/* ----------------------------------------------------------------------------*/
	extern "C" ONEU_BASE_API void Allocator_build(IAllocator* (*af)());
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief ��ȡ�ڴ����������
	 *
	 * @return ����
	 */
	/* ----------------------------------------------------------------------------*/
	extern "C" ONEU_BASE_API IAllocator& GetAllocator();
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief �����ڴ����������
	 */
	/* ----------------------------------------------------------------------------*/
	extern "C" ONEU_BASE_API void Allocator_destroy();
}

//comment�ᱻ��¼���ڴ����
inline void* operator new(size_t count, OneU::IAllocator* allocator, int/*Ŀǰ��������AllocatedObject��new��ԭ�� �������*/, const char* filename, const int Line, const OneU::wchar* comment = NULL){
	return allocator->alloc(count, filename, Line, comment);
}
//comment�ᱻ��¼���ڴ����
inline void* operator new[](size_t count, OneU::IAllocator* allocator, const char* filename, const int Line, int/*��ֹϵͳѡ��operator new����������operator new[]*/, const OneU::wchar* comment = NULL){
	size_t* p = (size_t*)allocator->alloc(count + sizeof(size_t), filename, Line, comment);

	*p = count;
	return ++p;
}

//��effective c++ #52
inline void operator delete(void* _ptr, OneU::IAllocator* allocator, int, const char* filename, const int Line, const OneU::wchar* comment){
	allocator->dealloc(_ptr);
}
//��effective c++ #52
inline void operator delete[](void* _ptr, OneU::IAllocator* allocator, const char* filename, const int Line, int, const OneU::wchar* comment){
	allocator->dealloc((size_t*)_ptr - 1);
}

namespace OneU
{
	template<class T>
	void _doDelete(T* _ptr, IAllocator* allocator, const char* filename, const int Line){
		_ptr->~T();
		allocator->dealloc(_ptr);
	}

	//@todo �����ж��Ƿ�Ϊ�����������Ż�
	template<class T>
	void _doDeleteArray(T* _ptr, IAllocator* allocator, const char* filename, const int Line){
		T* p = _ptr;
		size_t* s = (size_t*)_ptr - 1;
		ONEU_ASSERT(*s % sizeof(T) == 0);
		for(uint32 i = 0; i < *s / sizeof(T); ++i, ++p)
			p->~T();
		allocator->dealloc(s);
	}
}

/* ----------------------------------------------------------------------------*/
/**
 * @brief new��
 *
 * ����AllocatedObject������Interface��ʱ��ʹ�øú����new������Debugģʽ��׷�����ڴ档
 */
/* ----------------------------------------------------------------------------*/
//ʹ��ONEU�ڴ������������������
//ʹ�øú괴���Ķ�����Կ�dll���١�
#define ONEU_NEW new(&OneU::GetAllocator(), __FILE__, __LINE__)
#define ONEU_DELETE delete


/* ----------------------------------------------------------------------------*/
/**
 * @brief ����new��
 *
 * ����ԭ�����ͣ��Ƕ�̳����Ϳ��øúꡣ�ú�ʹ���ڴ����������֤�ڴ������ͬһ��DLL�ڡ�
 * ʹ��ONEU_DELETE_Tɾ����
 */
/* ----------------------------------------------------------------------------*/
#define ONEU_NEW_T(v) new(&OneU::GetAllocator(), int(), __FILE__, __LINE__) v

/* ----------------------------------------------------------------------------*/
/**
 * @brief OneU new�꣨����ע�ͣ�
 *
 * @todo ������ע�͡�δʵ�֡�
 */
/* ----------------------------------------------------------------------------*/
#define ONEU_NEW_C(v, comment) new(&OneU::GetAllocator(), __FILE__, __LINE__, c) v
//ʹ��ONEU���õ��ڴ�ش�������
//����ֱ�����ڴ�غ����ͷ� �������ONEU_DELETE��
#define ONEU_NEW_ARRAY_T(v) new(&OneU::GetAllocator(), __FILE__, __LINE__, int(), NULL) v
#define ONEU_NEW_ARRAY_T_C(v) new(&OneU::GetAllocator(), __FILE__, __LINE__, int(), c) v

/* ----------------------------------------------------------------------------*/
/**
 * @brief delete��
 */
/* ----------------------------------------------------------------------------*/
#define ONEU_DELETE_T(v) _doDelete(v, &OneU::GetAllocator(), __FILE__, __LINE__)
#define ONEU_DELETE_ARRAY_T(v) _doDeleteArray(v, &OneU::GetAllocator(), __FILE__, __LINE__)

/* ----------------------------------------------------------------------------*/
/**
 * @brief �����ڴ��
 *
 * ʹ��ONEU�ڴ���������������ڴ档
 * ��������ڴ�ɿ�dll���١�
 */
/* ----------------------------------------------------------------------------*/
#define ONEU_ALLOC(size) OneU::GetAllocator().alloc(size, __FILE__, __LINE__)
#define ONEU_ALLOC_C(size,comment) OneU::GetAllocator().alloc(size, __FILE__, __LINE__, c)

/* ----------------------------------------------------------------------------*/
/**
 * @brief �����ڴ��
 */
/* ----------------------------------------------------------------------------*/
#define ONEU_DEALLOC(p) OneU::GetAllocator().dealloc(p)


namespace OneU
{

	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief �ɷ��������
	 *
	 * ֱ�ӱ������ڴ����������Ķ����ࡣ
	 * @remarks �������new��delete����ʹ���ڴ����������֧��ONEU_NEW�����ڵ��ԡ�
	 */
	/* ----------------------------------------------------------------------------*/
	class AllocatedObject{
	public:
		void* operator new(size_t count, OneU::IAllocator* allocator, const char* filename, const int Line, const OneU::wchar* comment = NULL){
			return allocator->alloc(count, filename, Line, comment);
		}
		void* operator new(size_t count){
			return GetAllocator().alloc(count);
		}
		void operator delete(void* _ptr, OneU::IAllocator* allocator, const char* filename, const int Line, const OneU::wchar* comment){
			GetAllocator().dealloc(_ptr);
		}
		void operator delete(void* _ptr){
			GetAllocator().dealloc(_ptr);
		}
		void* operator new[](size_t count, OneU::IAllocator* allocator, const char* filename, const int Line, const OneU::wchar* comment = NULL){
			return allocator->alloc(count, filename, Line, comment);
		}
		void* operator new[](size_t count){
			return GetAllocator().alloc(count);
		}
		void operator delete[](void* _ptr){
			GetAllocator().dealloc(_ptr);
		}
		void operator delete[](void* _ptr, OneU::IAllocator* allocator, const char* filename, const int Line, const OneU::wchar* comment){
			GetAllocator().dealloc(_ptr);
		}
	};
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief �Զ�ָ��
	 * ֧��ONEU_NEW_T
	 *
	 * @remarks reserved.���ܻ���δ���İ汾ɾ����
	 */
	/* ----------------------------------------------------------------------------*/
	template<class T>
	class AutoPtr
	{
	private:
		mutable T* _p;
	public:
		typedef T* pointer;
		explicit AutoPtr(T* p)
			: _p(p)
		{}
		AutoPtr(const AutoPtr& rhs)
			: _p(rhs._p)
		{
			rhs._p = NULL;
		}
		AutoPtr& operator=(const AutoPtr& rhs){
			_p = rhs._p;
			rhs._p = NULL;
		}
		~AutoPtr(){
			if(_p != NULL) ONEU_DELETE_T(_p);
		}
		T* operator->(){ return _p; }
		T& operator*(){ return *_p; }
		operator pointer(){ return _p;}
	};
}