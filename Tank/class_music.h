#pragma once
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

class MUSIC {
	//用于储存音乐缓存的数组
	char back[255];
	char temp_laser[255];
	char temp_laser2[255];
public:
	MUSIC();
	void laser_level1();//激光炮第一阶段
	void laser_level3();//射出阶段
};