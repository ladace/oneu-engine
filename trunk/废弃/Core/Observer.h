//==========================
//Observer.h
//�������ʵ��
//
//ֻ֧�ֵ��̳нṹ
//����RTTIʱ��Ϊ�����������ָ����û��ƫ�Ƶ�
//�����������������
//����������������һ�㣬ʹ��RTTI������
//
//������Outputer���ӿڱ�׼�μ�Output.h
//
//              Ladace
//              2010.2.7
//==========================
#pragma once
//�����������RTTI��Ĭ��ԭ�����������ָ��û��ƫ��
//
#include <list>
#include <map>
#include <cassert>
//#define OBSERVER_USE_RTTI

//OBSERVER_CLASS_OUTPUT���ڶ������ʹ�ӡ ClassNameΪ������ƣ�ClassNameStr�ַ���Ϊ������ƣ�pClassΪ��������
#define OBSERVER_CLASS_OUTPUT_BEGIN( ClassName, ClassNameStr ) \
namespace Observer{\
	template< class Outputer >\
	class ClsGroup< ClassName, Outputer >\
		: public ClsGroup_Base< Outputer >\
	{\
	public:\
		void OutputClassName(){ Outputer()( ClassNameStr );}\
		void OutputElem( void * pElem )\
		{\
			ClassName *pClass = ( ClassName* ) pElem;
#define OBSERVER_CLASS_OUTPUT_END }};}

//����ú���ʹ��RTTI����
#ifdef OBSERVER_USE_RTTI
namespace Observer
{
	template< class T >
	struct Class_Use_RTTI
	{
		enum{ value = 0 };
	};
}
//��ClassName��ʹ��RTTIʱʹ�øú꣬�����������麯��
//��д������ClassName��ͷ�ļ���ȫ����������
#define OBSERVE_CLASS_RTTI( ClassName )\
namespace Observer{\
	template<>\
	struct Class_Use_RTTI< ClassName >\
	{\
		enum{ value = 1 };\
	};\
}
#endif

using namespace std;
namespace Observer
{
	//���������� ʵ������OneUEngine/Commander.h
	class DefautOutputer;
	//δ֪��
	class UnknownClass{};

	//ǰ������
	template< class Outputer = DefaultOutputer >
	class ClsGroup_Base;

	//ȫ�ּ���ģ��
	template< class Outputer = DefaultOutputer >
	class ClsObserver
	{
	private:
		typedef list< ClsGroup_Base< Outputer >* > ListType;
		ListType m_List;
		static ClsObserver *s_pInstance;
		ClsObserver(){}
	public:
		static ClsObserver* GetInstance()
		{
			if( !s_pInstance )
				s_pInstance = new ClsObserver();
			return s_pInstance;
		}
		void Insert( ClsGroup_Base< Outputer > * pW )
		{
			m_List.push_back( pW );
		}
		size_t GetN()
		{
			return m_List.size();
		}
		template< class T >
		void OutputClass()
		{
			ClsGroup_GetInstance< T, Outputer >()()->Output();
		}
		void Output();

	};

	template< class Outputer >
	void ClsObserver< Outputer >::Output()
	{
		for( ListType::iterator i = m_List.begin(); i != m_List.end(); ++i )
			( *i )->Output();
	};

	//ClsGroup���� ���ֽӿ�
	template< class Outputer >
	class ClsGroup_Base
	{
	protected:
		typedef list< void * > ListType;
		ListType m_List;
		static unsigned int num;//���͵�����
		unsigned int ID;//����ΨһID
	public:
		ClsGroup_Base()
			: ID ( num++ )
		{
		}
		static const int MAX_BUFFER_SIZE = 500;
		virtual void OutputClassName();
		virtual void OutputElem( void * Elem );
		virtual size_t GetSize(){ return 0;}
	#ifdef OBSERVER_USE_RTTI
		virtual//��ʹ��RTTI�ú�����Ϊ���
	#endif
		void Output();
		void Insert( void * pW )
		{
			m_List.push_back( pW );
		}
		//Remove�����Ƚ����� Ч�ʽϵ�
		//��Ϊ��֪��List��ʵ�ַ�ʽ�����������Ż�
		void Remove( void * pW )
		{
			ListType::iterator iter = m_List.begin();
			for( ; iter != m_List.end(); ++iter )
				if( *iter == pW ) break;
			if( iter == m_List.end() ) 
			{
				assert( 0 );
				return;
			}
			m_List.erase( iter );
		}

	};

	template< class Outputer >
	void ClsGroup_Base< Outputer >::OutputClassName()
	{
		Outputer()( L"UnknownClass#");
		Outputer()( ID );
	}

	template< class Outputer >
	void ClsGroup_Base< Outputer >::OutputElem( void *Elem )
	{
		Outputer()( Elem, GetSize() );
	}

	template< class Outputer >
	void ClsGroup_Base< Outputer >::Output()
	{
		for( ListType::iterator i = m_List.begin(); i != m_List.end(); ++i )
		{
			OutputClassName();
			Outputer()( L':' );
			OutputElem( *i );
			Outputer().NextLine();
		}
	}

	#ifdef OBSERVER_USE_RTTI

	//��Ϊtypeid���ص�type_infoΪ��̬����
	//ͨ��type_infoָ��ĵ�ַ��Ѱ��Ӧ���Group
	template< class Outputer >
	class RTTI_GetClsGroup
	{
	private:
		typedef map< const type_info *, ClsGroup_Base< Outputer > * > MapType;
		static MapType m_Map;
	public:
		template< class T >
		void AddMap( ClsGroup_Base< Outputer > * pGroup )
		{
			m_Map.insert( pair< const type_info *, ClsGroup_Base< Outputer > * >( &typeid( T ), pGroup ) );
		}
		ClsGroup_Base< Outputer > * operator()( const type_info & t )
		{
			MapType::iterator i = m_Map.find( &t );
			if( i == m_Map.end() ) return 0;
			return i->second;
		}
	};

	template< class Outputer >
	map< const type_info *, ClsGroup_Base< Outputer > * > RTTI_GetClsGroup< Outputer >::m_Map;

	//RTTI�м��
	template< class T, class Outputer, bool UseRTTI >
	class ClsGroup_RTTI
		: public ClsGroup_Base< Outputer >
	{
	};
	template< class T, class Outputer >
	class ClsGroup_RTTI< T, Outputer, true >
		: public ClsGroup_Base< Outputer >
	{
		void Output()
		{
			for( ListType::iterator i = m_List.begin(); i != m_List.end(); ++i )
			{
				ClsGroup_Base< Outputer > * pGroup = RTTI_GetClsGroup< Outputer >()( typeid( *( T * )( *i ) ) );
				if( pGroup )//
				{
					pGroup->OutputClassName();
					Outputer()( L':' );
					pGroup->OutputElem( *i );//���Ĭ�ϻ���ָ���������ָ����û��ƫ�Ƶ� Ҳ���Ǳ���Ϊ���̳�
					Outputer().NextLine();
				}
				else
				{
					Outputer()( typeid( *( T * )( *i ) ).name() );
					Outputer()( L':' );
					Outputer()( L"δ���ӵ�����-������" );
					Outputer()( typeid( T ).name() );
					Outputer().NextLine();
				}
			}
		}
	};
	#endif

	template< class T, class Outputer = DefaultOutputer >
	class ClsGroup
	#ifdef OBSERVER_USE_RTTI
		: public ClsGroup_RTTI< T, Outputer, Class_Use_RTTI< T >::value >
	#else
		: public ClsGroup_Base< Outputer >
	#endif
	{
	public:
		size_t GetSize();
		void OutputClassName();
	};

	template< class T, class Outputer >
	void ClsGroup< T, Outputer >::OutputClassName()
	{
		Outputer()( typeid( T ).name() );
	}

	template< class T, class Outputer >
	size_t ClsGroup< T, Outputer >::GetSize()
	{
		return sizeof( T );
	}


	//���ClsGroupָ��º���
	template< class T, class Outputer = DefaultOutputer >
	class ClsGroup_GetInstance
	{
	private:
		static ClsGroup< T, Outputer > *s_pInstance;
	public:
		ClsGroup< T, Outputer >* operator()()
		{
			if( !s_pInstance )
			{
				s_pInstance = new ClsGroup< T, Outputer >();
				ClsObserver< Outputer >::GetInstance()->Insert( s_pInstance );
	#ifdef OBSERVER_USE_RTTI
				RTTI_GetClsGroup< Outputer >().AddMap< T >( s_pInstance );
	#endif
			}
			return s_pInstance;
		}
		//���ģ��Ԫ���ر�汾
		//���޷���� �򴴽�ClsGroup_Adv< T, Declare, Outputer >
		template< class Declare >
		ClsGroup< T, Outputer >* Adv()
		{
			if( !s_pInstance )
			{
				s_pInstance = new ClsGroup_Adv< T, Declare, Outputer >();
				ClsObserver< Outputer >::GetInstance()->Insert( s_pInstance );
	#ifdef OBSERVER_USE_RTTI
				RTTI_GetClsGroup< Outputer >().AddMap< T >( s_pInstance );
	#endif
			}
			return s_pInstance;
		}
		bool Exist()
		{
			return s_pInstance != 0;
		}
	};

	//�����⸲��
	template< class T, class BaseClass = UnknownClass, class Outputer = DefaultOutputer >
	class ClsWrapper
	{
	public:
		ClsWrapper()
		{
			ClsGroup_GetInstance< T, Outputer >()()->Insert( ( T * )this );
		}
		ClsWrapper( const ClsWrapper< T, BaseClass, Outputer >& )
		{
			ClsGroup_GetInstance< T, Outputer >()()->Insert( ( T * )this );
		}
		~ClsWrapper()
		{
			ClsGroup_GetInstance< T, Outputer >()()->Remove( ( T * )this );
		}
	};
	template< class T, class Outputer >
	class ClsWrapper< T, UnknownClass, Outputer >
	{
	public:
		ClsWrapper()
		{
			ClsGroup_GetInstance< T, Outputer >()()->Insert( ( T * )this );
		}
		ClsWrapper( const ClsWrapper< T, UnknownClass, Outputer >& )
		{
			ClsGroup_GetInstance< T, Outputer >()()->Insert( ( T * )this );
		}
		~ClsWrapper()
		{
			ClsGroup_GetInstance< T, Outputer >()()->Remove( ( T * )this );
		}
	};


	template< class Outputer >
	ClsObserver< Outputer > * ClsObserver< Outputer >::s_pInstance = 0;
	template< class T, class Outputer >
	ClsGroup< T, Outputer > * ClsGroup_GetInstance< T, Outputer >::s_pInstance = 0;

	template< class Outputer >
	unsigned int ClsGroup_Base< Outputer >::num = 0;

}

using Observer::ClsWrapper;
using Observer::ClsObserver;