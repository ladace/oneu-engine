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
		enum COLOR_BLENDMODE{ CBM_NONE = 0, CBM_MODULATE = 1, CBM_ADD = 2, 
			CBM_LEFT = 0x10, CBM_RIGHT = 0x20, CBM_TOP = 0x30, CBM_DOWN = 0x40 };

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��Ⱦ�ڵ�
		 *
		 * ��װ��һ����Ⱦ������
		 * �̳д���������ͼ��ϵͳ�Ĺ��ܡ�
		 */
		/* ----------------------------------------------------------------------------*/
		class INode
			: public Interface
		{
		private:
			friend class INodeContainer;
			INodeContainer* m_pParent;
			List<_NodeTag>::iterator m_It;//��parent�����е������Ķ�Ӧ�Լ��ĵ�����
		public:
			bool visible;//visibleΪfalseʱ��ֹͣupdate ����ʾ
			bool active;//activeΪfalseʱ��ֹͣupdate
			INode() : m_pParent(NULL), visible(true), active(true) {}
			INodeContainer* getParent(){ return m_pParent; }
			~INode(){ detach(); }

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ʹ�����Ϊĳ���ڵ�Ķ���
			 * 
			 * @param parent ˫�׽ڵ�
			 * @param z ���
			 * @param tag ��ǩ
			 *
			 * @remarks �����ڻᱻ˫�׹���
			 */
			/* ----------------------------------------------------------------------------*/
			inline void attach(INodeContainer* parent, int z = 0, pcwstr tag = NULL);//��addChild����һ��
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �����˫�׵Ĺ�ϵ
			 *
			 * @remarks �����ڲ��ٱ�˫�׹���
			 */
			/* ----------------------------------------------------------------------------*/
			inline void detach();

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��Ⱦ����
			 *
			 * ��Ҫ����д�����䡣
			 * visibleΪtrueʱ�����á�
			 */
			/* ----------------------------------------------------------------------------*/
			virtual void paint() = 0;

			//ֻ��visible��activeΪtrueʱ�Żᱻ����
			virtual void update(){}

			//�ɱ���д
			virtual void describe(String& buffer, int depth){
				buffer.append(L"Unknown Node\n");
			}
			/**
			 * ��IVideo::render�����б����á�
			 */
			void visit_paint(){
				if(visible)
					paint();
			}
			void visit_update(){
				if(visible && active)
					update();
			}
			void getDescription(String& buffer, int depth = 0){
				describe(buffer, depth);
			}
		};


		struct _NodeTag
		{
			int z;
			INode* child;
			String* tag;
		};

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��Ⱦ�ڵ�����
		 *
		 * �������к��ӵ���Ⱦ�ڵ㡣
		 */
		/* ----------------------------------------------------------------------------*/
		class INodeContainer
			: public INode
		{
			friend void _DetachNodeFromParent(INode* node);
		protected:
			typedef List<_NodeTag> ListType;
			ListType m_Children;
			friend class INode;
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��Ӻ���
			 * 
			 * @param child ���ӽڵ�
			 * @param z ���
			 * @param tag ��ǩ
			 * 
			 * @returns �Ƿ�ɹ�
			 * @remarks ���ӵ������ڱ��������
			 */
			/* ----------------------------------------------------------------------------*/
			bool addChild(INode* child, int z = 0, pcwstr tag = NULL){
				if(child->m_pParent != NULL){
					//GetGame().getBroadcast().message(tag == NULL ? L"Node Container fails to add Child." : String().format(L"Node Container fails to add Child, Tag:%s", tag))
					return false;//fail to add
				}
				ListType::iterator iter;
				for(iter = m_Children.begin(); iter != m_Children.end(); ++iter)
					if(iter->z > z)
						break;
				ListType::iterator it = m_Children.insert(iter);
				it->child = child;
				it->z = z;
				if(tag == NULL)it->tag = NULL;
				else it->tag = ONEU_NEW(String(tag));

				child->m_pParent = this;
				child->m_It = it;
				return true;
			}
			virtual void paint(){
				for(ListType::iterator it = m_Children.begin(); it != m_Children.end(); ++it){
					it->child->visit_paint();
				}
			}
			virtual void update(){
				for(ListType::iterator it = m_Children.begin(); it != m_Children.end(); ++it){
					it->child->visit_update();
				}
			}
			virtual void describe(String& buffer, int depth){
				buffer.append(L"Node Container\n");
				++depth;
				for(ListType::iterator it = m_Children.begin(); it != m_Children.end(); ++it){
					for(int i = 0; i < depth; ++i){
						buffer.append(L"\t");
					}
					it->child->getDescription(buffer, depth);
				}
			}
			virtual ~INodeContainer(){
				for(ListType::iterator it = m_Children.begin(); it != m_Children.end();){
					if(it->tag != NULL) ONEU_DELETE(it->tag);
					(it++)->child->destroy();//����destroyʱ��ʹnode detach������ɾ��it��ָԪ�ء�����ʹ������д�����������ʧЧ��ɵ����⡣
				}
			}
		};

		inline void INode::attach(INodeContainer* parent, int z /* = 0 */, pcwstr tag /* = NULL */){
			parent->addChild(this, z, tag);
		}
		inline void INode::detach(){
			if(m_pParent != NULL){
				m_pParent->m_Children.erase(m_It);
				m_pParent = NULL;
			}
		}

		//��Ⱦ����
		class IRenderScene
			: public INodeContainer
		{
		private:
			IRenderScene(){}
			friend class IVideo;
		public:
			void destroy(){ ONEU_DELETE(this); }
			void describe(String& buffer, int depth){
				buffer.append(L"<render scene>");
				INodeContainer::describe(buffer, depth);
			}
		};
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ͼ�������ӿ�
		 */
		/* ----------------------------------------------------------------------------*/
		class IImage
			: public Interface
		{
		public:
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ������ü���
			 * 
			 * @returns �µ����ü���
			 */
			/* ----------------------------------------------------------------------------*/
			virtual uint addRef() = 0;
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief �ͷ����ü���
			 *
			 * ������ü����ͷź�Ϊ0��������ͼ�Ρ�
			 * 
			 * @returns �µ����ü���
			 */
			/* ----------------------------------------------------------------------------*/
			virtual uint release() = 0;

			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡͼ�ο��
			 * 
			 * @returns ���
			 * @remarks ���������ȣ�����Դ�ļ��Ŀ�ȡ�
			 */
			/* ----------------------------------------------------------------------------*/
			virtual uint getWidth() = 0;
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��ȡͼ�θ߶�
			 * 
			 * @returns �߶�
			 * @remarks ��������߶ȣ�����Դ�ļ��ĸ߶ȡ�
			 */
			/* ----------------------------------------------------------------------------*/
			virtual uint getHeight() = 0;
		};
	}

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
	protected:
		video::IRenderScene* m_pRenderScene;
		video::INodeContainer* m_pRoot;
	public:
		IVideo() : m_pRenderScene(NULL), m_pRoot(NULL){}
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
		 * @brief ��ʼ��ϵͳ
		 * 
		 * @param width ҳ����
		 * @param height ҳ��߶�
		 * @param bWindowed �Ƿ񴰿ڻ�
		 *
		 * @remarks һ�㲻��Ҫ�ͻ�����
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void init(uint width, uint height, bool bWindowed) = 0;
		//if width or heightΪ0 ����ʹ��Ŀǰ������
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �л��豸
		 *
		 * �ú������ͷ�������Դ���ؽ����Ǹ�����ĺ�����
		 * 
		 * @param width ��ҳ����
		 * @param height ��ҳ��߶�
		 * @param bWindowed �Ƿ񴰿ڻ�
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void switchDevice(uint width, uint height, bool bWindowed) = 0;
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
		*/
		/* ----------------------------------------------------------------------------*/
		virtual void update() = 0;
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
		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ���ñ任����
		 *
		 * @param m �任����
		 */
		/* ----------------------------------------------------------------------------*/
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
		virtual void setBlendColor(dword mode, color_t color) = 0;
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
		video::IRenderScene* createRenderScene(){ return ONEU_NEW(video::IRenderScene);}
		//@}
		
		//others
		//��̫��Ҫ��
		//��Shell�����ϵͳ����Ϣ
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

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ͼ������
	 *
	 * �ɵ�����������ʹ�á�һ���IVideo::loadImage���ص�ֱֵ���ô����ͱ������С�
	 */
	/* ----------------------------------------------------------------------------*/
	class image_t
	{
		video::IImage* m_pI;
	public:
		image_t(): m_pI(NULL){}
		image_t(video::IImage* i): m_pI(i){
			if(m_pI != NULL)
				m_pI->addRef();
		}
		image_t(const image_t& rhs): m_pI(rhs.m_pI){
			if(m_pI != NULL)
				m_pI->addRef();
		}
		~image_t(){
			if(m_pI != NULL)
				m_pI->release();
		}
		image_t& operator=(const image_t& rhs){
			if(m_pI != NULL)
				m_pI->release();
			m_pI = rhs.m_pI;
			m_pI->addRef();
			return *this;
		}
		image_t& operator=(video::IImage* i){
			if(m_pI != NULL)
				m_pI->release();
			m_pI = i;
			m_pI->addRef();
			return *this;
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡͼ��ӿ�
		 * 
		 * @returns ͼ��ӿ�
		 */
		/* ----------------------------------------------------------------------------*/
		video::IImage* operator->(){ return m_pI; }
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��ȡͼ��ӿ�
		 * 
		 * @returns ͼ��ӿ�
		 */
		/* ----------------------------------------------------------------------------*/
		video::IImage* get(){ return m_pI; }
	};

}
