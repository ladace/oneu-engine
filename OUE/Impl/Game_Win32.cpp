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
#include "Win32.h"
#include "../OS.h"
#include "Game_Win32.h"
#include "../Event.h"
#include "../Broadcast.h"
#include "../Video.h"
#include "../Stereo.h"
#include "../Scene.h"
#include "../Control.h"
#include "../Atom.h"
#include "Shell.h"
#include "../atom_export/AtomExport.h"

namespace OneU
{
	HWND Window_create(pcwstr pWndName, bool bPopUp, int iX, int iY, int iWidth, int iHeight);
}

namespace OneU
{
	Game_Win32::~Game_Win32(){
		if(m_pScene != NULL){ m_pScene->destroy(); m_pScene = NULL;}
		//GetAtom().unloadAllAtomLib();
		Atom_destroy();
		if(m_pBroadcast != NULL) m_pBroadcast->sendEvent(event::DESTROY);
		if(m_pControl != NULL){ m_pControl->destroy(); m_pControl = NULL;}
		if(m_pStereo != NULL){ m_pStereo->destroy(); m_pStereo = NULL; }
		if(m_pVideo != NULL){ m_pVideo->destroy(); m_pVideo = NULL;}
		if(m_pBroadcast != NULL){ m_pBroadcast->destroy(); m_pBroadcast = NULL;}
	}
	void Game_Win32::init(pcwstr WindowName, uint width, uint height, bool bWindowed){
		//��ʼ���������
		srand(::GetTickCount());
		//�����㲥ϵͳ
		ASSERT(m_pBroadcast == NULL);
		if(m_pBroadcast != NULL) m_pBroadcast = m_BroadcastFactory();
		else m_pBroadcast = BroadCast_create();

		//ps.ĿǰAtom������ϵͳģ�����ٵġ��߼���Atomֻ����߲㣨Ӧ������ϵͳģ�齨������Ŀǰ��Ϊ�˵���ϵͳ�������㡣
		//�����������ϵͳģ�����ٺͽ�����ʱ���ܹ�ʹ��Atom�⣬����Atom������ϵͳģ�齨����
		//���ڴ˴�Ϊ�������µ�ȫ�ֱ���Ϊ�˺����ı��ڷ��ſ����漰��ϵͳ��Դ�����Ը�ȫ�ֱ���ϵͳģ������ǰ���٣��������Ͼɵ�ȫ�ֱ�
		//���ϵͳģ�����ٺ�������ATOM���������һ��Ľ��������
		Atom_build();

		//�趨��ȫ�ֱ���
		g_hInstance = GetModuleHandle(NULL);

		//��������
		Window_create(WindowName, !bWindowed, 0, 0, width, height);
		ASSERT(m_pVideo == NULL);
		if(m_VideoFactory != NULL) m_pVideo = m_VideoFactory();
		else m_pVideo = Video_create();

		m_pVideo->init(width, height, bWindowed);

		if(m_StereoFactory != NULL) m_pStereo = m_StereoFactory();
		else m_pStereo = Stereo_create();
		m_pStereo->init();

		ASSERT(m_pControl == NULL);
		if(m_ControlFactory != NULL) m_pControl = m_ControlFactory();
		else m_pControl = Control_create();

		//Atom���׼��
		AtomExport();

		//shell��ʼ��
		m_pShell = tool::Shell_config();
		showInfo();
		m_pVideo->showInfo();
	}
	int Game_Win32::run(){
		while(true){
			MSG msg;

			while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
				if(msg.message == WM_QUIT) goto end;
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}

			try{
				OneU::os::Sleep(1);
				this->onFrame();
			}
			catch(...){
				ONEU_LOG(L"����ʱ���������˳���");
				Game_destroy();

				return -1;
			}
		}
end:
		Game_destroy();
		return 0;
	}
	void Game_Win32::quit(){
		PostQuitMessage(0);
	}


	IScene* Game_Win32::replaceScene( IScene* newscene )
	{
		if(newscene == m_pScene) return NULL;
		IScene* ret = m_pScene;
		m_pScene = newscene;

		m_pVideo->setRenderScene(newscene->getRenderScene());
		return ret;
	}


	void Game_Win32::onFrame(){
		if(!m_bActive) return;
		GetAtom().gc();

		//����FPS
		++m_Frames;
		if(m_lastTime != 0){
			dword now = ::timeGetTime();
			m_TimeInterval = float(now - m_lastTime);
			if(m_TimeInterval > 1000){
				m_lastTime = now;
				m_FPS = ((float)m_Frames) / m_TimeInterval * 1000.0f;
				m_Frames = 0;
			}
		}
		else m_lastTime = ::timeGetTime();

		m_pControl->update();
		m_pBroadcast->sendEvent(event::ENTER_FRAME);
		if(m_pScene != NULL) m_pScene->update();
		m_pVideo->update();
		m_pVideo->render();
		m_pVideo->flip();
	}
	void Game_Win32::onActiveWindow(bool bActive){
		m_bActive = bActive;
		m_lastTime = 0;
		if(m_bActive)
			m_pBroadcast->sendEvent(event::WINDOW_ACTIVE);
		else m_pBroadcast->sendEvent(event::WINDOW_DEACTIVE);
	}

	void Game_Win32::setWindowTitle(pcwstr title){
		SetWindowTextW(g_hWnd,title);
	}

	float Game_Win32::getFPS(){
		return m_FPS;
	}
	float Game_Win32::getTimeInterval(){
		return m_TimeInterval;
	}

	void Game_Win32::runShell( pcwstr command ){
		m_pShell->runCommand(command);
	}
	void Game_Win32::output( pcwstr data ){
		m_pShell->output(data);
	}

	void Game_Win32::showInfo()
	{
		stream() << TimeInfo << L"OneU 1.0.0.1 Ladace 2011\nWin32 OS\n\n";
	}

}

#include "WinException.h"

#pragma comment( lib, "winmm.lib" )
namespace OneU
{
	/** 
	* @name Windows����
	* @{ */

	/* ----------------------------------------------------------------------------*/
	/** 
	* @brief ����������
	*/
	/* ----------------------------------------------------------------------------*/
	const wchar_t * szClassName = L"��������";

	HINSTANCE g_hInstance = NULL;
	static HINSTANCE g_hPrevInstance = NULL;
	HWND g_hWnd = NULL;

	/* ----------------------------------------------------------------------------*/
	/** 
	* @brief ��Ϣ������
	*/
	/* ----------------------------------------------------------------------------*/
	LRESULT CALLBACK WindowProcedure(HWND hWnd, uint message, WPARAM wParam, LPARAM lParam);

	/* ----------------------------------------------------------------------------*/
	/** 
	* @brief ��ʼ�����ں���
	*/
	/* ----------------------------------------------------------------------------*/
	HWND Window_create(pcwstr pWndName, bool bPopUp, int iX, int iY, int iWidth, int iHeight){
		ASSERT(g_hInstance != NULL);

		WNDCLASSEX wincl;

		wincl.hInstance = g_hInstance;
		wincl.lpszClassName = szClassName;
		wincl.lpfnWndProc = WindowProcedure;      
		wincl.style = CS_DBLCLKS;                 
		wincl.cbSize = sizeof(WNDCLASSEX);

		wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
		wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
		wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
		wincl.lpszMenuName = NULL;                 
		wincl.cbClsExtra = 0;                      
		wincl.cbWndExtra = 0;
		wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

		if (!::RegisterClassEx(&wincl)){
			ONEU_LOG( L"ע�ᴰ����ʧ��" );
			ONEU_RAISE(WinException( ::GetLastError()));
		}

		ASSERT(g_hWnd == NULL);
		g_hWnd = ::CreateWindowEx(
			0,
			szClassName,
			pWndName ? pWndName : L"��������",
			bPopUp ? WS_POPUP : WS_OVERLAPPEDWINDOW,
			iX,
			iY,
			iWidth,
			iHeight,
			HWND_DESKTOP,
			NULL,
			g_hInstance,
			NULL
			);

		if(!g_hWnd){
			ONEU_LOG(L"��������ʧ��");
			ONEU_RAISE(WinException(::GetLastError()));
		}

		::ShowWindow (g_hWnd, SW_SHOW);

		return g_hWnd;
	}


	LRESULT CALLBACK WindowProcedure (HWND hwnd, uint message, WPARAM wParam, LPARAM lParam){
		switch (message){
			case WM_DESTROY:
				::PostQuitMessage (0);
				break;
				//����ע�⣺�����Ϣ����DXĳ������������bug���������DefWindowProcǰ̨����ᱻ���ɰ�ɫ��
			case WM_ERASEBKGND:
				break;
			case WM_ACTIVATE:
				if( LOWORD( wParam ) == WA_ACTIVE || LOWORD( wParam ) == WA_CLICKACTIVE )
					GetGame().onActiveWindow(true);
				else
					GetGame().onActiveWindow(false);
				break;
			case WM_CHAR:
				{
					IEventDispatcher* pED = GetGame().getInputFocus();
					if(pED) pED->sendEvent(event::CHAR, &event::CharArgs((::WCHAR)wParam));
					break;
				}
			default:
				return ::DefWindowProc( hwnd, message, wParam, lParam );
		}

		return 0;
	}
	/**  @} */
}