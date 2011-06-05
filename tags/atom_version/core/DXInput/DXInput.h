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
 * @file DXInput.h
 * @brief ����ϵͳͷ�ļ�
 * @author Ladace
 * @version 1.0.0.1
 * @date 2010-02-10
 */
#pragma once
#include "../Base/Base.h"

//�ڶ�����Base.h֮���ͷ�ļ��Ż��������
#ifdef __ONEU_USE_DIRECTINPUT

#include "../Base/Internal/DXDefs.h"
#include "InputConst.h"//include <dinput.h>

//#ifdef ONEU_DLL
#ifdef ONEU_EXPORTS
#define ONEU_DXINPUT_API __declspec(dllexport)
#else
#define ONEU_DXINPUT_API __declspec(dllimport)
#endif
//#else
//#define ONEU_DXINPUT_API
//#endif

namespace OneU
{
	namespace DX
	{
		/*@cond INTERNAL_IMPL*/
		extern IDirectInput8 *_pDInput;
		/*@endcond*///INTERNAL_IMPL

		//ǰ������
		class Input_cls;
		Input_cls * const GetInput();
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ȫ��Ψһ����ģ�����
		*/
		/* ----------------------------------------------------------------------------*/
		extern Input_cls& Input;

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ����ϵͳ
		 */
		/* ----------------------------------------------------------------------------*/
		class Input_cls
		{
		public:
			Input_cls()
			{
				ONEU_ASSERT( _pDInput == NULL );
			}
			~Input_cls()
			{
				Destroy();
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ʼ������ϵͳ
			 */
			/* ----------------------------------------------------------------------------*/
			void Init(HINSTANCE hInstance, HWND hWnd);
			void Destroy()
			{
				SAFE_RELEASE( _pDInput );
			}
		};

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �����豸
		 */
		/* ----------------------------------------------------------------------------*/
		class InputDevice
		{
		protected:
			IDirectInputDevice8 *m_pDIDevice;
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ʼ��
			 *
			 * ���������า�ǣ����Ƴ�ʼ������
			 * һ�㲻��Ҫ�ͻ����á�
			 * 
			 * @param BufferSize ��������С
			 */
			/* ----------------------------------------------------------------------------*/
			virtual void Init( uint32 BufferSize = 0 ) = 0;
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����ģʽ
			 *
			 * �洢�����¼��Ľṹ�塣Ӧ����һ��DataType����������һ����������
			 */
			/* ----------------------------------------------------------------------------*/
			typedef DIDEVICEOBJECTDATA DataType;
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �������ݴ�����
			 * 
			 * @param dword ��ʾ��Ӧ��λ��ID
			 * @param dword ��ʾ��λ��״̬
			 * @param dword ��ʾ�¼�������ʱ��
			 * @param dword ��ʾ�¼���һ���¼������е�λ��
			 *
			 */
			/* ----------------------------------------------------------------------------*/
			typedef void ( *DataHandler )( uint32, uint32, uint32, uint32 );
			static const int DATA_BUFFER_SIZE = 128;
			InputDevice()
				: m_pDIDevice( NULL )
			{
				//��Input�ȹ���
				GetInput();
			}
			~InputDevice()
			{
				Destroy();
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �����豸
			 *
			 * ���ڲ�������Init��
			 * 
			 * @param BufferSize ��������С��������Data�Ĵ�С��DXSDKδ˵����ʲô��λ������
			 *
			 * ��Ϊ0���ʾ��ʹ�û���ģʽ��
			 * @remarks ���BufferSize�趨�����豸֧�ֵĴ�С�����ʹ���豸�����֧�ֵĴ�С��
			 */
			/* ----------------------------------------------------------------------------*/
			void Create( uint32 BufferSize = 0 );
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ�����豸
			 *
			 * ���趨�����豸�����в���ִ�У�ʹ���豸��
			 */
			/* ----------------------------------------------------------------------------*/
			void Acquire()
			{
				DXCHECK_THROW( m_pDIDevice->Acquire(), L"��ȡ�����豸ʧ�ܣ�" );
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ѯ�豸
			 *
			 * ֻ����Ϸ����Ҫ�ò������ڻ�ȡ����ģʽ����֮ǰӦ����ѯ��
			 * һ�㲻��Ҫ�ͻ�ʹ�á�
			 */
			/* ----------------------------------------------------------------------------*/
			void Poll()
			{
				m_pDIDevice->Poll();
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ��ǰ״̬
			 *
			 * ����ģʽ������ʽ
			 * 
			 * @param DataBuffer ������
			 * @param BufferSize ��������С ���ֽڼ�
			 *
			 * һ�㲻��Ҫ�ͻ����á��������������صķ�����
			 */
			/* ----------------------------------------------------------------------------*/
			void Read( void *DataBuffer, uint32 BufferSize );
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ����ģʽ����
			 *
			 * һ�㲻Ҫ�ͻ�ֱ�ӵ��á�
			 * 
			 * @param Buffer ʱ�仺����
			 * @param dwElements ���뻺������С����������Ĵ�С�������ֽ����������ػ�õ��¼�������
			 * 
			 * @returns �������Ƿ�����������������������TRUE�����򷵻�FALSE��
			 */
			/* ----------------------------------------------------------------------------*/
			bool GetData( DataType *Buffer, uint32& dwElements );
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ������ģʽ����
			 *
			 * �ûص�����������ģʽ���ݡ�
			 * 
			 * @param Fn ������
			 *
			 * @sa DataHandler
			 */
			/* ----------------------------------------------------------------------------*/
			void HandleData( DataHandler Fn );
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �ͷ��豸
			 */
			/* ----------------------------------------------------------------------------*/
			void Destroy()
			{
				if( m_pDIDevice ) m_pDIDevice->Unacquire();
				SAFE_RELEASE( m_pDIDevice );
			}
		};

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���������豸
		 */
		/* ----------------------------------------------------------------------------*/
		class KeyBoard
			: public InputDevice
		{
		private:
			void Init( uint32 BufferSize = 0 );
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ״̬����
			 *
			 * ����������ģʽ�¶�ȡ״̬
			 */
			/* ----------------------------------------------------------------------------*/
			class State
			{
				char m[256];
				friend class KeyBoard;
			public:
				//TRUE��ʾ����
				bool GetState( uint32 KeyCode ) const
				{
#pragma warning(push)
#pragma warning(disable : 4800)
					return m[KeyCode] & 0x80;
#pragma warning(pop)
				}
			};

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����ǰ״̬
			 *
			 * ����ģʽ������ʽ
			 * 
			 * @param KeyBoardState ״̬����
			 */
			/* ----------------------------------------------------------------------------*/
			void Read( State &KeyBoardState )
			{
				InputDevice::Read( KeyBoardState.m, 256 );
			}
		};

		class Mouse
			: public InputDevice
		{
		private:
			void Init( uint32 BufferSize = 0 );
		public:
			class State
			{
				DIMOUSESTATE m;
				friend class Mouse;
			public:
				//TRUE��ʾ����
				bool GetState( uint32 KeyCode ) const
				{
#pragma warning(push)
#pragma warning(disable : 4800)
					return (bool)(m.rgbButtons[ KeyCode ] & 0x80);
#pragma warning(pop)
				}
				LONG GetlX() const
				{
					return m.lX;
				}
				LONG GetlY() const
				{
					return m.lY;
				}
				LONG GetlZ() const
				{
					return m.lZ;
				}
			};
			void Read( State &MouseState )
			{
				InputDevice::Read( &MouseState.m, sizeof( MouseState ) );
			}
		};
	}
}
#endif