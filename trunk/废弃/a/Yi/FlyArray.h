#ifndef __FLYARRAY_H
#define __FLYARRAY_H
/////////////////////////////////////////
/////////////////////////////////////////
//author ladace
//FlyArray���������������� �ṩ�������� T����Ϊ�������õ��κζ���
//ForEach���������ö���ĳ�Ա�������һ������Ϊ����ĺ�������һ������һ��Ϊ�ö�����һ��Ҫ�޸� ������
//LazyFuncͬ�ϣ������ǿ��÷���ֵ�ġ�����Ϊ��Ч�ʶ���ִ�еġ�����ʽʹ�ã�ʹ���������Apply��������������Yi::A<<=
//���߲��������ô�С���ڵ���ԭ�����С��FlyArray���Ὣ�Զ���Ӧ
//���߿���ʽָ���������� ˳��Ϊ ����ֵ���� ��һ���������� �ڶ����������͡���
//Ϊ���ܽ������������Ի�Yi::F�������Զ����ɲ�����������һ��FlyArray���顣����ʽָ�����͡�

//ʹ��const_cast�ĵط���dirty trick ������鷳������
//�޷��������Ϊ���õĺ�������Ϊ���úͷ����õ��õ�ʱ������һ�� �޷���ʽ�ƶϳ�����Ϊ���� ��__LazyFuncTag��û�п���TΪ���õ����
#include <boost\preprocessor\repetition\repeat.hpp>
#include <boost\preprocessor\punctuation\comma_if.hpp>
#include <boost\preprocessor\arithmetic\sub.hpp> 

#include <boost\type_traits\is_class.hpp>
#include <boost\type_traits\add_reference.hpp>
#include <boost\type_traits\add_pointer.hpp>
#include <boost\type_traits\remove_pointer.hpp>

#include <boost\static_assert.hpp>

#include "Array.h"
#define MAX_ARG_NUM  10 //���֧�ֲ�����Ŀ + 1

//Ϊ��Ԥ����Ԫ��̶������ĺ� ���ļ�ĩβUndef
#define REPEAT_TEXT( z, n, dt ) BOOST_PP_COMMA_IF( n ) dt
#define REPEAT_TEXTN( z, n, dt ) BOOST_PP_COMMA_IF( n ) dt##n

#define REPEAT_ARG_TN( z, n, t ) BOOST_PP_COMMA_IF(n) T##n _arg##n
#define REPEAT_ARG_TN_CREF( z, n, t ) BOOST_PP_COMMA_IF( n ) const T##n &_arg##n

#define REPEAT_DEFAULT_CLASS_TN( z, n, t ) BOOST_PP_COMMA_IF( n ) class Arg##n = unused
#define REPEAT_UNUSED( z, n, t ) BOOST_PP_COMMA_IF( n ) unused

#define REPEAT_DEFINE_ARG_MEM_REF( z, n, t ) T##n &_arg##n;
#define REPEAT_INITIALIZE_ARG_MEM( z, n, t ) BOOST_PP_COMMA_IF( n ) _arg##n ( _arg##n )
#define REPEAT_INITIALIZE_ARG_MEM_REF( z, n, t ) BOOST_PP_COMMA_IF( n ) _arg##n ( const_cast< T##n& >( _arg##n ) )


namespace OneU
{

	template< class T, UINT N > class FlyArray;
	namespace Yi
	{
		struct __unusedTag;
		typedef __unusedTag* unused;

		//ǰ������
		template< class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_DEFAULT_CLASS_TN, 0 ) >
		struct __LazyFuncTag;

		template< class Left, class T, class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_DEFAULT_CLASS_TN, 0 ) >
		struct __LazyMemFuncTag;


		//================================================================
		//����ĳ������Ҳ��FlyArray��Lazy��������ʽģ�����ĺ���
		//__ExpandArg�������ļ����
		//================================================================

		//==================================================
		//FlyArray������ȡ��
		//��TΪFlyArrayʱ value_typeΪArray�ں�������
		//TΪLazy�����������ʽģ��ʱ value_typeΪ����ֵ����
		//
		//ע��TΪ���ʽģ����ػ����ļ����� ����Ժ�д�����ʱ����ʽģ���������ػ�Ӧ��������ȡ���ػ���д ������������
		//�������ΪT
		//==================================================
		template< class T >
		struct __FlyArray_Traits
		{
			typedef T value_type;
			enum{ size = 1 };
		};
		template< class T, UINT N >
		struct __FlyArray_Traits< FlyArray< T, N > >
		{
			typedef T value_type;
			enum{ size = N };
		};
		template< class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ) >
		struct __FlyArray_Traits< __LazyFuncTag< Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) > >
		{
			typedef Ret value_type;
			enum{ size = Left::size };
		};
		template< class Left, class T, class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ) >
		struct __FlyArray_Traits< __LazyMemFuncTag< Left, T, Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) > >
		{
			typedef Ret value_type;
			enum{ size = Left::size };
		};

		//��ȡ������͵�size���� �Ե�һ��ȡ�õ���1��sizeΪ׼
		template< BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ) >
		struct __GetMulti_T_Size
		{
#define REPEAT_GET_TN_SIZE( z, n, t ) __FlyArray_Traits< T##n >::size !=1 ? __FlyArray_Traits< T##n >::size :
			enum{ size = BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_GET_TN_SIZE, 0 ) 1 };
#undef REPEAT_GET_TN_SIZE
		};

#define REPEAT_EXPAND_ARG( z, n, i ) BOOST_PP_COMMA_IF( n ) __ExpandArg( _arg##n, i )
#define REPEAT_TRAITS_VALUETYPE_TN( z, n, t ) BOOST_PP_COMMA_IF( n ) typename __FlyArray_Traits< T##n >::value_type

		//===================================================================
		//���ʽģ��ϵ��
		//===================================================================

		template< class T >
		struct error_cant_deduce_template_argument{ typedef T type; };

		//��Ԫ�����
		//����Ʋ����������ԭ�������� �����º궨��
#define TEMPLATE_LAZY_OP_2( Name, Op )\
		template< class Left, class Right >\
		struct Name\
		{\
			/*���ִ˴����ʾ���ʽģ�岻���жϸ��������������ֵ�����ͣ���Ҫ��ʾָ��*/\
			typedef Name< Left, Right > ThisType;\
			typedef typename error_cant_deduce_template_argument< typename Left::value_type >::type value_type;\
			enum{ size = Left::size };\
			Left &lhs;\
			Right &rhs;\
			Name( const Left &lhs, const Right &rhs )\
				: lhs( const_cast< Left& >( lhs ) ), rhs( const_cast< Right& >( rhs ) )\
			{}\
			value_type operator[]( UINT index )\
			{\
				return lhs[index] Op __ExpandArg( rhs, index );\
			}\
			template< class T >\
			__LazyEqual< ThisType, T > operator=( const T &rhs )\
			{\
				return __LazyEqual< ThisType, T >( *this, rhs );\
			}\
			__LazyEqual< ThisType, ThisType > operator=( const ThisType &rhs )\
			{ return __LazyEqual< ThisType, ThisType >( *this, rhs ); }\
			template< class Ret >\
			Ret operator[]( UINT index )\
			{\
				return lhs[index] Op __ExpandArg( rhs, index );\
			}\
			void Apply()\
			{\
				for( int i = 0; i < Left::size; ++i ) operator[]( i );\
			}\
		};
		//����Ʋ��������������������� �������º�
#define TEMPLATE_LAZY_OPE_2( Name, Op )\
		template< class Left, class Right >\
		struct Name\
		{\
			typedef typename boost::add_reference<\
				typename error_cant_deduce_template_argument< typename Left::value_type >::type\
				>::type value_type;\
			typedef Name< Left, Right > ThisType;\
			enum{ size = Left::size };\
			Left &lhs;\
			Right &rhs;\
			Name( const Left &lhs, const Right &rhs )\
				: lhs( const_cast< Left& >( lhs ) ), rhs( const_cast< Right& >( rhs ) )\
			{}\
			/*���ִ˴����ʾ���ʽģ�岻���жϸ��������������ֵ�����ͣ���Ҫ��ʾָ��*/\
			\
			value_type operator[]( UINT index )\
			{\
				return lhs[index] Op __ExpandArg( rhs, index );\
			}\
			template< class T >\
			__LazyEqual< ThisType, T > operator=( T &rhs )\
			{\
				return __LazyEqual< ThisType, T >( *this, rhs );\
			}\
			__LazyEqual< ThisType, ThisType > operator=( const ThisType &rhs )\
			{ return __LazyEqual< ThisType, ThisType >( *this, rhs ); }\
			template< class Ret >\
			Ret operator[]( UINT index )\
			{\
				return lhs[index] Op __ExpandArg( rhs, index );\
			}\
			void Apply()\
			{\
				for( int i = 0; i < Left::size; ++i ) operator[]( i );\
			}\
		};
		TEMPLATE_LAZY_OPE_2( __LazyEqual, = )
		TEMPLATE_LAZY_OP_2( __LazyPlus,+ )
		TEMPLATE_LAZY_OP_2( __LazyMinus, - )
		TEMPLATE_LAZY_OP_2( __LazyMul, * )
		TEMPLATE_LAZY_OP_2( __LazyDiv, / )
		TEMPLATE_LAZY_OPE_2( __LazyPlusE, += )
		TEMPLATE_LAZY_OPE_2( __LazyMinusE, -= )
		TEMPLATE_LAZY_OPE_2( __LazyMulE, *= )
		TEMPLATE_LAZY_OPE_2( __LazyDivE, /= )
		TEMPLATE_LAZY_OPE_2( __LazyIn, << )
		TEMPLATE_LAZY_OPE_2( __LazyOut, >> )
#undef TEMPLATE_LAZY_OP_2
		//====================================
		//һԪ����� ֻ�ṩ2��
		//��ָ��
		template< class Left >
		struct __LazyDef
		{
			typedef typename error_cant_deduce_template_argument< typename boost::add_reference<
				typename boost::remove_pointer< typename Left::value_type >::type
					>::type >::type value_type;
			typedef __LazyDef< Left > ThisType;
			enum{ size = Left::size };
			Left &lhs;
			__LazyDef( const Left &lhs )
				: lhs( const_cast< Left& >( lhs ) )
			{}
			value_type operator[]( UINT index )
			{
				return *lhs[index];
			}
			template< class T >
			__LazyEqual< ThisType, T > operator=( const T &rhs )
			{
				return __LazyEqual< ThisType, T >( *this, rhs );
			}
			__LazyEqual< ThisType, ThisType > operator=( const ThisType &rhs )
			{ return __LazyEqual< ThisType, ThisType >( *this, rhs ); }
			//�ƺ�û�� ����
			template< class Ret >
			Ret operator[]( UINT index )
			{
				return *lhs[index];
			}
			void Apply()
			{
				for( int i = 0; i < Left::size; ++i ) operator[]( i );\
			}
		};
		//ȡ��ַ
		template< class Left >
		struct __LazyAdr
		{
			typedef typename error_cant_deduce_template_argument< typename boost::add_pointer< typename Left::value_type >::type >::type value_type;
			enum{ size = Left::size };
			typedef __LazyAdr< Left > ThisType;
			Left &lhs;
			__LazyAdr( const Left &lhs )
				: lhs( const_cast< Left& >( lhs ) )
			{}
			value_type operator[]( UINT index )
			{
				return &lhs[index];
			}
			template< class T >
			__LazyEqual< ThisType, T > operator=( const T &rhs )
			{
				return __LazyEqual< ThisType, T >( *this, rhs );
			}
			__LazyEqual< ThisType, ThisType > operator=( const ThisType &rhs )
			{ return __LazyEqual< ThisType, ThisType >( *this, rhs ); }
			//�ƺ�û�� ����
			template< class Ret >
			Ret operator[]( UINT index )
			{
				return &lhs[index];
			}
			void Apply()
			{
				for( int i = 0; i < Left::size; ++i ) operator[]( i );\
			}
		};
		//Ϊһϵ�нṹ������һԪ�����
#define OPERATOR_1( Left, Name, Op )\
		template< class A >\
		Name< Left< A > > operator Op( const Left< A > &lhs )\
		{ return Name< Left< A > >( lhs );	}
#define OPERATOR_2_1( Left, Name, Op )\
		template< class A, class B >\
		Name< Left< A, B > > operator Op( const Left< A, B > &lhs )\
		{ return Name< Left< A, B > >( lhs ); }
#define OPERATOR_1_SINGLE( Name, Op )\
		OPERATOR_1( __LazyDef, Name,  Op )\
		OPERATOR_1( __LazyAdr, Name,  Op )\
		OPERATOR_2_1( __LazyEqual, Name,  Op )\
		OPERATOR_2_1( __LazyPlus,  Name,  Op )\
		OPERATOR_2_1( __LazyMinus, Name,  Op )\
		OPERATOR_2_1( __LazyMul,   Name,  Op )\
		OPERATOR_2_1( __LazyDiv,   Name,  Op )\
		OPERATOR_2_1( __LazyPlusE, Name,  Op )\
		OPERATOR_2_1( __LazyMinusE,Name,  Op )\
		OPERATOR_2_1( __LazyMulE,  Name,  Op )\
		OPERATOR_2_1( __LazyDivE,  Name,  Op )\
		OPERATOR_2_1( __LazyIn,    Name,  Op )\
		OPERATOR_2_1( __LazyOut,   Name,  Op )

		OPERATOR_1_SINGLE( __LazyDef, * )
		OPERATOR_1_SINGLE( __LazyAdr, & )
#undef OPERATOR_1_SINGLE
#undef OPERATOR_2_1
#undef OPERATOR_1
		//Ϊһϵ�нṹ�����ض�Ԫ�����
#define OPERATOR_1_2( Left, Name, Op )\
		template< class T, class A >\
		Name< Left< A >, T > operator Op( const Left< A > &lhs, const T& rhs )\
		{ return Name< Left< A >, T >( lhs, rhs ); }
#define OPERATOR_2( Left, Name, Op )\
		template< class T, class A, class B >\
		Name< Left< A, B >, T > operator Op( const Left< A, B > &lhs, const T& rhs )\
		{ return Name< Left< A, B >, T >( lhs, rhs ); }
#define OPERATOR_2_SINGLE( Name, Op )\
		OPERATOR_1_2( __LazyDef, Name,  Op )\
		OPERATOR_1_2( __LazyAdr, Name,  Op )\
		OPERATOR_2( __LazyEqual, Name,  Op )\
		OPERATOR_2( __LazyPlus,  Name,  Op )\
		OPERATOR_2( __LazyMinus, Name,  Op )\
		OPERATOR_2( __LazyMul,   Name,  Op )\
		OPERATOR_2( __LazyDiv,   Name,  Op )\
		OPERATOR_2( __LazyPlusE, Name,  Op )\
		OPERATOR_2( __LazyMinusE,Name,  Op )\
		OPERATOR_2( __LazyMulE,  Name,  Op )\
		OPERATOR_2( __LazyDivE,  Name,  Op )\
		OPERATOR_2( __LazyIn,    Name,  Op )\
		OPERATOR_2( __LazyOut,   Name,  Op )

		OPERATOR_2_SINGLE( __LazyPlus,  + )
		OPERATOR_2_SINGLE( __LazyMinus, - )
		OPERATOR_2_SINGLE( __LazyMul,   * )
		OPERATOR_2_SINGLE( __LazyDiv,   / )
		OPERATOR_2_SINGLE( __LazyPlusE, += )
		OPERATOR_2_SINGLE( __LazyMinusE,-= )
		OPERATOR_2_SINGLE( __LazyMulE,  *= )
		OPERATOR_2_SINGLE( __LazyDivE,  /= )
		OPERATOR_2_SINGLE( __LazyIn,    << )
		OPERATOR_2_SINGLE( __LazyOut,   >> )
#undef OPERATOR_2_SINGLE
#undef OPERATOR_1_2
#undef OPERATOR_2

		//================================================================
		//����Lazy��������
		//�������Ʊ��ʽģ�������
		//=======================================================
		//=========================================
		//Lazy���ɺ�����Ķ���
		//Ϊ�˽��ͱ�̸��Ӷ� ���һ��TN��Զ��UnUsed ���֧�ֲ�����ĿΪMAX_ARG_NUM - 1
		//��Ҫ������Ĳ�����Ŀ��ͬ������ƫ�ػ�
		//=================================================
		template< class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ) >
		struct __LazyFuncTag
		{};	


#define REPEAT_LAZYFUNC_SPECIALIZE( z, n, t )\
		template< class Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, class T ) >\
		struct __LazyFuncTag< Ret, BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T ) BOOST_PP_COMMA_IF( n )\
				BOOST_PP_REPEAT_##z( BOOST_PP_SUB( MAX_ARG_NUM, n ), REPEAT_UNUSED, 0 ) >\
		{\
			typedef __LazyFuncTag< Ret, BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T ) BOOST_PP_COMMA_IF( n )\
				BOOST_PP_REPEAT_##z( BOOST_PP_SUB( MAX_ARG_NUM, n ), REPEAT_UNUSED, 0 ) > ThisType;\
			enum{ size = __GetMulti_T_Size< BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T ) BOOST_PP_COMMA_IF( n )\
				BOOST_PP_REPEAT_##z( BOOST_PP_SUB( MAX_ARG_NUM, n ), REPEAT_UNUSED, 0 ) >::size };\
			typedef Ret value_type;\
			\
			typedef Ret (*FuncPointer)( BOOST_PP_REPEAT_##z( n, REPEAT_TRAITS_VALUETYPE_TN, 0 ) );\
			FuncPointer _pFunc;\
			BOOST_PP_REPEAT_##z( n, REPEAT_DEFINE_ARG_MEM_REF, 0 );\
			\
			__LazyFuncTag( FuncPointer pF BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_ARG_TN_CREF, 0 ) )\
				: _pFunc( pF ) BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_INITIALIZE_ARG_MEM_REF, 0 )\
			{}\
			Ret operator[]( UINT index )\
			{\
				return ( *_pFunc )(\
					BOOST_PP_REPEAT_##z( n, REPEAT_EXPAND_ARG, index ) );\
			}\
			template< class U >\
			__LazyEqual< ThisType, U > operator=( const U& rhs )\
			{\
				return __LazyEqual< ThisType, U >( *this, rhs );\
			}\
			__LazyEqual< ThisType, ThisType > operator=( const ThisType &rhs )\
			{ return __LazyEqual< ThisType, ThisType >( *this, rhs ); }\
			void Apply()/*��Lazy����ִ��*/\
			{\
				for( int i = 0; i < size; ++i )\
					operator[]( i );\
			}\
		};/*���ݲ�����Ŀƫ�ػ�*/
		BOOST_PP_REPEAT( MAX_ARG_NUM , REPEAT_LAZYFUNC_SPECIALIZE, 0 )
#undef REPEAT_LAZYFUNC_SPECIALIZE

		//=========================================
		//Lazy��Ա������Ķ���
		//��Ҫ������Ĳ�����Ŀ��ͬ������ƫ�ػ�
		template< class Left, class T, class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ) >
		struct __LazyMemFuncTag
		{};	
		
	
#define REPEAT_LAZYMEMFUNC_SPECIALIZE( z, n, t )\
		template< class Left, class T, class Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, class T ) >\
		struct __LazyMemFuncTag< Left, T, Ret, BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T ) BOOST_PP_COMMA_IF( n )\
				BOOST_PP_REPEAT_##z( BOOST_PP_SUB( MAX_ARG_NUM, n ), REPEAT_UNUSED, 0 ) >\
		{\
			typedef __LazyMemFuncTag< Left, T, Ret, BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T ) BOOST_PP_COMMA_IF( n )\
					BOOST_PP_REPEAT_##z( BOOST_PP_SUB( MAX_ARG_NUM, n ), REPEAT_UNUSED, 0 ) > ThisType;\
			enum{ size = Left::size };\
			typedef Ret value_type;\
			Left &_v;\
			typedef Ret (T::*FuncPointer)( BOOST_PP_REPEAT_##z( n, REPEAT_TRAITS_VALUETYPE_TN, 0 ) );\
			FuncPointer _pFunc;\
			BOOST_PP_REPEAT_##z( n, REPEAT_DEFINE_ARG_MEM_REF, 0 );\
			\
			__LazyMemFuncTag( Left &v, FuncPointer pF BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_ARG_TN_CREF, 0 ) )\
				: _v( v ), _pFunc( pF ) BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_INITIALIZE_ARG_MEM_REF, 0 )\
			{}\
			Ret operator[]( UINT index )\
			{\
				return ( (&(_v[index])/*�������ΪT�Ķ���*/)->*_pFunc )(\
				BOOST_PP_REPEAT_##z( n, REPEAT_EXPAND_ARG, index ) );\
			}\
			template< class U >\
			__LazyEqual< ThisType, U > operator=( const U& rhs )\
			{\
				return __LazyEqual< ThisType, U >( *this, rhs );\
			}\
			__LazyEqual< ThisType, ThisType > operator=( const ThisType &rhs )\
			{ return __LazyEqual< ThisType, ThisType >( *this, rhs ); }\
			void Apply()/*��Lazy����ִ��*/\
			{\
				for( int i = 0; i < size; ++i )\
					operator[]( i );\
			}\
		};/*���ݲ�����Ŀƫ�ػ�*/
		BOOST_PP_REPEAT( MAX_ARG_NUM , REPEAT_LAZYMEMFUNC_SPECIALIZE, 0 )
#undef REPEAT_LAZYMEMFUNC_SPECIALIZE


		//===================================================================
		//
		//Lazy�����ı��ʽģ��
		//��ҪΪLazy������Tag���ط���
		//===================================================================
		//һԪ�����

#define LAZYM_OPERATOR_1( Name, Op )\
		template< class Left, class T, class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ) >\
		Name< __LazyMemFuncTag< Left, T, Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) > > operator Op(\
			const __LazyMemFuncTag< Left, T, Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) > &lhs )\
		{\
			return Name<  __LazyMemFuncTag< Left, T, Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) > >( lhs );\
		}
#define LAZY_OPERATOR_1( Name, Op )\
		template< class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ) >\
		Name< __LazyFuncTag< Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) > > operator Op(\
			const __LazyFuncTag< Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) > &lhs )\
		{\
			return Name<  __LazyFuncTag< Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) > >( lhs );\
		}
		LAZY_OPERATOR_1( __LazyDef, * )
		LAZY_OPERATOR_1( __LazyAdr, & )
		LAZYM_OPERATOR_1( __LazyDef, * )
		LAZYM_OPERATOR_1( __LazyAdr, & )
#undef LAZYM_OPERATOR_1
#undef LAZY_OPERATOR_1
		//��Ԫ�����
#define LAZYM_OPERATOR_2( Name, Op )\
		template< class Left, class T, class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ), class U >\
		Name< __LazyMemFuncTag< Left, T, Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) >, U > operator Op(\
			const __LazyMemFuncTag< Left, T, Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) > &lhs, const U &rhs )\
		{\
			return Name<  __LazyMemFuncTag< Left, T, Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) >, U >( lhs, rhs );\
		}

#define LAZY_OPERATOR_2( Name, Op )\
		template< class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ), class U >\
		Name< __LazyFuncTag< Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) >, U > operator Op(\
			const __LazyFuncTag< Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) > &lhs, const U &rhs )\
		{\
			return Name<  __LazyFuncTag< Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) >, U >( lhs, rhs );\
		}
		LAZY_OPERATOR_2( __LazyPlus,  + )
		LAZY_OPERATOR_2( __LazyMinus, - )
		LAZY_OPERATOR_2( __LazyMul,   * )
		LAZY_OPERATOR_2( __LazyDiv,   / )
		LAZY_OPERATOR_2( __LazyPlusE, += )
		LAZY_OPERATOR_2( __LazyMinusE,-= )
		LAZY_OPERATOR_2( __LazyMulE,  *= )
		LAZY_OPERATOR_2( __LazyDivE,  /= )
		LAZY_OPERATOR_2( __LazyIn,    << )
		LAZY_OPERATOR_2( __LazyOut,   >> )
		LAZYM_OPERATOR_2( __LazyPlus,  + )
		LAZYM_OPERATOR_2( __LazyMinus, - )
		LAZYM_OPERATOR_2( __LazyMul,   * )
		LAZYM_OPERATOR_2( __LazyDiv,   / )
		LAZYM_OPERATOR_2( __LazyPlusE, += )
		LAZYM_OPERATOR_2( __LazyMinusE,-= )
		LAZYM_OPERATOR_2( __LazyMulE,  *= )
		LAZYM_OPERATOR_2( __LazyDivE,  /= )
		LAZYM_OPERATOR_2( __LazyIn,    << )
		LAZYM_OPERATOR_2( __LazyOut,   >> )
#undef LAZY_OPERATOR_2

		//===================================================================
		//ForEach���ⲿ�����汾
		//===================================================================
#define REPEAT_YI_FOREACH( z, n, t )\
		template< class Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, class T ), class T, UINT N >\
		inline void ForEach( FlyArray< T, N >& _v, Ret( T::*pFunc )( BOOST_PP_REPEAT_##z( n, REPEAT_TRAITS_VALUETYPE_TN, 0 ) ) BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_ARG_TN_CREF, 0 ) )\
		{\
			for( int i = 0; i < N; ++i )\
			{\
				( ( &_v[i] )->*pFunc )( BOOST_PP_REPEAT_##z( n, REPEAT_EXPAND_ARG, i ) );\
			}\
		}\
		template< class Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, class T ) >\
		inline void ForEach( Ret( *pFunc )( BOOST_PP_REPEAT_##z( n, REPEAT_TRAITS_VALUETYPE_TN, 0 ) ) BOOST_PP_COMMA_IF( n )\
			BOOST_PP_REPEAT_##z( n, REPEAT_ARG_TN_CREF, 0 ) )\
		{\
			for( int i = 0; i < __GetMulti_T_Size< BOOST_PP_REPEAT( n, REPEAT_TEXTN, T ) BOOST_PP_COMMA_IF( n )\
				BOOST_PP_REPEAT( BOOST_PP_SUB( MAX_ARG_NUM, n ), REPEAT_TEXT, unused ) >::size; ++i )\
			{\
				( *pFunc )( BOOST_PP_REPEAT_##z( n, REPEAT_EXPAND_ARG, i ) );\
			}\
		}
		BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_YI_FOREACH, 0 )
		//���������ִ��� ������
		//1.��ĺ��������ذ汾�������ذ汾����ʽָ������ֵ�Ͳ������ͣ�
		//2.��������Ŀ�����ʹ���
		//3.��ʽָ�������ʹ���
#undef REPEAT_YI_FOREACH

		//LazyFunc����
#define REPEAT_YI_LAZYFUNC( z, n, t )\
		template< class Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, class T ),  class T, class Left >\
		inline __LazyMemFuncTag< Left, T, Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T ) >\
			LazyFunc( Left& _v,\
				Ret( T::*pFunc )( BOOST_PP_REPEAT_##z( n, REPEAT_TRAITS_VALUETYPE_TN, 0 ) ) BOOST_PP_COMMA_IF( n )\
				BOOST_PP_REPEAT_##z( n, REPEAT_ARG_TN_CREF, 0 ) )\
		{\
			return __LazyMemFuncTag< Left, T,\
				Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T ) >\
				( _v, pFunc BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, _arg ) );\
		}\
		template< class Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, class T ) >\
		inline __LazyFuncTag< Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T ) >\
			LazyFunc(\
				Ret( *pFunc )( BOOST_PP_REPEAT_##z( n, REPEAT_TRAITS_VALUETYPE_TN, 0 ) ) BOOST_PP_COMMA_IF( n )/*����ֻ֧�ֺ�������ΪFlyArray���T������T�����õ�*/\
				BOOST_PP_REPEAT_##z( n, REPEAT_ARG_TN_CREF, 0 ) )\
		{\
			return __LazyFuncTag<\
				Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T ) >\
				( pFunc BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, _arg ) );\
		}
		BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_YI_LAZYFUNC, 0 )
		//���������ִ��� ������
		//1.��ĺ��������ذ汾�������ذ汾����ʽָ������ֵ�Ͳ������ͣ�
		//2.��������Ŀ�����ʹ���
		//3.��ʽָ�������ʹ���
#undef REPEAT_YI_LAZYFUNC

		//�ⲿApply����
		//��Lazy����ִ��
		template< class LazyFuncType >
		inline void Apply( LazyFuncType v )
		{
			v.Apply();
		}
		//���������ǰ�����Yi::A<<=���ö��Ժ�������ʽִ��
		struct __ATag
		{
			template< class LazyFuncType >
			void operator <<=( LazyFuncType v )
			{
				v.Apply();
			}
		};
		__ATag A;

		//======================================================
		//��Ա�����Ļ�ʽ����
		template< class T, class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_DEFAULT_CLASS_TN, 0 ) >
		struct MemFunc
		{};
#define REPEAT_MEMFUNC_SPECIALIZE( z, n, t )\
		template< class T, class Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, class T ) >\
		struct MemFunc< T, Ret, BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T ) BOOST_PP_COMMA_IF( n )\
			BOOST_PP_REPEAT_##z( BOOST_PP_SUB( MAX_ARG_NUM, n ), REPEAT_UNUSED, 0 ) >\
		{\
			typedef Ret( T::*type )( BOOST_PP_REPEAT_##z( n, REPEAT_TRAITS_VALUETYPE_TN, 0 ) );\
		};
		BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_MEMFUNC_SPECIALIZE, 0 )
#undef REPEAT_MEMFUNC_SPECIALIZE

	}

	//��������
	//�ṩһЩ��������
	//TΪ�����õ�����
	template< class T, UINT N >
	class FlyArray
		: public Array< T, N >
	{
	public:
		typedef FlyArray< T, N > ThisType;
	public:
		FlyArray()
		{
			//FlyArrayһ����׼����Ҫ������һ���� �����Ա�������������޷����
			BOOST_STATIC_ASSERT( sizeof( ThisType ) == N * sizeof( T ) );
		}
//#define REPEAT_FOREACH( z, n, t )\
//		template< class Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, class T ) >\
//		void ForEach( typename Yi::MemFunc< T, Ret BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT( n, REPEAT_TEXTN, T ) >::type pFunc\
//				BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_ARG_TN_CREF, 0 ) )\
//		{\
//			Yi::ForEach( *this, pFunc BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, _arg ) );\
//		}/*��һ�汣֤��������ʾָ������ֵ���ͺͲ������ͣ�����T��һ��ΪClass�������ҪMemFunc����ʽ����*/\
//		template< class FuncPointer BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, class T ) >\
//		void ForEach( FuncPointer pFunc\
//				BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_ARG_TN_CREF, 0 ) )\
//		{\
//			Yi::ForEach( *this, pFunc BOOST_PP_COMMA_IF( n ) BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, _arg ) );\
//		}/*����Ϊ���غ���ʱ����һ�汣֤���㲻��ָ������ֵ�Ͳ������;���ʹ��*/
//		BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_FOREACH, 0 )
//		//���������ִ��� ������
//		//1.��ĺ��������ذ汾�������ذ汾����ʽָ������ֵ�Ͳ������ͣ�
//		//2.��������Ŀ�����ʹ���
//		//3.��ʽָ�������ʹ���
//#undef REPEAT_FOREACH

		template< class U >
		Yi::__LazyEqual< ThisType, U > operator=( const U &rhs )
		{
			return Yi::__LazyEqual< ThisType, U >( *this, rhs );
		}
		Yi::__LazyEqual< ThisType, ThisType > operator=( const ThisType &rhs )//��ֹ��������Ĭ�϶���
		{
			return Yi::__LazyEqual< ThisType, ThisType >( *this, rhs );
		}
	};

	//====================================================
	//FlyArray�Ա��ʽ��֧��
	//ΪFlyArray���ظ��������
	//====================================================

#define FLYARRAY_OPERATOR_1( Name, Op )\
	template< class T, UINT N >\
	Name< FlyArray< T, N > > operator Op( const FlyArray< T, N > &lhs )\
	{ return Name< FlyArray< T, N > >( lhs ); }

	FLYARRAY_OPERATOR_1( Yi::__LazyDef, * )
	FLYARRAY_OPERATOR_1( Yi::__LazyAdr, & )
#undef FLYARRAY_OPERATOR_1

#define FLYARRAY_OPERATOR_2( Name, Op )\
	template< class T, UINT N, class U >\
	Name< FlyArray< T, N >, U > operator Op( const FlyArray< T, N > &lhs, const U &rhs )\
	{ return Name< FlyArray< T, N >, U >( lhs, rhs ); }

	FLYARRAY_OPERATOR_2( Yi::__LazyPlus,  + )
	FLYARRAY_OPERATOR_2( Yi::__LazyMinus, - )
	FLYARRAY_OPERATOR_2( Yi::__LazyMul,   * )
	FLYARRAY_OPERATOR_2( Yi::__LazyDiv,   / )
	FLYARRAY_OPERATOR_2( Yi::__LazyPlusE, += )
	FLYARRAY_OPERATOR_2( Yi::__LazyMinusE,-= )
	FLYARRAY_OPERATOR_2( Yi::__LazyMulE,  *= )
	FLYARRAY_OPERATOR_2( Yi::__LazyDivE,  /= )
	FLYARRAY_OPERATOR_2( Yi::__LazyIn,    << )
	FLYARRAY_OPERATOR_2( Yi::__LazyOut,   >> )
#undef FLYARRAY_OPERATOR_2


	namespace Yi
	{	
		//==========================================
		//Yi::F����FlyArray����
		//==========================================
#define REPEAT_ASSIGN_V( z, n, t ) v[n] = v##n;
#define REPEAT_F( z, n, t )\
		template< class T >\
		inline FlyArray< T, n > F( BOOST_PP_REPEAT_##z( n, REPEAT_TEXTN, T v ) )\
		{\
			FlyArray< T, n > v;\
			BOOST_PP_REPEAT_##z( n, REPEAT_ASSIGN_V, 0 )\
			return v;\
		}
		//���������ĿΪ20
		BOOST_PP_REPEAT( 20, REPEAT_F, 0 )
#undef REPEAT_F
#undef REPEAT_ASSIGN_V

		//================================================================
		//����ĳ������Ҳ��FlyArray��Lazy��������ʽģ�����ĺ���
		//����������ͨ�� չ����Ϊԭ��
		//��������Array չ����ΪArray[index]
		//================================================================
		template< class T >
		inline T __ExpandArg( const T &arg, UINT index ){ return arg; }

		template< class T, UINT N >
		inline T __ExpandArg( const FlyArray< T, N >& arg, UINT index ){ return arg[index]; }
		template< class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ) >
		inline Ret __ExpandArg( const __LazyFuncTag< Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) >& arg, UINT index ){ return arg[index]; }
		template< class Left, class T, class Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, class T ) >
		inline Ret __ExpandArg( const __LazyMemFuncTag< Left, T, Ret, BOOST_PP_REPEAT( MAX_ARG_NUM, REPEAT_TEXTN, T ) >& arg, UINT index ){ return arg[index]; }

#define EXPAND_OPERATOR_1( Name )\
		template< class A >\
		inline typename Name< A >::value_type __ExpandArg( Name< A > &arg, UINT index ){ return arg[index]; }
		EXPAND_OPERATOR_1( __LazyDef )
		EXPAND_OPERATOR_1( __LazyAdr )
#undef EXPAND_OPERATOR_1

#define EXPAND_OPERATOR_2( Name )\
	template< class A, class B >\
	inline typename Name< A, B >::value_type __ExpandArg( Name< A, B > &arg, UINT index ){ return arg[index]; }

		EXPAND_OPERATOR_2( __LazyEqual  )
		EXPAND_OPERATOR_2( __LazyPlus   )
		EXPAND_OPERATOR_2( __LazyMinus  )
		EXPAND_OPERATOR_2( __LazyMul    )
		EXPAND_OPERATOR_2( __LazyDiv    )
		EXPAND_OPERATOR_2( __LazyPlusE  )
		EXPAND_OPERATOR_2( __LazyMinusE )
		EXPAND_OPERATOR_2( __LazyMulE   )
		EXPAND_OPERATOR_2( __LazyDivE   )
		EXPAND_OPERATOR_2( __LazyIn     )
		EXPAND_OPERATOR_2( __LazyOut    )
#undef EXPAND_OPERATOR_2

		//������ȡ���Ա��ʽ���ػ�

#define VALUETYPE_TRAITS_OPERATOR_1( Name )\
		template< class A >\
		struct __FlyArray_Traits< Name< A > >\
		{\
			typedef typename Name< A >::value_type value_type;\
			enum{ size = Name< A >::size };\
		};
		VALUETYPE_TRAITS_OPERATOR_1( __LazyDef )
		VALUETYPE_TRAITS_OPERATOR_1( __LazyAdr )
#undef VALUETYPE_TRAITS_OPERATOR_1
#define VALUETYPE_TRAITS_OPERATOR_2( Name )\
		template< class A, class B >\
		struct __FlyArray_Traits< Name< A, B > >\
		{\
			typedef typename Name< A, B >::value_type value_type;\
			enum{ size = Name< A, B >::size };\
		};

		VALUETYPE_TRAITS_OPERATOR_2( __LazyEqual   )
		VALUETYPE_TRAITS_OPERATOR_2( __LazyPlus    )
		VALUETYPE_TRAITS_OPERATOR_2( __LazyMinus   )
		VALUETYPE_TRAITS_OPERATOR_2( __LazyMul     )
		VALUETYPE_TRAITS_OPERATOR_2( __LazyDiv     )
		VALUETYPE_TRAITS_OPERATOR_2( __LazyPlusE   )
		VALUETYPE_TRAITS_OPERATOR_2( __LazyMinusE  )
		VALUETYPE_TRAITS_OPERATOR_2( __LazyMulE    )
		VALUETYPE_TRAITS_OPERATOR_2( __LazyDivE    )
		VALUETYPE_TRAITS_OPERATOR_2( __LazyIn      )
		VALUETYPE_TRAITS_OPERATOR_2( __LazyOut     )
#undef VALUETYPE_TRAITS_OPERATOR_2
	}
}

#undef REPEAT_DEFINE_ARG_MEM_REF
#undef REPEAT_INITIALIZE_ARG_MEM
#undef REPEAT_INITIALIZE_ARG_MEM_REF

#undef REPEAT_DEFAULT_CLASS_TN
#undef REPEAT_UNUSED

#undef REPEAT_ARG_TN
#undef REPEAT_ARG_TN_CREF

#undef REPEAT_TEXTN
#undef REPEAT_TEXT

#endif