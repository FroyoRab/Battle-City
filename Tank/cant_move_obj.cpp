#include "cant_move_obj.h"
#include "func.h"


bool _MAP::did_in_obj(int x, int y, char ICO)
{
	//判断地图这个坐标是否有ICO这个地形
	if (c_map[y][x] == ICO)
		return true;
	else return false;
}

void _MAP::get_map_in_file(int select)
{
	using std::cout;
	using std::endl;
	FILE* pfile;
	//根据关卡打开地图
	switch (select)
	{
	default:
	case 1: {
		if (fopen_s(&pfile, "map\\map_level1.txt", "rb")) {
			cout << "打开文件失败，重置地图" << endl;
			Sleep(200);
			init_map();
		}break; }
	case 2: {
		if (fopen_s(&pfile, "map\\map_level2.txt", "rb")) {
			cout << "打开文件失败，重置地图" << endl;
			Sleep(200);
			init_map();
		}break; }
	case 3: {
		if (fopen_s(&pfile, "map\\map_level3.txt", "rb")) {
			cout << "打开文件失败，重置地图" << endl;
			Sleep(200);
			init_map();
			
		}break; }
	case 4: {
		if (fopen_s(&pfile, "map\\map_level4.txt", "rb")) {
			cout << "打开文件失败，重置地图" << endl;
			Sleep(200);
			init_map();
			
		}break; }
	case 5: {
		if (fopen_s(&pfile, "map\\map_level5.txt", "rb")) {
			cout << "打开文件失败，重置地图" << endl;
			Sleep(200);
			init_map();
			
		}break; }
	case 6: {
		if (fopen_s(&pfile, "map.txt", "rb")) {
			cout << "打开文件失败，重置地图" << endl;
			Sleep(200);
			init_map();
		}break; }
	}
	if (pfile != nullptr) {//成功打开后
		fread_s(&c_map, sizeof(c_map), sizeof(c_map), 1, pfile);
		fclose(pfile);
	}
	else {//打开文件失败
		cout << "打开文件失败" << endl;
		system("pause");

	}

}

void _MAP::print_map()
{

	for (int y = 0; y <= 60; y++)
	{
		for (int x = 0; x <= 80; x++)//打印墙体和草
		{
			if (c_map[y][x] == MAP_ICO) {}
			else if (c_map[y][x] == MAP_WALL_ICO) {
				print_some_in(x, y, WALL_ICO, WALL_COLOR);
			}
			else if (c_map[y][x] == MAP_GRASS_ICO) {
				print_some_in(x, y, GRASS_ICO, GRASS_COLOR);
			}
			else if (c_map[y][x] == MAP_REAL_WALL_ICO) {
				print_some_in(x, y, WALL_ICO, REAL_WALL_COLOR);
			}
			else if (c_map[y][x] == MAP_WATER_ICO) {
				print_some_in(x, y, WATER_ICO, WATER_COLOR);
			}
			else if (c_map[y][x] == MAP_SAND_ICO) {
				print_some_in(x, y, SAND_ICO, SAND_COLOR);
			}
		}
	}
	add_box();//打印外框
	print_some_in(28, 56, "◣★◢", 0xf4);//打印就老家
	print_some_in(28, 57, "■■■", 0xf4);
	print_some_in(28, 58, "◢■◣", 0xf4);
}

void _MAP::save_map()
{
	//保存地图
	using std::cout;
	using std::endl;
	FILE* pfile;
	add_box();
	for (size_t y = 0; y < 60; y++)
	{
		c_map[y][0] = MAP_WALL_ICO;
	}
	fopen_s(&pfile, "map.txt", "wb");
	if (pfile == nullptr)cout << "打开文件失败";
	else {
		fwrite(c_map, sizeof(c_map), 1, pfile);
		fclose(pfile);
	}
}

void _MAP::init_map()
{
	//重置地图
	system("cls");
	system("copy /Y map_back.txt map.txt");//将备份文件覆盖现有地图
	save_map();
	print_some_in(WINDOW_X / 2 - 10, WINDOW_Y / 2,
		"重置地图并保存成功！");
}

void _MAP::clear_one(int x, int y,char side)
{
	//清除地图上的一个点
	switch (side)
	{
	case DOWN:
	case UP: {
		for (int _x = -1; _x <= 1; _x++)
		{
			if (c_map[y][x + _x] == MAP_WALL_ICO) {
				c_map[y][x + _x] = ' ';
				print_some_in((x + _x), y, "  ");
			}
		}
		break;
	}
	case RIGHT:
	case LEFT: {
		for (int _y = -1; _y <= 1; _y++) {
			if (c_map[y + _y][x ] == MAP_WALL_ICO) {
				c_map[y + _y][x ] = ' ';
				print_some_in(x, (y + _y), "  ");
			}
		}
		break;
	}
	}

}

void _MAP::edit_map()
{
	//编辑地图
	system("cls");
	//打印边框
	pr_rightline(0);
	get_map_in_file(6);
	print_map();
	HANDLE std_in_handle = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(std_in_handle, ENABLE_MOUSE_INPUT);
	//启用鼠标输入

	INPUT_RECORD event_record = { 0 };
	DWORD temp;
	while (1)
	{
		//读取控制台输入
		ReadConsoleInput(std_in_handle, &event_record, 1, &temp);
		if (event_record.EventType == MOUSE_EVENT) {
			mouse_event_proc(event_record.Event.MouseEvent);//处理鼠标事件
		}
		else if (KEY_DOWN(VK_ESCAPE)) {
			save_map();
			break;
		}
	}
}

void _MAP::mouse_event_proc(MOUSE_EVENT_RECORD mouse_e)
{
	if (mouse_e.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
		int mouse_x = mouse_e.dwMousePosition.X;
		int mouse_y = mouse_e.dwMousePosition.Y;
		if (KEY_DOWN('Q')) {//Q键按住并且鼠标左键点击画墙
			c_map[mouse_y][mouse_x / 2] = MAP_WALL_ICO;
			print_some_in(mouse_x / 2, mouse_y, WALL_ICO, WALL_COLOR);
		}
		if (KEY_DOWN('W')) {//W按住并点击
			c_map[mouse_y][mouse_x / 2] = MAP_GRASS_ICO;
			print_some_in(mouse_x / 2, mouse_y, GRASS_ICO, GRASS_COLOR);
		}
		if (KEY_DOWN('E')) {//E按住并点击
			c_map[mouse_y][mouse_x / 2] = MAP_SAND_ICO;
			print_some_in(mouse_x / 2, mouse_y, SAND_ICO, SAND_COLOR);
		}
		if (KEY_DOWN('R')) {//R按住并点击
			c_map[mouse_y][mouse_x / 2] = MAP_REAL_WALL_ICO;
			print_some_in(mouse_x / 2, mouse_y, TANK_ICO, REAL_WALL_COLOR);
		}
		if (KEY_DOWN('F')) {//F按住并点击
			c_map[mouse_y][mouse_x / 2] = MAP_WATER_ICO;
			print_some_in(mouse_x / 2, mouse_y, WATER_ICO, WATER_COLOR);
		}
	}
	else if (mouse_e.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
		c_map[mouse_e.dwMousePosition.Y][mouse_e.dwMousePosition.X / 2]
			= MAP_ICO;//右键擦除
		print_some_in(
			mouse_e.dwMousePosition.X / 2,
			mouse_e.dwMousePosition.Y, "  ");
	}
	else {//右菜单栏
		print_some_in(RIGHT_LINEX + 7, RIGHT_LINEY + 40, "                 ");
		print_some_in(RIGHT_LINEX + 7, RIGHT_LINEY + 40, "X:");
		print_some_in(RIGHT_LINEX + 8, RIGHT_LINEY + 40, mouse_e.dwMousePosition.X);
		print_some_in(RIGHT_LINEX + 10, RIGHT_LINEY + 40, "Y:");
		print_some_in(RIGHT_LINEX + 11, RIGHT_LINEY + 40, mouse_e.dwMousePosition.Y);
	}
}

void _MAP::add_box()//保证边框
{
	for (size_t x = 0; x < 60; x++)
	{
		c_map[0][x] = MAP_REAL_WALL_ICO;
		print_some_in(x, 0, WALL_ICO, REAL_WALL_COLOR);
	}
	for (size_t x = 0; x < 60; x++)
	{
		c_map[59][x] = MAP_REAL_WALL_ICO;
		print_some_in(x, 59, WALL_ICO, REAL_WALL_COLOR);
	}
	for (size_t y = 0; y < 60; y++)
	{
		c_map[y][0] = MAP_REAL_WALL_ICO;
		print_some_in(0, y, WALL_ICO, REAL_WALL_COLOR);
	}
	for (size_t y = 0; y < 60; y++)
	{
		c_map[y][59] = MAP_REAL_WALL_ICO;
		print_some_in(59, y, WALL_ICO, REAL_WALL_COLOR);
	}
}

int& _MAP::get_score()
{
	return player_score;
}

void _MAP::change_map(COORD pos, char ico)
{
	if(pos.X<81&&pos.X>=0&&
		pos.Y<61&&pos.Y>=0)
	c_map[pos.Y][pos.X] = ico;//根据传入值更改地图位置
}

