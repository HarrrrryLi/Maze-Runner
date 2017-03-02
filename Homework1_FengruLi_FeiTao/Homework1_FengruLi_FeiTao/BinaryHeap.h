#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

class Node
{
public:	
	Node();
	int get_f();  //get f(s)
	int get_g();  //get g(s)
	int get_h();  //get h(s)
	int get_h_new();
	void set_f(int); //set f(s)
	void set_g(int); //set g(s)
	void set_h(int); //set h(s)
	void set_h_new(int);
	void update_f(); //update f(s) according to g(s) and h(s)
	pair<int, int> get_position(); // get position information
	void set_position(pair<int, int>); //set position information
	int get_search();  //get search
	void set_search(int); //set search
	void set_from(pair<int, int>);
	void set_observe();
	void clear_observe();
	bool get_observe();
	pair<int, int> get_from();
private:
	int f;   //f(s)
	int g;   //g(s)
	int h;   //h(s)
	int h_new;
	pair<int, int> position;  //position information (row,col)
	int search; 
	pair<int, int> from;
	bool obsevered;
};

class BinaryHeap    //binary heap based on array
{
public:
	BinaryHeap();   //initialize
	BinaryHeap(Node);  //initialize with a node
	bool is_empty();  //check whether is empty
	bool insert(Node,bool);  //insert a node 
	bool remove(Node x,bool);  //remove a node
	bool remove(int index,bool);  //remove a certain index node
	bool sort_gs();   //sort binary heap using merge sort
	bool sort_gl();
	Node peekTop();   //return top of binary heap. no action of empty
	void clear();  //clear binary heap
	int getHeight();  //get height of binary heap
	int getNodeNumber(); //get number of nodes
	int FindbyPosition(pair<int, int>);   //find a node with position information  if there is no such node return -1  else return its position
	Node extractMin();   //return the minimum, if empty return a node with f(s)=-1
private:
	Node *bHeap;  //pointer which points to the root of binary heap	
	int size; //the size of binary heap
};
#endif