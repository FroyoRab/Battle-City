#pragma once
#pragma once
#include <string>
#include <windows.h>
#include <iostream>
using namespace std;

class MENU {
private:
	int out_choose = 1;//外列表选择
	int in_choose = 1;//内部列表选择
	int* list = &out_choose;//用于切换控制选择值
	int pos[7][8] = { {}, {0,24,26,28,30,32,34},{0,26,28,30,32,34,36},{0,28},{0,30},{0,32},{0,34} };
	string out_list[7] = {//外部列表
		{" 坦克大战" },
		{"①单人游戏"},
		{"②双人游戏"},
		{"③编辑地图"},
		{"④游戏设置"},
		{"⑤读取存档"},
		{"⑥退出游戏"}
	};
	string in_list[7][7] = {//内部列表
	{},
	{{}, {"①LEVEL1"},{"②LEVEL2"},{"③LEVEL3"},
	{"④LEVEL4"},{"⑤LEVEL5"},{"⑥自定义地图"}
	},
	{{},{"①LEVEL1"},{"②LEVEL2"},{"③LEVEL3"},
	{"④LEVEL4"},{"⑤LEVEL5"},{"⑥自定义地图"}
	},
	{{},{"编辑自定义关卡地图"}},
	{{},{"可以设置坦克默认速度，AI寻路频率等"}},
	{{},{"读取存档，并直接开始游戏"}},
	{{},{"回车键退出游戏！"}},
	};
public:
	//清空右侧
	void clear_right();

	//判断按键
	void key_press();

	//更改列表
	void change_list();

	//无底色打印全部菜单
	void pr_menu();

	//打印被选择菜单
	void pr_choose(int choose = 1, bool bool_in = true);

	//返回选择菜单的内外列表值
	void get_choose(int& _out_choose, int& _out_choose2);

};