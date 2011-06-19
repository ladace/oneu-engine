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
#include "SurTex\SurTex.h"
#include < d3dx9.h >

namespace OneU
{
	namespace DX
	{
		extern uint32 s_Filter;
		extern uint32 s_MipFilter;

		template< uint32 _Usage, D3DPOOL _Pool >
		void CreateTextureFromFile( pcwstr pSrcFile, Texture_t< _Usage, _Pool > & txTexture,
			uint32 Level, PXLFORMAT Format, COLOR crColorKey = 0 )
		{
			IDirect3DTexture9 * pITexture = 0;

			HRESULT hr;
			if( FAILED( hr = ::D3DXCreateTextureFromFileEx(_pD3DDevice, pSrcFile, 0, 0, Level, _Usage, static_cast< D3DFORMAT > ( Format ), _Pool,
				s_Filter, s_MipFilter, crColorKey, NULL, NULL,  & pITexture ) ) )
			{
				GetLogger().stream() << TimeInfo << L"���ļ���������ʧ�ܣ�\n�ļ�����" << pSrcFile
					<< L"\nDX����" << DXERRGET_STR(hr) << L"\n";
				ONEU_RAISE(String().format(L"�޷���ȡͼƬ��\n·����%s\nDX����%s", pSrcFile, DXERRGET_STR(hr)).c_str());
			}

			txTexture._Create( pITexture );
		}
		template< uint32 _Usage, D3DPOOL _Pool >
		void CreateTextureFromMemory(LPVOID pSrcData, uint32 SrcDataSize, Texture_t< _Usage, _Pool > & txTexture,
			uint32 Level, PXLFORMAT Format, COLOR crColorKey = 0)
		{
			IDirect3DTexture9 * pITexture = 0;

			DXCHECK_RAISE( ::D3DXCreateTextureFromFileInMemoryEx( _pD3DDevice, pSrcData, SrcDataSize, 0, 0, Level, _Usage, static_cast< D3DFORMAT > ( Format ), _Pool,
				s_Filter, s_MipFilter, crColorKey, NULL, NULL, & pITexture ),
				L"���ڴ洴������ʧ�ܣ�" );

			txTexture._Create( pITexture );
		}
		template< D3DPOOL _Pool >
		void LoadSurfaceFromFile( pcwstr pFileName, Surface_t< _Pool > &Surface, RECT *pDestRect = 0, RECT *pSrcRect = 0, COLOR crColorKey = 0 )
		{
			DXCHECK_RAISE( ::D3DXLoadSurfaceFromFile( Surface._Obtain(), NULL, pDestRect, pFileName, pSrcRect, s_Filter, crColorKey, NULL ),
				L"��ȡ�ļ�������ʧ�ܣ�");
		}
		template< uint32 _Usage, D3DPOOL _Pool >
		void LoadSurfaceFromFile( pcwstr pFileName, Surface_Texture< _Usage, _Pool > &Surface, RECT *pDestRect = 0, RECT *pSrcRect = 0, COLOR crColorKey = 0 )
		{
			DXCHECK_RAISE( ::D3DXLoadSurfaceFromFile( Surface._Obtain(), NULL, pDestRect, pFileName, pSrcRect, s_Filter, crColorKey, NULL ),
				L"��ȡ�ļ�������ʧ�ܣ�");
		}
	}
}