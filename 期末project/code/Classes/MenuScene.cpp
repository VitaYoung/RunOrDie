#include "MenuScene.h"
#include "GameSence.h"
#include "RankSence.h"
#include "MemberScene.h"
#include"DescriptionScene.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//  游戏名添加示例，改文件来源和位置即可
	auto name = Sprite::create("gamename.png");
	name->setPosition(720 + origin.x, origin.y + 550);
	this->addChild(name, 2);

	auto bg = Sprite::create("background.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 0);

	startItem = MenuItemImage::create("start.png", "start-0.png", CC_CALLBACK_1(MenuScene::startMenuCallback, this));
	startItem->setPosition(715 + origin.x, origin.y + 360);

	descriptionItem = MenuItemImage::create("description.png", "description-0.png", CC_CALLBACK_1(MenuScene::descriptionMenuCallback, this));
	descriptionItem->setPosition(720 + origin.x, origin.y + 270);

	rankItem = MenuItemImage::create("rank.png", "rank-0.png", CC_CALLBACK_1(MenuScene::rankMenuCallback, this));
	rankItem->setPosition(720 + origin.x, origin.y + 200);

	teamItem = MenuItemImage::create("team.png", "team-0.png", CC_CALLBACK_1(MenuScene::memberMenuCallback, this));
	teamItem->setPosition(720 + origin.x, origin.y + 130);

	auto menu = Menu::create(startItem, descriptionItem, rankItem, teamItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	auto item1 = Sprite::create("item1.png");
	auto fade1 = Sequence::create(FadeOut::create(5.0f), FadeIn::create(5.0f), nullptr);
	auto rotate1 = RotateBy::create(10.0f, 360.0f);
	auto spawn1 = Spawn::createWithTwoActions(fade1, rotate1);
	item1->runAction(RepeatForever::create(spawn1));
	item1->setPosition(200 + origin.x, origin.y + 700);
	this->addChild(item1, 1);

	auto item2 = Sprite::create("item2.png");
	auto fade2 = Sequence::create(FadeOut::create(4.0f), FadeIn::create(4.0f), nullptr);
	auto rotate2 = RotateBy::create(8.0f, 360.0f);
	auto spawn2 = Spawn::createWithTwoActions(fade2, rotate2);
	item2->runAction(RepeatForever::create(spawn2));
	item2->setPosition(1220 + origin.x, origin.y + 130);
	this->addChild(item2, 1);

	auto item3 = Sprite::create("item3.png");
	auto fade3 = Sequence::create(FadeOut::create(4.5f), FadeIn::create(4.5f), nullptr);
	auto rotate3 = RotateBy::create(9.0f, 360.0f);
	auto spawn3 = Spawn::createWithTwoActions(fade3, rotate3);
	item3->runAction(RepeatForever::create(spawn3));
	item3->setPosition(400 + origin.x, origin.y - 50);
	this->addChild(item3, 1);

	auto item4 = Sprite::create("item4.png");
	auto fade4 = Sequence::create(FadeOut::create(3.0f), FadeIn::create(3.0f), nullptr);
	auto rotate4 = RotateBy::create(5.0f, 360.0f);
	auto spawn4 = Spawn::createWithTwoActions(fade4, rotate4);
	item4->runAction(RepeatForever::create(spawn4));
	item4->setPosition(1100 + origin.x, origin.y + 850);
	this->addChild(item4, 1);

	auto monster1 = Sprite::create("Monster1.png");
	auto fade5 = Sequence::create(FadeOut::create(3.0f), FadeIn::create(5.0f), nullptr);
	auto rotate5 = RotateBy::create(2.0f, 360.f);
	auto spawn5 = Spawn::createWithTwoActions(fade5, rotate5);
	auto move = Sequence::create(MoveBy::create(2.5, Vec2(50, 0)), MoveBy::create(2.5, Vec2(0, -50)), MoveBy::create(2.5, Vec2(-50, 0)), MoveBy::create(2.5, Vec2(0, 50)), nullptr);
	auto spawn6 = Spawn::createWithTwoActions(spawn5, move);
	monster1->runAction(RepeatForever::create(spawn6));
	monster1->setPosition(100 + origin.x, origin.y + 200);
	this->addChild(monster1, 1);

	auto monster2 = Sprite::create("Monster1.png");
	auto fade6 = Sequence::create(FadeOut::create(3.0f), FadeIn::create(5.0f), nullptr);
	auto rotate6 = RotateBy::create(2.0f, 360.f);
	auto spawn7 = Spawn::createWithTwoActions(fade6, rotate6);
	auto move1 = Sequence::create(MoveBy::create(2, Vec2(-50, 0)), MoveBy::create(2, Vec2(0, -50)), MoveBy::create(2, Vec2(50, 0)), MoveBy::create(2, Vec2(0, 50)), nullptr);
	auto spawn8 = Spawn::createWithTwoActions(spawn7, move1);
	monster2->runAction(RepeatForever::create(spawn8));
	monster2->setPosition(1300 + origin.x, origin.y + 550);
	this->addChild(monster2, 1);

	logo1 = Sprite::create("player1.png");
	logo1->setPosition(510 + origin.x, origin.y + 350);
	logo1->setVisible(false);
	this->addChild(logo1, 2);

	logo2 = Sprite::create("player1.png");
	logo2->setPosition(600 + origin.x, origin.y + 270);
	logo2->setVisible(false);
	this->addChild(logo2, 2);

	logo3 = Sprite::create("player1.png");
	logo3->setPosition(600 + origin.x, origin.y + 200);
	logo3->setVisible(false);
	this->addChild(logo3, 2);

	logo4 = Sprite::create("player1.png");
	logo4->setPosition(600 + origin.x, origin.y + 130);
	logo4->setVisible(false);
	this->addChild(logo4, 2);

	event = EventListenerMouse::create();

	event->onMouseMove = CC_CALLBACK_1(MenuScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);

    return true;
}

void MenuScene::onMouseMove(Event* eve) {
	Rect startbutton = startItem->getBoundingBox();
	Rect descriptionbutton = descriptionItem->getBoundingBox();
	Rect rankbutton = rankItem->getBoundingBox();
	Rect teambutton = teamItem->getBoundingBox();

	EventMouse* e = (EventMouse*)eve;

	if (startbutton.containsPoint(e->getLocationInView())) {
		logo1->setVisible(true);
		logo2->setVisible(false);
		logo3->setVisible(false);
		logo4->setVisible(false);
	}

	if (descriptionbutton.containsPoint(e->getLocationInView())) {
		logo1->setVisible(false);
		logo2->setVisible(true);
		logo3->setVisible(false);
		logo4->setVisible(false);
	}

	if (rankbutton.containsPoint(e->getLocationInView())) {
		logo1->setVisible(false);
		logo2->setVisible(false);
		logo3->setVisible(true);
		logo4->setVisible(false);
	}

	if (teambutton.containsPoint(e->getLocationInView())) {
		logo1->setVisible(false);
		logo2->setVisible(false);
		logo3->setVisible(false);
		logo4->setVisible(true);
	}

	if (!startbutton.containsPoint(e->getLocationInView()) && !descriptionbutton.containsPoint(e->getLocationInView()) && !rankbutton.containsPoint(e->getLocationInView()) && !teambutton.containsPoint(e->getLocationInView())) {
		logo1->setVisible(false);
		logo2->setVisible(false);
		logo3->setVisible(false);
		logo4->setVisible(false);
	}
}


void MenuScene::startMenuCallback(Ref* pSender) {
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameSence::create();

	// add layer as a child to scene
	scene->addChild(layer);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MenuScene::descriptionMenuCallback(Ref* pSender) {
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = DescriptionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
}

void MenuScene::rankMenuCallback(Ref* pSender) {
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = RankSence::create();

	// add layer as a child to scene
	scene->addChild(layer);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MenuScene::memberMenuCallback(Ref* pSender) {
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MemberScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
}


