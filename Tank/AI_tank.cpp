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
	//���AI�����и߼��ļ��ɶ��ϵͣ���ͨ�ϸ�
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

	//��ʼ������ʱ��
	find_time = clock();
	do {//���������
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
	//��5�����ɵ����������AI̹�ˣ��������ǽ��ˮ�ڻ�������̹�����ϣ���������

	switch (get_randnum(1, 4))//�������
	{
	case 1:side = UP;
	case 2:side = RIGHT;
	case 3:side = DOWN;
	case 4:side = LEFT;
	}
}

void _AI_TANK::auto_move()
{
	//�ж��Ƿ���ɳ���ϣ����Ҹ����ٶ�
	did_go_sand();
	
	if (!get_randnum(0, fire_chance)) {
		fire = true;
	}//�������״̬

	if (line_list.size() > 0 &&
		line_count > 0) {
		side = line_list[line_count].node_side;
		line_count--;
		//��ȡ���ҵ�·���ķ���ֵ
	}
	//ʹ�ø�����ݷ�����ƶ�
	move();
}

bool _AI_TANK::did_go_sand()
{
	if (tank_map.did_in_obj(//����������� ��ɳ��
		center_pos.X, center_pos.Y, MAP_SAND_ICO))
	{
		speed = speed_save+100;//���ٽ���100
		return true;
	}
	else {
		speed = speed_save;
		return false;
	}//ɳ��̽�����
}

void _AI_TANK::find_line(COORD player_tank_pos)
{
	A_star a_star(center_pos, player_tank_pos);
	//����A�Ƕ����Ҵ��뿪ʼ��������
	a_star._init();
	do {
		a_star.add_open_list();
		if (a_star.move_to_close_list())
			break;
	} while (a_star.close_list_last()->node_pos.X != player_tank_pos.X
		|| a_star.close_list_last()->node_pos.Y != player_tank_pos.Y);
	//ѭ��A�ǲ��ң����������line_list���һ���µ�·����
	line_list.clear();
	vector<NODE>().swap(line_list);
	line_list = a_star.pr_all_path();
	line_count = line_list.size() - 1;
	//�Ӻ���ǰ��ȡline_list
}

time_t& _AI_TANK::get_find_time()
{
	return find_time;
}

int& _AI_TANK::get_ai_count()
{
	return AI_count;
}

