#pragma once
//#include"BaseLayer.h"
#include <boost\static_assert.hpp>
//��C++
//������Ļ��С
//�����������ڶ�ֱ����µı仯
//Feng�пɶ������������ ��FengDef��Polygon�������
//�������д�����

namespace OneU
{
	template< class Contents >
	class LineBrk_t;
	template< class Contents >
	class Polygon_t;
	struct CVector4;
	struct CVector2;
	struct CLine2;
	namespace Feng
	{
		enum ALIGN{ LR_CENTER, LR_RIGHT, LR_LEFT, TB_CENTER, TB_TOP, TB_BOTTOM, STRETCH };

		//�������ʵ�൱��һ�������ռ� �û�����ʹ�������
		//ֻ�ܵ�����֮�еľ�̬����
		class Screen
		{	
		private:
			unsigned int m_Width, m_Height;
			Screen( unsigned int Width, unsigned int Height )
				: m_Width( Width ), m_Height( Height )
			{
			}
			static Screen s_Work, s_Device;
			
		public:
			//���ó���Ա����ʱ�����������Ļ
			static void SetWorkScreen( unsigned int Width, unsigned int Height )
			{
				s_Work.m_Width = Width;
				s_Work.m_Height = Height;
	
			}
			//�����豸ʵ����Ļ��С
			static void SetDeviceScreen( unsigned int Width, unsigned int Height )
			{
				s_Device.m_Width = Width;
				s_Device.m_Height = Height;
			}
			//���ڿ��������� ���²�ͬ����ģʽ������Ļ�еĹ�������ķ�Χ��ͬ
			static unsigned int GetWholeWorkScreenWidth( ALIGN alignment )
			{
				return RMapX( s_Device.m_Width ) - RMapX( 0, alignment );
			}
			static unsigned int GetWholeWorkScreenHeight( ALIGN alignment )
			{
				return RMapY( s_Device.m_Height, alignment ) - RMapY( 0, alignment );
			}
			
			//Ϊ4��3�����ת��ʹ��
			//���ܺ��õı�־
			//LR��ʾ������4��3��ת��������Ұ���� �����������С
			//RB���ʾ������Ұ���� ������С������
			//����������ӳ���ʵ������
			static float MapX( float x, ALIGN Alignment )
			{
				switch( Alignment )
				{
				case STRETCH:
				case TB_CENTER:
				case TB_TOP:
				case TB_BOTTOM:
					return x / s_Work.m_Width * s_Device.m_Width;
				case LR_CENTER:
					return ( x / s_Work.m_Width - 0.5f ) * ( static_cast< float >( s_Work.m_Width ) / s_Work.m_Height )
						* s_Device.m_Height + s_Device.m_Width / 2;
				case LR_LEFT:
					return x / s_Work.m_Width * ( static_cast< float > ( s_Work.m_Width ) / s_Work.m_Height ) * s_Device.m_Height;
				case LR_RIGHT:
					return ( x / s_Work.m_Width - 1.0f ) * ( static_cast< float > ( s_Work.m_Width ) / s_Work.m_Height )
						* s_Device.m_Height + s_Device.m_Width;
				}
				return 0.0f;
			}
			static float MapY( float y, ALIGN Alignment = LR_CENTER )
			{
				switch( Alignment )
				{
				case STRETCH:
				case LR_CENTER:
				case LR_LEFT:
				case LR_RIGHT:
					return y / s_Work.m_Height * s_Device.m_Height;
				case TB_CENTER:
					return ( y / s_Work.m_Height - 0.5f ) * ( static_cast< float > ( s_Work.m_Height ) / s_Work.m_Width )
						* s_Device.m_Width + s_Device.m_Height / 2;
				case TB_TOP:
					return y / s_Work.m_Height * ( static_cast< float > ( s_Work.m_Height ) / s_Work.m_Width ) * s_Device.m_Width;
				case TB_BOTTOM:
					return ( y / s_Work.m_Height - 1.0f ) * ( static_cast< float > ( s_Work.m_Height ) / s_Work.m_Width ) * s_Device.m_Width + s_Device.m_Height;
				}
				return 0.0f;
			}
			//������
			static float RMapX( float x, ALIGN alignment = LR_CENTER )
			{
				switch( alignment )
				{
				case STRETCH:
				case TB_CENTER:
				case TB_TOP:
				case TB_BOTTOM:
					return x / s_Device.m_Width * s_Work.m_Width;
				case LR_CENTER:
					return ( ( x - s_Device.m_Width / 2 ) / s_Device.m_Height * s_Work.m_Height / s_Work.m_Width + 0.5f ) * s_Work.m_Width;
				case LR_LEFT:
					return x / s_Device.m_Height * s_Work.m_Height / s_Work.m_Width * s_Work.m_Width;
				case LR_RIGHT:
					return ( ( x - s_Device.m_Width ) / s_Device.m_Height * s_Work.m_Height / s_Work.m_Width + 1.0f ) * s_Work.m_Width;
				}
				return 0.0f;
			}
			static float RMapY( float y, ALIGN alignment = LR_CENTER )
			{
				switch( alignment )
				{
				case STRETCH:
				case LR_CENTER:
				case LR_LEFT:
				case LR_RIGHT:
					return y / s_Device.m_Height * s_Work.m_Height;
				case TB_CENTER:
					return ( ( y - s_Device.m_Height / 2 ) / s_Device.m_Width * s_Work.m_Width / s_Work.m_Height + 0.5f ) * s_Work.m_Height;
				case TB_TOP:
					return y / s_Device.m_Width * s_Work.m_Width / s_Work.m_Height * s_Work.m_Height;
				case TB_BOTTOM:
					return ( ( y - s_Device.m_Height ) / s_Device.m_Width * s_Work.m_Width / s_Work.m_Height + 1.0f ) * s_Work.m_Height;
				}
				return 0.0f;
			}
	
		};
	
		//���ڳ���������λ��ӳ��
		//��������λ��ӳ���� FloatX<STRETCH>�����������ٶȡ����ٶ�ӳ��
		//Screen floatΪScrMapper����
		template< ALIGN alignment >
		class floatX
		{
		private:
			float v;
		public:
			floatX()
			{}
			floatX( float rhs )
				: v( Screen::MapX( rhs, alignment ) )
			{}
			floatX( const floatX< alignment >& rhs )
				: v( rhs.v )
			{}
			floatX< alignment >& operator = ( float rhs )
			{
				v = Screen::MapX( rhs, alignment );
				return *this;
			}
			floatX< alignment >& operator = ( const floatX< alignment >& rhs )
			{
				v = rhs.v;
				return *this;
			}
			operator float()
			{
				return Screen::RMapX( v, alignment );
			}
			float GetContents()
			{
				return v;
			}
		};
		template< ALIGN alignment >
		class floatY
		{
		private:
			float v;
		public:
			floatY()
			{}
			floatY( float rhs )
				: v( Screen::MapY( rhs, alignment ) )
			{}
			floatY( const floatY< alignment >& rhs )
				: v( rhs.v )
			{}
			floatY< alignment >& operator = ( float rhs )
			{
				v = Screen::MapY( rhs, alignment );
				return *this;
			}
			floatY< alignment >& operator = ( const floatY< alignment >& rhs )
			{
				v = rhs.v;
				return *this;
			}
			operator float()
			{
				return Screen::RMapY( v, alignment );
			}
			float GetContents()
			{
				return v;
			}
		};
	
		namespace _Screen
		{
			//ComplexShape��ָPolygon LineBrk�������Ƶ���
			template< class T >
			struct IsComplexShape
			{
				enum{ value = 0 };
			};
	
			template< class Contents >
			struct IsComplexShape< Polygon_t< Contents > >
			{
				enum{ value = 1 };
			};
			template< class Contents >
			struct IsComplexShape< LineBrk_t< Contents > >
			{
				enum{ value = 1 };
			};
		}
		//δ֪��Tһ����˵�����������
		template< int bComplexShape, class T, ALIGN alignment >
		class ScrMapper_Base
			//: public T
		{
	
		};
		//Ϊ LineBrk �� Polygon�������
		template< class T, ALIGN alignment >
		class ScrMapper_Base< 1, T, alignment >
		{
		public:
			T v;
	
			T& GetContents()
			{
				return v;
			}
	
			//���ⲿ�����ڹ�������֮��
			//���ڲ����豸����
			const floatX< alignment > X( unsigned int i ) const
			{
				return *reinterpret_cast< floatX< alignment >* >( &v.X( i ) );
			}
			const floatY< alignment > Y( unsigned int i ) const
			{
				return *reinterpret_cast< floatX< alignment >* >( &v.Y( i ) );
			}
	
			floatX< alignment >& X( unsigned int i )
			{
				return *reinterpret_cast< floatX< alignment >* >( &v.X( i ) );
			}
			floatY< alignment >& Y( unsigned int i )
			{
				return *reinterpret_cast< floatY< alignment >* >( &v.Y( i ) );
			}
		};
		//CPoint2
		template< ALIGN alignment >
		class ScrMapper_Base< 0, CPoint2, alignment >
		{
		public:
			struct 
			{
				floatX< alignment > x;
				floatY< alignment > y;
			};
			CPoint2& GetContents()
			{
				return *reinterpret_cast< CPoint2* > ( this );
			}
		};
		//CRect2
		template< ALIGN alignment >
		class ScrMapper_Base< 0, CVector4, alignment >
		{
		public:
			floatX< alignment > left;
			floatY< alignment > top;
			floatX< alignment > right;
			floatY< alignment > bottom;
			CVector4& GetContents()
			{
				return *reinterpret_cast< CVector4* > ( this );
			}
	
		};
	
		//��Ļ����ӳ�� ��ʱʲôҲ����
		template< class T, ALIGN alignment = LR_CENTER >
		class ScrMapper
			: public ScrMapper_Base< _Screen::IsComplexShape< T >::value, T, alignment >
		{
			BOOST_STATIC_ASSERT( sizeof( T ) == sizeof( ScrMapper_Base< _Screen::IsComplexShape< T >::value, T, alignment > ) );
		};

		//GetScrMapperRef���һ��ScrMapper�Ľӿ�
		//�ٵ���GetContents��õ����겻��
		//��Ҫ�������ܹ�ʹ��Men��������ʵ�ֹ���������ƶ�
		template< ALIGN alignment, class T >
		inline ScrMapper< T, alignment >& GetScrMapperRef( T &ct )
		{
			return reinterpret_cast< ScrMapper< T, alignment >& >( ct );
		}
	
		//CLine2
		template< ALIGN alignment >
		class ScrMapper_Base< 0, CLine2, alignment >
		{
		public:
			ScrMapper< CPoint2 > p1,p2;
			CLine2& GetContents()
			{
				return *reinterpret_cast< CLine2* >( this );
			}
		};


		template< ALIGN alignment >
		CMatrix& GetScrMapMatrix( CMatrix &M )
		{
			M.Transformation( Scale2( Screen::MapX( 1.0f, alignment ) - Screen::MapX( 0.0f, alignment ),//����������X������ű���
				Screen::MapY( 1.0f, alignment ) - Screen::MapY( 0.0f, alignment ) )
				* Translate2( Screen::MapX( 0.0f, alignment ), Screen::MapY( 0.0f, alignment ) ) );
			return M;
		}
		//========================================================================
		//���Ƿָ���
		//========================================================================

		template< class T >
		struct TexPaintTag;
		//����ScrMapper< TexPaint, alignment >��ʹ�� �е�����һ�� ��ʸ��ͼ�β�ͬ
		//����<<���������ĸ����ʸ���ľͲ�һ��
		//���Թؼ�������Map����û��GetContents
		//����
		template< ALIGN alignment, class TextureType >
		class ScrMapper_Base< 0, TexPaintTag< TextureType >, alignment >
		{
		private:
			ScrMapper_Base(){}
		public:
			const TextureType &Tex;
			CMatrix mat;

			TexPaintTag< TextureType >& Map()
			{
				GetScrMapMatrix< alignment >( internal::temp );
				mat = mat * internal::temp;
				return reinterpret_cast< TexPaintTag< TextureType >& >( *this );
			}
		};

		//========================================================================
		//�����Ƿָ���
		//========================================================================
		//�ⲿ��ΪĳЩ�����ṩ��һЩ�򵥵�д��
		template< class T >
		inline ScrMapper< T, LR_LEFT >& SL( T &ct )
		{
			return GetScrMapperRef< LR_LEFT >( ct );
		}
		template< class T >
		inline ScrMapper< T, LR_RIGHT >& SR( T &ct )
		{
			return GetScrMapperRef< LR_RIGHT >( ct );
		}
		template< class T >
		inline ScrMapper< T, LR_CENTER >& SW( T &ct )
		{
			return GetScrMapperRef< LR_CENTER >( ct );
		}
		template< class T >
		inline ScrMapper< T, STRETCH >& SS( T &ct )
		{
			return GetScrMapperRef< STRETCH >( ct );
		}
		//����TexPaintʹ��
		class __MapMan
		{};
		extern __MapMan SEnd;
		template< class T, ALIGN alignment >
		inline T& operator << ( ScrMapper< T, alignment > &lhs, const __MapMan & )
		{
			return lhs.Map();
		}
	}
}