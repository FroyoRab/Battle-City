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
	//����̹�˷���
	void change_side(int nside);
	//�� side �����ƶ�һ��
	void move();
	//��color��ɫ��ӡ����
	void show();
	//������ӡ�Ķ���
	void clear();
	//��ʼ������
	void _init(WORD ncolor, COORD born_pos,short splayer);
	//ȥ��
	void go_die();
	//�ж������Ƿ��ڶ����ڲ�
	bool did_in_obj(COORD xy);
	//�ж��Ƿ�ײǽ
	bool did_go_wall(char side);
	//�ж��Ƿ��ڲݵ�
	bool did_go_grass();
	//�ж��Ƿ���ɳ��
	bool did_go_sand();
	//������
	short get_player();
	//�Ƿ�ײ������̹��
	bool did_go_other_tank(int x ,int y);
	//����Ĭ���ٶ�
	static int& get_save_speed();

};

//�ӵ���
class _BULLET :public _MOVE_OBJ
{
	//��������
	bool friends = true;
	//ID����
	int bullet_numbers;
public:
	//��ʼ�������뷢��̹�˵����꣬������ɫ���͵���
	void _init(COORD fire_tank,int nside,WORD ncolor=0xf0,bool bfriends=true);
	//�ƶ�
	void move();
	//��ӡ
	void show();
	//����
	void clear();
	//ȥ��
	void go_die();
	//�ж������Ƿ��غ�
	bool did_in_obj(COORD xy);
	//��ȡ����״̬
	bool get_friends();
	//�ط�ײ�������ӵ�
	bool did_go_other_bullet();
	//���ID
	int& get_id();
};
