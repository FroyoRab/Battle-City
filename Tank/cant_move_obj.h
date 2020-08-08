#pragma once
#include <Windows.h>

class _MAP
{
protected:
	//WORD color;
	char c_map[61][81] = {0};
	int player_score = 0;
public:
	static int map_count;
	//�ж�XY�Ƿ���ǽ
	bool did_in_obj(int x, int y, char ICO);
	
	//���ļ����ص�ͼ
	void get_map_in_file(int select);
	
	//��ӡ��ͼ
	void print_map();

	//�����ͼ
	void save_map();

	//���õ�ͼ
	void init_map();

	//ɾ������
	void clear_one(int x,int y,char side);

	//�༭��ͼ
	void edit_map();

	//�༭��ͼ����¼�����
	void mouse_event_proc(MOUSE_EVENT_RECORD mouse_e);

	//�߿����
	void add_box();

	//��ȡ��ҷ���
	int& get_score();

	void change_map(COORD pos , char ico);
};

