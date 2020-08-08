#pragma once
#include <Windows.h>

class _MOVE_OBJ
{
protected:
	WORD color;			//颜色
	COORD center_pos;	//中心坐标
	char side;			//方向
	bool die;			//是否需要死亡
	bool died;			//是否已经死亡
	int speed;			//移动速度
public:
	//向 side 方向移动一格
	virtual void move() = 0;
	
	//用color颜色打印对象
	virtual void show() = 0;

	//擦除打印的对象
	virtual void clear() = 0;

	//去死
	virtual void go_die() = 0;

	//获取死否死亡
	virtual bool get_died();

	//获取中心坐标
	virtual COORD get_center_pos();

	//判断坐标是否在对象内部
	virtual bool did_in_obj(COORD xy) = 0;

	//获取对象移动速度
	virtual int get_speed();
	
	//更改对象移动速度
	virtual void change_speed(int num);

	//获取方向
	virtual int get_side();

	//获取颜色
	virtual int get_color();
};