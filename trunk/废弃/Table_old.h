#pragma once
#include "OneUPreDef.h"
#include "Interface.h"
#include <new>
#include <map>
#include <string>

namespace OneU
{
	//@todo ����дʵ�� ûд���������ȵ�
	//table�൱���ַ���ӳ���map

	template<typename T>
	class Table
	{
	public:
		typedef std::map<std::wstring, T> MapType;
	private:
		MapType m;
		typename MapType::iterator m_lastItem;
	public:
		Table(){}
		~Table(){}

		//�²���ĵ�������ͨ��getLastItem���
		//������ʧ�� ��ͨ��getLastItem�������Ϊindex��Ŀ�ĵ�����
		T* insert(pcwstr index){
			//�����ǵ��ÿ������캯�� ��׼�ǵ����޲ι��캯��
			std::pair<MapType::iterator, bool> ret = m.insert(std::pair<std::wstring, T>(index, T()));

			m_lastItem = ret.first;
			if(!ret.second)
				return NULL;

			return &ret.first->second;
		}
		T* find(pcwstr index){
			MapType::iterator iter = m.find(index);
			if(iter == m.end())
				return NULL;
			return &iter->second;
		}
		T& operator[](pcwstr index){
			return m[index];
		}

		class Iterator
		{
			friend class Table;
			typename MapType::iterator m_i;
		public:
			Iterator(typename MapType::iterator iter)
				: m_i(iter)
			{}
			Iterator(){}
			T& getValue(){ return m_i->second;}
		};
		Iterator getLastItem(){return m_lastItem; }
		void Erase(Iterator iter){
			m.erase(iter.m_i);
		}
	};
}
