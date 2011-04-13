/** 
 * @file Painter.h
 * @brief ��������
 *
 * Ϊ2D��Ϸ�ṩ�򵥵Ļ��ƺ�����
 * Ϊ��׷��Ч��ʹ�ÿ�Ƚϸ��ӡ����ʺ���DLL����������
 * @author Ladace
 * @version 1.0.0.1
 * @date 2010-07-16
 */
#pragma once

#include "../Utility.h"

#ifdef __ONEU_USE_GE
#include "..\..\DXGraphics\SpriteE.h"
#else
#pragma message( __FILE__":Feng Needs OneU GE Library!")
AnErrorOccured!!!
#endif
#include "FengDef.h"
//#ifdef __ONEU_USE_DIRECT3D
#include "..\..\DXGraphics\DXGraphics.h"
#include "..\..\DXGraphics\TStage.h"
#include "..\..\DXGraphics\VertexUP.h"
//namespace Lib = DX;
//#endif

namespace OneU
{
	namespace Feng
	{
		/**
		 * @defgroup FengPaint �������ģ��
		 * @addtogroup Feng
		 */
		/*@{*/
		//��׼���� �÷����ᾭ������任
		//
		//��������
		//�ٶ�RenderState��LIGHT��ΪFALSE ���޹�����
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ������׼����
		*
		* ʹ����ά�������������
		* �ᾭ��������ˮ�ߡ�
		* �����������TStage(0)������ �Լ�Graphics��FVF��
		* ע�����Ҫ��ȫ��ʾӦ�趨LIGHTINGΪFALSE��CULLMODEΪ1��0��
		* 
		* @param rd ��Ⱦ�ṹ��
		* @param Tex �����Ƶ�����
		* @param pDrawRect ���Ƶľ���λ�á�
		* @param pSrcRect Դ���� Ĭ��Ϊ��λ���Ρ�
		*
		* @remarks
		* �ú���Ϊ������������������һ������Ĳ����������һ�𡣿����ں���ǰ���趨һЩ����Ĳ�������TStage(0)���趨�任���������ƻ��ƹ��̣�
		* @attention
		* ��������ScreenPainter��ʱ��ʹ�á�\n
		* ��������ScreenDrawer��ʱ��ʹ�á�
		*
		* ע����λ�������ؼƣ��������UV���ꡣ��λ���α�ʾ����ҳ�档�������1��Wrap����Ч��ȡ����Wrap��ʽ��
		*/
		/* ----------------------------------------------------------------------------*/
		template< class TextureType >
		void Paint( DX::RenderManip &rd, const TextureType &Tex, const CRect *pDrawRect, const CRect *pSrcRect );
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ������׼����
		*
		* ʹ����ά�������������
		* �ᾭ��������ˮ�ߡ�
		* �����������TStage(0)������ �Լ�Graphics��FVF��
		* ע�����Ҫ��ȫ��ʾӦ�趨LIGHTINGΪFALSE��CULLMODEΪ1��0��
		* 
		* @param rd ��Ⱦ�ṹ��
		* @param Tex �����Ƶ�����
		* @param pDrawRect ���Ƶľ���λ�á�
		* @param crColor ��ɫЧ�� ��ɫ��Ч�������ӡ����Ƶȣ���TStage(0)�Ĳ�����ء�
		* @param pSrcRect Դ���� Ĭ��Ϊ��λ���Ρ�
		*
		* @remarks
		* �ú���Ϊ������������������һ������Ĳ����������һ�𡣿����ں���ǰ���趨һЩ����Ĳ�������TStage(0)���趨�任���������ƻ��ƹ��̣�
		* @attention
		* ��������ScreenPainter�����ʱ��ʹ�á�\n
		* ��������ScreenDrawer��ʱ��ʹ�á�
		*
		* ע����λ�������ؼƣ��������UV���ꡣ��λ���α�ʾ����ҳ�档�������1��Wrap����Ч��ȡ����Wrap��ʽ��
		*/
		/* ----------------------------------------------------------------------------*/
		template< class TextureType >
		void Paint( DX::RenderManip &rd, const TextureType &Tex, const CRect *pDrawRect, COLOR crColor, const CRect *pSrcRect );
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��Ļ������
		 *
		 * ��������һ������������Ļ�ϻ�������
		 * ���ʹ����DX::SpriteE�Ŀ⣬���ڴ˶��������ڷ�Χ�ڣ����й����豸�ĵ��ö��ᱻӰ�졣�ο�ID3DXSprite���Դ�Ϊһ����׼��
		 * �ڴ��౻�������豸����TStage(0)��Ķ�Ϊ�ʺ�2D��Ⱦ��ģʽ������ڸö����������ڸĶ��������������ա�����ܵ�����Ⱦ����
		 * ����ͬʱ�����������϶���
		 * ����Ϊ�����࣬��˿��ܻ���Щ�����������׷��Ч�ʣ�Ӧֱ��ʹ��SpriteE��
		 */
		/* ----------------------------------------------------------------------------*/
		class ONEU_UTIL_API ScreenPainter
		{
		private:
			DX::RenderManip &m_Rd;
			static int ClassNum;

			const MATRIX *_pLastMatrix;//�趨������һ�������ַ ����ͨ���ȶ� �Ż��趨�������

			//��Ԫ����
			//�������������������ڴ���ScreenPainter�����ʱ��ʹ�� ��˶���Ϊ��Ԫ����
			template< class TextureType >
			friend void Paint( DX::RenderManip &rd, const TextureType &Tex, const CRect *pDrawRect, const CRect *pSrcRect );
			template< class TextureType >
			friend void Paint( DX::RenderManip &rd, const TextureType &Tex, const CRect *pDrawRect, COLOR crColor, const CRect *pSrcRect );
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���캯��
			 * 
			 * @param &rd ��Ⱦ�ṹ��
			 */
			/* ----------------------------------------------------------------------------*/
			//ʵ�־����˲���ͬʱ���ڸ��������ʵ��
			ScreenPainter( DX::RenderManip &rd )
				: m_Rd( rd )
			{
				//Ԥ������ı�̶����Ķ���
				ClassNum++;
				ASSERT( ClassNum == 1 );
				//
				DX::SpriteE::I.Begin();
			}
			~ScreenPainter()
			{
				DX::SpriteE::I.End();
				ClassNum--;
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��������
			 * 
			 * @param &Tex ����
			 * @param &Pos ���Ƶ���Ļλ��
			 * @param pSrcRect Դ���Σ������ؼơ���������Դ�����������Ĳ��֡���ΪNULL�������������
			 * @param crColor ��ɫЧ������ɫ��Ч�������ӡ����Ƶȣ���TStage(0)�Ĳ�����ء�
			 */
			/* ----------------------------------------------------------------------------*/
			template< class TextureType >
			void Paint( const TextureType &Tex, const CVector2 &Pos, const RECT *pSrcRect = NULL, COLOR crColor = 0xffffffff )
			{
				if( _pLastMatrix != &matIMatrix ){ DX::SpriteE::I.SetTransform( &matIMatrix ); _pLastMatrix = &matIMatrix; }
				DX::SpriteE::I.Draw( &Tex, NULL, &CVector3( Pos.x, Pos.y, 0.0f ), pSrcRect, crColor );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��������
			 * 
			 * @param &Tex ����
			 * @param &Pos ���Ƶ���Ļλ�ã������ؼ�
			 * @param &Center ������Ϊ���飬�����������λ�á������ؼ�
			 * @param pSrcRect Դ���Σ������ؼơ���������Դ�����������Ĳ��֡���ΪNULL�������������
			 * @param crColor ��ɫЧ������ɫ��Ч�������ӡ����Ƶȣ���TStage(0)�Ĳ�����ء�
			 */
			/* ----------------------------------------------------------------------------*/
			template< class TextureType >
			void Paint( const TextureType &Tex, const CVector2 &Pos, const CVector2 &Center, const RECT *pSrcRect = NULL, COLOR crColor = 0xffffffff )
			{
				if( _pLastMatrix != &matIMatrix ){ DX::SpriteE::I.SetTransform( &matIMatrix ); _pLastMatrix = &matIMatrix; }
				DX::SpriteE::I.Draw( &Tex, &CVector3( Center.x, Center.y, 0.0f ), &CVector3( Pos.x, Pos.y, 0.0f ), pSrcRect, crColor );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��������
			 * 
			 * @param &Tex ����
			 * @param &mat ����ı任��������ᰴ�ձ任����任�ٻ��Ƶ���Ļ�ϡ�
			 * @param pSrcRect Դ���Σ������ؼơ���������Դ�����������Ĳ��֡���ΪNULL�������������
			 * @param crColor ��ɫЧ��
			 */
			/* ----------------------------------------------------------------------------*/
			template< class TextureType >
			void Paint( const TextureType &Tex, const MATRIX &mat, const RECT *pSrcRect = NULL, COLOR crColor = 0xffffffff );

			/*@name �򵥻���*/
			/*@{*/
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �趨�任����
			 *
			 * Paint�����ﶼ���Զ��趨�任���󡣶��ú�������S_Paint���ʹ�õġ�
			 * �趨�任��������S_Paint���ɱ���Ƶ���趨�任������������Ч��Ӱ�졣
			 * �ϸ߼���ʹ�÷�ʽ��
			 *
			 * @param mat ����
			 * @relates S_Paint
			 */
			/* ----------------------------------------------------------------------------*/
			void SetTransform( const MATRIX &mat )
			{
				DX::SpriteE::I.SetTransform( &mat );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �򵥻���
			 *
			 * ���ܵ�SetTransform��Ӱ�졣һ����SetTransform���ʹ�á�
			 * �ϸ߼���ʹ�÷�ʽ��
			 * 
			 * @param Tex �����Ƶ�����
			 * @param &Pos ���Ƶ���Ļλ�ã������ؼ�
			 * @param &Center ������Ϊ���飬�����������λ�á������ؼ�
			 * @param pSrcRect Դ���Σ������ؼơ���������Դ�����������Ĳ��֡���ΪNULL�������������
			 * @param crColor ��ɫЧ��
			 *
			 * ��ɫ��Ч�������ӡ����Ƶȣ���TStage(0)�Ĳ�����ء�
			 *
			 * @relates SetTransform
			 */
			/* ----------------------------------------------------------------------------*/
			template< class TextureType >
			void S_Paint( const TextureType &Tex, const CVector2 &Pos, const CVector2 &Center, const RECT *pSrcRect = NULL, COLOR crColor = 0xffffffff )
			{
				DX::SpriteE::I.Draw( &Tex, &CVector3( Center.x, Center.y, 0.0f ), &CVector3( Pos.x, Pos.y, 0.0f ), pSrcRect, crColor );
			}
			/*@{*/
		};

		template< class TextureType >
		void ScreenPainter::Paint( const TextureType &Tex, const MATRIX &mat, const RECT *pSrcRect, COLOR crColor )
		{
			if( _pLastMatrix != &mat ){ DX::SpriteE::I.SetTransform( &mat ); _pLastMatrix = &mat; }
			DX::SpriteE::I.Draw( &Tex, NULL, NULL, pSrcRect, crColor );
		}

		namespace internal
		{
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��λ����
			 * ����������߷ֱ�Ϊ0101
			 */
			/* ----------------------------------------------------------------------------*/
			extern CRect IRect;
		}
#ifdef __ONEU_USE_DIRECT3D
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���λ�λ��
		 *
		 * �Ծ�����ʱ���ʼ���ĸ������XY���ꡣ
		 * Ĭ��Ϊ��λ���Ρ�
		 * 
		 * @param v[] ��������
		 * @param prc ����
		 */
		/* ----------------------------------------------------------------------------*/
		template< dword FVF >
		inline void Rectialize( DX::VertexUP< FVF > v[], const CRect *prc = &internal::IRect )
		{
			v[0].SetPos( prc->left,  prc->top );
			v[1].SetPos( prc->left,  prc->bottom );
			v[2].SetPos( prc->right, prc->bottom );
			v[3].SetPos( prc->right, prc->top );
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���λ�UV
		 *
		 * �Ծ�����ʱ���ʼ���ĸ������UV���ꡣ
		 * Ĭ��Ϊ��λ���Ρ�
		 * 
		 * @tparam index UV�����
		 * @param v[] ��������
		 * @param prc ����
		 */
		/* ----------------------------------------------------------------------------*/
		template< int index, dword FVF >
		inline void Rectialize_UV( DX::VertexUP< FVF > v[], const CRect *prc = &internal::IRect )
		{
			v[0].SetUV< index >( prc->left,  prc->top );
			v[1].SetUV< index >( prc->left,  prc->bottom );
			v[2].SetUV< index >( prc->right, prc->bottom );
			v[3].SetUV< index >( prc->right, prc->top );
		}
		
		/* ----------------------------------------------------------------------------*/
		//��׼����ʵ��
		template< class TextureType >
		void Paint( DX::RenderManip &rd, const TextureType &Tex, const CRect *pDrawRect, const CRect *pSrcRect = &internal::IRect )
		{
			ASSERT( ScreenPainter::ClassNum == 0 );
			static DX::VertexUP< DX::FVF_XYZ | DX::FVF_TEX1 > v[4];
			Rectialize( v, pDrawRect );
			Rectialize_UV< 0 >( v, pSrcRect );
			DX::Graphics.SetFVF( v );
			DX::TStage( 0 ).SetTexture( Tex );
			rd.RenderVertexUP( DX::RenderManip::PT_TRIANGLEFAN, v, 2 );
		}
		template< class TextureType >
		void Paint( DX::RenderManip &rd, const TextureType &Tex, const CRect *pDrawRect, COLOR crColor, const CRect *pSrcRect = &internal::IRect )
		{
			ASSERT( ScreenPainter::ClassNum == 0 );
			static DX::VertexUP< DX::FVF_XYZ | DX::FVF_TEX1 | DX::FVF_DIFFUSE > v[4];
			Rectialize( v, pDrawRect );
			Rectialize_UV< 0 >( v, pSrcRect );
			v[0].Diffuse() = v[1].Diffuse() = v[2].Diffuse() = v[3].Diffuse() = crColor;
			DX::Graphics.SetFVF( v );
			DX::TStage( 0 ).SetTexture( Tex );
			rd.RenderVertexUP( DX::RenderManip::PT_TRIANGLEFAN, v, 2 );
		}
		/*@}*///FengPaint
#endif
	}//namespace Feng
}//namespace OneU
