#include "MenuScene.h"
#include "MemberScene.h"
USING_NS_CC;

Scene* MemberScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MemberScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MemberScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("nameyjj.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x - 225, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	auto sprite4 = Sprite::create("nameyzh.png");
	sprite4->setPosition(Vec2(visibleSize.width / 2 + origin.x + 75, visibleSize.height / 2 + origin.y));
	this->addChild(sprite4, 0);

	auto sprite2 = Sprite::create("nameyjh.png");
	sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x + 375, visibleSize.height / 2 + origin.y));
	this->addChild(sprite2, 0);

	auto sprite3 = Sprite::create("namewlm.png");
	sprite3->setPosition(Vec2(visibleSize.width / 2 + origin.x + 675, visibleSize.height / 2 + origin.y));
	this->addChild(sprite3, 0);

	auto tag1 = Sprite::create("jiajiayang.png");
	tag1->setScale(0.75, 0.75);
	tag1->setPosition(Vec2(visibleSize.width / 2 + origin.x - 470, visibleSize.height / 2 + origin.y + 150));
	this->addChild(tag1, 0);

	auto tag2 = Sprite::create("zhihuayang.png");
	tag2->setScale(0.75, 0.75);
	tag2->setPosition(Vec2(visibleSize.width / 2 + origin.x - 170, visibleSize.height / 2 + origin.y + 150));
	this->addChild(tag2, 0);

	auto tag3 = Sprite::create("jinhuiyang.png");
	tag3->setScale(0.75, 0.75);
	tag3->setPosition(Vec2(visibleSize.width / 2 + origin.x + 130, visibleSize.height / 2 + origin.y + 150));
	this->addChild(tag3, 0);

	auto tag4 = Sprite::create("linmanwu.png");
	tag4->setScale(0.75, 0.75);
	tag4->setPosition(Vec2(visibleSize.width / 2 + origin.x + 430, visibleSize.height / 2 + origin.y + 150));
	this->addChild(tag4, 0);

	//title
	auto sprite1 = Sprite::create("staff-title.png");
	sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height - 60));
	this->addChild(sprite1, 0);

	auto ani1 = Sprite::create("ani-1.png");
	ani1->setPosition(210, 100);
	this->addChild(ani1, 0);

	auto ani2 = Sprite::create("ani-2.png");
	ani2->setPosition(710, 100);
	this->addChild(ani2, 0);

	auto ani3 = Sprite::create("ani-3.png");
	ani3->setPosition(1210, 60);
	this->addChild(ani3, 0);

	auto ball = Sprite::create("ball.png");
	ball->setPosition(150, 700);
	this->addChild(ball, 0);


	auto bowl = Sprite::create("bowl.png");
	bowl->setPosition(200, 300);
	this->addChild(bowl, 0);

	auto carrot = Sprite::create("carrot.png");
	carrot->setPosition(700, 300);
	this->addChild(carrot, 0);

	auto bamboo = Sprite::create("bamboo.png");
	bamboo->setPosition(1200, 320);
	this->addChild(bamboo, 0);

	auto backItem = MenuItemImage::create("back-1.png", "back-2.png", CC_CALLBACK_1(MemberScene::backMenuCallback, this));
	backItem->setPosition(1350, 750);
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void MemberScene::backMenuCallback(Ref* pSender) {
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(menuscene);
}