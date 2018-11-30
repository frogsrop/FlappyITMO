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

#ifndef __FIRST_SCENE_H__
#define __FIRST_SCENE_H__

#include "cocos2d.h"

class FirstScene : public cocos2d::Scene
{
private:
	class wall;
	bool started = false;
	float radius;
	wall* cur_wall;
	cocos2d::Label* lb;
	float eps = 10;
	static int points;
	float visible_damage_pcnt = 0.1;
	float o_x;
	float o_y;

	static cocos2d::Size visible_size;
	static cocos2d::Vec2 origin;
	static std::string face;

	float left_border;
	float up_border;
	float down_border;
	cocos2d::Sprite* bird;
	cocos2d::DrawNode* nd;

	float get_d(float a, float b, float c);
	float dist(cocos2d::Vec2, cocos2d::Vec2);
	void check_death();
	void death();

public:
	static cocos2d::Scene* createScene();

	static void setFace(std::string s);

	static int get_points();

	virtual bool init();

	void onButtonClick();

	bool onTouchBegan(cocos2d::Touch* tch, cocos2d::Event* ev);

	CREATE_FUNC(FirstScene);

	virtual void update(float);
};

#endif // __FIRST_SCENE_H__
