#include "move_obj.h"

bool _MOVE_OBJ::get_died()
{
	return died;
}

COORD _MOVE_OBJ::get_center_pos()
{
	return center_pos;
}

int _MOVE_OBJ::get_speed()
{
	return speed;
}

void _MOVE_OBJ::change_speed(int num)
{
	speed = num;
}

int _MOVE_OBJ::get_side()
{
	return side;
}

int _MOVE_OBJ::get_color()
{
	return color;
}