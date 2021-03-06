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
#include "Game.h"
#include "Video.h"
#include "Scene.h"

#ifdef _WIN32
#include "Impl/Game_Win32.h"
#endif
#ifdef ONEU_USE_DIRECT3D
#include "Impl/DXVideo.h"
#endif
#include "Impl/DXAudio.h"
#ifdef ONEU_USE_DIRECTINPUT
#include "Impl/DXControl.h"
#endif

//输出流重定向
#include <io.h>

namespace OneU
{
	static IGame* s_pGame = NULL;

	ONEU_API IGame& GetGame(){ONEU_ASSERT(s_pGame != NULL); return *s_pGame;}
	ONEU_API bool HasGame(){ return s_pGame != NULL; }

	static TerminateHandler _last_eh = NULL;
	static void _destroyGame();

	ONEU_API void Game_build()
	{

		ONEU_ASSERT(s_pGame == NULL);
		Logger_build(LoggerDisk_Factory);

		//错误流重定向
		FILE* nferr = freopen("err", "w", stderr);

#ifdef _WIN32
		s_pGame = ONEU_NEW Game_Win32;
#endif

		_last_eh = SetTerminateHandler(_destroyGame);
	}	
	ONEU_API void Game_destroy(){
		if(s_pGame != NULL)
			ONEU_DELETE s_pGame;
		s_pGame = NULL;
		//销毁日志系统	其中Logger在Game_build中初始化
		Logger_destroy();
		GetAllocator().checkLeaks();
	}

	void _destroyGame()
	{
		Game_destroy();
		s_pGame = NULL;
		if(_last_eh != NULL)
			_last_eh();
	}

	ONEU_API IVideo* Video_create(){
#ifdef ONEU_USE_DIRECT3D
		return ONEU_NEW DXVideo;
#endif
	}
	ONEU_API IAudio* Audio_create(){
		return ONEU_NEW DXAudio;
	}
	ONEU_API IControl* Control_create(){
#ifdef ONEU_USE_DIRECTINPUT
		return ONEU_NEW DXControl;
#endif
	}

	ONEU_API void Aux_GameInit(pcwstr WindowName, uint32 width, uint32 height, bool bWindowed){
		IGame& g = GetGame();
		g.init(WindowName, width, height, bWindowed);

		g.getVideo().init(width, height, bWindowed);
		g.getAudio().init();
		g.getControl().init();
	}
}
