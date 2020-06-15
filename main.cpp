#include <SFML/Graphics.hpp>
#include<conio.h>
#include<iostream>
#include"header.h"
#include<fstream>
#include<thread>
using namespace std;
int main()
{
	int size, iteration;
	auto sw = 1;
	fstream configuration;
	unique_ptr<unique_ptr<char[]>[]>board;


	configuration.open("configuration.txt", std::ios::in);
	if (configuration.good() == true)
	{
		configuration.seekp(5, ios::cur);
		configuration >> size;
		configuration.seekp(12, ios::cur);
		configuration >> iteration;
		configuration.close();
	}

	while (true)
	{
		cout << "[1] Random Board" << endl;
		cout << "[2] Fill Board" << endl;
		cout << "[3] Blinker Pattern" << endl;
		cout << "[4] Glider Pattern" << endl;
		cout << "[5] Copperhead Pattern" << endl;
		cout << "[6] Queen Bee Shuttle" << endl;
		cout << "[7] Gosper Glider Gun" << endl;
		cout << "Press any other key to exit" << endl;
		cin >> sw;

		switch (sw)
		{
		case 1:
			board = fill_board(size);
			board = display(size, iteration, move(board));
			break;

		case 2:
			board = fill_board_2(size);
			board = display(size, iteration, move(board));
			break;

		case 3:
			board = fill_blinker(size);
			board = display(size, iteration, move(board));
			break;
		case 4:
			board = fill_glider(size);
			board = display(size, iteration, move(board));
			break;
		case 5:
			board = fill_copperhead(size);
			board = display(size, iteration, move(board));
			break;
		case 6:
			board = fill_queen_bee_shuttle(size);
			board = display(size, iteration, move(board));
			break;
		case 7:
			cout << sizeof(board);
			board = fill_gosper_glider_gun(size);
			board = display_without_boundary(size, iteration, move(board));
			break;
		default:
			exit(0);


		}

	}

	_getch();
}