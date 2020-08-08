#include "menu_class.h"
#include "func.h"

//清空右边菜单栏
void MENU::clear_right()
{
	for (int x = RIGHT_LINEX; x < RIGHT_LINEX + 19; x++) {
		for (int y = 24; y < 40; y++) {
			print_some_in(x, y, "  ");
		}
	}
}

//按键判断
void MENU::key_press()
{

	print_some_in(RIGHT_LINEX, RIGHT_LINEY + 42, "鼠标点按可按拖动窗口");
	pr_menu();
	PlaySoundA("sound\\menu\\stat_menu.wav", NULL, SND_ASYNC | SND_NODEFAULT);
	pr_choose(1, false);
	HANDLE STD_IN_HANDLE = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(out_handle, &cursor_info);
	cursor_info.bVisible = false;
	INPUT_RECORD event_record = { 0 };
	DWORD temp;

	RECT rect_pos;//窗口坐标结构体
	HWND hw_handle = GetForegroundWindow();//获取前景句柄？
	GetWindowRect(hw_handle, &rect_pos);//获取当前前景句柄和窗口坐标

	int x_differ = 0;
	int y_differ = 0;
	while (true)
	{
#pragma region mouse_move_window

		SetConsoleMode(STD_IN_HANDLE, ENABLE_MOUSE_INPUT| ENABLE_EXTENDED_FLAGS);
		ReadConsoleInput(STD_IN_HANDLE, &event_record, 1, &temp);
		if (event_record.EventType == MOUSE_EVENT) {
			if (event_record.Event.MouseEvent.dwButtonState
				== FROM_LEFT_1ST_BUTTON_PRESSED
				&&//判断鼠标左键是否按下，并且没有移动
				event_record.Event.MouseEvent.dwEventFlags
				!= MOUSE_MOVED)
			{//记录没有移动的时候的鼠标的位置
				x_differ =
					event_record.Event.MouseEvent.dwMousePosition.X*4
					- rect_pos.left;
				y_differ =
					event_record.Event.MouseEvent.dwMousePosition.Y*4
					- rect_pos.top;
			}
			if (event_record.Event.MouseEvent.dwButtonState
				== FROM_LEFT_1ST_BUTTON_PRESSED
				&&//如果左键按下并且拖动了，根据刚才记录的鼠标位置推算现在屏幕应该移动的距离
				event_record.Event.MouseEvent.dwEventFlags
				== MOUSE_MOVED)
			{
				rect_pos.left =
					event_record.Event.MouseEvent.dwMousePosition.X*4
					- x_differ;
				rect_pos.top =
					event_record.Event.MouseEvent.dwMousePosition.Y*4
					- y_differ;
				MoveWindow(hw_handle,//移动屏幕
					rect_pos.left,
					rect_pos.top,
					1305,
					980, true);
				SetConsoleCursorInfo(out_handle, &cursor_info);
			}
		}
#pragma endregion 使用鼠标拖动窗口

		if (event_record.EventType == KEY_EVENT) {//如果是按键事件
			if (KEY_DOWN(VK_LEFT)) {//根据左右切换更改的内外列表值
				if (list != &out_choose) {
					*list = 1;
					list = &out_choose;
					pr_menu();
					PlaySoundA("sound\\menu\\menu_change.wav",
						NULL, SND_ASYNC | SND_NODEFAULT);
				}
			}
			if (KEY_DOWN(VK_RIGHT)) {
				if (list != &in_choose && *list < 3) {
					list = &in_choose;
					pr_menu();
					PlaySoundA("sound\\menu\\menu_change.wav",
						NULL, SND_ASYNC | SND_NODEFAULT);
				}
			}
			if (KEY_DOWN(VK_RETURN)) {//如果按了回车，返回内外列表值
				PlaySoundA("sound\\menu\\menu_click.wav", 
					NULL, SND_ASYNC | SND_NODEFAULT);
				break;
			}
			if (KEY_DOWN(VK_ESCAPE)) {//esc直接退出
				exit(0);
			}

		}
		change_list();//判断上下按键
	}
}

void MENU::change_list()
{

	if (KEY_DOWN(VK_DOWN)) {
		while (KEY_DOWN(VK_DOWN));
		pr_choose(0);//如果是外列表，根据外列表长度控制数字最大值
		if (list == &out_choose && *list < _countof(out_list) - 1) {
			*list += 1;
			pr_menu();
		}//根据内列表长度控制最大值
		else if (list == &in_choose && *list <= _countof(in_list) - 2)
			*list += 1;
		PlaySoundA("sound\\menu\\menu_change.wav",
			NULL, SND_ASYNC | SND_NODEFAULT);
	}
	if (KEY_DOWN(VK_UP)) {
		while (KEY_DOWN(VK_UP));
		pr_choose(0);
		if (*list > 1) {
			*list -= 1;
			if (list == &out_choose)
				pr_menu();
		}
		PlaySoundA("sound\\menu\\menu_change.wav",
			NULL, SND_ASYNC | SND_NODEFAULT);
	}
	if (list == &in_choose) {
		pr_choose();//打印被选择的背景，函数内会自动清楚上一个背景
	}
	else {
		pr_choose(1, false);
	}
}

//无底色打印内外部菜单
void MENU::pr_menu()
{
	clear_right();//清空右边，避免位移造成的残留
	//根据列表值打印内外菜单
	for (int y = 1; y <= _countof(out_list) - 1; y++)
	{
		print_some_in(MENU_X, pos[1][y],
			out_list[y]);
	}
	for (int y = 1; y < _countof(in_list[out_choose]); y++)
	{
		print_some_in(RIGHT_LINEX, pos[out_choose][y], in_list[out_choose][y]);
	}
}


//打印选择的底色
void MENU::pr_choose(int choose, bool bool_in)
{
	print_some_in(MENU_X, 22, out_list[0]);
	switch (choose)
	{
	case 0: {
		print_some_in(RIGHT_LINEX, pos[out_choose][in_choose],
			in_list[out_choose][in_choose]);
		print_some_in(MENU_X, pos[out_choose][1],
			out_list[out_choose]);
		for (int x = MENU_X + 6; x < 59; x++)//删除连线
		{
			print_some_in(x, pos[out_choose][1], "  ");
		}
		break;
	}
	case 1: {
		if (bool_in) {
			print_some_in(RIGHT_LINEX, pos[out_choose][in_choose],
				in_list[out_choose][in_choose], 0x70);
		}
		print_some_in(MENU_X, pos[out_choose][1],
			out_list[out_choose], 0x70);
		for (int x = MENU_X + 6; x < 58; x++)//打印连线
		{
			print_some_in(x, pos[out_choose][1], "——");
		}
		break;
	}
	}
}

void MENU::get_choose(int& _out_choose, int& _out_choose2)
{
	_out_choose = out_choose;
	_out_choose2 = in_choose;
}
