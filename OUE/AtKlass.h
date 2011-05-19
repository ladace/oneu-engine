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
 * @file AtKlass.h
 * @brief ATOM��ֵ
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "AtEnv.h"
#include "AtFunc.h"

namespace OneU{
	/**
	 * @addtogroup group_atom
	 */
	//@{
	namespace atom
	{
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ����
		 * @sa makeObj
		 */
		/* ----------------------------------------------------------------------------*/
		class obj
		{
			klass* _klass;
			void (*_destroyer)(void*);

			friend class value;
			friend class obj_function;
			friend value* makeObj(klass*, value*);

			obj()
				: _pObj(NULL){}
			inline void init(klass* kls, value* arg);//should be called immediately after contructed

			void* _pObj;

			obj(const obj&);
			obj& operator=(const obj&);
		public:
			inline ~obj();
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ����������
			 * 
			 * @returns ���ַ
			 */
			/* ----------------------------------------------------------------------------*/
			klass* getKlass(){ return _klass;}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ����object function
			 * 
			 * @param func ������ַ
			 * @param arg ���������������ΪNULL���Tuple���Զ�ת��ΪTuple��
			 * 
			 * @returns �������ص�ֵ�������κ����Σ�
			 */
			/* ----------------------------------------------------------------------------*/
			inline value* call(obj_function* func, value* arg);
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ�ڲ�����ĵ�ַ
			 * 
			 * @returns �����ַ
			 * @remarks ��ν�����ַ����@ref makeKlass�У����ذ汾һ��ģ���������Ķ����ַ�������ذ汾���������������صĵ�ַ��
			 * @sa @ref section_export_cooperation
			 */
			/* ----------------------------------------------------------------------------*/
			inline void* getAddr(){ return _pObj; }
		};

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��
		 * @sa makeKlass
		 */
		/* ----------------------------------------------------------------------------*/
		class klass
			: public env
		{
		public:
			typedef void* (*creator_t)(value*);
			typedef void (*destroyer_t)(void*);
		private:
			friend class obj;
			friend class value;
			creator_t _creator;
			destroyer_t _destroyer;

			klass()
				: _creator(NULL), _destroyer(NULL)
			{}
			void init(creator_t c, destroyer_t d){//should be called immediately after contructed
				_creator = c; _destroyer = d;
			}
			friend value* makeKlass_(creator_t c, destroyer_t d);
		public:
		};

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief object function
		 * @sa makeObjFunc
		 */
		/* ----------------------------------------------------------------------------*/
		class obj_function
		{
		public:
			typedef value* (exported::*addr_t)(value*);
		private:
			friend class value;
			template<class T>
			friend value* makeObjFunc(klass* kls, value* (T::*ptr)(value*));

			klass* _klass;

			addr_t _addr;

			obj_function(){}
			void init(klass* kls, addr_t ptr){
				_klass = kls;
				_addr = (addr_t)ptr;
			}
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ������
			 * 
			 * @returns ���ַ
			 */
			/* ----------------------------------------------------------------------------*/
			klass* getKlass(){ return _klass;}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ���ú���
			 * 
			 * @param o �����õĶ���
			 * @param arg ���������������ΪNULL���Tuple���Զ�ת��ΪTuple��
			 * 
			 * @returns �������ص�ֵ�������κ����Σ�
			 */
			/* ----------------------------------------------------------------------------*/
			value* call(obj* o, value* arg){//���argΪNULL�������߻�õ�һ���յ�Tuple�����arg��Ϊtuple�����߻�õ�ֻ��һ��Ԫ�ص�tuple��
				ASSERT(o->getKlass() == this->getKlass());
				arg = _convert_to_tuple(arg);
				exported* _obj_ = (exported*)(o->_pObj);
				return (_obj_->*_addr)(arg);
			}
		};


		inline void obj::init(klass* kls, value* arg){
			_klass = kls;
			_pObj = _klass->_creator(arg);
			_destroyer = _klass->_destroyer;//����obj����ʱklass�Ѿ������������ӱ�����klass��obj��ͬһ�ű��ﵱ������ʱklass����obj���������⣩
		}
		inline obj::~obj(){
			if(_pObj != NULL)//�п����ڶ���û���������ֹ���򣬴�ʱ_pObjΪNULL
				_destroyer(_pObj);
		}
		inline value* obj::call(obj_function* func, value* arg){
			return func->call(this, arg);
		}

		//ǰ������
		template<class T>
		T* __klass_creator(value* arg){
			return ONEU_NEW T(arg);
		}
		template<class T>
		void __klass_destroyer(T* p){
			ONEU_DELETE p;
		}

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ������
		 *
		 * @tparam T ���������࣬Ӧ��������atom::exported��
		 * 
		 * @returns �����
		 */
		/* ----------------------------------------------------------------------------*/
		template<class T>
		inline value* makeKlass(){
			return makeKlass(__klass_creator<T>, __klass_destroyer<T>);
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �ӹ�������������
		 * 
		 * @param c ��������
		 * @param d ���ٺ���
		 * 
		 * @returns �����
		 */
		/* ----------------------------------------------------------------------------*/
		template<class T>
		inline value* makeKlass(T* (*c)(value*), void (*d)(T*)){
			return makeKlass_((klass::creator_t)c, (klass::destroyer_t)d);
		}
		inline value* makeKlass_(void* (*c)(value*), void (*d)(void*)){
			value* ret = makeValue<klass>();
			ret->get<klass>()->init(c, d);
			return ret;
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��������
		 * 
		 * @param kls ����������
		 * @param arg ��������
		 * 
		 * @returns �������
		 */
		/* ----------------------------------------------------------------------------*/
		inline value* makeObj(klass* kls, value* arg){
			arg = _convert_to_tuple(arg);
			value* ret = makeValue<obj>();
			ret->get<obj>()->init(kls, arg);
			return ret;
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ����object function
		 * 
		 * @param kls ������
		 * @param ptr ��Ա����ָ�롣һ����������atom::exported����ĳ�Ա������
		 * 
		 * @returns object function����
		 */
		/* ----------------------------------------------------------------------------*/
		template<class T>
		inline value* makeObjFunc(klass* kls, value* (T::*ptr)(value*)){
			T* __ = NULL;exported* ___ = __;//�����������û�а�T��exported����
			value* ret = makeValue<obj_function>();
			int memptr = *(int*)&ptr;
			ret->get<obj_function>()->init(kls,*(obj_function::addr_t*)(&memptr));
			return ret;
		}
	}
	//@}
}
