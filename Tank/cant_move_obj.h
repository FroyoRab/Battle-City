#pragma once
#include <Windows.h>

class _MAP
{
protected:
	//WORD color;
	char c_map[61][81] = {0};
	int player_score = 0;
public:
	static int map_count;
	//判断XY是否是墙
	bool did_in_obj(int x, int y, char ICO);
	
	//从文件加载地图
	void get_map_in_file(int select);
	
	//打印地图
	void print_map();

	//保存地图
	void save_map();

	//重置地图
	void init_map();

	//删除地形
	void clear_one(int x,int y,char side);

	//编辑地图
	void edit_map();

	//编辑地图鼠标事件处理
	void mouse_event_proc(MOUSE_EVENT_RECORD mouse_e);

	//边框控制
	void add_box();

	//获取玩家分数
	int& get_score();

	void change_map(COORD pos , char ico);
};

