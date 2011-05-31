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
#include "DXControl.h"
#include "../../DXInput/DXInput.h"
#include "Win32.h"
#include "../Event.h"
#include "../Game.h"

namespace OneU
{
	void __DeviceDataHandler(uint32 scancode, uint32 status, uint32, uint32){
#pragma warning(push)
#pragma warning(disable :4800)
		GetGame().onKey(KeyEvent((::WCHAR)scancode, (bool)(status & 0x80)));
#pragma warning(pop)
	}
	DXControl::DXControl()
		: m_curStateID(0), m_pKB_State(&m_KB_StateBuf[0]), m_pKB_LastState(&m_KB_StateBuf[0]),
		m_pMouse_State(&m_Mouse_StateBuf[0]), m_pMouse_LastState(&m_Mouse_StateBuf[0])
	{
		memset(m_KB_StateBuf, 0, sizeof(m_KB_StateBuf));
		DX::Input.Init(g_hInstance, g_hWnd);
		m_KB.Create(10);
		m_KB.Acquire();
		m_Mouse.Create(10);
		m_Mouse.Acquire();
	}
	DXControl::~DXControl(){
		m_KB.Destroy();
		m_Mouse.Destroy();
		DX::Input.Destroy();
	}
	void DXControl::update(){
		m_KB.Read(m_KB_StateBuf[m_curStateID]);
		m_Mouse.Read(m_Mouse_StateBuf[m_curStateID]);

		m_pMouse_State = &m_Mouse_StateBuf[m_curStateID];
		m_pKB_State = &m_KB_StateBuf[m_curStateID];

		m_curStateID = (m_curStateID + 1) % 2;
		m_pKB_LastState = &m_KB_StateBuf[m_curStateID];
		m_pMouse_LastState = &m_Mouse_StateBuf[m_curStateID];

		m_KB.HandleData(__DeviceDataHandler);
		m_Mouse.HandleData(__DeviceDataHandler);
	}
	bool DXControl::keyIsDown(uint32 scancode){
		return m_pKB_State->GetState(scancode); 
	}

	bool DXControl::keyPress(uint32 scancode){
		return (!m_pKB_State->GetState(scancode)) && m_pKB_LastState->GetState(scancode);
	}

	bool DXControl::keyRelease(uint32 scancode){
		return m_pKB_State->GetState(scancode) && (!m_pKB_LastState->GetState(scancode));
	}

	bool DXControl::buttonIsDown(uint32 ButtonID){
		return m_pMouse_State->GetState(ButtonID);
	}

	bool DXControl::buttonRelease(uint32 ButtonID){
		return (!m_pMouse_State->GetState(ButtonID)) && m_pMouse_LastState->GetState(ButtonID);
	}

	bool DXControl::buttonPress(uint32 ButtonID){
		return m_pMouse_State->GetState(ButtonID) && (!m_pMouse_LastState->GetState(ButtonID));
	}

	vector2i_t DXControl::mouseOffset(){
		return vector2i_t(m_pMouse_State->GetlX(), m_pMouse_State->GetlY());
	}
}