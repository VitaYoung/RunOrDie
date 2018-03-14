#include "MenuScene.h"
#include "DescriptionScene.h"
USING_NS_CC;

Scene* DescriptionScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = DescriptionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool DescriptionScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//title
	auto sprite1 = Sprite::create("description-title.png");
	sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height - 60));
	this->addChild(sprite1, 0);

	//游戏介绍
	auto sprite = Sprite::create("description-text.png");
	sprite->setScale(0.75, 0.75);
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150));
	this->addChild(sprite, 0);

	//图鉴
	auto sprite2 = Sprite::create("props.png");
	//sprite2->setScale(0.75, 0.75);
	sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite2, 0);

	//小刀
	auto sprite3 = Sprite::create("knife.png");
	sprite3->setScale(0.75, 0.75);
	sprite3->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 75));
	this->addChild(sprite3, 0);

	//炸弹
	auto sprite4 = Sprite::create("bomb.png");
	sprite4->setScale(0.75, 0.75);
	sprite4->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 170));
	this->addChild(sprite4, 0);

	//子弹
	auto sprite5 = Sprite::create("bullet.png");
	sprite5->setScale(0.75, 0.75);
	sprite5->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 260));
	this->addChild(sprite5, 0);

	//小刀图标
	auto tag1 = Sprite::create("knife-tag.png");
	tag1->setScale(0.1, 0.1);
	tag1->setPosition(Vec2(visibleSize.width / 2 + origin.x - 300, visibleSize.height / 2 + origin.y - 75));
	this->addChild(tag1, 0);

	//炸弹图标
	auto tag2 = Sprite::create("bomb-tag.png");
	tag2->setScale(0.1, 0.1);
	tag2->setPosition(Vec2(visibleSize.width / 2 + origin.x - 300, visibleSize.height / 2 + origin.y - 170));
	this->addChild(tag2, 0);

	//子弹图标
	auto tag3 = Sprite::create("bullet-tag.png");
	tag3->setScale(0.1, 0.1);
	tag3->setPosition(Vec2(visibleSize.width / 2 + origin.x - 300, visibleSize.height / 2 + origin.y - 260));
	this->addChild(tag3, 0);

	//  大体按设计图实现即可，最好使用艺术字
	auto circle1 = Sprite::create("circle1-75%.png");
	circle1->setPosition(690, 410);
	auto rotate1 = RotateBy::create(6.0f, -360.0f);
	circle1->runAction(RepeatForever::create(rotate1));
	this->addChild(circle1, 0);

	auto circle2 = Sprite::create("circle2.png");
	circle2->setPosition(520, 820);
	auto rotate2 = RotateBy::create(10.0f, 360.0f);
	circle2->runAction(RepeatForever::create(rotate2));
	this->addChild(circle2, 0);

	auto circle3 = Sprite::create("circle3.png");
	circle3->setPosition(860, -10);
	auto rotate3 = RotateBy::create(10.0f, 360.0f);
	circle3->runAction(RepeatForever::create(rotate3));
	this->addChild(circle3, 0);

	auto backItem = MenuItemImage::create("back-1.png", "back-2.png", CC_CALLBACK_1(DescriptionScene::backMenuCallback, this));
	backItem->setPosition(1350, 50);
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void DescriptionScene::backMenuCallback(Ref* pSender) {
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(menuscene);
}


