#pragma once
#pragma once
#include <string>
#include <windows.h>
#include <iostream>
using namespace std;

class MENU {
private:
	int out_choose = 1;//���б�ѡ��
	int in_choose = 1;//�ڲ��б�ѡ��
	int* list = &out_choose;//�����л�����ѡ��ֵ
	int pos[7][8] = { {}, {0,24,26,28,30,32,34},{0,26,28,30,32,34,36},{0,28},{0,30},{0,32},{0,34} };
	string out_list[7] = {//�ⲿ�б�
		{" ̹�˴�ս" },
		{"�ٵ�����Ϸ"},
		{"��˫����Ϸ"},
		{"�۱༭��ͼ"},
		{"����Ϸ����"},
		{"�ݶ�ȡ�浵"},
		{"���˳���Ϸ"}
	};
	string in_list[7][7] = {//�ڲ��б�
	{},
	{{}, {"��LEVEL1"},{"��LEVEL2"},{"��LEVEL3"},
	{"��LEVEL4"},{"��LEVEL5"},{"���Զ����ͼ"}
	},
	{{},{"��LEVEL1"},{"��LEVEL2"},{"��LEVEL3"},
	{"��LEVEL4"},{"��LEVEL5"},{"���Զ����ͼ"}
	},
	{{},{"�༭�Զ���ؿ���ͼ"}},
	{{},{"��������̹��Ĭ���ٶȣ�AIѰ·Ƶ�ʵ�"}},
	{{},{"��ȡ�浵����ֱ�ӿ�ʼ��Ϸ"}},
	{{},{"�س����˳���Ϸ��"}},
	};
public:
	//����Ҳ�
	void clear_right();

	//�жϰ���
	void key_press();

	//�����б�
	void change_list();

	//�޵�ɫ��ӡȫ���˵�
	void pr_menu();

	//��ӡ��ѡ��˵�
	void pr_choose(int choose = 1, bool bool_in = true);

	//����ѡ��˵��������б�ֵ
	void get_choose(int& _out_choose, int& _out_choose2);

};