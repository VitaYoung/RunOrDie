#include"GameSence.h"
#include"Monster.h"
#include <algorithm>
#include"SimpleAudioEngine.h"
#include"sqlite3.h"
#include"MenuScene.h"
#pragma comment(lib, "sqlite3.lib") 


USING_NS_CC;
template <typename T> std::string tostr(const T& t) { std::ostringstream os; os << t; return os.str(); }
using namespace CocosDenshion;

Scene* GameSence::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	//ccColor4B color = ccc4(238, 255, 255, 255);
	auto *layer = GameSence::create();

	//layer ->setColor(ccc3(255, 182, 193));

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameSence::init() {
	if (!Layer::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//添加计分器
	score = Sprite::create("score.png");
	score->setPosition(100, visibleSize.height - 20);
	this->addChild(score, 1);

	labelscore = Label::createWithTTF("100", "fonts/txjz.ttf", 50);
	labelscore->setPosition(Vec2(30 + score->getContentSize().width, visibleSize.height - 25));
	labelscore->setColor(ccc3(0, 0, 0));
	this->addChild(labelscore, 1);

	//创建数据库
	sqlite3* pdb = NULL;
	std::string path = FileUtils::getInstance()->getWritablePath() + "save.db";
	int result = sqlite3_open(path.c_str(), &pdb);
	std::string sql = "create table rank(ID int primary key not null, score int);";
	//result = sqlite3::exec(pdb, sql.c_str(), NULL, NULL, NULL);
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);

	//添加player
	player = Sprite::create("player2.png");
	player->setScale(0.08, 0.08);
	auto rotate = RotateBy::create(1.0f, 360.0f);
	player->setAnchorPoint(Vec2(0.5, 0.5));
	player->setPosition(visibleSize.width / 2, player->getContentSize().height);
	player->setName("player");
	player->runAction(RepeatForever::create(rotate));
	this->addChild(player, 1);

	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(GameSence::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	killnum = 0;
	// 添加刷新Monster和buff的计时器
	dtime = 0;
	btime = 0;
	schedule(schedule_selector(GameSence::updateCustom), 0.01f, kRepeatForever, 0);


	//添加判断碰撞的计时器, player hitted by buff
	schedule(schedule_selector(GameSence::update), 0.01f, kRepeatForever, 0);

	//player hitted by monster
	schedule(schedule_selector(GameSence::hitByMonster), 0.1f, kRepeatForever, 0);

	//monster hitted by buff
	schedule(schedule_selector(GameSence::hitByBuff), 0.1f, kRepeatForever, 0);

	//preload music 
	preloadMusic();
	playBgm();
}

void GameSence::onMouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	Director::getInstance()->getOpenGLView()->setCursorVisible(false);
	player->setPosition(e->getLocationInView());
}


void GameSence::updateCustom(float dt) {
	dtime++;
	auto fac = Factory::getInstance();

	if (dtime % 400 == 0) {
		//获取怪物工厂，添加怪物
		for (int i = 0; i < 2; i++) {
			auto mos = fac->createMonster1();
			float x = random(origin.x, visibleSize.width);
			float y = random(origin.y, visibleSize.height);
			mos->setPosition(x, y);
			addChild(mos, 3);
		}
		for (int i = 0; i < 2; i++) {
			auto mos = fac->createMonster2();
			float x = random(origin.x, visibleSize.width);
			float y = random(origin.y, visibleSize.height);
			mos->setPosition(x, y);
			addChild(mos, 3);
		}
		
	}
	if (dtime % 100 == 0) {
		float x = random(origin.x, visibleSize.width);
		float y = random(origin.y, visibleSize.height);
		Vec2 newpsoition;
		newpsoition.x = x;
		newpsoition.y = y;
		fac->moveMonster2(newpsoition, 1);
	}
	//移动怪物
	Vec2 playerpos = player->getPosition();
	fac->moveMonster1(playerpos, 0.01f);

	//添加buff
	if (dtime % 400 == 0) {
		auto buff = fac->createBuff();
		float x = random(origin.x, visibleSize.width);
		float y = random(origin.y, visibleSize.height);
		buff->setPosition(x, y);
		addChild(buff, 3);
	}
	//移动buff
	if (dtime % 100 == 0) {
		fac->moveBuff(1);
	}

}

void GameSence::update(float dt) {
	auto fac = Factory::getInstance();
	swordtime++;
	btime++;
	if (sword != NULL) {
		if (swordtime == 300) {
			Sequence* seq = Sequence::create(CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, sword)), NULL);
			sword->runAction(seq);
			sword = NULL;
		}
		if (swordtime < 295)
		sword->setPosition(player->getPosition());
	}
	Sprite* meetbuffw = fac->colliderBuffW(player->getBoundingBox());
	if (meetbuffw != NULL) {
		SimpleAudioEngine::getInstance()->playEffect("music/sword.wav", false);
		if (sword == NULL) {
			fac->removeBuffW(meetbuffw);
			swordtime = 0;
			sword = Sprite::create("sword2.png");
			sword->setScale(0.5, 0.5);
			auto rotate = RotateBy::create(0.5f, 360.0f);
			//sword->setPosition(player->getPosition());
			sword->runAction(RepeatForever::create(rotate));
			this->addChild(sword, 1);
		}
	}
	Sprite* meetbuffb = fac->colliderBuffB(player->getBoundingBox());
	if (meetbuffb != NULL) {
		SimpleAudioEngine::getInstance()->playEffect("music/bomb.wav", false);
		btime = 0;
		boom = Sprite::create("boom1.png");
		boom->setScale(0.6, 0.6);
		fac->removeBuffB(meetbuffb);
		auto fadein = FadeIn::create(1.5f);
		auto fadeout = FadeOut::create(1.5f);
		Sequence* seq = Sequence::create(fadein, fadeout, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, boom)), NULL);
		//Sequence* seq = Sequence::create(fadein, fadeout, NULL);
		boom->setPosition(player->getPosition());
		boom->runAction(seq);
		this->addChild(boom, 1);
	}
	Sprite* meetbuffs = fac->colliderBuffS(player->getBoundingBox());
	if (meetbuffs != NULL) {
		SimpleAudioEngine::getInstance()->playEffect("music/bullet.wav", false);

		shoot1 = Sprite::create("shoot1.png");
		shoot1->setScale(0.7, 0.7);
		shoot1->setPosition(player->getPosition());

		shoot2 = Sprite::create("shoot2.png");
		shoot2->setScale(0.7, 0.7);
		shoot2->setPosition(player->getPosition());

		shoot3 = Sprite::create("shoot3.png");
		shoot3->setScale(0.7, 0.7);
		shoot3->setPosition(player->getPosition());

		shoot4 = Sprite::create("shoot4.png");
		shoot4->setScale(0.7, 0.7);
		shoot4->setPosition(player->getPosition());

		shoot5 = Sprite::create("shoot5.png");
		shoot5->setScale(0.7, 0.7);
		shoot5->setPosition(player->getPosition());

		shoot6 = Sprite::create("shoot6.png");
		shoot6->setScale(0.7, 0.7);
		shoot6->setPosition(player->getPosition());

		shoot7 = Sprite::create("shoot7.png");
		shoot7->setScale(0.7, 0.7);
		shoot7->setPosition(player->getPosition());

		shoot8 = Sprite::create("shoot8.png");
		shoot8->setScale(0.7, 0.7);
		shoot8->setPosition(player->getPosition());

		fac->removeBuffS(meetbuffs);

		this->addChild(shoot1, 1);
		this->addChild(shoot2, 1);
		this->addChild(shoot3, 1);
		this->addChild(shoot4, 1);
		this->addChild(shoot5, 1);
		this->addChild(shoot6, 1);
		this->addChild(shoot7, 1);
		this->addChild(shoot8, 1);
		shoot1->runAction(MoveBy::create(2.0f, Vec2(0, visibleSize.height)));
		shoot2->runAction(MoveBy::create(2.0f, Vec2(visibleSize.width, 0)));
		shoot3->runAction(MoveBy::create(2.0f, Vec2(0, -visibleSize.height)));
		shoot4->runAction(MoveBy::create(2.0f, Vec2(-visibleSize.width, 0)));
		shoot5->runAction(MoveBy::create(2.0f, Vec2(visibleSize.width, visibleSize.height)));
		shoot6->runAction(MoveBy::create(2.0f, Vec2(visibleSize.width, -visibleSize.height)));
		shoot7->runAction(MoveBy::create(2.0f, Vec2(-visibleSize.width, -visibleSize.height)));
		shoot8->runAction(MoveBy::create(2.0f, Vec2(-visibleSize.width, visibleSize.height)));
	}
}

void GameSence::hitByMonster(float dt) {
	auto fac = Factory::getInstance();
	Sprite* collisionA = fac->colliderMonsterA(player->getBoundingBox());
	Sprite* collisionB = fac->colliderMonsterB(player->getBoundingBox());
	if ((collisionA != NULL || collisionB != NULL) && sword == NULL) {

		_eventDispatcher->removeAllEventListeners();
		unschedule(schedule_selector(GameSence::update));
		unschedule(schedule_selector(GameSence::updateCustom));
		unschedule(schedule_selector(GameSence::hitByMonster));
		unschedule(schedule_selector(GameSence::hitByBuff));
		Director::getInstance()->getOpenGLView()->setCursorVisible(true);
		auto over = Sprite::create("over.png");
		auto fadein = FadeIn::create(1.5f);
		over->runAction(fadein);
		over->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);
		addChild(over, 1);
		SimpleAudioEngine::getInstance()->playEffect("music/gameover.mp3", false);

		sqlite3* pdb = NULL;
		std::string path = FileUtils::getInstance()->getWritablePath() + "save.db";
		int result = sqlite3_open(path.c_str(), &pdb);
		CCString* na = CCString::createWithFormat("%d", killnum);
		string sql = "insert into rank values(" + na->_string + "," + na->_string + ");";
		result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
		//Todo 返回键d
		//auto backItem = MenuItemImage::create();
		auto backItem = MenuItemImage::create("back-1.png", "back-2.png", CC_CALLBACK_1(GameSence::backMenuCallback, this));
		backItem->setPosition(1350, 50);
		auto menu = Menu::create(backItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 1);
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	}
}

void GameSence::hitByBuff(float dt) {
	auto fac = Factory::getInstance();
	//monster hitted by sword
	if (sword != NULL) {
		Sprite* collisionAofSword = fac->colliderMonsterA(sword->getBoundingBox());
		Sprite* collisionBofSword = fac->colliderMonsterB(sword->getBoundingBox());
		if (collisionAofSword != NULL) {
			killnum++;
			fac->removeMonsterA(collisionAofSword);
			SimpleAudioEngine::getInstance()->playEffect("music/score.mp3", false);
		}
		else if (collisionBofSword != NULL) {
			killnum++;
			fac->removeMonsterB(collisionBofSword);
			SimpleAudioEngine::getInstance()->playEffect("music/score.mp3", false);
		}
	}
	
	//monster hitted by boom
	if (boom != NULL && btime < 295) {
		Sprite* collisionAofBoom = fac->colliderMonsterA(boom->getBoundingBox());
		Sprite* collisionBofBoom = fac->colliderMonsterB(boom->getBoundingBox());
		if (collisionAofBoom != NULL) {
			killnum++;
			fac->removeMonsterA(collisionAofBoom);
			SimpleAudioEngine::getInstance()->playEffect("music/score.mp3", false);
		}
		else if (collisionBofBoom != NULL) {
			killnum++;
			fac->removeMonsterB(collisionBofBoom);
			SimpleAudioEngine::getInstance()->playEffect("music/score.mp3", false);
		}
	}

	//monster hitted by shoot
	Vector<Sprite*> shoot;
	if (shoot1 != NULL) {
		shoot.pushBack(shoot1);
		shoot.pushBack(shoot2);
		shoot.pushBack(shoot3);
		shoot.pushBack(shoot4);
		shoot.pushBack(shoot5);
		shoot.pushBack(shoot6);
		shoot.pushBack(shoot7);
		shoot.pushBack(shoot8);
	}
	for (int i = 0; i < shoot.size(); i++) {
		Sprite* collisionAofShoot = fac->colliderMonsterA(shoot.at(i)->getBoundingBox());
		Sprite* collisionBofShoot = fac->colliderMonsterB(shoot.at(i)->getBoundingBox());
		if (collisionAofShoot != NULL) {
			killnum++;
			fac->removeMonsterA(collisionAofShoot);
			SimpleAudioEngine::getInstance()->playEffect("music/score.mp3", false);
		}
		else if (collisionBofShoot != NULL) {
			killnum++;
			fac->removeMonsterB(collisionBofShoot);
			SimpleAudioEngine::getInstance()->playEffect("music/score.mp3", false);
		}
	}
	CCString* na = CCString::createWithFormat("%d", killnum);
	labelscore->setString(na->_string);
	
}

void GameSence::preloadMusic() {
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("music/bgm.mp3");
	audio->preloadEffect("music/gameover.mp3");
	audio->preloadEffect("music/bullet.wav");
	audio->preloadEffect("music/bomb.wav");
	audio->preloadEffect("music/sword.wav");
	audio->preloadEffect("music/score.mp3");
}

void GameSence::playBgm() {
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("music/bgm.mp3", true);
}

void GameSence::backMenuCallback(Ref* pSender) {
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(menuscene);
}