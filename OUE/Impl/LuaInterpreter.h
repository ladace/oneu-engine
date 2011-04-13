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
#include "../AtInterpreter.h"

extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

namespace OneU
{
	namespace atom
	{
		class LuaInterpreter
			: public IInterpreter
		{
			lua_State* m_L;
		public:
			LuaInterpreter();
			~LuaInterpreter();

			void execFile(pcwstr filename);
			value* exec(pcwstr code);
			//��ȡ��ǰ�Ķ�ջ��Ϣ
			void _getStackInfo(String& buffer);
			void gc(){
				lua_gc(m_L, LUA_GCCOLLECT, 0);
			}
		};
	}
}