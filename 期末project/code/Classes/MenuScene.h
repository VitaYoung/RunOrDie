#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback

	// 以下为主界面4个按钮的对应触发函数，需实现相关页面的跳转以及点击后字体的效果变化

    void startMenuCallback(cocos2d::Ref* pSender);    //  点击“开始游戏”按钮的触发函数，需实现（1）跳转到游戏页面；（2）字体变化，选项前有“player”图标

	void descriptionMenuCallback(cocos2d::Ref* pSender);     //  点击“游戏说明”按钮的触发函数，需实现（1）跳转到说明页面；（2）字体变化，选项前有“player”图标

	void rankMenuCallback(cocos2d::Ref* pSender);       //  点击“得分排行”按钮的触发函数，需实现（1）跳转到排行榜页面；（2）字体变化，选项前有“player”图标

	void memberMenuCallback(cocos2d::Ref* pSender);       //  点击“制作团队”按钮的触发函数，需实现（1）跳转到成员名单页面；（2）字体变化，选项前有“player”图标
    
	cocos2d::MenuItemImage* startItem;

	cocos2d::MenuItemImage* descriptionItem;

	cocos2d::MenuItemImage* rankItem;

	cocos2d::MenuItemImage* teamItem;

	cocos2d::Sprite* logo1;

	cocos2d::Sprite* logo2;

	cocos2d::Sprite* logo3;

	cocos2d::Sprite* logo4;

	cocos2d::EventListenerMouse* event;

	void onMouseMove(cocos2d::Event* e);

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
