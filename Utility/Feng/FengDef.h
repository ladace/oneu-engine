/** 
 * @file FengDef.h
 * @brief Feng��������
 *
 * Feng�������������壬��ͼ�νṹ�嶨��͸������塣
 *
 * @author Ladace
 * @version 1.0.0.1
 * @date 2010-07-08
 */
#pragma once
#include "..\..\DXGraphics\D3DDefs.h"

namespace OneU
{
	/** 
	 * @defgroup FengDef ����ͼ������
	 * @addtogroup Feng
	 */
	/*@{*/
	namespace Feng
	{
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �������
		 *
		 * ������Feng���ʹ��
		 */
		/* ----------------------------------------------------------------------------*/
		const float Eps = 0.000001f;
	}
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ά����
	 */
	/* ----------------------------------------------------------------------------*/
	struct CVector2
		: public VECTOR2
	{
		CVector2(){}
		CVector2( float X, float Y )
			: VECTOR2( X, Y )
		{}

		operator POINT()
		{
			POINT ret = { ( LONG )x, ( LONG )y };
			return ret;
		}
	};

	//���ض�ά�����������
	inline CVector2 operator -( const CVector2 &lhs )
	{
		return CVector2( -lhs.x, -lhs.y );
	}
	inline CVector2 operator +( const CVector2 &lhs, const CVector2 &rhs )//�����ӷ�
	{
		return CVector2( lhs.x + rhs.x, lhs.y + rhs.y );
	}
	inline CVector2 operator -( const CVector2 &lhs, const CVector2 &rhs )//��������
	{
		return CVector2( lhs.x - rhs.x, lhs.y - rhs.y );
	}
	inline float operator *( const CVector2 &lhs, const CVector2 &rhs )//���
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
	inline float operator %( const CVector2 &lhs, const CVector2 & rhs )//��˺����������
	{
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}



	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ά����
	 */
	/* ----------------------------------------------------------------------------*/
	struct CVector3
		: public VECTOR3
	{
		CVector3( float X, float Y, float Z )
			: VECTOR3( X, Y, Z )
		{}
	};

	//������ά�����������
	inline CVector3 operator -( const CVector3 &lhs )
	{
		return CVector3( -lhs.x, -lhs.y, -lhs.z );
	}
	inline CVector3 operator +( const CVector3 &lhs, const CVector3 &rhs )
	{
		return CVector3( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z );
	}
	inline CVector3 operator -( const CVector3 &lhs, const CVector3 &rhs )
	{
		return CVector3( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z );
	}
	inline float operator *( const CVector3 &lhs, const CVector3 &rhs )//���
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}
	inline CVector3 operator %( const CVector3 &lhs, const CVector3 &rhs )//���
	{
		return CVector3( lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x );
	}

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ά����
	 */
	/* ----------------------------------------------------------------------------*/
	struct CVector4
		: public VECTOR4
	{
		CVector4()
		{}
		CVector4( float X, float Y, float Z, float W )
			: VECTOR4( X, Y, Z, W )
		{}
	};

	//������ά�����������
	inline CVector4 operator -( const CVector4 &lhs )
	{
		return CVector4( -lhs.x, -lhs.y, -lhs.z, -lhs.w );
	}
	inline CVector4 operator +( const CVector4 &lhs, const CVector4 &rhs )
	{
		return CVector4( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w );
	}
	inline CVector4 operator -( const CVector4 &lhs, const CVector4 &rhs )
	{
		return CVector4( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w );
	}
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ά��
	 *
	 * ��һ����ά��������ʾ��
	 */
	/* ----------------------------------------------------------------------------*/
	typedef CVector2 CPoint2;
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ά��
	 *
	 * ��һ����ά��������ʾ
	 */
	/* ----------------------------------------------------------------------------*/
	typedef CVector3 CPoint3;
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ����
	 *
	 * �ø����ʹ洢���ε��������ұ߽硣
	 * ��һ����ά��������ʾ��
	 */
	/* ----------------------------------------------------------------------------*/
	typedef CVector4 CRect;

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ôӵ�Aָ���B����������
	 * 
	 * @param &lhs ��A
	 * @param &rhs ��B
	 * 
	 * @return ��Aָ��B��������
	 */
	/* ----------------------------------------------------------------------------*/
	inline CVector2 operator >> ( const CPoint2 &lhs, const CPoint2 &rhs )
	{
		return rhs - lhs;
	}
	/* ----------------------------------------------------------------------------*/
	/** 
	* @brief ��ôӵ�Aָ���B����������
	* 
	* @param &lhs ��A
	* @param &rhs ��B
	* 
	* @return ��Aָ��B��������
	*/
	/* ----------------------------------------------------------------------------*/
	inline CVector3 operator >> ( const CPoint3 &lhs, const CPoint3 &rhs )
	{
		return rhs - lhs;
	}

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ά��
	 *
	 * ��������ά������ʾ
	 */
	/* ----------------------------------------------------------------------------*/
	struct CLine2
	{
		CPoint2 p1, p2;
		CLine2( float x1, float y1, float x2, float y2 )
			: p1( x1, y1 ), p2( x2, y2 )
		{}
		CLine2( CPoint2 & point1, CPoint2 &point2 )
			: p1( point1 ), p2( point2 )
		{}
	};




	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ���Ͷ�ά����
	 *
	 * ������VC���POINT������������ݡ�
	 */
	/* ----------------------------------------------------------------------------*/
	struct CVector2_n
		: public ::POINT
	{
		CVector2_n( LONG X, LONG Y )
		{
			x = X;
			y = Y;
		}
		explicit CVector2_n( const CVector2 &v )
		{
			x = static_cast< LONG >( v.x );
			y = static_cast< LONG >( v.y );
		}
	};

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ���Ͷ�ά��
	 *
	 * ��һ�����Ͷ�ά��������ʾ
	 */
	/* ----------------------------------------------------------------------------*/
	typedef CVector2_n CPoint2_n;
		
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ������ά����
	 *
	 * ������VC���RECT�������RECT����
	 */
	/* ----------------------------------------------------------------------------*/
	struct CVector4_n
		: public ::RECT
	{
		CVector4_n()
		{}
		CVector4_n( LONG Left, LONG Top, LONG Right, LONG Bottom )
		{
			left = Left;
			top = Top;
			right = Right;
			bottom = Bottom;
		}
		explicit CVector4_n( const CRect &rc )
		{
			left = ( LONG )rc.left;
			top = ( LONG )rc.top;
			right = ( LONG )rc.right;
			bottom = ( LONG )rc.bottom;
		}
	};

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ���;���
	 *
	 * ��һ��������ά��������ʾ
	 */
	/* ----------------------------------------------------------------------------*/
	typedef CVector4_n CRecti;
	/*@}*///defgroup FengDef
}//namespace OneU
