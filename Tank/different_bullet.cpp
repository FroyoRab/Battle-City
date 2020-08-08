#include "different_bullet.h"
#include "func.h"

LASER::LASER(COORD fire_tank, int side) 
	:center(fire_tank), nside(side)
{
	vanish_time = clock() + 1500;
	
}

void LASER::change_map()
{

	switch (nside)//中心点按方向的整个坐标轴
	{
	case UP: {
		center.Y -= 4;//中心点前移
		for (short y = center.Y; y >= 1; y--)
			_change_map({ center.X,y });
		break;
	}
	case DOWN: {
		center.Y += 4;
		for (short y = center.Y; y < 59 ; y++)
			_change_map({ center.X,y });

		break;
	}
	case LEFT: {
		center.X -= 4;
		for (short x = 0; x <= center.X; x++)
			_change_map({ x, center.Y });

		break;
	}
	case RIGHT: {
		center.X += 4;
		for (short x = center.X; x < 59; x++)
			_change_map({ x, center.Y });

		break;
	}
	}
	//中心点周围一圈
	for (short x = -1; x <= 1; x++)
	{
		for (short y = -1; y <= 1; y++)
		{
			_change_map({ center.X + x,center.Y + y });
		}
	}
}

void LASER::show()
{
	//不同阶段的显示
	switch (level)
	{
	case 1: {
		print_some_in(center.X, center.Y, LASER_BALL, LASER_BALL_COLOR);//中间
		music.laser_level1();
		music.laser_level3();
		break;
	}
	case 2: {
		for (int x = -1; x <= 1; x += 2)//左右
			print_some_in(center.X - x, center.Y, "┋", 0xfb);
		for (int y = -1; y <= 1; y += 2)//上下
			print_some_in(center.X, center.Y + 1, "┉┉", 0xfb);
			print_some_in(center.X, center.Y - 1, "┉┉", 0xfb);
		for (int i = -1; i <= 1; i += 2)
			print_some_in(center.X + i, center.Y + i, "〆", 0xfb);

		//斜角
		print_some_in(center.X - 1, center.Y + 1, "ゞ", 0xfb);
		print_some_in(center.X + 1, center.Y - 1, "ゝ", 0xfb);
		break;
	}
	case 3: {
		switch (nside)//中心点按方向的整个坐标轴
		{
		case UP: {
			for (int y = center.Y-1; y > 1; y--)
				print_some_in(center.X, y, "  ", LASER_COLOR);
			break;
		}
		case DOWN: {
			for (int y = center.Y+1; y <59 ; y++)
				print_some_in(center.X, y, "  ", LASER_COLOR);
			break;
		}
		case LEFT: {
			for (int x = 1; x <= center.X-1; x++)
				print_some_in(x, center.Y, "  ", LASER_COLOR);
			break;
		}
		case RIGHT: {
			for (int x = center.X+1; x < 59; x++)
				print_some_in(x, center.Y, "  ", LASER_COLOR);
			break;
		}
		}
	}
	}
	if (level < 3) {
		level++;
	}
}

bool LASER::sure()
{

	//物体在内识别
	for (temp_save_map& map_temp : land_save) {
		if (tank_list.size() > 0) {
			for (int i = 0; i < tank_list.size(); i++) {
				if (tank_list[i].did_in_obj(map_temp.pos)) {
					tank_list.erase(tank_list.begin() + i);
					_AI_TANK::get_ai_count()--;
					if (_AI_TANK::get_ai_count() <= 0) {
						if (_MAP::map_count == 5) {
							//通关界面
							PlaySoundA("sound\\tank\\win.wav",
								NULL, SND_ASYNC | SND_NODEFAULT);
							_MAP::map_count = 0;
						}
						else {
							_MAP::map_count++;
						}
						do_while = false;
						break;
					}
				}
			}
		}
		//判断子弹在内
		if (bullet_list.size() > 0) {
			for (int i = 0; i < bullet_list.size(); i++)
			{
				if (bullet_list[i].did_in_obj(map_temp.pos))
					bullet_list.erase(bullet_list.begin() + i);
			}
		}
	}
	//判断消失时间
	if (vanish_time < clock()) {
		clear();
		return true;
	}

	return false;
}

void LASER::clear()
{
	//根据储存的被照射的地方重新打印地形
	for (temp_save_map& save_temp : land_save)
	{
		if (save_temp.land_ico == MAP_SAND_ICO)
			print_some_in(save_temp.pos.X, save_temp.pos.Y, SAND_ICO, SAND_COLOR);
		else if (save_temp.land_ico == MAP_WALL_ICO)
			print_some_in(save_temp.pos.X, save_temp.pos.Y, WALL_ICO, WALL_COLOR);
		else
			print_some_in(save_temp.pos.X, save_temp.pos.Y, "  ");
	}
}

//遍历被照射的位置并且储存被更改后的地形
void LASER::_change_map(COORD pos)
{
	//墙，草变为沙漠
	if (tank_map.did_in_obj(pos.X, pos.Y, MAP_WALL_ICO) ||
		tank_map.did_in_obj(pos.X, pos.Y, MAP_GRASS_ICO) ||
		tank_map.did_in_obj(pos.X, pos.Y, MAP_REAL_WALL_ICO))
	{
		tank_map.change_map({ pos.X, pos.Y }, MAP_SAND_ICO);
		temp_save_map save_temp({ pos.X, pos.Y }, MAP_SAND_ICO, SAND_COLOR);
		land_save.push_back(save_temp);
	}
	//沙漠变墙
	else if (tank_map.did_in_obj(pos.X, pos.Y, MAP_SAND_ICO)) {
		tank_map.change_map({ pos.X, pos.Y }, MAP_WALL_ICO);
		temp_save_map save_temp({ pos.X, pos.Y }, MAP_WALL_ICO, WALL_COLOR);
		land_save.push_back(save_temp);
	}
	//水消失
	else {
		tank_map.change_map({ pos.X, pos.Y }, ' ');
		temp_save_map save_temp({ pos.X, pos.Y }, ' ');
		land_save.push_back(save_temp);
	}

}