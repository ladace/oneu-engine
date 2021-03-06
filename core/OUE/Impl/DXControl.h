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
#include "../Control.h"
#include "DXLib/DXInput.h"

namespace OneU
{
	class DXControl
		: public IControl
	{
		DX::KeyBoard m_KB;
		DX::Mouse m_Mouse;
		DX::KeyBoard::State m_KB_State;
		DX::Mouse::State m_Mouse_State;

		bool m_Button_Release[8], m_Button_Press[8];
		bool m_KB_Release[256], m_KB_Press[256];
	public:
		DXControl();
		~DXControl();

		void init(){}
		void update();
		bool keyIsDown(uint32 scancode);
		bool keyPress(uint32 scancode);
		bool keyRelease(uint32 scancode);

		bool buttonIsDown(uint32 ButtonID);
		bool buttonRelease(uint32 ButtonID);
		bool buttonPress(uint32 ButtonID);

		vector2i_t mouseOffset();

		void _notifyButton(uint32 id, bool down){
			if(!down)
				m_Button_Release[id] = true;
			else
				m_Button_Press[id] = true;
		}
		void _notifyKey(uint32 code, bool down){
			if(!down)
				m_KB_Release[code] = true;
			else
				m_KB_Press[code] = true;
		}
	};
}