#ifndef __MEMBER_SCENE_H__
#define __MEMBER_SCENE_H__

#include "cocos2d.h"

class MemberScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback

	// ����Ϊ������4����ť�Ķ�Ӧ������������ʵ�����ҳ�����ת�Լ�����������Ч���仯

	void backMenuCallback(cocos2d::Ref* pSender);    //  ��������ء���ť�Ĵ�����������ʵ�֣�1����ת�������棻��2������仯�������ֵ��


	CREATE_FUNC(MemberScene);
};

#endif // __MEMBER_SCENE_H__

