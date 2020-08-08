#include "menu_class.h"
#include "func.h"

//����ұ߲˵���
void MENU::clear_right()
{
	for (int x = RIGHT_LINEX; x < RIGHT_LINEX + 19; x++) {
		for (int y = 24; y < 40; y++) {
			print_some_in(x, y, "  ");
		}
	}
}

//�����ж�
void MENU::key_press()
{

	print_some_in(RIGHT_LINEX, RIGHT_LINEY + 42, "���㰴�ɰ��϶�����");
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

	RECT rect_pos;//��������ṹ��
	HWND hw_handle = GetForegroundWindow();//��ȡǰ�������
	GetWindowRect(hw_handle, &rect_pos);//��ȡ��ǰǰ������ʹ�������

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
				&&//�ж��������Ƿ��£�����û���ƶ�
				event_record.Event.MouseEvent.dwEventFlags
				!= MOUSE_MOVED)
			{//��¼û���ƶ���ʱ�������λ��
				x_differ =
					event_record.Event.MouseEvent.dwMousePosition.X*4
					- rect_pos.left;
				y_differ =
					event_record.Event.MouseEvent.dwMousePosition.Y*4
					- rect_pos.top;
			}
			if (event_record.Event.MouseEvent.dwButtonState
				== FROM_LEFT_1ST_BUTTON_PRESSED
				&&//���������²����϶��ˣ����ݸղż�¼�����λ������������ĻӦ���ƶ��ľ���
				event_record.Event.MouseEvent.dwEventFlags
				== MOUSE_MOVED)
			{
				rect_pos.left =
					event_record.Event.MouseEvent.dwMousePosition.X*4
					- x_differ;
				rect_pos.top =
					event_record.Event.MouseEvent.dwMousePosition.Y*4
					- y_differ;
				MoveWindow(hw_handle,//�ƶ���Ļ
					rect_pos.left,
					rect_pos.top,
					1305,
					980, true);
				SetConsoleCursorInfo(out_handle, &cursor_info);
			}
		}
#pragma endregion ʹ������϶�����

		if (event_record.EventType == KEY_EVENT) {//����ǰ����¼�
			if (KEY_DOWN(VK_LEFT)) {//���������л����ĵ������б�ֵ
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
			if (KEY_DOWN(VK_RETURN)) {//������˻س������������б�ֵ
				PlaySoundA("sound\\menu\\menu_click.wav", 
					NULL, SND_ASYNC | SND_NODEFAULT);
				break;
			}
			if (KEY_DOWN(VK_ESCAPE)) {//escֱ���˳�
				exit(0);
			}

		}
		change_list();//�ж����°���
	}
}

void MENU::change_list()
{

	if (KEY_DOWN(VK_DOWN)) {
		while (KEY_DOWN(VK_DOWN));
		pr_choose(0);//��������б��������б��ȿ����������ֵ
		if (list == &out_choose && *list < _countof(out_list) - 1) {
			*list += 1;
			pr_menu();
		}//�������б��ȿ������ֵ
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
		pr_choose();//��ӡ��ѡ��ı����������ڻ��Զ������һ������
	}
	else {
		pr_choose(1, false);
	}
}

//�޵�ɫ��ӡ���ⲿ�˵�
void MENU::pr_menu()
{
	clear_right();//����ұߣ�����λ����ɵĲ���
	//�����б�ֵ��ӡ����˵�
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


//��ӡѡ��ĵ�ɫ
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
		for (int x = MENU_X + 6; x < 59; x++)//ɾ������
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
		for (int x = MENU_X + 6; x < 58; x++)//��ӡ����
		{
			print_some_in(x, pos[out_choose][1], "����");
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
