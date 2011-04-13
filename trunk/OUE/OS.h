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
 * @file OS.h
 * @brief ����ϵͳ������
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once

#include "OUEDefs.h"
#include "../Base/Interface.h"
#include <windows.h>

#ifndef _WIN32
#pragma message("Error!This is not Win32 OS.")
#endif


namespace OneU
{
	namespace os
	{
		/** 
		* @name Windows��װ��
		* @{ */

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
			uint wYear; 
			uint wMonth; 
			uint wDayOfWeek; 
			uint wDay; 
			uint wHour; 
			uint wMinute; 
			uint wSecond; 
			uint wMilliseconds; 
		}SYSTEMTIME;


		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ˯��
		* 
		* @param dwMilliseconds ˯��ʱ�䣬�Ժ����
		*/
		/* ----------------------------------------------------------------------------*/
		ONEU_API void Sleep(dword dwMilliseconds);
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ��ȡ���ʱ��
		*
		* һ���̶��ϲ�׼ȷ
		* 
		* @return ���ʱ���ֵ
		*/
		/* ----------------------------------------------------------------------------*/
		ONEU_API dword GetTime();
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ��ȡϵͳʱ��
		* 
		* @param pSystemTime ָ��ϵͳʱ��ṹ���ָ��
		*
		* @sa SYSTEMTIME
		*/
		/* ----------------------------------------------------------------------------*/
		ONEU_API void GetSystemTime(SYSTEMTIME * pSystemTime);
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ���������ʾ״̬
		* 
		* @param bShow ΪTRUE�����ʾ��ΪFALSE������ء�
		*/
		/* ----------------------------------------------------------------------------*/
		ONEU_API void ShowCursor(bool bShow);
		/* ----------------------------------------------------------------------------*/
		/**
		* @brief �������λ��
		*
		* @param X ���X����
		* @param Y ���Y����
		* @remarks ���갴����Ļ����Ϊ��λ������GDI������ϵ(ԭ�������ϣ�������ֱ�Ϊ�º��ң���
		*/
		/* ----------------------------------------------------------------------------*/
		ONEU_API void SetCursorPos(int X, int Y);
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ��ȡ��ǰĿ¼λ��
		* 
		* @return ָ��Ŀ¼λ���ַ�����ָ��
		*/
		/* ----------------------------------------------------------------------------*/
		ONEU_API wchar * GetDirectory();

		/* ----------------------------------------------------------------------------*/
		/**
		* @brief ��������Ի���
		*
		* @param Errorinfo �Ի�����ʾ�Ĵ�����Ϣ
		*/
		/* ----------------------------------------------------------------------------*/
		ONEU_API void ErrorBox(pcwstr Errorinfo);

		ONEU_API float Rand();
		/**  @} */

	}
}
