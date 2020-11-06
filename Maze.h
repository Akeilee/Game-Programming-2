//Author: Jane Lee
//Date: 11/2020
//8501 Programming CW1

#pragma once
#include <iostream>
#include <vector>
#include <list>

struct Node {
	int x;
	int y;
	int distance;

	int prevx;
	int prevy;

	struct Node* parent;
	int v;

};

class Maze {
public:

	Maze();
	~Maze();

	void createMaze(int& r, int& c, int& exits);
	void createMiddle(int row, int col);
	void createWall(int r, int c, int rSize, int cSize);
	void createExit(int row, int col, int exits);
	std::vector<int> randGenerator();
	bool inBounds(int r, int c, int rSize, int cSize);

	void pPos();
	void getpPos();

	bool tileIsValid(std::vector<std::vector<char>>& maze, std::vector<std::vector<char>>& visitedMaze, int r, int c);
	void findPath(std::vector<std::vector<char>>& maze, int i, int j, int x, int y);

	void playerPositions();

	void mazeSolvable();

	void printMaze();
	void printShortestRoute();
	void printSolution();

	void clearAllMazes();
	void copyOGMaze();
	void copyTempMaze();

	void readFile();
	void writeFile();

	int tempi;
	int tempj;
	int getTempi() { return tempi; };
	int getTempj() { return tempj; };

	int rowMain;
	int colMain;
	int getRow() { return rowMain; };
	int getCol() { return colMain; };
	void setRow(int r) { rowMain = r; };
	void setCol(int c) { colMain = c; };

	bool shouldPrint;
	void setShouldPrint(bool p) { shouldPrint = p; };
	bool printOriginal;
	void setprintOriginal(bool p) { printOriginal = p; };

	std::vector<std::vector<char>>& getMaze() { return mazeVect; };
	std::vector<std::vector<char>>& getSolMaze() { return mazeSol; };

private:
	std::vector<std::vector<char>> mazeVect;
	std::vector<std::vector<char>> mazeSol;
	std::vector<std::vector<char>> tempMaze;
	std::vector<std::vector<char>> visitedMaze;
	std::vector<std::vector<char>> overallShortestMaze;
	std::list<int>pPosList;

};
