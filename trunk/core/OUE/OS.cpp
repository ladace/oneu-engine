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
#include "OS.h"

namespace OneU
{
	namespace os
	{
		ONEU_API void Sleep(dword dwMilliseconds){ ::Sleep( dwMilliseconds ); }

		ONEU_API dword GetTime(){ return ::timeGetTime(); }

		ONEU_API void GetSystemTime(SYSTEMTIME * pSystemTime){ ::GetSystemTime( (LPSYSTEMTIME)pSystemTime ); }

		ONEU_API void ShowCursor(bool bShow){ ::ShowCursor( bShow ); }

		ONEU_API void SetCursorPos(int X, int Y){ ::SetCursorPos( X, Y ); }

		ONEU_API wchar * GetDirectory()
		{
			static wchar strDirectory[ MAX_PATH ] = {};
			if( !strDirectory[ 0 ] )::GetCurrentDirectoryW( MAX_PATH, strDirectory );
			return strDirectory;
		}

		ONEU_API void ErrorBox(pcwstr Errorinfo){ ::MessageBoxW(NULL, Errorinfo, L"Error", MB_OK | MB_ICONERROR ); }

		//���������Game_Win32�б���ʼ��
		ONEU_API float Rand(){return ((float)rand()) / RAND_MAX;}
	}
}