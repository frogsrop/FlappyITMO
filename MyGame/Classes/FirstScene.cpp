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

#include "FirstScene.h"
#include "HelloScreen.h"

USING_NS_CC;


Scene* FirstScene::createScene()
{
	return FirstScene::create();
}

std::string FirstScene::face;

void FirstScene::setFace(std::string s)
{
	face = s;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
}


class FirstScene::wall : public Node
{
private:
	Sprite* down_wall;
	Sprite* up_wall;
	float width_scale = 0.45;
	float offset = 0;
	float distance_part = 1.0f / 3;
	float distance;
	float not_delta_part = 1.0f / 3;

	Sprite* make_wall(float y_offset)
	{
		Sprite* temp_wall;
		temp_wall = Sprite::create("Wall.png");
		if (temp_wall == nullptr)
		{
			problemLoading("'fonts/Marker Felt.ttf'");
		}
		else
		{
			temp_wall->setRotation(90);
			const auto scaling = visible_size.height / temp_wall->getContentSize().width;
			temp_wall->setScale(scaling, visible_size.width / temp_wall->getContentSize().height * 0.08);

			auto pos = origin;
			pos.x += visible_size.width;
			pos.y += y_offset;
			temp_wall->setPosition(pos);
			this->Node::addChild(temp_wall);
		}
		return temp_wall;
	}

	void move_y(float val)
	{
		float move_val = val - (up_wall->getPosition().y + down_wall->getPosition().y) / 2;
		up_wall->setPositionY(up_wall->getPositionY() + move_val);
		down_wall->setPositionY(down_wall->getPositionY() + move_val);
	}

public:

	using Node::addChild;

	virtual bool init()
	{
		distance = visible_size.height * distance_part;
		//building walls
		down_wall = make_wall(0 - distance / 2);
		up_wall = make_wall(visible_size.height + distance / 2);
		//adding offset
		float not_delta_dist = visible_size.height * not_delta_part;
		float up_delta = origin.y + visible_size.height - not_delta_dist;
		float down_delta = origin.y + not_delta_dist;

		offset = rand() % int(up_delta - down_delta) + int(down_delta);

		move_y(offset);
		return true;
	}

	static wall* create()
	{
		wall* ret = new(std::nothrow) wall();
		if (ret && ret->init())
		{
			ret->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(ret);
		}

		return ret;
	}

	void move(float sp) const
	{
		down_wall->setPosition(Vec2(down_wall->getPosition().x + sp, down_wall->getPosition().y));
		up_wall->setPosition(Vec2(up_wall->getPosition().x + sp, up_wall->getPosition().y));
	}

	float get_x() const
	{
		return down_wall->getPosition().x - down_wall->getContentSize().height * down_wall->getScaleY() / 2;
	}

	float get_mid() const
	{
		return (down_wall->getPosition().y + up_wall->getPosition().y) / 2;
	}

	Vec2 get_bottom() const
	{
		auto pos = down_wall->getPosition();
		pos.y += down_wall->getContentSize().width / 2 * down_wall->getScaleX();
		//nd->drawDot(pos, 5, Color4F::RED);
		return pos;
	}

	Vec2 get_up() const
	{
		auto pos = up_wall->getPosition();
		pos.y -= up_wall->getContentSize().width / 2 * up_wall->getScaleX();
		//nd->drawDot(pos, 5, Color4F::GREEN);
		return pos;
	}

	Vec2 get_left() const
	{
		auto pos = up_wall->getPosition();
		pos.x -= up_wall->getContentSize().height / 2 * up_wall->getScaleY();
		return pos;
	}

	Vec2 get_right() const
	{
		auto pos = up_wall->getPosition();
		pos.x += up_wall->getContentSize().height / 2 * up_wall->getScaleY();
		return pos;
	}
};

/*
void out(float x)
{
	log(std::to_string(x).c_str());
}
*/

float FirstScene::get_d(float a, float b, float c)
{
	return b * b - 4 * (a * c);
}

int FirstScene::get_points()
{
	return points;
}

int FirstScene::points = 0;

Size FirstScene::visible_size;
Vec2 FirstScene::origin;

bool FirstScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visible_size = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	this->scheduleUpdate();
	srand(time(nullptr));
	nd = DrawNode::create();
	this->Node::addChild(nd);

	lb = Label::create();
	if (lb == nullptr)
	{
		problemLoading("'Label'");
	}
	else
	{
		auto pos = origin;
		pos.y += visible_size.height * 0.8;
		pos.x += visible_size.width / 2;
		lb->setPosition(pos);

		//lb->setScale(10);
		lb->setSystemFontSize(100);
		lb->setColor(Color3B::BLACK);
		points = 0;
		lb->setString(std::to_string(points));
	}
	this->addChild(lb, 3);

	Sprite* itmo = Sprite::create("clouds.png");

	if (itmo == nullptr)
	{
		problemLoading("'Clouds'");
	}
	else
	{
		auto pos = origin + visible_size / 2;
		itmo->setPosition(pos);
		float scaleX = visible_size.width / itmo->getContentSize().width;
		float scaleY = visible_size.height / itmo->getContentSize().height;
		itmo->setScale(scaleX, scaleY);
		this->addChild(itmo, 0);
	}
	if (face.empty())
	{
		face = "StaFace.png";
	}
	bird = Sprite::create(face);
	if (bird == nullptr)
	{
		problemLoading("'Face'");
	}
	else
	{
		auto pos = origin;
		pos += visible_size / 2;
		pos -= visible_size / 3;
		bird->setPosition(pos);
		auto scaleX = visible_size.height / bird->getContentSize().height * 0.1;
		auto scaleY = visible_size.height / bird->getContentSize().height * 0.1;
		bird->setScale(scaleX, scaleY);
		this->addChild(bird, 1);
	}
	//cur_wall.reset(new wall(this));
	cur_wall = wall::create();
	this->Node::addChild(cur_wall);
	radius = bird->getContentSize().width * bird->getScaleX() / 2.0f - bird->getContentSize().width * bird->getScaleX()
		* visible_damage_pcnt;
	//nd->drawCircle(bird->getPosition(), radius, 360, 100, 0, Color4F::RED);
	auto touch_listener = EventListenerTouchOneByOne::create();
	touch_listener->onTouchBegan = CC_CALLBACK_2(FirstScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);
	left_border = Director::getInstance()->getVisibleOrigin().x;
	up_border = Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height;
	down_border = Director::getInstance()->getVisibleOrigin().y;

	o_x = bird->getPosition().x;
	o_y = bird->getPosition().y;

	return true;
}

float g = -9.81f * 3;
float bird_cur_speed = 0;
float wall_speed = -500;
float jump = 13;

float FirstScene::dist(Vec2 a, Vec2 b)
{
	return (a.y - b.y) * (a.y - b.y) + (a.x - b.x) * (a.x - b.x);
}

void FirstScene::death()
{
	//points = 0;
	auto scene = HelloScreen::createScene();
	Director::getInstance()->replaceScene(scene);
	started = false;
}

void FirstScene::check_death()
{
	float gx = cur_wall->get_x();
	float gu = cur_wall->get_up().y;
	float gb = cur_wall->get_bottom().y;
	float d_y =
		get_d(1, 2 * o_y, o_y * o_y - radius * radius + (gx - o_x) * (gx - o_x));
	float d_x_1 =
		get_d(1, 2 * o_x, o_x * o_x - radius * radius + (gu - o_y) * (gu - o_y));
	float d_x_2 =
		get_d(1, 2 * o_x, o_x * o_x - radius * radius + (gb - o_y) * (gb - o_y));

	if (d_y >= 0 && (o_y - radius < gb || o_y + radius > gu))
	{
		death();
	}

	float gl = cur_wall->get_left().x;
	float gr = cur_wall->get_right().x;

	if (d_x_1 >= 0 &&
		(o_x + radius > gl && o_x + radius < gr ||
			o_x - radius > gl && o_x - radius < gr ||
			o_x - radius < gl && o_x + radius > gr)
	)
	{
		death();
	}
	if (d_x_2 >= 0 &&
		(o_x + radius > gl && o_x + radius < gr ||
			o_x - radius > gl && o_x - radius < gr ||
			o_x - radius < gl && o_x + radius > gr)
	)
	{
		death();
	}

	if (o_y + 100 < down_border ||
		o_y - 100 > up_border)
	{
		death();
	}
}

void FirstScene::update(const float dt)
{
	check_death();

	//bird ops

	if (!started) return;

	bird_cur_speed += g * dt;
	o_y += bird_cur_speed;
	bird->setPosition(Vec2(o_x, o_y));
	//wall ops
	cur_wall->move(wall_speed * dt);
	//collision check
	if (cur_wall->get_x() + 100 < left_border)
	{
		points++;
		lb->setString(std::to_string(points));
		this->removeChild(cur_wall);
		cur_wall = wall::create();
		this->Node::addChild(cur_wall);
	}
}


bool FirstScene::onTouchBegan(Touch* tch, Event* ev)
{
	started = true;
	bird_cur_speed = jump;
	return true;
}
