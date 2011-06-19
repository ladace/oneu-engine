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
 * @file DXDefs.h
 * @brief DX��������
 * 
 * ����һЩ����DX����Ļ�������DXGraphics��DXInput֮�£������޴��ɷŷŵ��˵ײ㡣
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-10
 */
#pragma once

#include <windows.h>
#include <dxerr.h>

#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxerr9.lib" )

#define SAFE_RELEASE( ptr ) OneU::DX::SafeRelease( ptr )

#define DXERRGET_STR(hr) ::DXGetErrorDescription(hr)
#define ONEU_LOG_DXERR(hr) ONEU_LOG(::DXGetErrorDescription(hr))

namespace OneU
{
	namespace DX
	{
		template < class T >
		inline void SafeRelease( T *& ptr ){
			if( ptr ){
				ptr->Release();
				ptr = NULL;
			}
		}
	}
}
#define RAISE_HRESULT(hr) ONEU_RAISE(::DXGetErrorDescription(hr))
//���DX��HRESULT����ֵ ���д�����¼����־ �����������
#define DXCHECK( fn, str ) {\
	HRESULT hr;\
	if( FAILED( hr = fn ) ) {\
	GetLogger().stream(ILogger::ML_CRITICAL) << __FILE__ << ':' << __LINE__ << '\n' << str << '\n' << ::DXGetErrorDescription( hr );\
	}\
}void( 0 )/*@��¼��ʽ���ÿ� ���ع�*/

//���DX��HRESULT����ֵ ���д�����¼����־ �����׳�����
#define DXCHECK_RAISE( fn, str ) {\
	HRESULT hr;\
	if( FAILED( hr = fn ) ){\
		ONEU_LOG( str );\
		RAISE_HRESULT(hr);\
}\
}void( 0 )
#define XV( fn ) DXCHECK( fn, #fn )
#define XV_RAISE( fn ) DXCHECK_RAISE( fn, #fn );
#ifdef _DEBUG
//���ڵ��԰汾��鷵��ֵ �����汾������
#define DXCHECK_DEBUG( fn, str ) DXCHECK( fn, str )

//���ڵ��԰汾��鷵��ֵ �����汾������
#define XV_DEBUG( fn ) DXCHECK_DEBUG( fn, #fn )
#else
#define DXCHECK_DEBUG( fn, str ) fn;
#define XV_DEBUG( fn ) fn;
#endif
namespace OneU
{
	/* ----------------------------------------------------------------------------*/
	/*@cond INTERNAL_MPL*/
	/*@todo λ�ò�̫��*/
	/* ----------------------------------------------------------------------------*/
	//�ֱ��ʾTRUE FALSE
	struct __True_Category{};
	struct __False_Category{};

	template< bool boolean >
	struct __Bool_Category
	{
	};
	template<>
	struct __Bool_Category< true >
	{
		typedef __True_Category Category;
	};
	template<>
	struct __Bool_Category< false >
	{
		typedef __False_Category Category;
	};
	/* ----------------------------------------------------------------------------*/
	/*@endcond*///INTERNAL_MPL
}
