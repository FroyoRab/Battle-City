#pragma once
#include "move_obj.h"
#include<Windows.h>
#include<vector>

class _TANK:public _MOVE_OBJ
{
protected:
	bool side_change = false;
	short player = 0;
	static int TANK_PLAYER_SPEED;
public:
	//更改坦克方向
	void change_side(int nside);
	//向 side 方向移动一格
	void move();
	//用color颜色打印对象
	void show();
	//擦除打印的对象
	void clear();
	//初始化对象
	void _init(WORD ncolor, COORD born_pos,short splayer);
	//去死
	void go_die();
	//判断坐标是否在对象内部
	bool did_in_obj(COORD xy);
	//判断是否撞墙
	bool did_go_wall(char side);
	//判断是否在草地
	bool did_go_grass();
	//判断是否在沙地
	bool did_go_sand();
	//获得玩家
	short get_player();
	//是否撞上其他坦克
	bool did_go_other_tank(int x ,int y);
	//更改默认速度
	static int& get_save_speed();

};

//子弹类
class _BULLET :public _MOVE_OBJ
{
	//敌我区分
	bool friends = true;
	//ID储存
	int bullet_numbers;
public:
	//初始化，传入发射坦克的坐标，方向，颜色，和敌我
	void _init(COORD fire_tank,int nside,WORD ncolor=0xf0,bool bfriends=true);
	//移动
	void move();
	//打印
	void show();
	//擦除
	void clear();
	//去死
	void go_die();
	//判断坐标是否重合
	bool did_in_obj(COORD xy);
	//获取敌我状态
	bool get_friends();
	//地否撞到其他子弹
	bool did_go_other_bullet();
	//获得ID
	int& get_id();
};
