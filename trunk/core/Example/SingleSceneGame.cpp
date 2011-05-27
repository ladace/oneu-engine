//�������ű���������Ϸ��
//�����ű���ϵͳ��
//����script/lua/main.lua�ļ�����������main.lua��
//������Ӧ��Դ
#include <OUE/OUE.h>

using namespace OneU;

class SingleScene
	: public IScene
{
	atom::IInterpreter* m_Ip;
public:
	SingleScene(){
		m_Ip = GetAtom().createInterpreter(IAtom::L_LUA);
		m_Ip->execFile(L"./script/lua/main.lua");

		m_Ip->execWithScene(L"Scene:init()", this);
	}
	void update(){
		m_Ip->execWithScene(L"Scene:main()", this);
	}
	~SingleScene(){
		m_Ip->destroy();
	}
	void destroy(){
		ONEU_DELETE(this);
	}
};

extern "C" int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, ::LPSTR lpCmdLine, int nShowCmd){
	Game_build(Game_create);
	IGame& game = GetGame();
	game.init(L"OneU Engine", 800, 600, true);

	game.replaceScene(ONEU_NEW(SingleScene));
	return game.run();
}