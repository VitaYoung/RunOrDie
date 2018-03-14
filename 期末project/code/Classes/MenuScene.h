#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback

	// ����Ϊ������4����ť�Ķ�Ӧ������������ʵ�����ҳ�����ת�Լ�����������Ч���仯

    void startMenuCallback(cocos2d::Ref* pSender);    //  �������ʼ��Ϸ����ť�Ĵ�����������ʵ�֣�1����ת����Ϸҳ�棻��2������仯��ѡ��ǰ�С�player��ͼ��

	void descriptionMenuCallback(cocos2d::Ref* pSender);     //  �������Ϸ˵������ť�Ĵ�����������ʵ�֣�1����ת��˵��ҳ�棻��2������仯��ѡ��ǰ�С�player��ͼ��

	void rankMenuCallback(cocos2d::Ref* pSender);       //  ������÷����С���ť�Ĵ�����������ʵ�֣�1����ת�����а�ҳ�棻��2������仯��ѡ��ǰ�С�player��ͼ��

	void memberMenuCallback(cocos2d::Ref* pSender);       //  ����������Ŷӡ���ť�Ĵ�����������ʵ�֣�1����ת����Ա����ҳ�棻��2������仯��ѡ��ǰ�С�player��ͼ��
    
	cocos2d::MenuItemImage* startItem;

	cocos2d::MenuItemImage* descriptionItem;

	cocos2d::MenuItemImage* rankItem;

	cocos2d::MenuItemImage* teamItem;

	cocos2d::Sprite* logo1;

	cocos2d::Sprite* logo2;

	cocos2d::Sprite* logo3;

	cocos2d::Sprite* logo4;

	cocos2d::EventListenerMouse* event;

	void onMouseMove(cocos2d::Event* e);

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
