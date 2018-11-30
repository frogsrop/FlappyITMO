#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"

class SettingsScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void onStaClick();
	void onDimasClick();
	//void onRijkovClick();
	// implement the "static create()" method manually
	CREATE_FUNC(SettingsScene);
};

#endif // __SETTINGS_SCENE_H__
