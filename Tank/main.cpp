#include "func.h"
#include "tank_class.h"
#include "cant_move_obj.h"
#include "AI_tank.h"
#include "menu_class.h"
#include <windows.h>
#pragma comment(lib,"winmm.lib")
using std::string;
using std::vector;
/////////////////////////////////////////
//AI坦克数组
vector<_AI_TANK> tank_list;
vector<_TANK> tank_list_firends;


//子弹对象数组
vector<_BULLET> bullet_list;

//地图对象
_MAP tank_map;
MUSIC music;

//移动大循环的退出控制
bool do_while = true;

//AI最高数量
int _AI_TANK::AI_count = 6;
//光卡计数
int _MAP::map_count = 1;
//坦克速度
int _TANK::TANK_PLAYER_SPEED = 70;
int _AI_TANK::TANK_SPEED = 100;
//A星计算频率
int A_star::find_time = 1000;

////////////////////////////////////////


int main() {
	while (1) {
		//初始化，包含了窗口大小控制，光标隐藏数组清空等
		_init();

		//菜单
		start_form();
		
		//开始
		start();

		system("cls");
	}
}

void start() {
	system("cls");
	tank_map.get_score() = 0;
	//分数清零，因为初始化函数在过关的时候也会调用，所以放在这里
	
	MENU menu;
	tank_map.add_box();
	menu.key_press();
	int menu_choose;
	menu.get_choose(menu_choose, _MAP::map_count);
	//菜单和接收
	
	COORD START1 = { 21,55 };
	COORD START2 = { 38,55 };
	//两辆我方坦克出生点

	while (true)
	{
		_init();
		switch (menu_choose)//根据菜单返回值来决定选择
		{
		case 1:
		case '1': {
			tank_map.get_map_in_file(_MAP::map_count);
			_TANK tank1;
			tank_list_firends.push_back(tank1);
			tank_list_firends[0]._init(0xf5, START1, 0);
			//单人初始化，进移动的大循环👇
			all_move();
			//在我方坦克死亡和地方死光时会通过
			//do_while=false和map_count=0来选择过关还是退出到菜单
			break;
		}
		case 2:
		case '2': {
			tank_map.get_map_in_file(_MAP::map_count);
			for (int i = 0; i < 2; i++)
			{
				//坦克对象
				_TANK tank1;
				tank_list_firends.push_back(tank1);
			}
			//与单人一样，只是同时生成两个我方坦克。
			tank_list_firends[0]._init(0xf5, START1, 0);
			tank_list_firends[1]._init(0xf4, START2, 1);
			all_move();
			break;
		}
		case 3:
		case '3': {
			//编辑地图
			tank_map.edit_map();
			_MAP::map_count = 0;//退出到选择
			break;
		}
		case 4:
		case '4': {
			setting(); 
			//游戏设置
			_MAP::map_count = 0;
			break;
		}
		case 5:
		case '5': {
			if (load_save()) {//没存档会返回false
				menu_choose = tank_list_firends.size();
				//根据存档的单人双人来选择单人双人。
				all_move();
			}//如果没有存档👇
			else _MAP::map_count = 0;
			break;
		}
		case 6:exit(0);//退出游戏
		}
		if (_MAP::map_count == 0)
			break;//退出至菜单选择
	}

}

void pr_rightline(int choise, int map_count, int ai_num)
{
	//右状态栏的不同打印，0为地图编辑情况下的 右固定菜单
	switch (choise)
	{
	case 0: {
		print_some_in(RIGHT_LINEX, RIGHT_LINEY, "按住相应键后左键点击即可绘制地图：");
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 2, "\"Q\"——土墙", WALL_COLOR);
		print_some_in(RIGHT_LINEX + 7, RIGHT_LINEY + 2, WALL_ICO, WALL_COLOR);
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 4, "\"W\"——草地", GRASS_COLOR);
		print_some_in(RIGHT_LINEX + 7, RIGHT_LINEY + 4, GRASS_ICO, GRASS_COLOR);
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 6, "\"E\"——沙漠", SAND_COLOR);
		print_some_in(RIGHT_LINEX + 7, RIGHT_LINEY + 6, SAND_ICO, SAND_COLOR);
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 8, "\"R\"——钢墙", REAL_WALL_COLOR);
		print_some_in(RIGHT_LINEX + 7, RIGHT_LINEY + 8, WALL_ICO, REAL_WALL_COLOR);
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 10, "\"F\"——河水", WATER_COLOR);
		print_some_in(RIGHT_LINEX + 7, RIGHT_LINEY + 10, WATER_ICO, WATER_COLOR);

		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 40, "当前鼠标位置：");
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 42, "ESC键退出");
		break;
	}
	case 1: {//游戏内固定类
		print_some_in(RIGHT_LINEX, RIGHT_LINEY, "第  关");
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 4, WALL_ICO, WALL_COLOR);
		print_some_in(RIGHT_LINEX + 2, RIGHT_LINEY + 4, "——可破坏墙体", WALL_COLOR);
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 6, WALL_ICO, REAL_WALL_COLOR);
		print_some_in(RIGHT_LINEX + 2, RIGHT_LINEY + 6, "——固定墙体", REAL_WALL_COLOR);
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 8, GRASS_ICO, GRASS_COLOR);
		print_some_in(RIGHT_LINEX + 2, RIGHT_LINEY + 8, "——草丛，遮挡视线", GRASS_COLOR);
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 10, SAND_ICO, SAND_COLOR);
		print_some_in(RIGHT_LINEX + 2, RIGHT_LINEY + 10, "——沙漠，降低移速", SAND_COLOR);
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 12, WATER_ICO, WATER_COLOR);
		print_some_in(RIGHT_LINEX + 2, RIGHT_LINEY + 12, "——河流，无法通过", WATER_COLOR);
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 16, "敌人剩余数量：");
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 18, "当前分数：");
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 20, "空格键暂停后P键存档，空格键恢复暂停");
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 40, "WASD键移动，E键射击！");
		print_some_in(RIGHT_LINEX, RIGHT_LINEY + 42, "ESC键退出");
	}
	case 2: {//游戏内刷新类，敌人剩余数量，关卡
		print_some_in(RIGHT_LINEX + 1, RIGHT_LINEY, map_count);
		print_some_in(RIGHT_LINEX + 8, RIGHT_LINEY + 16, ai_num);
		print_some_in(RIGHT_LINEX + 8, RIGHT_LINEY + 18, tank_map.get_score());
	}
	}
}




