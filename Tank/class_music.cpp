#include "class_music.h"

MUSIC::MUSIC()
{//���죬��ǰ���ļ�
	mciSendString(("open sound\\tank\\LASER_level1.mp3 alias MUSIC5"), temp_laser, 255, 0);
	mciSendString(("open sound\\tank\\LASER_level3.mp3 alias MUSIC6"), temp_laser2, 255, 0);
}

void MUSIC::laser_level1()
{//�����ڵ�һ�׶�
	mciSendString("seek MUSIC5 to start", NULL, 0, 0);
	mciSendString("play MUSIC5", NULL, 0, 0);
}

void MUSIC::laser_level3()
{//����׶�
	mciSendString("seek MUSIC6 to start", NULL, 0, 0);
	mciSendString("play MUSIC6", NULL, 0, 0);
}
