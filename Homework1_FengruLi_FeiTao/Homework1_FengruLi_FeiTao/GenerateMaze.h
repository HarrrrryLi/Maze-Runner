#pragma once
#include <iostream>
#include <time.h>
#include <stack>

using namespace std;
#ifndef GENERATEMAZE_H
#define GENERATEMAZE_H
#define MAZESIZE 101
#define M_Up 0
#define M_Down 1
#define M_Left 2
#define M_Right 3

void displaymaze();  //display maze
void generatemaze(); //generate maze
int random_dir(int row,int col); //randomly decide a direction
bool get_random(double p); //flip a bias coin

#endif
