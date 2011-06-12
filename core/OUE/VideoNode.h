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
* @file VideoNode.h
* @brief ��Ⱦ���
* @author Ladace
* @version 1.0.0.1
* @date 2011-05-31
*/
#pragma once
#include "Video.h"

namespace OneU
{
	inline IVideo& GetVideo();
	namespace video
	{
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

			struct _TransformInfo2D{
				matrix m;
				bool mIsReady;
				float x, y;
				float scalex, scaley;
				float rotz;
			};
			union{
				_TransformInfo2D* _2;
				//why union? - reserved.
			}Transform;

		public:
			/**
			 * @brief ������
			 *
			 * ����Ϊfalseʱ��ֹͣupdate�����Ҳ���ʾ��
			 */
			bool visible;
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ���
			 *
			 * ����Ϊfalseʱ��ֹͣupdate��
			 */
			/* ----------------------------------------------------------------------------*/
			bool active;
			INode() : m_pParent(NULL), visible(true), active(true){memset(&Transform, 0, sizeof(Transform)); }

			~INode(){
				detach();
				if(Transform._2)
					ONEU_DELETE_T(Transform._2);
			}


			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ��ȡ�����
			 *
			 * @remarks ��û�и��ף��򷵻�NULL��
			 */
			/* ----------------------------------------------------------------------------*/
			INodeContainer* getParent(){ return m_pParent; }

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
			 * ��Ҫ����д�����䣬�������Ⱦ�ý��ʱ����Ⱦ������
			 * @remarks visibleΪtrueʱ�����á�
			 */
			/* ----------------------------------------------------------------------------*/
			virtual void paint() = 0;

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ���º���
			 *
			 * ��Ҫ����д�����䣬����ϸ��½��ʱ�Ĳ�����
			 * @remarks ֻ��visible��activeΪtrueʱ�Żᱻ���á�
			 */
			/* ----------------------------------------------------------------------------*/
			virtual void update(){}

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ���ֺ���
			 *
			 * ����д��Ϊ�ı�ý������ƣ�ʹ�����ڲ��ԡ�
			 * @returns �ýڵ������
			 */
			/* ----------------------------------------------------------------------------*/
			virtual pcwstr name(){
				return L"Unknown Node";
			}

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ��������
			 *
			 * ����д�����ĶԸý�����������ݡ�
			 * @remarks Ĭ�ϵ���name���������ý�㣬������ӽڵ��ٽ���һһ������һ�㲻��Ҫ�ͻ���д��
			 */
			/* ----------------------------------------------------------------------------*/
			virtual void _describe(String& buffer, int depth){
				buffer.append(name());
				buffer.append(L"\n");
			}


			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ��Ⱦ
			 * @remarks ��IVideo::render�����б����á�
			 */
			/* ----------------------------------------------------------------------------*/
			void visit_paint(){
				if(visible){
					bool b = _beginTransform();
					paint();
					if(b) GetVideo().popMatrix();
				}
			}

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ����
			 * @remarks ��IVideo::update�����б����á�
			 */
			/* ----------------------------------------------------------------------------*/
			void visit_update(){
				if(visible && active)
					update();
			}
			void getDescription(String& buffer, int depth = 0){
				_describe(buffer, depth);
			}


			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ����2D�任
			 *
			 * Ϊ�ڵ㴴��2D�任���ڻ���ʱ���Զ����б任�����任����ѹ�����ջ����
			 * @remarks �����任��@ref setX�Ⱥ������á�
			 */
			/* ----------------------------------------------------------------------------*/
			void create2DTransform(){
				if(Transform._2) return;
				Transform._2 = ONEU_NEW_T(_TransformInfo2D);
				memset(Transform._2, 0, sizeof(_TransformInfo2D));
				Transform._2->scalex = Transform._2->scaley = 1.0f;
			}

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ��ʼ�任
			 *
			 * ����б任�����򽫾���ѹ�����ջ��
			 * @remarks ����ʱ���á�
			 */
			/* ----------------------------------------------------------------------------*/
			bool _beginTransform(){
				if(Transform._2){
					if(!Transform._2->mIsReady){
						Transform._2->mIsReady = true;
						Transform._2->m = 
							matrix().setScale(vector3(Transform._2->scalex, Transform._2->scaley, 1.0f))
							* matrix().setRotation(vector3(0.0f, 0.0f, Transform._2->rotz))
							* matrix().setTranslation(vector3(Transform._2->x, Transform._2->y, 0.0f));
					}
					GetVideo().pushMatrix(Transform._2->m);
					return true;
				}
				return false;
			}

			/**
			 * @name �任���Բ�������
			 */
			//@{
			void setX(float x){
				if(Transform._2){
					Transform._2->x = x;
					Transform._2->mIsReady = false;
				}else ONEU_ASSERT(FALSE);
			}
			float getX() const{
				if(Transform._2){
					return Transform._2->x;
				}else ONEU_ASSERT(FALSE);
				return 0.0f;
			}
			void setY(float y){
				if(Transform._2){
					Transform._2->y = y;
					Transform._2->mIsReady = false;
				}else ONEU_ASSERT(FALSE);
			}
			float getY() const{
				if(Transform._2){
					return Transform._2->y;
				}else ONEU_ASSERT(FALSE);
				return 0.0f;
			}
			void setRotation(float z){
				if(Transform._2){
					Transform._2->rotz = z;
					Transform._2->mIsReady = false;
				}else ONEU_ASSERT(FALSE);
			}
			float getRotation() const{
				if(Transform._2){
					return Transform._2->rotz;
				}else ONEU_ASSERT(FALSE);
				return 0.0f;
			}
			void setScaleX(float ns){
				if(Transform._2){
					Transform._2->scalex = ns;
					Transform._2->mIsReady = false;
				}else ONEU_ASSERT(FALSE);
			}
			float getScaleX() const{
				if(Transform._2){
					return Transform._2->scalex;
				}else ONEU_ASSERT(FALSE);
				return 0.0f;
			}
			void setScaleY(float ns){
				if(Transform._2){
					Transform._2->scaley = ns;
					Transform._2->mIsReady = false;
				}else ONEU_ASSERT(FALSE);
			}
			float getScaleY() const{
				if(Transform._2){
					return Transform._2->scaley;
				}else ONEU_ASSERT(FALSE);
				return 0.0f;
			}
			//@}
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
			virtual ~INodeContainer(){
				for(ListType::iterator it = m_Children.begin(); it != m_Children.end();){
					if(it->tag != NULL) ONEU_DELETE_T(it->tag);
					ONEU_DELETE (it++)->child;//����destroyʱ��ʹnode detach������ɾ��it��ָԪ�ء�����ʹ������д�����������ʧЧ��ɵ����⡣
				}
			}
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
				else it->tag = ONEU_NEW_T(String(tag));

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
			virtual pcwstr name(){
				return L"NodeContainer";
			}
			virtual void _describe(String& buffer, int depth){
				INode::_describe(buffer, depth);
				++depth;
				for(ListType::iterator it = m_Children.begin(); it != m_Children.end(); ++it){
					for(int i = 0; i < depth; ++i){
						buffer.append(L"\t");
					}
					it->child->getDescription(buffer, depth);
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
	}
}