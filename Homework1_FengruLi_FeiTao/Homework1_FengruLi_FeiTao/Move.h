#pragma once
#ifndef MOVE_H
#define MOVE_H
#include "BinaryHeap.h"
#include "GenerateMaze.h"
#include <vector>


class Move
{
public:
	Move();   
	~Move();
	void reinitialize();
	void AgentForward(bool,bool);  //function of agent try to reach the target with forward A*
	void AgentBackward();  //function of agent try to reach the target with forward A*
	int ManhattanDistance(Node,pair<int,int>);  //calculate manhattan distance from a node to position
	void Forward_ComputePath(bool,bool); //compute path with forward A*
	void Backward_ComputePath(); //compute path with backward A*
	int num_expand;
private:
	pair<int, int> start;   //start position information (row,col)
	pair<int, int> goal;    //goal position information (row,col)
	pair<int, int> current; //current position information (row,col)
	Node AgentWorld[MAZESIZE][MAZESIZE];  //the grid world in agent vision
	BinaryHeap Openlist;  
	vector<Node> Closelist;
	int counter;  

	vector<pair<int, int>> path;
};
#endif
