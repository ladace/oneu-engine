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
 * @file Game.h
 * @brief ��Ϸ��ϵͳ
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "OUEDefs.h"
#include "Stack.h"
#include "Event.h"

namespace OneU
{
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @defgroup group_game ��Ϸ��ģ��
	 */
	/* ----------------------------------------------------------------------------*/
	//@{
	class IGame;
	class IVideo;
	class IStereo;
	class IControl;
	class IScene;
	class IBroadcast;
	class IInputReceiver;

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ȡ��Ϸ����
	 * 
	 * @returns ��Ϸ����ӿ�
	 * @sa Game_create, Game_build, Game_destroy
	 */
	/* ----------------------------------------------------------------------------*/
	ONEU_API IGame& GetGame();//interface

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��Ϸ�ӿ�
	 */
	/* ----------------------------------------------------------------------------*/
	class IGame
		: public Interface
	{
	protected:
		IBroadcast* m_pBroadcast;
		IVideo* m_pVideo;
		IStereo* m_pStereo;
		IControl* m_pControl;
		IScene* m_pScene;
		Factory<IBroadcast>::type m_BroadcastFactory;
		Factory<IVideo>::type m_VideoFactory;
		Factory<IStereo>::type m_StereoFactory;
		Factory<IControl>::type m_ControlFactory;

		Chain<IInputReceiver*> m_InputFocusStack;
	public:
		IGame()
			: m_pBroadcast(NULL), m_pVideo(NULL), m_pStereo(NULL), m_pControl(NULL), m_pScene(NULL),
			  m_BroadcastFactory(NULL), m_VideoFactory(NULL), m_StereoFactory(NULL), m_ControlFactory(NULL)
		{}
		~IGame(){
			ONEU_ASSERT(m_pScene == NULL);
			ONEU_ASSERT(m_pControl == NULL);
			ONEU_ASSERT(m_pStereo == NULL);
			ONEU_ASSERT(m_pVideo == NULL);
			ONEU_ASSERT(m_pBroadcast == NULL);
		}

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ�㲥����
		 * 
		 * @returns �㲥����
		 */
		/* ----------------------------------------------------------------------------*/
		virtual IBroadcast& getBroadcast(){ return *m_pBroadcast; }
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡͼ��ϵͳ����
		 * 
		 * @returns ͼ��ϵͳ����
		 */
		/* ----------------------------------------------------------------------------*/
		virtual IVideo& getVideo(){ return *m_pVideo; }
		virtual IStereo& getStereo(){ return *m_pStereo;}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ����ϵͳ����
		 * 
		 * @returns ����ϵͳ����
		 */
		/* ----------------------------------------------------------------------------*/
		virtual IControl& getControl(){ return *m_pControl;}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ���������
		 * 
		 * @returns ���������
		 */
		/* ----------------------------------------------------------------------------*/
		virtual IScene& getScene(){ return *m_pScene; }

		//��Game_create֮��init֮ǰ����
		//������Ϸ��ģ��Ĺ���
		virtual Factory<IBroadcast>::type setBroadcastFactory(Factory<IBroadcast>::type c){
			Factory<IBroadcast>::type ret = m_BroadcastFactory;
			m_BroadcastFactory = c;
			return ret;
		}
		virtual Factory<IVideo>::type setVideoFactory(Factory<IVideo>::type c){
			Factory<IVideo>::type ret = m_VideoFactory;
			m_VideoFactory = c;
			return ret;
		}
		virtual Factory<IStereo>::type setStereoFactory(Factory<IStereo>::type c){
			Factory<IStereo>::type ret = m_StereoFactory;
			m_StereoFactory = c;
			return ret;
		}
		virtual Factory<IControl>::type setControlFactory(Factory<IControl>::type c){
			Factory<IControl>::type ret = m_ControlFactory;
			m_ControlFactory = c;
			return ret;
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �滻����
		 *
		 * ����ǰ������滻���³�����
		 * 
		 * @param newscene �³�����ַ
		 * 
		 * @returns ��ǰ�������ַ��
		 *
		 * @remarks ��������Զ�����Ϸ��������ʱ��ɾ����
		 */
		/* ----------------------------------------------------------------------------*/
		//�滻������ջջ������ ���ؾɳ���
		virtual IScene* replaceScene(IScene* newscene) = 0;

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ʼ����Ϸ
		 * 
		 * @param WindowName ���ڵ�����
		 * @param width ���ڿ��
		 * @param height ���ڸ߶�
		 * @param bWindowed �Ƿ񴰿ڻ�
		 * 
		 * @returns ��ʾ�Ƿ��ʼ���ɹ�
		 * @retval true ��ʼ���ɹ�
		 * @retval false ��ʼ��ʧ��
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void init(pcwstr WindowName, uint32 width, uint32 height, bool bWindowed) = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ������Ϸ
		 *
		 * ������Ϸ��ѭ���������˳�ʱGame������Զ����١�
		 * 
		 * @returns ���򷵻�ֵ��һ�㽫�÷���ֵ��Ϊ���򷵻�ֵ���ء�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual int run() = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief �˳�����
		*/
		/* ----------------------------------------------------------------------------*/
		virtual void quit() = 0;

		//����
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ����ÿһ֡
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void onFrame() = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �ڴ��ڵõ���ʧȥ����ʱִ��
		 *
		 * @param bActive ��ʾ�ǵõ�����ʧȥ���㡣ΪTRUE�ǵõ����㣻ΪFALSE��ʧȥ���㡣
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void onActiveWindow(bool bActive) = 0;

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���ô�������
		 * 
		 * @param title ��������
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void setWindowTitle(pcwstr title) = 0;
		virtual vector2i_t getWindowPos() = 0;
		virtual void setWindowPos(const vector2i_t& newPos) = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ��ǰFPS
		 * 
		 * @returns FPS
		 */
		/* ----------------------------------------------------------------------------*/
		virtual float getFPS() = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ��ǰ֡��ǰһ֡��ʱ����
		 * 
		 * @returns ʱ�������Ժ�����㡣
		 */
		/* ----------------------------------------------------------------------------*/
		virtual float getTimeInterval() = 0;

		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �������뽹��
		 *
		 * @param pED ������Ϊ�����EventDispatcher����ΪNULL����Ϊ���뽹���EventDispatcher���Խ��յ�CHAR��Ŀǰֻ����CHAR����KEYDOWN���¼���
		 *
		 * @return �ɵ�EventDispatcher��
		 */
		/* ----------------------------------------------------------------------------*/
		virtual IInputReceiver* replaceInputFocus(IInputReceiver* pIR){
			IInputReceiver* ret = m_InputFocusStack.pop();
			m_InputFocusStack.push(pIR);
			return ret;
		}
		virtual void pushInputFocus(IInputReceiver* pIR){
			m_InputFocusStack.push(pIR);
		}
		virtual IInputReceiver* popInputFocus(){
			return m_InputFocusStack.pop();
		}
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ����Char�¼���
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void onChar(const CharEvent& event){
			m_InputFocusStack.handle(__CharFunctor(event));
		}
		virtual void onKey(const KeyEvent& event){
			m_InputFocusStack.handle(__KeyFunctor(event));
		}

		//tools
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ����Shellָ��
		 *
		 * @param command ָ���ַ���
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void runShell(pcwstr command) = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ���������Ϣ
		 *
		 * �����Ĭ��Ϊ��Ϸ����Shell��
		 *
		 * @param data ��Ϣ�ַ���
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void output(pcwstr data) = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��Ϸ�����
		 *
		 * ����output�������
		 */
		/* ----------------------------------------------------------------------------*/
		class Stream
			: public IOStreamMaker
		{
			IGame* m_pTarget;
		public:
			Stream(IGame* pTarget)
				: m_pTarget(pTarget){}
			void output(pcwstr data){
				m_pTarget->output(data);
			}
		};
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��ȡ��Ϸ�����
		 *
		 * ����output�������
		 *
		 * @return �����
		 * @sa output
		 */
		/* ----------------------------------------------------------------------------*/
		virtual Stream stream(){
			return Stream(this);
		}

		//��̫��Ҫ��
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �����̨�����Ϸ�����Ϣ
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void showInfo() = 0;
	};

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ������Ϸ��̬
	 * 
	 * @param gf ��Ϸ������һ�㴫��@ref Game_create
	 * 
	 * @sa Game_create, Game_destroy, GetGame
	 */
	/* ----------------------------------------------------------------------------*/
	ONEU_API void Game_build(Factory<IGame>::type gf);
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ������Ϸ��̬
	 * 
	 * @sa Game_create, Game_build, GetGame
	 */
	/* ----------------------------------------------------------------------------*/
	ONEU_API void Game_destroy();
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��Ϸ����
	 *
	 * һ����Ϊ��������@ref Game_build
	 * 
	 * @returns �µ���Ϸ����ӿ�
	 */
	/* ----------------------------------------------------------------------------*/
	ONEU_API IGame* Game_create();

	
	//@}

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ȡ�㲥����
	 * 
	 * @returns �㲥����
	 */
	/* ----------------------------------------------------------------------------*/
	inline IBroadcast& GetBroadcast(){ return GetGame().getBroadcast(); }
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ȡͼ��ϵͳ����
	 * 
	 * @returns ͼ��ϵͳ����
	 */
	/* ----------------------------------------------------------------------------*/
	inline IVideo& GetVideo(){ return GetGame().getVideo(); }
	inline IStereo& GetStereo(){ return GetGame().getStereo(); }
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ȡ����ϵͳ����
	 * 
	 * @returns ����ϵͳ����
	 */
	/* ----------------------------------------------------------------------------*/
	inline IControl& GetControl(){ return GetGame().getControl(); }
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ȡ���������
	 * 
	 * @returns ���������
	 */
	/* ----------------------------------------------------------------------------*/
	inline IScene& GetScene(){ return GetGame().getScene(); }
}
