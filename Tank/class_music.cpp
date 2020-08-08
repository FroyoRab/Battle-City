#include "class_music.h"

MUSIC::MUSIC()
{//构造，提前打开文件
	mciSendString(("open sound\\tank\\LASER_level1.mp3 alias MUSIC5"), temp_laser, 255, 0);
	mciSendString(("open sound\\tank\\LASER_level3.mp3 alias MUSIC6"), temp_laser2, 255, 0);
}

void MUSIC::laser_level1()
{//激光炮第一阶段
	mciSendString("seek MUSIC5 to start", NULL, 0, 0);
	mciSendString("play MUSIC5", NULL, 0, 0);
}

void MUSIC::laser_level3()
{//射出阶段
	mciSendString("seek MUSIC6 to start", NULL, 0, 0);
	mciSendString("play MUSIC6", NULL, 0, 0);
}
