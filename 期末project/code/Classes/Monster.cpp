#include"Monster.h"
USING_NS_CC;

Factory* Factory::factory = NULL;
Factory::Factory() {
}
Factory* Factory::getInstance() {
	if (factory == NULL) {
		factory = new Factory();
	}
	return factory;
}


Sprite* Factory::createMonster1() {
	//create buff
	Sprite* mons = Sprite::create("Monster.png");
	mons->setScale(0.05, 0.05);
	MonsterA.pushBack(mons);
	return mons;
}

Sprite* Factory::createMonster2() {
	//create buff
	Sprite* mons = Sprite::create("Monster.png");
	mons->setScale(0.05, 0.05);
	MonsterB.pushBack(mons);
	return mons;
}

void Factory::removeMonsterA(Sprite* sp) {
	Sequence* seq = Sequence::create(CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, sp)), NULL);
	sp->runAction(seq);
	MonsterA.eraseObject(sp);
}

void Factory::removeMonsterB(Sprite* sp) {
	Sequence* seq = Sequence::create(CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, sp)), NULL);
	sp->runAction(seq);
	MonsterB.eraseObject(sp);
}

void Factory::moveMonster1(Vec2 playerPos, float time) {
cocos2d:Vector<Sprite*>::iterator it = MonsterA.begin();
	for (; it != MonsterA.end();) {
		Vec2 monsterPos = (*it)->getPosition();
		Vec2 direction = playerPos - monsterPos;
		direction.normalize();
		(*it)->runAction(MoveBy::create(time, direction * 2));
		it++;
	}

}
void Factory::moveMonster2(Vec2 sPos, float time) {
cocos2d:Vector<Sprite*>::iterator it = MonsterB.begin();
	for (; it != MonsterB.end();) {
		Vec2 Pos;
		Pos.x = random(0, 1440);
		Pos.y = random(0, 800);
		Vec2 monsterPos = (*it)->getPosition();
		Vec2 direction = Pos - monsterPos;
		direction.normalize();
		(*it)->runAction(MoveBy::create(time, direction * 20));
		it++;
	}

}

Sprite* Factory::colliderMonsterA(Rect rect) {
	for (int i = 0; i < MonsterA.size(); i++) {
		auto monPos = MonsterA.at(i)->getPosition();
		if (rect.containsPoint(monPos)) return MonsterA.at(i);
	}
	return NULL;
}

Sprite* Factory::colliderMonsterB(Rect rect) {
	for (int i = 0; i < MonsterB.size(); i++) {
		auto monPos = MonsterB.at(i)->getPosition();
		if (rect.containsPoint(monPos)) return MonsterB.at(i);
	}
	return NULL;
}

Sprite* Factory::colliderBuffW(Rect rect) {
cocos2d:Vector<Sprite*>::iterator it = BuffW.begin();
	for (; it != BuffW.end();) {
		Vec2 BuffPos = (*it)->getPosition();
		if (rect.containsPoint(BuffPos)) {
			return (*it);
			break;
		}
		it++;
	}
}

Sprite* Factory::colliderBuffB(Rect rect) {
cocos2d:Vector<Sprite*>::iterator it = BuffB.begin();
	for (; it != BuffB.end();) {
		Vec2 BuffPos = (*it)->getPosition();
		if (rect.containsPoint(BuffPos)) {
			return (*it);
			break;
		}
		it++;
	}
}

Sprite* Factory::colliderBuffS(Rect rect) {
cocos2d:Vector<Sprite*>::iterator it = BuffS.begin();
	for (; it != BuffS.end();) {
		Vec2 BuffPos = (*it)->getPosition();
		if (rect.containsPoint(BuffPos)) {
			return (*it);
			break;
		}
		it++;
	}
}


Sprite* Factory::createBuff() {
	//create buff
	int r = random(0, 2);
	Sprite* buff;
	if (r == 0) {
		buff = Sprite::create("Sword.png");
		buff->setScale(0.065, 0.065);
		BuffW.pushBack(buff);
	}
	if (r == 1) {
		buff = Sprite::create("shoot.png");
		buff->setScale(0.065, 0.065);
		BuffS.pushBack(buff);
		
	}
	if (r == 2) {
		buff = Sprite::create("boom.png");
		buff->setScale(0.065, 0.065);
		BuffB.pushBack(buff);
	}
	return buff;
}

void Factory::moveBuff(float time) {
cocos2d:Vector<Sprite*>::iterator it = BuffS.begin();
	for (; it != BuffS.end();) {
		Vec2 Pos;
		Pos.x = random(0, 1440);
		Pos.y = random(0, 800);
		Vec2 buffPos = (*it)->getPosition();
		Vec2 direction = Pos - buffPos;
		direction.normalize();
		(*it)->runAction(MoveBy::create(time, direction * 80));
		it++;
	}
	it = BuffW.begin();
	for (; it != BuffW.end();) {
		Vec2 Pos;
		Pos.x = random(0, 1440);
		Pos.y = random(0, 800);
		Vec2 buffPos = (*it)->getPosition();
		Vec2 direction = Pos - buffPos;
		direction.normalize();
		(*it)->runAction(MoveBy::create(time, direction * 80));
		it++;
	}
	it = BuffB.begin();
	for (; it != BuffB.end();) {
		Vec2 Pos;
		Pos.x = random(0, 1440);
		Pos.y = random(0, 800);
		Vec2 buffPos = (*it)->getPosition();
		Vec2 direction = Pos - buffPos;
		direction.normalize();
		(*it)->runAction(MoveBy::create(time, direction * 80));
		it++;
	}

}
void Factory::removeBuffW(Sprite* sp) {
	Sequence* seq = Sequence::create(CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, sp)), NULL);
	sp->runAction(seq);
	BuffW.eraseObject(sp);
}

void Factory::removeBuffB(Sprite* sp) {
	Sequence* seq = Sequence::create(CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, sp)), NULL);
	sp->runAction(seq);
	BuffB.eraseObject(sp);
}

void Factory::removeBuffS(Sprite* sp) {
	Sequence* seq = Sequence::create(CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, sp)), NULL);
	sp->runAction(seq);
	BuffS.eraseObject(sp);
}