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
 * @file String.h
 * @brief �ַ���
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
//level 0
#include "OneUPreDef.h"
#include <cstdio>
#include <cstring>
#include <cstdarg>

namespace OneU
{
	class String
	{
		IAllocator& allocator;
		size_t buf_size, m_len;
		wchar* m_buf;

		//��buf_size��Ա����������size ��ѭһ������
		void _mem_align(size_t size){
			while(buf_size < size) buf_size = (buf_size << 1) + 1;
		}
		//��������һ�����size�����ڴ棨���´�����ڴ����ݣ�
		void _new_buffer(size_t size){
			if(m_buf != NULL) allocator.dealloc(m_buf);
			_mem_align(size);
			m_buf = (wchar*)allocator.alloc(buf_size * sizeof(wchar), __FILE__, __LINE__);
			if(m_buf == NULL) buf_size = 0;//�����ڴ�ʧ��
		}
	public:
		String()
			: allocator(GetAllocator()), buf_size(0), m_len(0), m_buf(NULL){}
		~String(){
			if(m_buf != NULL) allocator.dealloc(m_buf);
		}
		void eval(pcwstr str){
			m_len = wcslen(str);
			if(m_len + 1 > buf_size)
				_new_buffer(m_len + 1);

			if(m_buf == NULL) return;//�����ڴ�ʧ��
			wcscpy(m_buf, str);
		}
		void append(pcwstr str){
			const size_t l = wcslen(str);
			if(m_len + l + 1 > buf_size){
				wchar* old_buf = m_buf;
				_mem_align(m_len + l + 1);
				m_buf = (wchar*)allocator.alloc(buf_size * sizeof(wchar), __FILE__, __LINE__);
				if(old_buf != NULL){
					wcscpy(m_buf, old_buf);
					allocator.dealloc(old_buf);
				}
				//��������ڴ�ʧ�� �����κ���
				if(m_buf == NULL){ buf_size = 0; return;}
			}
			wcscpy(m_buf + m_len, str);
			m_len = m_len + l;
		}
		void append(wchar ch){
			wchar t[2];
			t[0] = ch; t[1] = 0;
			append(t);
		}
		void reverse(){
			wchar *b = m_buf, *e = m_buf;
			while(*e != 0)
				++e;
			--e;
			while(b < e){
				wchar t = *b;
				*b = *e;
				*e = t;
				--e;++b;
			}
		}
		pcwstr c_str() const{
			if(m_buf == NULL) return L"";
			return m_buf;
		}
		wchar& operator[](uint32 index){
			return m_buf[index];
		}
		wchar operator[](uint32 index) const{
			return m_buf[index];
		}
		uint32 getLength(){
			return (uint32)m_len;
		}
		uint32 getSize(){ return getLength(); }
		void cut(uint32 cutsize){
			if(cutsize == 0) return;
			if(cutsize <= m_len){
				m_buf[m_len - cutsize] = L'\0';
				m_len = m_len - cutsize;
			}
			//Ҫ�г��Ĵ��ڳ��� ʲôҲ����
		}
		//pwstr getBuffer(){
		//	return m_buf;
		////  ��Ҫά��m_len
		//}

		String& vformat(pcwstr fmt, va_list marker){
			m_len = _vsnwprintf(NULL, 0, fmt, marker);
			if(m_len + 1 > buf_size)_new_buffer(m_len + 1);
			if(m_buf == NULL) return *this;//�����ڴ�ʧ��
			vswprintf(m_buf, fmt, marker);
			return *this;
		}

		String& format(pcwstr fmt, ...){
			va_list va_alist;
			va_start(va_alist, fmt);

			return vformat(fmt, va_alist);
		}

		String(pcwstr str)
			:allocator(GetAllocator()), buf_size(0), m_len(0), m_buf(NULL){
			eval(str);
		}
		String(const String& other)
			:allocator(GetAllocator()), buf_size(0), m_len(0), m_buf(NULL){
			eval(other.c_str());
		}
		String& operator=(pcwstr str){
			eval(str);
			return *this;
		}
		String& operator=(const String& other){
			eval(other.c_str());
			return *this;
		}
		bool operator==(pcwstr rhs){
			return !wcscmp(c_str(), rhs);
		}
		bool operator==(const String& rhs){
			return operator==(rhs.c_str());
		}
		bool operator!=(pcwstr rhs){
			return !operator==(rhs);
		}
		bool operator!=(const String& rhs){
			return !operator==(rhs);
		}
		String& operator+=(wchar ch){
			append(ch);
			return *this;
		}
		String& operator+=(pcwstr str){
			append(str);
			return *this;
		}
		String& operator+=(const String& other){
			append(other.c_str());
			return *this;
		}
		//����str1��str2��Ϊ��string��ʼ����
		String(pcwstr str1, pcwstr str2)
			:allocator(GetAllocator()), buf_size(0), m_len(0), m_buf(NULL){
			eval(str1);append(str2);
		}
	};

	inline String operator+(const String& lhs, const String& rhs){
		return String(lhs.c_str(), rhs.c_str());
	}
	inline String operator+(const String& lhs, pcwstr rhs){
		return String(lhs.c_str(), rhs);
	}
	inline String operator+(const String& lhs, wchar rhs){
		wchar t[2];
		t[0] = rhs;
		t[1] = L'\0';
		return String(lhs.c_str(), t);
	}
	inline String operator+(pcwstr lhs, const String& rhs){
		return String(lhs, rhs.c_str());
	}
	inline String operator+(wchar lhs, const String& rhs){
		wchar t[2];
		t[0] = lhs;
		t[1] = L'\0';
		return String(t, rhs.c_str());
	}

	extern "C" ONEU_API wchar* _Char2Wide(pcstr cstr, uint32 codepage = 0);
	extern "C" ONEU_API char* _Wide2Char(pcwstr cstr, uint32 codepage = 0);
	//codepage��ʾʹ�ú��ִ���ҳ��Ϊ���뷽ʽ
	//0����ʹ�ñ��ش���ҳ
	//(UTF8 65001 UTF7 65000)
	inline AutoPtr<wchar> Char2Wide(pcstr cstr, uint32 codepage = 0){
		return AutoPtr<wchar>(_Char2Wide(cstr, codepage));
	}
	inline String Char2WideStr(pcstr cstr, uint32 codepage = 0){
		return String(_Char2Wide(cstr, codepage));
	}
	inline AutoPtr<char> Wide2Char(pcwstr cstr, uint32 codepage = 0){
		return AutoPtr<char>(_Wide2Char(cstr));
	}
}

#define ONEU_FORMAT(formatString, ...) OneU::String().format(formatString, __VA_ARGS__).c_str()