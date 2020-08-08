#include "AI_tank.h"
#include "func.h"
#define SAND_G 5

//NODE 构造函数
NODE::NODE(int h, int g,
	int pos_x, int pos_y,
	NODE* father_NODE)
	: H(h), G(g)
{
	node_pos.X = pos_x;
	node_pos.Y = pos_y;
	F = H + G;
	father_node = father_NODE;
	if (father_node != NULL) {
		//根据父节点的位置计算此点side
		change_side();
	}
}

void NODE::change_side()
{
	//根据父节点计算此点方向
	int x_diffent = node_pos.X - father_node->node_pos.X;
	int y_diffent = node_pos.Y - father_node->node_pos.Y;
	switch (x_diffent) {
	case 1:node_side = RIGHT; break;
	case -1:node_side = LEFT; break;
	default: {
		switch (y_diffent) {
		case 1:node_side = DOWN; break;
		case -1:node_side = UP; break;
		}
	}
	}
}


//构造函数
A_star::A_star(COORD Start_pos, COORD End_pos) :
	start_pos(Start_pos), end_pos(End_pos) {}


void A_star::_init()
{
	line_list.clear();
	vector<NODE>().swap(line_list);

	NODE* node_temp = new NODE((abs(start_pos.X - end_pos.X) +
		abs(start_pos.X - end_pos.X)),//H值
		close_list.size(),//G值
		start_pos.X,//位置
		start_pos.Y,
		NULL//父节点地址
	);
	close_list.push_back(node_temp);
	//将开始点送入close_list
}


//open_list增加
void A_star::add_open_list()
{
	//close_list的长度
	int clist_size = close_list.size();
	//close_list最后一个的引用
	NODE& last_close =
		*close_list[close_list.size() - 1];

	const NODE need_add_node
		= *close_list[clist_size - 1];
	//获取close列表最后一个
	for (int x_temp = -1; x_temp <= 1; x_temp += 2)
	{
		bool do_while = true;//用于在循环内跳出外循环
		if (need_add_node.node_pos.X >= WINDOW_X * 2
			|| need_add_node.node_pos.Y >= WINDOW_Y)
			continue;
		if (need_add_node.node_pos.X + x_temp <= 0
			|| need_add_node.node_pos.Y <= 0)
			continue;
		//将周围四格加入open_list
		if (!tank_map.did_in_obj(
				need_add_node.node_pos.X + x_temp,
				need_add_node.node_pos.Y,
				MAP_REAL_WALL_ICO)
			) {

			for (int inx_y_temp = -1; inx_y_temp <= 1; inx_y_temp++)
			{
				for (int temp_x = -1; temp_x <= 1; temp_x++)
				{
					if (tank_map.did_in_obj(
						need_add_node.node_pos.X + x_temp + temp_x,
						need_add_node.node_pos.Y + inx_y_temp,
						MAP_WALL_ICO)
						|| //加入时判断是否是墙壁
						tank_map.did_in_obj(
							need_add_node.node_pos.X + x_temp + temp_x,
							need_add_node.node_pos.Y + inx_y_temp,
							MAP_REAL_WALL_ICO)
						||//加入时判断是否是钢墙
						tank_map.did_in_obj(
							need_add_node.node_pos.X + x_temp + temp_x,
							need_add_node.node_pos.Y + inx_y_temp,
							MAP_WATER_ICO)
						)//加入时判断是否是水
					{
						do_while = false;
						break;
					}
				}
				if (do_while == false)
					break;
			}
			if (do_while == false)
				continue;


			//或者是否已经在close_list内，是的话跳过。 
			for (size_t i = 0; i < clist_size; i++)
			{
				if (need_add_node.node_pos.X + x_temp
					== close_list[i]->node_pos.X
					&&
					need_add_node.node_pos.Y
					== close_list[i]->node_pos.Y)
					do_while = false;
			}
			if (do_while == false)
				continue;

			//不是的话，判断是否已经在open_list内，
			for (size_t temp = 0;
				temp < open_list.size();
				temp++)
			{
				if (need_add_node.node_pos.X + x_temp
					== open_list[temp]->node_pos.X
					&&
					need_add_node.node_pos.Y
					== open_list[temp]->node_pos.Y) {

					//是的话判断G值是否比当前方格小，
					if (open_list[temp]->G <
						last_close.G + 1) {
						NODE* tempnode = new NODE(*open_list[temp]);
						close_list.push_back(tempnode);
						//是的话将当前方格父类变为那个方格，重新计算G
						last_close.father_node =
							close_list[close_list.size() - 1];

						if (tank_map.did_in_obj(
							last_close.node_pos.X,
							last_close.node_pos.Y,
							MAP_SAND_ICO
						)) {//如果是沙漠的话，增加代价值
							last_close.G
								= last_close.father_node->G + 1 + SAND_G;
						}
						else {//不是的话，按照夫节点计算代价值
							last_close.G
								= last_close.father_node->G + 1;
						}
						last_close.change_side();//更改方向

					}
					do_while = false;
					break;
				}
			}
			if (do_while == false)
				continue;

			//都不是的话，加入open_list
			NODE* node_temp = new NODE(
				(abs(
					need_add_node.node_pos.X + x_temp
					-
					end_pos.X)
					+ abs(need_add_node.node_pos.Y - end_pos.Y)),
				need_add_node.G + 1,//G值
				need_add_node.node_pos.X + x_temp,
				need_add_node.node_pos.Y,
				&last_close
			);
			if (tank_map.did_in_obj(
				node_temp->node_pos.X,
				node_temp->node_pos.Y,
				MAP_SAND_ICO
			)) {
				node_temp->G += SAND_G;
			}
			open_list.push_back(node_temp);
		}
	}

	//Y轴确认，与X一样的……
	for (int y_temp = -1; y_temp <= 1; y_temp += 2)
	{
		bool do_while = true;
		if (need_add_node.node_pos.X <= 0
			|| need_add_node.node_pos.Y + y_temp <= 0)
			continue;
		if (need_add_node.node_pos.X >= WINDOW_X * 2
			|| need_add_node.node_pos.Y >= WINDOW_Y)
			continue;
		//将周围四格加入open_list,加入时判断是否是墙壁，
		if (!tank_map.did_in_obj(
				need_add_node.node_pos.X,
				need_add_node.node_pos.Y + y_temp,
				MAP_REAL_WALL_ICO))
		{

			for (int iny_x_temp = -1; iny_x_temp <= 1; iny_x_temp++)
			{
				for (int temp_y = -1; temp_y <= 1; temp_y++)
				{
					if (tank_map.did_in_obj(
						need_add_node.node_pos.X + iny_x_temp,
						need_add_node.node_pos.Y + y_temp + temp_y,
						MAP_WALL_ICO)
						||
						tank_map.did_in_obj(
							need_add_node.node_pos.X + iny_x_temp,
							need_add_node.node_pos.Y + y_temp + temp_y,
							MAP_REAL_WALL_ICO)
						||
						tank_map.did_in_obj(
							need_add_node.node_pos.X + iny_x_temp,
							need_add_node.node_pos.Y + y_temp + temp_y,
							MAP_WATER_ICO)
						)
					{
						do_while = false;
						break;
					}
				}
				if (do_while == false)
					break;
			}
			if (do_while == false)
				continue;


			//或者是否已经在close_list内，是的话跳过。 
			for (size_t i = 0; i < clist_size; i++)
			{
				if (need_add_node.node_pos.X
					== close_list[i]->node_pos.X
					&&
					need_add_node.node_pos.Y + y_temp
					== close_list[i]->node_pos.Y)
					do_while = false;
			}
			if (do_while == false)
				continue;

			//不是的话，判断是否已经在open_list内，
			for (size_t temp = 0; temp < open_list.size(); temp++)
			{
				if (need_add_node.node_pos.X
					== open_list[temp]->node_pos.X
					&&
					need_add_node.node_pos.Y + y_temp
					== open_list[temp]->node_pos.Y) {

					//是的话判断G值是否比当前方格小，
					if (open_list[temp]->G
						<
						last_close.G + 1) {
						NODE* tempnode = new NODE(*open_list[temp]);
						close_list.push_back(tempnode);
						//是的话将当前方格父类变为那个方格，重新计算G
						last_close.father_node =
							close_list[close_list.size() - 1];
						if (tank_map.did_in_obj(
							last_close.node_pos.X,
							last_close.node_pos.Y,
							MAP_SAND_ICO
						)) {
							last_close.G
								= last_close.father_node->G + 1 + SAND_G;
						}

						else {
							last_close.G
								= last_close.father_node->G + 1;
						}
						last_close.change_side();
					}
					do_while = false;
					break;
				}
			}
			if (do_while == false)
				continue;

			//都不是的话，加入open_list
			NODE* node_temp = new NODE(
				(abs(need_add_node.node_pos.X - end_pos.X)
					+ abs(need_add_node.node_pos.Y + y_temp
						- end_pos.Y)),
				need_add_node.G + 1,//G值
				need_add_node.node_pos.X,
				need_add_node.node_pos.Y + y_temp,
				&last_close
			);
			if (tank_map.did_in_obj(
				node_temp->node_pos.X,
				node_temp->node_pos.Y,
				MAP_SAND_ICO)) {
				node_temp->G += SAND_G;
			}

			open_list.push_back(node_temp);

		}
	}

}

//查找最小F值的open_list node 返回下标
int A_star::find_min_F()
{
	if (open_list.size() == 0)
		return -1;

	int temp = 0;
	int F_temp = open_list[0]->F;
	for (int i = 0; i < open_list.size(); i++)
	{
		if (open_list[i]->F <= F_temp) {//<=保证更新的节点优先选择
			temp = i;
			F_temp = open_list[i]->F;
		}
	}
	return temp;//返回找到的下标

}

//将open_list中F最小的放入close_list中
bool A_star::move_to_close_list()
{
	int min_F = find_min_F();
	if (min_F == -1)
		return true;

	close_list.push_back(open_list[min_F]);
	open_list.erase(open_list.begin() + min_F);
	//放入close_list并且删除open_list中的节点
	return false;
}

NODE* A_star::close_list_last()
{
	return (close_list[close_list.size() - 1]);
	//获取close_lsit最后一个节点
}

vector<NODE> A_star::pr_all_path()
{
	//打印整个路径，现用作将整个路径输出
	//引用传递之前导致了内存泄漏_(:_」∠)_，在外面不太方便delete；
	NODE* node_temp = close_list_last();
	while (node_temp->father_node)
	{
		/*print_some_in(
			node_temp->node_pos.X,
			node_temp->node_pos.Y,
			"M", 0xfC);*/
		line_list.push_back(*node_temp);
		node_temp = node_temp->father_node;
	}
	//用node_temp临时存一下通过父节点回溯的路径；

	for (size_t i = 0; i < open_list.size(); i++)
	{
		delete open_list[i];
	}
	for (size_t i = 0; i < close_list.size(); i++)
	{
		delete close_list[i];
	}//👆先释放，后删除👇
	open_list.clear();
	close_list.clear();
	vector<NODE*>().swap(open_list);
	vector<NODE*>().swap(close_list);

	return line_list;
}

int& A_star::get_find_time()
{
	return find_time;
	//获得查找频率
}
