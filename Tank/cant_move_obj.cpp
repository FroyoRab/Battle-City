#include "cant_move_obj.h"
#include "func.h"


bool _MAP::did_in_obj(int x, int y, char ICO)
{
	//�жϵ�ͼ��������Ƿ���ICO�������
	if (c_map[y][x] == ICO)
		return true;
	else return false;
}

void _MAP::get_map_in_file(int select)
{
	using std::cout;
	using std::endl;
	FILE* pfile;
	//���ݹؿ��򿪵�ͼ
	switch (select)
	{
	default:
	case 1: {
		if (fopen_s(&pfile, "map\\map_level1.txt", "rb")) {
			cout << "���ļ�ʧ�ܣ����õ�ͼ" << endl;
			Sleep(200);
			init_map();
		}break; }
	case 2: {
		if (fopen_s(&pfile, "map\\map_level2.txt", "rb")) {
			cout << "���ļ�ʧ�ܣ����õ�ͼ" << endl;
			Sleep(200);
			init_map();
		}break; }
	case 3: {
		if (fopen_s(&pfile, "map\\map_level3.txt", "rb")) {
			cout << "���ļ�ʧ�ܣ����õ�ͼ" << endl;
			Sleep(200);
			init_map();
			
		}break; }
	case 4: {
		if (fopen_s(&pfile, "map\\map_level4.txt", "rb")) {
			cout << "���ļ�ʧ�ܣ����õ�ͼ" << endl;
			Sleep(200);
			init_map();
			
		}break; }
	case 5: {
		if (fopen_s(&pfile, "map\\map_level5.txt", "rb")) {
			cout << "���ļ�ʧ�ܣ����õ�ͼ" << endl;
			Sleep(200);
			init_map();
			
		}break; }
	case 6: {
		if (fopen_s(&pfile, "map.txt", "rb")) {
			cout << "���ļ�ʧ�ܣ����õ�ͼ" << endl;
			Sleep(200);
			init_map();
		}break; }
	}
	if (pfile != nullptr) {//�ɹ��򿪺�
		fread_s(&c_map, sizeof(c_map), sizeof(c_map), 1, pfile);
		fclose(pfile);
	}
	else {//���ļ�ʧ��
		cout << "���ļ�ʧ��" << endl;
		system("pause");

	}

}

void _MAP::print_map()
{

	for (int y = 0; y <= 60; y++)
	{
		for (int x = 0; x <= 80; x++)//��ӡǽ��Ͳ�
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
	add_box();//��ӡ���
	print_some_in(28, 56, "���嗀", 0xf4);//��ӡ���ϼ�
	print_some_in(28, 57, "������", 0xf4);
	print_some_in(28, 58, "������", 0xf4);
}

void _MAP::save_map()
{
	//�����ͼ
	using std::cout;
	using std::endl;
	FILE* pfile;
	add_box();
	for (size_t y = 0; y < 60; y++)
	{
		c_map[y][0] = MAP_WALL_ICO;
	}
	fopen_s(&pfile, "map.txt", "wb");
	if (pfile == nullptr)cout << "���ļ�ʧ��";
	else {
		fwrite(c_map, sizeof(c_map), 1, pfile);
		fclose(pfile);
	}
}

void _MAP::init_map()
{
	//���õ�ͼ
	system("cls");
	system("copy /Y map_back.txt map.txt");//�������ļ��������е�ͼ
	save_map();
	print_some_in(WINDOW_X / 2 - 10, WINDOW_Y / 2,
		"���õ�ͼ������ɹ���");
}

void _MAP::clear_one(int x, int y,char side)
{
	//�����ͼ�ϵ�һ����
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
	//�༭��ͼ
	system("cls");
	//��ӡ�߿�
	pr_rightline(0);
	get_map_in_file(6);
	print_map();
	HANDLE std_in_handle = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(std_in_handle, ENABLE_MOUSE_INPUT);
	//�����������

	INPUT_RECORD event_record = { 0 };
	DWORD temp;
	while (1)
	{
		//��ȡ����̨����
		ReadConsoleInput(std_in_handle, &event_record, 1, &temp);
		if (event_record.EventType == MOUSE_EVENT) {
			mouse_event_proc(event_record.Event.MouseEvent);//��������¼�
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
		if (KEY_DOWN('Q')) {//Q����ס���������������ǽ
			c_map[mouse_y][mouse_x / 2] = MAP_WALL_ICO;
			print_some_in(mouse_x / 2, mouse_y, WALL_ICO, WALL_COLOR);
		}
		if (KEY_DOWN('W')) {//W��ס�����
			c_map[mouse_y][mouse_x / 2] = MAP_GRASS_ICO;
			print_some_in(mouse_x / 2, mouse_y, GRASS_ICO, GRASS_COLOR);
		}
		if (KEY_DOWN('E')) {//E��ס�����
			c_map[mouse_y][mouse_x / 2] = MAP_SAND_ICO;
			print_some_in(mouse_x / 2, mouse_y, SAND_ICO, SAND_COLOR);
		}
		if (KEY_DOWN('R')) {//R��ס�����
			c_map[mouse_y][mouse_x / 2] = MAP_REAL_WALL_ICO;
			print_some_in(mouse_x / 2, mouse_y, TANK_ICO, REAL_WALL_COLOR);
		}
		if (KEY_DOWN('F')) {//F��ס�����
			c_map[mouse_y][mouse_x / 2] = MAP_WATER_ICO;
			print_some_in(mouse_x / 2, mouse_y, WATER_ICO, WATER_COLOR);
		}
	}
	else if (mouse_e.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
		c_map[mouse_e.dwMousePosition.Y][mouse_e.dwMousePosition.X / 2]
			= MAP_ICO;//�Ҽ�����
		print_some_in(
			mouse_e.dwMousePosition.X / 2,
			mouse_e.dwMousePosition.Y, "  ");
	}
	else {//�Ҳ˵���
		print_some_in(RIGHT_LINEX + 7, RIGHT_LINEY + 40, "                 ");
		print_some_in(RIGHT_LINEX + 7, RIGHT_LINEY + 40, "X:");
		print_some_in(RIGHT_LINEX + 8, RIGHT_LINEY + 40, mouse_e.dwMousePosition.X);
		print_some_in(RIGHT_LINEX + 10, RIGHT_LINEY + 40, "Y:");
		print_some_in(RIGHT_LINEX + 11, RIGHT_LINEY + 40, mouse_e.dwMousePosition.Y);
	}
}

void _MAP::add_box()//��֤�߿�
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
	c_map[pos.Y][pos.X] = ico;//���ݴ���ֵ���ĵ�ͼλ��
}

