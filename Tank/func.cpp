#include "func.h"
#include "cant_move_obj.h"
//
//在x,y用color颜色打印
//template<typename T>


//初始化程序
void _init() {
	HWND hwnd = GetConsoleWindow();
	LONG Style;	//窗口风格
	Style = GetWindowLong(hwnd, GWL_STYLE);	 // 得到窗口风格   
	Style = Style & ~WS_CAPTION;			 //去掉标题栏
	SetWindowLong(hwnd, GWL_STYLE, Style);	 //为窗口设置新的风格
	HANDLE STD_IN_HANDLE = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(STD_IN_HANDLE, ENABLE_MOUSE_INPUT| ENABLE_EXTENDED_FLAGS);
	HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
	char ctemp[50] = { "mode con:cols=" };
	char ctemp1[20] = { " lines=" };
	char ctemp2[20] = { 0 };
	_itoa_s(WINDOW_X * 2, ctemp2, 10);
	strcat_s(ctemp, 50, ctemp2);
	strcat_s(ctemp, 50, ctemp1);
	_itoa_s(WINDOW_Y, ctemp2, 10);
	strcat_s(ctemp, 50, ctemp2);
	system(ctemp);
	//设置窗口大小
	system("color f0");

	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(outhandle, &cursor_info);
	cursor_info.bVisible = false;
	SetConsoleCursorInfo(outhandle, &cursor_info);
	//隐藏光标

	srand(time(0));
	//随机种子确定

	tank_list.clear();
	tank_list_firends.clear();
	bullet_list.clear();
	do_while = true;
	_AI_TANK::get_ai_count() = 6;
}

//获取指定大小随机数
int get_randnum(int min, int max) {
	int ntemp = min + (rand() % (max - min + 1));
	return (ntemp);
}

//子弹射出
void tank_fire(COORD tank_pos, int side, WORD ncolor, short choise) {
	_BULLET bullet;
	bullet_list.push_back(bullet);
	
	static int id = 0;//子弹ID
	bullet_list[bullet_list.size() - 1].get_id()= id;
	id++;

	//根据敌友区别初始化子弹
	switch (choise) {
	case 0: {
		bullet_list[bullet_list.size() - 1]._init(tank_pos, side, ncolor);
		break;
	}
	case 1: {
		bullet_list[bullet_list.size() - 1]._init(tank_pos, side, ncolor, false);
		break;
	}
	}
	bullet_list[bullet_list.size() - 1].show();
}

//创建Ai并且初始化
void creat_ai() {//创建AI，并自动初始化
	_AI_TANK ai_tank1;
	tank_list.push_back(ai_tank1);
	tank_list[tank_list.size() - 1]._init(tank_list.size(), 0xf0);
}

//读档
bool load_save()
{
	FILE* pfile;
	fopen_s(&pfile, "save\\save.i", "r+");
	if (pfile != nullptr) {
		tank_list.clear();
		tank_list_firends.clear();
		bullet_list.clear();
		//清空当前数据
		int ntemp_ai_count;
		int ntemp_friends_count;
		int ntemp_map_count;
		//先读取数组大小
		fscanf_s(pfile, "ai:%d", &ntemp_ai_count);
		fscanf_s(pfile, "friends:%d", &ntemp_friends_count);
		fscanf_s(pfile, "map:%d", &_MAP::map_count);
		fread_s(&tank_list, ntemp_ai_count, ntemp_ai_count, 1, pfile);
		fread_s(&tank_list_firends, ntemp_friends_count,
			ntemp_friends_count, 1, pfile);
		//读入数据
		fclose(pfile);
		system("del save\\save.i");
		return true;
	}
	else {//如果没有存档文件
		print_some_in(RIGHT_LINEX, 55, "无存档文件！");
		print_some_in(RIGHT_LINEX, 57, " ");
		system("pause");
		return false;
	}
}

//欢迎界面
void start_form()
{
	system("cls");
	using std::endl;
	using std::cout;
	system("color f8");
	cout << "                                                                                                                                                                " << endl;
	cout << "                                                                                                                                                                " << endl;
	cout << "                                                                                                                                                                " << endl;
	cout << "                    ir;riSa27:                                                                                                                                  " << endl;
	cout << "                 :2MMMMMMMMMMMMW8Xi                                                                                                                             " << endl;
	cout << "              XBMMMMWW0B0B000BB@MMMM8Si                                                                                                                         " << endl;
	cout << "           ,0MMM@BB8Z808BBBB000808BWMMM8i                                                                                                                       " << endl;
	cout << "         .8MM@WBZZ8B@MMMMMMMMMMMWB8880WM@2.                                                                                                                     " << endl;
	cout << "        XMMWW0Za0@MMMMM@M@M@M@MMMMM@B800WMB: ,.                                                                                                                 " << endl;
	cout << "       SM@BWZaBMMM@M@M@M@M@M@M@M@MMMMM080B@@i ,:.:.                                                                                                             " << endl;
	cout << "      ZMWBW2a@M@M@@@M@@@@@M@M@M@M@M@MMMWZ80WMX  ,7WMWX:                                                                                                         " << endl;
	cout << "     8MWBWSZM@W@W@@M@M@M@M@M@M@M@M@M@MMM@ZZ0BM;    i0MMM8r                                                                                                      " << endl;
	cout << "    XMWB@S2@@WW@@@M@M@M@M@M@M@M@M@M@M@MMM@ZZ0WW      ,aMMM2                                                                                                     " << endl;
	cout << "    MMBWZXM@W@W@@M@@@M@M@M@M@M@M@M@M@M@MMM0Z80M;        rWMM0:                                                                                                  " << endl;
	cout << "   ;MBBWr8MWWW@W@@@@M@@@M@M@M@M@M@M@MMMMMMMZ80@a          7WMM7       ,  .                                                                                      " << endl;
	cout << "   SMBB0iM@@WWW@@M@M@M@M@@@M@M@M@M@M@M@MMMM8Z0BB           ,aMM7     SMZXZX                                                                                     " << endl;
	cout << "   2MBWaiMM@@W@@@@@@M@M@M@M@M@M@M@M@MMM@MMM8Z8BW             SM@,    BMWSi:                                                                                     " << endl;
	cout << "   8MBWZ.MW@W@WM@M@M@M@M@M@M@M@M@M@M@M@M@MMZZ0BW   . .        8MZ   XMM0ri        i:i, ;S                                                                       " << endl;
	cout << "   aMBB0 @@W@W@W@@M@M@M@M@M@M@M@M@M@M@M@MMMa88WZ    .   . .   ,M@     X:2MMS,  i77@B2S;SZ::iri:,,,,:i                                                           " << endl;
	cout << "   SMBB@.8MMWWWM@M@M@M@M@M@M@M@M@M@M@M@MMMWaZ0@S   . .   .     @M;     :0@0@aSZZ2S,, .,,.::i:i,,,:::ii;W:                                                       " << endl;
	cout << "    MWBW2:MWWWWWM@M@M@M@M@M@M@M@M@@@M@MMMMZZ80@7.......   .    WMr        i,,rBBZa2,:i::i :,:,:,:,:,i:,2M:                                                      " << endl;
	cout << "    aMBBWraMW@W@W@WM@@@@@M@M@M@M@@@M@MMMM0288Wa,:i,,,:,. .   .:@M;   .     Xr  ZMBX7,:ii::,,,:,:::::,:,,2Mi                                                     " << endl;
	cout << "     MMBWBr0MW@WWW@@M@M@M@M@M@M@@@M@MMMM0288BWr,ii;:i:,.:.. ,raMM  ..       7S  @0ZX::;i::::ii,.::,,;:  ,rS,                                                    " << endl;
	cout << "     iMMBW0XZMM@W@@M@M@M@M@@@M@@@M@MMMM82Z8BBX.;ir;;;i,::,.:S8WMa :i:::,,i   ir 8WBX,7,,,7...i.,,    . ,,.i;                                                    " << endl;
	cout << "      ;WMBWB2SWMM@M@M@M@M@M@M@M@MMMMM02aZ8BZi,rr777;;iii:.;a0W@B:.r;;ii:SX.  i, MMM@i ..iii;7Xr7SSXSZ22a8ZS                                                     " << endl;
	cout << "        8MWB0ZXa0MMMMMMMMMMMMMMMMM@8XSZ000ar;XXX7riii:.,:S88W@Wr.;iii;:r7,  iSrMMMMMS82BW@0W@Wa88Z2a22SS2S                                                      " << endl;
	cout << "         XMMWBBaSXa0@MMMMMMMMMMB8SXSZ8B0ZXXXSS27r;7rriXSZ80W0B8 i:::;;rXXX20WWMMM@M@aZ0808B08a0Z2XSS222SS:       ..     .                                       " << endl;
	cout << "          ,2WMMWB82SS22ZZ8ZZaa2SSaZ000aXX2ZZ2aSSXX7XSZZZ8BW@; :irXZ0Wa0MMMMMMMMMMMMM28BBBBBBBWB27XXSiii, ,,ii;r;r7ii:iXWMMMW87                                  " << endl;
	cout << "             iZ@MMWBB88ZZaaZZZ8800WB8aS28Z2SXXSXS8aZB80BW0ZSX28WMMMMMM@MMMMMMMMMMMMM@MMBWBWB088BW2i :i;::,i::,i,.     .:;72ZB2.   .ri,.                         " << endl;
	cout << "                iZBMMMMMMM@M@MMMWBB0WMM@8Z800W@W0WBB0BBB0BBMMMMMM@W@BBBBBB8BW80WBB@MZ8WMW@BWZ@MM@MMZ   .   ,     ....          .. ,i 87,;:.i                    " << endl;
	cout << "                    .i7XSXSXSZS.      7B@80ZZa8ZZBBB@WWBWMMWWBBBW@MMW08Z0ZZZZXXrrXZZ2aaZM@r .rXr7;;r, . . .     ..,,::,..    .:,i,;Z@87:: 7B7X2ZS.XM2:          " << endl;
	cout << "                                       X80WBa7i:;B@MW2X28@W88ZZBWMMMM@Z2XSZ0aS77;7rX7X; .,i  ,.    . .,...,..::r;. . ..,..      :r7XXi       ;88MMMM8;,..       " << endl;
	cout << "                                       ;ZSXZB@WZa2B@8SZ800000ZaaZZ8a2X7r287;7i;ZS,::,,i. .::::ii,,::::::iiiii::,,,,        ,;i      .           .i7X, :ii:,     " << endl;
	cout << "                                        rXiX;a@MW8Z0B2aBMZ;;;28Z:...  .iXX::ii::i;:i:ii:,..::::i:i::::,,..,       . ,8SX2W0S0MZ0MMaXaaW8i0WZ,  .     ,..   ,.   " << endl;
	cout << "                                        S2,X2ii708Za00B8Si...iri:,,,i,:::,:,i::,::::i::,i , ..            , ..XM8  .0MBM2Z@BS8Ba0WMMMWM8XaMMMZ              ,.  " << endl;
	cout << "                                        0M:.2i,2WMB8ZZ80,.;77i:7SX;;rSZri7a7,;7:,:,:,:,: ,:. ;;,:S8Xi S8:;W7,78MB   :XXr a8aS8WB0MB2ZMM7i2W@MMB            . ,. " << endl;
	cout << "                                        iMMi2 ,Z@MM@BZBBZ0080SSSZZ0MMMMBZSXi,:aS:,:,i:i:r8MBS8MMZZWMZaMM@raai. :0rM8  .7Xr@ri8M@M@B .7M22BMBWWM8        i   . . " << endl;
	cout << "                                         MMMMS i2ZWMM@WW0ZBZ22Z88S2WM0aX:.,ir;:r:;;:;:;XiX2BX8S@ZZaB888M@, :;Z;.,2WB    7iS2 XB@@MMB; a7WWWB80WMa,rSSZ@MM       " << endl;
	cout << "                                         2MMMM2.XSX2B@M@MBS27r:rZZX,  ..:;::ii::::;7X8MM8WW; XZ8ZrB@Z8BZWM@@rZa,.  Xa 0BZ0MMXXZ0M@MM@@MXXSSSZ0W@MMMM28M00S      " << endl;
	cout << "                                          MM@MMi:2XXaBWM@@Za0B2@MMWi;i ,S2XX77i;;7;i:,SM@MW27.rM8X:S0ZBZ2MMM0  ZBWMM072r.:;i,irXaBWB8@0a2Z0@MMWMBB0BZr2XiZ2     " << endl;
	cout << "                                          BMMMMX 7S7a8Z8WBZ0M@BW8;X7XZSa8ZZZ8ZX;r;7rr;.iMM2a2ZSMMi2:;aM@8WBZ0aBMMM@0@MX ..:irSa2ZaZZ2SZB@MM@MBSariirZiX72MM     " << endl;
	cout << "                                           MMMMMr.:;S8Z8WW0@MZa8XS222Z8000BWBBZX;;rrri. BMZaSZMMM0ZZXZMW7i.  ;;rrSai,7SS280B0088ZaaZWM@@@@@@@M2arX0B8MMMMM      " << endl;
	cout << "                                            MMMMMa  rZZ2BW0a22S088BaZWW88Z82SaBZXiii;i: ;MBBMMMMMMMMZi7;:,iiXX;;7XZZ80WB080ZZZZZ2BBSMMMWWWMMMB0BW@MWZ8BB;       " << endl;
	cout << "                                             MMMMM8  XZZBW8aSSi2MW  X8Ba28Xi7irrX8Srii,, ;XZZB@@MWBMWa2aZ00@@WW@BB88ZZaZa88Z8BW8SBMZZMMMM@S0Waa2XSBMMBa.        " << endl;
	cout << "                                              MMMMM@  SZ0BZX77;;MM r7SWZ22rX2Si;2ZZ8Zrr:;;7XXXX2a222aZ8800W@@@W8ZZ88Z0@W@@@0@MMWZ0M0BM@W@W80MMMMMMMZ7           " << endl;
	cout << "                                              :MMM@M@.:X202Xrr:,ZMZ880aaX7XZ00ZXZBBZrMM8BW82SZS22ZZ0BWBWWBZaX20WM@Z8Z2@MMM@M@M@@B@MWZ@B0WMMMMMWaSi              " << endl;
	cout << "                                               ;MMMMMMX,rZ2X7r. X@8XXXSS8BBZ08MMMMWZSMWBB880WW@@@WBZ2X;.        7MM@B0BZ@MM@MMMMMBMWWMMMMMBX,                   " << endl;
	cout << "                                                rMMM@MMZ:7ri: ,@0Xr2@@W@M@MZiXM@BB00ZX:ZZZ0BZS;:.                7MMMMMMWMMMMMMMMMMMMMZr                        " << endl;
	cout << "                                                 :MMM@MMBX7S28MMMWWZWMMWWBWZ7a0ZZSXSSa:Saa.                          .;2Z@MMM0SX2Sr.                            " << endl;
	cout << "                                                   MMMMMMMMMMMM0MW8BZBW0Z22WX ;;irrZZ0MMS                                                                       " << endl;
	cout << "                                                    MMM@@W@@@W@BM2 XX:ii;;Xa2SZB@MMMMMZ7                                                                        " << endl;
	cout << "                                                     MMM@WW@WWB@WB,r.i708B@MS8MMWWBWMZ                                                                          " << endl;
	cout << "                                                      MMMWWM@WWW@@MWrZMMMWWWXSZS2ZWM2                                                                           " << endl;
	cout << "                                                      :M@@WM@WWMM7XBX882XXS8ZB0WWM@X                                                                            " << endl;
	cout << "                                                       @M@@W@@MM@aXS22Z80BWZB@@WMW                                                                              " << endl;
	cout << "                                                        MMMM@@@MaZBaBMM@WWZWW@@MM.                                                                              " << endl;
	cout << "                                                         0MM@@M88000B@WWB8@@@MM0                                                                                " << endl;
	cout << "                                                          MM@MB800@MWW@WBMMMMMZ                                                                                 " << endl;
	cout << "                                                          iMM@0BM@MMMMMMMMM0X                                                                                   " << endl;
	cout << "                                                           ,WMMMMMMMMWZr.                                                                                       " << endl;
	cout << "                                                             .r::.                                                                                              " << endl;
	cout << "                                                                                                                                                                " << endl;
	while (1) {
		//闪烁封面下面的开始游戏
		print_some_in(WINDOW_X / 2 - 3, WINDOW_Y / 2 + 15,
			"开始游戏  请按任意键继续", 0x8f);
		if (_kbhit())break;
		Sleep(500);
		print_some_in(WINDOW_X / 2 - 3, WINDOW_Y / 2 + 15,
			"                        ", 0xf8);
		if (_kbhit())break;
		Sleep(200);
	}
	system("color f0");
}

//游戏设置
void setting()
{
	int player_speed_temp = 70;
	int ai_speed_temp = 100;
	int a_star_find_temp = 1000;
	//👆默认值设定，获取玩家设置👇
	print_some_in(WINDOW_X - 5, WINDOW_Y, "请输入玩家坦克速度(0-140)：");
	std::cin >> player_speed_temp;
	print_some_in(WINDOW_X - 5, WINDOW_Y, "请输入AI坦克速度(0-200)：");
	std::cin >> ai_speed_temp;
	print_some_in(WINDOW_X - 5, WINDOW_Y, "请输入AI寻路频率(500-1000,0为不寻路)：");
	std::cin >> a_star_find_temp;
	_TANK::get_save_speed() =//计算跟输入数据的差值
		(140 - (player_speed_temp < 140 ? player_speed_temp : 140));
	_AI_TANK::get_save_speed() =
		(200 - (ai_speed_temp < 200 ? ai_speed_temp : 200));
	if (a_star_find_temp == 0) {//如果寻路频率为0 ，将频率设为99999，取消寻路
		A_star::get_find_time() = 999999;
	}
	else {//
		A_star::get_find_time() =
			(2000 - (a_star_find_temp < 2000 ? a_star_find_temp : 2000));
	}
}

//存档
void save()
{
	FILE* pfile;
	fopen_s(&pfile, "save\\save.i", "w+");
	if (pfile != nullptr) {//如果文件打开了
		//先存入数组大小
		fprintf(pfile, "ai:%d",
			tank_list.size() * sizeof(_AI_TANK));
		fprintf(pfile, "friends:%d",
			tank_list_firends.size() * sizeof(_TANK));
		fprintf(pfile, "map:%d", _MAP::map_count);
		//再写数据
		fwrite(&tank_list,
			sizeof(_AI_TANK) * tank_list.size(), 1, pfile);
		fwrite(&tank_list_firends,
			sizeof(_TANK) * tank_list_firends.size(), 1, pfile);
		print_some_in(RIGHT_LINEX, 55, "存档成功！");
	}
	else {
		print_some_in(RIGHT_LINEX, 55, "打开文件失败！");
		exit(1);//直接爆掉
	}
	fclose(pfile);
}