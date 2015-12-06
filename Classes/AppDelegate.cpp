#include "AppDelegate.h"
#include "MainScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // director初期化
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // 画面サイズ設定
    auto size = Director::getInstance()->getWinSize();
    float width  = 640.0f;
    float height = size.height / size.width * width;
    glview->setDesignResolutionSize(width, height, ResolutionPolicy::SHOW_ALL);

    // 60FPS, デバッグ(非)表示
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    
    // ファイルパス設定
    FileUtils::getInstance()->addSearchPath("res");
    FileUtils::getInstance()->addSearchPath("res/Default");
    FileUtils::getInstance()->addSearchPath("res/Font");
    FileUtils::getInstance()->addSearchPath("res/Image");
    FileUtils::getInstance()->addSearchPath("res/Scene");
    FileUtils::getInstance()->addSearchPath("res/Scene/EnemyList");
    FileUtils::getInstance()->addSearchPath("res/Scene/General");
    
    FileUtils::getInstance()->addSearchPath("tiled");
    FileUtils::getInstance()->addSearchPath("tiled/image");
    FileUtils::getInstance()->addSearchPath("tiled/image/school");
    FileUtils::getInstance()->addSearchPath("tiled/image/town");
    FileUtils::getInstance()->addSearchPath("tiled/image/world");

    FileUtils::getInstance()->addSearchPath("image");
    FileUtils::getInstance()->addSearchPath("image/character");
    
    
    
    // 
    Director::getInstance()->setProjection(Director::Projection::_2D);
    
    
#if 0
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    Size frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();
#endif
    
    
    // シーン読み込み
    auto scene = MainScene::createScene();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
