# Maze-Runner
Developed by Fengru Li, Fei Tao.
Enviroment: Visual Studio

## Problem Intro
There is a maze(in grid world) which is randomly generated. A maze runner is randomly placed in the maze(not on the wall). There is war-fog in the maze. The runner can only observe cell which is adjust with it. The goal is try to find a path to the destination.

## Solving Algorithm
Using repeated adaptive A-star(A*) algorithm. Each time of A* search algorithm will search currently observed maze to find the path. Then move according this path until it hits a wall. Repeat this until find there is no way to desination or already arrived the destination
For A* algorithm, using Manhattan distance to be the heuristic function. 

Also, there is a comparsion among BFS,DFS, reapted A* algorithm and repeated adaptive A* algorithm.
