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
//һ��SpriteE�����൱��һ�����������
//���Ի��ƾ��� ���ڲ�����һ����������Ϣ ���󴫵ݽ����������Ϊ��������Ϣ���ݸ�����
//��ͨ����Ա������������
//����FontE��DrawText����
//��ʹ��SpriteE::I��ʹ�����ж���
#pragma once
#include "../../Base.h"
#ifdef __ONEU_USE_GE
#include "DXGraphics.h"
#include "SurTex\SurTex.h"
#include < d3dx9.h >

#define __ONEU_SPRITE_VERSION 100

namespace OneU
{
	namespace DX
	{
		class ONEU_DXGRAPHICS_API SpriteE
		{
		private:
			ID3DXSprite *m_pSprite;
		public:
			static SpriteE I;

			SpriteE()
				: m_pSprite( NULL )
			{
				//��֤���캯����˳��
				GetGraphics();
			}
			~SpriteE()
			{
				Destroy();
			}
			ID3DXSprite* _Obtain()
			{
				return m_pSprite;
			}
			void Create()
			{
				ONEU_ASSERT( m_pSprite == NULL );
				XV( D3DXCreateSprite( _pD3DDevice, &m_pSprite ) );
			}
			void Destroy()
			{
				SAFE_RELEASE( m_pSprite );
			}
			void Begin( uint32 Flags = D3DXSPRITE_ALPHABLEND )/*ע:�˺�����Ҫ��������Ⱦ�ṹ��Graphics::Render?�������ӳ����� */
			{
				XV( m_pSprite -> Begin( Flags ) );
			}
			void End()
			{
				XV_DEBUG( m_pSprite -> End() );
			}
			void Draw( const Texture_Base * _Texture, const VECTOR3 * pCenter, const VECTOR3 * pPosition, const RECT * pSrcRect, const COLOR crColor = 0xffffffff )
			{
				XV_DEBUG( m_pSprite -> Draw( _Texture->_Obtain(), pSrcRect,
					reinterpret_cast< const D3DXVECTOR3 * > ( pCenter ),
					reinterpret_cast< const D3DXVECTOR3 * > ( pPosition ), crColor ) );
			}
			void SetTransform( const MATRIX * Transform )
			{
				XV_DEBUG( m_pSprite -> SetTransform( reinterpret_cast< const D3DXMATRIX * > ( Transform ) ) );
			}
			MATRIX * GetTransform( MATRIX * Transform )
			{
				XV( m_pSprite -> SetTransform( reinterpret_cast< D3DXMATRIX * > ( Transform ) ) );
				return Transform;
			}

			void OnLostDevice()
			{
				m_pSprite->OnLostDevice();
			}
			void OnResetDevice()
			{
				m_pSprite->OnResetDevice();
			}
		};
	}
}
#endif