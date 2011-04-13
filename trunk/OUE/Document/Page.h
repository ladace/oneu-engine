//���ļ������������ĵ�

namespace OneU{
/* ----------------------------------------------------------------------------*/
/** 
 * @mainpage ��������2D�����ĵ�
 *
 * This ain't a game. This is One Universe.\n
 * \n
 * ��������2D����Ŀ����ʵ�ֿ�ƽ̨֧��OpenGL��DirectX���ܴ�����չ�����һ��2D��Ϸƽ̨��\n
 * \n
 *
 * ��SDK���ﹲ������
 *  - c++����SDK��������VCʹ�ã���
 *  - ���������ý���������Ϸִ�а�����Ϊ������ļ�ִ�г��򣬿���ͨ����д�ű�д��Ϸ��
 *  - �ĵ���
 *  .
 * @section section_contents �ĵ��ṹ
 *  - @subpage page_cpp
 *  - @subpage page_lua
 *  - @subpage page_extending
 *  - �ο�
 *		- @subpage page_run
 *		- @subpage page_atom_lua
 *		- @subpage page_exports
 *		.
 *  .
 * @section section_faq FAQ
 * Q: ΪʲôSDKֻ��ʹ��VC��\n
 * A: ��Ϊ������֮��Ķ����ڴ沼�ֲ����ݣ���SDK��ʹ��VC����ģ����ʹ���������������ܻᵼ�³�����������ҵ��ǣ�VC�Ĳ�ͬ�汾�ڶ����ڴ沼�ֱ�����һ���ԡ���˶�VC�İ汾û�����ơ��Ժ���Ƴ�MinGW���SDK��\n
 * Q: �ɷ���openGL��DX�ں��л���\n
 * A: ����ֻ����DX�ںˡ�\n
 * Q: �����ýű���ʵ�����ã�
 * A: ����Atom�Ĺ���֮һ����ΪAtom������������������ģ�
 */

/* ----------------------------------------------------------------------------*/
/**
 * @page page_cpp ʹ��C++ SDK
 * ��SDK��������Ϸ�߱��ĵײ�Ԫ�أ����������Ͻ�����Ϸ��ܱ�д��Ϸ��Ҳ����������չ���档\n
 *
 * һ��ʹ�����������HelloWorld���ο�HelloWorld.cpp��\n
 *
 *  - @ref section_defintion
 *		- @ref section_renderscene
 *		.
 *  - @ref section_program
 *		- @ref section_config_sdk
 *		- @ref section_start
 *		- @ref section_display_image
 *		- @ref section_retrieve_control
 *		- @ref section_user_video_node
 *		- @ref section_to_extend
 *		.
 *  .
 * @section section_defintion ����
 * ��Ҫ�ӿڣ�
 *  - ��Ϸ�ӿ� @ref IGame\n
 *  ����������Ϸ�������̣��������úʹ�����ˢ�¸���ϵͳ������ӿڡ�
 *  - �㲥�ӿ� @ref IBroadcast\n
 *  ����ȫ���¼���
 *  - ͼ�νӿ� @ref IVideo
 *  ������ʾ�͹���ͼ�񡢶�����
 *  - ���ƽӿ� @ref IControl\n
 *  ��������̺����������豸��
 *  - �����ӿ� @ref IScene\n
 *  ��������Ϸ�߼���һ��������һ���߼���Ԫ������Ϸ���������кʹ���
 * .
 * 
 * @subsection section_event �¼�ϵͳ
 * �¼�ϵͳ���¼��ɷ��������������¼��������¼���������ɡ�ʹ���ַ���������һ���¼����¼��ɷ����ǽ����¼����࣬ͨ�����¼��ɷ�����Ӽ�����������ĳһ���¼�������������Ӷ����\n
 * Ŀǰ���¼�����û�в��ö��У����ڷ�����Ϣ��ͬʱִ�м������Ĵ���������\n
 * �����¼���ͨ���㲥ϵͳ�������㲥�����¼��ɷ����ļ̳��ࡣ\n
 * �����¼�������@ref IGame::setInputFocus��һ���¼��ɷ�����Ϊ���뽹�㣬���¼��ɷ������Խ��յ����̵������¼���
 * @subsection section_renderscene ͼ��ϵͳ����Ⱦ����
 * ��������ʹ��������Ⱦ�����е�ÿһ���ڵ㼴��ʾһ����Ⱦ��������Ⱦʱ��������б�����\n
 * һ����Ⱦ������Ϊһ����Ⱦ����һ����ԣ�һ��������Ӧһ����Ⱦ������\n
 * @ref video::INode������Ⱦ�ڵ�Ľӿڣ�@ref video::INodeContainer�������к��ӵ���Ⱦ�ڵ�ӿڡ�zֵ��ʾһ����Ⱦ�ڵ������ֵܽڵ㱻��Ⱦ��˳��zֵС�Ļ��ȱ���Ⱦ��\n
 * �̳����������������ͼ��ϵͳ�Ĺ��ܡ�\n
 *
 * @section section_program ��д����
 * @subsection section_config_sdk ����SDK
 *  - �����include�ļ�����ӵ�VC��include·������俽���������ڣ�����libs/x86�ļ����µ�����lib�ļ���\n
 *  - ����Libs������dll�������ڡ���VC2005Ϊ����������ΪClient���򿽱���Client/Client�¡�
 *  - ��ʹ�ýű�������script�ļ��У��ű��⣩����ϷĿ¼�¡�
 *  .
 * @subsection section_start ��ʼ
 * ���ȼ̳�@ref IScene����дupdate������
 * ��д����������������׼���̣�
 *  - ����@ref Game_build��������Game��̬��
 *  - ����@ref GetGame��ȡIGame�ӿڡ�����@ref IGame::init������ʼ����Ϸ��
 *  - ����@ref IGame�ӿ�������Ϸ�߼��ȡ�����@ref IGame::replaceScene����һ����������Ϊ��Ϸ�������
 *  - ����@ref IGame::run�������䷵��ֵ���ú������Զ�������Ϸ���̡�
 *  .
 * ���ȶ���һ��������
 * @code
 * using namespace OneU;
 * class HelloScene
 *	: public IScene
 * {
 * public:
 *	HelloScene(){
 *	}
 *	void update(){
 *	}
 * };
 * @endcode
 * ������д��������
 * @code
 * extern "C" int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, ::LPSTR lpCmdLine, int nShowCmd){
 *	Game_build(Game_create);
 *	IGame* game = GetGame();
 *	game->init(L"Hello World", 800, 600, true);
 *	game->replaceScene(ONEU_NEW(HelloScene));
 *	return game->run();
 * }
 * @endcode
 * �������к���һ���մ��ڡ�
 * @subsection section_display_image ��ʾͼ��
 * ���¶���HelloScene���ڹ��캯���ﴴ������:
 * @code
 * class HelloScene
 *	: public IScene
 * {
 *	ISprite* m_pS;
 * public:
 *	HelloScene(){
 *		m_pS = Sprite_create(GetVideo.loadImage(L"picture.png"));
 *		getRenderScene().addChild(m_pS, 0);
 *	}
 *	void update(){
 *	}
 * };
 * @endcode
 * �ڸ�Ŀ¼�����picture.pngͼ���ļ���������Ϸ��picture.png��ʾ�ڴ��ڵ����Ͻǡ�\n
 * @ref ISprite���������õľ���ӿڡ�����Sprite_create�������顣\n
 * ����@ref IScene::getRenderScene��øó�����Ӧ����Ⱦ������������ڵ����ó���������ʹ����ʾ������\n
 * @subsection section_retrieve_control ��Ӧ����
 * ��Ӧ���룬һ�ְ취��ֱ�ӷ��������豸��ͨ���鿴״̬����Ӧ�����롣\n
 * ��update����������´��룺
 * @code
 * if(GetControl().keyIsDown(OIK_RIGHT))
 *	m_pS->setX(m_pS->getX() + 10.0f);
 * @endcode
 * �������У����·�����Ҽ���ͼ�������ƶ���\n
 * @ref IScene::update��������Ϸ��ÿһ֡�������һ�Ρ�\n
 * @ref GetControl������ÿ��������󣬿������鿴����״̬��OIK_RIGHT�Ƿ�����Ҽ���Ӧ��ɨ���롣\n
 * ����ʹ�õ�����ϵ�����Ͻ�Ϊԭ�㣬����Ϊ��λ��\n
 * @subsection section_user_video_node �Զ�����ȾԪ��
 * ��ȾԪ��ָ��Ⱦ���еĽ���������\n
 * �������õļ�����ȾԪ�أ�Sprite, Label�ȣ��Ƚϼ򵥣���ԶԶ�����õġ��������ṩһ���Լ�������ȾԪ�صķ�����������Ч����չ����������Ҫ�Ĺ��ܡ�\n
 * ��BlinkSpriteΪ����������α�д�µ���ȾԪ�ء�
 * @code
 * class BlinkSprite
 *	: public video:INode
 * {
 *	image_t m_Img;
 * public:
 *	BlinkSprite(image_t& img)
 *		: m_Img(img)
 *	void paint(){
 *		IVideo& Vi = GetVideo();
 *		Vi.setBlendColor(video::CBM_NONE, 0);
 *		Vi.setBlendMode(video::BM_NORMAL);
 *		Vi.renderImage_d(*m_Img.get(), rect(0, 0, 100, 100));
 *	}
 * };
 * @endcode
 * ������HelloScene�Ĺ��캯����������´��룺
 * @code
 * getRenderScene().addChild(ONEU_NEW(BlinkSprite(GetVideo().loadImage(L"picture.png"))), 1);
 * @endcode
 * �������У�picture.png��ʾ�����Ͻ�100 * 100�ľ����ڡ�\n
 * ��д@ref video::INode::paint�������ں������д��ȾԪ����Ⱦʱ������Ĳ�������INode�ĳ�ԱvisibleΪtrueʱ���ú�������ÿһ֡�����á�\n
 * @ref IVideo::setBlendColor������Ⱦ������ֻ����������Ⱦ�ڼ���ã���ֻ����@ref video::INode::paint��������á�\n
 * ������Ҫ�þ����ܹ���˸��\n
 * ΪBlinkSprite������³�Ա��
 * @code
 * bool m_bV;
 * @endcode
 * �ڹ��캯�����ʼ��Ϊtrue��\n
 * �޸�paint��������дINode::update������\n
 * @code
 *	void paint(){
 *		if(!m_bV) return;
 *		IVideo& Vi = GetVideo();
 *		Vi.setBlendColor(video::CBM_NONE, 0);
 *		Vi.setBlendMode(video::BM_NORMAL);
 *		Vi.renderImage_d(*m_Img.get(), rect(0, 0, 100, 100));
 *	}
 * void update(){
 *	m_bV = !m_bV;
 * }
 * @endcode
 * �������У�ͼ���ÿ��һ֡��˸һ�Ρ�\n
 * @ref video::INode::update��������visible��active��Ϊtrueʱ��ÿһ֡������õĺ���������ˢ�¶�����\n
 * @subsection section_to_extend ���ף���չ����
 * ����չ����֮ǰ����ȷ�������Ķ���@ref page_principles���˽��˱������ص�ԭ��
 * �μ�@ref page_extending��
 */
/**
 * @page author_backup ���߱���
 * @section section_layer ����ֲ�
 * �ļ������ܵĲ㼶��ϵ��Ϊ�˱�������Լ�����ʶ�ļ�ӵݹ飬�б�Ҫ���ײ����ֲ㣬ʹ�õͲ�εĲ��ܵ��ø߲�εĺ�����\n
 * ����ɵ͵��ߣ�
 *  - �������壨typedef����
 *  - IAllocator��Memory��
 *  - String����String���ڷ����ڴ�ʧ�ܵ�Ĭ�ϴ����ǲ����κβ�����
 *  - Logger��
 *  - Error��������
 *  - ���������������Ͻ����Ĺ��ܡ�
 *  -.
 *
 */

/* ----------------------------------------------------------------------------*/
/**
 * @page page_principles ���ԭ��
 * @section section_interface_principles dll���дԭ��
 * dll�����ܹ�������C�������ӵĿ⡣���ǿ��Խ���������dll���ṩͷ�ļ�������dll��exeʹ�á�\n
 * ����dll���ʱ��Ϊ���ܹ�������������ȷʹ�ã���Щ����������ء�\n
 * dll�����е�һЩͷ�ļ�����Ϊ���ͷ�ļ��ģ����Ǳ�Ĵ���ʹ�������ĸ�������Щͷ�ļ�ֻ�ܳ������¶��壨ֻ����Щ������ܱ��ⲿ������ȷʹ�ã���
 *  - Cʽ��ȫ�ֵ���������ʹ��ONEU_API��ʹһ��������ΪCʽ�ĵ�����������ONEU_API void Initialize();
 *  - �ӿ��࣬��ֻ�д��麯�����ࡣ
 *  - �����ࡣ���к���Ҫ�������Ҳ�������ľ�̬��Ա�����ͺ����ľ�̬������
 *  - �ӿ����������Ļ���塣
 *  .
 * ������������������ؿ��ܻᵼ�����Ӵ�������ı�����
 * @par �򵼣�
 * ����һ���µ����ʱ��һ��дһ���ӿ��࣬Ȼ������һ��ʵ���࣬ʵ���麯����
 * ����һ���������������������������Ǵ���ʵ����Ķ���һ��ʹ��ONEU_NEW�������Խӿ����ָ�뷵�ء�
 * ֻ�нӿ���͹���������¶���ⲿ���򣬶���������������
 * 
 * @section section_principles �����дԭ��ͷ��
 *  - ��dll���󼰱���ʹ��ONEU_NEW��ONEU_DELETEʵ���ڴ����ͻ��գ�Ϊ�����鷳����ͳһʹ���������
 *  - ��������Java�����񡣵��ʿ�ͷ��д������֮�����ַ����ӡ���Ա������һ������Сд��
 *  - ��ͽṹ�������������Ÿ�ռһ�С�����������һ�������뺯��ͷ������ͬһ�С�
 *  - ������������Klass_create���ӹ���������������������������Klass_build�����ٵ���Klass_destroy��
 *  - �ڱ��汾�У���ֹ�ͻ�delete�ӿڡ�Ӧ����destroy����ʾɾ���������е���������������
 *  - ����ǰ����˫�»��ߵ�Ϊ�ǳ��ײ�ķ��ţ��Ͻ��ͻ����á�
 *  - ����ǰ�е��»��ߵ�Ϊ�ϵײ�ķ��ţ�ʹ��������Ҫ��������Ƚϸ�Ч��
 *  - �ļ�·��ʹ����б�ܡ�
 *  - ʹ��dword����unsigned long��uint����unsigned int��
 *  - �ӿڵ�ͷ�ļ����������Doxygenע�͡�
 *  - ��ֹ�ӿں������������������г���STL�е��ࡣʹ��OneU��List��String���档
 *  - ����ͷ�ļ��ڱ�����\#pragma once�������еı��������ܻ᲻֧�֣������������ٶȻ��һ�㡣
 *  - ��ʹ��C++�쳣�����������쳣�����Խdll�������쳣��ʹ��ONEU_RAISE��������
 *  - operator new��operator delete�����������
 *  - ����ʹ��ȫ�ֱ�����ԭ����ֻ��Allocator�������������Ժ��������ʵ�����ܹ�����������˲��������ⶨ��ȫ�ֱ�����
 *  .
 */

/* ----------------------------------------------------------------------------*/
/**
 * @page page_run ����˵��
 * ����˳��
 *  - ����������
 *	- ����Game_build
 *		- �����ڴ��ϵͳ
 *   	- ������־ϵͳ
 *   	- new��Game
 *			- �����㲥
 *			- ����Atomϵͳ��Atom���ǽ����ڸ�ϵͳģ��֮�ϵģ�������֮ǰ����һ�����⣩
 *			- ����ͼ��ϵͳ
 *			- ��������ϵͳ
 *			- ��������
 *			.
 *  - ����Game��init������˳��ͼ��ϵͳ������ϵͳ���������Ϸ�߼���
 *  .
 *  ����˳����IGame::run�У�
 *   - ���ٳ���
 *   - �㲥�����¼�
 *   - ����Atom
 *   - ���ٿ���ϵͳ
 *   - ����ͼ��ϵͳ
 *   - ���ٹ㲥ϵͳ
 *   .
 *  @remarks һ�е��������Կ�������Game_build֮������ģ����Բ�����Game_build֮ǰʹ���ڴ�صȵ�����
 */
/* ----------------------------------------------------------------------------*/
/**
 * @page page_extending ��չ����
 * ��չ���������ĺ��ġ�\n
 * Ϊ�����д��չ�������¹��ܣ�������Ҫ��Ч����\n
 * �����߿��Ի�ȡ�ײ��DX�ӿ�ʵ�ָ�������δʵ�ֵĹ��ܣ�Ҳ���Զ��ÿ�Դ��Ϊ������һ��������\n
 * @section section_extend_form_class ��ʽ���
 * @par ��дdll�⡪��SDKʽ����չ
 * ����dll��дԭ���дdll������dll��ͷ�ļ������ɴ����κ��˿��õ�dll��չ�����˿���ͨ���������ӵķ�ʽʹ�ø���չ���μ�@ref section_interface_principles��
 * @par ��дat�⡪�������ƶ�̬���Է�����չ
 * ͬ����дdll������Atom���д��׼�������չ����Ϊat���ɡ�����loadAtom���ɼ��ظ���չ����չ����Atom���е������Ź���̬����ʹ�á�
 * ����Waterfall_atom.cpp��
 * @par ��д�ű���չ
 * ��at�⹦����ͬ��ֻ����չ��ʹ�ö�̬���Ա�д�ġ�
 * ��δʵ��
 * @par ʵ��LUA�ű���ϵͳ
 * ʵ����Ҫ�����ⲿ���ݵĹ���ʱ����������luaǿ�������ԣ������������ԣ������������ݡ�Ԫ���ݵȡ�
 * @section section_extend_functional_class �������
 * @par ������ǿ���
 * Ϊ�����ṩ�¹��ܣ������µ���Ⱦ��Ч���Ĳ������������������ڴ��븴�á�
 * @par ��ܲ��
 * Ϊ�����ṩ�߼���ܵĲ���������������������Ƹ��á�
 * ������ʵ��
 * @section section_atom_standards at��չ��д��׼
 * @par ��ѡ����������void AtomInit(pcwstr)
 * �ڼ��ص�ʱ�򱻵��ã����뵱ǰAtom�汾�š�
 * @par ��ѡ����������void AtomDestroy()
 * ��ж�ص�ʱ�򱻵��á�
 */
/* ----------------------------------------------------------------------------*/
/**
 * @page page_lua ʹ��LUA�ű���д��Ϸ
 * ���ʹ��bin/game/�µ�ִ�а���������Ϸ��\n
 * ����script/lua/�ļ��У��༭main.lua�ļ������������Ϸ����ʱ���ظ��ļ���\n
 * ���ļ��ж���Scene������Scene:init()��Scene:main()����������init����ֻ�ڳ�ʼ��ʱ���á�main�����ٳ���ÿһ֡������á�\n
 * һ��ű��ļ�ͷ�����иþ䡣
 * @code
 * require "stdlib"
 * @endcode
 * ��ʾʹ�ñ�׼�⣬��ʹ�������Դ��ķ��ſ⡣���Ųο��μ�@ref page_exports��
 * @section section_lua_display_image ��ʾͼ��
 * ����picture.pngͼ�񵽸�Ŀ¼��
 * �޸�main.lua����Scene:init()�в������´���
 * @code
 * self.sp = Sprite("picture.png", 0);
 * @endcode
 * ���г�����û�п���picture.png��ʾ�����ˣ�\n
 * Sprite�Ǳ�׼��ķ��ţ�������ʾͼƬ��
 * ��һ��ĺ�����ǽ����¾��飬�������������Ϊ������sp��Ա��
 * �������ľ������ʾ����Ļ�ϡ�
 * @section section_lua_retrieve_control ��Ӧ����
 * ������Ӧ������һ�ּ򵥷��������ǲ鿴�����豸��״̬�����Ծ��������ı䡣
 * @code
 * if Control:keyIsDown(Control.OIK_RIGHT) then
 *	self.sp:setX(self.sp:getX() + 10.0f);
 * end
 * @endcode
 * ControlҲ�Ǳ�׼��ķ��ţ����ڷ��ʿ���ϵͳ��
 * �þ京���ǣ������ַ�������Ҽ�������ʱ��������ƽ��10���ء�
 */
/* ----------------------------------------------------------------------------*/
/** 
* @page page_atom_lua Atom LUAǶ�����Բο�
*
* @section section_atom_lua Atomϵͳģ��
*
* ����atom value��һ�����ͣ�������function��env��klass��obj��obj_function��cpointer����һ�֡�\n
* ���³��ֵ�function��env�Ⱦ���ʾΪ�����͵�atom value����atom_v��ʾatom value��
*
* @par Atom.type(atom_v)
* 	����atom_v�����͡�
* 	����ֵ��
* 	- Atom.T_FUNC
* 	- Atom.T_OBJ
* 	- etc.
* 	.
* @par Atom.getEnv()
* 	����ȫ�ֻ�����
* @par Atom.G
* 	ȫ�ֻ�������Ч�ʸ��ߣ�
* @par Atom.getSymbol(atom_v, string)
* 	���atom_v����ֵ��env���ͻ�klass���ͣ�����Զ�ȥѰ�����������Ӧ�ı������Ҳ���ʱ����nil��
* 	���atom_v����ֵʱobj����Ѱ�����Ӧklass�ķ��š�
* @par Atom.call
* 	ԭ��1��Atom.call(function, ...)\n
* 		��...Ϊ����������function�����ط���ֵ��
* 	ԭ��2��Atom.call(obj_function, obj, ...)\n
* 		��...Ϊ��������objΪ�������obj_function�����ط���ֵ
* 	ԭ��3��Atom.call(klass, ...)\n
*		��...Ϊ���������ù��캯��������obj��
* @par Atom.createObj(klass, ...)
* 	ͬAtom.callԭ��3��
* @par Atom.traversalEnv(atom_v, function(symbol, value))
* 	atom_v������env��klass��obj��
* 	��ÿһ�����ŵ��ò���2��function������symbol�Ͷ�Ӧ��atom value��
* @par Atom.loadLib(libpath)
* 	����һ��Atom�⡣
* @par Atom.log(string)
* 	��string�������־�ļ���
* @par Atom.destroy(atom_v)
*	�������ٸñ�����
*
* @section section_atom_value atom value
*
* @par []�������ȡ����š�
* 	����env��klass��objΪȡ���еķ��š�\n
* 	��metatable�е�__indexΪAtom.getSymbol��
* @par ()����������á�
* 	����function����obj_functionΪ����֮��\n
* 	����klass��Ϊ��������Ķ���\n
* 	��matatable�е�__callδAtom.call��
*
*/
/* ----------------------------------------------------------------------------*/
/**
 * @page page_exports �������Ųο�
 * @b �ĵ�˵��<br>
 * [property]��ʾ�Ǹ�������ԣ�����setXXX��getXXX���������û��ȡ�����ԡ�<br>
 * <div style = "font-size:15px">
 * @b Sprite class<br>
 * Sprite(string path, int z) pathΪͼ��·����zΪ��ʾ��ȡ�<br>
 * <small>
 * X[property] float X����<br>
 * Y[property] float Y����<br>
 * CenterX[property] float ����X���꣬�ѹ�һ����<br>
 * CenterY[property] float ����Y���꣬�ѹ�һ����<br>
 * Rotation[property] float ��ת�ȣ��Զ�Ϊ��λ��<br>
 * ScaleX[property] float X�����ű���<br>
 * ScaleY[property] float Y�����ű���<br>
 * Color[property] int, int, int �ֱ�ΪR, G, Bֵ<br>
 * Alpha[property] int Alphaֵ<br>
 * BlendMode[property] int ���ģʽ 0Ϊ��ͨ 1Ϊ���<br>
 * ColorBlendMode[property] int ��Color���Թ��ã���ɫ���ģʽ��0Ϊ��ͨ��1Ϊ��ӣ�2Ϊ���ƣ�16���ϣ�32�һ�ϣ�48�ϻ�ϣ�64�»�ϡ��ֺ�����Ĳ����������ָ�����ӻ��ģʽ��<br>
 * </small>
 * @b Label class<br>
 * Label(float width, float height, int fontsize[, string fontname]) width, height��ǩ����Ŀ��, fontsize�����С, fontname�������ơ�<br>
 * X[property] float X����<br>
 * Y[property] float Y����<br>
 * Text[property] string ��ʾ����<br>
 * Color[property] int, int, int �ֱ�ΪR, G, Bֵ<br>
 * Alpha[property] int ͸����
 * @b Control object<br>
 * <small>
 * keyIsDown(int scancode):bool[o-function] �����̡��жϸü��Ƿ��ڰ���״̬��<br>
 * keyPress(int scancode):bool[o-function] �����̡��жϸü��Ƿ񱻰��¡�<br>
 * keyRelease(int scancode):bool[o-function] �����̡��жϸü��Ƿ��ͷ�<br>
 * buttonIsDown(int buttonID):bool[o-function] ����꡿�жϸü��Ƿ��ڰ���״̬��<br>
 * buttonPress(int buttonID):bool[o-function] ����꡿�жϸü��Ƿ񱻰��¡�<br>
 * buttonRelease(int buttonID):bool[o-function] ����꡿�жϸü��Ƿ��ͷ�<br>
 * ����꡿0��ʾ�����1��ʾ�Ҽ���2��ʾ�м���<br>
 * mouseOffset():int, int[o-function] ����꡿��ȡ��һ֡����֡������ƶ�������<br>
 * </small>
 * </div>
 */
/* ----------------------------------------------------------------------------*/
/**
 * @example HelloWorld.cpp
 * @example UseAtom.h
 * @example Waterfall_atom.cpp
 * @example SingleSceneGame.cpp
 * @example main.lua
 */

//@todo ����Timerϵͳ ��ʱһ��ʱ��ִ��ĳһ����
//@todo ����Resourceģ�����Releaseԭ�� ʹ�䷵����������
//@todo ��Resource�������ɲ���
//@todo ֧��RT��֧����������
}
