#pragma once
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

class MUSIC {
	//���ڴ������ֻ��������
	char back[255];
	char temp_laser[255];
	char temp_laser2[255];
public:
	MUSIC();
	void laser_level1();//�����ڵ�һ�׶�
	void laser_level3();//����׶�
};