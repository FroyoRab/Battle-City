#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include "tank_class.h"
#include "cant_move_obj.h"
#include "AI_tank.h"
#include "class_music.h"
/**********************************/
using std::string;
using std::vector;
#define KEY_DOWN(VK_NONAME) \
((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

#define WINDOW_X 80
#define WINDOW_Y 60
#define RIGHT_LINEX 61
#define RIGHT_LINEY 5
#define	MENU_X 26
/*********����************/
#define HOME_X 30
#define HOME_Y 57	//��xy
#define NEW1_X 12
#define NEW1_Y 4	//������1
#define NEW2_X 30
#define NEW2_Y 4	//������2
#define NEW3_X 50
#define NEW3_Y 4	//������3
#define NEW4_X 4
#define NEW4_Y 18	//������4
#define NEW5_X 57
#define NEW5_Y 15	//������5
/********�ƶ�����*********/
#define TANK_ICO "��"
#define TANK_HEAD_ICO_UP "��"
#define TANK_HEAD_ICO_LEFT "����"
#define BULLET_ICO_UP "��"
#define BULLET_ICO_LEFT "����"
/********��ͼ*********/
#define MAP_WALL_ICO '#'
#define MAP_REAL_WALL_ICO 'X'
#define MAP_ICO '_'
#define MAP_GRASS_ICO 'v'
#define MAP_WATER_ICO 'w'
#define MAP_SAND_ICO 's'
#define SAND_ICO "�n"
#define WATER_ICO "�P"
#define WALL_ICO "��"
#define GRASS_ICO "����"
/********����*********/
#define UP			'w'
#define UP_B		'W'
#define DOWN		's'
#define DOWN_B		'S'
#define RIGHT		'd'
#define RIGHT_B		'D'
#define LEFT		'a'
#define LEFT_B		'A'

#define UP1			'i'
#define UP1_B		'I'
#define DOWN1		'k'
#define DOWN1_B		'K'
#define RIGHT1		'l'
#define RIGHT1_B	'L'
#define LEFT1		'j'
#define LEFT1_B		'J'

#define FIRE1		'e'
#define FIRE1_B		'E'
#define FIRE2		'u'
#define FIRE2_B		'U'
#define add_ai_B	'P'
/********��ɫ**********/
#define WATER_COLOR 0xf9
#define REAL_WALL_COLOR 0xf0
#define WALL_COLOR 0xf8
#define GRASS_COLOR 0xf2
#define SAND_COLOR 0xf6
/*********����************/

extern _MAP tank_map;
extern MUSIC music;
extern vector<_BULLET> bullet_list;
extern vector<_AI_TANK> tank_list;
extern vector<_TANK> tank_list_firends;
extern bool do_while;
/**********************************/
//��x,y��color��ɫ��ӡ
template<typename T>
void print_some_in(int x, int y, T text, WORD color=0xf0) {
	HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
	using std::cout;
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(outhandle, pos);

	WORD _color;
	_color = color;
	SetConsoleTextAttribute(outhandle, _color);

	cout << text;
}
//
void start();

//��ʼ������
void _init();

//��ȡָ����С�����
int get_randnum(int min, int max);

//�ӵ����
void tank_fire(COORD tank_pos, int side, WORD ncolor, short choise = 0);


//ȫ���ƶ�
void all_move();

//����ai
void creat_ai();

//��ӡ��״̬��0Ϊ�༭��ͼ�˵���1Ϊ��Ϸ�˵�
void pr_rightline(int choise = 1, int map_count = 1, int ai_num = 4);

//�浵
void save();

//����
bool load_save();

//��ʼ����
void start_form();

//����
void setting();