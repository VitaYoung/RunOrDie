#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;

class RankSence : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(RankSence);

	void backMenuCallback(Ref* pSender);

	Sprite* one;
	Sprite* two;
	Sprite* three;
	Sprite* four;
	Sprite* five;
	Sprite* six;
	Sprite* seven;
	cocos2d::Label*  labelone;
	cocos2d::Label*  labeltwo;
	cocos2d::Label*  labelthree;
	cocos2d::Label*  labelfour;
	cocos2d::Label*  labelfive;
	cocos2d::Label*  labelsix;
private:
	Size visibleSize;
	cocos2d::Vec2 origin;

};