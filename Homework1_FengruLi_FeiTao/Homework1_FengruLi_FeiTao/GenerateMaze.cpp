#include "GenerateMaze.h"


int GridWorld[MAZESIZE][MAZESIZE] = { 0 };  //define the maze

void displaymaze()
{
	for (int cnt = 0; cnt < MAZESIZE+2; cnt++)  //display wall
		cout << "-";
	cout << endl;
	for (int row_cnt = 0; row_cnt < MAZESIZE; row_cnt++)
	{
		cout << "|";   //display wall
		for (int col_cnt = 0; col_cnt < MAZESIZE; col_cnt++)
			if (GridWorld[row_cnt][col_cnt] == 1)
				cout << " ";  //means grid is unblocked
			else if (GridWorld[row_cnt][col_cnt] == 0)
				cout << "X";  //X means grid is blocked
			else if (GridWorld[row_cnt][col_cnt] == 2)
				cout << "*";
			else if (GridWorld[row_cnt][col_cnt] == 3)
				cout << "$";
		cout << "|" << endl; //display wall
	}
	for (int cnt = 0; cnt < MAZESIZE+2; cnt++)
		cout << "-";  //display wall
	cout << endl;
}

void generatemaze()
{
	for (int row_cnt = 0; row_cnt < MAZESIZE; row_cnt++)       //make all grid as unvisited.  unvisited:-1  unblocked:1 blocked:0
		for (int col_cnt = 0; col_cnt < MAZESIZE; col_cnt++)
			GridWorld[row_cnt][col_cnt] = -1;
	int cnt = 0;
	int row = rand() % MAZESIZE, col = rand() % MAZESIZE;   //randomly pick a grid
	stack<pair<int,int>> unblocked;  //creat a stack to store unblocked grid
	pair<int, int> temp;
	while (cnt!=MAZESIZE*MAZESIZE)  //if there are some grids unvisited
	{
		if (GridWorld[row][col] == -1) // if the grid is unvisited 
		{
			if (get_random(0.7))  //decide whether it's unblocked
			{
				GridWorld[row][col] = 1;
				unblocked.push(pair<int, int>(row, col));  //if it's unblocked then push it in to stack
			}
			else
				GridWorld[row][col] = 0;
			cnt++;  
		}
		//if go into a dead end and there are some unvisited grid
		while ((cnt != MAZESIZE*MAZESIZE) && (row - 1 < 0 || GridWorld[row - 1][col] != -1) && (row + 1 > MAZESIZE || GridWorld[row + 1][col] != -1) && (col - 1 < 0 || GridWorld[row][col - 1] != -1) && (col + 1 > MAZESIZE || GridWorld[row][col + 1] != -1))
		{
			if (unblocked.empty())  //if stack is empty
			{
				do      //choose a unvisited block
				{
					row = rand() % MAZESIZE;
					col = rand() % MAZESIZE;
				} while (GridWorld[row][col] != -1);
				if (get_random(0.7))  
				{
					GridWorld[row][col] = 1;
					unblocked.push(pair<int, int>(row, col));
				}
				else
					GridWorld[row][col] = 0;
				cnt++;
				continue;
			}
			temp = unblocked.top();  // get a unblocked grid from stack
			row = temp.first;     //get row of postion
			col = temp.second;    //get column of position
			unblocked.pop();
		}
		switch (random_dir(row,col))   //randomly choose a direction
		{
		case M_Up:col = col - 1; break;
		case M_Down:col = col + 1; break;
		case M_Left:row = row - 1; break;
		case M_Right:row = row + 1; break;
		}
	}
}

int random_dir(int row,int col)  // 0 left  1 right 2 up 3 down
{
	int dir;
	do
	{
		dir = rand() % 4;
	} while ((dir == M_Up && col - 1 < 0 && GridWorld[row][col - 1] != -1) || (dir == M_Down && col + 1 > MAZESIZE && GridWorld[row][col + 1] != -1) || (dir == M_Left && row - 1 < 0 && GridWorld[row - 1][col] != -1) || (dir == M_Right && row + 1 > MAZESIZE && GridWorld[row + 1][col] != -1));
	return dir;
}

bool get_random(double p)  //flip a bias coin
{
	if (rand() % 100 < 100 * p)
		return true;
	else
		return false;
}
