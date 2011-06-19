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
* @file Texture.h
* @brief ���������
* Ŀǰֻ�л����������������
* @author Ladace
* @version 1.0.0.1
* @date 2010-07-09
*/
//CreateFromSurface���ڷ���������
//����D3D��û�еĹ��� ����UpdateSurface��ʵ��
//��UpdateSurface����������Σ��޷�ȥ����������ҲΥ����UpdateSurface�����ı��⡣
#pragma once

#include "Surface.h"

namespace OneU
{
	namespace DX
	{

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �������
		 *
		 * �����е�DirectX���÷�װ������������ ��Ϊ���ֱ����ṩһ�����ࡣ
		 * ��Щ��û�ж�̬�ԣ��ӿڲ�ͬ������Ϊ��ʵ��DirectX�ı����ڼ�顣
		 * ��2D�����У���ֻ��ʹ��IDirect3DTexture9�����Թ�����ˡ�
		 * ����չ��3D�������ع���
		 */
		/* ----------------------------------------------------------------------------*/
		class ONEU_DXGRAPHICS_API Texture_Base
		{
		private:
			//���ÿ������캯���͸�ֵ����
			Texture_Base( Texture_Base & ){}
			Texture_Base & operator=( Texture_Base & ){ return ( * this ); }

			IDirect3DTexture9 * m_pTexture;

#ifdef __ONEU_USE_CLASS_NUM
			static int s_Num;
			static void IncClassNum(){ s_Num++; }
			static void DecClassNum(){ s_Num--; }
		public:
			static int GetClassNum(){ return s_Num;  }
#endif

		protected:
			//����
			void _Create( uint32 nWidth, uint32 nHeight, PXLFORMAT Format, uint32 Level, uint32 Usage, D3DPOOL Pool )
			{
				ONEU_ASSERT( m_pTexture == NULL );
				DXCHECK_RAISE(
					_pD3DDevice->CreateTexture( nWidth, nHeight, Level, Usage, static_cast< D3DFORMAT >( Format ), Pool, &m_pTexture, NULL ),
					L"������ʧ�ܣ�"
					);
			}
			
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �ӱ��洴�������÷�����Ϊ����Ⱦ�����ʹ�á�
			 *
			 * ֻ�ܴ���LevelΪ1������
			 * �ӱ��洴���������������;
			 * ���LevelΪ1 ��Ϊ���ñ������Ⱦ
			 *
			 * ʵ�����ڲ�������UpdateSurface�����������������һ������Σ�ʹ�������ڲ�������״̬�޷������
			 * ��˴�ʵ����һ��������ʵ�֡�
			 *
			 * @param Surface ����
			 * @param Usage ʹ�÷�ʽ
			 * @param Pool �ڴ��
			 */
			/* ----------------------------------------------------------------------------*/
			void CreateFromSurface( const Surface_Base & Surface, uint32 Usage, D3DPOOL Pool )
			{
				Surface_Base::INFO info = Surface.GetInfo();
				_Create( Surface.GetWidth( info ), Surface.GetHeight( info ), Surface.GetFormat( info ), 1, Usage, Pool );
				Surface_Texture_Base(_GetSurfaceLevel( 0 )).UpdateSurface( NULL, &Surface, NULL );
			}

			IDirect3DSurface9* _GetSurfaceLevel( uint32 Level ) const
			{
				IDirect3DSurface9* pSurface;
				DXCHECK_RAISE(
					m_pTexture->GetSurfaceLevel( Level, &pSurface ),
					L"��ȡ�������ʧ�ܣ�"
					);
				return pSurface;
			}
			//const IDirect3DSurface9* _GetSurfaceLevel( uint Level ) const
			//{
			//	IDirect3DSurface9* pSurface;
			//	DXCHECK_ST(
			//		m_pTexture->GetSurfaceLevel( Level, &pSurface ),
			//		L"��ȡ�������ʧ�ܣ�"
			//		);
			//	return pSurface;
			//}
		public:
			typedef D3DSURFACE_DESC INFO;
			Texture_Base()
				: m_pTexture( NULL )
			{
#ifdef __ONEU_USE_CLASS_NUM
				IncClassNum();
#endif
				//��֤���캯����˳��
				GetGraphics();
				//�������캯���͸�ֵ��������Ҫ ��Ϊ��������Texture����Graphics��Ȼ����
			}
			//@internal
			explicit Texture_Base( IDirect3DTexture9* pTexture )
				: m_pTexture( pTexture )
			{
#ifdef __ONEU_USE_CLASS_NUM
				IncClassNum();
#endif
			}
			~Texture_Base()
			{
#ifdef __ONEU_USE_CLASS_NUM
				DecClassNum();
#endif
				Destroy();
			}
			IDirect3DTexture9 * _Obtain() const { return m_pTexture; }

			void _Create( IDirect3DTexture9 * pTexture )
			{
				ONEU_ASSERT( m_pTexture == NULL );
				m_pTexture = pTexture;
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �ͷ�����
			 */
			/* ----------------------------------------------------------------------------*/
			void Destroy()
			{
				SAFE_RELEASE( m_pTexture );
			}

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief �ж������Ƿ񱻴���
			 *
			 * @return true�����Ѵ�����false����δ���������ͷš�
			 */
			/* ----------------------------------------------------------------------------*/
			bool IsCreated() const { return m_pTexture != 0; }


			D3DSURFACE_DESC & _GetDesc( uint32 Level ) const
			{
				static D3DSURFACE_DESC s_SD = {};
				DXCHECK( m_pTexture->GetLevelDesc( Level, &s_SD ), L"��ȡ���������Ϣʧ��" );
				return s_SD;
			}

			INFO& GetInfo( uint32 Level ) const
			{
				return _GetDesc( Level );
			}
			uint32 GetWidth( const INFO& Info ) const
			{
				return Info.Width;
			}
			uint32 GetWidth( uint32 Level ) const
			{
				return GetWidth( GetInfo( Level ) );
			}
			uint32 GetHeight( const INFO& Info ) const
			{
				return Info.Height;
			}
			uint32 GetHeight( uint32 Level ) const
			{
				return GetHeight( GetInfo( Level ) );
			}
			PXLFORMAT GetFormat( const INFO& Info ) const
			{
				return static_cast< PXLFORMAT > ( Info.Format );
			}
			PXLFORMAT GetFormat( uint32 Level ) const
			{
				return GetFormat( GetInfo( Level ) );
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �������������β���
			 *
			 * ��������Ÿ��ֲ���������¼�������������������������β��֡�
			 * ����DX���ù��ܡ��ɲο�DirectX�ֲ�UpdateTexture��
			 * Ŀǰ����εļ�¼�������¡�
			 * UpdateSurface��Ŀ����¼����Ρ�
			 * Lockû��ʹ��READONLY���¼����Ρ�
			 * 
			 * @param pSrcTexture Դ����
			 */
			/* ----------------------------------------------------------------------------*/
			void UpdateTexture( const Texture_Base * pSrcTexture )
			{
				DXCHECK( _pD3DDevice->UpdateTexture( pSrcTexture->_Obtain(), m_pTexture ), L"��������ʧ��" );
			}

		};


		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ������
		 *
		 * ���ϱ���������������
		 * @tparam _Usage ʹ������
		 * @tparam _Pool �ڴ������
		 */
		/* ----------------------------------------------------------------------------*/
		template< uint32 _Usage, D3DPOOL _Pool >
		class Texture_t
			: public Texture_Base
		{
		private:
			template< uint32 Usage, D3DPOOL Pool >
			void _UpdateTexture( Texture_t< Usage, Pool >* pSrcTexture, __True_Category )
			{
				Texture_Base::UpdateTexture( pSrcTexture );
			}
		public:
			enum { Usage = _Usage, Pool = _Pool };
			typedef Surface_Texture< _Usage, _Pool > SurfaceType;
			void Create( uint32 nWidth, uint32 nHeight, PXLFORMAT Format, uint32 Level = 1 )
			{
				_Create( nWidth, nHeight, Format, Level, _Usage, _Pool );
			}

			template< uint32 Usage, D3DPOOL Pool >
			void UpdateTexture( const Texture_t< Usage, Pool >* pSrcTexture )
			{
				_UpdateTexture( pSrcTexture, __Bool_Category< _Pool == D3DPOOL_DEFAULT && Pool == D3DPOOL_SYSTEMMEM >::Category );
			}
			//��������ʹ�� �ú�������Ϊ�����ñ����ܹ�����Ⱦ
			//��Ϊ�����е�����UpdateSurface�������������������һ������Ρ�			
			//CreateFromSurface2���� ��UpdateSurface�н������ͼ��
			/*@name �ӱ��洴������ */
			/*@{ */
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �ӱ��洴�������÷�����Ϊ����Ⱦ�����ʹ�á�
			 *
			 * ֻ�ܴ���LevelΪ1������
			 * �ӱ��洴���������������;
			 * ���LevelΪ1 ��Ϊ���ñ������Ⱦ
			 *
			 * ʵ�����ڲ�������UpdateSurface�����������������һ������Σ�ʹ�������ڲ�������״̬�޷������
			 * ��˴�ʵ����һ��������ʵ�֡�
			 *
			 * @param Surface ����
			 */
			/* ----------------------------------------------------------------------------*/
			template< class T >
			void CreateFromSurface( const T & Surface )
			{
				typename T::INFO info = Surface.GetInfo();
				Create( Surface.GetWidth( info ), Surface.GetHeight( info ), Surface.GetFormat( info ), 1 );//���Level��Ϊ1�追���ܶ�� ����Ϊ�˷�ֹǱ�ڵ�Ч��Ӱ�죨���û���֪������£� �������Levelֻ��Ϊ1
				GetSurfaceLevel( 0 ).UpdateSurface( NULL, &Surface, NULL );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �ӱ��洴�������÷�����Ϊ����Ⱦ�����ʹ�á�
			 *
			 * ֻ�ܴ���LevelΪ1������
			 * �ӱ��洴���������������;
			 * ���LevelΪ1 ��Ϊ���ñ������Ⱦ
			 *
			 * ʵ�����ڲ�������UpdateSurface�����������������һ������Σ�ʹ�������ڲ�������״̬�޷������
			 * ��˴�ʵ����һ��������ʵ�֡�
			 *
			 * @param Surface ����
			 */
			/* ----------------------------------------------------------------------------*/
			void CreateFromSurface( const Surface_Base & Surface )
			{
				Texture_Base::CreateFromSurface( Surface, _Usage, _Pool );
			}
			/** @} */


			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ�������
			 * 
			 * @param Level ���漶��
			 *
			 * ���Level���������������������������׳�����
			 * 
			 * @return ����ĵ�Level������
			 */
			/* ----------------------------------------------------------------------------*/
			SurfaceType GetSurfaceLevel( uint32 Level )
			{
				return Surface_Texture< _Usage, _Pool > ( _GetSurfaceLevel( Level ) );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ�������
			 * 
			 * @param Level ���漶��
			 *
			 * ���Level���������������������������׳�����
			 * 
			 * @return ����ĵ�Level������
			 */
			/* ----------------------------------------------------------------------------*/
			const SurfaceType GetSurfaceLevel( uint32 Level ) const
			{
				return Surface_Texture< _Usage, _Pool > (_GetSurfaceLevel( Level ));
			}
		};
	}
}
