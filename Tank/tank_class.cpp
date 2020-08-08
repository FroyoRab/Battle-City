#include "tank_class.h"
#include "func.h"
/*****************************************************/
//̹�����Ա����
void _TANK::move()
{
	show();
	clear();
	switch (side)
	{
	case UP: {
		if (did_go_wall(side))
			break;
		if (side_change) {
			side_change = false;
			break;
		}
		center_pos.Y--;
		break;
	}
	case DOWN: {
		if (did_go_wall(side))
			break;
		if (side_change) {
			side_change = false;
			break;
		}
		center_pos.Y++;
		break;
	}
	case RIGHT: {
		if (did_go_wall(side))
			break;
		if (side_change) {
			side_change = false;
			break;
		}
		center_pos.X++;
		break;
	}
	case LEFT: {
		if (did_go_wall(side))
			break;
		if (side_change) {
			side_change = false;
			break;
		}
		center_pos.X--;
		break;
	}
	}
	clear();
	show();
	
}

void _TANK::show()
{
	switch (side)
	{
	case UP: {
		for (int x = center_pos.X - 1; x <= center_pos.X + 1; x++)
		{
			for (int y = center_pos.Y - 1; y <= center_pos.Y + 1; y++)
			{
				if (tank_map.did_in_obj(x, y, MAP_GRASS_ICO)) {
					continue;
				}
				if (x == center_pos.X&&y == center_pos.Y - 1)
					print_some_in(x, y, TANK_HEAD_ICO_UP, color);//x,y-1��ӡͷ
				else if (x == center_pos.X&&y == center_pos.Y + 1) {
					continue;
				}
				else print_some_in(x, y, TANK_ICO, color);	//������ӡ����
			}
		}
		break;
	}
	case DOWN: {
		for (int x = center_pos.X - 1; x <= center_pos.X + 1; x++)
		{
			for (int y = center_pos.Y - 1; y <= center_pos.Y + 1; y++)
			{
				if (tank_map.did_in_obj(x, y, MAP_GRASS_ICO)) {
					continue;
				}
				if (x == center_pos.X&&y == center_pos.Y - 1) {
					continue;
				}
				else if (x == center_pos.X&&y == center_pos.Y + 1)
					print_some_in(x, y, TANK_HEAD_ICO_UP, color); //x,y+1 head
				else print_some_in(x, y, TANK_ICO, color);//��������
			}
		}
		break;
	}
	case RIGHT: {
		for (int x = center_pos.X - 1; x <= center_pos.X + 1; x++)
		{
			for (int y = center_pos.Y - 1; y <= center_pos.Y + 1; y++)
			{
				if (tank_map.did_in_obj(x, y, MAP_GRASS_ICO)) {
					continue;
				}
				if (x == center_pos.X - 1 && y == center_pos.Y) {
					continue;
				}
				else if (x == center_pos.X + 1 && y == center_pos.Y)
					print_some_in(x, y, TANK_HEAD_ICO_LEFT, color); //x+1,y head
				else print_some_in(x, y, TANK_ICO, color);//��������
			}
		}
		break;
	}
	case LEFT: {
		for (int x = center_pos.X - 1; x <= center_pos.X + 1; x++)
		{
			for (int y = center_pos.Y - 1; y <= center_pos.Y + 1; y++)
			{
				if (tank_map.did_in_obj(x, y, MAP_GRASS_ICO)) {
					continue;
				}
				if (x == center_pos.X - 1 && y == center_pos.Y)
					print_some_in(x, y, TANK_HEAD_ICO_LEFT, color); //x+1,y head
				else if (x == center_pos.X + 1 && y == center_pos.Y) {
					continue;
				}
				else print_some_in(x, y, TANK_ICO, color);//��������
			}
		}
		break;
	}
	}
	did_go_grass();
}


void _TANK::clear()
{
	for (int x = center_pos.X - 1; x <= center_pos.X + 1; x++)
	{
		for (int y = center_pos.Y - 1; y <= center_pos.Y + 1; y++)
		{
			if (tank_map.did_in_obj(x, y, MAP_GRASS_ICO)) {
				continue;
			}
			else if (tank_map.did_in_obj(x, y, MAP_SAND_ICO)) {
				switch (side)
				{
				case UP: {//ɳ���жϣ����ۼ�
					if (x == center_pos.X)
						print_some_in(x, y, SAND_ICO, SAND_COLOR);
					else
						print_some_in(x, y, "��", SAND_COLOR);
					break;
				}
				case DOWN: {
					if (x == center_pos.X)
						print_some_in(x, y, SAND_ICO, SAND_COLOR);
					else
						print_some_in(x, y, "��", SAND_COLOR);
					break;
				}
				case LEFT: {
					if (y == center_pos.Y)
						print_some_in(x, y, SAND_ICO, SAND_COLOR);
					else
						print_some_in(x, y, "<<", SAND_COLOR);
					break;
				}
				case RIGHT: {
					if (y == center_pos.Y)
						print_some_in(x, y, SAND_ICO, SAND_COLOR);
					else
						print_some_in(x, y, ">>", SAND_COLOR);
					break;
				}
				}
			}
			else print_some_in(x, y, "  ");
		}
	}
}

void _TANK::_init(WORD ncolor,COORD born_pos,short splayer)
{
	center_pos.X =born_pos.X;
	center_pos.Y = born_pos.Y;
	color = ncolor;
	side = UP;
	speed = TANK_PLAYER_SPEED;
	player = splayer;
}

void _TANK::go_die()
{
	clear();
	center_pos.X = 0;
	center_pos.Y = 0;//�������
}

bool _TANK::did_in_obj(COORD xy)
{
	if ((xy.X >= center_pos.X - 1
		&& xy.X <= center_pos.X + 1)
		&& (xy.Y >= center_pos.Y - 1
			&& xy.Y <= center_pos.Y + 1))//x��x-1��x+1֮�� y��y-1��y+1֮��
	{
		return true;
	}
	else return false;
}

bool _TANK::did_go_wall(char side)
{
	switch (side)
	{//���ݲ�ͬ�ķ���
	case UP: {//�ж��Ƿ���ǽ�͸�ǽ�Լ�ˮ��
		for (int i = -1; i <= 1; i++)
		{
			if (tank_map.did_in_obj(center_pos.X + i,
				center_pos.Y - 2, MAP_WALL_ICO)
				|| tank_map.did_in_obj(center_pos.X + i,
					center_pos.Y - 2, MAP_REAL_WALL_ICO)
				|| tank_map.did_in_obj(center_pos.X + i,
					center_pos.Y - 2, MAP_WATER_ICO)
				||did_go_other_tank(center_pos.X + i,
					center_pos.Y - 2))
				return true;
		}return false;
	}
	case DOWN: {
		for (int i = -1; i <= 1; i++)
		{
			if (tank_map.did_in_obj(center_pos.X + i,
				center_pos.Y + 2, MAP_WALL_ICO)
				|| tank_map.did_in_obj(center_pos.X + i,
					center_pos.Y + 2, MAP_REAL_WALL_ICO)
				|| tank_map.did_in_obj(center_pos.X + i,
					center_pos.Y + 2, MAP_WATER_ICO)
				||did_go_other_tank(center_pos.X + i,
					center_pos.Y + 2))
				return true;
		}return false;
	}
	case RIGHT: {
		for (int i = -1; i <= 1; i++)
		{
			if (tank_map.did_in_obj(center_pos.X + 2,
				center_pos.Y + i, MAP_WALL_ICO)
				|| tank_map.did_in_obj(center_pos.X + 2,
					center_pos.Y + i, MAP_REAL_WALL_ICO)
				|| tank_map.did_in_obj(center_pos.X + 2,
					center_pos.Y + i, MAP_WATER_ICO)
				||did_go_other_tank(center_pos.X + 2,
					center_pos.Y + i))
				return true;
		}return false;
	}
	case LEFT: {
		for (int i = -1; i <= 1; i++)
		{
			if (tank_map.did_in_obj(center_pos.X - 2,
				center_pos.Y + i, MAP_WALL_ICO)
				|| tank_map.did_in_obj(center_pos.X - 2,
					center_pos.Y + i, MAP_REAL_WALL_ICO)
				|| tank_map.did_in_obj(center_pos.X - 2,
					center_pos.Y + i, MAP_WATER_ICO)
				||did_go_other_tank(center_pos.X - 2,
					center_pos.Y + i))
				return true;
		}return false;
	}
	}
	printf("did_go_wall err!");
	system("pause");
	return false;
}

bool _TANK::did_go_grass()
{
	for (int x = center_pos.X - 1; x <= center_pos.X + 1; x++)
	{
		for (int y = center_pos.Y - 1; y <= center_pos.Y + 1; y++)
		{
			if (tank_map.did_in_obj(x, y, MAP_GRASS_ICO)) {
				//print_some_in(x, y, GRASS_ICO, GRASS_COLOR);
				return true;
			}
		}
	}
	return false;
}

bool _TANK::did_go_sand()
{
	if (tank_map.did_in_obj(
		center_pos.X, center_pos.Y, MAP_SAND_ICO))
	{
		speed = TANK_PLAYER_SPEED + 100;
		return true;
	}
	else {
		speed = TANK_PLAYER_SPEED;
		return false;
	}//ɳ��̽�����
}

short _TANK::get_player()
{
	return player;
}

bool _TANK::did_go_other_tank(int x, int y)
{
	COORD xy = { x,y };
	for (size_t i = 0; i < tank_list.size(); i++)
	{
		if (tank_list[i].did_in_obj(xy))
			return true;
	}
	for (size_t i = 0; i < tank_list_firends.size(); i++)
	{
		if (tank_list_firends[i].did_in_obj(xy))
			return true;
	}
	return false;
}

int& _TANK::get_save_speed()
{
	return TANK_PLAYER_SPEED;
}

void _TANK::change_side(int nside)
{
	if (side != nside) {
		side = nside;
		side_change = true;
	}

}

/********************************************************************/
//�ӵ����Ա����

void _BULLET::_init(COORD fire_tank, int nside, WORD ncolor, bool bfriends)
{
	friends = bfriends;
	center_pos.X = fire_tank.X;//������xy�����̹�˵�xy
	center_pos.Y = fire_tank.Y;

	side = nside;//���������Ƿ���̹�˵�ǰ����
	died = false;
	color = ncolor;//��ɫĬ��0xf0

	//���ݷ���ǰ���ӵ�λ��
	switch (side)
	{
	case UP: {
		center_pos.Y -= 1;
		break;
	}
	case DOWN: {
		center_pos.Y += 1;
		break;
	}
	case RIGHT: {
		center_pos.X += 1;
		break;
	}
	case LEFT: {
		center_pos.X -= 1;
		break;
	}
	}
	if (tank_map.did_in_obj(center_pos.X, center_pos.Y, MAP_REAL_WALL_ICO)) {
		go_die();
	}
}

void _BULLET::move()
{
	if (!tank_map.did_in_obj(//�ж��ӵ��Ƿ���вݵ�
		center_pos.X, center_pos.Y, MAP_GRASS_ICO)) {
		clear();
	}
	switch (side)
	{
	case UP: {
		center_pos.Y--;
		break;
	}
	case DOWN: {
		center_pos.Y++;
		break;
	}
	case RIGHT: {
		center_pos.X++;
		break;
	}
	case LEFT: {
		center_pos.X--;
		break;
	}
	}
	if (!died)
		show();
}

void _BULLET::show()
{
	switch (side)
	{
	case DOWN:
	case UP: {
		if (tank_map.did_in_obj(//�ж��ӵ��Ƿ���вݵ�
			center_pos.X, center_pos.Y, MAP_GRASS_ICO)) {
			break;
		}
		else {
			print_some_in(center_pos.X, center_pos.Y, BULLET_ICO_UP, color);
			break;
		}
	}
	case LEFT:
	case RIGHT: {
		if (tank_map.did_in_obj(//�ж��ӵ��Ƿ���вݵ�
			center_pos.X, center_pos.Y, MAP_GRASS_ICO)) {
			break;
		}
		else {
			print_some_in(center_pos.X, center_pos.Y, BULLET_ICO_LEFT, color);
			break;
		}
	}
	}
	switch (side)//ˮ��ָ�
	{
	case UP: {
		if (tank_map.did_in_obj(center_pos.X, center_pos.Y + 3, MAP_WATER_ICO))
			print_some_in(center_pos.X, center_pos.Y + 3, WATER_ICO, WATER_COLOR);break; }
	case DOWN: {
		if (tank_map.did_in_obj(center_pos.X, center_pos.Y - 3, MAP_WATER_ICO))
			print_some_in(center_pos.X, center_pos.Y - 3, WATER_ICO, WATER_COLOR);break; }
	case LEFT: {
		if (tank_map.did_in_obj(center_pos.X + 3, center_pos.Y, MAP_WATER_ICO))
			print_some_in(center_pos.X + 3, center_pos.Y, WATER_ICO, WATER_COLOR);break; }
	case RIGHT: {
		if (tank_map.did_in_obj(center_pos.X - 3, center_pos.Y, MAP_WATER_ICO))
			print_some_in(center_pos.X - 3, center_pos.Y, WATER_ICO, WATER_COLOR);break; }
	}
	switch (side)//ɳ��ָ�
	{
	case UP: {
		if (tank_map.did_in_obj(center_pos.X, center_pos.Y + 3, MAP_SAND_ICO))
			print_some_in(center_pos.X, center_pos.Y + 3, SAND_ICO, SAND_COLOR); break; }
	case DOWN: {
		if (tank_map.did_in_obj(center_pos.X, center_pos.Y - 3, MAP_SAND_ICO))
			print_some_in(center_pos.X, center_pos.Y - 3, SAND_ICO, SAND_COLOR); break; }
	case LEFT: {
		if (tank_map.did_in_obj(center_pos.X + 3, center_pos.Y, MAP_SAND_ICO))
			print_some_in(center_pos.X + 3, center_pos.Y, SAND_ICO, SAND_COLOR); break; }
	case RIGHT: {
		if (tank_map.did_in_obj(center_pos.X - 3, center_pos.Y, MAP_SAND_ICO))
			print_some_in(center_pos.X - 3, center_pos.Y, SAND_ICO, SAND_COLOR); break; }
	}
}

void _BULLET::clear()
{
	if (tank_map.did_in_obj(//�ж��ӵ��Ƿ���в����ƻ�ǽ��,����ǽ��
		center_pos.X, center_pos.Y, MAP_REAL_WALL_ICO)) {
		print_some_in(center_pos.X, center_pos.Y, WALL_ICO, REAL_WALL_COLOR);
	}
	else if (tank_map.did_in_obj(//�ж��ӵ��Ƿ����ˮ��
		center_pos.X, center_pos.Y, MAP_WATER_ICO)) {
		switch (side)
		{
		case UP: print_some_in(center_pos.X, center_pos.Y, "��", WATER_COLOR); break;
		case DOWN:print_some_in(center_pos.X, center_pos.Y, "��", WATER_COLOR); break;
		case LEFT:print_some_in(center_pos.X, center_pos.Y, "<<", WATER_COLOR); break;
		case RIGHT:print_some_in(center_pos.X, center_pos.Y, ">>", WATER_COLOR); break;
		}
	}
	else if (tank_map.did_in_obj(//�ж��ӵ��Ƿ����ɳ��
		center_pos.X, center_pos.Y, MAP_SAND_ICO)) {
		switch (side)
		{
		case UP: print_some_in(center_pos.X, center_pos.Y, "��", SAND_COLOR); break;
		case DOWN:print_some_in(center_pos.X, center_pos.Y, "��", SAND_COLOR); break;
		case LEFT:print_some_in(center_pos.X, center_pos.Y, "<<", SAND_COLOR); break;
		case RIGHT:print_some_in(center_pos.X, center_pos.Y, ">>", SAND_COLOR); break;
		}
	}
	else {
		print_some_in(center_pos.X, center_pos.Y, "  ");
	}

}

void _BULLET::go_die()
{
	for (int x = -2; x <= 2; x++)
	{
		for (int y = -2; y <= 2; y++)
		{
			if (tank_map.did_in_obj(//���ӵ�������Χ16���ˮ����
				center_pos.X + x,
				center_pos.Y + y,
				MAP_WATER_ICO))
			{
				print_some_in(
					center_pos.X + x,
					center_pos.Y + y,
					WATER_ICO, WATER_COLOR);
			}
			if (tank_map.did_in_obj(//���ӵ�������Χ16���ɳ������
				center_pos.X + x,
				center_pos.Y + y,
				MAP_SAND_ICO))
			{
				print_some_in(
					center_pos.X + x,
					center_pos.Y + y,
					SAND_ICO, SAND_COLOR);
			}
		}
	}
	clear();
	center_pos.X = 0;
	center_pos.Y = 0;
	died = true;
}

bool _BULLET::did_in_obj(COORD xy)
{
	if (xy.X == center_pos.X&&xy.Y == center_pos.Y)
		return true;
	else return false;
}

bool _BULLET::get_friends()
{
	return friends;
}

bool _BULLET::did_go_other_bullet()
{
	for (size_t i = 0; i < bullet_list.size(); i++)
	{
		if (bullet_list[i].did_in_obj(center_pos)
			&&
			bullet_list[i].bullet_numbers!=bullet_numbers) {
			return true;
		}
	}
	return false;
}

int& _BULLET::get_id()
{
	return bullet_numbers;
}
