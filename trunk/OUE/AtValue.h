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
 * @file AtValue.h
 * @brief ATOMֵ
 *
 * ATOM�ĺ��ġ�
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "OUEDefs.h"
#include "Atom.h"
namespace OneU
{
	/**
	 * @addtogroup group_atom
	 */
	//@{
	namespace atom
	{
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ������������
		 */
		/* ----------------------------------------------------------------------------*/
		enum AT_TYPE{
			T_NIL = 0,
			T_BOOL,
			T_INT,
			T_FLOAT,
			T_STR,
			T_CPOINTER,
			T_TUPLE,
			T_FUNC,
			T_ENV,
			T_KLS,
			T_OBJ,
			T_OBJFUNC,
			T_REF = 0x80000000
			//T_TYPEDEF/*����һ�����͵ķ���*/,//???
			//T_USERTYPE/*�������ţ��ȸ÷���ֵ��ľ�Ϊ�û����������*///
		};
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ��������
		 * 
		 * @param t ��ʾ���͵ĳ���
		 * 
		 * @returns ���������ַ�������NULL������
		 */
		/* ----------------------------------------------------------------------------*/
		inline pcwstr typeName(dword t){
			switch(t)
			{
			case T_NIL:
				return L"none";
			case T_BOOL:
				return L"bool";
			case T_INT:
				return L"int";
			case T_FLOAT:
				return L"float";
			case T_STR:
				return L"string";
			case T_CPOINTER:
				return L"cpointer";
			case T_TUPLE:
				return L"tuple";
			case T_FUNC:
				return L"function";
			case T_ENV:
				return L"environment";
			case T_KLS:
				return L"klass";
			case T_OBJ:
				return L"object";
			case T_OBJFUNC:
				return L"object function";
			default:
				return L"<Error!>";
			}
			return NULL;
		}

		/*@cond INTERNAL_MPL*/
		template<typename T>
		struct _atom_traits{
			//enum{ type_id = ATT_NIL };
		};
		template<>
		struct _atom_traits<value*>{
			enum{ type_id = T_REF };
		};
		template<>
		struct _atom_traits<bool>{
			enum{ type_id = T_BOOL };
		};
		template<>
		struct _atom_traits<int>{
			enum{ type_id = T_INT };
		};
		template<>
		struct _atom_traits<float>{
			enum{ type_id = T_FLOAT };
		};
		template<>
		struct _atom_traits<String>{
			enum{ type_id = T_STR };
		};
		template<>
		struct _atom_traits<void*>{
			enum{ type_id = T_CPOINTER };
		};
		template<>
		struct _atom_traits<tuple>{
			enum{ type_id = T_TUPLE };
		};
		template<>
		struct _atom_traits<function>{
			enum{ type_id = T_FUNC };
		};
		template<>
		struct _atom_traits<env>{
			enum{ type_id = T_ENV };
		};
		template<>
		struct _atom_traits<klass>{
			enum{ type_id = T_KLS };
		};
		template<>
		struct _atom_traits<obj>{
			enum{ type_id = T_OBJ };
		};
		template<>
		struct _atom_traits<obj_function>{
			enum{ type_id = T_OBJFUNC };
		};
		/*@endcond*///INTERNAL_MPL
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief Atom������
		 */
		/* ----------------------------------------------------------------------------*/
		class value
		{
			//_type_idΪT_REFʱ���ñ�������һ�����������á�
			//_type_id���λΪ1��T_REF��Ϊ���λΪ1������Ϊ0��������λ���ڷ���ֵʱ��ȥ�����λ��Ϊ�ñ��������͡��ñ���������ָ���ݲ������ڴ档��Ҳ��һ��������ʽ��
			//ò����Ƶ��е㸴���ˣ���һ���������ɡ�
			//�����ȥ���ù��ܣ�ɾ��makeValueFromPtr����T_REFֵ�����������ȥ��_type_id & ~T_REF��벿�֣�ɾ��evalPtr��ȥ��_destroy_valueǰ��������жϣ�Ȼ�����±���dll��
			dword _type_id;
			void* _ptr;

			//һ������������GC��ص�
			List<value*>::iterator gcID;
			bool b_hold;

			template<typename T>
			void _set_value(const T& v, dword type){
				if(_type_id != type){
					_destroy_value();
					_type_id = type;
					_ptr = ONEU_NEW_T(T(v));
				}
				else
					*((T*)_ptr) = v;
			}
			template<typename T>
			void _create_value(dword type){
				if(_type_id != type){
					_destroy_value();
					_ptr = ONEU_NEW_T(T);
					_type_id = type;
				}
			}
			inline void _destroy_value();

			friend class IAtom;

			value()
				:_type_id(T_NIL), _ptr(NULL), b_hold(false){
			}
			value(const value&);
			value& operator=(const value&);
		public:
			~value(){
				_destroy_value();
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ����
			 * 
			 * @returns ����
			 * @remarks �������Ϊ������᷵���������õ�ֵ������
			 */
			/* ----------------------------------------------------------------------------*/
			dword type() const {
				if(_type_id == T_REF) return (*(value**)_ptr)->type();
				else return _type_id & ~T_REF;
			}
			//copy v to self
			//��������C++��������
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ֵ
			 * 
			 * @param v ֵ��ֻ������C�������͡�
			 * 
			 * @returns �˱���������
			 */
			/* ----------------------------------------------------------------------------*/
			template<typename T>
			value& eval(const T& v){
				_set_value(v, _atom_traits<T>::type_id);
				return *this;
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��T���ͳ�ʼ��
			 * @tparam T ֻ������C�������͡�
			 * 
			 * @returns �˱���������
			 */
			/* ----------------------------------------------------------------------------*/
			template<typename T>
			value& eval(){
				_create_value<T>(_atom_traits<T>::type_id);
				return *this;
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			* @brief ���ⲿ�ڴ��ʼ��
			* @param v ֵ��ֻ������C�������͡�
			* 
			* @returns �˱���������
			*/
			/* ----------------------------------------------------------------------------*/
			template<typename T>
			value& evalPtr(T* v){
				dword type = _atom_traits<T>::type_id;
				_destroy_value();
				_type_id = type | T_REF;
				_ptr = v;
				return *this;
			}
			//�Զ�������
			//template<typename T>
			//value& eval(const T& v, dword typeID){
			//	_set_value(v, typeID);
			//	return *this;
			//}
			//template<typename T>
			//value& eval(dword typeID){
			//	_create_value<T>(typeID);
			//	return *this;
			//}//

			//���nil
			value& evalNil(){
				_destroy_value();
				_type_id = T_NIL;
				_ptr = NULL;
				return *this;
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ����
			 * @tparam T ��Ҫ��ȡ������
			 * 
			 * @returns ����ñ���������Ϊ�����͵Ļ�Ϊ�����͵����ã��򷵻����ݵĵ�ַ�����򷵻�NULL��
			 * @remarks ���TΪvalue*����᷵���������õı�����
			 */
			/* ----------------------------------------------------------------------------*/
			template<typename T>
			T* get(){
				if(_atom_traits<T>::type_id == (_type_id & ~T_REF))
					return (T*)_ptr;
				else if(_type_id == T_REF)
					return (*(value**)_ptr)->get<T>();
				else
					return NULL;
			}
			template<typename T>
			const T* get() const{
				if(_atom_traits<T>::type_id == (_type_id & ~T_REF))
					return (T*)_ptr;
				else if(_type_id == T_REF)
					return (*(value**)_ptr)->get<T>();
				else
					return NULL;
			}


			//eval���ػ�
			template<>
			value& eval<pcwstr>(const pcwstr& v){
				//�ַ���
				eval<String>();
				(*(String*)_ptr) = v;
				return *this;
			}

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡ����Ȩ
			 * 
			 * @returns ��ʾ��ȡ����Ȩ�ɹ����
			 * @retval true ��ȡ����Ȩ�ɹ�
			 * @retval false ��ȡ����Ȩʧ��
			 * @sa unacquire
			 */
			/* ----------------------------------------------------------------------------*/
			bool acquire(){ return GetAtom().acquireValue(this);}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �ͷſ���Ȩ
			 *
			 * ���û�б���ÿ���Ȩ�������κβ�����
			 */
			/* ----------------------------------------------------------------------------*/
			void unacquire(){ GetAtom().unacquireValue(this);}
			/* ----------------------------------------------------------------------------*/
			/** 
			* @brief �Ƿ�Ϊ����
			*
			* @return ��ʾ�ñ����Ƿ�Ϊ����
			*/
			/* ----------------------------------------------------------------------------*/
			bool isRef(){ return _type_id == T_REF; }
		};

		void value::_destroy_value(){
			if((_type_id & T_REF) != 0 && (_type_id & ~T_REF) != 0)
				return;
			if(_ptr != NULL){
				switch(_type_id){
				case T_REF:
				case T_BOOL:
				case T_INT:
				case T_FLOAT:
				case T_CPOINTER:
					ONEU_DEALLOC(_ptr);
					break;
				case T_STR:
					ONEU_DELETE_T((String*)_ptr);
					break;
				case T_TUPLE:
					ONEU_DELETE_T((tuple*)_ptr);
					break;
				case T_FUNC:
					ONEU_DELETE_T((function*)_ptr);
					break;
				case T_ENV:
					ONEU_DELETE_T((env*)_ptr);
					break;
				case T_KLS:
					ONEU_DELETE_T((klass*)_ptr);
					break;
				case T_OBJ:
					ONEU_DELETE_T((obj*)_ptr);
					break;
				case T_OBJFUNC:
					ONEU_DELETE_T((obj_function*)_ptr);
					break;
				default:
					ONEU_ENSURE(0);
				}
			}
		}

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ����C�������ͱ���
		 * @tparam T ���ͣ�����ΪC��������
		 * @returns ����
		 */
		/* ----------------------------------------------------------------------------*/
		template<typename T>
		inline value* makeValue(){ return &GetAtom()._make_value()->eval<T>(); }
		template<typename T>
		inline value* makeValue(const T&v){ return &GetAtom()._make_value()->eval(v); }
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �����ձ���
		 * @returns ����
		 */
		/* ----------------------------------------------------------------------------*/
		inline value* makeNil(){ return GetAtom()._make_value(); }
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��������
		 * @param v �����õı���
		 * @return ����v�ı���
		 * @attention ��Ŀǰ�İ汾�У����뱣֤�����õı����ڸ����õ���������һֱ���ڡ�
		 */
		/* ----------------------------------------------------------------------------*/
		inline value* makeRef(value* v){ return makeValue(v); }

		/* ----------------------------------------------------------------------------*/
		/**
		* @brief �����ⲿ�ڴ����
		* @param v �����õ��ڴ�
		* @return �����ⲿ�ڴ�v�ı���
		* @remarks �ú����ṩһ������һ��ʹ���ⲿ�ڴ�ı����ķ������������ٺ�������õ�ֵ��v��ָ���ڴ棩���ᱻ���٣��������ڶ����ڱ�����
		*/
		/* ----------------------------------------------------------------------------*/
		template<class T>
		inline value* makeValueFromPtr(T* v){ return &GetAtom()._make_value()->evalPtr(v); }
	}

	/*@cond INTERNAL*/
	atom::value* IAtom::_make_value(){ atom::value* ret = ONEU_NEW_T(atom::value); unacquireValue(ret); return ret;}
	/*@endcond*/

	List<atom::value*>::iterator& IAtom::__value_gcID(atom::value* v){ return v->gcID;}
	bool& IAtom::__value_b_hold(atom::value* v){ return v->b_hold; }

	//@}
}

#include "AtTuple.h"
#include "AtEnv.h"
#include "AtFunc.h"
#include "AtKlass.h"
