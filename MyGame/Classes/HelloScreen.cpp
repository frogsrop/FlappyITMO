/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloScreen.h"
#include "ui/UIButton.h"
#include "FirstScene.h"
#include "SettingsScene.h"
USING_NS_CC;

int HelloScreen::local_points;

Scene* HelloScreen::createScene()
{
	return HelloScreen::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf(
		"Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloScreen::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	auto visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//close button
	auto closeItem = ui::Button::create(
		"CloseNormal.png",
		"CloseSelected.png");

	if (closeItem == nullptr)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float size = visible_size.height / closeItem->getContentSize().height * 0.1;
		closeItem->setScale(size, size);
		float x = origin.x + visible_size.width - closeItem->getContentSize().width * closeItem->getScaleX() / 2;
		float y = origin.y + closeItem->getContentSize().height * closeItem->getScaleY() / 2;
		closeItem->setPosition(Vec2(x, y));
		closeItem->addTouchEventListener(CC_CALLBACK_1(HelloScreen::menuCloseCallback, this));
		this->addChild(closeItem, 0);
	}
	//settings button
	auto settingsItem = ui::Button::create("Options.png");

	if (settingsItem == nullptr)
	{
		problemLoading("'Options.png'");
	}
	else
	{
		float size = visible_size.height / settingsItem->getContentSize().height * 0.1;
		settingsItem->setScale(size, size);
		float x = settingsItem->getContentSize().width * settingsItem->getScaleX() / 2;
		float y = origin.y + settingsItem->getContentSize().height * settingsItem->getScaleY() / 2;
		settingsItem->setPosition(Vec2(x, y));
		settingsItem->addTouchEventListener(CC_CALLBACK_0(HelloScreen::onSettingsClick, this));
		this->addChild(settingsItem, 0);
	}

	//first level button
	auto firstLevel = ui::Button::create("StartButton.png");
	if (firstLevel == nullptr)
	{
		problemLoading("'StartButton.png'");
	}
	else
	{
		auto pos = origin;
		pos += visible_size / 2;
		firstLevel->setPosition(pos);
		firstLevel->setSize(Size(50, 50));
		firstLevel->addTouchEventListener(CC_CALLBACK_0(HelloScreen::onButtonClick, this));
		this->addChild(firstLevel, 1);
	}

	Label* lb = Label::create();
	if (lb == nullptr)
	{
		problemLoading("Label");
	}
	else
	{
		auto pos = origin;
		pos.y += visible_size.height * 0.8;
		pos.x += visible_size.width / 2;
		lb->setPosition(pos);
		//lb->setScale(10);
		lb->setSystemFontSize(100);
		lb->setColor(Color3B::WHITE);
		local_points = UserDefault::getInstance()->getIntegerForKey("best_score");
		local_points = std::max(local_points, FirstScene::get_points());
		UserDefault::getInstance()->setIntegerForKey("best_score", local_points);
		UserDefault::getInstance()->flush();
		lb->setString("Your best score: " + std::to_string(local_points));
	}
	this->addChild(lb, 3);
	return true;
}


void HelloScreen::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void HelloScreen::onButtonClick()
{
	auto scene = FirstScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void HelloScreen::onSettingsClick()
{
	auto scene = SettingsScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
