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
#pragma comment( lib, "dinput8.lib" )

#include "DXInput.h"

namespace OneU
{
	namespace DX
	{
		IDirectInput8 *_pDInput = 0;

		static HWND s_hWnd = NULL;

		Input_cls* const GetInput()
		{
			static Input_cls instance;
			return &instance;
		}

		Input_cls& Input = *GetInput();

		void Input_cls::Init(HINSTANCE hInstance, HWND hWnd)
		{
			DXCHECK_THROW( DirectInput8Create( hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast< void ** >( &_pDInput ), NULL ), L"��ʼ������ʧ�ܣ�" );
			s_hWnd = hWnd;
		}

		void InputDevice::Create(uint32 BufferSize)
		{
			ONEU_ASSERT(m_pDIDevice == NULL);

			Init(BufferSize);

			DXCHECK_THROW(m_pDIDevice->SetCooperativeLevel( s_hWnd, DISCL_BACKGROUND|DISCL_NONEXCLUSIVE ), L"���������豸Э������ʧ�ܣ�");
				
			if(BufferSize)
			{
				//���û�������С ʹ�豸�ܹ��û���ģʽ����
				DIPROPDWORD dp;
				dp.diph.dwSize = sizeof(DIPROPDWORD);
				dp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
				dp.diph.dwObj = 0;
				dp.diph.dwHow = DIPH_DEVICE;
				dp.dwData = BufferSize;
				DXCHECK(m_pDIDevice->SetProperty(DIPROP_BUFFERSIZE, &dp.diph), L"���������豸��������Сʧ�ܣ�");
			}
		}
		void InputDevice::Read( void *DataBuffer, uint32 BufferSize )
		{
			while( TRUE )
			{
				HRESULT hr;

				if( SUCCEEDED( hr = m_pDIDevice->GetDeviceState( BufferSize, DataBuffer ) ) )
					break;

				if( hr != DIERR_INPUTLOST && hr != DIERR_NOTACQUIRED )
					THROW_HRESULT(hr);

				if( FAILED( m_pDIDevice->Acquire() ) )
					THROW_HRESULT(hr);
			}
		}
		bool InputDevice::GetData( DataType *Buffer, uint32& dwElements )
		{
			while( TRUE )
			{
				HRESULT hr;
				if( SUCCEEDED( hr= m_pDIDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), Buffer, &dwElements, 0 ) ) )
				{
					if( hr == DI_BUFFEROVERFLOW ) return TRUE;
					else return FALSE;
				}

				// ������һ������ ����
				// ��������п����� DI_BUFFEROVERFLOW �������������
				// �����������ִ��󣬶���ζ��ͬ�����豸����ϵ����ʧ��

				// ���ִ�������������صĺ����������㰴��һ������δ�ɿ�ʱ
				// �����˴��󣬾ͻᶪʧ�����ɿ��ü�����Ϣ������һ������ĳ���
				// �Ϳ�����Ϊ�ü���δ���ɿ����Ӷ�����һЩ���벻�������

				// ������δ��벢δ����ô���

				// ����������һ���취�ǣ��ڳ������ִ���ʱ����ȥ����һ��
				// GetDeviceState()��Ȼ��ѽ��ͬ�����������¼��״̬����
				// �Ƚϣ��Ӷ��������ܷ����Ĵ���

				if( hr != DIERR_INPUTLOST && hr != DIERR_NOTACQUIRED )
					THROW_HRESULT(hr);

				if( FAILED( m_pDIDevice->Acquire() ) )
					THROW_HRESULT(hr);

			}
		}

		void InputDevice::HandleData( DataHandler Fn )
		{
			uint32 dwElements = DATA_BUFFER_SIZE;
			static DataType Buffer[ DATA_BUFFER_SIZE ];
			bool bOverFlow;
			do
			{
				bOverFlow = GetData( Buffer, dwElements );
				for( unsigned long i = 0; i < dwElements; i++ )
				{
					( *Fn )( Buffer[i].dwOfs, Buffer[i].dwData, Buffer[i].dwTimeStamp, Buffer[i].dwSequence );
				}
			}while( bOverFlow );
		}

		void KeyBoard::Init( uint32 BufferSize )
		{
			DXCHECK_THROW( _pDInput->CreateDevice( GUID_SysKeyboard, &m_pDIDevice, NULL ), L"�������������豸ʧ�ܣ�" );

			DXCHECK_THROW( m_pDIDevice->SetDataFormat( &c_dfDIKeyboard ), L"���ü��������豸���ݸ�ʽʧ�ܣ�" );

		}

		void Mouse::Init( uint32 BufferSize )
		{
			DXCHECK_THROW( _pDInput->CreateDevice( GUID_SysMouse, &m_pDIDevice, NULL ), L"������������豸ʧ�ܣ�" );

			DXCHECK_THROW( m_pDIDevice->SetDataFormat( &c_dfDIMouse ), L"������������豸���ݸ�ʽʧ�ܣ�" );
		}
	}
}