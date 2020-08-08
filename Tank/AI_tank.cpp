#include "AI_tank.h"
#include "func.h"
//#include "A_star.h"

bool _AI_TANK::get_fire()
{
	return fire;
}

void _AI_TANK::change_fire(bool nfire)
{
	fire = nfire;
}

void _AI_TANK::_init(int number, WORD ncolor)
{
	//随机AI级别，中高级的纪律都较低，普通较高
	level = get_randnum(0, 10);
	switch (level) {
	default: {
		color = ncolor;
		speed=speed_save = TANK_SPEED;
		fire_chance = 10; 
		break;
	}
	case 1: {
		color = 0xf6;
		speed_save = speed = TANK_SPEED - 10;
		fire_chance = 5;
		break;
	}
	case 0: {
		color = 0xf4;
		speed_save = speed = TANK_SPEED - 20;
		fire_chance = 3;
		break;
	}
	}

	//初始化查找时间
	find_time = clock();
	do {//随机出生点
		switch (get_randnum(1, 5))
		{
		case 1:center_pos.X = NEW1_X; center_pos.Y = NEW1_Y; break;
		case 2:center_pos.X = NEW2_X; center_pos.Y = NEW2_Y; break;
		case 3:center_pos.X = NEW3_X; center_pos.Y = NEW3_Y; break;
		case 4:center_pos.X = NEW4_X; center_pos.Y = NEW4_Y; break;
		case 5:center_pos.X = NEW5_X; center_pos.Y = NEW5_Y; break;
		}
	} while (tank_map.did_in_obj(center_pos.X, center_pos.Y, MAP_WALL_ICO)
		|| tank_map.did_in_obj(center_pos.X, center_pos.Y, MAP_REAL_WALL_ICO)
		|| tank_map.did_in_obj(center_pos.X, center_pos.Y, MAP_WATER_ICO)
		|| !did_go_other_tank(center_pos.X, center_pos.Y));
	//在5个生成点内随机生成AI坦克，如果点在墙，水内或者其他坦克身上，重新生成

	switch (get_randnum(1, 4))//随机方向
	{
	case 1:side = UP;
	case 2:side = RIGHT;
	case 3:side = DOWN;
	case 4:side = LEFT;
	}
}

void _AI_TANK::auto_move()
{
	//判断是否在沙子上，并且更改速度
	did_go_sand();
	
	if (!get_randnum(0, fire_chance)) {
		fire = true;
	}//随机开火状态

	if (line_list.size() > 0 &&
		line_count > 0) {
		side = line_list[line_count].node_side;
		line_count--;
		//获取查找到路径的方向值
	}
	//使用父类根据方向的移动
	move();
}

bool _AI_TANK::did_go_sand()
{
	if (tank_map.did_in_obj(//如果中心坐标 在沙地
		center_pos.X, center_pos.Y, MAP_SAND_ICO))
	{
		speed = speed_save+100;//移速降低100
		return true;
	}
	else {
		speed = speed_save;
		return false;
	}//沙地探测减速
}

void _AI_TANK::find_line(COORD player_tank_pos)
{
	A_star a_star(center_pos, player_tank_pos);
	//创建A星对象并且传入开始结束坐标
	a_star._init();
	do {
		a_star.add_open_list();
		if (a_star.move_to_close_list())
			break;
	} while (a_star.close_list_last()->node_pos.X != player_tank_pos.X
		|| a_star.close_list_last()->node_pos.Y != player_tank_pos.Y);
	//循环A星查找，跳出后，清空line_list并且获得新的路径。
	line_list.clear();
	vector<NODE>().swap(line_list);
	line_list = a_star.pr_all_path();
	line_count = line_list.size() - 1;
	//从后往前读取line_list
}

time_t& _AI_TANK::get_find_time()
{
	return find_time;
}

int& _AI_TANK::get_ai_count()
{
	return AI_count;
}

