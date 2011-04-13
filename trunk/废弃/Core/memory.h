//�����ڴ�Ŀ�
//                  2009.10
#pragma once
#include<memory.h>
#include<new>
//VC STL�ռ������
#include<xmemory>

//*****************************
//CRT�� �ڴ��⹤��
//��DEBUGģʽ��ʹ��
//���� CRT�� alloc�ļ������� ����� ���� ����
//*****************************
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>

#include<crtdbg.h>
#endif

//���� ����DXEnc/Segment.h
//����δ����
//���������Ҫ��Ϊ3D�����ʼ��
template < typename T >
inline T* mem_init( T dst[], size_t num, const T& x)//��XΪ��ֵ��ʼ���ڴ� ��֧�ֹ��캯��
{
	for(unsigned int i=0; i<num; i++)//���ط��� ��һ�ֱ���������ÿ�ΰ��ѳ�ʼ���õĿ��������� �������󿽱��ĳ���
		dst[i]=x;
	return dst;
}

template < typename T >
inline T* mem_init( T dst[], size_t num)//�Ե�һ��Ԫ��Ϊ��ֵ��ʼ���ڴ�
{
	for( size_t i=1;i<num;i++)
		dst[i]=dst[0];
	return dst;
}

inline void* mem_init( void* dst, size_t size_x, size_t offset, size_t step, size_t size_all )//��������Ծ��ʼ�� ����δ��Ч�ʻ���� ����
{
	for( size_t i=offset + step; i<size_all; i+=step)
		memcpy( (char*)dst + i, (char*)dst + offset, size_x);
	return dst;
}

//VC��STL��ռ�������̫��
//����

//adapter for VC's Allocator
template < int inst >
class vc_alloc
{
private:
	static std::allocator<char> _r;
public:
	static void * allocate( size_t size )
	{
#ifdef _DEBUG
		char * ret = _r.allocate( size + 8 );

		ret[ 0 ] = ret[ 1 ]=ret [ 2 ] = '*';

		return ret + 8;
#elif
		return _r.allocate( size );
#endif
	}

	static void deallocate( void * p, size_t size )
	{
#ifdef _DEBUG
		_r.deallocate( reinterpret_cast< char * >( p ) - 8, size );
#elif
		_r.deallocate( p, size );
#endif
	}
};

template < int inst >
std::allocator< char > vc_alloc< inst >::_r;

typedef vc_alloc< 0 > alloc;

///////////////////////////////////////
// �����޸ĺ��SGI�ռ�������
// ò����bug
//////////////////////////////////////
/*#include "sgi_alloc.h"

class sgi_debug_alloc
{
public:
	static void * allocate( size_t size )
	{
		char * ret = reinterpret_cast < char * > ( SGI::alloc::allocate( size + 8) );
		ret[ 0 ] = ret [ 1 ] = ret [ 2 ];
		return ret + 8;

	}
	static void deallocate( void * p, size_t size )
	{
		SGI::alloc::deallocate( reinterpret_cast< char * >( p ) - 8, size );
	}
};*/

#ifdef _DEBUG
//typedef sgi_debug_alloc alloc;
#elif
//typedef SGI::alloc alloc;
#endif
