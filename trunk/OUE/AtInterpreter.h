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
 * @file AtInterpreter.h
 * @brief ATOM�������ӿ�
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "Atom.h"

namespace OneU
{
	namespace atom
	{
		class IInterpreter
			: public Interface
		{
		public:
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ִ���ļ��еĴ���
			 *
			 * @param filename �ļ����·�������·����
			 */
			/* ----------------------------------------------------------------------------*/
			virtual void execFile(pcwstr filename) = 0;
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ִ�д���
			 *
			 * @param code ����
			 *
			 * @return NULL��Reserved.
			 */
			/* ----------------------------------------------------------------------------*/
			virtual value* exec(pcwstr code) = 0;
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ��ȡ��ǰջ����Ϣ
			 *
			 * @param buffer �ַ�����
			 */
			/* ----------------------------------------------------------------------------*/
			virtual void _getStackInfo(String& buffer) = 0;
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ִ�������ռ�
			 */
			/* ----------------------------------------------------------------------------*/
			virtual void gc() = 0;
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ִ�д���
			 *
			 * reserved.�������1.
			 * �趨Sceneϵͳ����ֵ�����ô��빩������Ԫ��ʹ�á�
			 * @sa atom::GetLocalScene
			 *
			 * @param code ����
			 * @param s ����
			 */
			/* ----------------------------------------------------------------------------*/
			void execWithScene(pcwstr code, IScene* s){
				GetAtom().getSystemEnv()->createSymbol(L"Scene_", makeValue((void*)s));
				exec(code);
				GetAtom().getSystemEnv()->removeSymbol(L"Scene_");
			}
		};
	}
}
