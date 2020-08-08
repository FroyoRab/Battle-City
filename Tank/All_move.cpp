#include "func.h"
#include "cant_move_obj.h"
#include "tank_class.h"
#include "different_bullet.h"
#pragma comment(lib,"winmm.lib")

void all_move() {
	system("cls");
	pr_rightline();
	tank_map.print_map();
	time_t time_move1 = clock();
	time_t time_move2 = clock();
	time_t time_add_bullet = clock();
	time_t time_add_bullet1 = clock();
	time_t time_bullet = clock();
	time_t time_bullet1 = clock();
	time_t ai_time = clock();
	time_t ai_time_list[20] = { clock() };
	time_t add_ai = clock();
	time_t ai_find_line = clock();
	time_t laser_time = clock();
	LASER* laser = nullptr;//������ָ��
	for (int i = 0; i < tank_list_firends.size(); i++)
	{
		tank_list_firends[i].show();
	}

	while (do_while)
	{/*******************�ƶ��ж�*************************/
		pr_rightline(2, _MAP::map_count, tank_list.size());
		for (int p = 0; p < tank_list_firends.size(); p++)
		{
			if (tank_list_firends[p].get_player() == 0) {
				if ((clock() - time_move1) > tank_list_firends[p].get_speed()) {
					if (KEY_DOWN(UP_B)) {
						time_move1 = clock();
						tank_list_firends[p].did_go_sand();
						tank_list_firends[p].change_side(UP);
						tank_list_firends[p].move();
					}
					if (KEY_DOWN(DOWN_B)) {
						time_move1 = clock();
						tank_list_firends[p].did_go_sand();
						tank_list_firends[p].change_side(DOWN);
						tank_list_firends[p].move();
					}
					if (KEY_DOWN(RIGHT_B)) {
						time_move1 = clock();
						tank_list_firends[p].did_go_sand();
						tank_list_firends[p].change_side(RIGHT);
						tank_list_firends[p].move();
					}
					if (KEY_DOWN(LEFT_B)) {
						time_move1 = clock();
						tank_list_firends[p].did_go_sand();
						tank_list_firends[p].change_side(LEFT);
						tank_list_firends[p].move();
					}
					if (KEY_DOWN(VK_ESCAPE)) {
						while (!KEY_DOWN(VK_ESCAPE));
						do_while = false;
						_MAP::map_count = 0;
						break;
					}

					if (KEY_DOWN(VK_SPACE)) {
						while (KEY_DOWN(VK_SPACE));
						print_some_in(RIGHT_LINEX, 50, "���ո����������P���浵");
						while (!KEY_DOWN(VK_SPACE)) {
							if (KEY_DOWN(0X50)) {//P������
								save();
							}
						}
						while (KEY_DOWN(VK_SPACE));
					}
				}/*******************�ӵ��ж�*************************/
				if (KEY_DOWN(FIRE1_B))
					if (clock() - time_add_bullet > 200) {
						time_add_bullet = clock();
						tank_fire(
							tank_list_firends[p].get_center_pos(),
							tank_list_firends[p].get_side(),
							tank_list_firends[p].get_color());
						PlaySoundA("sound\\tank\\fire.wav",
							NULL, SND_ASYNC | SND_NODEFAULT);
					}
				if (KEY_DOWN(0x52)) {//������
					while (KEY_DOWN(0x52));
					if (laser == nullptr) {
						laser = new LASER(
							tank_list_firends[0].get_center_pos(),
							tank_list_firends[0].get_side());
						laser->change_map();
						laser->show();
					}
				}
			}/*******************�ƶ��ж�*************************/
			else if (tank_list_firends[p].get_player() == 1) {
				if ((clock() - time_move2) > tank_list_firends[p].get_speed()) {
					if (KEY_DOWN(UP1_B)) {
						time_move2 = clock();
						tank_list_firends[p].did_go_sand();
						tank_list_firends[p].change_side(UP);
						tank_list_firends[p].move();
					}
					if (KEY_DOWN(DOWN1_B)) {
						time_move2 = clock();
						tank_list_firends[p].did_go_sand();
						tank_list_firends[p].change_side(DOWN);
						tank_list_firends[p].move();
					}
					if (KEY_DOWN(RIGHT1_B)) {
						time_move2 = clock();
						tank_list_firends[p].did_go_sand();
						tank_list_firends[p].change_side(RIGHT);
						tank_list_firends[p].move();
					}
					if (KEY_DOWN(LEFT1_B)) {
						time_move2 = clock();
						tank_list_firends[p].did_go_sand();
						tank_list_firends[p].change_side(LEFT);
						tank_list_firends[p].move();
					}
					if (KEY_DOWN(VK_ESCAPE)) {
						while (KEY_DOWN(VK_ESCAPE));
						do_while = false;
						_MAP::map_count = 0;
						break;
					}
				}/*******************�ӵ��ж�*************************/
				if (KEY_DOWN(FIRE2_B))
					if (clock() - time_add_bullet1 > 500) {
						time_add_bullet1 = clock();
						tank_fire(
							tank_list_firends[p].get_center_pos(),
							tank_list_firends[p].get_side(),
							tank_list_firends[p].get_color());
					}
			}
		}
		/*******************�ӵ��ж�*************************/
		if (do_while == false)
			break;

		if (laser != nullptr) {
			//������
			if ((clock() - laser_time) > 1000) {
				laser_time = clock();
				laser->show();
			}
			if (laser->sure()) {
				delete laser;
				laser = nullptr;	
			}
		
		}

		if ((clock() - time_bullet) > 45) {
			time_bullet = clock();
			if (bullet_list.size() > 0) {
				for (int i = 0; i < bullet_list.size(); i++)
				{
					bullet_list[i].move();
					//tank1.show();
					if (tank_map.did_in_obj(//�ж��ӵ��Ƿ����ǽ��
						bullet_list[i].get_center_pos().X,
						bullet_list[i].get_center_pos().Y,
						MAP_WALL_ICO)) {

						tank_map.clear_one(//ɾ��������ǽ��
							bullet_list[i].get_center_pos().X/*+x*/,
							bullet_list[i].get_center_pos().Y/*+y*/,
							bullet_list[i].get_side());
						if (bullet_list[i].get_friends()) {
						}
						bullet_list[i].go_die();//�������棡
					}
					else if (tank_map.did_in_obj(//�ж��ӵ��Ƿ���в����ƻ�ǽ��
						bullet_list[i].get_center_pos().X,
						bullet_list[i].get_center_pos().Y,
						MAP_REAL_WALL_ICO)) {
						bullet_list[i].go_die();//�������棡
					}

					if (tank_list.size() > 0) {//�жϵз�̹������
						for (int a = 0; a < tank_list.size(); a++) {//�ж��ӵ��Ƿ�ai̹��
							if (tank_list[a].did_in_obj(
								bullet_list[i].get_center_pos())
								&& bullet_list[i].get_friends())
							{
								tank_list[a].go_die();
								tank_list.erase(tank_list.begin() + a);
								_AI_TANK::get_ai_count()--;
								PlaySoundA("sound\\tank\\fire_tank.wav",
									NULL, SND_ASYNC | SND_NODEFAULT);
								tank_map.get_score()++;
								bullet_list[i].go_die();
								if (_AI_TANK::get_ai_count() <= 0) {
									if (_MAP::map_count == 5) {
										//ͨ�ؽ���
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
					if (do_while == false)
						break;


					if (tank_list_firends.size() > 0) {
						for (int f = 0; f < tank_list_firends.size(); f++)
						{
							if (tank_list_firends[f].did_in_obj(bullet_list[i].get_center_pos())
								&& bullet_list[i].get_friends() == false) {
								tank_list_firends[f].clear();
								tank_list_firends.erase(tank_list_firends.begin() + f);
								if (tank_list_firends.size() == 0) {
									print_some_in(WINDOW_X / 2, WINDOW_Y / 2, "̫������");
									PlaySoundA("sound\\tank\\died.wav",
										NULL, SND_ASYNC | SND_NODEFAULT);
									system("pause");
									do_while = false;//��Ϸ����
									_MAP::map_count = 0;
								}
							}
						}
						if (do_while == false)
							break;

					}
					if (bullet_list[i].get_center_pos().X >= HOME_X - 1
						&& bullet_list[i].get_center_pos().X <= HOME_X + 1
						&& bullet_list[i].get_center_pos().Y >= HOME_Y - 1
						&& bullet_list[i].get_center_pos().Y <= HOME_Y + 1) {
						print_some_in(WINDOW_X / 2, WINDOW_Y / 2, "̫������");
						PlaySoundA("sound\\tank\\died.wav",
							NULL, SND_ASYNC | SND_NODEFAULT);
						system("pause");
						do_while = false;//���ر���
						_MAP::map_count = 0;
					}

					if (bullet_list[i].did_go_other_bullet())
						bullet_list[i].go_die();

					//�ж��Ƿ�Ӧ������
					if (bullet_list[i].get_died()) {
						bullet_list.erase(bullet_list.begin() + i);
					}
				}
				if (do_while == false)
					break;
			}

		}/*******************�ӵ��ж�*************************/
		/*******************AI�ж�***********************/
		/*if (KEY_DOWN(add_ai_B) && ) {*/
		if ((clock() - add_ai > 200) && tank_list.size() < _AI_TANK::get_ai_count()) {
			add_ai = clock();
			creat_ai();
		}
		/*}*/
		for (int ai = 0; ai < tank_list.size(); ai++) {
			if (clock() - tank_list[ai].get_find_time() > A_star::get_find_time())
			{
				tank_list[ai].get_find_time() = clock();
				tank_list[ai].find_line(
					tank_list_firends[0].get_center_pos());
			}

			if (clock() - ai_time_list[ai] >
				tank_list[ai].get_speed()) {
				ai_time_list[ai] = clock();
				if (tank_list.size() > 0) {
					//tank_list[i].did_go_sand();
					tank_list[ai].auto_move();
				}
			}//�ƶ�


			if (tank_list[ai].get_fire()) {
				tank_fire(
					tank_list[ai].get_center_pos(),
					tank_list[ai].get_side(),
					tank_list[ai].get_color(), 1);
				tank_list[ai].change_fire(false);
			}//�����ж�
		}/*******************AI�ж�***********************/
	}
}