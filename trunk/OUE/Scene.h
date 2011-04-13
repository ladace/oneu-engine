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
 * @file Scene.h
 * @brief 场景
 * @author Ladace
 * @version 1.0.0.1
 * @date 2011-04-09
 */
#pragma once
#include "OUEDefs.h"
#include "Game.h"
#include "Video.h"

namespace OneU
{
	/**
	 * @addtogroup group_game
	 */
	//@{
	
	/* ----------------------------------------------------------------------------*/
	/** 
	 * @brief 场景类
	 *
	 * 负责程序逻辑。
	 * 继承该类来书写对程序逻辑的控制。
	 * 游戏对象基本组成之一。
	 */
	/* ----------------------------------------------------------------------------*/
	class IScene
		: public Interface
	{
		video::IRenderScene* m_pRenderScene;
	public:
		IScene(){ m_pRenderScene = GetVideo().createRenderScene(); }
		~IScene(){ m_pRenderScene->destroy(); }
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief 更新场景
		 *
		 * 每帧被调用一次。重写此函数来控制程序逻辑。
		 */
		/* ----------------------------------------------------------------------------*/
		virtual void update() = 0;
		/* ----------------------------------------------------------------------------*/
		/** 
		 * @brief 获取该场景的渲染场景。
		 * 
		 * @returns 渲染场景对象
		 */
		/* ----------------------------------------------------------------------------*/
		video::IRenderScene* getRenderScene(){
			return m_pRenderScene;
		}
	};
	//@}
}
