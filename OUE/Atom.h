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
 * @file Atom.h
 * @brief Atom��ͷ�ļ�
 * 
 * ʹ��Atomʱ�������ͷ�ļ���
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-02-15
 */
#pragma once
#include "OUEDefs.h"
#include "List.h"
//�����Base֮�� ����֮��

namespace OneU
{
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @addtogroup group_atom Atom��ϵͳ
	 */
	/* ----------------------------------------------------------------------------*/
	//@{
	namespace atom
	{
		class value;
		class tuple;
		class function;
		class env;
		class klass;
		class obj;
		class obj_function;

		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ���������
		 *
		 * �κ���Ҫ������Atom��Ҫ�����Ը��ࡣ
		 */
		/* ----------------------------------------------------------------------------*/
		class exported{};

		class IInterpreter;
	}
	class IAtom
	{
	public:
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ִ����������
		 *
		 * ��Ҫ����ִ���������������Ч��value��
		 * ��OUE�����Ĭ��ÿִ֡��һ�Ρ�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void gc() = 0;
		virtual ~IAtom(){}

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ����Ȩ
		 *
		 * ����Ȩֻ��һ��������ñ����Ѿ�����ȡ����Ȩ������ȡ����Ȩʧ�ܡ�
		 * ��ȡ�ñ�������Ȩ�������ĸ�����Ʊ����������ڣ��ڱ�Ҫ��ʱ������unacquire��
		 * һ��ͨ������@ref atom::value::acquireʵ����ͬ���ܡ�
		 * 
		 * @param v ����
		 * 
		 * @returns ��ʾ��������Ȩ��ȡ�ɹ����
		 * @retval true ��ȡ��������Ȩ�ɹ�
		 * @retval false ��ȡ��������Ȩʧ��
		 * 
		 * @sa atom::value::acquire
		 */
		/* ----------------------------------------------------------------------------*/
		virtual bool acquireValue(atom::value* v) = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��������Ȩ
		 *
		 * ���������Ŀ���Ȩ��ʹ����뵽GC�б�����´������ռ�ʱ���ͷš�
		 * һ��ͨ������@ref atom::value::unacquireʵ����ͬ���ܡ�
		 *
		 * @remarks ����ñ�������Ȩ�Ѿ�����������û���κ���Ϊ��
		 *
		 * @param v ����
		 * @sa atom::value::unacquire
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void unacquireValue(atom::value* v) = 0;

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �õ���ǰ������
		 * 
		 * @returns ��ǰ�������ַ
		 */
		/* ----------------------------------------------------------------------------*/
		virtual atom::env* getEnv() = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �õ�ϵͳ������
		 * 
		 * @returns ϵͳ�������ַ
		 *
		 * @remarks ϵͳ������������һЩ�漰�ײ��̵�Ԫ�ء�����DXDevice��ָ�룬���á�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual atom::env* getSystemEnv() = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �õ����������
		 *
		 * @return ��ǰ���������
		 */
		/* ----------------------------------------------------------------------------*/
		virtual atom::value* getEnvValue() = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �õ�ϵͳ������
		 *
		 * @return ϵͳ���������
		 */
		/* ----------------------------------------------------------------------------*/
		virtual atom::value* getSystemEnvValue() = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ��ȡ�˱���������
		* 
		* @param v ����
		* @param buffer �ַ�����������������׷�ӵ����ַ����ϡ�
		*/
		/* ----------------------------------------------------------------------------*/
		virtual void getDescription(atom::value* v, OneU::String& buffer) = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ����
		 * 
		 * ��ʹ��Atomʱ���øú�����Atom�ύ����
		 *
		 * @param error_message ������Ϣ��
		 * @remarks �������ء�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void raise(pcwstr error_message) = 0;
		virtual void raise(pcwstr error_message, pcstr source_file, int source_line) = 0;

		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ����Atom���ļ�
		 *
		 * @param path ������·�������·����
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void loadAtomLib(pcwstr path) = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ж������Atom���ļ� 
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void unloadAllAtomLib() = 0;

		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �������� 
		 */
		/* ----------------------------------------------------------------------------*/
		enum LANGUAGE {L_LUA = 0, L_END};

		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��ȡȫ�ֽ�����
		 *
		 * @param language �������� 
		 *
		 * @return �������ӿ�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual atom::IInterpreter* getInterpreter(LANGUAGE language) = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ����������
		 *
		 * @param language ��������
		 *
		 * @return �������ӿ�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual atom::IInterpreter* createInterpreter(LANGUAGE language) = 0;

		//typedef void (*ut_df_t)(void*);
		//typedef void (*ut_of_t)(void*, String&);
		//virtual dword registerUserType(ut_df_t deleteFunction = NULL, ut_of_t outputFunction = NULL) = 0;

		//virtual ut_df_t _getUserTypeDeleteFunction(dword userType) = 0;
		//virtual ut_of_t _getUserTypeOutputFunction(dword userType) = 0;

		//in AtValue.h
		/*@cond INTERNAL*/
		inline atom::value* _make_value();
		/*@endcond*/
	protected:
		//������Atom��ʵ�ַ���value˽�г�Ա
		//in AtValue.h
		inline List<atom::value*>::iterator& __value_gcID(atom::value*);
		inline bool& __value_b_hold(atom::value*);
	};
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ����Atom��̬
	 *
	 * @remarks Ҫ�ڶ�Atom������κβ���֮ǰ���á�����Atom_destroy���ٵ�̬��
	 * @sa Atom_destroy
	 */
	/* ----------------------------------------------------------------------------*/
	ONEU_API void Atom_build();
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ����Atom��̬
	 *
	 * @remarks Ҫ�ڶ�Atom������κβ���֮����á�
	 * @sa Atom_build
	 */
	/* ----------------------------------------------------------------------------*/
	ONEU_API void Atom_destroy();
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ȡAtom��̬����
	 * 
	 * @returns Atom��̬������
	 * @remarks ���������Atom_build֮����ã�����������Ԥ�ϡ�
	 */
	/* ----------------------------------------------------------------------------*/
	ONEU_API IAtom& GetAtom();

#define ATOM_RAISE(error_msg) GetAtom().raise(error_msg, __FILE__, __LINE__)


	/* ----------------------------------------------------------------------------*/
	/** 
	 * @page page_atom Atom���
	 *
	 * Atom�����̬���ͱ�������ɵı�ϵͳ��\n
	 * Atom�Ա�Ϊ���ģ����ڴ洢�ŷ��ţ��ַ������Ա�����ӳ�䡣���������ϵͳ���������������๩�ű����õȡ�\n
	 * \n
	 * 
	 * @section section_value ����
	 * ��������
	 *  - nil
	 *  - bool
	 *  - int
	 *  - float
	 *  - string
	 *  - cpointer
	 *  - tuple
	 *  - function
	 *  - environment
	 *  - klass
	 *  - object
	 *  - object function
	 *  .
	 * ���д�bool��cpointer����C�������͡�\n
	 * \n
	 * ����C�������ͣ����Ե���@ref atom::value::eval���κα�����ֵ��C�������ͣ������������ͻᶯ̬�ı䡣\n
	 * ���ڷ�C�������ͣ�ʹ��makeXXX���������������Ŀǰ��֧�ֽ�������ֵ�ɷ�C�������͡�\n
	 * cpointer�ǹ��������ݵײ���Ϣʹ�õģ�����洢DXDevice��ָ�롣�������Ͷ����System��\n
	 *
	 * atom::value�Ĺ���������
	 *  - @ref atom::makeValue ������C�������͡�
	 *  - @ref atom::makeRef
	 *  - @ref atom::makeTuple
	 *  - @ref atom::makeTupleWithElem
	 *  - @ref atom::makeFunc
	 *  - @ref atom::makeEnv
	 *  - @ref atom::makeKlass
	 *  - @ref atom::makeObj
	 *  - @ref atom::makeObjFunc
	 *  .
	 * ͨ�������������Դ����������͵ı�����\n
	 * \n
	 * Ϊ�˻�ȡ���������ݣ�����@ref atom::value::get��������ģ�������ʾָ�����ͣ����ɻ������Ӧ���͵�ֵ��ָ�루ע����ָ�룩��������Ͳ���֧�֣����������\n
	 * C��������ΪC++��������Ӧ�����͡�����cpointer��Ӧvoid*��\n
	 * ��C�������Ͷ�Ӧ���ࣺ
	 *  - tuple @ref atom::tuple
	 *  - environment @ref atom::env
	 *  - klass @ref atom::klass
	 *  - object @ref atom::obj
	 *  - object function @ref atom::obj_function
	 *  .
	 * C�������͵�ʹ�ã�
	 * @code
	 * atom::value* v = atom::makeNil();
	 * v->eval(L"This is a String");//v->type() = atom::T_STRING
	 * v->get<String>();//����String*ָ�룬������ΪL"This is a String"
	 * v->eval(20.0f);//v->type() = atom::T_FLOAT��ע�⣬�������f�Ļ�����������Ϊatom��֧��double��
	 * v->get<float>();//����float*ָ�룬��ָ������Ϊ20.0f
	 * @endcode
	 * Tuple��ʹ�ã�
	 * @code
	 * atom::value* v = atom::makeTuple(3);//����һ��3Ԫ�ص�Tuple v = (nil, nil, nil)
	 * v->get(0)->eval(10.0f);
	 * v->get(1)->eval(true);
	 * v->get(2)->eval(3);//v = (10.0f, true, 3)
	 * @endcode
	 * @code
	 * atom::value* v= atom::makeTupleWithElem(3, atom::makeValue(10.0f), atom::makeValue(true), atom::makeValue(3));//v = (10.0f, true, 3)
	 * @endcode
	 * function��ʹ�ã���\n
	 * klass��obj��ʹ�ã�
	 * @code
	 * class exported_klass
	 * 	:public atom::exported//����Ҫ�����ĳ�Ա������һ��Ҫ�������������
	 * {
	 * public:
	 * 	exported_klass(atom::value* arg){
	 *		//arg��һ��Tuple�����ȿ�Ϊ0������ʾ��ʼ��������
	 * 	}
	 * };
	 * //...
	 * 	atom::value* k = atom::makeKlass<exported_klass>();
	 * 	atom::value* o = atom::makeObj(k->get<atom::klass>(), NULL);//NULL���Զ�תΪ����Ϊ0��Tuple
	 * //...
	 * @endcode
	 * object function��ʹ�ã�
	 * @code
	 * class exported_klass
	 * 	:public atom::exported//����Ҫ�����ĳ�Ա������һ��Ҫ�������������
	 * {
	 * public:
	 * 	exported_klass(atom::value*);
	 * 	atom::value* exported_method(atom::value*){ return NULL; }
	 * };
	 * //...
	 * 	atom::value* v = atom::makeObjFunc(klass_v, &exported_klass::exported_method);//atom::klass* klass_v
	 * //...
	 * @endcode
	 * @subsection section_acquire ����Ȩ��GC
	 * Atom���а��Զ���������ϵͳ��\n
	 * ÿ����������Ψһ����Ȩ�����û�б���ȡ����Ȩ�ᱻ��Ϊ��ʱ������������һ��GC���ͷš������ȡ���ο���Ȩ���ڶ��λ�ʧ�ܡ�\n
	 * ���Ҫ����һ��������Ӧ�û�ȡ�ñ����Ŀ���Ȩ��Ȼ���ں��ʵĵط��ͷſ���Ȩ��\n
	 * ������Щ�����᳢�Ի�ȡ����Ȩ�����ʧ�������ɲ���ʧ�ܡ�\n
	 * ����Ȩ��ʹ�ã�
	 * @code
	 * class hold_control
	 * {
	 * 	atom::value* v;
	 * public:
	 * 	hold_control(){
	 * 		v = atom::makeValue(10.0f);
	 * 		v->acquire();
	 * 	}
	 *	~hold_control(){
	 *		v->unacquire();
	 *	}
	 * };
	 * @endcode
	 *
	 *
	 * @section section_list ��ϵͳ
	 *
	 * environment������һ��Atom���൱�����ַ���Ϊ��ֵ����atom::value*Ϊֵ��map��\n
	 * atom::klass������atom::env������klassҲ����֧��environment�������ԡ����ǽ�atom::T_KLASS��atom::T_ENV��Ϊ���ֲ�ͬ���͡�\n
	 * \n
	 * �����������ӱ�����ɾ������������������ȡ����Ȩ�������ȡ����Ȩʧ�ܣ�����ӱ���ʧ�ܡ�\n
	 * ������У������̳й�ϵ������@ref atom::env::setFatherʹһ�ű�̳���һ�ű�
	 * ��һ�ű�̳�����һ��ʱ���ڲ��ҷ���ʱ�������ڵ�ǰ����ң����ڸ����в��ҡ�
	 *
	 * @section section_exporting ������
	 * @code
	 * class exported_class
	 * 	: public atom::exported
	 * {
	 * 	float m_f;
	 * public:
	 * 	exported_class(atom::value* v){
	 * 		m_f = *getArg<float>(v, 0);
	 * 	}
	 * 	atom::value* exported_method(atom::value* arg){
	 * 		return arg;
	 * 	}
	 * };
	 * ...
	 * 	atom::value* v = atom::makeKlass<exported_class>();
	 * 	GetAtom()->getEnv()->createSymbol(L"new_class", v);
	 * 	v->get<atom::klass>()->exportMethod(L"new_method", &exported_class::exported_method);
	 * ...
	 * @endcode
	 * ͬ��Ҳ���Է�װһ���࣬���䵼����
	 * @code
	 * class exported_class
	 * 	: public atom::exported, private aClass
	 * {
	 * public:
	 * 	exported_class(atom::value* v)
	 * 		: aClass(*getArg<float>(v, 0))
	 * 	{}
	 * };
	 * @endcode
	 * @subsection section_export_cooperation ������Э����ϵ����ĵ���
	 * ��ʱ��һ����ĳ�Ա����������Ҫ��һ����Ķ��������������磺
	 * @code
	 * class IImage
	 * {
	 * 	//...
	 * };
	 * class Sprite
	 * {
	 * public:
	 * 	Sprite(IImage*);
	 * };
	 * @endcode
	 * ����Sprite���ʱ��Ҫ���䵼���๹�캯������֤��������Ƿ�ΪIImage*��Ҫ��ȫ��ת��ΪIImage*���ܹ�Sprite��ʹ�á�\n
	 * ʵ�ַ�����\n
	 * ͷ�ļ���
	 * @code
	 * IImage* SafeToImage(atom::obj* v);
	 * class Image_exp
	 * 	: public atom::exported
	 * {
	 * 	IImage* m_pImage;
	 * public:
	 * 	Image(atom::value* arg){ m_pImage = GetVideo().loadImage(atom::getArg<String>().c_str()); }
	 * 	IImage* getImage(){ return m_pImage; }
	 * };
	 * class Sprite_exp
	 * 	: public atom::exported, public Sprite
	 * {
	 * public:
	 * 	Sprite_exp(atom::value* arg)
	 * 		: Sprite(SafeToImage(atom::getArg<atom::obj>(arg, 0)))
	 * 	{}
	 * };
	 * @endcode
	 * ʵ���ļ���
	 * @code
	 * static atom::klass* image_kls = NULL;
	 * bool RegisterImage(){
	 * 	atom::value* image_kls_v = atom::makeKlass<Image_exp>();
	 * 	image_kls = image_kls_v->get<atom::klass>();
	 * 	return GetAtom().getEnv()->createSymbol(L"image", image_kls_v);
	 * }
	 * IImage* SafeToImage(atom::obj* v)
	 * {
	 * 	if(v->getKlass() != image_kls) GetAtom().error(L"not a image object!");
	 * 	return ((IImage_exp*)v->getAddr())->getImage();
	 * }
	 * @endcode
	 * ���ַ����ܹ���֤���԰�ȫ�����Ǵ���һ��ȱ�ݣ�������IImage��һ���ӿڣ�����ڱ�Ĳ����д��һ��ʵ�֣���û�а취��Sprite_exp�����õġ�\n
	 * ����������޸�������룬��һ����Ӳ㣬��Image_expʵ�ֳ�һ��ָ������࣬����ΪImage_holder����ֻ����һ������cpointer���ͣ�������ǿת��IImage*�������档�����ܱ�֤ʹ��Image_holder��ʱ�������Ͱ�ȫ�ġ�
	 * ͬʱ����дһ����������������һ��Image_holder����������ʵ�ָղŵĹ��ܡ�����ڱ�Ĳ��д��һ��ʵ�֣�������дһ������������ʵ���˶�̬��\n
	 * ���Ͳ���ȫ�ĵط�ֻ������Image_holder�Ĺ��캯����ֻҪ��д��������ʱע�⼴�ɡ��������Ͳ���ȫ�ԣ�Image_holder���ڵײ��࣬��˿�����Image��������ǰ��һ���»��ߡ�\n
	 * \n
	 * \n
	 * @remarks ������һ�ֽ���취��������SafeToImage��ΪImage_exp����һ����ȡIImage*�ĺ�������������Ϊcpointer������Ҫ��ø���һ�㣨��������������Sprite�е��øú�����ǿת��IImage*���÷�������С���ʲ���ȫ�ԡ�
	 * ����и��õİ취֪ͨ�ҡ�
	 *
	 * @todo ���ʵ����Atom�û��Զ������͵Ļ����������Ͳ���ȫ�Կ��Խ����
	 *
	 * @todo ʵ���Զ������͡�
	 */
	/* ----------------------------------------------------------------------------*/

	//@}
}



#include "AtValue.h"
#include "AtConvert.h"
#include "AtInterpreter.h"
#include "AtUtility.h"
