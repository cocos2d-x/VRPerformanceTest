#include "AppDelegate.h"
#include "HelloWorldScene.h"
//VR_PLATFORM_INCLUDES_BEGIN
#include "malivr-sdk/CCVRMaliVRRenderer.h"
#include "malivr-sdk/CCVRMaliVRShaders.h"
//VR_PLATFORM_INCLUDES_END

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("VRPerformanceTest", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("VRPerformanceTest");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
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

//VR_PLATFORM_SOURCES_BEGIN
     auto vrImpl = new VRMaliVRRenderer;
     glview->setVR(vrImpl);
     std::string programHeaders = "#version 300 es\n #extension GL_OVR_multiview2 : enable\n precision highp float;\n precision highp int;\n";
     auto prog = GLProgram::createWithByteArrays(ccPositionTextureColor_malivr_vert, ccPositionTextureColor_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR);
     prog = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_malivr_vert, ccPositionTextureColor_noMVP_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
     prog = GLProgram::createWithByteArrays(ccPositionTextureColor_malivr_vert, ccPositionTextureColorAlphaTest_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST);
     prog = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_malivr_vert, ccPositionTextureColorAlphaTest_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV);
     prog = GLProgram::createWithByteArrays(ccPositionColor_malivr_vert ,ccPositionColor_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_COLOR);
     prog = GLProgram::createWithByteArrays(ccPositionColorTextureAsPointsize_malivr_vert ,ccPositionColor_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_COLOR_TEXASPOINTSIZE);
     prog = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_malivr_vert ,ccPositionColor_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP);
     prog = GLProgram::createWithByteArrays(ccPositionTexture_malivr_vert ,ccPositionTexture_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_TEXTURE);
     prog = GLProgram::createWithByteArrays(ccPositionTexture_uColor_malivr_vert, ccPositionTexture_uColor_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR);
     prog = GLProgram::createWithByteArrays(ccPositionTextureA8Color_malivr_vert, ccPositionTextureA8Color_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR);
     prog = GLProgram::createWithByteArrays(ccPosition_uColor_malivr_vert, ccPosition_uColor_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_U_COLOR);
     prog->bindAttribLocation("aVertex", GLProgram::VERTEX_ATTRIB_POSITION);
     prog = GLProgram::createWithByteArrays(ccPositionColorLengthTexture_malivr_vert, ccPositionColorLengthTexture_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR);
     prog = GLProgram::createWithByteArrays(ccLabel_malivr_vert, ccLabelDistanceFieldNormal_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL);
     prog = GLProgram::createWithByteArrays(ccLabel_malivr_vert, ccLabelDistanceFieldGlow_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW);
     prog = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_malivr_vert, ccPositionTexture_GrayScale_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_POSITION_GRAYSCALE);
     prog = GLProgram::createWithByteArrays(ccLabel_malivr_vert, ccLabelNormal_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_LABEL_NORMAL);
     prog = GLProgram::createWithByteArrays(ccLabel_malivr_vert, ccLabelOutline_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_LABEL_OUTLINE);
     prog = GLProgram::createWithByteArrays(cc3D_PositionTex_malivr_vert, cc3D_Color_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_POSITION);
     prog = GLProgram::createWithByteArrays(cc3D_PositionTex_malivr_vert, cc3D_ColorTex_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_POSITION_TEXTURE);
     prog = GLProgram::createWithByteArrays(cc3D_SkinPositionTex_malivr_vert, cc3D_ColorTex_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_SKINPOSITION_TEXTURE);
     GLchar def[256];
     auto conf = Configuration::getInstance();
     snprintf(def, sizeof(def)-1, "\n#define MAX_DIRECTIONAL_LIGHT_NUM %d \n" 
                   "\n#define MAX_POINT_LIGHT_NUM %d \n" 
                   "\n#define MAX_SPOT_LIGHT_NUM %d \n", 
                   conf->getMaxSupportDirLightInShader(), 
                   conf->getMaxSupportPointLightInShader(), 
                   conf->getMaxSupportSpotLightInShader()); 
     std::string stdDef = std::string(def); 
     prog = GLProgram::createWithByteArrays((stdDef + std::string(cc3D_PositionNormalTex_malivr_vert)).c_str(), (stdDef + std::string(cc3D_ColorNormal_malivr_frag)).c_str(), programHeaders, ""); 
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_POSITION_NORMAL);
     prog = GLProgram::createWithByteArrays((stdDef + std::string(cc3D_PositionNormalTex_malivr_vert)).c_str(), (stdDef + std::string(cc3D_ColorNormalTex_malivr_frag)).c_str(), programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_POSITION_NORMAL_TEXTURE);
     prog = GLProgram::createWithByteArrays((stdDef + std::string(cc3D_SkinPositionNormalTex_malivr_vert)).c_str(), (stdDef + std::string(cc3D_ColorNormalTex_malivr_frag)).c_str(), programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_SKINPOSITION_NORMAL_TEXTURE);
     std::string normalMapDef = "\n#define USE_NORMAL_MAPPING 1 \n";
     prog = GLProgram::createWithByteArrays((stdDef + normalMapDef + std::string(cc3D_PositionNormalTex_malivr_vert)).c_str(), (stdDef + normalMapDef + std::string(cc3D_ColorNormalTex_malivr_frag)).c_str(), programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_POSITION_BUMPEDNORMAL_TEXTURE);
     prog = GLProgram::createWithByteArrays((stdDef + normalMapDef + std::string(cc3D_SkinPositionNormalTex_malivr_vert)).c_str(), (stdDef + normalMapDef + std::string(cc3D_ColorNormalTex_malivr_frag)).c_str(), programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_SKINPOSITION_BUMPEDNORMAL_TEXTURE);
     prog = GLProgram::createWithByteArrays(cc3D_Particle_malivr_vert, cc3D_Particle_tex_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_PARTICLE_COLOR);
     prog = GLProgram::createWithByteArrays(cc3D_Particle_malivr_vert, cc3D_Particle_color_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_PARTICLE_TEXTURE);
     prog = GLProgram::createWithByteArrays(cc3D_Skybox_malivr_vert, cc3D_Skybox_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_SKYBOX);
     prog = GLProgram::createWithByteArrays(cc3D_Terrain_malivr_vert, cc3D_Terrain_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_3D_TERRAIN);
     prog = GLProgram::createWithByteArrays(ccCameraClearMalivrVert, ccCameraClearMalivrFrag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_CAMERA_CLEAR);
     prog = GLProgram::createWithByteArrays(ccPositionTextureColor_malivr_vert, ccETC1ASPositionTextureColor_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR);
     prog = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_malivr_vert, ccETC1ASPositionTextureColor_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR_NO_MVP);
     prog = GLProgram::createWithByteArrays(ccPositionTextureColor_malivr_vert, ccETC1ASPositionTextureGray_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY);
     prog = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_malivr_vert, ccETC1ASPositionTextureGray_malivr_frag, programHeaders, "");
     GLProgramCache::getInstance()->addGLProgram(prog, GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY_NO_MVP);
//VR_PLATFORM_SOURCES_END
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
