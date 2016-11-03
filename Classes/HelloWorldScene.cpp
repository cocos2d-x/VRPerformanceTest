#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static int SPRITE3D_TAG = 0;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//    
//    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));
//
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    
//    MenuItemFont::setFontName("fonts/arial.ttf");
//    MenuItemFont::setFontSize(65);
//    auto decrease = MenuItemFont::create(" - ", CC_CALLBACK_1(HelloWorld::delCallback, this));
//    decrease->setColor(Color3B(0,200,20));
//    auto increase = MenuItemFont::create(" + ", CC_CALLBACK_1(HelloWorld::addCallback, this));
//    increase->setColor(Color3B(0,200,20));
//    
//    auto menu = Menu::create(decrease, increase, nullptr);
//    menu->alignItemsHorizontally();
//    menu->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(menu, 1);
    
    auto event = EventListenerTouchAllAtOnce::create();
    event->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouch, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
    
    TTFConfig ttfCount("fonts/Marker Felt.ttf", 30);
    _label = Label::createWithTTF(ttfCount,"0 Sprite3D");
    _label->setColor(Color3B(0,200,20));
    _label->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 40));
    this->addChild(_label);
    
    _frameRate = Label::createWithTTF(ttfCount,"FrameRate");
    _frameRate->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 40));
    this->addChild(_frameRate);
    
    
    
    _spriteNode = Node::create();
    this->addChild(_spriteNode);
    
    scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float delta)
{
    char str[255];
    sprintf(str, "%f FrameRate", Director::getInstance()->getFrameRate());
    _frameRate->setString(str);
}

void HelloWorld::addCallback(cocos2d::Ref* sender)
{
    for (int i = 0; i < 10; ++i) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        float offsetX = CCRANDOM_MINUS1_1() * visibleSize.width * 0.25f;
        float offsetY = CCRANDOM_MINUS1_1() * visibleSize.height * 0.5f;
        
        auto sprite3d = Sprite3D::create("orc.c3b");
        sprite3d->setRotation3D(Vec3(0.0f, 180.0f, 0.0f));
        sprite3d->setPosition(Vec2(visibleSize.width/2 + origin.x + offsetX, visibleSize.height/2 + origin.y + offsetY));
        sprite3d->setScale(1.0f);
        auto animation = Animation3D::create("orc.c3b");
        if (animation) {
            auto animate = Animate3D::create(animation);
            sprite3d->runAction(RepeatForever::create(animate));
        }
        _spriteNode->addChild(sprite3d, 0, SPRITE3D_TAG);
        ++SPRITE3D_TAG;
    }
    char str[255];
    sprintf(str, "%d Sprite3D", SPRITE3D_TAG);
    _label->setString(str);
}

void HelloWorld::delCallback(cocos2d::Ref* sender)
{
    if (_spriteNode->getChildrenCount() < 10)
        return;
    for (int i = 0; i < 10; ++i) {
        --SPRITE3D_TAG;
        _spriteNode->removeChildByTag(SPRITE3D_TAG);
    }
    
    char str[255];
    sprintf(str, "%d Sprite3D", SPRITE3D_TAG);
    _label->setString(str);
}

void HelloWorld::onTouch(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    addCallback(event);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
