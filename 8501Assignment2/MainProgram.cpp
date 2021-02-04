//Author: Jane Lee
//Date: 11/2020
//8501 Programming CW2

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdlib.h>

#include "Maze.h"

using namespace std;

int main() {

	Maze* testM = new Maze();
	char input;
	int r = 0;
	int c = 0;
	int players = 0;
	bool notDoneB = false;
	int noLRow = 0;
	int noLCol = 0;
	int noLPlayer = 0;
	string fileName;
	bool fromI = false;


	cout << " - MENU - \n"
		<< " - m = Show Menu\n"
		<< " - r = Restart Program\n"
		<< " - n = Create new maze\n"
		<< " - b = Find all routes (player progression)\n"
		<< " - f = Shortest path out of all routes\n"
		<< " - t = Maze analysis\n"
		<< " - i = Info displaying properties of different maze and player combinations\n"
		<< " - s = Save CURRENT shown Maze to file\n"
		<< " - a = Save BLANK maze to file\n"
		<< " - o = Open file\n"
		<< " - e = Exit program\n\n"
		<< "Please enter a character:\n" << endl;

	cin >> input;

	while (input != NULL) {

		switch (input) {

		case 'n':
			testM->setMazeLimit(false);
			testM->clearAllMazes();
			cout << "Enter row size from 9 to 31: ";
			cin >> r;
			testM->setRow(r);
			cout << "Enter column size from 9 to 31: ";
			cin >> c;
			testM->setCol(c);
			cout << "Enter no. players from 1 to 8: "; 
			cin >> players;

			while (cin.fail()) {
				cout << "\n\nWrong input, please try again\n";
				cin.clear();
				cin.ignore();
				r = 0;
				c = 0;
				players = 0;
				cout << "Enter row size from 7 to 51: ";
				cin >> r;
				testM->setRow(r);
				cout << "Enter column size from 7 to 51: ";
				cin >> c;
				testM->setCol(c);
				cout << "Enter no. exits from 1 to " << (((testM->getRow() * 2) + (testM->getCol() * 2)) - 4) / 4 << ": ";
				cin >> players;
			}

			testM->createMaze(r, c, players);
			testM->createMiddle(testM->getRow(), testM->getCol());
			cout << endl;
			testM->printMaze();

			cout << "\nEnter character for next operation: ";
			cin >> input;
			r = 0;
			c = 0;

			break;

		case 'b':
			if (testM->getMazeLimit() != true) {
				if (testM->getMaze().size() <= 0) {
					cout << "No maze found, please create a maze\n\n";
					input = 'n';
				}
				else {
					testM->pPos();
					testM->copyOGMaze();

					for (int i = 0; i < players; i++) {
						testM->getpPos();
						testM->findPath(testM->getMaze(), testM->getTempi(), testM->getTempj(), testM->getRow() / 2, testM->getCol() / 2, i);
					}
					testM->playerPositions(players);
					testM->mazeSolvable();

					if (notDoneB == false) {
						cout << endl;
						testM->printSolution();
						testM->setShouldPrint(true);
						cout << "\nEnter character for next operation: ";
						cin >> input;
					}
					if (notDoneB == true) {
						testM->setShouldPrint(false);
						input = 'f';
						notDoneB = false;
					}
				}
			}
			else {
				cout << "\nUnable to use maze from analysis, please create a new maze\n";
				cout << "\nEnter character for next operation: ";
				cin >> input;
			}
			break;

		case 'f':
			if (testM->getMaze().size() <= 0) {
				cout << "No maze found, please create a maze\n\n";
				input = 'n';
			}
			else if (testM->getSolMaze().size() <= 0 && testM->getMaze().size() > 0) {
				notDoneB = true;
				input = 'b';
				testM->setShouldPrint(false);
			}
			else {
				cout << endl;
				testM->printShortestRoute();
				testM->setShouldPrint(false);
				cout << "\nEnter character for next operation: ";
				cin >> input;
			}
			break;

		case 't':
			testM->setMazeLimit(true);
			cout << "Enter row limit:\n";
			cin >> noLRow;
			cout << "Enter col limit:\n";
			cin >> noLCol;
			cout << "Enter players limit:\n";
			cin >> noLPlayer;
			cout << "\n100 random mazes with max size limit of "<< noLRow <<"x" <<noLCol << " and max "<< noLPlayer <<" players:\n";
			testM->mazeAnalysis(noLRow, noLCol, noLPlayer);
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;

		case 'i':
			fromI = true;
			input = 'o';
			break;

		case 's':
			testM->setprintOriginal(false);
			testM->writeFile();
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;

		case 'a':
			testM->setprintOriginal(true);
			testM->writeFile();
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;

		case 'o':
			try {
				if (fromI == false) {
					cout << "Enter file name to open: ";
					cin >> fileName;
				}
				else {
					fileName = "information";
					fromI = false;
				}
				cout << '\n';
				testM->readFile(fileName);
			}
			catch (const invalid_argument& iae) {
				cout << iae.what() << endl;
			}
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;

		case 'm':
			cout << "\n - MENU - \n"
				<< " - m = Show Menu\n"
				<< " - r = Restart Program\n"
				<< " - n = Create new maze\n"
				<< " - b = Find all routes (player progression)\n"
				<< " - f = Shortest path out of all routes\n"
				<< " - t = Maze analysis\n"
				<< " - i = Info displaying properties of different maze and player combinations\n"
				<< " - s = Save CURRENT shown Maze to file\n"
				<< " - a = Save BLANK maze to file\n"
				<< " - o = Open file\n"
				<< " - e = Exit program\n";
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;

		case 'r':
			cout << "\nProgram Restarted\n";
			r = 0;
			c = 0;
			players = 0;
			notDoneB = false;
			testM->setMazeLimit(false);
			testM->clearAllMazes();
			input = 'm';
			break;

		case 'e':
			cout << "Exiting...";
			delete testM;
			testM = nullptr;
			return 0;

		default:
			cout << "Please try again: ";
			cin >> input;
			break;
		}

	}

	delete testM;
	testM = nullptr;
	return 0;
}