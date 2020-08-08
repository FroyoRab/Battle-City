#pragma once
#include <Windows.h>

class _MOVE_OBJ
{
protected:
	WORD color;			//��ɫ
	COORD center_pos;	//��������
	char side;			//����
	bool die;			//�Ƿ���Ҫ����
	bool died;			//�Ƿ��Ѿ�����
	int speed;			//�ƶ��ٶ�
public:
	//�� side �����ƶ�һ��
	virtual void move() = 0;
	
	//��color��ɫ��ӡ����
	virtual void show() = 0;

	//������ӡ�Ķ���
	virtual void clear() = 0;

	//ȥ��
	virtual void go_die() = 0;

	//��ȡ��������
	virtual bool get_died();

	//��ȡ��������
	virtual COORD get_center_pos();

	//�ж������Ƿ��ڶ����ڲ�
	virtual bool did_in_obj(COORD xy) = 0;

	//��ȡ�����ƶ��ٶ�
	virtual int get_speed();
	
	//���Ķ����ƶ��ٶ�
	virtual void change_speed(int num);

	//��ȡ����
	virtual int get_side();

	//��ȡ��ɫ
	virtual int get_color();
};