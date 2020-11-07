//Author: Jane Lee
//Date: 11/2020
//8501 Programming CW1

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

	cout << " - MENU - \n"
		<< " - m = Show Menu\n"
		<< " - n = Create new maze\n"
		<< " - b = Find all routes\n"
		<< " - f = Shortest path out of all routes\n"
		<< " - s = Save CURRENT shown Maze to file\n"
		<< " - a = Save BLANK maze to file\n"
		<< " - o = Open file\n"
		<< " - e or 0 = Exit program\n\n"
		<< "Please enter a character:\n" << endl;;

	cin >> input;

	while (input != NULL) {

		switch (input) {

		case 'n':

			testM->clearAllMazes();
			cout << "Enter row size from 9 to 31: ";
			cin >> r;
			testM->setRow(r);
			cout << "Enter column size from 9 to 31: ";
			cin >> c;
			testM->setCol(c);
			cout << "Enter no. players from 2 to 10: "; ///////////////////////////////////////////////////
			cin >> players;

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
					
					testM->copyTempMaze();
				}
				testM->playerPositions(players);
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
				testM->readFile();
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
				<< " - n = Create new maze\n"
				<< " - b = Find all routes\n"
				<< " - f = Shortest path out of all routes\n"
				<< " - s = Save CURRENT shown Maze to file\n"
				<< " - a = Save BLANK maze to file\n"
				<< " - o = Open file\n"
				<< " - e or 0 = Exit program\n";
			cout << "\nEnter character for next operation: ";
			cin >> input;
			break;

		case 'e':
			cout << "Exiting...";
			delete testM;
			testM = nullptr;
			return 0;

		case '0': //////////////////////////////////////////////////////////////////
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

	return 0;
}