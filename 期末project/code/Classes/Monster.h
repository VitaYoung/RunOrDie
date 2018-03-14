#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Factory :public cocos2d::Ref {
public:
	//��ȡ��������
	static Factory* getInstance();
	//����һ��������洢�������й���
	Sprite* createMonster1();
	Sprite* createMonster2();

	//�������е�����MonsterA������ɫ�ƶ���MonsterB������ƶ�
	void moveMonster1(Vec2 playerPos, float time);
	void moveMonster2(Vec2 Pos, float time);
	//�Ƴ�����
	//void removeMonster(Sprite*);
	void removeMonsterA(Sprite*);
	void removeMonsterB(Sprite*);
	//�ж���ײmonster
	Sprite* colliderMonsterA(Rect rect);
	Sprite* colliderMonsterB(Rect rect);

	//�ж���ײbuff
	Sprite* colliderBuffW(Rect rect);
	Sprite* colliderBuffS(Rect rect);
	Sprite* colliderBuffB(Rect rect);
	//����һ��buff�����洢�������й���
	Sprite* createBuff();
	//�������е�����buff������ƶ�
	void moveBuff(float time);
	//�Ƴ�buff
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