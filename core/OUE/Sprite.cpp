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
#include "Sprite.h"
#include "Game.h"

namespace OneU
{
	class Sprite_Impl
		: public ISprite
	{
		image_t m_Img;
		color_t color;

		float m_CenterX, m_CenterY;
		video::BLENDMODE m_Mode;
		uint32 m_CMode;
	public:
		Sprite_Impl(image_t& img)
			: m_Img(img), color(0, 0, 0), m_CenterX(0.0f), m_CenterY(0.0f),
			m_Mode(video::BM_NORMAL), m_CMode(video::CBM_ADD){
			this->create2DTransform();
		}
		~Sprite_Impl(){
			int haha = 0;
		}

		void setImage(image_t img){ m_Img = img; }
		image_t getImage(){ return m_Img; }
		void setCenterX(float nx){ m_CenterX = nx;}
		float getCenterX() const { return m_CenterX; }
		void setCenterY(float ny){ m_CenterY = ny;}
		float getCenterY() const { return m_CenterY; }

		void setBlendMode(video::BLENDMODE mode){ m_Mode = mode;}
		video::BLENDMODE getBlendMode(){ return m_Mode; }
		void setColorBlendMode(uint32 mode){ m_CMode = mode; }
		uint32 getColorBlendMode(){ return m_CMode; }


		void setColor(color_t c){ color = c; }
		color_t getColor(){ return color; }
		void setAlpha(ubyte alpha){ color.setAlpha(alpha); }

		void paint();
		void _describe(String& buffer, int depth){ buffer.append(L"<sprite>\n"); }
	};

	void Sprite_Impl::paint(){
		IVideo& Vi = GetVideo();
		vector2u_t ss = Vi.getDeviceSize();

		Vi.setBlendColor(m_CMode, color);
		Vi.setBlendMode(m_Mode);
		float w = (float)m_Img.get()->getWidth(), h = (float)m_Img.get()->getHeight();
		Vi.renderImage(*m_Img.get(), rect(-m_CenterX * w, -m_CenterY * h, (1 - m_CenterX) * w, (1 - m_CenterY) * h));
	}

	ONEU_API ISprite* Sprite_create(image_t& img)
	{
		return ONEU_NEW Sprite_Impl(img);
	}
}