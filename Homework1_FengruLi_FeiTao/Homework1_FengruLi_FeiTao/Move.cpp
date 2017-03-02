#include "Move.h"
extern int GridWorld[MAZESIZE][MAZESIZE];
Move::Move()
{
	num_expand = 0;
	counter = 0;
	do
	{
		start.first = rand() % MAZESIZE;
		start.second = rand() % MAZESIZE;
	} while (GridWorld[start.first][start.second] == 0);  //set a random unblocked grid as start
	GridWorld[start.first][start.second] = 3;
	current = start;

	do
	{
		goal.first = rand() % MAZESIZE;
		goal.first = rand() % MAZESIZE;
	} while (goal == start || GridWorld[goal.first][goal.second] == 0);  //set a random unblocked grid as goal
	GridWorld[goal.first][goal.second] = 3;
	for (int row_cnt = 0; row_cnt < MAZESIZE; row_cnt++)   //initialize the grid world in agent's mind
		for (int col_cnt = 0; col_cnt < MAZESIZE; col_cnt++)
		{
			AgentWorld[row_cnt][col_cnt].set_f(0);
			AgentWorld[row_cnt][col_cnt].set_g(0);
			AgentWorld[row_cnt][col_cnt].set_h(0); 
			AgentWorld[row_cnt][col_cnt].set_h_new(INT_MAX);
			AgentWorld[row_cnt][col_cnt].set_position(pair<int, int>(row_cnt, col_cnt));
			AgentWorld[row_cnt][col_cnt].set_from(pair<int, int>(row_cnt, col_cnt));
		}
	AgentWorld[start.first][start.second].set_g(0);
	AgentWorld[start.first][start.second].set_h(abs(goal.first - start.first + goal.second - start.second));
	AgentWorld[start.first][start.second].update_f();
	Openlist.insert(AgentWorld[start.first][start.second],0);
	AgentWorld[goal.first][goal.second].set_g(INT_MAX);
	AgentWorld[goal.first][goal.second].update_f();
}

Move::~Move()
{
	Openlist.clear();
}

void Move::reinitialize()
{
	num_expand = 0;
	counter = 0;
	current = start;
	for (int row_cnt = 0; row_cnt < MAZESIZE; row_cnt++)   //initialize the grid world in agent's mind
		for (int col_cnt = 0; col_cnt < MAZESIZE; col_cnt++)
		{
			AgentWorld[row_cnt][col_cnt].set_f(0);
			AgentWorld[row_cnt][col_cnt].set_g(0);
			AgentWorld[row_cnt][col_cnt].set_h(0);
			AgentWorld[row_cnt][col_cnt].set_h_new(INT_MAX);
			AgentWorld[row_cnt][col_cnt].set_search(0);
			AgentWorld[row_cnt][col_cnt].set_position(pair<int, int>(row_cnt, col_cnt));
			AgentWorld[row_cnt][col_cnt].set_from(pair<int, int>(row_cnt, col_cnt));
			AgentWorld[row_cnt][col_cnt].clear_observe();
			if (GridWorld[row_cnt][col_cnt] == 2)
				GridWorld[row_cnt][col_cnt] = 1;
		}
	AgentWorld[start.first][start.second].set_g(0);
	AgentWorld[start.first][start.second].set_h(abs(goal.first - start.first + goal.second - start.second));
	AgentWorld[start.first][start.second].update_f();
	Openlist.insert(AgentWorld[start.first][start.second],0);
	AgentWorld[goal.first][goal.second].set_g(INT_MAX);
	AgentWorld[goal.first][goal.second].update_f();
}

void Move::AgentForward(bool adapt,bool gs)
{
	while (current != goal) //if agent don't reach the goal
	{
		counter++;	
		Forward_ComputePath(adapt,gs);  //calculate the path
		if (Openlist.is_empty())  //if there is no way to get the goal
		{
			cout << "The Agent Can't Reach the Target." << endl;
			return;
		}
		else  //if there is still some probabilities to reach the goal
		{
			for (int cnt = path.size() - 1; cnt > 0 && current == path[cnt] && GridWorld[path[cnt - 1].first][path[cnt - 1].second] >= 1; cnt--)
			{
				if (GridWorld[current.first][current.second] != 3)
					GridWorld[current.first][current.second] = 2;
				current = path[cnt - 1];
				int row = current.first;
				int col = current.second;
				//set grid as observed
				AgentWorld[row][col].set_observe();
				if (row - 1 > 0)
					AgentWorld[row - 1][col].set_observe();
				if (row + 1 < MAZESIZE)
					AgentWorld[row + 1][col].set_observe();
				if (col - 1 > 0)
					AgentWorld[row][col - 1].set_observe();
				if (col + 1 < MAZESIZE)
					AgentWorld[row][col + 1].set_observe();
			}
		}
	}
	cout << "The Agent has already Reach the Target." << endl;
	displaymaze();
}

void Move::AgentBackward()
{
	AgentWorld[start.first][start.second].set_g(INT_MAX);
	AgentWorld[start.first][start.second].set_h(abs(start.first - goal.first + start.second - goal.second));
	AgentWorld[start.first][start.second].update_f();
	AgentWorld[goal.first][goal.second].set_g(0);
	AgentWorld[goal.first][goal.second].update_f();

	current = start;
	Openlist.clear();
	Openlist.insert(AgentWorld[goal.first][goal.second],0);
	
	while (current != goal) //if agent don't reach the goal
	{
		counter++;
		Backward_ComputePath();  //calculate the path
		if (Openlist.is_empty())  //if there is no way to get the goal
		{
			cout << "The Agent Can't Reach the Target." << endl;
			return;
		}
		else  //if there is still some probabilities to reach the goal
		{
			AgentWorld[current.first][current.second].set_g(0);
			AgentWorld[current.first][current.second].update_f();
			if (path.size() > 1)
			{
				for (int cnt = 0; cnt < path.size()-1 && current == path[cnt] && GridWorld[path[cnt + 1].first][path[cnt + 1].second] >= 1; cnt++)
				{
					if (GridWorld[current.first][current.second] != 3)
						GridWorld[current.first][current.second] = 2;
					current = path[cnt+1];
					int row = current.first;
					int col = current.second;
					//set grid as observed
					AgentWorld[row][col].set_observe();
					if (row - 1 > 0)
						AgentWorld[row - 1][col].set_observe();
					if (row + 1 < MAZESIZE)
						AgentWorld[row + 1][col].set_observe();
					if (col - 1 > 0)
						AgentWorld[row][col - 1].set_observe();
					if (col + 1 < MAZESIZE)
						AgentWorld[row][col + 1].set_observe();
				}
			}
		}
	}
	cout << "The Agent has already Reach the Target." << endl;
	displaymaze();
}

int Move::ManhattanDistance(Node x,pair<int,int> p)
{
		return (abs(x.get_position().first - p.first) + abs(x.get_position().second - p.second));
}

void Move::Forward_ComputePath(bool adapt,bool gs)
{
	Openlist.clear();
	Closelist.clear();
	AgentWorld[current.first][current.second].set_search(counter);
	AgentWorld[goal.first][goal.second].set_search(counter);
	Openlist.insert(AgentWorld[current.first][current.second],1);
	AgentWorld[goal.first][goal.second].set_g(INT_MAX);
	AgentWorld[goal.first][goal.second].update_f();

	while (AgentWorld[goal.first][goal.second].get_g() >= Openlist.extractMin().get_f())   //if g(goal)>f(s) s is the top of openlist
	{
		if (Openlist.is_empty()) //if open list is empty or find the goal
			break;
		else if (Openlist.peekTop().get_position() == goal)
		{
			path.clear();
			path.push_back(goal);
			int row = goal.first;
			int col = goal.second;
			while (row != current.first || col != current.second)
			{
				pair<int, int> p = AgentWorld[row][col].get_from();
				row = p.first;
				col = p.second;
				path.push_back(p);
			}
			break;
		}
		else
		{
			Node s = Openlist.peekTop();

			int lastRow = s.get_position().first;
			int lastCol = s.get_position().second;
			
			// expand state
			Openlist.remove(s,gs);
			Closelist.push_back(s);

			// four possible directions: up,down,left,right
			const int dirrow[] = { -1,1,0,0 };//up and down
			const int dircol[] = { 0,0,-1,1 };//left and right
			
			for (int i = 0; i < 4; i++)
			{
				int dirR = dirrow[i];
				int dirC = dircol[i];
				int curRow = lastRow + dirR;
				int curCol = lastCol + dirC;

				//check if valid
				if (curRow < 0 || curRow >= MAZESIZE || curCol < 0 || curCol >= MAZESIZE
					|| (GridWorld[curRow][curCol] == 0 && (AgentWorld[curRow][curCol].get_observe() || ManhattanDistance(AgentWorld[curRow][curCol], current) == 1)))
					continue;
				if (AgentWorld[curRow][curCol].get_search() < counter)
				{
					AgentWorld[curRow][curCol].set_g(INT_MAX);
					AgentWorld[curRow][curCol].set_search(counter);
				}
				if (AgentWorld[curRow][curCol].get_g() > AgentWorld[lastRow][lastCol].get_g() + 1)
				{
					AgentWorld[curRow][curCol].set_g(AgentWorld[lastRow][lastCol].get_g() + 1); //update g(s) of current position
					int index = Openlist.FindbyPosition(pair<int, int>(curRow, curCol));
					if (index != -1)   //if the grid has been expanded then remove it
						Openlist.remove(index,gs);
					int h_new = AgentWorld[curRow][curCol].get_h_new();
					if(adapt && h_new!=INT_MAX)
						AgentWorld[curRow][curCol].set_h(h_new);
					else
						AgentWorld[curRow][curCol].set_h(ManhattanDistance(AgentWorld[curRow][curCol], goal));
					AgentWorld[curRow][curCol].update_f();
					AgentWorld[curRow][curCol].set_from(s.get_position());
					Openlist.insert(AgentWorld[curRow][curCol],1);  //insert current position to the openlist
				}
			}
		}
	}

	vector<Node>::iterator itr;
	for (itr = Closelist.begin(); itr != Closelist.end(); itr++)
		AgentWorld[itr->get_position().first][itr->get_position().second].set_h_new(AgentWorld[goal.first][goal.second].get_g() - AgentWorld[itr->get_position().first][itr->get_position().second].get_g());
}

void Move::Backward_ComputePath()
{
	AgentWorld[current.first][current.second].set_g(INT_MAX);
	AgentWorld[current.first][current.second].set_from(pair<int,int>(current.first, current.second));
	AgentWorld[current.first][current.second].update_f();
	AgentWorld[current.first][current.second].set_search(counter);
	AgentWorld[goal.first][goal.second].set_search(counter);
	Openlist.clear();
	Closelist.clear();
	Openlist.insert(AgentWorld[goal.first][goal.second],0);

	while (AgentWorld[current.first][current.second].get_g() >= Openlist.extractMin().get_f())   //if g(goal)>f(s) s is the top of openlist
	{
		if (Openlist.is_empty()) //if open list is empty or find the goal
			break;
		else if (Openlist.peekTop().get_position() == current)
		{
			path.clear();
			path.push_back(current);
			int row = current.first;
			int col = current.second;
			while (row != goal.first || col != goal.second)
			{
				pair<int, int> p = AgentWorld[row][col].get_from();
				row = p.first;
				col = p.second;
				path.push_back(p);
			}
			break;
		}
		else
		{
			Node s = Openlist.peekTop();
			int lastRow = s.get_position().first;
			int lastCol = s.get_position().second;

			// expand state
			Openlist.remove(s,0);
			Closelist.push_back(s);

			// four possible directions: up,down,left,right
			int dirrow[] = { -1,1,0,0 };//up and down
			int dircol[] = { 0,0,-1,1 };//left and right

			for (int i = 0; i < 4; i++)
			{
				int dirR = dirrow[i];
				int dirC = dircol[i];
				int curRow = lastRow + dirR;
				int curCol = lastCol + dirC;

				//check if valid
				if (curRow < 0 || curRow >= MAZESIZE || curCol < 0 || curCol >= MAZESIZE
					|| (GridWorld[curRow][curCol] == 0 && (AgentWorld[curRow][curCol].get_observe() || ManhattanDistance(AgentWorld[curRow][curCol], current) == 1)))
					continue;
				if (AgentWorld[curRow][curCol].get_search() < counter)
				{
					AgentWorld[curRow][curCol].set_g(INT_MAX);
					AgentWorld[curRow][curCol].set_search(counter);
				}
				if (AgentWorld[curRow][curCol].get_g() > AgentWorld[lastRow][lastCol].get_g() + 1)
				{
					AgentWorld[curRow][curCol].set_g(AgentWorld[lastRow][lastCol].get_g() + 1); //update g(s) of current position
					int index = Openlist.FindbyPosition(pair<int, int>(curRow, curCol));
					if (index != -1)   //if the grid has been expanded then remove it
						Openlist.remove(index,0);
					AgentWorld[curRow][curCol].set_h(ManhattanDistance(AgentWorld[curRow][curCol], current));
					AgentWorld[curRow][curCol].update_f();
					AgentWorld[curRow][curCol].set_from(s.get_position());
					Openlist.insert(AgentWorld[curRow][curCol],0);  //insert current position to the openlist			
				}
			}
		}
	}
}

