//==========================
//Observer_Adv.h
//�������ʵ�� ģ��Ԫ������
//
//ʹ�øÿ�Ḳ�ǵ�OBSERVER_CLASS_OUTPUT����Ķ���
//
//�����δ�������ȷ�Ľ����������������������
//��Ϊ���漰�����������ڴ�Ķ�������
//ȷ����ĳ�Ա��Ϊ4�ֽڿ��ý��׼ȷ
//              Ladace
//              2010.2.7
//==========================
#pragma once
//�����������ĵط�(���������)
//
//VC�������Ĺ��ɣ�
//��Щ���ڴ治����롣���綼��char���࣬�������char����4�ֽڵĳ�Ա���������˵�����Ҷ������ܵ��³�Առ�õ��ڴ治����������ʱ�����С�ֱ��������Ա�����л��࣬������ؼ̳еĻ������л�������Ϊһ���������ģ�����Ϊ4�ı���������A��СΪ9��B������A������9��char��ռ�ÿռ�Ϊ24������20��
//
//�κδ��麯�������ڴ�ᱻ���롣
//
//��������
//
//A�����Կ��࣬B������A����һ���࣬��ôsizeof(B)��ȥ���г�Ա�Ĵ�С����ᷢ�ֻ�ʣ��1���������Ϊ�������ŵġ�
//
//һ����������ݿ�������ɢ�� ��֤��Ա��Ϊ4�ֽ����Ϳɱ��������
//

#include <boost/mpl/vector.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include "Observer.h"

#define OBSERVER_MEM_ALIGN_1( N ) ( N / 4 + 1 ) * 4
namespace Observer
{

	//�麯��ָ��ṹ ������Ƕ�̬��Vector��һ����vfptr����������ʹ��ClsWrapper_Adv_Plm
	class vfptr
	{
	private:
		void *_p;
	public:
		void * GetPointer() const{ return _p; }
	};
	//

	//DeclareΪmpl::vector��һ��ʵ�� Ԫ��Ϊ��ĳ�Ա����
	template< class T, class Declare, class BaseClass = UnknownClass, class Outputer = DefaultOutputer >
	class ClsWrapper_Adv
	{
	private:
		enum{ M_Size = OBSERVER_MEM_ALIGN_1( sizeof( BaseClass ) ) - sizeof( BaseClass ) };
		char __holder[ M_Size ];//ֻռλ �Ѷ��ؼ̳л����С֮�Ͷ��뵽4�ı��� ���������˵��
	public:
		ClsWrapper_Adv()
		{
			ClsGroup_GetInstance< T, Outputer >().Adv<
				typename boost::mpl::push_front<
					typename boost::mpl::push_front<
						Declare, TMP::PlaceHolder< M_Size > //ռλ
					>::type, BaseClass 
				>::type >()->Insert( ( T * )this );
		}
		~ClsWrapper_Adv()
		{
			ClsGroup_GetInstance< T, Outputer >()()->Remove( ( T * )this );
		}
	};
	template< class T, class Declare, class Outputer >
	class ClsWrapper_Adv< T, Declare, UnknownClass, Outputer >
	{
	public:
		ClsWrapper_Adv()
		{
			ClsGroup_GetInstance< T, Outputer >().Adv< Declare >()->Insert( ( T * )this );
		}
		~ClsWrapper_Adv()
		{
			ClsGroup_GetInstance< T, Outputer >()()->Remove( ( T * )this );
		}
	};

	template< class T, class Declare, class BaseClass = UnknownClass, class Outputer = DefaultOutputer >
	class ClsWrapper_Adv_Plm
		: public ClsWrapper_Adv< T, typename boost::mpl::push_front< Declare, vfptr >::type, BaseClass, Outputer >
	{};

	//
	template< class T, class Declare, class Outputer = DefaultOutputer >
	class ClsGroup_Base_Adv
		:public ClsGroup< T, Outputer >
	{
	public:
		void OutputElem( void * Elem )
		{
			BOOST_STATIC_ASSERT( TMP::SizeSum< Declare >::value <= sizeof( T ) );//���б����� �ڴ�������� ���Զ���С�ڵ���
			TMP::DeclareOutputer< Declare, Outputer >()( Elem );
			//Outputer()( sizeof( T ) );
		}
	};
	template< class T, class Declare, class Outputer = DefaultOutputer >
	class ClsGroup_Adv
		: public ClsGroup_Base_Adv< T, Declare, Outputer >
	{

	};




	//////////////////////////////
	//ģ��Ԫ����
	//
	namespace TMP
	{
		template< int size >
		class PlaceHolder//ռsize���ֽڵ���
		{
			char a[ size ];
		};
		template<>
		class PlaceHolder< 0 >
		{};
		template< class Vector, class Iter > struct _ForEachSum;
		template< class Vector, class Iter > struct _SumOp;
		template< class Vector >
		struct SizeSum
		{
			typedef typename _ForEachSum< Vector, typename boost::mpl::begin< Vector >::type >::type type;
			enum{ value = type::value };
		};
		template< class Vector, class Iter >
		struct _ForEachSum
		{
			typedef typename boost::mpl::eval_if< boost::is_same< Iter, typename boost::mpl::end< Vector >::type >,
				boost::mpl::int_< 0 >,
				_SumOp< Vector, Iter > >::type type;
		};
		template< class Vector, class Iter >
		struct _SumOp
		{
			typedef boost::mpl::plus< boost::mpl::int_< sizeof( boost::mpl::deref< Iter >::type ) >,
				typename _ForEachSum< Vector, typename boost::mpl::next< Iter >::type >::type > type;
		};

		template< class Vector, class Outputer >
		struct DeclareOutputer
		{
			void operator()( void * Elem )
			{
				Outputer().NextLine();
				_ForEachOut< Vector, boost::mpl::begin< Vector >::type, Outputer >()( ( char * )Elem );
			}
		};

		struct _None
		{
			void operator()( void* ){}
		};

		template< class Vector, class Iter, class Outputer >
		struct _ForEachOut
		{
			void operator()( char * Elem )
			{
				typedef boost::mpl::deref< Iter >::type T;

				_Outputer< Outputer >()( ( T* )Elem );

				boost::mpl::eval_if< boost::is_same< typename boost::mpl::next< Iter >::type, typename boost::mpl::end< Vector >::type >,
					_None,
					_ForEachOut< Vector, typename boost::mpl::next< Iter >::type, Outputer > >()( Elem + sizeof( T ) );
			}
		};

		template< class Outputer >
		struct _Outputer
		{
			template< class T >
			void operator()( T * Elem )
			{
				Outputer().IncTab();
				boost::mpl::eval_if< boost::is_scalar< T >,
					_ScalarOutputer< Outputer >,
					_ObjOutputer< Outputer > >()( *Elem );
				Outputer().DecTab();
			}
		};
		template< class Outputer >
		struct _ScalarOutputer
		{
			template< class T >
			void operator()( const T & Elem )
			{
				Outputer()( typeid( T ).name() );
				Outputer()( L':' );
				Outputer()( Elem );
				Outputer().NextLine();
			}
		};
		template< class Outputer >
		struct _ObjOutputer
		{
			template< class T >
			void operator()( const T & Elem )
			{
				if( !ClsGroup_GetInstance< T, Outputer >().Exist() )
				{
					Outputer()( typeid( T ).name() );
					Outputer()( L':' );
					Outputer()( sizeof( T ) );
					Outputer()( "�ֽڡ�" );
					Outputer().NextLine();
				}
				else
				{
					//���ڴ�ʱΪ�������� ���߱���̬������ָ������ã� ��˲���Ҫʹ��RTTI
					ClsGroup_GetInstance< T, Outputer >()()->OutputClassName();
					Outputer()( ":" );
					ClsGroup_GetInstance< T, Outputer >()()->OutputElem( ( void* )&Elem );
				}
			}
			template< int Size >
			void operator()( const PlaceHolder< Size > & Elem ){}
			template<>
			void operator()< vfptr >( const vfptr & Elem )
			{
				Outputer()( "vfptr" );
				Outputer()( L':' );
				Outputer()( Elem.GetPointer() );
				Outputer().NextLine();
			}
		};
	}
}

using Observer::ClsWrapper_Adv;