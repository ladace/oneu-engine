#pragma once
#include "..\..\DXGraphics\SurTex\STLock.h"
#include "Polygon.h"
#include "FengDef.h"

namespace OneU
{
	namespace Feng
	{
		//����ֵ ��Ҫ��GetImageBound
		template< typename T >
		inline T _abs( T v )
		{
			return v >= 0 ? v : -v;
		}

		//���ͼ��߽�
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ���ͼ��߽�
		 *
		 * ���ͼ��߽磬���Զ���ε���ʽ����polygon��߽緽��Ϊ��ʱ�롣
		 *
		 * @tparam Format ���ظ�ʽ
		 * @param Texture ����ͼ�������
		 * @param Level �����һ�����𣬽����������ı���������߽硣
		 * @param prc ͼ�����ڵľ��Σ���ΪNULL��ȫ��������Ϊͼ��
		 * @param polygon �������Ķ����
		 * @param minAlpha ��Ϊ���ش��ڵ���С͸���ȣ���Ϊ0����Ч��
		 * @param crKeyColor �ؼ�ɫ��Ĭ��Ϊ0
		 */
		/* ----------------------------------------------------------------------------*/
		template< DX::PXLFORMAT Format, class Contents >
		void GetImageBound( DX::Texture_Lk& Texture, uint Level, const RECT *prc, Polygon_t< Contents, MultiPolygon_Impl >& polygon, dword minAlpha, COLOR crKeyColor = 0 )
		{
			static COLOR crKey;
			static dword min;
			crKey = crKeyColor;
			min = minAlpha;
			struct ColorFunctor
			{
				bool operator()( COLOR crColor )
				{
					if( crColor == crKey )
						return FALSE;
					if( GetAlpha( crColor ) < min )
						return FALSE;
					return TRUE;
				}
			};

			DX::SurfaceLock< Format > lk( &Texture.GetSurfaceLevel(Level), prc );

			_GetImageBound< ColorFunctor >( lk, polygon );
		}

		/*@cond INTERNAL_MPL*/
		template< class ColorFunctor, class T, class Contents >
		void _GetImageBound( T& Lock, Polygon_t< Contents, MultiPolygon_Impl >& polygon )
		{
			const int MAX_SIZE = 5000;
			const float PRECISION = 50.0f;
			struct _Struct
			{
				_Struct()
					: top( 0 )
				{}
				struct 
				{
					struct
					{
						uint left, right;
					};
				} v[ MAX_SIZE ];
				int a;//�ڱ� ����Line[-1]����ʵ���ֵ ��Ϊ0
				int Line[ 1500 ];
				uint top;
			} obj;
			obj.a = 0;
			for( uint j = 0; j < Lock.GetLockHeight(); j++ )
			{
				int k = -1;//�������±� -1��ʾ��Ч
				for( uint i = 0; i < Lock.GetLockWidth(); i++ )//��X��������ѭ����һ����ϰ�ߣ���Lock�Ķ�д�������ܻ����Ч��
				{
					if( ColorFunctor()( Lock.GetPixel( i, j ) ) )
					{
						if( k != -1 )
						{
							obj.v[ k ].right = i;
						}
						else
						{
							obj.v[ obj.top ].left = obj.v[ obj.top ].right = i;
							k = obj.top;
							obj.top++;
						}
					}
					else
						k = -1;
				}
				obj.Line[ j ] = obj.top;
				ASSERT( obj.top < MAX_SIZE - 1000 );
			}


			
			Lock.Unlock();
			//������GetLockHeight�������øĳ�һ����
			//�Ż��õ�����
			float weight = 0.0f;
			bool b[ MAX_SIZE * 2 ] = {};
			polygon.Clear( 0 );

			int i = 0, y = 0;
			for( ; y < Lock.GetLockHeight(); y++ )
				for( ; i < obj.Line[y]; i++ )
				{
					if( !b[i] )
						goto end;
				}
end:
			while( i != obj.top )
			{
				int dir = 1;//���� 1��ʾ��� ���½��� 0��ʾ�Ҳ� ���Ͻ���
				while( TRUE ) 
				{
					//���½��е������
					if( dir == 1 )
					{
						//�ս�����
						if( b[i] )goto nextseg;

						b[i] = true;
						if( polygon.PolyEnd( polygon.NoP() - 1 ) - polygon.PolyBegin( polygon.NoP() - 1 ) >= 2 )
						{
							//�Ż�����
							float area = ( polygon.P( polygon.Size() - 2 ) >> polygon.P( polygon.Size() - 1 ) )
								% ( polygon.P( polygon.Size() - 1 ) >> CPoint2( ( float )obj.v[i].left, ( float )y + 0.5f ) );
							if( _abs( area + weight ) <= PRECISION
								)//�����ж������ѣ�����̫�á�����
							{
								weight += area;
								polygon.X( polygon.Size() - 1 ) = ( float )obj.v[i].left + 1.0f;
								polygon.Y( polygon.Size() - 1 ) = ( float )y + 0.5f;
								goto noPush1;
							}
						}
						weight = 0;
						polygon.PushBack( ( float )obj.v[i].left + 1.0f, ( float )y + 0.5f );//�������� y������һ����� ����
noPush1:
						if( y + 1 == Lock.GetLockHeight() )
						{
							//ת�Ƶ��Ҳ� ���Ͻ��� i,y����
							dir = 0;
							continue;
						}

						uint oldy = y;
						for( int k = obj.Line[y]; k < obj.Line[y + 1]; k++ )
						{
							if( obj.v[k].right >= obj.v[i].left && obj.v[k].left <= obj.v[i].right )
							{
								if(((i - 1) >= obj.Line[y - 1]) && (obj.v[i - 1].right >= obj.v[k].left))
								{
									i = i - 1;
									//y����
									dir = 0;
									break;
								}
								else
								{
									y++;
									i = k;
									//dir����
									break;
								}
							}
						}
						if( k == obj.Line[oldy + 1])
							//ת�Ƶ��Ҳ�
							dir = 0;
					}
					//���Ͻ��е������
					else
					{
						//�ս�����
						if( b[i + MAX_SIZE] )goto nextseg;
						b[i + MAX_SIZE] = true;

						if( polygon.PolyEnd( polygon.NoP() - 1 ) - polygon.PolyBegin( polygon.NoP() - 1 ) >= 2 )
						{	
							float area = ( polygon.P( polygon.Size() - 2 ) >> polygon.P( polygon.Size() - 1 ) )
								% ( polygon.P( polygon.Size() - 1 ) >> CPoint2( ( float )obj.v[i].right, ( float )y + 0.5f ) );
							if( _abs(area + weight) <= PRECISION
								)//����
							{
								weight += area;
								polygon.X( polygon.Size() - 1 ) = ( float )obj.v[i].right + 1.0f;
								polygon.Y( polygon.Size() - 1 ) = ( float )y + 0.5f;
								goto noPush2;
							}
						}
						weight = 0.0f;
						polygon.PushBack( ( float )obj.v[i].right, ( float )y + 0.5f );//�������� ����
noPush2:
						if( y == 0 )
						{
							//ת�Ƶ���� ���½��� i,y����
							dir = 1;
							continue;
						}

						uint oldy = y;

						for( int k = obj.Line[y - 1] - 1; k >= obj.Line[y - 2]; k-- )
						{
							if( obj.v[k].left <= obj.v[i].right && obj.v[k].right >= obj.v[i].left )
							{
								if( i + 1 < obj.Line[y] && obj.v[i + 1].left <= obj.v[k].right )
								{
									i = i + 1;
									//y����
									dir = 1;
									break;
								}
								else
								{
									y--;
									i = k;
									//dir����
									break;
								}
							}
						}

						if( k == obj.Line[oldy - 2] - 1 )
							dir = 1;

					}

				}
				//whileѭ������

nextseg:

				i = 0; y = 0;
				for( ; y < Lock.GetLockHeight(); y++ )
					for( ; i < obj.Line[y]; i++ )
					{
						if( !b[i] )
							goto end2;
					}
end2:

				if( i != obj.top )
					polygon.NewPoly( 0 );
			}//while
		}
		/*@endcond*//* INTERNAL_MPL*/
	}//namespace Feng
}//namespace OneU
