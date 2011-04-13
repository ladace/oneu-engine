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
 * @file AtomLocal.h
 * @brief ���汾��ATOM����
 *
 * ����OneU�����Atom���Լ������ȡ����ʹ��ATOM����ļȶ����롣
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
		template<class T>
		inline T* GetVoidPtr(pcwstr symbol){
			value* s = GetAtom().getSystemEnv()->getSymbol(symbol);
			if(s)
				return *(T**)s->get<void*>();
			else return NULL;
		}
		//�����ǰ��������Scene_���� ����IScene�ӿ� ���򷵻�NULL��
		//��C++һ��Scene������ͼ�ýű���ʼ��ʱ lua��ô��Ϥ�ö��󣿣�֪���ö�����֪��SpriteҪ�����ĸ�RenderScene�У�
		//Ŀǰ�Ľ��������Scene�������ú�Scene_���ţ��ٵ��ýű����ù��̱�execWithScene��װ��
		inline IScene* GetLocalScene(){
			return GetVoidPtr<IScene>(L"Scene_");
		}
		inline void* GetD3D9(){
			return GetVoidPtr<void>(L"Direct3D9_");
		}
		inline void* GetD3DDevice9(){
			return GetVoidPtr<void>(L"Direct3DDevice9_");
		}

		//����Shell����
		inline bool ExportShellCommand(pcwstr command, value* (*addr)(value*)){
			return ugetSymbol<env>(GetAtom().getEnv(), L"shell").createSymbol(command, atom::makeFunc(addr));
		}
	}
}
