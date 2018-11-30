#include "SettingsScene.h"
#include "ui/UIButton.h"
#include "FirstScene.h"
#include "HelloScreen.h"

USING_NS_CC;

Scene* SettingsScene::createScene()
{
	return SettingsScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
}

bool SettingsScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	auto visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto staButton = ui::Button::create("StaFace.png");

	if (staButton == nullptr)
	{
		problemLoading("'StaFace.png'");
	}
	else
	{
		float size = visible_size.height / staButton->getContentSize().height * 0.2;
		staButton->setScale(size, size);
		float x = origin.x + visible_size.width/ 4;
		float y = origin.y + visible_size.height/2;
		staButton->setPosition(Vec2(x, y));
		staButton->addTouchEventListener(CC_CALLBACK_0(SettingsScene::onStaClick, this));
		this->addChild(staButton, 0);
	}

	auto dimasButton = ui::Button::create("KekFace.png");

	if (dimasButton == nullptr)
	{
		problemLoading("'KekFace.png'");
	}
	else
	{
		float size = visible_size.height / dimasButton->getContentSize().height * 0.2;
		dimasButton->setScale(size, size);
		float x = origin.x + 2 * visible_size.width / 4;
		float y = origin.y + visible_size.height / 2;
		dimasButton->setPosition(Vec2(x, y));
		dimasButton->addTouchEventListener(CC_CALLBACK_0(SettingsScene::onDimasClick, this));
		this->addChild(dimasButton, 0);
	}
	return true;
}

void SettingsScene::onStaClick()
{
	FirstScene::setFace("StaFace.png");
	auto scene = HelloScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}

void SettingsScene::onDimasClick()
{
	FirstScene::setFace("KekFace.png");
	auto scene = HelloScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}
