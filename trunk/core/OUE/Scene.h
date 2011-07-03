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
 * @file Scene.h
 * @brief ����
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "OUEDefs.h"
#include "Game.h"
#include "Video.h"

namespace OneU
{
	/**
	 * @addtogroup group_game
	 */
	//@{
	
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ������
	 *
	 * ��������߼���
	 * �̳и�������д�Գ����߼��Ŀ��ơ�
	 * ��Ϸ����������֮һ��
	 */
	/* ----------------------------------------------------------------------------*/
	class IScene
		: public Interface
	{
		video::IRenderScene* m_pRenderScene;
		Chain< Handle<IInputReceiver> > m_InputFocusStack;
	public:
		IScene(){ m_pRenderScene = GetVideo().createRenderScene(); }
		~IScene(){ ONEU_DELETE m_pRenderScene; }

		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �滻���뽹��
		 *
		 * ��ջ��InputReceiver�滻�ɸ���InputReceiver��
		 *
		 * @param pIR ���滻Ϊ�����InputReceiver����ΪNULL����Ϊ���뽹���EventDispatcher���Խ��յ�Char��Key�¼���
		 *
		 * @return �ɵ�InputReceiver��
		 * @sa pushInputFocus
		 */
		/* ----------------------------------------------------------------------------*/
		virtual IInputReceiver* replaceInputFocus(IInputReceiver* pIR){
			IInputReceiver* ret = SAFE_H(m_InputFocusStack.pop());
			m_InputFocusStack.push(pIR);
			return ret;
		}
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ���뽹��ѹջ
		 *
		 * @param pIR ��ѹջ�����뽹�㡣
		 * @remarks ���뽹��������ݰ������������ݡ�ջ�����Ƚ��������¼���Ȼ�����ѡ����ֹ�����´��ݡ�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void pushInputFocus(IInputReceiver* pIR){
			return m_InputFocusStack.push(pIR);
		}
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ���뽹�㵯ջ
		 * @returns ջ�������뽹��
		 * @sa pushInputFocus
		 */
		/* ----------------------------------------------------------------------------*/
		virtual IInputReceiver* popInputFocus(){
			return SAFE_H(m_InputFocusStack.pop());
		}
		/* ----------------------------------------------------------------------------*/
		/**
		* @brief �����ַ��¼���
		*/
		/* ----------------------------------------------------------------------------*/
		virtual void onChar(const CharEvent& event){
			m_InputFocusStack.handle(__CharFunctor(event));
		}
		/* ----------------------------------------------------------------------------*/
		/**
		* @brief ������̰����¼���
		*/
		/* ----------------------------------------------------------------------------*/
		virtual void onKey(const KeyEvent& event){
			m_InputFocusStack.handle(__KeyFunctor(event));
		}
		/* ----------------------------------------------------------------------------*/
		/**
		* @brief ������갴���¼���
		*/
		/* ----------------------------------------------------------------------------*/
		virtual void onMouse(const MouseEvent& event){
			m_InputFocusStack.handle(__MouseFunctor(event));
		}

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���³���
		 *
		 * ÿ֡������һ�Ρ���д�˺��������Ƴ����߼���
		 * @param dt ʱ�䳤��
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void update(float dt) = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ�ó�������Ⱦ������
		 * 
		 * @returns ��Ⱦ��������
		 */
		/* ----------------------------------------------------------------------------*/
		video::IRenderScene* getRenderScene(){
			return m_pRenderScene;
		}
	};
	//@}
}
