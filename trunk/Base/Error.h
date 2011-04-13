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
 * @file Error.h
 * @brief ������
 * @author Ladace
 * @version 1.0.0.1
 * @date 2009-11-11
 * level 1
 */

#pragma once

#include "OneUPreDef.h"
#include "String.h"

#include <errno.h>

/* ----------------------------------------------------------------------------*/
/**
 * @brief �����ַ���
 * 
 * �����������ַ�����
 * @param str �ַ���
 */
/* ----------------------------------------------------------------------------*/
#ifdef _DEBUG
#define TRACE(str) DumpString(str)

namespace OneU
{
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief �����������ַ���
	 * 
	 * @param str �ַ���ָ��
	 */
	/* ----------------------------------------------------------------------------*/
	extern "C" ONEU_BASE_API void DumpString(pcwstr str);

	extern "C" ONEU_BASE_API pcwstr GetErrnoString( errno_t Errno );
}

#else
#define TRACE(str) void(0)
#endif


/* ----------------------------------------------------------------------------*/
/** 
 * @brief ��¼��Ϣ
 * 
 * @param str ��Ϣ�ַ���ָ��
 */
/* ----------------------------------------------------------------------------*/
#define ONEU_LOG(str)    GetLogger().stream() << TimeInfo << '\n' << str << '\n';
/* ----------------------------------------------------------------------------*/
/** 
 * @brief д����Ϣ
 * 
 * @param str ��Ϣ�ַ���ָ��
 */
/* ----------------------------------------------------------------------------*/
#define LOGMSG(str) GetLogger().stream() << str << '\n';

namespace OneU
{
	extern "C" ONEU_BASE_API void _TerminateApp(const char * FileName, const int Line, pcwstr str);

	inline void _TerminateApp(const char * FileName, const int Line, pcstr str){
		_TerminateApp(FileName, Line, ANSI2Wide(str));
	}

	typedef void (*TerminateHandler)();

	//ֻ�е���ONEU_EXIT(_ExitApp)�Ż����Handler
	extern "C" ONEU_BASE_API TerminateHandler SetTerminateHandler(TerminateHandler eh);

	//���Ϊfalse��������
	inline void _Ensure(const char* FileName, const int Line, const char* expression, bool exp){
		if(!exp)
			_TerminateApp(FileName, Line, String().format(L"The ensured expression '%S' equal to false!", expression).c_str());
	}
}

//��ִ��TernimateHandler
//������ȫ�ֶ���
#define ONEU_RAISE(description) OneU::_TerminateApp(__FILE__, __LINE__, description)

#define ONEU_ENSURE(exp) OneU::_Ensure(__FILE__, __LINE__, #exp, exp)//��ASSERT��ͬ �ڷ����汾Ҳ��ִ�еĴ��� ���Ϊfalse��������
