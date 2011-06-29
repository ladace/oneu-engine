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
 *  - @subpage page_script
 *  - @subpage page_extending
 *  - �ο�
 *		- @subpage page_run
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
 * �����¼�������@ref IGame::pushInputFocus��һ���¼��ɷ�����Ϊ���뽹�㣬���¼��ɷ������Խ��յ����̵������¼���
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
 *	game->replaceScene(ONEU_NEW HelloScene);
 *	int ret = game->run();
 *  Game_destroy();
 *  return ret;
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
 * getRenderScene().addChild(ONEU_NEW BlinkSprite(GetVideo().loadImage(L"picture.png")), 1);
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
 *  - ��������Java�����񡣵��ʿ�ͷ��д������֮�����ַ����ӡ���Ա������һ������Сд��
 *  - ��ͽṹ�������������Ÿ�ռһ�С�����������һ�������뺯��ͷ������ͬһ�С�
 *  - ������������Klass_create���ӹ���������������������������Klass_build�����ٵ���Klass_destroy��
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
 * @section section_memory �ڴ�������
 *  - ������AllocatedObject�Ķ�����Ա�ֱ�ӹ����ڴ棨ʹ������new�ȣ�������ʹ��ONEU_NEW����NEW��ʵ��׷���ڴ棨�����޷���֪�������ļ��������ȣ���
 *  - ԭ�����Ϳ���ʹ��ONEU_NEW_T���Լ�ONEU_NEW_ARRAY_T������ʹ��Ĭ���ڴ�ع����ڴ棨���̳ж���ʵ��Ҳ��ʹ�ã����������飬���������AllocatedObject����
 *  - C++Ĭ��new��Ȼ��Ч������new����ԭ�����ͻ�����ͨ������Ȼ��Ĭ����Ϊ��
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
 * @page page_memory �ڴ����
 * ʹ���Լ��Ķ����ڴ�����������ڴ档\n
 * �ڵ�ǰ�İ汾�У�ֻ��һ���ڴ��������ͨ������@ref GetAllocator����ȡ���á�\n
 * @ref AllocatedObject ���ڴ汻�������Ļ��ࡣ�����Ը���Ķ���ʹ��new�������ڴ�ʱ���Զ���ʹ���ڴ��������\n
 * �����ڴ���������ڴ棬�ɲ���dll���ޣ����κ�λ�ñ����������١�\n
 * C++Ĭ�ϵ�new��Ȼ����ʹ�ã����ǰ���C++�Ĺ���ͬһ��dll�������ڴ������ͬһ��dll���ͷš�\n
 * Ϊ��ʹ�÷��㣬�ṩ��һ������ڷ����ڴ档�������Կ����ڴ�׷�ٹ��ܣ�����ڴ�й¶��\n
 * - ONEU_NEW ����AllocatedObject�������ࡣ
 * - ONEU_NEW_T ����ԭ�����͡�
 * - ONEU_NEW_ARRAY_T ����ԭ���������顣
 * - ONEU_ALLOC ֱ�ӷ����ڴ档
 * .
 * 
*/
/* ----------------------------------------------------------------------------*/
/**
 * @page page_matrix_stack ����ջ(add 11.5.31)
 * @ref IVideo ��������ջ�������������Խ�����ѹ��ջ�л��ߵ�ջ������ΪӦ��Video�Ļ����ڼ�ִ�У�����ĳ��INode��paint�����\n
 * ����@ref IVideo::_getTransform �ɻ�õ�ǰ�ľ���ջ�����о�����˵Ľ��������ǰINode����ʱ�����ı任�����е���@ref IVideo::renderImage ���Զ�Ӧ�þ���ջ�ı任��
 * �����������֧�־���ջ�ı仯��Ҫ���øú�����ȡ�任������Ӧ�õ��Լ��Ļ�ͼ�С�\n
 * \n
 * ÿһ��INode��ѡ����2D�任��Ϣ����һ��INode���б任��Ϣ������ڻ���ʱѹ��ջ�С�����������OGRE��DeriveOrientation�ȡ���OGRE����ֽ�ĸ�ϸС���˴�������ջ�Ǵ���ȱ�ݵģ�
 * ���ھ���ջ��ʱ������ơ���
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
 * @par Ϊdll�ṩ�ű�֧��
 * ʹ��SWIG����д.i�ӿ��ļ�����ҪʱҪ���� OUE\\swig �ļ����µĽӿ��ļ���
 */
/* ----------------------------------------------------------------------------*/
/**
 * @page page_script ʹ�ýű���д��Ϸ
 * Ŀǰ�ű����ڱȽϾ����״̬��
 * Ŀǰʵ����Lua��Ruby�Ľӿڣ�������SWIG��Lua��֧��Directors�����Թ��ܺ����ޣ�һ��ֻ������������Ϸ��
 * 1.ʹ��ruby(recommanded)
 * �ṩ��������@ref RubyRun��ֱ�������������ü��ɣ�����Ҫ���κ������¡�
 * ����Game_build, Game_destroy�����߼�����Ruby�б�д��
 * 2.ʹ��Lua
 * ��Ҫ�Լ���дһ����������Ψһ�ĳ��������ο�r19��Game\\main.cpp��(ע�������°�ĸĶ�����Ҫ��run���������Game_destroy��
 * Game_build��Game.run�Ȼ����߼���C++���д��
 */
/**
 * @page page_problems PROBLEMS
 * PROBLEMS:
 * - Ruby��Luaʹ�÷�ʽ�е����졣�μ����档
 * - Ruby���쳣������C���ѽڵģ�ò����ʹ��longjmp)��Ҳ����˵���ʹ��DirectorʱĳЩ�����ľֲ������ᱻֱ��������һЩ����Ҳ���е�ʧ�ء�
 *   ����������⣬ֻҪ��֤���е�ϵͳ��Դ��ӱ�Game���У�Game_destroyȷ����ִ�У��Ϳ��Ա�֤��������Դй¶��
 * - Ҫ�����ٽű�������������Game����Ϊ�ű���������ı������ܹغ���Դ��
 * - �൱�ຯ�����ࣨ��Ҫ�ǽӿ��࣬Ҳ��core�е��ࣩ����Ҫ�����ڴ�������Ĵ��ڲſɱ�ʹ�á���Game_destroy�����ٵ��ڴ��������������Game_build֮ǰ��Game_destroy֮�󶼲���ʹ�á�
 *   ��������Ruby�߼���д��ʽ���ԣ����ڿ�ʼ���͵�ʱ��û���ڴ�������������RubyInterpreter�����ܴ��������ԲŻ�����˲�ʹ���ڴ��������RubyRun����������
 * - ���ڽű�����Э�����漰��Ownership����SWIG����ʱScript����ĳ�������ȡ��Ownership����ʱ�ֻ�ʧȥ����Ownership��ȡ��ʱ��һ��ͨ������ֵ��������ĳЩ��ʧȥOwnershipʱ��ʱ�ñ���������Ownership��
 * - win32��һ��������PostQuitMessage�����޷���ʾMessageBox�ˡ�
 * - Ŀǰ�������͵�typemap���ܲ������ơ�
 * - ���ڸ�SDK��������ȫ����ű���д�ģ���˵������ű�ʱ������Ownership�ȸ��ӵ����⣨������SWIG���ⲿWrap�ķ�ʽ���������ڽ������ƣ��������ű���д��Ҫ����SWIG���Լ�дSWIG��չ����
 *	- ÿ�ε���Get����������������ȡĳ������ʱ����ʵ���½���һ��script���Wrapper������һ��������ܶ�Ӧ���wrapper�������һ����ownership��ֻ����ownership�Ķ�������������ݡ������ͨ������ĳ������ownership��C++�ں����ߣ���Ҫ����ı�������ownership�Ķ�����Ϊ�ű������˲���Ҫ�ĸ����ԡ�������������ָ����ԣ���Ҫ��ÿ�����������ﶨ��һ����Ӧ�ű����VALUE��Ҳ��������ʽ��̣�һҪ���������ƣ���������ʹ��SWIG����SWIG�Ƿ�����ʽ��̣�
 *	- ���ʹ��SWIG��Ĭ�Ͽ�Ļ����������ܲ鿴һ�������Ƿ���ownership��Ҫ������Լ�д��һ�δ��룬��δ�����SWIG��Ӧ���Եľ���ʵ��ǿ��أ�������ִ�Ķ�����ʧЧ��������ʱ�Ƽ�swig2.0.4��
 *  - SWIG��������pcwstr��director�麯�����ܻ����ڴ汻��ǰ�ͷŵ����⡣��δ��֤��
 *	.
 * .
 * �ű���C++��Ե�����׳�Ī���������ĵط�����Ҫ�ر�ע�⣩��
 * - @ref IGame::pushInputReceiver��������ڽű��б��ָñ����������������ô����Ҹô�����ֵ�ʱ��������ġ�
 * - @ref IGame::replaceScene����������ַ��صı��������Զ�����ԭ���ĳ�����һ�㲻����ʹ�÷��صı������ᶪʧ���ű����ֵ���Ϣ������鷳��
 * - @ref INode::addChild����ownershipת�Ƹ����ڵ㣬�ű��������ָñ������ܻ�ʹ��ʾԪ����ʧ��
 * .
 * @attention ��Ҫ�Ķ���Game.run����Ҫ����Game.destroy
 * @remarks ����ӿڲμ�swig/*.i�ļ���
 */
/* ----------------------------------------------------------------------------*/
//ע�����Դ��� LuaInterpreter.cpp�к�RubyInterpreter.cpp��cpath�趨��debug�ļ����£������Դ��롣��release������û�а�cpath����release�ļ����£�ֱ��������ʵ�ǲ����ܵġ�
//ע��AtomDemo����Ŀǰ���ڲ�����״̬��

//@todo ����Timerϵͳ ��ʱһ��ʱ��ִ��ĳһ����
//@todo ����Resourceģ�����Releaseԭ�� ʹ�䷵����������
//@todo ��Resource�������ɲ���
//@todo ֧��RT��֧����������
}
