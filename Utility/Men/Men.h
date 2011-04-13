/** 
 * @file Men.h
 * @brief �任Ԫ�Ķ���
 *
 * ����ֻ���ṩ�˱任Ԫ�Ķ��塣
 * ÿ��֧�����������Ҫ����д���ڱ任Ԫ��֧�֡�
 *
 * ע����ת�ĵ�λ��Ϊ����
 *
 * @author Ladace
 * @version 1.0.0.1
 * @date 2010-07-09
 */
#ifndef __MEN_H
#define __MEN_H

namespace OneU
{
	/**
	 * @defgroup Men �����
	 *
	 * �任Ԫ�Ķ��塣
	 * �Ͳ�(0)
	 */
	/* ----------------------------------------------------------------------------*/
	/**
	 * @defgroup Men2 ��ά�任Ԫ
	 * @addtogroup Men
	 * �ڲ�����ö��ֵDim = 2��ʾ���Ƕ�ά�任Ԫ
	 *
	 */
	/*@{*/
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��άƽ��
	 */
	/* ----------------------------------------------------------------------------*/
	struct Translate2
	{
		enum{ Dim = 2 };
		float x,y;
		Translate2( float _x, float _y )
			: x( _x ), y( _y )
		{}
	};
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief �����ĵĶ�ά��ת
	 *
	 * �ɱ�Rotate2ת������
	 * ��������Ҫ�࣬���ṩ�����֧�֡�
	 * ��Ϊ��������Translate2��Rotate2��϶��ɡ�
	 * @sa Rotate2
	 */
	/* ----------------------------------------------------------------------------*/
	struct Rotate2c//���ṩ����֧��
	{
		enum{ Dim = 2 };
		float cx, cy, val;
		Rotate2c( float cx, float cy, float val )
			: cx( cx ), cy( cy ), val( val )
		{}
	};
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief �����ĵĶ�ά����
	 * \ingroup Men2
	 *
	 * �ɱ�Scale2ת������
	 * ��������Ҫ�࣬���ṩ�����֧�֡�
	 * ��Ϊ��������Translate2��Scale2��϶��ɡ�
	 * @sa Scale2
	 */
	/* ----------------------------------------------------------------------------*/
	struct Scale2c//���ṩ����֧��
	{
		enum{ Dim = 2 };
		float cx, cy, valx, valy, rotation;
		Scale2c( float cx, float cy, float valx, float valy, float rotation = 0.0f )
			: cx( cx ), cy( cy ), valx( valx ), valy( valy ), rotation( rotation )
		{}
	};

	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ά��ת
	 *
	 * ��ת����Rotate2c
	 * @sa Rotate2c
	 */
	/* ----------------------------------------------------------------------------*/
	struct Rotate2
	{
		enum{ Dim = 2 };
		float val;
		Rotate2( float rot )
			: val( rot )
		{}
		operator Rotate2c() const
		{
			return Rotate2c( 0.0f, 0.0f, val );
		}
	};
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ά����
	 *
	 * ��ת����Scale2c
	 * @sa Scale2c
	 */
	/* ----------------------------------------------------------------------------*/
	struct Scale2
	{
		enum{ Dim = 2 };
		float valx, valy;
		Scale2( float valx, float valy )
			: valx( valx ), valy( valy )
		{}
		operator Scale2c() const
		{
			return Scale2c( 0.0f, 0.0f, valx, valy );
		}
	};
	/*@}*/
	/* ----------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------*/
	/**
	 * @defgroup Men3 ��ά�任Ԫ
	 * 
	 * @addtogroup Men
	 * �ڲ�����ö��ֵDim = 3��ʾ������ά�任Ԫ
	 * 
	 */
	/*@{*/
	
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��άƽ��
	 */
	/* ----------------------------------------------------------------------------*/
	struct Translate3
	{
		enum{ Dim = 3 };
		float x, y, z;
		Translate3( float x, float y, float z )
			: x( x ), y( y ), z( z )
		{}
	};
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��ά����
	 */
	/* ----------------------------------------------------------------------------*/
	struct Scale3
	{
		enum{ Dim = 3 };
		float valx, valy, valz;
		Scale3( float valx, float valy, float valz )
			: valx( valx ), valy( valy ), valz( valz )
		{}
	};
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief X����ת
	 */
	/* ----------------------------------------------------------------------------*/
	struct RotateX
	{
		enum{ Dim = 3 };
		float rot;
		RotateX( float rot )
			: rot( rot )
		{}
	};
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief Y����ת
	 */
	/* ----------------------------------------------------------------------------*/
	struct RotateY
	{
		enum{ Dim = 3 };
		float rot;
		RotateY( float rot )
			: rot( rot )
		{}
	};
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief Z����ת
	 */
	/* ----------------------------------------------------------------------------*/
	struct RotateZ
	{
		enum{ Dim = 3 };
		float rot;
		RotateZ( float rot )
			: rot( rot )
		{}
	};
	/*@}*/
	/* ----------------------------------------------------------------------------*/
	/**
	 * @defgroup Men_Generator �任Ԫ������
	 * 
	 * @addtogroup Men
	 * �Զ����ݲ�����Ŀѡ���Ӧ�ı任Ԫ
	 * 
	 */
	/*@{*/

	inline Translate2 Translate( float x, float y )
	{
		return Translate2( x, y );
	}
	inline Translate3 Translate( float x, float y, float z )
	{
		return Translate3( x, y, z );
	}
	inline Rotate2 Rotate( float val )
	{
		return Rotate2( val );
	}
	inline Rotate2c Rotate( float cx, float cy, float val )
	{
		return Rotate2c( cx, cy, val );
	}
	inline Scale2 Scale( float valx, float valy )
	{
		return Scale2( valx, valy );
	}
	inline Scale2c Scale( float cx, float cy, float valx, float valy, float rotation = 0.0f )
	{
		return Scale2c( cx, cy, valx, valy, rotation );
	}
	inline Scale3 Scale( float valx, float valy, float valz )
	{
		return Scale3( valx, valy, valz );
	}
	/*@}*/
	/* ----------------------------------------------------------------------------*/
}//namespace OneU

#endif // ifndef __MEN_H
