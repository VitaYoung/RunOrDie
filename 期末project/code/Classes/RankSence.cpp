#include"RankSence.h"
#include"Monster.h"
#include"MenuScene.h"
#include <algorithm>
#include"SimpleAudioEngine.h"
#include"sqlite3.h"
#pragma comment(lib, "sqlite3.lib") 

USING_NS_CC;
template <typename T> std::string tostr(const T& t) { std::ostringstream os; os << t; return os.str(); }
using namespace CocosDenshion;

Scene* RankSence::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	//ccColor4B color = ccc4(238, 255, 255, 255);
	auto *layer = RankSence::create();

	//layer ->setColor(ccc3(255, 182, 193));

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool RankSence::init() {
	if (!Layer::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto flower1 = Sprite::create("flower1.png");
	auto fadeout1 = Spawn::create(FadeOut::create(2.0f), ScaleBy::create(2.0f, 0.5f), RotateBy::create(2.0f, 180.0f), nullptr);
	auto fadein1 = Spawn::create(FadeIn::create(1.0f), ScaleBy::create(1.0f, 2.0f), RotateBy::create(1.0f, -180.0f), nullptr);
	auto squ1 = Sequence::createWithTwoActions(fadeout1, fadein1);
	flower1->runAction(RepeatForever::create(squ1));
	flower1->setPosition(200, 700);
	this->addChild(flower1, 0);

	auto flower2 = Sprite::create("flower2-75%.png");
	auto fadeout2 = Spawn::createWithTwoActions(FadeOut::create(5.0f), ScaleBy::create(5.0f, 0.2f));
	auto fadein2 = Spawn::createWithTwoActions(FadeIn::create(3.0f), ScaleBy::create(3.0f, 5.0f));
	auto squ2 = Sequence::createWithTwoActions(fadeout2, fadein2);
	flower2->runAction(RepeatForever::create(squ2));
	flower2->setPosition(1100, 170);
	this->addChild(flower2, 0);

	auto flower3 = Sprite::create("flower3.png");
	flower3->runAction(RepeatForever::create(RotateBy::create(20.0f, 360.0f)));
	flower3->setPosition(1250, 800);
	this->addChild(flower3, 0);

	auto flower4 = Sprite::create("flower3.png");
	flower4->runAction(RepeatForever::create(RotateBy::create(20.0f, -360.0f)));
	flower4->setPosition(200, -50);
	this->addChild(flower4, 0);

	auto backItem = MenuItemImage::create("back-1.png", "back-2.png", CC_CALLBACK_1(RankSence::backMenuCallback, this));
	backItem->setPosition(1350, 50);
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	one = Sprite::create("one.png");
	one->setPosition(visibleSize.width / 4, visibleSize.height * 5 / 6);
	one->setScale(0.3, 0.3);
	addChild(one, 1);

	labelone = Label::createWithTTF("100", "fonts/txjz.ttf", 200);
	labelone->setPosition(visibleSize.width  / 2, visibleSize.height * 5 / 6);
	labelone->setColor(ccc3(0, 0, 0));
	this->addChild(labelone, 1);

	two = Sprite::create("two.png");
	two->setPosition(visibleSize.width / 3, visibleSize.height  / 2 + 100);
	two->setScale(0.2, 0.2);
	addChild(two, 1);

	labeltwo = Label::createWithTTF("80", "fonts/txjz.ttf", 150);
	labeltwo->setPosition(visibleSize.width  / 2 + 100, visibleSize.height  / 2 + 100);
	labeltwo->setColor(ccc3(0, 0, 0));
	this->addChild(labeltwo, 1);

	three = Sprite::create("three.png");
	three->setPosition(visibleSize.width / 2 - 120, visibleSize.height  /  2 - 50);
	three->setScale(0.15, 0.15);
	addChild(three, 1);

	labelthree = Label::createWithTTF("100", "fonts/txjz.ttf", 100);
	labelthree->setPosition(visibleSize.width / 2 + 160, visibleSize.height / 2 - 50);
	labelthree->setColor(ccc3(0, 0, 0));
	this->addChild(labelthree, 1);


	labelfour = Label::createWithTTF("100", "fonts/txjz.ttf", 80);
	labelfour->setPosition(visibleSize.width / 2 + 80, visibleSize.height / 2 - 150);
	labelfour->setColor(ccc3(0, 0, 0));
	this->addChild(labelfour, 1);
	
	labelfive = Label::createWithTTF("100", "fonts/txjz.ttf", 80);
	labelfive->setPosition(visibleSize.width / 2 + 100, visibleSize.height / 2 - 250);
	labelfive->setColor(ccc3(0, 0, 0));
	this->addChild(labelfive, 1);

	labelsix = Label::createWithTTF("100", "fonts/txjz.ttf", 80);
	labelsix->setPosition(visibleSize.width / 2 + 120, visibleSize.height / 2 - 350);
	labelsix->setColor(ccc3(0, 0, 0));
	this->addChild(labelsix, 1);

	sqlite3* pdb = NULL;

	string path = FileUtils::getInstance()->getWritablePath() + "save.db";
	int result = sqlite3_open(path.c_str(), &pdb);

	char **re;
	int row, col;

	std::string sql = "create table rank(ID int primary key not null, score int);";
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	sqlite3_get_table(pdb, "select * from rank", &re, &row, &col, NULL);
	int n[100];
	for (int i = 0; i < 100; i++) {
		n[i] = -1;
	}

	for (int i = 1; i <= row; i++) {
		n[i - 1] = std::atoi(re[i*col+1]);
	}
	int temp = 0;
	CCString* na;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row - 1 - i; j++) {
			if (n[j] < n[j + 1]) {
				temp = n[j + 1];
				n[j + 1] = n[j];
				n[j] = temp;
			}
		}
	}
	if (n[0] >= 0) {
		na = CCString::createWithFormat("%d", n[0]);
		labelone->setString(na->_string);
	}
	if (n[1] >= 0) {
		na = CCString::createWithFormat("%d", n[1]);
		labeltwo->setString(na->_string);
	}
	if (n[2] >= 0) {
		na = CCString::createWithFormat("%d", n[2]);
		labelthree->setString(na->_string);
	}
	
	if (n[3] >= 0) {
		na = CCString::createWithFormat("%d", n[3]);
		labelfour->setString("4     " + na->_string);
	}
	if (n[4] >= 0) {
		na = CCString::createWithFormat("%d", n[4]);
		labelfive->setString("5     " + na->_string);
	}
	if (n[5] >= 0) {
		na = CCString::createWithFormat("%d", n[5]);
		labelsix->setString("6     " + na->_string);
	}

	sqlite3_free_table(re);

}

void RankSence::backMenuCallback(Ref* pSender) {
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(menuscene);
}