#include "../FrameSystem/Game.h"
#include "ScriptScene.h"
//��������Ϸ��ʼ����ֻ��һ��Scene
namespace OneU
{
	class MyGame
		: public Game
	{
	public:
		void InitScene(Scene*& pScene);
	};
	void MyGame::InitScene(Scene*& pScene)
	{
		pScene = new ScriptScene;
	}
	//�����洴��������Ϸ
	Game* GameFactroy()
	{
		return new MyGame();
	}
}