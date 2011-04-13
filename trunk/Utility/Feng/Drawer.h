/**
 * @file Drawer.h
 * @brief ʸ����ͼ��
 * @author Ladace
 * @version 1.0.0.1
 * @date 2010-09-01
 */
#pragma once

#include "../Utility.h"
#ifdef __ONEU_USE_GE
#include "..\..\DXGraphics\LineE.h"
#else
#pragma message( __FILE__":Feng Needs OneU GE Library!")
AnErrorOccured!!!
#endif

#include <vector>
#include "Polygon.h"
#include "FengAlgo.h"
#include "..\..\DXGraphics\DXGraphics.h"
#include "..\..\DXGraphics\VertexUP.h"
#include "FengMen.h"

//������
//�ײ�(0)
//��д�������� �л��ƺ���
//��Drawer���ع���������1.��ͼ�λ�ȡ��ֱ�ӻ��Ƶ�Vertex������ �ɴ�Polygon_t< VertexCt >����2.���Ʋ��֣��ͺܼ��ˣ�
//�ⲿ�ӿ�һ��
//@todo ���������ڳ���ֱ�ӱ��涥���� �������� ʹ�ö�����ɫ���������������� ��Ȼ����任�����
//���ԸĽ��ĵط� ʹ�ö�����ɫ���������������� ����CPU����Զ���������任
//ԭ���ϲ�����ScreenPainter����

namespace OneU
{
	namespace Feng
	{
		class ONEU_UTIL_API ScreenDrawer
		{
		private:
			static int ClassNum;
			DX::RenderManip &m_Rd;
			MATRIX m_Mat;
			bool m_UseMatrix;

#ifdef __ONEU_USE_GE
#if __ONEUE_LINE_VERSION == 100
		public:
			static float DefaultWidth;

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief �趨�������
			 *
			 * ��Ҫ������֧�֡� 
			 *
			 * @param fWidth ��ȴ�С
			 */
			/* ----------------------------------------------------------------------------*/
			void SetWidth( float fWidth )
			{
				DX::LineE::I.SetWidth( fWidth );
				m_Width = fWidth;
			}
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ����������
			 *
			 * ��Ҫ������֧�֡�
			 *
			 * @return ��ȴ�С
			 */
			/* ----------------------------------------------------------------------------*/
			float GetWidth() const
			{
				return m_Width;
			}
		private:
			float m_Width;
#else
NeedCode
#endif
#else
NeedCode
#endif
		public:
			ScreenDrawer( DX::RenderManip &Rd )
				: m_Rd( Rd ), m_UseMatrix( false )
#ifdef __ONEU_USE_GE
				, m_Width(DX::LineE::I.GetWidth())
#endif
			{
				ClassNum++;
				ASSERT( ClassNum == 1 );
				SetWidth( DefaultWidth );//Ĭ���������ֵ

				//DX::LineE::I.Begin(); //д�������������д��� ��ΪBegin֮����������������Ķ�������ִ���
			}
			~ScreenDrawer()
			{
				//DX::LineE::I.End();
				ClassNum--;
			}
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief �趨�任����
			 *
			 * @param mat ����
			 */
			/* ----------------------------------------------------------------------------*/
			void SetTransform( const MATRIX &mat )
			{
				m_Mat = mat;
				if( memcmp( &mat, &matIMatrix, sizeof( mat ) ) == 0 ) m_UseMatrix = false;
				else m_UseMatrix = true;
			}
		private:
			//PolyLine
			//���ݷ�CPoint2�����ٰ汾
			template< class Contents, class T >
			void _Draw( const PolyLine_t< Contents > &line, COLOR crColor, T );

			//����ΪCPoint2�Ŀ��ٰ汾
			template< class Contents >
			void _Draw( const PolyLine_t< Contents > &line, COLOR crColor, CPoint2 );

			//Polygon
			//���ݷ�CPoint2�����ٰ汾
			template< class Contents, template< class > class Impl, class T >
			void _Draw( const Polygon_t< Contents, Impl > &polygon, COLOR crColor, T );

			//����ΪCPoint2�Ŀ��ٰ汾
			template< class Contents, template< class > class Impl >
			void _Draw( const Polygon_t< Contents, Impl > &pol, COLOR crColor, CPoint2 );
		public:
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ���ƶ�ά��
			 *
			 * ��Ĵ�СΪ�����Ŀ�ȴ�С��
			 * @param p ��ά��
			 * @param crColor ����ɫ
			 */
			/* ----------------------------------------------------------------------------*/
			void Draw( const CPoint2 &p, COLOR crColor );
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ���ƶ�ά��
			 *
			 * @param line ��ά��
			 * @param crColor ������ɫ
			 */
			/* ----------------------------------------------------------------------------*/
			void Draw( const CLine2 &line, COLOR crColor );
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ���ƾ��α���
			 *
			 * @param rc ����
			 * @param crColor ��ɫ
			 */
			/* ----------------------------------------------------------------------------*/
			void Draw( const CRect &rc, COLOR crColor );
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ��������
			 *
			 * Ч����Contents�йء�
			 * @todo ��ǰʵ���£�Contentsʹ��CPoint2�Ҳ�ʹ�þ����Ч����ߡ�����ƫ�͡�
			 * @param line ����
			 * @param crColor ������ɫ
			 */
			/* ----------------------------------------------------------------------------*/
			template< class Contents >
			void Draw( const PolyLine_t< Contents > &line, COLOR crColor )
			{
				//���ݲ�ͬ��value_typeִ�в�ͬ�ĺ��� ���Ǽ������һ������ ռ��һ��ʱ�� �ⲻ֪���ܲ��ܱ��Ż���
				_Draw( line, crColor, typename PolyLine_t< Contents >::value_type() );
			}
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ���ƶ���α���
			 *
			 * @param polygon �����
			 * @param crColor ��ɫ
			 */
			/* ----------------------------------------------------------------------------*/
			template< class Contents, template< class > class Impl >
			void Draw( const Polygon_t< Contents, Impl > &polygon, COLOR crColor )
			{
				//���ݲ�ͬ��value_typeִ�в�ͬ�ĺ���
				_Draw( polygon, crColor, typename Contents::value_type() );
			}

			//���ͼ��
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ������
			 *
			 * @param rc ����
			 * @param crColor ������ɫ
			 */
			/* ----------------------------------------------------------------------------*/
			void Fill( const CRect &rc, COLOR crColor );

			//͹�������� ���Ʒ�ʽ���Ե�һ�����㻭������
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ���͹�����
			 *
			 * Ҫ��ÿһ���Ӷ���ζ���͹����βſ�����ȷ���ơ�
			 * @param polygon �����
			 * @param crColor �������ɫ
			 */
			/* ----------------------------------------------------------------------------*/
			template< class Contents, template< class > class Impl >
			void Fill( const Polygon_t< Contents, Impl > &polygon, COLOR crColor );

			//���������� ���ȷ����͹�����Ӧʹ��Fill
			//������Ҫʹ�øú��� ��������˳���п�����Fill�ɹ����� �μ�Fill
			//���Ʊ��Խ��Ķ������ʾ�������Ԥ�ڣ��������������
			//@todo ʵ����δ֪���� �����ܹ��Ѱ�����ηָ�����ɶ���εĺ�����
			//���������ڸ������ ����Ԫ����
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ��䰼�����
			 *
			 * Ϊ����ȷ��Ⱦ������ζ�����ĺ�����Ч�ʺܵ͡�������ʹ�á�
			 * @param polygon �����
			 * @param crColor �������ɫ
			 */
			/* ----------------------------------------------------------------------------*/
			template< class Contents, template< class > class Impl >
			void FillConcave( const Polygon_t< Contents, Impl > &polygon, COLOR crColor );
		private:
			//ʵ��FillConcave�ĵݹ麯��
			//ע��First Last��ǰ���������
			template< class Contents, template< class > class Impl >
			void _FillConcave( const Polygon_t< Contents, Impl > &polygon, std::vector< DX::VertexUP< DX::FVF_XYZRHW | DX::FVF_DIFFUSE > > &Use,
				uint Center, uint First, uint Last, COLOR crColor );
		public:
		};//class Drawer
		
		template< class Contents, class T >
		void ScreenDrawer::_Draw( const PolyLine_t< Contents > &line, COLOR crColor, T )
		{
			using DX::LineE;
			
			//@todo �ĳ���ɫ����ʽ
			static std::vector< CPoint2 > point;

			point.resize( line.Size() );

			for( uint i = 0; i < line.Size(); i++ )
			{
				point[ i ].x = line.X( i );
				point[ i ].y = line.Y( i );
				if (m_UseMatrix) point[i] << m_Mat;
			}
			LineE::I.Draw( point, line.Size(), crColor );
		}
		template< class Contents >
		void ScreenDrawer::_Draw( const PolyLine_t< Contents > &line, COLOR crColor, CPoint2 )
		{
			if (m_UseMatrix) _Draw(line, crColor, void*());//ʹ�����ٷ�ʽ
			else
				DX::LineE::I.Draw( line.Data(), line.Size(), crColor );
		}

		template< class Contents, template < class > class Impl, class T >
		void ScreenDrawer::_Draw( const Polygon_t< Contents, Impl > &polygon, COLOR crColor, T )
		{
			using DX::LineE;

			//@todo �ĳ���ɫ����ʽ ����ٺܶ�
			const uint num = polygon.NoP();

			std::vector< CPoint2 > point;

			uint t;

			for( uint i = 0; i < num; i++ )
			{
				t = 0;

				point.resize( polygon[i].Size() + 1 );
				for( uint j = 0; j < polygon[i].Size(); ++j )
				{
					point[t].x = polygon[i].X( j );
					point[t].y = polygon[i].Y( j );
					if (m_UseMatrix) point[t] << m_Mat;
					t++;
				}
				point[ t ] = point[ 0 ];

				//���������ǿյ� �Ͳ����л���
				if( t == 0 ) continue;

				LineE::I.Draw( &point[0], t + 1, crColor );//δ��鷵��ֵ
			}
		}

		template< class Contents, template< class > class Impl >
		void ScreenDrawer::_Draw( const Polygon_t< Contents, Impl > &pol, COLOR crColor, CPoint2 )
		{
			using DX::LineE;

			//@todo �ĳ���ɫ����ʽ
			if( m_UseMatrix )
			{
				_Draw(pol, crColor, (void*)(0));//ʹ�����ٷ�ʽ
				return;
			}
			for( uint i = 0; i < pol.NoP(); i++ )
			{
				LineE::I.Draw( pol[i].Data(), pol[i].Size(), crColor );
				static CPoint2 v[ 2 ];
				v[ 0 ].x = pol[i].X( pol[i].Size() - 1 ); v[ 0 ].y = pol[i].Y( pol[i].Size() - 1 );
				v[ 1 ].x = pol[i].X( 0 ); v[ 1 ].y = pol[i].Y( 0 );
				LineE::I.Draw( v, 2, crColor );
			}
		}

		template< class Contents, template< class > class Impl >
		void ScreenDrawer::Fill( const Polygon_t< Contents, Impl > &polygon, COLOR crColor )
		{
			if( polygon.Size() < 3 ) return;

			//@todo �ĳ���ɫ����ʽ
			//�趨����任
			if( m_UseMatrix ) Graphics.SetWorldTransform( &m_Mat );
			//else Graphics.SetWorldTransform( NULL );

			std::vector< DX::VertexUP< DX::FVF_XYZRHW | DX::FVF_DIFFUSE > > v;

			v.resize( polygon.Size() );
			for( uint i = 0; i < polygon.Size(); i++ )
			{
				v[i].X() = polygon.X( i );
				v[i].Y() = polygon.Y( i );
				v[i].Z() = 0.0f;
				v[i].RhW() = 1;
				v[i].Diffuse() = crColor;
			}
			Graphics.SetFVF( &v[0] );

			for( uint i = 0; i < polygon.NoP(); i++ )
			{
				const uint nElem = polygon[i].Size() - 2;
				if( nElem >= 1 )
				{
					m_Rd.RenderVertexUP( DX::RenderManip::PT_TRIANGLEFAN, &v[ polygon.PolyBegin( i ) ],
						nElem );
				}
			}
		}
		template< class Contents, template< class > class Impl >
		void ScreenDrawer::FillConcave( const Polygon_t< Contents, Impl > &polygon, COLOR crColor )
		{
			if( polygon.Size() < 3 ) return;

			//�趨����任
			if( m_UseMatrix ) Graphics.SetWorldTransform( &m_Mat );
			//else Graphics.SetWorldTransform( NULL );

			std::vector< DX::VertexUP< DX::FVF_XYZRHW | DX::FVF_DIFFUSE > > v;

			Graphics.SetFVF( DX::FVF_XYZRHW | DX::FVF_DIFFUSE );

			for( uint k = 0; k < polygon.NoP(); k++ )
			{
				_FillConcave( polygon, v, polygon.PolyBegin( k ), polygon.PolyBegin( k ) + 1, polygon.PolyEnd( k ), crColor );
			}
		}

		template< class Contents, template< class > class Impl >
		void ScreenDrawer::_FillConcave( const Polygon_t< Contents, Impl > &polygon, std::vector< DX::VertexUP< DX::FVF_XYZRHW | DX::FVF_DIFFUSE > > &v, uint Center, uint First, uint Last, COLOR crColor )
		{

			if( First >= Last - 1 )return;

			v.resize( Last - First + 1 );
			v[0].X() = polygon.X( Center );
			v[0].Y() = polygon.Y( Center );
			v[0].RhW() = 1.0f;
			v[0].Diffuse() = crColor;
			v[1].X() = polygon.X( First );
			v[1].Y() = polygon.Y( First );
			v[1].RhW() = 1.0f;
			v[1].Diffuse() = crColor;
			
			uint i = First + 1;
			for( ; i < Last; i++ )
			{
				if( ( CLine2( polygon.X( Center ), polygon.Y( Center ), polygon.X( i ), polygon.Y( i ) ) ^ polygon )
					|| ( !( CPoint2( ( polygon.X( Center ) + polygon.X( i ) ) / 2, ( polygon.Y( Center ) + polygon.Y( i ) ) / 2 ) ^ polygon ) ) )//�жϴ��߶��Ƿ��ڶ������ ���߶��е���ʵ��
					break;
				v[i - First + 1].X() = polygon.X( i );
				v[i - First + 1].Y() = polygon.Y( i );
				v[i - First + 1].RhW() = 1.0f;
				v[i - First + 1].Diffuse() = crColor;
			}

			//һ�λ��Ƴɹ������
			if( Last - i <= 1 )
			{
				if( i - First - 1 > 0 )
					m_Rd.RenderVertexUP( DX::RenderManip::PT_TRIANGLEFAN, &v[0],
					i - First - 1 );
				return;
			}

			uint j = i + 1;
			for( ; j < Last; j++ )
				if( !( CLine2( polygon.X( Center ), polygon.Y( Center ), polygon.X( j ), polygon.Y( j ) ) ^ polygon 
					|| ( !( CPoint2( ( polygon.X( Center ) + polygon.X( j ) ) / 2, ( polygon.Y( Center ) + polygon.Y( j ) ) / 2 ) ^ polygon ) ) ) )
					break;

			if( j >= Last )
			{
				if( i - First - 1 > 0 )
					m_Rd.RenderVertexUP( DX::RenderManip::PT_TRIANGLEFAN, &v[0],
					i - First - 1 );
			}
			v[i - First + 1].X() = polygon.X( j );
			v[i - First + 1].Y() = polygon.Y( j );
			v[i - First + 1].RhW() = 1.0f;
			v[i - First + 1].Diffuse() = crColor;
			m_Rd.RenderVertexUP( DX::RenderManip::PT_TRIANGLEFAN, &v[0],
				i - First );

			_FillConcave( polygon, v, i - 1, i, j + 1, crColor );//��Ϊ�����ұ� ������j + 1
			_FillConcave( polygon, v, Center, j, Last, crColor );
		}
	}//namespace Feng
}//namespace OneU
