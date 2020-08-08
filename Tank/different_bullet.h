#pragma once
#include <Windows.h>
#include <vector>
#include <string>

#define LASER_BALL "��"
#define LASER_BALL_COLOR 0xf1
#define LASER_ICO_UP "|"
#define LASER_ICO_LEFT "=="
#define LASER_COLOR 0xbf

using std::vector;
using std::string;

struct temp_save_map {
	temp_save_map(COORD poss, char land, DWORD ncolor=0xf0)
		:pos(poss), land_ico(land), color(ncolor) {}
	COORD pos;
	char land_ico;
	DWORD color;
};

class _DIFFERENT_BULLET {
protected:
	//���ĵ���,���ұ�����ĺ�ĵ���
	virtual void change_map() = 0;

	//��ӡ
	virtual void show() = 0;

	//ȷ���Ƿ��������ڣ���ֱ�Ӵ�������ȷ��ʱ��
	virtual bool sure() = 0;

	//���
	virtual void clear() = 0;

};

class LASER :public _DIFFERENT_BULLET{
	COORD center;//��������
	int nside;//����
	vector<temp_save_map> land_save;//���ڴ��汻��������ĵ���
	int vanish_time;//��ʧʱ��
	int level = 1;//����
public:
	LASER(COORD fire_tank, int side);
	//���ĵ���,���ұ�����ĺ�ĵ���
	void change_map();
	//��ӡ
	void show();
	//ȷ���Ƿ��������ڣ���ֱ�Ӵ�������ȷ��ʱ��
	bool sure();
	//���
	void clear();
protected:
	void _change_map(COORD pos);
};