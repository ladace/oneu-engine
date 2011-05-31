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
//��װ�ɱ䶥���ʽ����
//Ŀǰ֧�ֱ�־λ��������
#pragma once
#include <d3d9.h>
#include "D3DDefs.h"

namespace OneU
{
	namespace DX
	{
		//FVF��־����
		enum FVF_FLAG
		{
			FVF_XYZ = D3DFVF_XYZ,
			FVF_XYZRHW = D3DFVF_XYZRHW,
			FVF_NORMAL = D3DFVF_NORMAL,
			FVF_PSIZE = D3DFVF_PSIZE,
			FVF_DIFFUSE = D3DFVF_DIFFUSE,
			FVF_SPECULAR = D3DFVF_SPECULAR,
			FVF_TEX1 = D3DFVF_TEX1
		};

		/* ----------------------------------------------------------------------------*/
		/*@cond INTERNAL_MPL*/
		/* ----------------------------------------------------------------------------*/
//�ڲ�ʹ�ú궨��
#define FVF_TEX FVF_TEX1
#define __FVF_LAST_FLAG 0x8000
#define __FVF_OVER_TEX 0x1000



		/////////////////////////////////
		//��ģ�������Ƿ����ض�mask���б�־λ
		template< uint32 flag_mask, uint32 flag >
		struct __FVF_Flag_Traits
		{
			enum{ bHas = ( flag_mask & flag ) ? 1 : 0 };
			typedef typename __Bool_Category< bHas >::Category Has_Category;
		};

		template< uint32 num_of_tex, uint32 flag >
		struct __FVF_Flag_Tex_Traits
		{
			enum{ Num = ( ( flag & D3DFVF_TEXCOUNT_MASK ) >> D3DFVF_TEXCOUNT_SHIFT ), bHas = Num >= num_of_tex };
			typedef typename __Bool_Category< bHas >::Category Has_Category;
		};
		///////////////////////////////////
		//�����ض�mask��ʾ�ı�־����ʾ��FVF��Ա�Ŀռ��С
		//////////////////////////////////
		template< uint32 flag_mask >
		struct __FVF_Mask_Traits
		{
			enum{ Size = 0 };
		};
		template<>
		struct __FVF_Mask_Traits< FVF_XYZ >
		{
			enum{ Size = 3 * sizeof( float ) };
		};
		template<>
		struct __FVF_Mask_Traits< FVF_XYZRHW >
		{
			enum{ Size = 4 * sizeof( float ) };
		};
		template<>
		struct __FVF_Mask_Traits< FVF_NORMAL >
		{
			enum{ Size = 3 * sizeof( float ) };
		};
		template<>
		struct __FVF_Mask_Traits< FVF_PSIZE >
		{
			enum{ Size = sizeof( float ) };
		};
		template<>
		struct __FVF_Mask_Traits< FVF_DIFFUSE >
		{
			enum{ Size = sizeof( D3DCOLOR ) };
		};
		template<>
		struct __FVF_Mask_Traits< FVF_SPECULAR >
		{
			enum{ Size = sizeof( D3DCOLOR ) };
		};
		template<>
		struct __FVF_Mask_Traits< FVF_TEX >
		{
		};
		/////////////////////////////////
		
		//���ڵ�����ѰFVF��Ա��ƫ�Ƶ�ַ�ķº���
		template< uint32 flag_mask , uint32 flag , int pos = 0 >
		class __FVF_FindValue
		{
		public:
			enum {
				_size = __FVF_Flag_Traits< flag_mask, flag >::bHas ? __FVF_Mask_Traits< flag_mask >::Size : 0,
				_offset = __FVF_FindValue< ( flag_mask >> 1 ), flag, pos >::_end,
				_end = _offset + _size
			};
		private:
			void * _Get( char * p, __True_Category )
			{
				return &p[ _offset + pos ];
			}
		public:
			void * operator() ( void * p )
			{
				return _Get(
					reinterpret_cast< char * >( p ),
					__FVF_Flag_Traits< flag_mask, flag >::Has_Category()
					);
			}
		};

		//����������������⴦��ƫ�ػ��汾
		//posΪż��ָ���pos / 2 + 1�������U����
		//posΪ����ָ���pos / 2 + 1�������V����
		template< uint32 flag, int pos >
		class __FVF_FindValue< FVF_TEX, flag, pos >
		{
		public:
			enum{ 
				_size =  __FVF_Flag_Tex_Traits< pos /2 + 1, flag >::Num * 2 * sizeof( float ),
				_offset = __FVF_FindValue< ( FVF_TEX >> 1 ), flag, pos >::_end,
				_end = _offset + _size
			};
		private:
			void * _Get( char * p, __True_Category )
			{
				return &p[ _offset + pos * 4 ];
			}
		public:
			void * operator() ( void * p )
			{
				return _Get(
					reinterpret_cast< char * >( p ),
					__FVF_Flag_Tex_Traits< pos / 2 + 1, flag >::Has_Category()
					);
			}
		};

		//����������mask��һ����mask�����⴦��
		template< uint32 flag, int pos >
		class __FVF_FindValue< __FVF_OVER_TEX, flag, pos >
		{
		public:
			enum{
				_size = __FVF_Flag_Traits< D3DFVF_LASTBETA_UBYTE4, flag >::bHas ? __FVF_Mask_Traits< D3DFVF_LASTBETA_UBYTE4 >::Size : 0,
				_offset =	__FVF_FindValue< ( FVF_TEX ), flag, pos >::_end,
				_end = _size + _offset
			};
		private:
			void * _Get( char * p, __True_Category )
			{
				return &p[ _offset + pos ];
			}
		public:
			void * operator() ( void * p )
			{
				return _Get(
					reinterpret_cast< char * >( p ),
					__FVF_Flag_Tex_Traits< pos / 2 + 1, flag >::Has_Category()
					);
			}
		};
		//////////////////

		//��ʼ����Ѱ��ַ�º��� �����յ�
		template< uint32 flag, int pos >
		class __FVF_FindValue< 0, flag, pos >
		{
		public:
			enum{ _end = 0 };
		};

		/*@endcond*///INTERNAL_MPL
		/* ----------------------------------------------------------------------------*/

		
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �û��ɱ䶥��
		 *
		 * @tparam flag FVF��־λ
		 */
		/* ----------------------------------------------------------------------------*/
		template< uint32 flag >
		class VertexUP
		{
			
		public:
			enum{
				Flag = flag,
				Size = __FVF_FindValue< __FVF_LAST_FLAG, Flag >::_end
			};
		private:
			//����ȥŪÿ��const��Ա����
			//���ֻ���ڲ�����
			mutable char buffer[ Size ];

			template < int pos >
			struct _FindXYZ
			{
				void * operator()( void * p_buffer, __True_Category )//3D�����
				{
					return __FVF_FindValue< FVF_XYZ, Flag, pos >()( p_buffer );
				}
				void * operator()( void * p_buffer, __False_Category )//2D�����
				{
					return __FVF_FindValue< FVF_XYZRHW, Flag, pos >()( p_buffer );
				}
			};
		public:

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����
			 *
			 * ���ڲ���Ա����
			 */
			/* ----------------------------------------------------------------------------*/
			void Zero()
			{
				memset( buffer, 0, sizeof( buffer ) );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ʼ��
			 *
			 * ������Ҳ����������
			 */
			/* ----------------------------------------------------------------------------*/
			void Initialize()
			{
				Zero();
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief X����
			 * 
			 * @return X���긡����������
			 */
			/* ----------------------------------------------------------------------------*/
			float & X()
			{
				return *reinterpret_cast< float * >(
					_FindXYZ< 0 >()( buffer, __FVF_Flag_Traits< FVF_XYZ, Flag >::Has_Category() )
					);
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���X����
			 * 
			 * @return X���긡����������
			 */
			/* ----------------------------------------------------------------------------*/
			const float & X() const
			{
				return *reinterpret_cast< const float * >(
					_FindXYZ< 0 >()( buffer, __FVF_Flag_Traits< FVF_XYZ, Flag >::Has_Category() )
					);
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief Y����
			 * 
			 * @return Y���긡����������
			 */
			/* ----------------------------------------------------------------------------*/
			float & Y()
			{
				return *reinterpret_cast< float * >(
					_FindXYZ< sizeof( float ) >()( buffer, __FVF_Flag_Traits< FVF_XYZ, Flag >::Has_Category() )
					);
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���Y����
			 * 
			 * @return Y���긡����������
			 */
			/* ----------------------------------------------------------------------------*/
			const float & Y() const
			{
				return *reinterpret_cast< float * >(
					_FindXYZ< sizeof( float ) >()( buffer, __FVF_Flag_Traits< FVF_XYZ, Flag >::Has_Category() )
					);
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief Z����
			 * 
			 * @return Z���긡����������
			 */
			/* ----------------------------------------------------------------------------*/
			float & Z()
			{
				return *reinterpret_cast< float * >(
					_FindXYZ< 2 * sizeof( float ) >()( buffer, __FVF_Flag_Traits< FVF_XYZ, Flag >::Has_Category() )
					);
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���Z����
			 * 
			 * @return Z���긡����������
			 */
			/* ----------------------------------------------------------------------------*/
			const float & Z() const
			{
				return *reinterpret_cast< float * >(
					_FindXYZ< 2 * sizeof( float ) >()( buffer, __FVF_Flag_Traits< FVF_XYZ, Flag >::Has_Category() )
					);
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���Rhw
			 * 
			 * @return Rhw������������
			 */
			/* ----------------------------------------------------------------------------*/
			float & RhW()
			{
				return *reinterpret_cast< float * >(
					__FVF_FindValue< FVF_XYZRHW, Flag, 3 * sizeof( float ) >()( buffer )
					);
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���Rhw
			 * 
			 * @return Rhw������������
			 */
			/* ----------------------------------------------------------------------------*/
			const float & RhW() const
			{
				return *reinterpret_cast< float * >(
					__FVF_FindValue< FVF_XYZRHW, Flag, 3 * sizeof( float ) >()( buffer )
					);
			}
			float & PSize()
			{
				return *reinterpret_cast< float * >(
					__FVF_FindValue< FVF_PSIZE, Flag >()( buffer )
					);
			}
			const float & PSize() const
			{
				return *reinterpret_cast< float * >(
					__FVF_FindValue< FVF_PSIZE, Flag >()( buffer )
					);
			}
			COLOR & Diffuse()
			{
				return *reinterpret_cast< COLOR * >(
					__FVF_FindValue< FVF_DIFFUSE, Flag >()( buffer )
					);
			}
			const COLOR & Diffuse() const
			{
				return *reinterpret_cast< COLOR * >(
					__FVF_FindValue< FVF_DIFFUSE, Flag >()( buffer )
					);
			}

			COLOR & Specular()
			{
				return *reinterpret_cast< COLOR * >(
					__FVF_FindValue< FVF_SPECULAR, Flag >()( buffer )
					);
			}
			const COLOR & Specular() const
			{
				return *reinterpret_cast< COLOR * >(
					__FVF_FindValue< FVF_SPECULAR, Flag >()( buffer )
					);
			}

			template< int index >
			float & U()
			{
				return *reinterpret_cast< float * >(
					__FVF_FindValue< FVF_TEX, Flag, index * 2 >()( buffer ) );
			}
			template< int index >
			const float & U() const
			{
				return *reinterpret_cast< float * >(
					__FVF_FindValue< FVF_TEX, Flag, index * 2 >()( buffer ) );
			}
			template< int index >
			float & V()
			{
				return *reinterpret_cast< float * >(
					__FVF_FindValue< FVF_TEX, Flag, index * 2 + 1 >()( buffer ) );
			}
			template< int index >
			const float & V() const
			{
				return *reinterpret_cast< float * >(
					__FVF_FindValue< FVF_TEX, Flag, index * 2 + 1 >()( buffer ) );
			}

			//��ݺ���
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����3Dλ��
			 * 
			 * @param x �µ�X����
			 * @param y �µ�Y����
			 * @param z �µ�Z����
			 */
			/* ----------------------------------------------------------------------------*/
			void SetPos( float x, float y, float z )
			{
				X() = x; Y() = y; Z() = z;
			}

			//��ݺ���
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����2Dλ��
			 * 
			 * @param x �µ�X����
			 * @param y �µ�Y����
			 */
			/* ----------------------------------------------------------------------------*/
			void SetPos( float x, float y )
			{
				X() = x; Y() = y;
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����UV����
			 * 
			 * @tparam index ����������
			 * @param u �µ�U����
			 * @param v �µ�V����
			 */
			/* ----------------------------------------------------------------------------*/
			template< int index >
			void SetUV( const float u, const float v )
			{
				U< index >() = u;
				V< index >() = v;
			}
		};
	}
}
