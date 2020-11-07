//Author: Jane Lee
//Date: 11/2020
//8501 Programming CW1

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>


#include "Maze.h"

using namespace std;
int rowArr[] = { -1, 0, 0, 1 };
int colArr[] = { 0, -1, 1, 0 };
int lowest = INT_MAX;
int exitX;
int exitY;


Maze::Maze() {
	rowMain = 0;
	colMain = 0;
	tempi = 0;
	tempj = 0;
	shouldPrint = false;
	printOriginal = false;
}

Maze::~Maze() {
}

void Maze::createMaze(int& row, int& col, int& players) {

	bool validMaze = false;
	bool validPlayers = false;
	int r2 = row;
	int c2 = col;
	int p2 = players;

	while (!validMaze) {

		if ((row <= 31 && row >= 9) && (col <= 31 && col >= 9) && row == int(row) && col == int(col)) {
			rowMain = row;
			colMain = col;
			mazeVect.resize(row, std::vector<char>(col, 'X'));
			int midRow = row / 2;
			int midCol = col / 2;

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					mazeVect[0][j] = 'X';
					mazeVect[i][0] = 'X';
					mazeVect[row - 1][j] = 'X';
					mazeVect[i][col - 1] = 'X';
				}
			}

			createWall(midRow, midCol, row, col);

			while (!validPlayers) {
				int maxPlayers = 10;
				if (players <= maxPlayers && players >= 2 && players == int(players)) { //////////////////////////////////////////////////////////////////////////
					createExit(row, col, players);
					validPlayers = true;
				}

				else {
					cin.clear();
					cin.ignore();
					cout << "Incorrect no. of players. Re-enter no. of players:" << endl;
					cin >> p2;
					players = p2;
				}
			}

			validMaze = true;
		}
		else {
			validMaze = false;
			cin.clear();
			cin.ignore();
			cout << "\n\nIncorrect maze size. Re-enter row size: ";
			cin >> r2;
			cout << "Re-enter column size: ";
			cin >> c2;
			row = r2;
			col = c2;

			validPlayers = false;
			cin.clear();
			cin.ignore();
			cout << "Enter no. players from 2 to 10: ";
			cin >> p2;
			players = p2;

		}

	}

}

void Maze::createMiddle(int row, int col) {

	int midRow = row / 2;
	int midCol = col / 2;

	mazeVect[midRow][midCol] = 'F';

	mazeVect[midRow - 1][midCol - 1] = ' ';
	mazeVect[midRow - 1][midCol] = ' ';
	mazeVect[midRow - 1][midCol + 1] = ' ';
	mazeVect[midRow][midCol - 1] = ' ';
	mazeVect[midRow][midCol + 1] = ' ';
	mazeVect[midRow + 1][midCol - 1] = ' ';
	mazeVect[midRow + 1][midCol] = ' ';
	mazeVect[midRow + 1][midCol + 1] = ' ';

}

void Maze::createWall(int r, int c, int rSize, int cSize) {

	const int up = 0;
	const int right = 1;
	const int left = 2;
	const int down = 3;
	vector<int> directions = randGenerator();

	mazeVect[r][c] = ' ';

	for (int i = 0; i < 4; ++i) {
		int x = 0;
		int y = 0;
		switch (directions[i]) {
		case up:
			y = -1;
			break;
		case right:
			x = 1;
			break;
		case down:
			y = 1;
			break;
		case left:
			x = -1;
			break;
		}

		int x2 = r + (x + x);
		int y2 = c + (y + y);

		if (inBounds(x2, y2, rSize, cSize)) {
			if (mazeVect[x2][y2] == 'X') {
				mazeVect[x2 - x][y2 - y] = ' ';
				createWall(x2, y2, rSize, cSize);
			}
		}

	}

}

void Maze::createExit(int row, int col, int exits) {

	for (int i = 1; i <= exits; i++) {
		int rRand = rand() % (row - 4) + 2;
		int cRand = rand() % (col - 4) + 2;

		int randGen = rand() % 4;
		switch (randGen) {
		case 0:
			while (mazeVect[rRand][0] == 'E') {
				rRand = rand() % (row - 4) + 2;
			}
			mazeVect[rRand][0] = 'E';
			mazeVect[rRand][1] = 'P';
			mazeVect[rRand][2] = ' ';
			break;
		case 1:
			while (mazeVect[rRand][col - 1] == 'E') {
				rRand = rand() % (row - 4) + 2;
			}
			mazeVect[rRand][col - 1] = 'E';
			mazeVect[rRand][col - 2] = 'P';
			mazeVect[rRand][col - 3] = ' ';
			break;
		case 2:
			while (mazeVect[0][cRand] == 'E') {
				cRand = rand() % (col - 4) + 2;
			}
			mazeVect[0][cRand] = 'E';
			mazeVect[1][cRand] = 'P';
			mazeVect[2][cRand] = ' ';
			break;
		case 3:
			while (mazeVect[row - 1][cRand] == 'E') {
				cRand = rand() % (col - 4) + 2;
			}
			mazeVect[row - 1][cRand] = 'E';
			mazeVect[row - 2][cRand] = 'P';
			mazeVect[row - 3][cRand] = ' ';
			break;
		}
	}

}

std::vector<int> Maze::randGenerator() {

	vector<int>dir;

	for (int i = 0; i < 4; i++) {
		dir.push_back(i);
	}
	random_shuffle(dir.begin(), dir.end());

	return dir;
}

bool Maze::inBounds(int r, int c, int rSize, int cSize) {
	if (r <= 0 || r >= rSize - 1) {
		return false;
	}
	else if (c <= 0 || c >= cSize - 1) {
		return false;
	}
	else {
		return true;
	}
}


void Maze::pPos() {
	for (int i = 0; i < mazeVect.size(); i++) {
		for (int j = 0; j < mazeVect[i].size(); j++) {
			if (mazeVect[i][j] == 'P') {
				pPosList.push_back(i);
				pPosList.push_back(j);
			}

		}

	}
}

void Maze::getpPos() {

	while (!pPosList.empty()) {
		tempi = pPosList.front();
		pPosList.pop_front();
		tempj = pPosList.front();
		pPosList.pop_front();
		break;
	}

}


bool Maze::tileIsValid(vector<vector<char>>& maze, vector<vector<char>>& visitedMaze, int r, int c) {
	if ((r >= 0) && (r < rowMain) && (c >= 0) && (c < colMain) && maze[r][c] && visitedMaze[r][c] != 'o' && visitedMaze[r][c] != 'X') {
		return true;
	}
	else
		return false;
}

void Maze::findPath(vector<vector<char>>& maze, int i, int j, int x, int y, int players) {


	visitedMaze.resize(rowMain, std::vector<char>(colMain, ' '));
	tempMaze.resize(rowMain, std::vector<char>(colMain, ' '));
	tempMaze = mazeVect;
	visitedMaze = mazeVect;

	for (int i = 0; i < mazeVect.size(); i++) {
		for (int j = 0; j < mazeVect[i].size(); j++) {
			if (mazeVect[i][j] == 'P') {
				visitedMaze[i][j] = ' ';
			}
			if (mazeVect[i][j] == 'E') {
				visitedMaze[i][j] = 'X';
			}
		}
	}

	int tempX;
	int tempY;

	list<Node>* visitedList = new list<Node>;
	vector<Node>* allVisitedNodes = new vector<Node>;

	visitedMaze[i][j] = 'o';
	visitedMaze[x][y] = 'F';
	visitedList->push_back({ i, j, 0 });

	int min_dist = INT_MAX;
	Node* node = new Node;


	while (!visitedList->empty()) {

		*node = visitedList->front();
		visitedList->pop_front();

		int i = node->x;
		int j = node->y;
		int dist = node->distance;

		if (i == x && j == y) {
			tempX = i;
			tempY = j;
			min_dist = dist;
			break;
		}

		int v = 0;
		for (int k = 0; k < 4; ++k) {

			if (i == x && j == y) {
				break;
			}

			if (tileIsValid(maze, visitedMaze, i + rowArr[k], j + colArr[k])) {
				visitedMaze[i + rowArr[k]][j + colArr[k]] = 'o';

				int currX = node->x;
				int currY = node->y;
				visitedList->push_back({ i + rowArr[k], j + colArr[k], dist + 1,currX ,currY, node, v++ });
				allVisitedNodes->push_back(visitedList->back());


				//cout << endl;
				//for (int i = 0; i < mazeVect.size(); i++) {
				//	for (int j = 0; j < mazeVect[i].size(); j++) {
				//		cout << visitedMaze[i][j] << ' ';
				//	}
				//	cout << '\n';
				//}

			}
		}
	}


	if (min_dist != INT_MAX) {

		cout << "The shortest path from {" << j + 1 << ',' << i + 1 << "} to {" << y + 1 << ',' << x + 1 << "} is: " << min_dist << endl;

		list<Node>* traverseNode = new list<Node>;

		for (int i = 0; i < min_dist; i++) {

			vector<Node>::iterator findxy = find_if(allVisitedNodes->begin(), allVisitedNodes->end(), [tempX, tempY, traverseNode](Node& item) {
				if (item.x == tempX && item.y == tempY)
					traverseNode->push_back(item);
				return item.x == tempX && item.y == tempY; });

			list<Node>::iterator it;
			for (it = traverseNode->begin(); it != traverseNode->end(); ++it) {
				//tempMaze[it->prevx][it->prevy] = 'o';
				tempX = it->prevx;
				tempY = it->prevy;
			}
		}

		list<Node>::reverse_iterator rit;
		////////////////////////////////
		char i = 48;
		int input;
		bool cont = false;
		int move = 1;


		(*allPlayers).push_back(new vector<Node>());


		for (rit = next(traverseNode->rbegin()); rit != traverseNode->rend(); ++rit) {



			cout << players;
			(*allPlayers)[players]->push_back(*rit);


			tempMaze[rit->prevx][rit->prevy] = 'o';

			cout << endl;
			cout << "Move " << move++ << endl;
			for (int i = 0; i < mazeVect.size(); i++) {
				for (int j = 0; j < mazeVect[i].size(); j++) {
					cout << tempMaze[i][j] << ' ';
				}
				cout << '\n';
			}

			//if (cont == false) {
			//	cout << "\nEnter '0' for next iteration or '1' to show all movement\n";
			//	cin >> input;
			//	if (input == 0) {
			//		cont = false;
			//		continue;
			//	}
			//	else {
			//		cont = true;
			//		continue;
			//	}
			//}




		}

		(*allPlayers)[players]->push_back({ rowMain / 2, colMain / 2,0,rowMain/2, colMain/2});

		tempMaze[rowMain / 2][colMain / 2] = 'F';

		if (min_dist <= lowest) {
			lowest = min_dist;
			overallShortestMaze = tempMaze;
			exitX = tempi;
			exitY = tempj;
		}

		delete traverseNode;
		traverseNode = nullptr;
	}
	else cout << "No route found \n";

	visitedMaze.clear();
	delete visitedList;
	delete allVisitedNodes;
	delete node;
	visitedList = nullptr;
	allVisitedNodes = nullptr;
	node = nullptr;
}

char Maze::switchPlayer(int currPlayer) {
	char path;
	switch (currPlayer) {

	case 0:
		path = 'a';
		break;
	case 1:
		path = 'b';
		break;
	case 2:
		path = 'c';
		break;
	case 3:
		path = 'd';
		break;
	case 4:
		path = 'e';
		break;
	case 5:
		path = 'f';
		break;
	case 6:
		path = 'g';
		break;
	case 7:
		path = 'h';
		break;
	case 8:
		path = 'i';
		break;
	case 9:
		path = 'j';
		break;


	}
	return path;
}

void Maze::playerPositions(int players) {

	tempMaze2 = mazeVect;

	int change = 0;
	int k = 2;

	vector<int> playerarr[2];
	playerarr->push_back(0);
	playerarr->push_back(1);

	if ((*allPlayers).size() > playerarr->size()) {
		playerarr->push_back(k);
		k++;
	}


	int currPlayer = 0;
	char path = NULL;
	
	int prevx = 0;
	int prevy = 0;
	bool skipped = false;
	char tempPath = NULL;
	backupMaze = tempMaze2;

	cout << (*allPlayers).size();
	vector<vector<int>*>* aaaaaa = new vector<vector<int>*>;

	for (int a = 0; a <= (*allPlayers).size(); a++) {
		
		for (int i = 0; i < (*allPlayers).size(); i++) {


			cout << (*allPlayers).size();
			
			for (int j = 0; j < (*allPlayers)[i]->size(); j++) { //////////////////////////////////


				cout << (*allPlayers)[i]->size();

				if ((*allPlayers)[i]->size() <=0) {
					break;
				}
				else {
					
					prevx = allPlayers->at(i)->at(0).prevx;
					prevy = allPlayers->at(i)->at(0).prevy;
					(*aaaaaa).push_back(new vector<int>());
					(*aaaaaa)[i]->push_back(prevx);
					(*aaaaaa)[i]->push_back(prevy);

					

					path = switchPlayer(i);
					cout << "\nPlayer " << i+1 << " turn:\n";

					for (int i = 0; i < tempMaze2.size(); i++) {
						for (int j = 0; j < tempMaze2[i].size(); j++) {
							
							
							if (skipped == false && tempMaze2[i][j] == path) {
								tempMaze2[i][j] = ' ';
							}
							if (skipped == true) {

								if (backupMaze[i][j] == path) {
									backupMaze[i][j] = ' ';
									tempMaze2 = backupMaze;
								}
								
								
							}
						

						}
						
					}
					skipped = false;

					if ((tempMaze2)[allPlayers->at(i)->at(0).prevx][allPlayers->at(i)->at(0).prevy] <97) {

						tempMaze2[allPlayers->at(i)->at(0).prevx][allPlayers->at(i)->at(0).prevy] = path;


						if ((*allPlayers)[i]->size() ==1) {
							cout << "here";
							tempMaze2[allPlayers->at(i)->at(0).x][allPlayers->at(i)->at(0).y] = 'F';
						}
						else {
							(*allPlayers)[i]->erase((*allPlayers)[i]->begin());
						}
						
					}

					else {
						cout << "skipped\n";
						cout << tempMaze2[allPlayers->at(i)->at(0).prevx][allPlayers->at(i)->at(0).prevy];

						for (int i = 0; i < backupMaze.size(); i++) {
							for (int j = 0; j < backupMaze[i].size(); j++) {
								cout << backupMaze[i][j] << ' ';
							}
							cout << '\n';
						}
						backupMaze = backupMaze;
						skipped = true;
						tempPath = path;
						//tempMaze2[allPlayers->at(i)->at(change).prevx][allPlayers->at(i)->at(change).prevy] = 'H';
						//break;
					}


					if (skipped == false) {
						for (int i = 0; i < tempMaze2.size(); i++) {
							for (int j = 0; j < tempMaze2[i].size(); j++) {
								cout << tempMaze2[i][j] << ' ';
							}
							cout << '\n';
						}
						backupMaze = tempMaze2;
					}
				
					
					
				}

				


				break;
			}
			
		
		}
		
		change++;

		//aaaaaa->clear();
		
		//(prevx != 0 && prevy != 0 ? tempMaze2[prevx][prevy] = ' ' : tempMaze2[prevx][prevy] = 'o');
	}



	//for (int i = 0; i < (*allPlayers).size(); i++) {
	//	for (int j = 0; j < (*allPlayers)[i]->size(); j++) {
	//		cout << allPlayers->size() << endl;
	//		cout << (*allPlayers)[i]->size() << endl;
	//		cout << allPlayers[i][j]->front().prevx;
	//		cout << allPlayers[i][j]->front().prevy << endl;

	//		while (allPlayers[i].size() > 1) {
	//			//(*allPlayers)[i][j].erase(*&(allPlayers)->begin());
	//			(allPlayers[i][j])->erase((allPlayers[i][j])->begin());
	//			break;
	//		}
	//		//tempMaze[rit->prevx][rit->prevy] = 'o';
	//	}
	//}

}



void Maze::mazeSolvable() {


}









void Maze::printMaze() {
	for (int i = 0; i < mazeVect.size(); i++) {
		for (int j = 0; j < mazeVect[i].size(); j++) {
			cout << mazeVect[i][j] << ' ';
		}
		cout << '\n';
	}

}

void Maze::printShortestRoute() {

	if (lowest == INT_MAX) {
		cout << "\nNo route found\n";
	}
	else {
		cout << "\nShortest Distance Overall is from {" << colMain / 2 + 1 << "," << rowMain / 2 + 1 << "} to {" << exitY + 1 << "," << exitX + 1 << "}\n";
		cout << "Number of steps: " << lowest << endl;
		for (int i = 0; i < overallShortestMaze.size(); i++) {
			for (int j = 0; j < overallShortestMaze[i].size(); j++) {
				cout << overallShortestMaze[i][j] << ' ';
			}
			cout << '\n';
		}
	}

}

void Maze::printSolution() {

	for (int i = 0; i < mazeSol.size(); i++) {
		for (int j = 0; j < mazeSol[i].size(); j++) {
			cout << mazeSol[i][j] << ' ';
		}
		cout << '\n';
	}
}

void Maze::clearAllMazes() {
	mazeVect.clear();
	mazeSol.clear();
	tempMaze.clear();
	visitedMaze.clear();
	overallShortestMaze.clear();
	pPosList.clear();
	lowest = INT_MAX;
}

void Maze::copyOGMaze() {
	mazeSol = mazeVect;
}

void Maze::copyTempMaze() {

	for (int i = 0; i < mazeSol.size(); i++) {
		for (int j = 0; j < mazeSol[i].size(); j++) {
			if (mazeSol[i][j] == 'o' && tempMaze[i][j] == 'o') {
				mazeSol[i][j] = 'H';
			}
			if (mazeSol[i][j] == ' ' && tempMaze[i][j] == 'o') {
				mazeSol[i][j] = 'o';
			}
			if (mazeSol[i][j] == 'o' && tempMaze[i][j] == ' ') {
				mazeSol[i][j] = 'o';
			}
			if (mazeSol[i][j] == 'E' && tempMaze[i][j] == 'o') {
				mazeSol[i][j] = 'E';
			}
			if (mazeSol[i][j] == 'P' && (tempMaze[i][j] == 'X' || tempMaze[i][j] == 'o')) {
				mazeSol[i][j] = 'P';
			}
			else
				mazeSol[i][j] = mazeSol[i][j];
		}
	}

	tempMaze.clear();
}


void Maze::readFile() throw(invalid_argument) {

	string input;
	string output;
	cout << "Enter file name to open: ";
	cin >> input;
	cout << '\n';
	ifstream readMaze(input + ".txt");

	if (readMaze.is_open()) {
		while (getline(readMaze, output)) {
			cout << output;
			cout << '\n';
		}
		readMaze.close();
	}
	else {
		throw invalid_argument('"' + input + "\" file does not exist\n");
	}


}

void Maze::writeFile() {

	if (mazeVect.size() <= 0) {
		cout << "No maze found to save, please create Maze first\n";
	}
	else {
		ofstream mazeTxt;
		string input;
		vector<vector<char>> tempPrint;

		cout << "Enter file save name: ";
		cin >> input;
		mazeTxt.open(input + ".txt");

		if (mazeSol.size() <= 0 && overallShortestMaze.size() <= 0) {
			cout << "Saved maze\n";
			tempPrint = mazeVect;
		}
		else if ((mazeSol.size() > 0 || overallShortestMaze.size() > 0) && printOriginal == true) {
			cout << "Saved blank maze\n";
			tempPrint = mazeVect;
		}
		else if (mazeSol.size() > 0 && shouldPrint == true && printOriginal == false) {
			cout << "Saved all solutions\n";
			tempPrint = mazeSol;
		}
		else if (overallShortestMaze.size() > 0 && shouldPrint == false && printOriginal == false) {
			cout << "Saved shortest maze\n";
			tempPrint = overallShortestMaze;
		}


		for (const auto& x : tempPrint) {
			copy(x.begin(), x.end(), ostream_iterator<char>(mazeTxt, " "));
			mazeTxt << '\n';
		}

		mazeTxt.close();

		cout << "File saved as " << input << ".txt" << endl;
		tempPrint.clear();

	}

}



