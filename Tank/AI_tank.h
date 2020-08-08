#pragma once
#include "tank_class.h"
#include <Windows.h>
#include <algorithm>
#include <string>
#include <vector>

using std::vector;
using std::string;

//A星节点
struct NODE
{
	int F;
	int H;//预估值
	int G;//代价值
	char node_side;//节点方向
	COORD node_pos;//节点位置
	NODE* father_node;//指向父节点
	NODE(int h, int g, int pos_x, int pos_y,
		NODE* father_NODE);//节点构造
	void change_side();//更改方向，用于在更改父节点时重算方向使用
};


class A_star {
	vector<NODE*> open_list;
	vector<NODE*> close_list;
	vector<NODE> line_list;
	//储存将返回出去的路径

	COORD start_pos;//通过构造给的开始位置
	COORD end_pos;//结束点
	
	static int find_time;//寻路频率
public:
	A_star(COORD Start_pos, COORD End_pos);
	//初始化
	void _init();

	//将周围四格加入open_list,加入时判断是否是墙壁，
	//或者是否已经在close_list内，是的话跳过。 
	//不是的话，判断是否已经在open_list内，
	//是的话判断G值是否比当前方格小，是的话将当前方格父类变为那个方格，
	//并且重新计算G值
	void add_open_list();

	//查找open_list中F值最小的，并返回下标
	int find_min_F();

	//将open_list中F最小的放入close_list中，并且从open_list删除
	bool move_to_close_list();

	//返回close_list的结尾
	NODE* close_list_last();

	//打印整个路径
	vector<NODE> pr_all_path();

	//获得储存的寻找频率
	static int& get_find_time();

};


class _AI_TANK : public _TANK
{
	//是否开火，随机决定的
	bool fire = false;
	//决定AI级别，级别决定开火频率和移动速度
	short level ;
	//保存的A星的数据
	vector<NODE> line_list;
	//记录路径的读取位置
	int line_count = 0;
	//查找频率
	time_t find_time = 0;
	//ai数量控制
	static int AI_count;
	//开火频率
	short fire_chance;
	//储存的速度，沙地减速时使用
	int speed_save;
	//外部设置默认速度
	static int TANK_SPEED;
public:
	//获得开火状态
	bool get_fire();
	//更改开火状态
	void change_fire(bool fire);
	//初始化AI状态
	void _init(int number, WORD ncolor);
	//自动移动，更改方向然后调用父类move
	void auto_move();
	//判断是否进入沙子
	bool did_go_sand();
	//计算路径
	void find_line(COORD player_tank_pos);
	//获取计算频率
	time_t& get_find_time();
	//获取AI数量控制
	static int& get_ai_count();
};