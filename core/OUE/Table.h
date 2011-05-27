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
 * @file Table.h
 * @brief ��
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "../Base/Error.h"
#include "String.h"

namespace OneU
{
	//�ַ���ӳ���֧�ֿմ�ӳ�䣩
	template<typename T>
	class Table
	{
		Table(const Table<T>&);
		Table<T>& operator=(const Table<T>&);
	private:
		struct node
		{
			node *child, *brother, *parent, *rbrother;//���� �ֵ� ���� �������ֵ�ָ��

			wchar c;//Key
			T* val;
		};
		IAllocator& allocator;
		node root;

		node* last_item;
		//Ѱ��p��keyΪc�ĺ��ӣ����Ѱ�Ҳ����򷵻�NULL��
		node* _find_child(node* p, wchar c){
			node* child = p->child;
			while(child != NULL){
				if(child->c == c) return child;
				child = child->brother;
			}
			return NULL;
		}
		//��ȡp��keyΪc�ĺ��ӣ����Ѱ�Ҳ����򴴽�һ����
		//��������ڴ�ʧ�ܣ���������̡�
		node* _get_child(node* p, wchar c){
			node** child = &p->child;
			node* last_child = NULL;//���������е���һ������
			while(*child != NULL && (*child)->c <= c){
				if((*child)->c == c) return *child;
				last_child = *child;
				child = &(*child)->brother;
			}

			//û���ҵ� ������node
			node* old = *child;
			node* newp = *child = (node*)allocator.alloc(sizeof(node), __FILE__, __LINE__);

			if(newp == NULL) ONEU_RAISE(L"Allocating Error!");

			newp->brother = old;
			newp->c = c;
			newp->val = NULL;
			newp->child = NULL;

			newp->parent = p;

			if(newp->brother != NULL)
				newp->brother->rbrother = newp;
			newp->rbrother = last_child;

			return newp;
		}
		//һ���ڵ�Ϊ����������ǣ�
		//1.���ӽڵ�ȫ��Ϊ����Ļ���û�ж��ӽڵ�
		//2.�ڵ㲻Я����Ч��value��
		//�ú����ݹ���ж�p�ĺ����Ƿ�Ϊ�����Ȼ��ɾ���ýڵ�ĺ��Ӳ��жϸýڵ��Ƿ�Ϊ����ġ�
		//����ýڵ��Ƕ���ģ�����true�����򷵻�false��
		//bool _recursive_tidy(node* p){
		//	node** ch = &p->child;
		//	bool ret = (p->val == NULL);
		//	while(*ch != NULL){
		//		node** t = &(*ch)->brother;

		//		bool r = _recursive_tidy(*ch);
		//		if(r){
		//			node* temp = *t;
		//			allocator.dealloc(*ch);
		//			*ch = temp;
		//		}
		//		else ch = t;

		//		ret &= r;
		//	}
		//	return ret;
		//}
		void _recursive_delete_child(node* p){
			node* ch = p->child;
			while(ch != NULL){
				node* t = ch->brother;
				_recursive_delete_child(ch);
				
				if(ch->val != NULL){
					//����ɾ��
					ch->val->~T();
					allocator.dealloc(ch->val);
				}

				//ɾ���ڵ�
				allocator.dealloc(ch);

				ch = t;
			}
		}
	public:
		class iterator
		{
			friend class Table;
			node* ptr;
			iterator(node* p) : ptr(p){}
			void _next_ptr(){
				if(ptr->child != NULL) ptr = ptr->child;
				else if(ptr->brother != NULL) ptr = ptr->brother;
				else{
					while(ptr->parent->brother == NULL)
						ptr = ptr->parent;
					ptr = ptr->parent->brother;
				}
			}
		public:
			iterator() : ptr(NULL){}
			iterator(const iterator& other) : ptr(other.ptr){}
			iterator& operator=(const iterator& other){ ptr = other.ptr; return *this;}
			bool operator==(const iterator& other) const{ return ptr == other.ptr; }
			bool operator!=(const iterator& other) const{ return ptr != other.ptr; }

			iterator& operator++(){
				if(ptr == NULL) return *this;

				_next_ptr();
				if(ptr->parent == NULL) return *this;//is root
				while(ptr->val == NULL){
					_next_ptr();
					if(ptr->parent == NULL) return *this;
				}
				return *this;
			}
			iterator operator++(int){
				iterator ret = *this;
				operator++();
				return ret;
			}
			iterator next(){
				iterator ret = *this;
				return ++ret;
			}

			T& getValue(){ ASSERT(ptr != NULL); return *ptr->val;}
			const T& getValue() const{ if(ptr != NULL) return ptr->val; else return NULL;}
			String _getKey() const{
				String ret;
				node* p = ptr;
				while(p->parent != NULL){
					ret.append(p->c);
					p = p->parent;
				}
				ret.reverse();
				return ret;
			}//temp
		};
		Table()
			:allocator(GetAllocator()), last_item(NULL){
			root.child = root.parent = NULL;
			root.brother = root.rbrother = &root;//Ϊiterator��operator++��--�ṩ�������� ʹ���ڵ���_next_ptr��_prev_ptr��ǡ��ѭ������
			root.val = NULL;
		}
		iterator begin(){ iterator ret = &root; ++ret; return ret;}
		iterator end(){ return &root; }
		iterator getLastItem(){ return last_item; }
		//����ҵ�index�Ľڵ㣬��ô����ʧ�ܷ���NULL
		//���û���ҵ� ����ɹ� �����µ�T�ĵ�ַ
		//�ú������޸�last_itemΪ�¼���Ľڵ���ҵ��Ľڵ�
		//��������ڴ�ʧ�ܣ���������̡�
		T* insert(pcwstr index){
			node* p = &root;
			for(const wchar* pc = index; *pc != 0; ++pc)
			{
				p = _get_child(p, *pc);//�����ڴ�ʧ�ܸú������������
				//if(p == NULL){last_item = NULL; return NULL;}//�����ڴ�ʧ��
			}

			last_item = p;

			if(p->val) return NULL;

			//�մ��Ͳ嵽root
			p->val = (T*)allocator.alloc(sizeof(T), __FILE__, __LINE__);
			if(p->val == NULL)ONEU_RAISE(L"Allocating Error!");//{ last_item = NULL; return NULL;}//�����ڴ�ʧ��
			new(p->val) T;

			return p->val;
		}
		//����ҵ�index�Ľڵ㣬����T�ĵ�ַ�����򷵻�NULL��
		//����ҵ��ڵ㣬�ú������޸�last_itemΪ�ҵ��Ľڵ㡣�����޸�last_itemΪNULL��
		T* find(pcwstr index){
			node* p = &root;
			for(const wchar* pc = index; p != NULL && *pc != 0; ++pc)
				p = _find_child(p, *pc);

			last_item = p;

			if(p == NULL) return NULL;
			return p->val;
		}

		//�ú�������last_itemΪNULL��
		void erase(iterator it){
			node* p = it.ptr;
			if(p == NULL) return;

			if(p->val != NULL){
				//����
				p->val->~T();
				allocator.dealloc(p->val);
				p->val = NULL;
			}

			while(p->child == NULL && p->val == NULL && p != &root){
				node* parent = p->parent;

				if(p->brother != NULL)
					p->brother->rbrother = p->rbrother;
				if(p->rbrother != NULL)
					p->rbrother->brother = p->brother;
				else
					p->parent->child = p->brother;

				allocator.dealloc(p);
				p = parent;
			}
			last_item = NULL;
		}

		void remove(pcwstr index){
			find(index);
			erase(last_item);
		}
		//���trie�������֦�ڡ������֦�ڻ���remove�в�����
		//���Ƶ���ĵ���remove��Ӧ���ڵ��øú�����
		//void tidy(){
		//	_recursive_tidy(&root);
		//}
		T& operator[](pcwstr index){
			insert(index);
			return *last_item->val;
		}
		void clear(){
			_recursive_delete_child(&root);

			if(root.val != NULL){
				root.val->~T();
				allocator.dealloc(root.val);
				root.val = NULL;
			}
			root.child = NULL;
		}
		~Table(){
			clear();
		}
	};
}
