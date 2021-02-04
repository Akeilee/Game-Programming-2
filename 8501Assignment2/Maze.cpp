//Author: Jane Lee
//Date: 11/2020
//8501 Programming CW2

#include <fstream>
#include <algorithm>

#include "Maze.h"

using namespace std;

int rowArr[] = { -1, 0, 0, 1 }; //north east 
int colArr[] = { 0, -1, 1, 0 }; //south west
int lowest = INT_MAX;
int exitX;
int exitY;
bool firstMove = true;


Maze::Maze() {
	rowMain = 0;
	colMain = 0;
	tempi = 0;
	tempj = 0;
	shouldPrint = false;
	printOriginal = false;
	mazeLimit = false;
}

Maze::~Maze() {
	delete allPlayers;
	allPlayers = NULL;
}

void Maze::createMaze(int& row, int& col, int& players) {

	bool validMaze = false;
	bool validPlayers = false;
	int r2 = row;
	int c2 = col;
	int p2 = players;

	int maxPlayers = 8;
	int uLim = 31;
	int lLim = 9;

	if (mazeLimit == true) {
		maxPlayers = players;
		(row >= col ? uLim = row : uLim = col);
	}

	while (!validMaze) {
		if ((row <= uLim && row >= lLim) && (col <= uLim && col >= lLim) && row == int(row) && col == int(col)) {
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
				if (players <= maxPlayers && players >= 1 && players == int(players)) { 
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
			cout << "Enter no. players from 1 to 8: ";
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


void Maze::pPos() { //player position
	for (int i = 0; i < mazeVect.size(); i++) {
		for (int j = 0; j < mazeVect[i].size(); j++) {
			if (mazeVect[i][j] == 'P') {
				pPosList.push_back(i);
				pPosList.push_back(j);
			}
		}
	}
}

void Maze::getpPos() { //get player position

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

void Maze::findPath(vector<vector<char>>& maze, int i, int j, int x, int y, int player) {  //x, y is middle of maze   //i, j is player pos

	visitedMaze.resize(rowMain, std::vector<char>(colMain, ' '));
	tempMaze.resize(rowMain, std::vector<char>(colMain, ' '));
	tempMaze = mazeVect;
	visitedMaze = mazeVect;

	for (int i = 0; i < mazeVect.size(); i++) {
		for (int j = 0; j < mazeVect[i].size(); j++) {
			if (mazeVect[i][j] == 'P') {  //P is player
				visitedMaze[i][j] = ' ';
			}
			if (mazeVect[i][j] == 'E') { //E is exit
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

		if (i == x && j == y) { //if found middle of maze then solved
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
			if (tileIsValid(maze, visitedMaze, i + rowArr[k], j + colArr[k])) { //checking all directions N,E,S,W
				visitedMaze[i + rowArr[k]][j + colArr[k]] = 'o';

				int currX = node->x;
				int currY = node->y;
				visitedList->push_back({ i + rowArr[k], j + colArr[k], dist + 1,currX ,currY, node, v++ });
				allVisitedNodes->push_back(visitedList->back());

				//for (int i = 0; i < visitedMaze.size(); i++) {
				//	for (int j = 0; j < visitedMaze[i].size(); j++) {
				//		cout << visitedMaze[i][j] << ' ';
				//	}
				//	cout << '\n';
				//}
				//cout << '\n';
			}
		}
	}

	if (min_dist != INT_MAX) {
		list<Node>* traverseNode = new list<Node>;

		for (int i = 0; i < min_dist; i++) { //finding path

			vector<Node>::iterator findxy = find_if(allVisitedNodes->begin(), allVisitedNodes->end(), [tempX, tempY, traverseNode](Node& item) {
				if (item.x == tempX && item.y == tempY)
					traverseNode->push_back(item);
				return item.x == tempX && item.y == tempY; });

			list<Node>::iterator it;
			for (it = traverseNode->begin(); it != traverseNode->end(); ++it) {
				tempX = it->prevx;
				tempY = it->prevy;
			}
		}

		list<Node>::reverse_iterator rit;
		(*allPlayers).push_back(new vector<Node>());

		for (rit = next(traverseNode->rbegin()); rit != traverseNode->rend(); ++rit) {
			(*allPlayers)[player]->push_back(*rit);
			tempMaze[rit->prevx][rit->prevy] = 'o';
		}

		(*allPlayers)[player]->push_back({ rowMain / 2, colMain / 2,0,rowMain / 2, colMain / 2 }); //i
		(*allPlayers)[player]->push_back({ rowMain / 2, colMain / 2,0,rowMain / 2, colMain / 2 }); //j

		tempMaze[rowMain / 2][colMain / 2] = 'F';

		if (min_dist <= lowest) {
			lowest = min_dist;
			overallShortestMaze = tempMaze;
			exitX = tempi;
			exitY = tempj;
		}

		char playerName = switchPlayer(player);
		cout << "\nPlayer " << playerName << " shortest path\n";
		for (int i = 0; i < tempMaze.size(); i++) {
			for (int j = 0; j < tempMaze[i].size(); j++) {
				cout << tempMaze[i][j] << ' ';
			}
			cout << '\n';
		}

		delete traverseNode;
		traverseNode = nullptr;

		copyTempMaze();
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
	char path = NULL;
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
	}
	return path;
}

int Maze::playerPositions(int players) {
	playerPosMaze = mazeVect;
	backupPMaze = playerPosMaze;

	int sizeofCol = 0;
	int prevx = 0;
	int prevy = 0;
	bool skipped = false;
	bool progress = false;
	char path = NULL;
	char tempPath = NULL;
	char progressPrint;

	cout << "\n\n\n--- Player progressions ---\n";
	for (int a = 0; a <= (*allPlayers).size(); a++) {
		
		while ((*allPlayers)[a]->size() != 0) {
			if (sizeofCol == (*allPlayers).size()) {
				return 1;
			}
			else {
				sizeofCol = 0;
				for (int i = 0; i < (*allPlayers).size(); i++) {
					for (int j = 0; j < (*allPlayers)[i]->size(); j++) {

						if ((*allPlayers)[i]->size() <= 0) {
							break;
						}
						else {
							prevx = allPlayers->at(i)->at(0).prevx;
							prevy = allPlayers->at(i)->at(0).prevy;

							if ((*allPlayers)[i]->size() <= 1) {
								sizeofCol += 1;
								break;
							}

							path = switchPlayer(i);
							cout << "\nPlayer " << path << " turn:\n";

							for (int i = 0; i < playerPosMaze.size(); i++) {
								for (int j = 0; j < playerPosMaze[i].size(); j++) {
									
									if (skipped == false && playerPosMaze[i][j] == path) {
										playerPosMaze[i][j] = ' ';
									}
									if (skipped == true) {
										if (backupPMaze[i][j] == path) {
											backupPMaze[i][j] = ' ';
											playerPosMaze = backupPMaze;
										}
									}
								}
							}
							skipped = false;

							if ((playerPosMaze)[allPlayers->at(i)->at(0).prevx][allPlayers->at(i)->at(0).prevy] < 97) {
								playerPosMaze[allPlayers->at(i)->at(0).prevx][allPlayers->at(i)->at(0).prevy] = path;

								if ((*allPlayers)[i]->size() == 1) {
									break;
								}
								if ((*allPlayers)[i]->size() == 2) {
									playerPosMaze[allPlayers->at(i)->at(0).x][allPlayers->at(i)->at(0).y] = 'F';
									(*allPlayers)[i]->erase((*allPlayers)[i]->begin());
								}
								else {
									(*allPlayers)[i]->erase((*allPlayers)[i]->begin());
								}

							}
							else {
								cout << "---- Skipped ----\n";
								playerPosMaze = backupPMaze;
								skipped = true;
								tempPath = path;
							}
							sizeofCol += (*allPlayers)[i]->size();

							if (progress == false) {
								printPlayerMove();
								cout << "\nEnter s to save maze progression\n";
								cout << "\nEnter 1 to continue or enter anything else to print all player movement mazes\n";
								cin >> progressPrint;
								if (progressPrint == 's') {
									saveProgression();
									cout << "\nEnter 1 to continue or enter anything else to print all player movement mazes\n";
									cin >> progressPrint;
								}
								(progressPrint == '1' ? progress = false : progress = true);
							}
							else {
								printPlayerMove();
							}
							backupPMaze = playerPosMaze;
						}
						break;
					}
				}
			}
			firstMove = false;
		}
	}
	return 1;
}

void Maze::mazeSolvable() {
	int playerCount = 0;

	for (int i = 0; i < playerPosMaze.size(); i++) {
		for (int j = 0; j < playerPosMaze[i].size(); j++) {
			(playerPosMaze[i][j] >= 97 ? playerCount++ : playerCount = playerCount);
		}
	}

	if (playerCount == 8) {
		cout << "\n--- Maze not solvable ---\n"<<"--- Deadlock scenario ---\n";
	}
	else if (playerCount >= 2 && playerCount < 8) {
		cout << "\n--- Maze partially solvable ---\n" << "--- Deadlock scenario ---\n";
	}
	else {
		cout << "\n--- Maze solvable ---\n" << "--- No Deadlock scenario ---\n";
	}

}


void Maze::mazeAnalysis(int row, int col, int player) {
	int i = 1;

	while (i != 101) {
		int playerRand = rand()% (player-1) + 2;
		int rowRand = rand()% (row-8) + 9;
		int colRand = rand()% (col-8) + 9;

		cout <<"\nPlayers: "<< playerRand << " - " <<colRand << "x" << rowRand;

		cout << "\n------  MAZE " << i << "  ------\n";
		clearAllMazes();
		createMaze(rowRand, colRand, playerRand);
		createMiddle(rowRand, colRand);
		printMaze();

		i++;
	}

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
	cout << "\nShortest route for all players\n";
	for (int i = 0; i < mazeSol.size(); i++) {
		for (int j = 0; j < mazeSol[i].size(); j++) {
			cout << mazeSol[i][j] << ' ';
		}
		cout << '\n';
	}
}

void Maze::printPlayerMove() {
	for (int i = 0; i < playerPosMaze.size(); i++) {
		for (int j = 0; j < playerPosMaze[i].size(); j++) {
			if (playerPosMaze[i][j] == 'P' && firstMove == false) {
				playerPosMaze[i][j] = ' ';
			}
			cout << playerPosMaze[i][j] << ' ';
		}
		cout << '\n';
	}
}


void Maze::clearAllMazes() {
	mazeVect.clear();
	mazeSol.clear();
	tempMaze.clear();
	allPlayers->clear();
	playerPosMaze.clear();
	backupPMaze.clear();
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


void Maze::saveProgression() {
	ofstream mazeTxt;
	string input;
	vector<vector<char>> tempPrint;

	cout << "Enter file save name: ";
	cin >> input;
	mazeTxt.open(input + ".txt");

	tempPrint = playerPosMaze;

	for (const auto& x : tempPrint) {
		copy(x.begin(), x.end(), ostream_iterator<char>(mazeTxt, " "));
		mazeTxt << '\n';
	}

	mazeTxt.close();

	cout << "File saved as " << input << ".txt" << endl;
	tempPrint.clear();
}

void Maze::readFile(string in) throw (invalid_argument) {

	bool valid = false;
	string input;
	string output;
	input = in;
	ifstream readMaze(input + ".txt");

	if (readMaze.is_open()) {
		while (getline(readMaze, output)) {
			if (input != "information" && (output.find("X X ") != std::string::npos || output.find("E") != std::string::npos || output.find("P") != std::string::npos || output.find("F") != std::string::npos)) {
				valid = true;
				cout << output;
				cout << '\n';
			}
			else {
				cout << output;
				cout << '\n';
			}
		}
		if (input != "information") {
			cout << (valid == true ? "\nValid Maze\n" : "\nNot Valid maze\n");
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





