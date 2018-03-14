#ifndef __GAMESENCE_H__
#define __GAMESENCE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
class GameSence : public cocos2d::Layer 
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameSence);

	void onMouseMove(cocos2d::Event* event);
	void updateCustom(float dt);
	void updateBuff(float dt);
	void update(float dt);
	void hitByMonster(float dt);
	void hitByBuff(float dt);
	void preloadMusic();
	void playBgm();
	void meet(EventCustom* event);
	void backMenuCallback(Ref* pSender);
//private:
	Sprite* player;
	Sprite* sword;
	Sprite* boom;
	Sprite* shoot1;
	Sprite* shoot2;
	Sprite* shoot3;
	Sprite* shoot4;
	Sprite* shoot5;
	Sprite* shoot6;
	Sprite* shoot7;
	Sprite* shoot8;
	Sprite* score;
	cocos2d::Label*  labelscore;
	Size visibleSize;
	cocos2d::EventListenerMouse* _mouseListener;
	int dtime;
	int btime;
	int swordtime;
	int killnum;
	cocos2d::Vec2 origin;
};
#endif
