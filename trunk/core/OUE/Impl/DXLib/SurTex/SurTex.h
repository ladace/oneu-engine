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
#include "Texture.h"
namespace OneU
{
	namespace DX
	{
		//һ��typedef 
		//__Surface_Texture����Texture�����SurfaceType
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ͨ���� 
		 */
		/* ----------------------------------------------------------------------------*/
		typedef Surface_t< D3DPOOL_DEFAULT > Surface;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �������ı���
		 *
		 * �ɱ�CPU������д������Ⱦ������
		 */
		/* ----------------------------------------------------------------------------*/
		typedef Surface_t< D3DPOOL_SYSTEMMEM > Surface_Lk;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��D3DĬ�Ϲ���ı���
		 *
		 * ���Ա�������ͬʱ��Ⱦ�����Ͽ졣
		 * ֻ��������д��ʱ����Ҫ��Surface_Lk����һ���ֹ�����
		 */
		/* ----------------------------------------------------------------------------*/
		typedef Surface_t< D3DPOOL_MANAGED > Surface_Mg;
		//һ��typedef
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ͨ����
		 */
		/* ----------------------------------------------------------------------------*/
		typedef Texture_t< 0, D3DPOOL_DEFAULT > Texture;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �ɱ�����������
		 *
		 * �ɱ�CPU������д������Ⱦ������
		 */
		/* ----------------------------------------------------------------------------*/
		typedef Texture_t< 0, D3DPOOL_SYSTEMMEM > Texture_Lk;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��D3DĬ�Ϲ��������
		 *
		 * ���Ա�������ͬʱ��Ⱦ�����Ͽ졣
		 * ֻ��������д��ʱ����Ҫ��Texture_Lk����һ���ֹ�����
		 */
		/* ----------------------------------------------------------------------------*/
		typedef Texture_t< 0, D3DPOOL_MANAGED > Texture_Mg;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȾĿ������
		 *
		 * �����еı����������ȾĿ��
		 */
		/* ----------------------------------------------------------------------------*/
		typedef Texture_t< D3DUSAGE_RENDERTARGET, D3DPOOL_DEFAULT > Texture_RT;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��̬����
		 *
		 * ��ҪӲ��֧��
		 * ����������ĵ�D3DUSAGE_DYNAMIC
		 */
		/* ----------------------------------------------------------------------------*/
		typedef Texture_t< D3DUSAGE_DYNAMIC, D3DPOOL_DEFAULT > Texture_D;//��ҪӲ��֧�� �л����ٲ����ĵ�
	}

};
