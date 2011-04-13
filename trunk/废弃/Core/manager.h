/** 
 * @file Manager.h
 * @brief ��������� ����������
 * @author Ladace
 * @version 1.0.0.1
 * @date 2009-10-24
 */

//*****************************************************
//                                             Ladace
// OneU Manager
//���������
// 2009.10
//���������� 2009.10.14
//�����С�����������
//
//*****************************************************

#include "OneULib.h"

#include <list> //���� ���ʹ��SGI�汾

//*****************************************************
//�������� ��д��һ��ͷ�ļ�
//Ŀǰ��û���뵽������
//*****************************************************
#ifdef _DEBUG
#include <assert.h>
#ifndef ASSERT
#define ASSERT(exp) assert(exp)
#endif
#else
#define ASSERT(exp) void( 0 )
#endif
//*************************

//*************************
#include "memory.h"
//*************************

namespace OneU
{
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��������뺯������
	 */
	/* ----------------------------------------------------------------------------*/
	namespace Manager
	{
		//****************************************************************************
		//!\defgroup Hook ����ϵͳ
		//!���ڳ�Ա�����Ĺ���
		//!
		//!ע������������Է�������T��ʲô���붼��һ����
		//!MemCall��һ����Ҫǿ��ת���Ļ����� ClassCall��һ��ģ���ADAPTER �����´�������
		//!�����޲��޷���ֵ�� ����ΪCall
		//*****************************************************************************

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief  ��Ա��������ӡ�һ�㡿
		 * \ingroup Hook
		 */
		/* ----------------------------------------------------------------------------*/
		//
		class MemCall
		{
		public:
			typedef void ( NullClass:: * FuncPointer) ();
			typedef NullClass ClassType;
		private:
			ClassType * const _pObj;
			FuncPointer const _pFunc;
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���캯��
			 * 
			 * @param pFunc NullClass��Ա����ָ��
			 * @param pObj NullClass����ָ��
			 */
			/* ----------------------------------------------------------------------------*/
			//
			MemCall( FuncPointer pFunc, ClassType * pObj)
				:_pFunc( pFunc ), _pObj( pObj ){}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief  ִ�й�����ĺ���
			 */
			/* ----------------------------------------------------------------------------*/
			void operator() () { ( _pObj->*_pFunc )(); }
		};


		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���Ա��������
		 *
		 * MemCall��Adapter
		 * \tparam T ��Ա����������
		 * \ingroup Hook
		 */
		/* ----------------------------------------------------------------------------*/
		template< class T >
		class ClassCall
		{
		public:

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����ָ������
			 */
			/* ----------------------------------------------------------------------------*/
			typedef void (T::* FuncPointer)();

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �������
			 */
			/* ----------------------------------------------------------------------------*/
			typedef T ClassType;
		private:
			MemCall _m;
		public:

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���캯��
			 * 
			 * @param pFunc T�ĳ�Ա��������
			 * @param pObj T�Ķ�������
			 */
			/* ----------------------------------------------------------------------------*/
			ClassCall( FuncPointer pFunc, ClassType *pObj)
				:_m( reinterpret_cast< MemCall::FuncPointer > ( pFunc ), 
				reinterpret_cast< MemCall::ClassType * > ( pObj ) )
			{}
			void operator() () { _m(); }
		};

		//*****************************************************************************
		//!����ӹ�����
		//!
		//!ά��һ����������
		//!\ingroup Hook
		//*****************************************************************************
		class CallManager
		{
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��������
			 */
			/* ----------------------------------------------------------------------------*/
			typedef ::std::list< MemCall > ListType;
		private:
			ListType m_List;
		public:


			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �������빳��
			 * 
			 * @param pFunc ��Ա����ָ��
			 * @param pObj ����ָ��
			 * 
			 * @return ������������������ʾ������λ��
			 */
			/* ----------------------------------------------------------------------------*/
			template < class T >
			ListType::iterator PushBack( void ( T::* pFunc)(), T * pObj )
			{
				m_List.push_back( 
					MemCall( reinterpret_cast< MemCall::FuncPointer > ( pFunc ), 
					reinterpret_cast< MemCall::ClassType * > ( pObj ) ) );
				return m_List.end();
			}
			

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �Ƴ�����
			 * 
			 * @param index ���Ӷ�Ӧ������
			 */
			/* ----------------------------------------------------------------------------*/
			void Remove( ListType::iterator index )
			{
				m_List.erase( index );
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���ȫ�����Ӻ���
			 */
			/* ----------------------------------------------------------------------------*/
			void Clear()
			{
				m_List.clear();
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����ִ�и������Ӻ���
			 */
			/* ----------------------------------------------------------------------------*/
			void Run()
			{
				for( ListType::iterator i=m_List.begin(); i != m_List.end(); i++)

					(*i)();
			}
		};

		//*****************************************************************************
		//������� �����ϵͳ
		//������ܹ���ʮ�� 
		//��Ҫ����������з�����󣻽������طſ�
		//��ģ��ʵ�����ÿռ���������Ҫ��
		//*****************************************************************************


		//!\defgroup ObjectWrapper �����⸲��
		//!�����⸲�� ����ʵ����ȷ��ɾ������

		//!\defgroup ObjectPool �����ϵͳ

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �����⸲������
		 *
		 * Ϊ��ʵ�ֶ�̬�����Ļ���
		 * �����������ÿռ��������Ĺ���
		 * \tparam Alloc ���ø���ռ�Ŀռ�������
		 * \ingroup ObjectWrapper 
		 * \ingroup ObjectPool
		 */
		/* ----------------------------------------------------------------------------*/
		//
		template< class Alloc = alloc >
		class ObjectWrapper_Base
		{
		public:
			virtual ~ObjectWrapper_Base() = 0 {}

			static void * operator new( size_t size )
			{
				return Alloc::allocate( size );
			}
			static void operator delete( void *p, size_t size )
			{
				return Alloc::deallocate( p, size );
			}
		};

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �����⸲��
		 *
		 * ��֧�ְ�ɾ������ɾ������
		 * \tparam T �����Ķ�������
		 * \tparam Alloc ���ø���ռ�Ŀռ�������
		 * \ingroup ObjectWrapper
		 * \ingroup ObjectPool
		 */
		/* ----------------------------------------------------------------------------*/
		template < class T , class Alloc = alloc >
		class ObjectWrapper
			: public ObjectWrapper_Base < Alloc >
		{
		public:
			typedef T ClassType;

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ɾ���� 
			 *
			 * ����԰��������ڴ��ж�ء�
			 * Ϊ��׼�ռ�������ж���ڴ�ĺ���������
			 */
			/* ----------------------------------------------------------------------------*/
			typedef void ( *DeleterPointer )( void * , size_t );
		private:
			ClassType * const _p;
			DeleterPointer const _pDeleter;
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���캯��
			 * 
			 * @param pObj �����Ķ���ָ��
			 * @param pDeleter ɾ����ָ��
			 */
			/* ----------------------------------------------------------------------------*/
			ObjectWrapper( ClassType * pObj, DeleterPointer pDeleter )
				:_p( pObj ), _pDeleter( pDeleter ) {}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��������
			 */
			/* ----------------------------------------------------------------------------*/
			~ObjectWrapper();
		};

		template < class T , class Alloc >
		ObjectWrapper< T, Alloc >::~ObjectWrapper()
		{
			if( !_pDeleter )
				delete _p;
			else
			{
				_p->~ClassType();
				( * _pDeleter )( reinterpret_cast < void * > ( _p ), sizeof( ClassType ) );
			}
		}

		//*****************************************************************************
		//!������������Ϣ���⸲��
		//!
		//!��ģ��Ԫ����ʵ�ֵ� ��С����һ��ָ�� ��Ҫ�������ɴ�����
		//!����һ����Զ����ض���������������ǹ̶��� ���Բ�����벻�����͵ú�����
		//!
		//!\ingroup ObjectWrapper
		//!\ingroup ObjectPool
		//*****************************************************************************
		template< class T, class ObjAlloc, class Alloc = alloc >
		class ObjectWrapper_A
			:public ObjectWrapper_Base < Alloc >
		{
		public:
			ObjectWrapper_A( T * pObj )
				:_p( pObj ){}
			~ObjectWrapper_A();

			T * GetPointer(){ return _p }

			typedef T ClassType;
			typedef ObjAlloc AllocatorType;
		private:
			T * const _p;
		};

		template< class T, class ObjAlloc, class Alloc >
		ObjectWrapper_A< T, ObjAlloc, Alloc >::~ObjectWrapper_A()
		{
			_p->~ClassType();
			ObjAlloc::deallocate( _p, sizeof( ClassType ) );
		}

		//*****************************************************************************
		//!�����
		//!
		//!ע�������Alloc��Wrapper�ķ����� ������Object����Pool�ķ�����
		//!��������漰���ڴ���� Ӧ��Ƴ�Ĭ���ڴ������ ����
		//!\ingroup ObjectPool
		//*****************************************************************************
		template< class Alloc = alloc >
		class _ObjectPool
		{
		private:
			//ɾ���� �����ǹ�����ڴ��ж��  ����֮ǰҪ�ȵ�����������
			typedef void ( *DeleterPointer )( void * , size_t );
			typedef ::std::list< ObjectWrapper_Base< Alloc > * > ListType;

			ListType m_List;

		public:
			template < class T >
			void Attach( T * pObj,DeleterPointer pDeleter = 0 );

			template < class T, class ObjAlloc >
			void Attach( ObjectWrapper_A< T , ObjAlloc, Alloc > * pWrp )
			{
				m_List.push_back( pWrp );
			}
			void Clear();

			bool IsEmpty() const{ return m_List.empty(); }

			~_ObjectPool();
		};

		template< class Alloc >
		_ObjectPool< Alloc >::~_ObjectPool()
		{
			Clear();
		}

		template< class Alloc >
		template< class T >
		void _ObjectPool< Alloc >::Attach( T * pObj, DeleterPointer pDeleter )	
		{
			typedef ObjectWrapper< T, Alloc > Wrapper;

			Wrapper *p = new Wrapper( pObj, pDeleter );
			m_List.push_back( p );
		}

		template< class Alloc >
		void _ObjectPool< Alloc >::Clear()
		{
			for( ListType::iterator i = m_List.begin(); i != m_List.end(); i++)

				delete ( *i );

			m_List.clear();
		}

		//*****************************************************************************
		//!���������
		//!
		//!��װ��n������� ֧�ֽ�������뵽�ض��������	
		//!ע�������Alloc��Wrapper�ķ����� ������Object����ķ�����
		//!\ingroup ObjectPool
		//*****************************************************************************
		template< int n, class Alloc = alloc >
		class _ObjectManager
		{
		private:
			typedef void ( *DeleterPointer )( void * , size_t );
			_ObjectPool< Alloc > m_Pool[ n ];
		public:
			template< class T >
			T * Attach( int index, T * pObj, DeleterPointer pDeleter =0)
			{
				m_Pool[ index ].Attach( pObj, DeleterPointer );
				return pObj;
			}

			template< class T, class ObjAlloc >
			T * Attach( int index, ObjectWrapper_A< T, ObjAlloc, Alloc > * pWrp )
			{
				m_Pool[ index ].Attach( pWrp );
				return pWrp->GetPointer();
			}

			void Clear( int index )
			{
				m_Pool[ index ].Clear();
			}
		};

		//****************************************************************
		//!�����������ǿ
		//!
		//!�ṩ��������
		//!\ingroup ObjectPool
		//****************************************************************
		template< int n, class Alloc = alloc >
		class _ObjectManagerW
			:public _ObjectManager< n, Alloc >
		{
		private:
			CallManager m_CallMgr[ n ];
		public:
			template< class T >
			void InsertFunction( int index, void (T::* pFunc) (), T * pObj)
			{
				m_CallMgr[ index ].PushBack( pFunc, pObj );
			}
			void Clear( int index )
			{
				m_Pool[ index ].Clear();
				m_CallMgr[ index ].Clear();
			}

			void Run()
			{
				for( int i = 0; i < n; i++ )
					m_CallMgr[ i ].Run();
			}

		};


		//*****************************************************************************
		//!���󴴽��º���
		//                           
		//!ֻҪ���빹�캯����������Զ������������
		//!��Ҫ�Ͷ������������
		//!��Ҫ���������ʵ�ֶԴ��������ڴ�Ĺ���
		//!\ingroup ObjectPool
		//                            2009.10.16
		//*****************************************************************************
		template< class T, class ObjAlloc = alloc, class Alloc = alloc >
		struct CreateObject
		{
			typedef Alloc AllocatorType;
			typedef T ClassType;
			typedef ObjectWrapper_A< T, ObjAlloc, Alloc > WrapperType;

			WrapperType * operator()( );

			template < class Arg1 >
			WrapperType * operator()( Arg1 & arg1 );

			template < class Arg1, class Arg2 >
			WrapperType * operator()( Arg1 & arg1, Arg2 & arg2 );
		};

		template< class T, class ObjAlloc, class Alloc >
		typename CreateObject< T, ObjAlloc, Alloc >::WrapperType *
			CreateObject< T, ObjAlloc, Alloc >::operator()( )
		{
			void * p = Alloc::allocate( sizeof( T ) );
			T * ret = new ( p ) T;
			return new WrapperType( ret );
		}

		template< class T, class ObjAlloc, class Alloc >
		template< class Arg1 >
		typename CreateObject< T, ObjAlloc, Alloc >::WrapperType *
			CreateObject< T, ObjAlloc, Alloc >::operator()( Arg1 & arg1 )
		{
			void * p = Alloc::allocate( sizeof( T ) );
			T * ret = new ( p ) T ( arg1 );
			return new WrapperType( ret );
		}

		template< class T, class ObjAlloc, class Alloc >
		template< class Arg1, class Arg2 >
		typename CreateObject< T, ObjAlloc, Alloc >::WrapperType *
			CreateObject< T, ObjAlloc, Alloc >::operator()( Arg1 & arg1, Arg2 & arg2 )
		{
			void * p = Alloc::allocate( sizeof( T ) );
			T * ret = new ( p ) T ( arg1, arg2 );
			return WrapperType( ret );
		}

		//*****************************************************************************
		//�ṩ��typedef
		//���� Ӧ���嵽��
		//*****************************************************************************


		//!Ĭ�ϵĶ����
		typedef _ObjectPool<> ObjPool;
		//!\brief Ĭ�ϵĶ��������
		//!
		//!����7�������
		typedef _ObjectManager< 7 > ObjMgr;
		//!Ĭ�ϵ���ǿ���������
		typedef _ObjectManagerW< 7 > ObjMgrW;
		//typedef ObjectWrapper_A ;
	}
}
