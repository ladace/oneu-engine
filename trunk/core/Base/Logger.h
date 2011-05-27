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
 * @file Logger.h
 * @brief ��־�ӿ�
 * @author Ladace
 * @version 1.0.0.1
 * @date 2009-11-11
 * level 1
 */
#pragma once

#include "OneUPreDef.h"
#include "Interface.h"
#include "Error.h"
#include "Stream.h"
#include "String.h"

#define ONEU_LOG_THRESHOLD 1

namespace OneU
{
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief ��־�ӿ���
	 *
	 * �ṩһ��������־�Ľӿڣ������ǲ���ϵͳ�޹صģ���ʵ�ֿ����ǲ���ϵͳ��ص�
	 */
	/* ----------------------------------------------------------------------------*/
	class ILogger
		: public Interface
	{
	public:
		enum MessageLevel{ML_TRIVIAL = 1, ML_NORMAL = 2, ML_CRITICAL = 3};
	public:
		/* ----------------------------------------------------------------------------*/
		/** 
		* @brief ���캯��
		*/
		/* ----------------------------------------------------------------------------*/
		ILogger(){};
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��������
		 */
		/* ----------------------------------------------------------------------------*/
		virtual ~ILogger() {};

		virtual void flush() = 0;

		virtual void write(pcwstr lpstrLog) = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief ��¼��Ϣ
		 * 
		 * @param lvl ��¼����
		 * @param lpstrLog ��Ϣ�ַ���ָ��
		 */
		/* ----------------------------------------------------------------------------*/
		void logMessage(pcwstr lpstrLog, MessageLevel lvl = ML_NORMAL){
			if(lvl >= ONEU_LOG_THRESHOLD)
				write(lpstrLog);
		}
		void logMessage(pcstr lpstrLog, MessageLevel lvl = ML_NORMAL){logMessage(ANSI2Wide(lpstrLog), lvl);}

		class Stream
			: public IOStreamMaker
		{
			ILogger* m_target;
			MessageLevel m_lvl;
		public:
			Stream(ILogger* target, MessageLevel lvl) : m_target(target), m_lvl(lvl){}
			virtual void output(pcwstr data){
				m_target->logMessage(data, m_lvl);
			}
		};
		Stream stream(MessageLevel lvl = ML_NORMAL){return Stream(this, lvl);}
	};

	//��̬
	/* ----------------------------------------------------------------------------*/
	/** 
	* @brief ����ʵ��
	*
	* ���ݸú���ʵ�ֵĲ�ͬ�������ɲ�ͬ�������ʵ��
	*/
	/* ----------------------------------------------------------------------------*/
	extern "C" ONEU_BASE_API void Logger_build(Factory<ILogger>::type lf);
	/* ----------------------------------------------------------------------------*/
	/** 
	* @brief ���ʵ��ָ��
	* 
	* @return ָ��ʵ����ָ��
	*/
	/* ----------------------------------------------------------------------------*/
	extern "C" ONEU_BASE_API ILogger& GetLogger();
	/* ----------------------------------------------------------------------------*/
	/** 
	* @brief ɾ��ʵ��
	*/
	/* ----------------------------------------------------------------------------*/
	extern "C" ONEU_BASE_API void Logger_destroy();


	//�ṩ����ʵ��
	extern "C" ONEU_BASE_API ILogger* LoggerDisk_Factory();
	extern "C" ONEU_BASE_API ILogger* LoggerNull_Factory();
}
