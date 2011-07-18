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
 * @file Video.h
 * @brief ͼ��ϵͳ
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "OUEDefs.h"
#include "List.h"
#include "Vector.h"
#include "Matrix.h"
#include "TplTypes.h"

//IVideo Game�������֮һ
namespace OneU
{
	namespace video
	{
		struct _NodeTag;
		class INode;
		class INodeContainer;

		class IRenderScene;
		class IImage;
		class IModule;

		enum BLENDMODE{ BM_NORMAL = 0, BM_ADD };
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��ɫ���ģʽ
		 *
		 * CBM_LEFT��ʾ��ɫֻ�����벿������CBM_MODULATE��λ������Ϊ��ʶ������ͬ��
		 *
		 * @sa IVideo::setBlendColor
		 */
		/* ----------------------------------------------------------------------------*/
		enum COLOR_BLENDMODE{ CBM_NONE = 0, CBM_ADD = 1, CBM_MODULATE = 2,
			CBM_LEFT = 0x10, CBM_RIGHT = 0x20, CBM_TOP = 0x30, CBM_DOWN = 0x40 };

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ͼ�������ӿ�
		 */
		/* ----------------------------------------------------------------------------*/
		class IImage
			: public InterfaceRef
		{
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡͼ�ο��
			 * 
			 * @returns ���
			 * @remarks ���������ȣ�����Դ�ļ��Ŀ�ȡ�
			 */
			/* ----------------------------------------------------------------------------*/
			virtual uint32 getWidth() = 0;
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡͼ�θ߶�
			 * 
			 * @returns �߶�
			 * @remarks ��������߶ȣ�����Դ�ļ��ĸ߶ȡ�
			 */
			/* ----------------------------------------------------------------------------*/
			virtual uint32 getHeight() = 0;
		};

		struct Mode
		{
			vector2u_t size;
			uint32 refreshRate;
		};
	}

	typedef RefWrapper<video::IImage> image_t;
	/**
	 * @addtogroup group_game
	 */
	//@{
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ͼ��ϵͳ�ӿ�
	 * 
	 * @remarks ֻ֧�ֵ�Video�����ʹ���˶��Video������ʵ�ֻ�������⡣
	 */
	/* ----------------------------------------------------------------------------*/
	class IVideo
		: public Interface
	{
		friend class video::IModule;
		List<video::IModule*> m_ModuleList;
	protected:
		video::IRenderScene* m_pRenderScene;
		video::INodeContainer* m_pRoot;
	public:
		IVideo() : m_pRenderScene(NULL), m_pRoot(NULL){}
		inline ~IVideo();
		/* ----------------------------------------------------------------------------*/
		/**
		* @brief ע��ģ��
		*
		* @param module ģ���ַ
		* @remarks һ�㲻��ͻ�ֱ�ӵ��á�
		*/
		/* ----------------------------------------------------------------------------*/
		List<video::IModule*>::iterator __addModule(video::IModule* module);
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡͼ��ϵͳ������
		 * 
		 * @returns ͼ��ϵͳ������
		 */
		/* ----------------------------------------------------------------------------*/
		virtual LPCTSTR getName() = 0;

		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ׼��ϵͳ
		 *
		 * @remarks ���ô˺�������Խ��м���豸�����Ĳ�����
		 * ��������豸������Ҳ���Բ����øú�������init�������Զ����øú�����
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void prepare() = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ʼ��ϵͳ
		 * 
		 * @param width ҳ����
		 * @param height ҳ��߶�
		 * @param bWindowed �Ƿ񴰿ڻ�
		 *
		 * @remarks һ�㲻��Ҫ�ͻ�����
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void init(uint32 width, uint32 height, bool bWindowed) = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �л��豸
		 *
		 * �ú������ͷ�������Դ���ؽ����Ǹ�����ĺ�����
		 * 
		 * @param width ��ҳ����
		 * @param height ��ҳ��߶�
		 * @param bWindowed �Ƿ񴰿ڻ�
		 * @remarks ���width����heightΪ0������ʹ��Ŀǰ�����á�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void switchDevice(uint32 width, uint32 height, bool bWindowed) = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��Ⱦ
		 *
		 * ����ǰ��Ⱦ������Ⱦ����ǰ��ȾĿ���ϡ�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void render() = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ���¶���
		*
		* ���µ�ǰ��Ⱦ������
		* @param dt ʱ�䳤��
		*/
		/* ----------------------------------------------------------------------------*/
		virtual void update(float dt) = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ҳ
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void flip() = 0;

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ѯ�ʴ��ڻ�
		 * 
		 * @returns �Ƿ񴰿ڻ�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual bool isWindowed() = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ�豸ҳ����
		 *
		 * �����@ref init��@ref switchDeviceָ���Ĳ�����
		 * 
		 * @returns ҳ��������
		 */
		/* ----------------------------------------------------------------------------*/
		virtual vector2u_t getDeviceSize() = 0;

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡͼƬ
		 * 
		 * @param filename ͼƬ���ļ���
		 * 
		 * @returns ͼƬ�ӿڡ����ü���Ϊ0��һ��ֱ�Ӹ�ֵ��@ref image_t�����
		 *
		 * @attention ͼƬ�ӿڱ�����Video����ǰ���١�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual image_t loadImage(pcwstr filename) = 0;

		/**
		 * @name ��Ⱦ����
		 * @{
		 */
		//���Կ��ǵ�����ȡRenderer��
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��Ⱦͼ��
		 *
		 * ��ͼ���Ծ��εķ�ʽ��Ⱦ��Ŀ�ꡣ
		 * ��������任��
		 * ��Ļ����ռ���D3DΪ׼����Ŀǰ��
		 *
		 * @param image ͼ��
		 * @param dest Ŀ��λ��
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void renderImage(video::IImage& image, const rect& dest = rect(0.0f, 0.0f, 1.0f, 1.0f)) = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��Ⱦͼ��direct
		 *
		 * ��ͼ���Ծ��εķ�ʽ��Ⱦ��Ŀ�ꡣ
		 * ����������任��
		 * ��Ļ����ռ���D3DΪ׼����Ŀǰ��
		 *
		 * @param image ͼ��
		 * @param dest Ŀ��λ�á�������Ϊ��λ��
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void renderImage_d(video::IImage& image, const rect& dest) = 0;
		virtual void setTransform(const matrix& m) = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ����ͼ��Դ����
		 *
		 * ָʾ��Ⱦʱʹ��ͼ����һ���֡�
		 *
		 * @param src Դ���Ρ���һ����λ����1��ʾ�ҡ��£�0��ʾ���ϡ�Ŀǰ�����Ǵ���1�������
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void selectImageSourceRect(const rect& src = rect(0.0f, 0.0f, 1.0f, 1.0f)) = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ������ɫ���
		 *
		 * @param mode ���ģʽ��ʶ����ʶΪCOLORBLENDMODE������λ��
		 * @param color �����ɫ��alphaλ��Ч��Ϊ����ģʽ��
		 *
		 * @sa COLORBLENDMODE
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void setBlendColor(uint32 mode, color_t color) = 0;
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ���û��ģʽ
		 *
		 * @param mode ģʽ��ʶ
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void setBlendMode(video::BLENDMODE mode) = 0;
		/*@}*/

		/**
		 * @name ��Ⱦ������
		 * ����������һ�㲻���û�ʹ��
		 */
		//@{
		video::INodeContainer& getRoot(){ return *m_pRoot; }
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ���Ⱦ����
		 * 
		 * @returns ��Ⱦ����
		 */
		/* ----------------------------------------------------------------------------*/
		video::IRenderScene* getRenderScene(){
			return m_pRenderScene;
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ���û��Ⱦ����
		 * 
		 * @param pRenderScene �µ���Ⱦ����
		 * 
		 * @returns �ɵ���Ⱦ����
		 * @remarks �����ڲ�������
		 */
		/* ----------------------------------------------------------------------------*/
		virtual video::IRenderScene* setRenderScene(video::IRenderScene* pRenderScene){
			video::IRenderScene* ret = m_pRenderScene;
			m_pRenderScene = pRenderScene;
			return ret;
		}
		
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ������Ⱦ����
		 * 
		 * @returns �µ���Ⱦ����
		 */
		/* ----------------------------------------------------------------------------*/
		inline video::IRenderScene* createRenderScene();
		//@}

		/**
		 * @name �豸��麯��
		 * @remarks ����ǰҪ����prepare���������init������
		 */
		//@{
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡ���õ���ʾģʽ
		 * 
		 * @param buf ����ʾģʽ��Ϊ�б��ء�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void getAvailableMode(List<video::Mode>& buf) = 0;
		//@}
		//others
		//��̫��Ҫ��
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief �����Ϣ
		 *
		 * ��Shell�����ϵͳ����Ϣ
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void showInfo() = 0;
	};

	//in game.cpp
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ͼ��ϵͳ����
	 * 
	 * @returns ͼ��ϵͳ�ӿ�
	 */
	/* ----------------------------------------------------------------------------*/
	ONEU_API IVideo* Video_create();
	//@}
}

#include "VideoNode.h"

namespace OneU
{
	namespace video
	{

		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��Ⱦ����
		 *
		 * @remarks ÿһ��������Ӧһ����Ⱦ������
		 */
		/* ----------------------------------------------------------------------------*/
		class IRenderScene
			: public INodeContainer
		{
		private:
			IRenderScene(){}
			friend class IVideo;
		public:
			void _describe(String& buffer, int depth){
				buffer.append(L"<render scene>");
				INodeContainer::_describe(buffer, depth);
			}
		};
	}
	inline video::IRenderScene* IVideo::createRenderScene(){ return ONEU_NEW video::IRenderScene;}

	namespace video
	{
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ͼ����ģ��
		 * 
		 * �ɼ̳���ʵ��ͼ��ϵͳ����ģ�顣
		 * @remarks ��ģ��Ϊ�������ڽ������ע�ᵽͼ��ϵͳ�����ͼ��ϵͳ����ǰ�Զ����١�
		 */
		/* ----------------------------------------------------------------------------*/
		class IModule
			: public Interface
		{
			friend class IVideo;
			List<IModule*>::iterator m_ID;
		public:
			IModule(){
				m_ID = GetVideo().__addModule(this);
			}
			~IModule(){
				GetVideo().m_ModuleList.erase(m_ID);
			}
		};
	}
	inline IVideo::~IVideo(){
		for(List<video::IModule*>::iterator it = m_ModuleList.begin(); it != m_ModuleList.end();)//��������ģ��
			ONEU_DELETE *(it++);
	}
	inline List<video::IModule*>::iterator IVideo::__addModule(video::IModule* module){
		m_ModuleList.pushBack(module);
		return m_ModuleList.end().prev();
	}
}