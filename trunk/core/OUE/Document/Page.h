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
 *  - ����ӿ� @ref IAudio\n
 *  - ͼ�νӿ� @ref IVideo\n
 *  ������ʾ�͹���ͼ�񡢶�����
 *  - ���ƽӿ� @ref IControl\n
 *  ��������̺����������豸��
 *  - �����ӿ� @ref IScene\n
 *  ��������Ϸ�߼���һ��������һ���߼���Ԫ������Ϸ���������кʹ���
 * .
 * 
 * @subsection section_event �¼�ϵͳ(δ��ɣ�depracated)
 * �¼�ϵͳ���¼��ɷ��������������¼��������¼���������ɡ�ʹ���ַ���������һ���¼����¼��ɷ����ǽ����¼����࣬ͨ�����¼��ɷ�����Ӽ�����������ĳһ���¼�������������Ӷ����\n
 * Ŀǰ���¼�����û�в��ö��У����ڷ�����Ϣ��ͬʱִ�м������Ĵ���������\n
 * �����¼���ͨ���㲥ϵͳ�������㲥�����¼��ɷ����ļ̳��ࡣ\n
 * �����¼�������@ref IScene::pushInputFocus��һ���¼��ɷ�����Ϊ���뽹�㣬���¼��ɷ������Խ��յ����̵������¼���
 * @subsection section_renderscene ͼ��ϵͳ����Ⱦ����
 * ��������ʹ��������Ⱦ�����е�ÿһ���ڵ㼴��ʾһ����Ⱦ��������Ⱦʱ��������б�����\n
 * һ����Ⱦ������Ϊһ����Ⱦ����һ����ԣ�һ��������Ӧһ����Ⱦ������\n
 * @ref video::INode������Ⱦ�ڵ�Ľӿڣ�@ref video::ILayer�������к��ӵ���Ⱦ�ڵ�ӿڡ�zֵ��ʾһ����Ⱦ�ڵ������ֵܽڵ㱻��Ⱦ��˳��zֵС�Ļ��ȱ���Ⱦ��\n
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
 *	Game_build();
 *	IGame* game = GetGame();
 *	Aux_GameInit(L"Hello World", 800, 600, true);
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
 * @subpage page_memory��
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
 * @ref page_memory
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
 * ��дIAllocator����ʵ���Զ�����ڴ������������ԭ�����͡�AllocatedObjectĿǰ��֧���Զ����ڴ��������\n
 * C++Ĭ�ϵ�new��Ȼ����ʹ�ã����ǰ���C++�Ĺ���ͬһ��dll�������ڴ������ͬһ��dll���ͷš�\n
 * Ϊ��ʹ�÷��㣬�ṩ��һ������ڷ����ڴ档�������Կ����ڴ�׷�ٹ��ܣ�����ڴ�й¶��\n
 * - ONEU_NEW ����AllocatedObject�������ࡣ
 * - ONEU_NEW_T ����ԭ�����͡�
 * - ONEU_NEW_TA ����ԭ�����ͣ�ʹ���Զ����ڴ��������
 * - ONEU_NEW_ARRAY_T ����ԭ���������顣
 * - ONEU_NEW_ARRAY_TA ����ԭ���������飬ʹ���Զ����ڴ��������
 * - ONEU_ALLOC ֱ�ӷ����ڴ档
 * .
 * 
*/
/* ----------------------------------------------------------------------------*/
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
 * ʹ��ruby��д��Ϸ��\n
 * C++���֣��μ�Game/main.cpp�������������ñ�������@ref RubyRun��\n
 * Ruby�ű������������ļ����±�дscript/main.rb��\n
 * ����Game_build, Game_destroy�����߼�����Ruby�б�д��\n
 * ��checkout OUE/swig�´�������ȡ�ű��ο���
 */
/* ----------------------------------------------------------------------------*/
/**
 * @page page_problems PROBLEMS
 * PROBLEMS:
 * - Ruby���쳣������C���ѽڵģ�ò����ʹ��longjmp)��Ҳ����˵���ʹ��DirectorʱĳЩ�����ľֲ������ᱻֱ��������һЩ����Ҳ���е�ʧ�ء�
 *   ����������⣬ֻҪ��֤���е�ϵͳ��Դ��ӱ�Game���У�Game_destroyȷ����ִ�У��Ϳ��Ա�֤��������Դй¶��
 * - Ҫ�����ٽű�������������Game����Ϊ�ű���������ı������ܹغ���Դ��
 *   ��������Ruby�߼���д��ʽ���ԣ����ڿ�ʼ���͵�ʱ��û���ڴ�������������RubyInterpreter�����ܴ��������ԲŻ�����˲�ʹ���ڴ��������RubyRun����������
 * - ���ڽű�����Э�����漰��Ownership����SWIG����ʱScript����ĳ�������ȡ��Ownership����ʱ�ֻ�ʧȥ����Ownership��ȡ��ʱ��һ��ͨ������ֵ��������ĳЩ��ʧȥOwnershipʱ��ʱ�ñ���������Ownership��Ownership��ת�ƻ�������ิ���ԣ��Ѿ���ȡ����
 * - win32��һ��������PostQuitMessage�����޷���ʾMessageBox�ˡ�
 * - Ŀǰ�������͵�typemap���ܲ������ơ�
 * - ���ڸ�SDK��������ȫ����ű���д�ģ���˵������ű�ʱ������Ownership�ȸ��ӵ����⣨������SWIG���ⲿWrap�ķ�ʽ���������ڽ������ƣ��������ű���д��Ҫ����SWIG���Լ�дSWIG��չ����
 *		- ÿ�ε���Get����������������ȡĳ������ʱ����ʵ���½���һ��script���Wrapper������һ��������ܶ�Ӧ���wrapper�������һ����ownership��ֻ����ownership�Ķ�������������ݡ������ͨ������ĳ������ownership��C++�ں����ߣ���Ҫ����ı�������ownership�Ķ�����Ϊ�ű������˲���Ҫ�ĸ����ԡ�������������ָ����ԣ���Ҫ��ÿ�����������ﶨ��һ����Ӧ�ű����VALUE��Ҳ��������ʽ��̣�һҪ���������ƣ���������ʹ��SWIG����SWIG�Ƿ�����ʽ��̣�
 *		- SWIG��������pcwstr��director�麯�����ܻ����ڴ汻��ǰ�ͷŵ����⡣��δ��֤��
 *		.
 * .
 * �ű���C++��Ե�����׳�Ī���������ĵط�����Ҫ�ر�ע�⣩��
 * - @ref IScene::pushInputFocus��������ڽű��б��ָñ����������������ô����Ҹô�����ֵ�ʱ��������ġ�
 * - @ref IGame::replaceScene��ͬ�ϣ���Ҫʹ�ñ������֣�������ȫ�ֱ����������������δ���
 * - @ref video::ILayer::addChild����ownershipת�Ƹ����ڵ㣬�ű��������ָñ������ܻ�ʹ��ʾԪ����ʧ��
 * .
 * @remarks ����ӿڲμ�swig/*.i�ļ���
 */

//ע�����Դ��� RubyUtil.cpp��cpath�趨��debug�ļ����£������Դ��롣��release������û�а�cpath����release�ļ����£�ֱ��������ʵ�ǲ����ܵġ�

/**
 * @page page_ruby_reference ruby�ο�
 *
 * <h2>Basic Types</h2>
 * ע��{xyz}��ʾ�ô��ַ����ô������������ַ�����x��y��z���滻���Ǵ�openGL�ĵ��н��������д������һ��i��ʾint��f��ʾ��������
 * <h3>Color</h3>
 * �������ĸ��������������ʾΪColor���ͣ��ֱ������ɫ��red, green, blue, alpha������
 * <h3>Rect{if}.new</h3>
 * <h3>Rect{if}.new(left, top, right, bottom)</h3>
 * ���ĸ������ʾһ�����Ρ�
 * ���ԣ�
 *  - left
 *  - top
 *  - right
 *  - bottom
 *  .
 *
 * <h3>Vector{234}{if}.new</h3>
 * <h3>Vector{234}{if}.new(x, y, [z, [w]])</h3>
 * 2~4ά������
 * ���ԣ�
 *  - x
 *  - y
 *  - z��3ά������4ά������
 *  - w��4ά������
 *  .
 *
 * <h2>Module Functions</h2>
 *
 * <h3>Aux_GameInit(windowTitle, width, height, windowed)</h3>
 * �����⣺��ʼ����������ʼ����ϵͳ��δ������ϸ����ϵͳ��������
 * ��ʼ��windowTitle���ƵĴ��ڣ���width*heightΪ�ֱ��ʡ���windowedΪfalse������Ϸ��ȫ���ġ�
 * <h3>GetGame</h3>
 * ��ȡ����Ϸ��Game���ʵ����
 * <h3>GetVideo</h3>
 * ��ȡͼ��ģ�顣Video���ʵ����
 * <h3>GetAudio</h3>
 * ��ȡ����ģ�顣Audio���ʵ����
 * <h3>GetControl</h3>
 * ��ȡ����ģ�顣Control���ʵ����
 * <h3>GetScene</h3>
 * ��ȡ������Scene���ʵ����
 *
 *
 * <h2>Game Class</h2>
 * ����������Ϸ��Դ�Ķ����ࡣ
 *
 * <h3>getVideo</h3>
 * ��ȡͼ��ģ�顣Video���ʵ����
 * <h3>getAudio</h3>
 * ��ȡ����ģ�顣Audio���ʵ����
 * <h3>getControl</h3>
 * ��ȡ����ģ�顣Control���ʵ����
 * <h3>getScene</h3>
 * ��ȡ������Scene���ʵ����
 * 
 * <h3>init(windowTitle, width, height, windowed)</h3>
 * ��ʼ����ע��ú���������ʼ����ģ�顣һ��ʹ��Aux_GameInit��ʼ����
 * <h3>run</h3>
 * ������Ϸ��
 * <h3>quit</h3>
 * �˳���Ϸ��
 *
 * <h3>onFrame</h3>
 * Ϊ��Ϸ����֡�¼���
 * <h3>onActiveWindow(actived)</h3>
 * Ϊ��Ϸ���ڷ��ͼ���򷴼����¼���
 *
 * <h3>setWindowTitle</h3>
 * ���ô��ڱ��⡣
 * <h3>getWindowPos</h3>
 * ��ȡ����λ�á�
 * <h3>setWindowPos(pos)</h3>
 * ���ô���λ�á�
 * ����λ����Vector2i��ʾ��
 * <h3>showCursor(show)</h3>
 * ���ù����ʾ״̬��
 *
 * <h3>getFPS</h3>
 * ��ȡ��ǰFPS��
 * <h3>getTimeInverval</h3>
 * ��ȡ��һ֡�ĳ��ȡ�
 * <h3>replaceScene(scene)</h3>
 * �滻�³�����
 * @attention ��Ҫ����scene�����ã�����scene���ܻ���Ϊ�������ն���ʧ�����׳�����
 * 
 * <h3>onChar</h3>
 * �����ַ��¼���
 * <h3>onKey</h3>
 * ���Ͱ����¼���
 * <h3>onMouse</h3>
 * ��������¼���
 *
 * <h3>runShell</h3>
 * <h3>output</h3>
 *
 * <h3>showInfo</h3>
 *
 * 
 * <h2>Video Class</h2>
 * ͼ��ģ�顣
 * <h3>Constant(in Module)</h3>
 *  - Blend Mode
 *    ���ģʽ�������˸�ͼ���Ժ��ַ�ʽ���õ������ϡ�
 *  	- BM_NORMAL
 *  	��ͨģʽ��
 *  	- BM_ADD
 *  	�ӷ�ģʽ��
 *  	.
 *  - Color Blend Mode
 *    ��ɫ���ģʽ������ͼ����ĳ����ɫ�Ը�ģʽ��ϻ��������ϡ��ɽ���λ�ĺ��㷨�Ľ��ʹ�á�
 *  	- CBM_NONE
 *  	����ϡ�
 *  	- CBM_ADD
 *  	�ӷ�ģʽ��
 *  	- CBM_MODULATE
 *  	����ģʽ�����˷�ģʽ��
 *  	- CBM_LEFT
 *  	���ϡ�
 *  	- CBM_RIGHT
 *  	�һ�ϡ�
 *  	- CBM_TOP
 *  	�ϻ�ϡ�
 *  	- CBM_DOWN
 *  	�»�ϡ�
 *  	.
 *  .
 *
 * <h3>Image_t Class</h3>
 * ͼ���ࡣ����һ��ͼ�񻺴档
 * ֻ�����ԣ�
 *  - width
 *  - height
 *  .
 *
 *  
 * <h3>getName</h3>
 * <h3>prepare</h3>
 * <h3>init</h3>
 * 
 * <h3>switchDevice(width, height, windowed)</h3>
 * �л��豸����width * height�ֱ��ʡ���windowedΪtrue���򴰿ڻ���
 * <h3>isWindowed</h3>
 * �Ƿ񴰿ڻ�
 * <h3>getDeviceSize</h3>
 * ��ȡ�ֱ��ʴ�С��
 * <h3>loadImage(filename)</h3>
 * ��ȡͼ��
 * <h3>getRoot</h3>
 * ��ȡ����Ⱦ��㡣
 * <h3>getRenderScene</h3>
 * ��ȡ��ǰ��Ⱦ������
 * <h3>setRenderScene</h3>
 * ���õ�ǰ��Ⱦ������
 * <h3>createRenderScene</h3>
 * ������Ⱦ������
 * <h3>showInfo</h3>
 * <h3>getAvailableMode</h3>
 * ��ȡ�������е���ʾģʽ��
 *
 * 
 * <h2>Audio Class</h2>
 * ����ģ�顣
 *
 * <h3>Sound_t</h3>
 *
 * <h3>init</h3>
 * <h3>loadSound(filename, streamed)</h3>
 * ��ȡ������Ŀǰֻ֧��ogg����streamedΪtrue�������������롣
 * <h3>playMusic</h3>
 * ��������Ϊ�������ֲ��š�
 * <h3>stopMusic</h3>
 * ֹͣ��ǰ�������֡�
 * <h3>getPlayingMusic</h3>
 * ��ȡ��ǰ������
 * <h3>playFX</h3>
 * ������Ч��
 *
 *
 * <h2>Control Class</h2>
 * 
 * <h3>init</h3>
 * <h3>keyIsDown(scancode)</h3>
 * <h3>keyPress(scancode)</h3>
 * <h3>keyRelease(scancode)</h3>
 * �ֱ��ʾɨ����Ϊscancode�ļ��̰����Ƿ񱻰��¡��ڸ�֡�����¡��ڸ�֡���ͷš�
 * <h3>buttonIsDown(id)</h3>
 * <h3>buttonRelease(id)</h3>
 * <h3>buttonPress(id)</h3>
 * �ֱ��ʾid�������갴���Ƿ񱻰��¡��ڸ�֡�����¡��ڸ�֡���ͷš�
 * <h3>mouseOffset</h3>
 * ǰһ֡����ǰ֡���������ƶ���ƫ������
 *
 * <h3>Key Scan Code Constant(in Module)</h3>
 * @ref page_key_scan_code
 *
 * <h2>Scene Class</h2>
 * Abstract Class.
 *
 * <h3>RS</h3>
 * �ó�����Ӧ����Ⱦ������inherits Layer.
 * <h3>pushInputFocus(ir)</h3>
 * <h3>popInputFocus</h3>
 * ���뽹��ѹջ����ջ����ջ���ض��˵����뽹�㡣
 * 
 * override
 * <h3>update(dt)</h3>
 * ���º�����dtΪ��ǰ֡��ʱ�䳤�ȡ���Ҫ����д��
 *
 *
 * <h2>VideoNode Class</h2>
 *
 * ����Ⱦ�ڵ��ࡣ
 * <h3>{xy}</h3>
 * <h3>{xy}=</h3>
 * x��y���ꡣ
 * <h3>o{xy}</h3>
 * <h3>o{xy}=</h3>
 * ����x��y���ꡣ
 * <h3>rotation</h3>
 * <h3>rotation=</h3>
 * ��ת�ȡ���ʱ��Ϊ�����ԽǶȼơ�
 * <h3>scale{XY}</h3>
 * <h3>scale{XY}=</h3>
 * x��y�ϵ����š�
 * <h3>visible</h3>
 * <h3>visible=</h3>
 * �Ƿ�ɼ���
 * <h3>active</h3>
 * <h3>active=</h3>
 * �Ƿ��������Ƿ����ø��º�����
 *
 * <h3>parent</h3>
 * ���ڵ㡣
 * <h3>detach</h3>
 * �Ӹ��ڵ������롣
 * <h3>update(dt)</h3>
 * ���½ڵ㡣
 * <h3>name</h3>
 * <h3>create2DTransform</h3>
 * ����2D�任��ĳЩ��Ⱦ�ڵ�Ҫ����2D�任����ʹ�任���������á�//todo
 *
 * <h2>Layer Class</h2>
 * Inherits VideoNode.
 * <h3>name</h3>
 * <h3>addChild(child, z)</h3>
 * ���뺢�ӡ�zΪ������ȡ�
 * @attention ��Ҫ�ڽű��б���child�����ã�����ýڵ���ܻ���Ϊ�������ն���ʧ��
 *
 *
 * <h2>Sprite Class</h2>
 * Inherits VideoNode.
 * ���飬��ʾͼ��
 *
 * <h3>new(filename)</h3>
 * <h3>new(image)</h3>
 * �������顣
 * <h3>o{hv}</h3>
 * <h3>o{hv}=</h3>
 * �������꣬��һ����
 * <h3>color</h3>
 * <h3>color=</h3>
 * ���ӵ���ɫ��
 * <h3>alpha</h3>
 * <h3>alpha=</h3>
 * ͸���ȡ�
 * <h3>srcRect</h3>
 * <h3>srcRect=</h3>
 * ��ͼ���ļ���ȡ��Դ���Ρ�
 * <h3>width</h3>
 * <h3>height</h3>
 * ͼ�ο�ߡ�
 *
 * <h3>image</h3>
 * <h3>image=</h3>
 * ��ʾͼ��
 *
 * <h3>blendMode</h3>
 * <h3>blendMode=</h3>
 * ���ģʽ��
 * <h3>colorBlendMode</h3>
 * <h3>colorBlendMode=</h3>
 * ��ɫ���ģʽ��
 * 
 * <h2>Label Class</h2>
 * Inherits VideoNode.
 * ��ǩ����ʾ�ı���
 *
 * <h3>Constant(in Module)</h3>
 * ���뷽ʽ
 *  - T_LEFT
 *  - T_RIGHT
 *  - T_CENTER
 *  - T_TOP
 *  - T_BOTTOM
 *  - T_VCENTER
 *  .
 * 
 * <h3>new(width, height, fontSize, font = default)</h3>
 * ������ǩ��fontΪ�ַ�������ʾ�������ơ�
 * <h3>alpha</h3>
 * <h3>alpha=</h3>
 * ͸���ȡ�
 * <h3>text</h3>
 * <h3>text=</h3>
 * ��ʾ�ı���
 * <h3>color</h3>
 * <h3>color=</h3>
 * �ı���ɫ��
 * <h3>align</h3>
 * <h3>align=</h3>
 * �ı����뷽ʽ��
 * 
 *
 * <h2>Shape Class</h2>
 * Inherits VideoNode.
 * ��״��
 * 
 * <h3>new(rect)</h3>
 * ����������״��
 * <h3>color</h3>
 * <h3>color=</h3>
 * ��״��ɫ��
 * <h3>mode</h3>
 * <h3>mode=</h3>
 * �Ƿ�ֻ���Ʊ߿�
 *
 * <h2>Event Classes</h2>
 * <h3>CharEvent</h3>
 * getChar - �����ַ���
 * <h3>KeyEvent</h3>
 * getCode - ����ɨ���롣
 * isRelease - �Ƿ�Ϊ�����ͷ��¼���
 * isPress - �Ƿ�Ϊ���������¼���
 * <h3>MouseEvent</h3>
 * getButtonID - ��ð�ťID��
 * isRelease - �Ƿ�Ϊ��ť�ͷ��¼���
 * isPress - �Ƿ�Ϊ��ť�����¼���
 *
 *
 * <h2>InputReceiver Classes</h2>
 * �����������
 * ��������д��������Ϊ��
 * override
 * <h3>onChar(event)</h3>
 * ����CharEvent�����InputReceiver�յ��ַ��¼�ʱ�����á�
 * <h3>onKey(event)</h3>
 * ����KeyEvent�����InputReceiver�յ������¼�ʱ�����á�
 * <h3>onMouse(event)</h3>
 * ����MouseEvent�����InputReceiver�յ�����¼�ʱ�����á�
 *
 * ...todo remove BroadCast?
 * ...todo remove Shell?
 */
/**
 * @page page_key_scan_code ɨ�����б�
 *
 * - IK_ESCAPE
 * - IK_1
 * - IK_2
 * - IK_3
 * - IK_4
 * - IK_5
 * - IK_6
 * - IK_7
 * - IK_8
 * - IK_9
 * - IK_0
 * - IK_MINUS
 * - IK_EQUALS
 * - IK_BACK
 * - IK_TAB
 * - IK_Q
 * - IK_W
 * - IK_E
 * - IK_R
 * - IK_T
 * - IK_Y
 * - IK_U
 * - IK_I
 * - IK_O
 * - IK_P
 * - IK_LBRACKET
 * - IK_RBRACKET
 * - IK_RETURN
 * - IK_LCONTROL
 * - IK_A
 * - IK_S
 * - IK_D
 * - IK_F
 * - IK_G
 * - IK_H
 * - IK_J
 * - IK_K
 * - IK_L
 * - IK_SEMICOLON
 * - IK_APOSTROPHE
 * - IK_GRAVE
 * - IK_LSHIFT
 * - IK_BACKSLASH
 * - IK_Z
 * - IK_X
 * - IK_C
 * - IK_V
 * - IK_B
 * - IK_N
 * - IK_M
 * - IK_COMMA
 * - IK_PERIOD
 * - IK_SLASH
 * - IK_RSHIFT
 * - IK_MULTIPLY
 * - IK_LMENU
 * - IK_SPACE
 * - IK_CAPITAL
 * - IK_F1
 * - IK_F2
 * - IK_F3
 * - IK_F4
 * - IK_F5
 * - IK_F6
 * - IK_F7
 * - IK_F8
 * - IK_F9
 * - IK_F10
 * - IK_NUMLOCK
 * - IK_SCROLL
 * - IK_NUMPAD7
 * - IK_NUMPAD8
 * - IK_NUMPAD9
 * - IK_SUBTRACT
 * - IK_NUMPAD4
 * - IK_NUMPAD5
 * - IK_NUMPAD6
 * - IK_ADD
 * - IK_NUMPAD1
 * - IK_NUMPAD2
 * - IK_NUMPAD3
 * - IK_NUMPAD0
 * - IK_DECIMAL
 * - IK_OEM_102
 * - IK_F11
 * - IK_F12
 * - IK_F13
 * - IK_F14
 * - IK_F15
 * - IK_KANA
 * - IK_ABNT_C1
 * - IK_CONVERT
 * - IK_NOCONVERT
 * - IK_YEN
 * - IK_ABNT_C2
 * - IK_NUMPADEQUALS
 * - IK_PREVTRACK
 * - IK_AT
 * - IK_COLON
 * - IK_UNDERLINE
 * - IK_KANJI
 * - IK_STOP
 * - IK_AX
 * - IK_UNLABELED
 * - IK_NEXTTRACK
 * - IK_NUMPADENTER
 * - IK_RCONTROL
 * - IK_MUTE
 * - IK_CALCULATOR
 * - IK_PLAYPAUSE
 * - IK_MEDIASTOP
 * - IK_VOLUMEDOWN
 * - IK_VOLUMEUP
 * - IK_WEBHOME
 * - IK_NUMPADCOMMA
 * - IK_DIVIDE
 * - IK_SYSRQ
 * - IK_RMENU
 * - IK_PAUSE
 * - IK_HOME
 * - IK_UP
 * - IK_PRIOR
 * - IK_LEFT
 * - IK_RIGHT
 * - IK_END
 * - IK_DOWN
 * - IK_NEXT
 * - IK_INSERT
 * - IK_DELETE
 * - IK_LWIN
 * - IK_RWIN
 * - IK_APPS
 * - IK_POWER
 * - IK_SLEEP
 * - IK_WAKE
 * - IK_WEBSEARCH
 * - IK_WEBFAVORITES
 * - IK_WEBREFRESH
 * - IK_WEBSTOP
 * - IK_WEBFORWARD
 * - IK_WEBBACK
 * - IK_MYCOMPUTER
 * - IK_MAIL
 * - IK_MEDIASELECT
 *
 * - IK_BACKSPACE
 * - IK_NUMPADSTAR
 * - IK_LALT
 * - IK_CAPSLOCK
 * - IK_NUMPADMINUS
 * - IK_NUMPADPLUS
 * - IK_NUMPADPERIOD
 * - IK_NUMPADSLASH
 * - IK_RALT
 * - IK_UPARROW
 * - IK_PGUP
 * - IK_LEFTARROW
 * - IK_RIGHTARROW
 * - IK_DOWNARROW
 * - IK_PGDN
 *
 * - IK_CIRCUMFLEX
 * .
 * 
 */
//@todo ֧��RT��֧����������
//@todo oload����ϸд��
}
