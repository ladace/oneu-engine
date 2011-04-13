/** 
 * @file Polygon.h
 * @brief ����κ����ߵĿ�
 *
 * ���ߺͶ����������ͼ���࣬����ͼ��Ҳ�ǵ��������
 * ��Ϊ������ģ�������ʾʵ�ʴ洢���ͺʹ洢��ʽ���ɴ�Ԥ����ѡ��
 * ������������ز����Ƿ��ʹ�á�
 *
 * ���������ģ�������ʾʵ�ַ�ʽ���и��Ӷ����ʵ�ֺͼ򵥶����ʵ�֡�
 * ���Ӷ����ֻ�����һ��������ܽ�����������������Ϊ��һ���γɲ����׸Ķ�������Ŀ�Ķ������Ƶġ�
 * �򵥶���β��ܴ����������Ρ�
 *
 * ���Ӷ���Σ��ɶ���򵥶������ɣ���������ʾ�пն����档
 * �򵥶���Σ��ɱպ������γɵĶ���Ρ�
 * ����ʱ�붥��˳��Ϊ��������������Ļ����
 * @author Ladace
 * @version 1.0.0.1
 * @date 2010-07-20
 */
#pragma once
#include <vector>
#include "..\..\DXGraphics\D3DDefs.h"
#include "..\..\DXGraphics\VertexUP.h"
#include "FengDef.h"

namespace OneU
{
	//ǰ������
	template< class Contents >
	class MultiPolygon_Impl;
	template< class Contents >
	class SinglePolygon_Impl;
	//��һ������Ϊѡ��洢��������������ݣ���Point��ʽ��Vertex��ʽ�����ڶ�������Ϊʵ�ַ�ʽ
	//���������ʵ�ֻ���ض����ʵ�֣�Ĭ��Ϊ���ض����ʵ�֣��ڴ���������ж���ʹ�ö��ض���Σ�
	//����Polygon_t��δ�������������йصĺ��� ����
	template< class Contents, template< class > class Impl = SinglePolygon_Impl >
	class Polygon_t;

	//�Դ˽ṹ��Ϊ�ӿڱ�׼
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��vector�洢Point�ṹ
	 *
	 * ��Resize��PushBack��
	 * ��������ΪPolyLine_t�Ĳ�����Polygon_t�ĵ�һ������
	 * 	 
	 * @sa PolyLine_t
	 * @sa Polygon_t
	 */
	/* ----------------------------------------------------------------------------*/
	class PointCt
	{
	public:
		typedef CPoint2 value_type;
		typedef std::size_t size_type;
		enum{
			b_resize = 1, /*��ʾ���ඥ����Ŀ�ɱ�*/
			b_push_front = 0, /*��ʾ����ɴ�ͷ������*/
			b_push_back = 1, /*��ʾ����ɴ�β������*/
			b_insert = 0 /*��ʾ��������������*/
		};
	private:
		std::vector< CPoint2 > _v;
		size_type _n;
	public:
		PointCt()
			: _n( 0 )
		{}
		value_type* Data()
		{
			return &_v[0];
		}
		float& X( size_type index )
		{
			ASSERT( index < _n );
			return _v[ index ].x;
		}
		float& Y( size_type index )
		{
			ASSERT( index < _n );
			return _v[ index ].y;
		}
		float X( size_type index ) const
		{
			ASSERT( index < _n );
			return _v[ index ].x;
		}
		float Y( size_type index ) const
		{
			ASSERT( index < _n );
			return _v[ index ].y;
		}
		size_type Size() const
		{
			return _n;
		}
		void Resize( size_type N )
		{
			_v.resize( N );
			_n = N;
		}
		//�������ԣ��ɴ�β������
		void PushBack( float x, float y )
		{
			_v.push_back( CPoint2( x, y ) );
			_n++;
		}
	};

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��vector�洢VertexUP< FVF >�ṹ
	 *
	 * ��Resize��PushBack��
	 * ��������ΪPolyLine_t�Ĳ�����Polygon_t�ĵ�һ������
	 *
	 * @sa PolyLine_t
	 * @sa Polygon_t
	 */
	/* ----------------------------------------------------------------------------*/
	template< dword FVF >
	class VertexCt
	{
	public:
		typedef DX::VertexUP< FVF > value_type;
		typedef std::size_t size_type;
		enum{
			b_resize = 1, /*��ʾ���ඥ����Ŀ�ɱ�*/
			b_push_front = 0, /*��ʾ����ɴ�ͷ������*/
			b_push_back = 1, /*��ʾ����ɴ�β������*/
			b_insert = 0 /*��ʾ��������������*/
		};
	private:
		std::vector< DX::VertexUP< FVF > > _v;
		size_type _n;
	public:
		VertexCt()
			: _n( 0 )
		{}
		value_type* Data()
		{
			return &_v[0];
		}
		float& X( size_type index )
		{
			ASSERT( index < _n );

			return _v[ index ].X();
		}
		float& Y( size_type index )
		{
			ASSERT( index < _n );

			return _v[ index ].Y();
		}
		float X( size_type index ) const
		{
			ASSERT( index < _n );

			return _v[ index ].X();
		}
		float Y( size_type index ) const
		{
			ASSERT( index < _n );

			return _v[ index ].Y();
		}
		size_type Size() const
		{
			return _n;
		}
		void Resize( size_type N )
		{
			_v.resize( N );
			_n = N;
		}
		void PushBack( float x, float y )
		{
			_v.push_back( VertexType() );
			_v[ _n ].x() = x;
			_v[ _n ].y() = y;
			_n++;
		}
	};
	//�̶���С�ĵ�����
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��Cʽ����洢Point�ṹ��
	 *
	 * ����Resize��PushBack��
	 * ��������ΪPolyLine_t�Ĳ�����Polygon_t�ĵ�һ������
	 *
	 * @sa PolyLine_t
	 * @sa Polygon_t
	 */
	/* ----------------------------------------------------------------------------*/
	template< std::size_t N >
	class PointStaticCt
	{
	public:
		typedef CPoint2 value_type;
		typedef std::size_t size_type;
		enum{
			b_resize = 1, /*��ʾ���ඥ����Ŀ�ɱ�*/
			b_push_front = 0, /*��ʾ����ɴ�ͷ������*/
			b_push_back = 1, /*��ʾ����ɴ�β������*/
			b_insert = 0 /*��ʾ��������������*/
		};
		size_type _n;
	private:
		CPoint2 _v[N];
	public:
		PointStaticCt()
			: _n( 0 )
		{}
		value_type* Data()
		{
			return &_v[0];
		}
		float& X( size_type index )
		{
			ASSERT( index < _n );

			return _v[ index ].x;
		}
		float& Y( size_type index )
		{
			ASSERT( index < _n );

			return _v[ index ].y;
		}
		float X( size_type index ) const
		{
			ASSERT( index < _n );

			return _v[ index ].x;
		}
		float Y( size_type index ) const
		{
			ASSERT( index < _n );

			return _v[ index ].y;
		}
		size_type Size() const
		{
			return _n;
		}
		void Resize( size_type NewN )
		{
			ASSERT( NewN <= N );

			_n = NewN;
		}
		void PushBack( float x, float y )
		{
			Resize( _n + 1 );
			_v[ _n - 1 ].x() = x;
			_v[ _n - 1 ].y() = y;
		}
	};
	//�̶���С�Ķ�������
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��Cʽ����洢VertexUP< FVF >�ṹ��
	 *
	 * ����Resize��PushBack��
	 * ��������ΪPolyLine_t�Ĳ�����Polygon_t�ĵ�һ������
	 *
	 * @sa PolyLine_t
	 * @sa Polygon_t
	 */
	/* ----------------------------------------------------------------------------*/
	template< dword FVF, std::size_t N >
	class VertexStaticCt
	{
	public:
		typedef DX::VertexUP< FVF > value_type;
		typedef std::size_t size_type;
		enum{
			b_resize = 1, /*��ʾ���ඥ����Ŀ�ɱ�*/
			b_push_front = 0, /*��ʾ����ɴ�ͷ������*/
			b_push_back = 1, /*��ʾ����ɴ�β������*/
			b_insert = 0 /*��ʾ��������������*/
		};
		size_type _n;
	private:
		DX::VertexUP< FVF > _v[N];
	public:
		VertexStaticCt()
			: _n( 0 )
		{}
		value_type* Data()
		{
			return &_v[0];
		}
		float& X( size_type index )
		{
			ASSERT( index < _n );

			return _v[ index ].X();
		}
		float& Y( size_type index )
		{
			ASSERT( index < _n );

			return _v[ index ].Y();
		}
		float X( size_type index ) const
		{
			ASSERT( index < _n );

			return _v[ index ].X();
		}
		float Y( size_type index ) const
		{
			ASSERT( index < _n );

			return _v[ index ].Y();
		}
		size_type Size() const
		{
			return _n;
		}
		void Resize( size_type NewN )
		{
			ASSERT( NewN <= N );

			_n = NewN;
		}
		void PushBack( float x, float y )
		{
			Resize( _n + 1 );
			_v[ _n - 1 ].x() = x;
			_v[ _n - 1 ].y() = y;
		}
	};


	//Line
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ������
	 *
	 * @tparam Contents �����࣬�ɴ�Ԥ�õ�����ѡ��
	 *
	 * @sa PointCt
	 * @sa VertexCt
	 * @sa PointStaticCt
	 * @sa VertexStaticCt
	 */
	/* ----------------------------------------------------------------------------*/
	template< class Contents >
	class PolyLine_t
	{
	private:
		Contents _r;
	public:
		typedef typename Contents::value_type value_type;
		typedef std::size_t size_type;

		enum{
			b_resize = Contents::b_resize, /*��ʾ���ඥ����Ŀ�ɱ�*/
			b_push_front = Contents::b_push_front, /*��ʾ����ɴ�ͷ������*/
			b_push_back = Contents::b_push_back, /*��ʾ����ɴ�β������*/
			b_insert = Contents::b_insert /*��ʾ��������������*/
		};

		value_type* Data()
		{
			 return _r.Data();
		}
	public:
		PolyLine_t()
			: _r()
		{}
		const float X( size_type index ) const
		{
			return _r.X( index );
		}
		const float Y( size_type index ) const
		{
			return _r.Y( index );
		}
		float& X( size_type index )
		{
			return _r.X( index );
		}
		float& Y( size_type index )
		{
			return _r.Y( index );
		}
		size_type Size() const
		{
			return _r.Size();
		}
		void Clear( size_type N )
		{
			_r.Resize( N );
		}
		void PushBack( float x, float y )
		{
			_r.PushBack( x, y );
		}
	};

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ���Ӷ����ʵ��
	 *
	 * ��ΪPolygon_t�ĵڶ�������
	 *
	 * @sa Polygon_t
	 */
	/* ----------------------------------------------------------------------------*/
	template< class Contents >
	class MultiPolygon_Impl
	{
	public:
		typedef typename Contents::size_type size_type;
		typedef typename Contents::value_type value_type;

		enum{
			b_resize = Contents::b_resize, /*��ʾ���ඥ����Ŀ�ɱ�*/
			b_push_front = Contents::b_push_front, /*��ʾ����ɴ�ͷ������*/
			b_push_back = Contents::b_push_back, /*��ʾ����ɴ�β������*/
			b_insert = Contents::b_insert /*��ʾ��������������*/
		};
	private:
		std::vector< size_type > m_Seg;
		Contents _r;

		size_type _PolyBegin( uint index ) const
		{
			if( index == 0 )return 0;
			ASSERT( index < NoP() );
			return m_Seg[ index - 1 ];
		}
		size_type _PolyEnd( uint index ) const
		{
			if( index == NoP() - 1 ) return _r.Size();
			ASSERT( index < NoP() );
			return m_Seg[ index ];
		}
	public:
		DEPRECATED size_type PolyBegin( uint index ) const
		{
			if( index == 0 )return 0;
			ASSERT( index < NoP() );
			return m_Seg[ index - 1 ];
		}
		DEPRECATED size_type PolyEnd( uint index ) const
		{
			if( index == NoP() - 1 ) return _r.Size();
			ASSERT( index < NoP() );
			return m_Seg[ index ];
		}

	public:
		MultiPolygon_Impl()
			: m_Seg()
		{}
		MultiPolygon_Impl( const VECTOR4 &rc )
		{
			operator=( rc );
		}
		template< class U, template< class > class Impl >
		explicit MultiPolygon_Impl( const Polygon_t< U, Impl > &rhs)
		{
			operator=(rhs);
		}
		template< class U, template< class > class Impl >
		MultiPolygon_Impl& operator=(const Polygon_t<U, Impl> &rhs)
		{
			for( uint i = 0; i < rhs.NoP(); ++i )
			{
				size_type n = Size();
				NewPoly( rhs[i].Size() );
				for( size_type j = 0; j < rhs[i].Size(); ++j )
				{
					_r.X( j + n ) = rhs[i].X( j );
					_r.Y( j + n ) = rhs[i].Y( j );
				}
			}
			return *this;
		}
		MultiPolygon_Impl< Contents >& operator= ( const VECTOR4 &rc )
		{
			Clear( 4 );
			_r.X( 0 ) = ( rc.left ); _r.Y( 0 ) = ( rc.top );
			_r.X( 1 ) = ( rc.left ); _r.Y( 1 ) =( rc.bottom );
			_r.X( 2 ) = ( rc.right ); _r.Y( 2 ) =( rc.bottom );
			_r.X( 3 ) = ( rc.right ); _r.Y( 3 ) = ( rc.top );

			return *this;
		}
		template< class U, template< class > class Impl >
		void Append( const Polygon_t< U, Impl > &rhs )
		{
			for( uint i = 0; i < rhs.NoP(); ++i )
			{
				size_type n = Size();
				NewPoly( rhs[i].Size() );
				for( size_type j = 0; j < rhs[i].Size(); ++j )
				{
					_r.X( j + n ) = rhs[i].X( j );
					_r.Y( j + n ) = rhs[i].Y( j );
				}
			}
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���ض������ڵ��ڴ��
		 * 
		 * @return �ڴ�ε��׵�ַ
		 */
		/* ----------------------------------------------------------------------------*/
		value_type* Data()
		{
			return _r.Data();
		}
		/*����*/
		DEPRECATED float& X( size_type index )
		{
			return _r.X( index );
		}
		/*����*/
		DEPRECATED float& Y( size_type index )
		{
			return _r.Y( index );
		}
		/*����*/
		DEPRECATED const float X( size_type index ) const
		{
			return _r.X( index );
		}
		/*����*/
		DEPRECATED const float Y( size_type index ) const
		{
			return _r.Y( index );
		}
		//�����һ���򵥶��������Ӷ���
		DEPRECATED void PushBack( float x, float y )
		{
			_r.PushBack( x, y );
		}

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ���ж������Ŀ
		 * 
		 * @return ���ж������Ŀ
		 */
		/* ----------------------------------------------------------------------------*/
		size_type Size() const
		{
			return _r.Size();
		}
		//����������һ���� ��СΪN
		void Clear( size_type N = 0 )
		{
			_r.Resize( N );
			m_Seg.resize( 0 );
		}
		class PolyElem
		{
		private:
			Contents &_r;
			size_type _begin, _end;
			uint index;
			const MultiPolygon_Impl< Contents > &p;
		public:
			PolyElem( const MultiPolygon_Impl< Contents > &p, const Contents &contents, size_type _begin, size_type _end, uint index )
				: p( p ), _r( const_cast< Contents& >( contents ) ), _begin( _begin ), _end( _end ), index( index )
			{}
			float& X( size_type index )
			{
				return _r.X( _begin + index );
			}
			float& Y( size_type index )
			{
				return _r.Y( _begin + index );
			}
			const float X( size_type index ) const
			{
				return _r.X( _begin + index );
			}
			const float Y( size_type index ) const
			{
				return _r.Y( _begin + index );
			}
			size_type Size() const{ return _end - _begin; }

			//�������һ���򵥶���οɵ���PushBack Clear����
			void PushBack( float x, float y )
			{
				ASSERT( index == p.NoP() - 1 );
				_r.PushBack( x, y );
				_end++;
			}
			void Clear()
			{
				ASSERT( index == p.NoP() - 1 );
				_r.Resize( _begin );
				_end = _begin;
			}
			CPoint2* Data()
			{
				return _r.Data() + _begin;
			}
			const CPoint2* Data() const
			{
				return _r.Data() + _begin;
			}
		};
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ���Ӷ�����еļ򵥶����
		 * 
		 * @param index �򵥶���ε�ID
		 *
		 * ����NoP()����ü򵥶������Ŀ��index����ΧΪ[ 0, Nop() )��
		 * 
		 * @return ��index���򵥶����
		 *
		 * @sa NoP()
		 */
		/* ----------------------------------------------------------------------------*/
		PolyElem operator[]( uint index )
		{
			return PolyElem( *this, _r, _PolyBegin( index ), _PolyEnd( index ), index );
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ���Ӷ�����еļ򵥶����
		 * 
		 * @param index �򵥶���ε�ID
		 *
		 * ����NoP()����ü򵥶������Ŀ��index����ΧΪ[ 0, Nop() )��
		 * 
		 * @return ��index���򵥶����
		 *
		 * @sa NoP()
		 */
		/* ----------------------------------------------------------------------------*/
		const PolyElem operator[]( uint index ) const
		{
			return PolyElem( *this, _r, _PolyBegin( index ), _PolyEnd( index ), index );
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��Ӽ򵥶����
		 *
		 * �����һ�������Ϊ�գ��򲻻���Ӷ���Σ����ǽ����һ������εĶ�����������PolySize��
		 * 
		 * @param PolySize �򵥶���ζ������Ŀ
		 */
		/* ----------------------------------------------------------------------------*/
		void NewPoly( size_type PolySize )
		{
			if(Size() == 0 || m_Seg.size() != 0 && m_Seg.back() == Size());
			else
				m_Seg.push_back( _r.Size() );
			_r.Resize( _r.Size() + PolySize );
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �򵥶���ε���Ŀ��Number of Polygons��
		 * 
		 * @return ���ؼ򵥶���ε���Ŀ 
		 */
		/* ----------------------------------------------------------------------------*/
		uint NoP() const
		{
			return m_Seg.size() + 1;
		}
	};
	template< class Contents >
	class SinglePolygon_Impl
	{	
	public:
		typedef typename Contents::size_type size_type;
		typedef typename Contents::value_type value_type;

	enum{
		b_resize = Contents::b_resize, /*��ʾ���ඥ����Ŀ�ɱ�*/
		b_push_front = Contents::b_push_front, /*��ʾ����ɴ�ͷ������*/
		b_push_back = Contents::b_push_back, /*��ʾ����ɴ�β������*/
		b_insert = Contents::b_insert /*��ʾ��������������*/
	};
	private:
		Contents _r;

		size_type _PolyBegin( uint index ) const
		{
			ASSERT( index == 0 );
			return 0;
		}
		size_type _PolyEnd( uint index ) const
		{
			ASSERT( index == 0 );
			return _r.Size();
		}
	public:
		DEPRECATED size_type PolyBegin( uint index ) const
		{
			ASSERT( index == 0 );
			return 0;
		}
		DEPRECATED size_type PolyEnd( uint index ) const
		{
			ASSERT( index == 0 );
			return _r.Size();
		}

	public:
		SinglePolygon_Impl()
		{}
		SinglePolygon_Impl( const VECTOR4 &rc )
		{
			operator=( rc );
		}
		template< class U >
		explicit SinglePolygon_Impl( const Polygon_t< U > &other )
		{
			operator=(other);
		}
		template< class U >
		SinglePolygon_Impl& operator =( const Polygon_t< U > &other )
		{
			_r.Resize( other.Size() );
			for( size_type i = 0; i < _r.Size(); i++ )
			{
				_r.X( i ) = other._r.X( i );
				_r.Y( i ) = other._r.Y( i );
			}
			return *this;
		}
		SinglePolygon_Impl< Contents >& operator= ( const VECTOR4 &rc )
		{
			Clear( 4 );
			_r.X( 0 ) = ( rc.left ); _r.Y( 0 ) = ( rc.top );
			_r.X( 1 ) = ( rc.left ); _r.Y( 1 ) =( rc.bottom );
			_r.X( 2 ) = ( rc.right ); _r.Y( 2 ) =( rc.bottom );
			_r.X( 3 ) = ( rc.right ); _r.Y( 3 ) = ( rc.top );

			return *this;
		}
		template< class U >
		void Append( const Polygon_t< U > &rhs )
		{
			unsigned int n = Size();
			NewPoly( rhs.Size() );
			for( unsigned int i = 0; i < rhs.Size(); ++i )
			{
				_r.X( i + n ) = rhs.X( i );
				_r.Y( i + n ) = rhs.Y( i );
			}
		}
		value_type* Data()
		{
			return _r.Data();
		}
		/*����*/
		DEPRECATED float& X( size_type index )
		{
			return _r.X( index );
		}
		/*����*/
		DEPRECATED float& Y( size_type index )
		{
			return _r.Y( index );
		}
		/*����*/
		DEPRECATED const float X( size_type index ) const
		{
			return _r.X( index );
		}
		/*����*/
		DEPRECATED const float Y( size_type index ) const
		{
			return _r.Y( index );
		}
		//�����һ���򵥶��������Ӷ���
		DEPRECATED void PushBack( float x, float y )
		{
			_r.PushBack( x, y );
		}
		size_type Size() const
		{
			return _r.Size();
		}
		//����������һ���� ��СΪN
		void Clear( size_type N = 0 )
		{
			_r.Resize( N );
		}
		class PolyElem
		{
		private:
			Contents &_r;
			size_type _begin, _end;
			uint index;
			const SinglePolygon_Impl< Contents > &p;
		public:
			PolyElem( const SinglePolygon_Impl< Contents > &p, const Contents &contents, size_type _begin, size_type _end, uint index )
				: p( p ), _r( const_cast< Contents& >( contents ) ), _begin( _begin ), _end( _end ), index( index )
			{}
			float& X( size_type index )
			{
				return _r.X( _begin + index );
			}
			float& Y( size_type index )
			{
				return _r.Y( _begin + index );
			}
			const float X( size_type index ) const
			{
				return _r.X( _begin + index );
			}
			const float Y( size_type index ) const
			{
				return _r.Y( _begin + index );
			}
			size_type Size() const{ return _end - _begin; }

			//���һ���򵥶���οɵ���PushBack Clear����
			void PushBack( float x, float y )
			{
				ASSERT( index == p.NoP() - 1 );
				_r.PushBack( x, y );
				_end++;
			}
			void Clear()
			{
				ASSERT( index == p.NoP() - 1 );
				_r.Resize( _begin );
				_end = _begin;
			}
			CPoint2* Data()
			{
				return _r.Data() + _begin;
			}
			const CPoint2* Data() const
			{
				return _r.Data() + _begin;
			}
		};
		//���ص�index�������
		//����NoP��Ա�����ɻ�ö������Ŀ
		PolyElem operator[]( uint index )
		{
			return PolyElem( *this, _r, _PolyBegin( index ), _PolyEnd( index ), index );
		}
		const PolyElem operator[]( uint index ) const
		{
			return PolyElem( *this, _r, _PolyBegin( index ), _PolyEnd( index ), index );
		}
		//Ϊ�˶��ض���������һ���򵥶����
		//���ڵ����������˵ �ⲻ�������
		void NewPoly( size_type PolySize )
		{
			ASSERT( FALSE );
		}
		//��ü򵥶������Ŀ(Number of Polygons)
		uint NoP() const
		{
			return 1;
		}
	};

	//����������Ϊ���÷��ͺ����ܹ�ʶ��������
	template< class Contents, template< class > class Impl >
	class Polygon_t
		: public Impl< Contents >
	{
	public:
		Polygon_t()
		{}
		Polygon_t(const Polygon_t<Contents, Impl>& rhs)
			: Impl<Contents>((Impl<Contents>&)(rhs)){}//��һ���Ļ��� �˴��޸�
		Polygon_t< Contents, Impl >& operator=(const Polygon_t<Contents, Impl>& rhs)
		{
			Impl< Contents >::operator=((Impl<Contents>&)(rhs));return *this;
		}
		template< class T >
		Polygon_t( const T &rhs )
			: Impl< Contents >( rhs )
		{}
		template< class T >
		Polygon_t< Contents, Impl >& operator=( const T &rhs )
		{
			Impl< Contents >::operator=( rhs );return *this;
		}
		CPoint2 P(typename Impl<Contents>::size_type index)
		{
			return CPoint2(X(index), Y(index));
		}
	};

	typedef PolyLine_t< PointCt > PolyLine;
	typedef Polygon_t< PointCt, SinglePolygon_Impl > Polygon;//PolygonĬ��Ϊ���ض����
	typedef Polygon_t< PointCt, MultiPolygon_Impl > MPolygon;
}//namespace OneU
