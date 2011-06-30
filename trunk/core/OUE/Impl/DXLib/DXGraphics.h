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
 * @file DXGraphics.h
 * @brief ͼ�ζ���
 *
 * �ӿں�ʵ�־�Ϊ���󱸻����ģʽ
 *
 * ��ϵ���ӿ�GetRenderTarget SetRenderTarget
 *
 * @author Ladace
 * @version 1.0.0.1
 * @date 2010-01-22
 */
#pragma once

#include "D3DDefs.h"

#include <d3d9.h>

#define __ONEU_DIRECT3D_VERSION DIRECT3D_VERSION
#include "PixelFormat.h"


namespace OneU
{
	namespace DX
	{
		class Surface;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ʾģʽ
		 */
		/* ----------------------------------------------------------------------------*/
		struct DisplayMode
		{
			uint32 Width;
			uint32 Height;
			uint32 RefreshRate;
			PXLFORMAT Format;
		};

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief D3D��������
		 * @internal
		 */
		/* ----------------------------------------------------------------------------*/
		extern IDirect3D9 * _pD3D;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief D3D�����豸����
		 * @internal
		 */
		/* ----------------------------------------------------------------------------*/
		extern IDirect3DDevice9 * _pD3DDevice;

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���ڻ���־
		 */
		/* ----------------------------------------------------------------------------*/
		extern bool _Windowed;


		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ͼ�ζ���
		 */
		/* ----------------------------------------------------------------------------*/
		class  Graphics_t
		{
		public:
			static Graphics_t* GetInstance();
		private:
			uint32 m_Width, m_Height;
			Graphics_t( const Graphics_t& );
			Graphics_t& operator=( const Graphics_t& );
			Graphics_t()
				: m_Width( 0 ), m_Height( 0 )
			{
				ONEU_ASSERT( _pD3D == NULL );
			}
			//һ�㲻��Ҫ�û�����
			//�ͷ��ڲ�������Դ���Դ���ڶ�ʧ�豸��������豸ǰ���á�
			void OnLostDevice();
			//�����ڲ�����
			//���豸���ú���á�
			void OnResetDevice();
		public:

			~Graphics_t()
			{
				Destroy();
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �ͷ���Դ
			 */
			/* ----------------------------------------------------------------------------*/
			void Destroy();

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ʼ��Ԥ����
			 *
			 * �ڳ�ʼ��֮ǰ����
			 * ��Ҫ������׼�����Ӳ��
			 */
			/* ----------------------------------------------------------------------------*/
			void PreInit();
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���ڻ���ʼ��
			 * 
			 * @param nWidth ���ڿ��
			 *
			 * �غ����󱸻�����
			 * @param nHeight ���ڸ߶�
			 *
			 * �غ����󱸻���߶�
			 * @param hWnd ���ھ��
			 */
			/* ----------------------------------------------------------------------------*/
			void InitWindowed( uint32 nWidth, uint32 nHeight, HWND hWnd );
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ȫ����ʼ��
			 * 
			 * ��ʼ��֮ǰӦ����SetDisplayMode���ú���ʾ��ʽ
			 *
			 * @param pDM ��ʾģʽ
			 * @param hWnd ���ھ��
			 *
			 * @sa SetDisplayMode
			 */
			/* ----------------------------------------------------------------------------*/
			void InitFullScreen( const DisplayMode *pDM, HWND hWnd );
			void _InitWithPtr(IDirect3D9* pD3D, IDirect3DDevice9* pDevice, uint32 Width, uint32 Height);

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ����Ϊ����ģʽ
			 *
			 * �ı䴰��ģʽ��ȫ��ģʽʹ�á�
			 * ����Reset�򻯰汾��
			 * @attention �����趨������޷����������øú�������Ҫ�����趨��
			 */
			/* ----------------------------------------------------------------------------*/
			void ResetWindowed( uint32 nWidth, uint32 nHeight, HWND hWnd );
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ����Ϊȫ��ģʽ
			 *
			 * �ı䴰��ģʽ��ȫ��ģʽʹ�á�
			 * ����Reset�򻯰汾��
			 * @attention �����趨������޷����������øú�������Ҫ�����趨��
			 */
			/* ----------------------------------------------------------------------------*/
			void ResetFullScreen( const DisplayMode *pDM, HWND hWnd );

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ����豸���
			 * @return ��ȣ������ؼơ�
			 */
			/* ----------------------------------------------------------------------------*/
			uint32 GetWidth() const
			{
				return m_Width;
			}
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ����豸�߶�
			 * @return �߶ȣ������ؼơ�
			 */
			/* ----------------------------------------------------------------------------*/
			uint32 GetHeight() const
			{
				return m_Height;
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ʼ������
			 *
			 * ��һЩ����Ϊ2D��Ϊ��ʼֵ
			 * ��InitWindowed��InitFullScreen����
			 *
			 * @sa InitWindowed InitFullScreen
			 */
			/* ----------------------------------------------------------------------------*/
			void InitParameters();
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���ҳ�������ɫ
			 * 
			 * @param crColor 32λ��ɫֵ
			 */
			/* ----------------------------------------------------------------------------*/
			void ClearTarget( COLOR crColor = 0 )
			{
				HRESULT hr;
				if( FAILED( hr = _pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, crColor, 0.0f, 0 ) ) )
					ONEU_LOG_DXERR( hr );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ҳ����
			 */
			/* ----------------------------------------------------------------------------*/
			void Present()
			{
				HRESULT hr;
				if( FAILED( hr = _pD3DDevice->Present( NULL, NULL, NULL, NULL ) ) )
					RAISE_HRESULT(hr);
			}

#ifdef ONEU_USE_GRAPHICS_3D
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��������任����
			 * 
			 * @param pMatrix �����ֵ
			 * @param Level �����õ�����任���󼶱�
			 *
			 * ÿ������ľ���Ĭ��Ϊ��λ����
			 * ��Ⱦʱ�������ռ���˳�����������Ϊ����ı任���󡣼������Ϊ��0����˳�����任��
			 */
			/* ----------------------------------------------------------------------------*/
			void SetWorldTransform( const MATRIX * pMatrix, BYTE Level = 0 )
			{
				DXCHECK_DEBUG( _pD3DDevice->SetTransform( D3DTS_WORLDMATRIX( Level ), pMatrix ), L"�����������ʧ�ܣ�" );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �����Ӵ��任����
			 * 
			 * @param pMatrix �����ֵ
			 */
			/* ----------------------------------------------------------------------------*/
			void SetViewTransform( const MATRIX * pMatrix )
			{
				XV_DEBUG( _pD3DDevice->SetTransform( D3DTS_VIEW, pMatrix ) );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����ͶӰ�任����
			 * 
			 * @param pMatrix �����ֵ
			 */
			/* ----------------------------------------------------------------------------*/
			void SetProjectionTransform( const MATRIX * pMatrix )
			{
				XV_DEBUG( _pD3DDevice->SetTransform( D3DTS_PROJECTION, pMatrix ) );
			}
#endif
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ������Ⱦ�ö����־λ
			 * 
			 * @param FVF_Flag �����־���
			 */
			/* ----------------------------------------------------------------------------*/
			void SetFVF( uint32 FVF_Flag )
			{
				DXCHECK_DEBUG( _pD3DDevice->SetFVF( FVF_Flag ), L"FVF����ʧ�ܣ�" );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ������Ⱦ�ö����־λ
			 * 
			 * @tparam ��������
			 */
			/* ----------------------------------------------------------------------------*/
			template< class VertexType >
			void SetFVF( VertexType * )
			{
				SetFVF( VertexType::Flag );
			}

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ������������Ⱦ����
			 *
			 * @param Mode ����
			 *
			 * 0��ʾȫ����Ⱦ��
			 * 1��ʾ����˳ʱ���棬��ʱ�붥��˳�����ᱻ��Ⱦ��
			 * -1��ʾ������ʱ���棬˳ʱ��˳����汻��Ⱦ��
			 * �������ֵĽ������Ԥ֪��
			 */
			/* ----------------------------------------------------------------------------*/
			void SetCullMode( int Mode )
			{
				_pD3DDevice->SetRenderState( D3DRS_CULLMODE, Mode == 0 ? D3DCULL_NONE : Mode == 1 ? D3DCULL_CW : D3DCULL_CCW );
			}

			//�����ʾ��ʽ
#define __ONEU_DISPLAYMODE_COUNT_INDEX //Ϊ����count ͨ��indexö��ģʽ
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���ָ�����ظ�ʽ����ʾ��ʽ��Ŀ
			 * 
			 * @param Format ���ظ�ʽ
			 * 
			 * @return ��ʾ��ʽ��Ŀ
			 *
			 * @sa GetAvailableDisplayMode
			 */
			/* ----------------------------------------------------------------------------*/
			uint32 GetAvailableDisplayCount( PXLFORMAT Format ){ return _pD3D->GetAdapterModeCount( D3DADAPTER_DEFAULT, static_cast< D3DFORMAT > ( Format ) ); }
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �����ʾ��ʽ
			 * 
			 * @param Format ��ʾ��ʽ�����ظ�ʽ
			 * @param index ��ʾ��ʽ������
			 * 
			 * @return ָ����ʾ��ʽ�ṹ���ָ��
			 *
			 * @sa GetAvailableDisplayCount
			 */
			/* ----------------------------------------------------------------------------*/
			DisplayMode *GetAvailableDisplayMode( PXLFORMAT Format, int index );

#define __ONEU_DISPLAYMODE_CHECK //�ɼ����ʾģʽ
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �����ʾ��ʽ�Ƿ����
			 * 
			 * @param pDM ��ʾ��ʽ�ṹ��
			 * @param Windowed ���ڻ���־λ
			 * 
			 * @return ����ΪTRUE������ΪFALSE
			 */
			/* ----------------------------------------------------------------------------*/
			bool CheckDisplayMode( const DisplayMode * pDM, bool Windowed )
			{
				if( _pD3D->CheckDeviceType( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, static_cast< const D3DFORMAT >( pDM->Format ), static_cast< const D3DFORMAT >( pDM->Format ), Windowed ) == D3D_OK )
					return TRUE;
				return FALSE;
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ�󱸻���ҳ�棨��ǰ��Ⱦ����ҳ�棩
			 * 
			 * @returns ��Ⱦ����ҳ�����
			 */
			/* ----------------------------------------------------------------------------*/
			Surface GetRenderTarget() const;
			void SetRenderTarget( Surface &RenderTarget );

			//����
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����
			 * 
			 * @param dwSeconds ����ʱ��
			 * 
			 * @internal
			 */
			/* ----------------------------------------------------------------------------*/
			void Test( uint32 dwSeconds );
		};

		//��Ⱦ�ṹ
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��Ⱦ�ṹ��
		 *
		 * ����Ҫ��Ⱦ��ʱ��ʵ���������Ժ󱸻��������ʵ������ʱ�Զ�������Ⱦ��
		 */
		/* ----------------------------------------------------------------------------*/
		class  RenderManip
		{
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��Ⱦͼ������
			 */
			/* ----------------------------------------------------------------------------*/
			enum PRIMITIVETYPE{
				PT_POINTLIST = D3DPT_POINTLIST,
				PT_LINELIST = D3DPT_LINELIST,
				PT_LINESTRIP = D3DPT_LINESTRIP,
				PT_TRIANGLELIST = D3DPT_TRIANGLELIST,
				PT_TRIANGLEFAN = D3DPT_TRIANGLEFAN,
				PT_FORCE_DWORD = D3DPT_FORCE_DWORD
			};
			RenderManip()
			{
				HRESULT hr;
				if( FAILED( hr = _pD3DDevice->BeginScene() ) )
				{
					ONEU_LOG( L"��Ⱦ��ʼ��ʧ�ܣ�" );
					RAISE_HRESULT(hr);
				}
			}
			~RenderManip()
			{
				HRESULT hr;
				if( FAILED( hr = _pD3DDevice->EndScene() ) )
					ONEU_LOG( L"��Ⱦ����ʧ�ܣ�" );
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��Ⱦ�û��Զ��嶥��
			 * 
			 * @param PrimitiveType ��Ⱦ��������
			 * @param pVertex ��������
			 * @param nElem ������Ŀ
			 */
			/* ----------------------------------------------------------------------------*/
			template< class VertexType >
			void RenderVertexUP( PRIMITIVETYPE PrimitiveType, VertexType * pVertex, int nElem )
			{
				XV_DEBUG( _pD3DDevice->DrawPrimitiveUP( static_cast< D3DPRIMITIVETYPE > ( PrimitiveType ), nElem, pVertex, sizeof( VertexType ) ) );
			}
		};//class Graphics_t

		inline Graphics_t* GetGraphics()
		{
			return Graphics_t::GetInstance();
		}
	}
}
