#ifndef __DESCRIPTION_SCENE_H__
#define __DESCRIPTION_SCENE_H__

#include "cocos2d.h"

class DescriptionScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback

	// 以下为主界面4个按钮的对应触发函数，需实现相关页面的跳转以及点击后字体的效果变化

	void backMenuCallback(cocos2d::Ref* pSender);    //  点击“返回”按钮的触发函数，需实现（1）跳转到主界面；（2）字体变化，以体现点击

	CREATE_FUNC(DescriptionScene);
};

#endif // __DESCRIPTION_SCENE_H__

