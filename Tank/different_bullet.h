#pragma once
#include <Windows.h>
#include <vector>
#include <string>

#define LASER_BALL "●"
#define LASER_BALL_COLOR 0xf1
#define LASER_ICO_UP "|"
#define LASER_ICO_LEFT "=="
#define LASER_COLOR 0xbf

using std::vector;
using std::string;

struct temp_save_map {
	temp_save_map(COORD poss, char land, DWORD ncolor=0xf0)
		:pos(poss), land_ico(land), color(ncolor) {}
	COORD pos;
	char land_ico;
	DWORD color;
};

class _DIFFERENT_BULLET {
protected:
	//更改地形,并且保存更改后的地形
	virtual void change_map() = 0;

	//打印
	virtual void show() = 0;

	//确认是否物体在内，并直接处理，并且确认时间
	virtual bool sure() = 0;

	//清除
	virtual void clear() = 0;

};

class LASER :public _DIFFERENT_BULLET{
	COORD center;//中心坐标
	int nside;//方向
	vector<temp_save_map> land_save;//用于储存被激光照射的地形
	int vanish_time;//消失时间
	int level = 1;//级别
public:
	LASER(COORD fire_tank, int side);
	//更改地形,并且保存更改后的地形
	void change_map();
	//打印
	void show();
	//确认是否物体在内，并直接处理，并且确认时间
	bool sure();
	//清除
	void clear();
protected:
	void _change_map(COORD pos);
};