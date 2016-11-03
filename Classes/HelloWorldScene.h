#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    
    void addCallback(cocos2d::Ref* sender);
    void delCallback(cocos2d::Ref* sender);
    void onTouch(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    
    virtual void update(float delta) override;
    
private:
    
    cocos2d::Label *_label;
    cocos2d::Label *_frameRate;
    cocos2d::Node  *_spriteNode;
};

#endif // __HELLOWORLD_SCENE_H__
