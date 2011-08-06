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
			friend class ILayer;
			ILayer* m_pParent;
			List<_NodeTag>::iterator m_It;//��parent�����е������Ķ�Ӧ�Լ��ĵ�����

			struct _TransformInfo2D{
				matrix m;//�����˸����ڵ�ľ��Ա任;
				bool mIsReady;
				float x, y, ox, oy;
				float scalex, scaley;
				float rotz;
			};
			struct{
				union{
					_TransformInfo2D* _2;
				};//why union? - reserved.
				matrix absTrans;
				bool absNeedUpdate;
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
			INode() : m_pParent(NULL), visible(true), active(true){
				memset(&Transform, 0, sizeof(Transform));
				Transform.absTrans = matrix(matrix::IDENTITY);
			}

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
			ILayer* getParent(){ return m_pParent; }

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
			 * @param dt ʱ�䳤��
			 * @remarks ֻ��visible��activeΪtrueʱ�Żᱻ���á�
			 */
			/* ----------------------------------------------------------------------------*/
			virtual void update(float dt){}

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
					matrix* m = this->_getTransform();
					if(m)
						GetVideo().setTransform(*m);
					paint();
				}
			}

			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ����
			 * @remarks ��IVideo::update�����б����á�
			 */
			/* ----------------------------------------------------------------------------*/
			void visit_update(float dt){
				if(visible && active)
					update(dt);
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
			 * @brief ��ȡ���Ա任����
			 *
			 * @remarks �ڲ����á�
			 */
			/* ----------------------------------------------------------------------------*/
			matrix* _getTransform();
			/* ----------------------------------------------------------------------------*/
			/**
			* @brief ���Լ��㵱ǰ�ڵ����
			* @remarks �ڲ�����
			*/
			/* ----------------------------------------------------------------------------*/
			void _calcTransform(){
				if(Transform._2){
					if(!Transform._2->mIsReady){
						Transform._2->mIsReady = true;
						Transform._2->m =
							matrix().setTranslation(vector3(-Transform._2->ox, -Transform._2->oy, 0.0f))
							* matrix().setScale(vector3(Transform._2->scalex, Transform._2->scaley, 1.0f))
							* matrix().setRotation(vector3(0.0f, 0.0f, Transform._2->rotz))
							* matrix().setTranslation(vector3(Transform._2->x, Transform._2->y, 0.0f));
						Transform.absNeedUpdate = true;
					}
				}
			}
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ��ȡ���Ա任����
			 *
			 * @param checkAncester ������ȵı仯�����Ƿ���Ҫ���¡�
			 * @remarks һ����˵������һ����Ⱦ���������øú����ڼ䣬������ȵ�ĳ���ڵ�ı任�����п��ܱ仯����Ӧ����Ϊtrue��
			 */
			/* ----------------------------------------------------------------------------*/
			matrix& getWorldTransform(bool checkAncester = true);
			/* ----------------------------------------------------------------------------*/
			/**
			 * @brief ��ȡ��Ա任����
			 *
			 * ��ȡ����ڸ��ڵ�ı任����
			 */
			/* ----------------------------------------------------------------------------*/
			matrix& getRelativeTransform(){
				ONEU_ENSURE(Transform._2 != NULL);
				_calcTransform();
				return Transform._2->m;
			}
			//ΪILayer��
			virtual void refreshAll(){}

			/**
			 * @name �任���Բ�������
			 */
			//@{
			void setX(float x){
				if(Transform._2){
					Transform._2->x = x;
					Transform._2->mIsReady = false;
				}else ONEU_ENSURE(FALSE);
			}
			float getX() const{
				if(Transform._2){
					return Transform._2->x;
				}else ONEU_ENSURE(FALSE);
				return 0.0f;
			}
			void setY(float y){
				if(Transform._2){
					Transform._2->y = y;
					Transform._2->mIsReady = false;
				}else ONEU_ENSURE(FALSE);
			}
			float getY() const{
				if(Transform._2){
					return Transform._2->y;
				}else ONEU_ENSURE(FALSE);
				return 0.0f;
			}
			void setCenterX(float x){
				if(Transform._2){
					Transform._2->ox = x;
					Transform._2->mIsReady = false;
				}else ONEU_ENSURE(FALSE);
			}
			float getCenterX() const{
				if(Transform._2)
					return Transform._2->ox;
				else ONEU_ENSURE(FALSE);
				return 0.0f;
			}
			void setCenterY(float y){
				if(Transform._2){
					Transform._2->oy = y;
					Transform._2->mIsReady = false;
				}else ONEU_ENSURE(FALSE);
			}
			float getCenterY() const{
				if(Transform._2)
					return Transform._2->oy;
				else ONEU_ENSURE(FALSE);
				return 0.0f;
			}
			void setRotation(float z){
				if(Transform._2){
					Transform._2->rotz = z;
					Transform._2->mIsReady = false;
				}else ONEU_ENSURE(FALSE);
			}
			float getRotation() const{
				if(Transform._2){
					return Transform._2->rotz;
				}else ONEU_ENSURE(FALSE);
				return 0.0f;
			}
			void setScaleX(float ns){
				if(Transform._2){
					Transform._2->scalex = ns;
					Transform._2->mIsReady = false;
				}else ONEU_ENSURE(FALSE);
			}
			float getScaleX() const{
				if(Transform._2){
					return Transform._2->scalex;
				}else ONEU_ENSURE(FALSE);
				return 0.0f;
			}
			void setScaleY(float ns){
				if(Transform._2){
					Transform._2->scaley = ns;
					Transform._2->mIsReady = false;
				}else ONEU_ENSURE(FALSE);
			}
			float getScaleY() const{
				if(Transform._2){
					return Transform._2->scaley;
				}else ONEU_ENSURE(FALSE);
				return 0.0f;
			}
			//@}
		};


		struct _NodeTag
		{
			int z;
			INode* child;
			bool ownFlag;
			String* tag;
		};

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��Ⱦ�ڵ�����
		 *
		 * �������к��ӵ���Ⱦ�ڵ㡣
		 */
		/* ----------------------------------------------------------------------------*/
		class ILayer
			: public INode
		{
			friend void _DetachNodeFromParent(INode* node);
		protected:
			typedef List<_NodeTag> ListType;
			ListType m_Children;
			friend class INode;
		public:
			virtual ~ILayer(){
				for(ListType::iterator it = m_Children.begin(); it != m_Children.end();){
					if(it->tag != NULL) ONEU_DELETE_T(it->tag);
					if(it->ownFlag) ONEU_DELETE (it++)->child;//����destroyʱ��ʹnode detach������ɾ��it��ָԪ�ء�����ʹ������д�����������ʧЧ��ɵ����⡣
					else (it++)->child->detach();
				}
			}
			/* ----------------------------------------------------------------------------*/
			/** 
			 * @brief ��Ӻ���
			 * 
			 * @param child ���ӽڵ�
			 * @param z ���
			 * @param tag ��ǩ
			 * @param ownedByParent �Ƿ񱻸��׹���������
			 * 
			 * @returns �Ƿ�ɹ�
			 * @remarks ��ownedByParentΪtrue���ӵ������ڱ����׹������ڸ���ɾ����ʱ��ɾ�����Խű����ԣ�ͳһΪfalse��
			 */
			/* ----------------------------------------------------------------------------*/
			bool addChild(INode* child, int z = 0, pcwstr tag = NULL, bool ownedByParent = true){
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
				it->ownFlag = ownedByParent;
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
			virtual void update(float dt){
				for(ListType::iterator it = m_Children.begin(); it != m_Children.end(); ++it){
					it->child->visit_update(dt);
				}
			}
			virtual pcwstr name(){
				return L"Layer";
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

			//��������Ļ����ǣ�Ŀǰ�Ǿ���
			virtual void _refreshAll(){
				bool absNeedUpdate = Transform.absNeedUpdate || (!(Transform._2 && Transform._2->mIsReady));
				for(ListType::iterator it = m_Children.begin(); it != m_Children.end(); ++it){
					INode* node = it->child;
					node->Transform.absNeedUpdate |= absNeedUpdate;
					it->child->refreshAll();
				}
			}
		};

		inline void INode::detach(){
			if(m_pParent != NULL){
				m_pParent->m_Children.erase(m_It);
				m_pParent = NULL;
			}
		}
		inline matrix* INode::_getTransform(){
			if(Transform._2){
				_calcTransform();
				if(Transform.absNeedUpdate){
					matrix* parentTrans = m_pParent ? m_pParent->_getTransform() : NULL;
					Transform.absTrans = parentTrans ? Transform._2->m * (*parentTrans) : Transform._2->m;
				}
				return &Transform.absTrans;
			}
			return NULL;
		}
		inline matrix& INode::getWorldTransform(bool checkAncester){
			//�������ȼ���Ƿ���Ҫ���»������(absTrans�����ڱ��
			if(checkAncester){
				INode *node = m_pParent, *targetRefresh = NULL;
				if(node) while(node->m_pParent){
					node = node->m_pParent;
					if(node->Transform._2 && (!node->Transform._2->mIsReady))
						targetRefresh = node;
				}
				else node = this;
				if(targetRefresh) targetRefresh->refreshAll();
			}

			matrix* ret = _getTransform();
			if(!ret) return Transform.absTrans;
			return *ret;
		}
	}
}