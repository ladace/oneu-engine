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

	/*
	template<class T>
	class ISEventListener{
	public:
		virtual void onEvent(T& event) = 0;
	};
	template<class T>
	class ISEventReceiver
		: public Interface
	{
	private:
		typedef InterfacePtr<ISEventListener<T>> HandlerHolder;
		typedef List<HandlerHolder> EventList_t;
		EventList_t m_event_list;
	public:
		virtual void addListener(IEventListener* listener){
			m_event_list.pushBack(listener);
		}
		virtual void trigger(T& event){
			for(EventList_t::iterator iter = m_event_list.begin(); iter != m_event_list.end(); ++iter){
				(*iter)->onEvent(event);
			}
		}
	};*/

	/* ----------------------------------------------------------------------------*/
	/** 
	* @brief �¼�������
	* 
	* �̳иýӿڿ���ʹ��ɴ����¼�
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
	class CharEvent
		: public EventArgs
	{
		wchar charCode;
	public:
		CharEvent(wchar code)
			: charCode(code){}
		wchar getCode(){ return charCode;}
	};
	class KeyEvent
	{
		dword scancode;
		bool bRelease;//��Ϊtrue��Release������ΪPress
	public:
		KeyEvent(dword scancode, bool bRelease)
			: scancode(scancode), bRelease(bRelease){}
		dword getCode(){ return scancode;}
		bool isRelease(){ return bRelease; }
		bool isPress(){ return !bRelease; }
	};
	class IInputReceiver
		: public Interface
	{
		bool m_bWillPropagate;
	public:
		void propagate(bool bPropagate){//reserved
			m_bWillPropagate = bPropagate;
		};
		bool willPropagate(){ return m_bWillPropagate; }
		virtual void onChar(CharEvent& event){}
		virtual void onKey(KeyEvent& event){}
	};
}