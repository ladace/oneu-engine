#pragma once


#include "BaseLayer.h"
#include <windows.h>
#include "WinException.h"
#include "File.h"

namespace OneU
{
	extern HINSTANCE g_hInstance;
	extern HWND g_hWnd;
	//�����ʼ���ṹ��
	/** 
	 * @name Windows��װ��
	 * @{ */
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ���ڳ�ʼ���ṹ��
	 */
	/* ----------------------------------------------------------------------------*/
	typedef struct tagONEU_INITWIN
	{
		int iX;
		int iY;
		int iWidth;
		int iHeight;
		bool bPopUp;
		WCHAR *pWndName;
	} ONEU_INITWIN;

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ȫ�ִ��ڳ�ʼ���ṹ��
	 *
	 * Ӧ��OneUPreInitWin�����ýṹ��
	 * @sa OneUPreInitWin
	 */
	/* ----------------------------------------------------------------------------*/
	extern ONEU_INITWIN OneU_InitWin;

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ϵͳʱ��ṹ��
	 *
	 * ����GetSystemTime�����Ĳ�������
	 * @sa GetSystemTime
	 */
	/* ----------------------------------------------------------------------------*/
	typedef struct tagSystemTime
	{
		WORD wYear; 
		WORD wMonth; 
		WORD wDayOfWeek; 
		WORD wDay; 
		WORD wHour; 
		WORD wMinute; 
		WORD wSecond; 
		WORD wMilliseconds; 
	}SYSTEMTIME;

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ���
	 */
	/* ----------------------------------------------------------------------------*/
	class Handle
	{
	private:
		::HANDLE m_h;
	public:
		typedef ::HANDLE Type;
		Handle() : m_h( 0 ){}
		Handle( ::HANDLE h ) : m_h( h ){}
		HANDLE GetHandle(){ return m_h; }
	};
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ���ھ��
	 */
	/* ----------------------------------------------------------------------------*/
	class HWindow
		: public Handle
	{
	private:
		::HWND m_hWnd;
	public:
		typedef ::HWND Type;
		HWindow() : m_hWnd( 0 ){}
		HWindow( HWND hWnd ) : m_hWnd( hWnd ){}
		HWND GetHWnd(){ return m_hWnd; }
	};

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ���̾��
	 */
	/* ----------------------------------------------------------------------------*/
	class HInstance
		: public Handle
	{
	private:
		::HINSTANCE m_hInstance;
	public:
		typedef ::HINSTANCE Type;
		HInstance() : m_hInstance( 0 ){}
		HInstance( HINSTANCE hInst ) : m_hInstance( hInst ){}
		HINSTANCE GetHInstance(){ return m_hInstance; }
	};

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief �豸��������
	 */
	/* ----------------------------------------------------------------------------*/
	class HDeviceContext
		: public Handle
	{
	private:
		::HDC m_hDC;
	public:
		typedef ::HDC Type;
		HDeviceContext() : m_hDC( 0 ){}
		HDeviceContext( HDC hDC ) : m_hDC( hDC ){}
		HDC GetHDC(){ return m_hDC; }
	};

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ���ڻ�ͼ��
	 */
	/* ----------------------------------------------------------------------------*/
	class PaintDC
	{
	private:
		HDeviceContext m_hDC;
		HWindow m_hWnd;
	public:
		PaintDC( HWindow hWnd = g_hWnd )
		{
			::GetDC( hWnd.GetHWnd() );
			m_hWnd = hWnd;
		}
		~PaintDC()
		{
			::ReleaseDC( m_hWnd.GetHWnd(), m_hDC.GetHDC() );
		}
		HDeviceContext GetDeviceContext(){ return m_hDC; }
	};

	
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief �˳�����
	 */
	/* ----------------------------------------------------------------------------*/
	inline void Quit(){ PostQuitMessage( 0 ); }
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ˯��
	 * 
	 * @param dwMilliseconds ˯��ʱ�䣬�Ժ����
	 */
	/* ----------------------------------------------------------------------------*/
	inline void Sleep( DWORD dwMilliseconds ){ ::Sleep( dwMilliseconds ); }
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ȡ���ʱ��
	 *
	 * һ���̶��ϲ�׼ȷ
	 * 
	 * @return ���ʱ���ֵ
	 */
	/* ----------------------------------------------------------------------------*/
	inline DWORD GetTime(){ return ::timeGetTime(); } 
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ȡϵͳʱ��
	