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
#pragma once
#include "STDef.h"
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
		class ONEU_DXGRAPHICS_API Surface_Base
		{
		private:
		
			IDirect3DSurface9 * m_pSurface;

#ifdef __ONEU_USE_CLASS_NUM

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �������ʵ����Ŀ
			 */
			/* ----------------------------------------------------------------------------*/
			static int s_Num;
			static void IncClassNum(){ s_Num++; }
			static void DecClassNum(){ s_Num--; }
		public:
			static int GetClassNum(){ return s_Num; }
#endif
		protected:
			void _Create( uint nWidth, uint nHeight, PXLFORMAT Format, D3DPOOL Pool )
			{
				ASSERT( m_pSurface == NULL );
				DXCHECK_THROW( _pD3DDevice->CreateOffscreenPlainSurface( nWidth, nHeight, static_cast< D3DFORMAT > ( Format ), Pool, &m_pSurface, NULL ),
					L"���洴��ʧ�ܣ�" );
			}
			void _CreateRenderTarget( uint nWidth, uint nHeight, PXLFORMAT Format, dword MultiSample, dword MultisampleQuality, bool Lockable )
			{
				ASSERT( m_pSurface == NULL );
				DXCHECK_THROW(
					_pD3DDevice->CreateRenderTarget( nWidth, nHeight, static_cast< D3DFORMAT > ( Format ),
					static_cast< D3DMULTISAMPLE_TYPE > ( MultiSample ), MultisampleQuality, Lockable, &m_pSurface, NULL ),
					L"��ȾĿ����洴��ʧ�ܣ�" );
			}
			void _CreateDepthSurface( uint nWidth, uint nHeight, PXLFORMAT Format, dword MultiSample, dword MultisampleQuality, bool Discard )
			{
				ASSERT( m_pSurface == NULL );
				DXCHECK_THROW(
					_pD3DDevice->CreateDepthStencilSurface( nWidth, nHeight, static_cast< D3DFORMAT > ( Format ),
					static_cast< D3DMULTISAMPLE_TYPE > ( MultiSample ), MultisampleQuality, Discard, &m_pSurface, NULL ),
					L"��ȱ��洴��ʧ�ܣ�" );
			}
		public:
			typedef D3DSURFACE_DESC INFO;

			Surface_Base()
				: m_pSurface( NULL )
			{
				//��֤���캯����˳��
				GetGraphics();
				//�������캯���͸�ֵ��������Ҫ ��Ϊ��������Surface����Graphics��Ȼ����
#ifdef __ONEU_USE_CLASS_NUM
				IncClassNum();
#endif
			}
			explicit Surface_Base( IDirect3DSurface9 * pSurface )
				: m_pSurface( pSurface )
			{
#ifdef __ONEU_USE_CLASS_NUM
				IncClassNum();
#endif
			}
			Surface_Base( Surface_Base & rhs )
				: m_pSurface( rhs.m_pSurface )
			{
#ifdef __ONEU_USE_CLASS_NUM
				IncClassNum();
#endif
				rhs.m_pSurface = NULL;
			}
			Surface_Base & operator = ( Surface_Base & rhs )
			{
				ASSERT( !m_pSurface );
					m_pSurface = rhs.m_pSurface;
				rhs.m_pSurface = NULL;
				return ( * this );
			}
			~Surface_Base()
			{
#ifdef __ONEU_USE_CLASS_NUM
				DecClassNum();
#endif
				Destroy();
			}
		
			IDirect3DSurface9 * _Obtain() const { return m_pSurface; }
			D3DSURFACE_DESC & _GetDesc() const
			{
				static D3DSURFACE_DESC s_SD = {};
				DXCHECK( m_pSurface->GetDesc( &s_SD ), L"��ȡ������Ϣʧ��" );
					return s_SD;
			}

			void Create( uint nWidth, uint nHeight, PXLFORMAT Format )
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
			uint GetWidth( const INFO& Info ) const
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
			uint GetWidth() const
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
			uint GetHeight( const INFO& Info ) const
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
			uint GetHeight() const
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
			void UpdateSurface( POINT * pDtnPoint, const Surface_Base * pSrcSurface, RECT * pSrcRect )
			{
				DXCHECK( _pD3DDevice->UpdateSurface( pSrcSurface->m_pSurface, pSrcRect, m_pSurface, pDtnPoint ),
					L"��������ʧ�ܣ�" );
			}
			void StretchRect( RECT * pDtnRect, const Surface_Base * pSrcSurface, RECT * pSrcRect )
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
			void GetData( Surface_Base * pDestSurface )
			{
				DXCHECK( _pD3DDevice->GetRenderTargetData( m_pSurface, pDestSurface->_Obtain() ), L"��ȡ��ȾĿ���������ʧ�ܣ�" );
			}
		};
		
		//ǰ������
		template< uint _Usage, D3DPOOL Pool >
		class Surface_Texture;
		
		//__Surface_Base��Wrapper
		//����Pool�ṩ�ӿ�
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ͨ����������
		 *
		 * ʹ��ʱ������Create����������
		 *
		 * @tparam _Pool�ڴ������
		 */
		/* ----------------------------------------------------------------------------*/
		template< D3DPOOL _Pool >
		class Surface_t
			: public Surface_Base
		{
		private:
			void _ColorFill( COLOR crColor, RECT *pRect, __True_Category )
			{
				Surface_Base::ColorFill( crColor, pRect );
			}
			void _UpdateSurface( POINT * pDtnPoint, const Surface_t< D3DPOOL_SYSTEMMEM > * pSrcSurface, RECT * pSrcRect, __True_Category )
			{
				Surface_Base::UpdateSurface( pDtnPoint, pSrcSurface, pSrcRect );
			}
			void _CopyRect( POINT * pDtnPoint, const Surface_t< D3DPOOL_DEFAULT > * pSrcSurface, RECT * pSrcRect, __True_Category )
			{
				RECT DtnRect = {
					pDtnPoint->x, pDtnPoint->y,
					pDtnPoint->x + pSrcRect->right-pSrcRect->left,
					pDtnPoint->y + pSrcRect->bottom - pSrcRect->top
				};
				Surface_Base::StretchRect( &DtnRect, pSrcSurface, pSrcRect );
			}
		public:
			enum{ Pool = _Pool };
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��������
			 *
			 * ÿ�������������Ҫͨ���÷��������������ʹ�á�
			 * 
			 * @param nWidth �����ȣ������ؼ�
			 * @param nHeight ����߶ȣ������ؼ�
			 * @param Format �������ظ�ʽ
			 */
			/* ----------------------------------------------------------------------------*/
			void Create( uint nWidth, uint nHeight, PXLFORMAT Format )
			{
				_Create( nWidth, nHeight, Format, _Pool );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �����ɫ
			 *
			 * ����������crColor����ɫ��
			 * 
			 * @param crColor ������ɫֵ
			 * @param pRect �����εĵ�ַ
			 *
			 * �������ΪNULL����������ᱻ��䡣
			 */
			/* ----------------------------------------------------------------------------*/
			void ColorFill( COLOR crColor, RECT *pRect = NULL )
			{
				_ColorFill( crColor, pRect, __Surface_Pool_Traits< _Pool >::ColorFill_Category );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���±���
			 *
			 * ����һ�����濽�����ݵ��ñ��档
			 * Դ����Pool���ͱ���ΪD3DPOOL_SYSTEMMEM��Surface_Lk����Ŀ�ı���Pool���ͱ���ΪD3DPOOL_DEFAULT��Surface����
			 * �������ʹ��ͬ�������ظ�ʽ��
			 * �Ҳ���ΪDepth Stencil Format��
			 * @todo�����ڣ���֪��ʲô���Ӧ�ò���Ҫ������㡣��Surface_Depth Surface_Stencil�����������������ظ�ʽ�ı��棩
			 *  
			 * @param pDtnPoint Ŀ�ı��棨�ñ��棩�������ľ��ε����Ͻǵ��ַ
			 *
			 * �������ΪNULL���������涼�ᱻ������
			 * @param pSrcSurface Դ����ĵ�ַ��
			 * @param pSrcRect Դ����ľ��ε�ַ
			 *
			 * �������ΪNULL���������涼�ᱻ������
			 */
			/* ----------------------------------------------------------------------------*/
			void UpdateSurface( POINT * pDtnPoint, const Surface_t< D3DPOOL_SYSTEMMEM > * pSrcSurface, RECT * pSrcRect )
			{
				_UpdateSurface( pDtnPoint, pSrcSurface, pSrcRect, __Surface_Pool_Traits< _Pool >::UpdateSurfaceDestination_Category );
			}
			//ͬ��
			template< uint Usage_, D3DPOOL Pool_ >
			void UpdateSurface( POINT * pDtnPoint, const Surface_Texture< Usage_, Pool_ > * pSrcSurface, RECT * pSrcRect )
			{
				_UpdateSurface( pDtnPoint, pSrcSurface, pSrcRect, __Texture_UgPl_Traits< Usage_, Pool_ >::UpdateSurfaceSource_Category );
			}
			//ͬ��
			void UpdateSurface( POINT * pDtnPoint, const Surface_t< D3DPOOL_DEFAULT > * pSrcSurface, RECT * pSrcRect )
			{
				_CopyRect( pDtnPoint, pSrcSurface, pSrcRect, __Surface_Pool_Traits< _Pool >::StretchRectDestination_Category );
			}
		
		};
		
		
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȾĿ�����
		 *
		 * �ɵ���Create�������档
		 * �ɵ���Graphics.GetRenderTarget��ú���ȾĿ����档
		 */
		/* ----------------------------------------------------------------------------*/
		class ONEU_DXGRAPHICS_API Surface_RenderTarget
			: public Surface_Base
		{
		private:
			void _UpdateSurface( POINT * pDtnPoint, const Surface_Base * pSrcSurface, RECT * pSrcRect, __True_Category )
			{
				Surface_Base::UpdateSurface( pDtnPoint, pSrcSurface, pSrcRect );
			}
		public:
			Surface_RenderTarget()
				: Surface_Base(){}
			Surface_RenderTarget( IDirect3DSurface9 * pRenderTarget )
				: Surface_Base( pRenderTarget ){}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ������ȾĿ�����
			 * 
			 * @param nWidth �����ȣ������ؼ�
			 * @param nHeight ����߶ȣ������ؼ�
			 * @param Format �������ظ�ʽ
			 * @param MultiSample ����������0ΪĬ�ϲ����ö��ز�����1Ϊʹ�ò�����������
			 * @param MultisampleQuality ��������
			 *
			 * �Ϸ�ֵ��0��CheckDeviceMultiSampleType����ֵ��һ֮�䡣
			 *
			 * @param Lockable ��������
			 *
			 * �趨ΪTRUE��ʹ�����ܹ���������
			 *
			 * @sa Graphics_t::CheckDeviceMultiSampleType
			 */
			/* ----------------------------------------------------------------------------*/
			void Create( uint nWidth, uint nHeight, PXLFORMAT Format, dword MultiSample, dword MultisampleQuality, bool Lockable )
			{
				_CreateRenderTarget( nWidth, nHeight, Format, MultiSample, MultisampleQuality, Lockable );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ������ȾĿ�����
			 *
			 * Դ����Pool����ΪD3DPOOL_SYSTEMMEM��
			 * Դ����Ϊ�������档
			 * ����豸֧�֣�Դ�������Ϊ��ͨ�������
			 * @todo�������δ˹��ܣ������ڣ�
			 * 
			 * @param pDtnPoint Ŀ�ı��棨�ñ��棩�������ľ��ε����Ͻǵ��ַ
			 *
			 * �������ΪNULL���������涼�ᱻ������
			 * @param pSrcSurface Դ����ĵ�ַ��
			 * @param pSrcRect Դ����ľ��ε�ַ
			 *
			 * �������ΪNULL���������涼�ᱻ������
			 */
			/* ----------------------------------------------------------------------------*/
			void UpdateSurface( POINT * pDtnPoint, const Surface_t< D3DPOOL_SYSTEMMEM > * pSrcSurface, RECT * pSrcRect )
			{
				Surface_Base::UpdateSurface( pDtnPoint, pSrcSurface, pSrcRect );
			}
			//template< uint Usage_, D3DPOOL Pool_ >
			//void UpdateSurface( POINT * pDtnPoint, const __Surface_Texture< Usage_, Pool_ > * pSurface, RECT * pSrcRect )
			//{
			//	_UpdateSurface( pDtnPoint, pSrcSurface, pSrcRect, __Texture_UgPl_Traits< Usage_, Pool_ >::UpdateSurfaceSource_Category );
			//}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���쿽����ȾĿ�����
			 *
			 * Դ����Pool���ͱ���ΪD3DPOOL_DEFAULT��
			 * ���ظ�ʽ��������Compressed Texture Formats
			 * �����趨Stretch Filter��
			 * ���ԶԶ��ز�����ȾĿ�������
			 * ���߼����⡭��
			 * 
			 * @param pDtnRect Ŀ�ı��棨�ñ��棩�������ľ��ε�ַ
			 *
			 * �������ΪNULL���´�������������ϡ�
			 * @param pSrcSurface Դ����ĵ�ַ��
			 * @param pSrcRect Դ����ľ��ε�ַ��
			 *
			 * �������ΪNULL���������涼�ᱻ������
			 */
			/* ----------------------------------------------------------------------------*/
			void StretchRect( RECT * pDtnRect, const Surface_t< D3DPOOL_DEFAULT > * pSrcSurface, RECT * pSrcRect )
			{
				Surface_Base::StretchRect( pDtnRect, pSrcSurface, pSrcRect );
			}
			void StretchRect( RECT * pDtnRect, const Surface_RenderTarget * pSrcSurface, RECT * pSrcRect )
			{
				Surface_Base::StretchRect( pDtnRect, pSrcSurface, pSrcRect );
			}
			template< uint _Usage, D3DPOOL _Pool >
			void StretchRect( RECT * pDtnRect, const Surface_Texture< _Usage, _Pool > * pSurface, RECT * pSrcRect )
			{
				_StretchRect( pDtnRect, pSrcSurface, pSrcRect, __Texture_UgPl_Traits< _Usage, _Pool >::StretchRectSource );
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �����ȾĿ���������
			 *
			 * ���˱�������ݿ�����Ŀ������ϡ�
			 * Ŀ��������Pool���ͱ���ΪD3DPOOL_SYSTEMMEM��
			 * ��ȾĿ����治�����Ƕ��ز����ġ�
			 * �������ظ�ʽ������ͬ���ߴ������ͬ��
			 * 
			 * @param pDestSurface Ŀ������ַ
			 */
			/* ----------------------------------------------------------------------------*/
			void GetData( Surface_t< D3DPOOL_SYSTEMMEM > * pDestSurface )
			{
				Surface_Base::GetData( pDestSurface );
			}
			template< uint Usage_ >
			void GetData( Surface_Texture< Usage_, D3DPOOL_SYSTEMMEM > * pDestSurface )
			{
				Surface_Base::GetData( pDestSurface );
			}
		};
		//��Ȼ���ҳ��
		//@todo�����ڣ�
		class ONEU_DXGRAPHICS_API Surface_Depth
			: Surface_Base
		{
		};

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ����������
		 *
		 * ��Ϊ�����������Ļ����ṩָ��
		 * �ܹ��ô����ָ����ָ������ı���
		 * ��װ���������Ŀǰ��û�У�
		 */
		/* ----------------------------------------------------------------------------*/
		class ONEU_DXGRAPHICS_API Surface_Texture_Base
			: public Surface_Base
		{
		public:
			explicit Surface_Texture_Base( IDirect3DSurface9 * pSurface )
				: Surface_Base( pSurface ){}
		};

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���������
		 *
		 * @tparam _Usage ��Ӧ�����Usage
		 * @tparam _Pool ��Ӧ�����Pool
		 *
		 * ��ģ������ֻ�������__Texture���ֻ�����һһ��Ӧ
		 */
		/* ----------------------------------------------------------------------------*/
		template< uint _Usage, D3DPOOL _Pool >
		class Surface_Texture
			: public Surface_Texture_Base
		{
		public:
			explicit Surface_Texture( IDirect3DSurface9 * pSurface )
				: Surface_Texture_Base( pSurface )
			{
			}
		private:
			void _ColorFill( COLOR crColor, RECT * pRect, __True_Category )
			{
				Surface_Base::ColorFill( crColor, pRect );
			}
			void _UpdateSurface( POINT * pDtnPoint, const Surface_Base * pSrcSurface, RECT * pSrcRect, __True_Category )
			{
				Surface_Base::UpdateSurface( pDtnPoint, pSrcSurface, pSrcRect );
			}
			void _StretchRect( RECT * pDtnRect, const Surface_Base * pSrcSurface, RECT * pSrcRect, __True_Category )
			{
				Surface_Base::StretchRect( pDtnRect, pSrcSurface, pSrcRect );
			}
			void _GetData( Surface_Base * pDestSurface )
			{
				Surface_Base::GetData( pDestSurface );
			}
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����������
			 *
			 * ����Pool���ͱ���ΪD3DPOOL_DEFAULT��
			 * 
			 * @param crColor �����ɫֵ
			 * @param pRect �����ε�ַ
			 *
			 * �������ΪNULL����������ᱻ��䡣
			 */
			/* ----------------------------------------------------------------------------*/
			void ColorFill( COLOR crColor, RECT * pRect = NULL )
			{
				_ColorFill( crColor, pRect, __Texture_UgPl_Traits< _Usage, _Pool >::ColorFill_Category() );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �����������
			 *
			 * Դ����Pool���ͱ���ΪD3DPOOL_SYSTEMMEM��
			 * Ŀ�ı���Pool���ͱ���ΪD3DPOOL_DEFAULT��
			 * 
			 * @param pDtnPoint Ŀ�ı��棨�ñ��棩�������ľ��ε�ַ
			 *
			 * �������ΪNULL���´�������������ϡ�
			 * @param pSrcSurface  Դ����ĵ�ַ��
			 * @param pSrcRect Դ����ľ��ε�ַ
			 *
			 * �������ΪNULL���������涼�ᱻ������
			 */
			/* ----------------------------------------------------------------------------*/
			void UpdateSurface( POINT * pDtnPoint, const Surface_t< D3DPOOL_SYSTEMMEM > * pSrcSurface, RECT * pSrcRect )
			{
				_UpdateSurface( pDtnPoint, pSrcSurface, pSrcRect, __Texture_UgPl_Traits< _Usage, _Pool >::UpdateSurfaceDestination_Category );
			}
			template< uint Usage_, D3DPOOL Pool_ >
			void UpdateSurface( POINT * pDtnPoint, const Surface_Texture< Usage_, Pool_ > * pSrcSurface, RECT * pSrcRect )
			{
				_UpdateSurface( pDtnPoint, pSrcSurface, pSrcRect,
					__Bool_Category<
					__Texture_UgPl_Traits< Usage_, Pool_ >::bUpdateSurfaceSource && __Texture_UgPl_Traits< _Usage, _Pool >::bUpdateSurfaceDestination
					>::Category());
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���쿽����ȾĿ���������
			 *
			 * ��������ȾĿ������ʹ�á�
			 * Դ����Pool���ͱ���ΪD3DPOOL_DEFAULT��
			 * ���ظ�ʽ��������Compressed Texture Formats
			 * �����趨Stretch Filter��
			 * ���ԶԶ��ز�����ȾĿ�������
			 * ���߼����⡭��
			 * 
			 * @param pDtnRect Ŀ�ı��棨�ñ��棩�������ľ��ε�ַ
			 *
			 * �������ΪNULL���´�������������ϡ�
			 * @param pSrcSurface Դ����ĵ�ַ��
			 * @param pSrcRect Դ����ľ��ε�ַ��
			 *
			 * �������ΪNULL���������涼�ᱻ����
			 */
			/* ----------------------------------------------------------------------------*/
			void StretchRect( RECT * pDtnRect, const Surface_t< D3DPOOL_DEFAULT > * pSrcSurface, RECT * pSrcRect )
			{
				_StretchRect( pDtnRect, pSrcSurface, pSrcRect, __Texture_UgPl_Traits< _Usage, _Pool >::StretchRectDestination_Category() );
			}
			void StretchRect( RECT * pDtnRect, const Surface_RenderTarget * pSrcSurface, RECT * pSrcRect )
			{
				_StretchRect( pDtnRect, pSrcSurface, pSrcRect, __Texture_UgPl_Traits< _Usage, _Pool >::StretchRectDestination_Category() );
			}
			template< uint Usage_, D3DPOOL Pool_ >
			void StretchRect( RECT * pDtnRect, const Surface_Texture< Usage_, Pool_ > * pSrcSurface, RECT * pSrcRect )
			{
				_StretchRect( pDtnRect, pSrcSurface, pSrcRect,
					__Bool_Category<
					__Texture_UgPl_Traits< _Usage, _Pool >::bStretchRectDestination && __Texture_UgPl_Traits< Usage_, Pool_ >::bStretchRectSource
							>::Category() );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ��ȾĿ�������������
			 * 
			 * ���˱�������ݿ�����Ŀ������ϡ�
			 * Ŀ��������Pool���ͱ���ΪD3DPOOL_SYSTEMMEM��
			 * ��ȾĿ����治�����Ƕ��ز����ġ�
			 * �������ظ�ʽ������ͬ���ߴ������ͬ��
			 * 
			 * @param pDestSurface Ŀ������ַ
			 */
			/* ----------------------------------------------------------------------------*/
			void GetData( Surface_t< D3DPOOL_SYSTEMMEM > * pDestSurface )
			{
				_GetData( pDestSurface, __Bool_Category< _Usage == D3DUSAGE_RENDERTARGET >::Category() );
			}
			template< uint Usage_ >
			void GetData( Surface_Texture< Usage_, D3DPOOL_SYSTEMMEM > * pDestSurface )
			{
				_GetData( pDestSurface, __Bool_Category< _Usage == D3DUSAGE_RENDERTARGET >::Category() );
			}
		};		
	}
}
