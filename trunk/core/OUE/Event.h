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
 * @file Event.h
 * @brief �¼�ϵͳ
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "OUEDefs.h"
namespace OneU
{
	class IEventDispatcher;
	class EventArgs{};
	namespace event
	{
		//�޲����¼�
		//�㲥�¼�
		//�㲥������յ����¼�
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ����һ֡��ʱ�򱻹㲥
		 *
		 * �ڳ�������֮ǰ��
		 */
		/* ----------------------------------------------------------------------------*/
		extern const wchar* ENTER_FRAME;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���ڱ�����ʱ���㲥
		 */
		/* ----------------------------------------------------------------------------*/
		extern const wchar* WINDOW_ACTIVE;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ����ʧȥ����ʱ���㲥
		 */
		/* ----------------------------------------------------------------------------*/
		extern const wchar* WINDOW_DEACTIVE;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��Ϸ��������ʱ���㲥
		 *
		 * �ڳ�������֮�󣬸���ϵͳ����֮ǰ��
		 * @sa section_run
		 */
		/* ----------------------------------------------------------------------------*/
		extern const wchar* DESTROY;
	}
}
#include "Table.h"
#include "List.h"

namespace OneU
{

	/* ----------------------------------------------------------------------------*/
	/** 
	* @brief �¼�������
	*
	* �̳иýӿ���ʵ��һ���¼���������
	*/
	/* ----------------------------------------------------------------------------*/
	class IEventListener
		: public Interface
	{
	public:
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief �����¼�
		* 
		* @param event �¼�����
		* @param pArg �¼���������ΪNULL��
		* @param source ���������¼�������
		* @sa @ref event
		*/
		/* ----------------------------------------------------------------------------*/
		virtual void onEvent(pcwstr event, EventArgs* pArg, IEventDispatcher* source) = 0;
	};

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief �¼�������
	 * 
	 * �̳иýӿڿ���ʹ��ɴ����¼���
	 */
	/* ----------------------------------------------------------------------------*/
	class IEventDispatcher
		: public Interface
	{
	private:
		typedef InterfacePtr<IEventListener> HandlerHolder;
		typedef List<HandlerHolder> EventList_t;
		Table<EventList_t> m_event_table;
	public:
		virtual ~IEventDispatcher(){}

		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ����¼�������
		* 
		*
		* @param event �¼�����
		* @param eventhandler �¼�������
		*
		* @remarks �������������ڻᱻ�������
		* @sa @ref event
		*/
		/* ----------------------------------------------------------------------------*/
		virtual void addEventListener(pcwstr event, IEventListener* eventhandler){
			m_event_table[event].pushBack(eventhandler);
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief �����¼� 
		* 
		* @param event �¼�����
		* @param pArgs �¼���������ΪNULL��
		*
		* @remarks �����������������������ں�������ִ�У�
		* @sa @ref event
		*/
		/* ----------------------------------------------------------------------------*/
		virtual void sendEvent(pcwstr event, EventArgs* pArgs = NULL){
			EventList_t* l = m_event_table.find(event);
			if(l != NULL){
				for(EventList_t::iterator iter = l->begin(); iter != l->end(); ++iter){
					(*iter)->onEvent(event, pArgs, this);
				}
			}
		}
	};
}

namespace OneU
{
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief �ַ��¼�
	 */
	/* ----------------------------------------------------------------------------*/
	class CharEvent
	{
		wchar charCode;
	public:
		CharEvent(wchar code)
			: charCode(code){}
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��ȡ�ַ�����
		 * @returns �ַ�����
		 */
		/* ----------------------------------------------------------------------------*/
		wchar getChar() const{ return charCode;}
	};
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief ���̰����¼�
	 */
	/* ----------------------------------------------------------------------------*/
	class KeyEvent
	{
		uint32 scancode;
		bool bPress;//��Ϊtrue��Press������ΪRelease
	public:
		KeyEvent(uint32 scancode, bool bPress)
			: scancode(scancode), bPress(bPress){}
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��ȡ����ɨ����
		 * @returns ɨ����
		 */
		/* ----------------------------------------------------------------------------*/
		uint32 getCode(){ return scancode;}
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �ж��Ƿ����ͷŰ����¼� 
		 */
		/* ----------------------------------------------------------------------------*/
		bool isRelease(){ return !bPress; }
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �ж��Ƿ��ǰ��°����¼�
		 */
		/* ----------------------------------------------------------------------------*/
		bool isPress(){ return bPress; }
	};

	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief ��갴���¼�
	 */
	/* ----------------------------------------------------------------------------*/
	class MouseEvent
	{
		uint32 buttonID;
		bool bPress;//��Ϊtrue��Release������ΪPress
	public:
		MouseEvent(uint32 buttonID, bool bPress)
			: buttonID(buttonID), bPress(bPress){}
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��ȡ��갴��ID
		 * @returns ID 0��ʾ�����1��ʾ�Ҽ���2��ʾ�м���
		 */
		/* ----------------------------------------------------------------------------*/
		uint32 getButtonID(){ return buttonID;}
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �ж��Ƿ����ͷŰ����¼� 
		 */
		/* ----------------------------------------------------------------------------*/
		bool isRelease(){ return !bPress; }
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �ж��Ƿ��ǰ��°����¼�
		 */
		/* ----------------------------------------------------------------------------*/
		bool isPress(){ return !bPress; }
	};

	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief �����¼�������
	 *
	 * ���������¼����ࡣ�����Ը�����Խ��������¼���
	 * @remarks ��Ҫ����@ref IScene::pushInputFocus()������ע�ᵽջ�в��ܽ��յ������¼���
	 * @sa IGame::pushInputFocus()
	 */
	/* ----------------------------------------------------------------------------*/
	class IInputReceiver
		: public Interface
	{
	public:
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �ַ��¼���Ӧ
		 *
		 * @retval true �¼������´���
		 * @retval false �¼����´���
		 */
		/* ----------------------------------------------------------------------------*/
		virtual bool onChar(const CharEvent& event){ return true; }
		/* ----------------------------------------------------------------------------*/
		/**
		* @brief ���̰����¼���Ӧ
		* 
		* @retval true �¼������´���
		* @retval false �¼����´���
		*/
		/* ----------------------------------------------------------------------------*/
		virtual bool onKey(const KeyEvent& event){ return true; }
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��갴���¼���Ӧ
		 * 
		 * @retval true �¼������´���
		 * @retval false �¼����´���
		 */
		/* ----------------------------------------------------------------------------*/
		virtual bool onMouse(const MouseEvent& event){ return true; }
	};
	/*@cond INTERNAL_MPL*/
	//����������
	struct __CharFunctor
	{
		const CharEvent& m_event;
		__CharFunctor(const CharEvent& event) : m_event(event){}
		bool operator()(Handle<IInputReceiver> p){
			return SAFE_H(p)->onChar(m_event);
		}
	};
	struct __KeyFunctor
	{
		const KeyEvent& m_event;
		__KeyFunctor(const KeyEvent& event) : m_event(event){}
		bool operator()(Handle<IInputReceiver> p){
			return SAFE_H(p)->onKey(m_event);
		}
	};
	struct __MouseFunctor
	{
		const MouseEvent& m_event;
		__MouseFunctor(const MouseEvent& event) : m_event(event){}
		bool operator()(Handle<IInputReceiver> p){
			return SAFE_H(p)->onMouse(m_event);
		}
	};
	/*@endcond*///INTERNAL_MPL
}
