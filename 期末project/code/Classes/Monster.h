#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Factory :public cocos2d::Ref {
public:
	//获取单例工厂
	static Factory* getInstance();
	//生成一个怪物，并存储到容器中管理
	Sprite* createMonster1();
	Sprite* createMonster2();

	//让容器中的所有MonsterA都往角色移动，MonsterB都随机移动
	void moveMonster1(Vec2 playerPos, float time);
	void moveMonster2(Vec2 Pos, float time);
	//移除怪物
	//void removeMonster(Sprite*);
	void removeMonsterA(Sprite*);
	void removeMonsterB(Sprite*);
	//判断碰撞monster
	Sprite* colliderMonsterA(Rect rect);
	Sprite* colliderMonsterB(Rect rect);

	//判断碰撞buff
	Sprite* colliderBuffW(Rect rect);
	Sprite* colliderBuffS(Rect rect);
	Sprite* colliderBuffB(Rect rect);
	//生成一个buff，并存储到容器中管理
	Sprite* createBuff();
	//让容器中的所有buff都随机移动
	void moveBuff(float time);
	//移除buff
	void removeBuffW(Sprite*);
	void removeBuffS(Sprite*);
	void removeBuffB(Sprite*);

private:
	Factory();
	Vector<Sprite*> MonsterA;
	Vector<Sprite*> MonsterB;
	Vector<Sprite*> BuffW;
	Vector<Sprite*> BuffB;
	Vector<Sprite*> BuffS;
	static Factory* factory;
};