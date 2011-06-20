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

#include "D3DDefs.h"
#include "DXGraphics.h"

#include < dxerr.h >

namespace OneU
{
	namespace DX
	{
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���������
		 *
		 * �����е�DirectX���÷�װ������������ ��Ϊ���ֱ����ṩһ�����ࡣ
		 * ��Щ��û�ж�̬�ԣ��ӿڲ�ͬ������Ϊ��ʵ��DirectX�ı����ڼ�顣
		 *
		 */
		/* ----------------------------------------------------------------------------*/
		class Surface
		{
		private:
		
			IDirect3DSurface9 * m_pSurface;
		protected:
			void _Create( uint32 nWidth, uint32 nHeight, PXLFORMAT Format, D3DPOOL Pool )
			{
				ONEU_ASSERT( m_pSurface == NULL );
				DXCHECK_RAISE( _pD3DDevice->CreateOffscreenPlainSurface( nWidth, nHeight, static_cast< D3DFORMAT > ( Format ), Pool, &m_pSurface, NULL ),
					L"���洴��ʧ�ܣ�" );
			}
			void _CreateRenderTarget( uint32 nWidth, uint32 nHeight, PXLFORMAT Format, uint32 MultiSample, uint32 MultisampleQuality, bool Lockable )
			{
				ONEU_ASSERT( m_pSurface == NULL );
				DXCHECK_RAISE(
					_pD3DDevice->CreateRenderTarget( nWidth, nHeight, static_cast< D3DFORMAT > ( Format ),
					static_cast< D3DMULTISAMPLE_TYPE > ( MultiSample ), MultisampleQuality, Lockable, &m_pSurface, NULL ),
					L"��ȾĿ����洴��ʧ�ܣ�" );
			}
			void _CreateDepthSurface( uint32 nWidth, uint32 nHeight, PXLFORMAT Format, uint32 MultiSample, uint32 MultisampleQuality, bool Discard )
			{
				ONEU_ASSERT( m_pSurface == NULL );
				DXCHECK_RAISE(
					_pD3DDevice->CreateDepthStencilSurface( nWidth, nHeight, static_cast< D3DFORMAT > ( Format ),
					static_cast< D3DMULTISAMPLE_TYPE > ( MultiSample ), MultisampleQuality, Discard, &m_pSurface, NULL ),
					L"��ȱ��洴��ʧ�ܣ�" );
			}
		public:
			typedef D3DSURFACE_DESC INFO;

			Surface()
				: m_pSurface( NULL )
			{
				//��֤���캯����˳��
				GetGraphics();
				//�������캯���͸�ֵ��������Ҫ ��Ϊ��������Surface����Graphics��Ȼ����
			}
			explicit Surface( IDirect3DSurface9 * pSurface )
				: m_pSurface( pSurface )
			{
			}
			Surface( Surface & rhs )
				: m_pSurface( rhs.m_pSurface )
			{
				rhs.m_pSurface = NULL;
			}
			Surface & operator = ( Surface & rhs )
			{
				ONEU_ASSERT( !m_pSurface );
					m_pSurface = rhs.m_pSurface;
				rhs.m_pSurface = NULL;
				return ( * this );
			}
			~Surface()
			{
				Destroy();
			}
		
			IDirect3DSurface9 * _Obtain() const { return m_pSurface; }
			D3DSURFACE_DESC & _GetDesc() const
			{
				static D3DSURFACE_DESC s_SD = {};
				DXCHECK( m_pSurface->GetDesc( &s_SD ), L"��ȡ������Ϣʧ��" );
					return s_SD;
			}

			void Create( uint32 nWidth, uint32 nHeight, PXLFORMAT Format )
			{
				_Create( nWidth, nHeight, Format, D3DPOOL_DEFAULT );
			}
			void Destroy()
			{
				SAFE_RELEASE( m_pSurface );
			}
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief �жϱ����Ƿ񱻴���
			 *
			 * @return true�����Ѵ�����false����δ���������ͷš�
			 */
			/* ----------------------------------------------------------------------------*/
			bool IsCreated() const { return m_pSurface != 0; }
		
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ������Ϣ���
			 *
			 * ��Ҫ��ȡ���������Ϣ��ʱ���Ȼ�ô˾����
			 * �ٽ��˾�������ȡ��Ϣ�������һЩ���μ�GetWidth��GetHeight��
			 * 
			 * @return ��Ϣ���
			 *
			 * @sa GetWidth GetHeight
			 */
			/* ----------------------------------------------------------------------------*/
			//������Ϣ���
			const INFO& GetInfo() const
			{
				return _GetDesc();
			}
		
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ���
			 *
			 * ��ȡ����Ŀ�ȣ������ؼơ�
			 * 
			 * @param Info ������Ϣ���
			 *
			 * �����GetInfo��Ա������á�
			 * 
			 * @return �����ȣ������ؼơ�
			 *
			 * @sa GetInfo
			 */
			/* ----------------------------------------------------------------------------*/
			//��ȡ������Ϣ
			uint32 GetWidth( const INFO& Info ) const
			{
				return Info.Width;
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ���
			 *
			 * ��ȡ����Ŀ�ȣ������ؼơ�
			 * �����һ��ʹ�ö����ȡ��Ϣ�����Ļ���
			 * ��ʹ��GetInfo��
			 * 
			 * @return �����ȣ������ؼơ�
			 *
			 * @sa GetInfo
			 */
			/* ----------------------------------------------------------------------------*/
			uint32 GetWidth() const
			{
				return GetWidth( GetInfo() );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ�߶�
			 *
			 * ��ȡ����ĸ߶ȣ������ؼơ�
			 * 
			 * @param Info ������Ϣ���
			 *
			 * �����GetInfo��Ա������á�
			 * 
			 * @return ����߶ȣ������ؼơ�
			 *
			 * @sa GetInfo
			 */
			/* ----------------------------------------------------------------------------*/
			uint32 GetHeight( const INFO& Info ) const
			{
				return Info.Height;
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ�߶�
			 *
			 * ��ȡ����ĸ߶ȣ������ؼơ�
			 * �����һ��ʹ�ö����ȡ��Ϣ�����Ļ���
			 * ��ʹ��GetInfo��
			 * 
			 * @return ����߶ȣ������ؼơ�
			 *
			 * @sa GetInfo
			 */
			/* ----------------------------------------------------------------------------*/
			uint32 GetHeight() const
			{
				return GetHeight( GetInfo() );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ���ظ�ʽ
			 *
			 * ��ȡ��������ظ�ʽ��
			 * 
			 * @param Info ������Ϣ���
			 *
			 * �����GetInfo��Ա������á�
			 * 
			 * @return �����ʽ
			 *
			 * @sa GetInfo
			 */
			/* ----------------------------------------------------------------------------*/
			PXLFORMAT GetFormat( const INFO& Info ) const
			{
				return static_cast< PXLFORMAT > ( Info.Format );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ���ظ�ʽ
			 *
			 * ��ȡ��������ظ�ʽ��
			 * �����һ��ʹ�ö����ȡ��Ϣ�����Ļ���
			 * ��ʹ��GetInfo��
			 * 
			 * @return �����ʽ
			 *
			 * @sa GetInfo
			 */
			/* ----------------------------------------------------------------------------*/
			PXLFORMAT GetFormat() const
			{
				return GetFormat( GetInfo() );
			}
		
			//�����ǻᱻ�̳����ڸǵ��ĺ���
			//û�о�̬����DXAPI����
			void UpdateSurface( POINT * pDtnPoint, const Surface * pSrcSurface, RECT * pSrcRect )
			{
				DXCHECK( _pD3DDevice->UpdateSurface( pSrcSurface->m_pSurface, pSrcRect, m_pSurface, pDtnPoint ),
					L"��������ʧ�ܣ�" );
			}
			void StretchRect( RECT * pDtnRect, const Surface * pSrcSurface, RECT * pSrcRect )
			{
				DXCHECK( _pD3DDevice->StretchRect( pSrcSurface->m_pSurface, pSrcRect, m_pSurface, pDtnRect, _TexFilter ),
					L"���޷�������������ʧ�ܣ�" );
			}
			void ColorFill( COLOR crColor, RECT * pRect = NULL )
			{
				HRESULT hr = _pD3DDevice->ColorFill( m_pSurface, pRect, crColor );
				if( FAILED( hr ) )
				{
					ONEU_LOG( L"������ʧ�ܣ�");
					ONEU_LOG_DXERR( hr );
				}
			}
			//RenderTarget Surfaceר��
			void GetData( Surface * pDestSurface )
			{
				DXCHECK( _pD3DDevice->GetRenderTargetData( m_pSurface, pDestSurface->_Obtain() ), L"��ȡ��ȾĿ���������ʧ�ܣ�" );
			}
		};

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
		class Texture
		{
		private:
			//���ÿ������캯���͸�ֵ����
			Texture( Texture & ){}
			Texture & operator=( Texture & ){ return ( * this ); }

			IDirect3DTexture9 * m_pTexture;

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
			void CreateFromSurface( const Surface& surface, uint32 Usage, D3DPOOL Pool )
			{
				Surface::INFO info = surface.GetInfo();
				_Create( surface.GetWidth( info ), surface.GetHeight( info ), surface.GetFormat( info ), 1, Usage, Pool );
				Surface(_GetSurfaceLevel( 0 )).UpdateSurface( NULL, &surface, NULL );
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
		public:
			typedef D3DSURFACE_DESC INFO;
			Texture()
				: m_pTexture( NULL )
			{
				//��֤���캯����˳��
				GetGraphics();
				//�������캯���͸�ֵ��������Ҫ ��Ϊ��������Texture����Graphics��Ȼ����
			}
			//@internal
			explicit Texture( IDirect3DTexture9* pTexture )
				: m_pTexture( pTexture )
			{
			}
			~Texture()
			{
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
			void UpdateTexture( const Texture * pSrcTexture )
			{
				DXCHECK( _pD3DDevice->UpdateTexture( pSrcTexture->_Obtain(), m_pTexture ), L"��������ʧ��" );
			}

		};
	}
}
