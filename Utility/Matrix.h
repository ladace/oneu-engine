/** 
 * @file Matrix.h
 * @brief ����
 * @author Ladace
 * @version 1.0.0.1
 * @date 2010-07-09
 */
#ifndef __MATRIX_H
#define __MATRIX_H

#include "Utility.h"

#ifdef __ONEU_USE_GE
#include "../DXGraphics/MatrixE.h"
#if __ONEUE_MATRIX_VERSION != 100
#pragma message( __FILE__":MatrixE Version Unmatched!")
AnErrorOccured
#endif
#else
#pragma message( __FILE__":CMatrix Needs OneU GE Library!")
AnErrorOccured!!!
#endif

#include "Feng\FengDef.h"
#include "Men\Men.h"

namespace OneU
{
	//ǰ������ ���ʽģ�� �ڲ��ṹ��
	template< class Left >
	struct MatrixFactor;

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief 4*4������
	 *
	 * ������MATRIX �����������
	 */
	/* ----------------------------------------------------------------------------*/
	class Matrix
		: public MATRIX
	{
	public:
		Matrix(){}
		Matrix( const MATRIX & M )
			: MATRIX( M )
		{}
		template< class T >
		explicit Matrix( const T& rhs )
		{
			Transformation( rhs );
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��λ����
		 */
		/* ----------------------------------------------------------------------------*/
		static const Matrix E;

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ����ʽ
		 * 
		 * @return ���������ʽֵ
		 */
		/* ----------------------------------------------------------------------------*/
		float operator~() const
		{
			return MatrixDeterminant( *this );
		}

		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �ӱ��ʽģ�忽��
		 * 
		 * @param rhs ���ʽģ��
		 */
		/* ----------------------------------------------------------------------------*/
		template< class Left >	
		explicit Matrix( const MatrixFactor< Left >& rhs )
		{
			operator= ( rhs );
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief �ӱ��ʽģ�帳ֵ
		 * 
		 * @param rhs ���ʽģ��
		 * 
		 * @return �������������
		 */
		/* ----------------------------------------------------------------------------*/
		template< class Left >
		Matrix& operator= ( const MatrixFactor< Left > &rhs )
		{
			rhs.Interpret( *this );
			return *this;
		}

		/* ----------------------------------------------------------------------------*/
		/**
		 * @brief ��ֵ����
		 *
		 * @param rhs ��һ�������
		 *
		 * @return �������������
		 */
		/* ----------------------------------------------------------------------------*/
		Matrix& operator= (const MATRIX& rhs)
		{
			MATRIX::operator=(rhs);
			return *this;
		}
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @name �ӱ任Ԫ��������
		 *
		 * ���ݱ任Ԫ������Ӧ�ľ���
		 * @{
		 */
		/* ----------------------------------------------------------------------------*/
		Matrix& Transformation( const Translate2 &Trans )
		{
			MatrixTranslation( *this, Trans.x, Trans.y, 0 );
			return *this;
		}
		Matrix& Transformation( const Rotate2 &Rot )
		{
			MatrixRotationZ( *this, Rot.val );
			return *this;
		}
		Matrix& Transformation( const Scale2 &Scl )
		{
			MatrixScaling( *this, Scl.valx, Scl.valy, 1.0f );
			return *this;
		}
		Matrix& Transformation( const Translate3 &Trans )
		{
			MatrixTranslation( *this, Trans.x, Trans.y, Trans.z );
			return *this;
		}
		Matrix& Transformation( const RotateX & Rot )
		{
			MatrixRotationX( *this, Rot.rot );
			return *this;
		}
		Matrix& Transformation( const RotateY & Rot )
		{
			MatrixRotationY( *this, Rot.rot );
			return *this;
		}
		Matrix& Transformation( const RotateZ & Rot )
		{
			MatrixRotationZ( *this, Rot.rot );
			return *this;
		}
		Matrix& Transformation( const Scale3 & Scl )
		{
			MatrixScaling( *this, Scl.valx, Scl.valy, Scl.valz );
			return *this;
		}
		template <class T>
		Matrix& operator=(const T& Transform)
		{
			return Transformation(Transform);
		}
		/** @}*/
		/* ----------------------------------------------------------------------------*/
	};


	/* ----------------------------------------------------------------------------*/
	/** 
	 * @name ���ʽģ��
	 *
	 * �ӵĹ���û���壬ֻ�г˷��Ĺ���
	 * @internal
	 * @{
	 */
	/* ----------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ���ʽģ�� �˷�
	 *
	 * @internal
	 */
	/* ----------------------------------------------------------------------------*/
	template< class Left >
	struct MatrixFactor
	{
		const Left &m_lhs;const Matrix &m_rhs;
		MatrixFactor( const Left &lhs, const Matrix &rhs )
			: m_lhs( lhs ), m_rhs( rhs )
		{}
		Matrix& Interpret( const Matrix &Result )
		{
			MatrixMultiply( Result, m_lhs.Interpret( Result ), m_rhs )
		}
		operator Matrix()
		{
			return Interpret( Matrix() );
		}
	};
	template<>
	struct MatrixFactor< Matrix >
	{
		const Matrix &m_lhs, &m_rhs;
		MatrixFactor( const Matrix &lhs, const Matrix &rhs )
			: m_lhs( lhs ), m_rhs( rhs )
		{}
		Matrix& Interpret( Matrix &Result )
		{
			MatrixMultiply( Result, m_lhs, m_rhs );
			return Result;
		}
		operator Matrix()
		{
			return Interpret( Matrix() );
		}
	};


	template< class Left >
	MatrixFactor< Left > operator*( const Left &lhs, const Matrix &rhs )
	{
		return MatrixFactor< Left >( lhs, rhs );
	}
	/** @}*/
	/* ----------------------------------------------------------------------------*/

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @name Matrix Internal
	 * @internal
	 * @{
	 */
	/* ----------------------------------------------------------------------------*/
	namespace internal
	{
		extern ONEU_UTIL_API Matrix matT1;
		extern ONEU_UTIL_API Matrix matT2;
		//������Ϊ���󷵻ؾ����� ��Ϊ�任Ԫ(Translate2)һ�����������ɾ��󷵻� Ϊ��operator*������ĺ��� �Ը���T��ͬ����ͬ����
		inline const Matrix &MatrixTransformation( const Matrix &m ) { return m; }
		template< class T >
		inline const Matrix &MatrixTransformation( const T &v ){ static Matrix m; return m.Transformation( v ); }
	}	
	/** @}*/
	/* ----------------------------------------------------------------------------*/

	////////////////////////////
	//�������ӱ任Ԫ������CMatrix

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @name �任Ԫ�����ĳ˷�
	 *
	 * ֧�ֱ任Ԫ֮�����
	 * ֧�־�����任Ԫ��ˣ��������󣬱任Ԫ���ң�
	 *
	 * ���ؾ���
	 * 
	 * ��֧��Rotate2c��Scale2c
	 * @{
	 */
	/* ----------------------------------------------------------------------------*/
	template< class T >
	inline Matrix operator *( const T& lhs, const Translate2 &rhs )
	{
		return internal::MatrixTransformation( lhs ) * internal::matT1.Transformation( rhs );
	}
	template< class T >
	inline Matrix operator *( const T &lhs, const Rotate2& rhs )
	{
		return internal::MatrixTransformation( lhs ) * internal::matT1.Transformation( rhs );
	}
	template< class T >
	inline Matrix operator *( const T &lhs, const Scale2& rhs )
	{
		return internal::MatrixTransformation( lhs ) * internal::matT1.Transformation( rhs );
	}
	template< class T >
	inline Matrix operator *( const T &lhs, const Translate3& rhs )
	{
		return internal::MatrixTransformation( lhs ) * internal::matT1.Transformation( rhs );
	}
	template< class T >
	inline Matrix operator *( const T &lhs, const Scale3& rhs )
	{
		return internal::MatrixTransformation( lhs ) * internal::matT1.Transformation( rhs );
	}
	template< class T >
	inline Matrix operator *( const T &lhs, const RotateX &rhs )
	{
		return internal::MatrixTransformation( lhs ) * internal::matT1.Transformation( rhs );
	}
	template< class T >
	inline Matrix operator *( const T &lhs, const RotateY &rhs )
	{
		return internal::MatrixTransformation( lhs ) * internal::matT1.Transformation( rhs );
	}
	template< class T >
	inline Matrix operator *( const T &lhs, const RotateZ &rhs )
	{
		return internal::MatrixTransformation( lhs ) * internal::matT1.Transformation( rhs );
	}
	/** @}*/
	/* ----------------------------------------------------------------------------*/
}
#endif // ifndef __MATRIX_H

