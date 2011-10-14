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
 * @file Label.h
 * @brief ��ǩ
 *
 * ��ȾԪ�ء�
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "Video.h"

namespace OneU
{
	enum T_ALIGN_V{ T_TOP = 0, T_BOTTOM = 4, T_VCENTER = 8};
	enum T_ALIGN_H{ T_LEFT = 0, T_RIGHT = 1, T_CENTER = 2 };
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief ��ǩ
	 *
	 * ������ʾ���֡�
	 */
	/* ----------------------------------------------------------------------------*/
	class ILabel
		: public video::INode
	{
	public:
		virtual void setText(pcwstr text) = 0;
		virtual pcwstr getText() = 0;
		virtual void setColor(color_t color) = 0;
		virtual color_t getColor() = 0;
		virtual void setAlpha(ubyte alpha) = 0;
		ubyte getAlpha(){ return getColor().getAlpha(); }
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ���ö��뷽ʽ
		 *
		 * @param align ��ΪT_ALIGN_V��T_ALIGN_H�Ľ�ϣ�λ�򣩡�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void setAlign(uint32 align) = 0;
		virtual uint32 getAlign() = 0;
	};
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief ��ǩ����
	 *
	 * @param Width ��ʾ���
	 * @param Height ��ʾ�߶�
	 * @param fontSize ���ִ�С
	 * @param fontName ��������
	 *
	 * @return ��ǩ
	 */
	/* ----------------------------------------------------------------------------*/
	ONEU_API ILabel* Label_create(float Width, float Height, uint32 fontSize, pcwstr fontName = L"Arial");
}
