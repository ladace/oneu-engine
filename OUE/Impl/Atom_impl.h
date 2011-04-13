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
#include "../Atom.h"
#include "../List.h"
namespace OneU
{
	class Atom_Impl
		: public IAtom
	{
		typedef List<atom::value*> gc_list_t;
		gc_list_t gc_list;

		atom::value* global_env_v, *system_env_v;
		atom::env* global_env, *system_env;

		//�������environment����ʱ����
		int value_outputer_tab_depth;


		//����������Դ�����
		//ehmĳ��λ���б�־��ʾʹ���˸����ԣ�����ʱ�����ý�������ջ
		//������ֶ���������͸������ˡ���
		int ehm[L_END];
		atom::IInterpreter* m_pInterpter[L_END];

		//�Ѽ��ص�AtomLib
		struct ModuleInfo{
			HMODULE H;
			int ref;
		};
		Table<ModuleInfo> LibTable;
	public:
		//�ǽӿں���
		void init();//��Atom_build�б����ã�����ڹ��캯���д���������������õ�������麯�����������⡣
		void value_outputer_add_tab(String& buffer);

		Atom_Impl()
			: value_outputer_tab_depth(0)
		{
			memset(m_pInterpter, 0, sizeof(m_pInterpter));
			memset(ehm, 0, sizeof(ehm));
		}

		//��д����
		~Atom_Impl();
		void gc();
		bool acquireValue(atom::value* v);
		void unacquireValue(atom::value* v);

		atom::env* getEnv(){ return global_env; }
		virtual atom::value* getEnvValue(){ return global_env_v; }
		atom::env* getSystemEnv(){ return system_env; }
		virtual atom::value* getSystemEnvValue(){ return system_env_v; }

		void getDescription(atom::value* v, OneU::String& buffer);
	public:
		//��������
		//���ø����Ե�ĳ����ʱӦѹջ ����������ʱ���и����ԵĶ�ջ��Ϣ
		//�ǽӿڣ���Ϊ���øú�����ģ��Ϊ�����������ڸ�ģ�顣
		void _pushErrorHook(LANGUAGE e){
			ehm[(int)e]++;
		}
		void _popErrorHook(LANGUAGE e){
			ehm[(int)e]--;
		}
		void raise(pcwstr error_message){
			String out = error_message;
			//ͨ���ж��Ƿ��hookѹջ������
			if(ehm[L_LUA])
			{
				out.append(L"\nLua Stack:\n");
				m_pInterpter[L_LUA]->_getStackInfo(out);
			}
			ONEU_RAISE(out.c_str());
		}
		void raise(pcwstr error_message, pcstr source_file, int source_line){
			raise(String().format(L"%s\nFile:%S(%d)", error_message, source_file, source_line).c_str());
		}
		//���������

		void loadAtomLib(pcwstr path);
		void unloadAllAtomLib();

		atom::IInterpreter* getInterpreter(LANGUAGE language){
			return m_pInterpter[language];
		}
		atom::IInterpreter* createInterpreter(LANGUAGE language);
	};
}