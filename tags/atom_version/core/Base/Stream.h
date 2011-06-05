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
 * @file Stream.h
 * @brief ���ӿڼ�һЩ���ߡ�
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
//level 2
#include "OneUPreDef.h"
#include "String.h"

namespace OneU
{
	//interface of ostream
	class IOStream;
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief �Զ��������������������
	 *
	 * ���ñ�����������������ĳ��ʱ������øú���ָ����ָ��ĺ���������Ϊ�������
	 */
	/* ----------------------------------------------------------------------------*/
	typedef IOStream& (*StreamSymbol_t)(IOStream& Target);
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief ������ӿ�
	 * @attention �ڼ̳�������������������flush��
	 */
	/* ----------------------------------------------------------------------------*/
	class IOStream
	{
	public:
		IOStream(){}
		virtual ~IOStream(){}
		virtual IOStream& operator <<(int) = 0;
		virtual IOStream& operator <<(float) = 0;
		virtual IOStream& operator <<(wchar) = 0;
		virtual IOStream& operator <<(char) = 0;
		virtual IOStream& operator <<(pcwstr) = 0;
		virtual IOStream& operator <<(pcstr) = 0;
		virtual IOStream& operator <<(void*) = 0;
		IOStream& operator <<(StreamSymbol_t v){return v(*this);}
		virtual void flush() = 0;
	};

	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief �����������
	 *
	 * �û��ɼ̳д��࣬��дoutput������flush����ѡ��������ʵ��һ��IOStream��
	 */
	/* ----------------------------------------------------------------------------*/
	class IOStreamMaker
		: public IOStream
	{
	public:
		virtual void output(pcwstr data) = 0;

		//��֤operator<<(StreamSymbol_t)�����ڸ�
		using IOStream::operator <<;
		virtual IOStream& operator <<(int v){
			output(String().format(L"%d", v).c_str());
			return *this;
		}
		virtual IOStream& operator <<(float v){
			output(String().format(L"%f", v).c_str());
			return *this;
		}
		virtual IOStream& operator <<(wchar v){
			output(String().format(L"%c", v).c_str());
			return *this;
		}
		virtual IOStream& operator <<(char v){
			output(String().format(L"%C", v).c_str());
			return *this;
		}
		virtual IOStream& operator <<(pcwstr v){
			output(v);
			return *this;
		}
		virtual IOStream& operator <<(pcstr v){
			output(String().format(L"%S", v).c_str());
			return *this;
		}
		virtual IOStream& operator <<(void* v){
			output(String().format(L"%p", v).c_str());
			return *this;
		}
		virtual void flush(){}
	};

	//@addtogroup group_ostream_manipulator Ԥ������������
	//@{
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief ʱ����Ϣ
	 */
	/* ----------------------------------------------------------------------------*/
	extern "C" ONEU_BASE_API IOStream& TimeInfo(IOStream& target);
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief ���з�
	 */
	/* ----------------------------------------------------------------------------*/
	extern "C" ONEU_BASE_API IOStream& endl(IOStream& target);
	//@}
}
