#pragma once
#include "tank_class.h"
#include <Windows.h>
#include <algorithm>
#include <string>
#include <vector>

using std::vector;
using std::string;

//A�ǽڵ�
struct NODE
{
	int F;
	int H;//Ԥ��ֵ
	int G;//����ֵ
	char node_side;//�ڵ㷽��
	COORD node_pos;//�ڵ�λ��
	NODE* father_node;//ָ�򸸽ڵ�
	NODE(int h, int g, int pos_x, int pos_y,
		NODE* father_NODE);//�ڵ㹹��
	void change_side();//���ķ��������ڸ��ĸ��ڵ�ʱ���㷽��ʹ��
};


class A_star {
	vector<NODE*> open_list;
	vector<NODE*> close_list;
	vector<NODE> line_list;
	//���潫���س�ȥ��·��

	COORD start_pos;//ͨ��������Ŀ�ʼλ��
	COORD end_pos;//������
	
	static int find_time;//Ѱ·Ƶ��
public:
	A_star(COORD Start_pos, COORD End_pos);
	//��ʼ��
	void _init();

	//����Χ�ĸ����open_list,����ʱ�ж��Ƿ���ǽ�ڣ�
	//�����Ƿ��Ѿ���close_list�ڣ��ǵĻ������� 
	//���ǵĻ����ж��Ƿ��Ѿ���open_list�ڣ�
	//�ǵĻ��ж�Gֵ�Ƿ�ȵ�ǰ����С���ǵĻ�����ǰ�������Ϊ�Ǹ�����
	//�������¼���Gֵ
	void add_open_list();

	//����open_list��Fֵ��С�ģ��������±�
	int find_min_F();

	//��open_list��F��С�ķ���close_list�У����Ҵ�open_listɾ��
	bool move_to_close_list();

	//����close_list�Ľ�β
	NODE* close_list_last();

	//��ӡ����·��
	vector<NODE> pr_all_path();

	//��ô����Ѱ��Ƶ��
	static int& get_find_time();

};


class _AI_TANK : public _TANK
{
	//�Ƿ񿪻����������
	bool fire = false;
	//����AI���𣬼����������Ƶ�ʺ��ƶ��ٶ�
	short level ;
	//�����A�ǵ�����
	vector<NODE> line_list;
	//��¼·���Ķ�ȡλ��
	int line_count = 0;
	//����Ƶ��
	time_t find_time = 0;
	//ai��������
	static int AI_count;
	//����Ƶ��
	short fire_chance;
	//������ٶȣ�ɳ�ؼ���ʱʹ��
	int speed_save;
	//�ⲿ����Ĭ���ٶ�
	static int TANK_SPEED;
public:
	//��ÿ���״̬
	bool get_fire();
	//���Ŀ���״̬
	void change_fire(bool fire);
	//��ʼ��AI״̬
	void _init(int number, WORD ncolor);
	//�Զ��ƶ������ķ���Ȼ����ø���move
	void auto_move();
	//�ж��Ƿ����ɳ��
	bool did_go_sand();
	//����·��
	void find_line(COORD player_tank_pos);
	//��ȡ����Ƶ��
	time_t& get_find_time();
	//��ȡAI��������
	static int& get_ai_count();
};