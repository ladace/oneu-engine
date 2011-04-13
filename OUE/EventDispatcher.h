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
 * @file EventDispatcher.h
 * @brief �¼��ɷ���
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "OUEDefs.h"
#include "List.h"
#include "Table.h"

//(�¼�������event.h�У�

namespace OneU
{
	class IEventDispatcher;
	class EventArgs{};

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
		virtual void onTrigger(pcwstr event, EventArgs* pArg, IEventDispatcher* source) = 0;
	};

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
					(*iter)->onTrigger(event, pArgs, this);
				}
			}
		}
	};
}
