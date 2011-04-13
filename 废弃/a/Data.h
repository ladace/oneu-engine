// Data.h: �������ݵ���
//
//////////////////////////////////////////////////////////////////////

#pragma once

namespace OneU
{
	class RawFile;

	template<class T>
	class CData  
	{
	public:
		typedef T DataType;

		CData(){};
		CData(T& Ref){ memcpy( &_Contents, &Ref, sizeof(Ref) );}
		~CData(){};

		void Get(RawFile* pFile)//���ļ���ȡ����
		{
			pFile->Read( (char*)&_Contents, sizeof( _Contents ) );
		}
		void Put(RawFile* pFile) const//�����ݷ����ļ�
		{
			pFile->Write( (char*)&_Contents , sizeof( _Contents ) );
		}

		T& Data(){ return _Contents;}
		T* operator->(){ return &_Contents;}

	private:
		T _Contents;
	};




	//Data��ĵ�2ʵ��
	template<int size>
	class CData2
	{
	public:
		CData2(){};
		CData2(void *px){ memcpy( _Contents, px, size );}
		~CData2(){};

		void Get(RawFile* pFile)//���ļ���ȡ����
		{
			pFile->Read( (char*)_Contents, sizeof( _Contents ) );
		}
		void Put(RawFile* pFile) const//�����ݷ����ļ�
		{
			pFile->Write( (char*)_Contents , sizeof( _Contents ) );
		}

		void* Data(){ return _Contents;}

	private:
		char _Contents[ size ];
	};
}