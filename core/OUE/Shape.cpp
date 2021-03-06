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
#include "Shape.h"
#include "Impl/DXVideo.h"
#include "Game.h"
#include "Impl/DXLib/VertexUP.h"
#include "Impl/DXLib/TStage.h"

namespace OneU
{
	class Shape_Rect
		: public IShape
	{
		rect m_Rect;
		color_t m_Color;
		bool m_bBorder;
	public:
		Shape_Rect(const rect& rc)
			: m_Rect(rc), m_Color(255, 255, 255), m_bBorder(false){
			this->create2DTransform();
		}

		void setColor(color_t color){ m_Color = color; }
		color_t getColor(){ return m_Color; }
		void setMode(bool bBorder){m_bBorder = bBorder; }
		bool getMode(){ return m_bBorder;}

		void paint();
		void _describe(String& buffer, int depth){ buffer.append(L"<shape rect>\n"); }
	};

	void Shape_Rect::paint(){
		GetVideo().setBlendMode(video::BM_NORMAL);

		static DX::VertexUP< DX::FVF_XYZ | DX::FVF_DIFFUSE > v[5];

		DX::TStage(0).DisableTexture();

		v[0].SetPos(m_Rect.left, m_Rect.top);
		v[1].SetPos(m_Rect.left, m_Rect.bottom);
		v[2].SetPos(m_Rect.right, m_Rect.bottom);
		v[3].SetPos(m_Rect.right, m_Rect.top);
		v[4].SetPos(m_Rect.left, m_Rect.top);

		v[0].Diffuse() = v[1].Diffuse() = v[2].Diffuse() = v[3].Diffuse() = v[4].Diffuse() = m_Color;

		DX::Graphics.SetFVF(v);
		if(m_bBorder)
			g_pRD->RenderVertexUP(DX::RenderManip::PT_LINESTRIP, v, 4);
		else
			g_pRD->RenderVertexUP(DX::RenderManip::PT_TRIANGLEFAN, v, 2);
	}

	ONEU_API IShape* Shape_rect(const rect& rc){
		return ONEU_NEW Shape_Rect(rc);
	}
}