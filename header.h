#pragma once
#include <windows.h>
#include<iostream>
#include<ctime>
#include<fstream>
#include <filesystem>
using namespace std;


unique_ptr<unique_ptr<char[]>[]> fill_board(int size)
{
	int l;
	unique_ptr<unique_ptr<char[]>[]>board(new unique_ptr<char[]>[size]);
	for (int i = 0; i < size; i++)
	{
		board[i] = unique_ptr<char[]>(new char[size]);
	}

	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			l = rand() % 2;
			if (l)
			{
				board[i][j] = 'o';
			}
			else
			{
				board[i][j] = '.';
			}

		}
	}
	return board;
}




unique_ptr<unique_ptr<char[]>[]> fill_board_2(int size)
{
	unique_ptr<unique_ptr<char[]>[]>board(new unique_ptr<char[]>[size]);
	for (int i = 0; i < size; i++)
	{
		board[i] = unique_ptr<char[]>(new char[size]);
	}

	char a = '.';
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << "[" << i << "]" << "[" << j << "]" << endl;
			cin >> a;
			while (a != 'o' && a != '.')
			{
				cout << "[" << i << "]" << "[" << j << "]" << endl;
				cin >> a;
			}
			board[i][j] = a;
		}
	}
	return board;
}

unique_ptr<unique_ptr<char[]>[]> fill_blinker(int &size)
{
	if (size < 5)
	{
		size = 5;
	}

	unique_ptr<unique_ptr<char[]>[]>board(new unique_ptr<char[]>[size]);
	for (int i = 0; i < size; i++)
	{
		board[i] = unique_ptr<char[]>(new char[size]);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = '.';
		}
	}

	board[1][2] = 'o';
	board[2][2] = 'o';
	board[3][2] = 'o';
	return board;
}

unique_ptr<unique_ptr<char[]>[]> fill_glider(int &size)
{
	if (size < 5)
	{
		size = 5;
	}

	fstream file;
	unique_ptr<unique_ptr<char[]>[]>board(new unique_ptr<char[]>[size]);
	for (int i = 0; i < size; i++)
	{
		board[i] = unique_ptr<char[]>(new char[size]);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = '.';
		}
	}

	board[2][2] = 'o';
	board[3][2] = 'o';
	board[4][2] = 'o';
	board[4][1] = 'o';
	board[3][0] = 'o';

	return board;
}

unique_ptr<unique_ptr<char[]>[]> load_rle(unique_ptr<unique_ptr<char[]>[]> board, filesystem::path path, int size)
{
	string line, encode = "", cur, prev;
	auto c = 5;

	if (filesystem::exists(path))
	{
		fstream copperhead(path);
		while (!copperhead.eof())
		{
			getline(copperhead, line, '$');
			for (int i = 0; i < line.size(); i++)
			{
				prev = line[i];
				cur = line[i + 1];
				if (prev == "b" || prev == "o")
				{
					encode = encode + prev;
					continue;
				}
				if (cur == "b" || cur == "o")
				{
					for (int j = 0; j < stoi(prev); j++)
					{
						encode = encode + cur;
					}
					i++;
				}
				if (cur != "b" && cur != "o" && prev != "b" && prev != "o")
				{
					string w = prev + cur;
					for (int j = 0; j < stoi(w)-1; j++)
					{
						if (i + 2 < line.size())
							encode = encode + line[i + 2];
						
					}
					i++;
				}	

			}

			for (int i = 0; i < encode.size(); i++)
			{
				if (encode[i] == 'b')
				{
					encode[i] = '.';
				}
				board[c][i] = encode[i];
			}
			if (line[line.size() - 1] == '2')
			{
				c++;
			}
			c++;
			encode = "";
		}
		copperhead.close();
	}
	return board;
}

unique_ptr<unique_ptr<char[]>[]> fill_copperhead(int &size)
{
	string line, encode = "", cur, prev;
	int c = 0;
	if (size < 20)
	{
		size = 20;
	}

	unique_ptr<unique_ptr<char[]>[]>board(new unique_ptr<char[]>[size]);
	for (int i = 0; i < size; i++)
	{
		board[i] = unique_ptr<char[]>(new char[size]);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = '.';
		}
	}
	filesystem::path path{ "E:\\Studia/VI semestr/C++ pliki/copperhead.txt" };
	if (filesystem::exists(path))
	{
		board = load_rle(move(board), path, size);
	}
	return board;
}

unique_ptr<unique_ptr<char[]>[]> fill_queen_bee_shuttle(int &size)
{
	string line, encode = "", cur, prev;
	int c = 0;
	if (size < 23)
	{
		size = 23;
	}

	unique_ptr<unique_ptr<char[]>[]>board(new unique_ptr<char[]>[size]);
	for (int i = 0; i < size; i++)
	{
		board[i] = unique_ptr<char[]>(new char[size]);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = '.';
		}
	}
	filesystem::path path{ "E:\\Studia/VI semestr/C++ pliki/queen bee shuttle.txt" };
	if (filesystem::exists(path))
	{
		board = load_rle(move(board), path, size);
	}
	return board;
}
unique_ptr<unique_ptr<char[]>[]> fill_gosper_glider_gun(int &size)
{
	string line, encode = "", cur, prev;
	int c = 0;
	if (size < 36)
	{
		size = 36;
	}

	unique_ptr<unique_ptr<char[]>[]>board(new unique_ptr<char[]>[size]);
	for (int i = 0; i < size; i++)
	{
		board[i] = unique_ptr<char[]>(new char[size]);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = '.';
		}
	}
	filesystem::path path{ "E:\\Studia/VI semestr/C++ pliki/gosper glider gun.txt" };
	if (filesystem::exists(path))
	{
		board = load_rle(move(board), path, size);
	}
	return board;
}


unique_ptr<unique_ptr<char[]>[]> write_board(int size, unique_ptr<unique_ptr<char[]>[]>board)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	return board;
}

unique_ptr<unique_ptr<char[]>[]> update_board(int size, unique_ptr<unique_ptr<char[]>[]>board)
{
	int new_i, new_j, count;
	int coordinate_i[8] = { -1,0,1,-1,1,-1,0,1 };
	int coordinate_j[8] = { -1,-1,-1,0,0,1,1,1 };

	unique_ptr<unique_ptr<char[]>[]> new_board(new unique_ptr<char[]>[size]);
	for (int i = 0; i < size; i++)
	{
		new_board[i] = unique_ptr<char[]>(new char[size]);
	}


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			count = 0;
			for (int k = 0; k < 8; k++)
			{
				new_i = i + coordinate_i[k];
				new_j = j + coordinate_j[k];
				if (new_i < 0)
				{
					new_i = size - 1;
				}
				if (new_i >= size)
				{
					new_i = 0;
				}
				if (new_j < 0)
				{
					new_j = size - 1;
				}
				if (new_j >= size)
				{
					new_j = 0;
				}

				if (board[new_i][new_j] == 'o')
				{
					count++;
				}

			}

			if (count == 3 && board[i][j] == '.')
			{
				new_board[i][j] = 'o';
			}

			else if ((count == 2 || count == 3) && board[i][j] == 'o')
			{
				new_board[i][j] = 'o';
			}

			else
			{
				new_board[i][j] = '.';
			}
		}

	}


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = new_board[i][j];
		}
	}
	return board;

}

unique_ptr<unique_ptr<char[]>[]> update_board_without_boundary(int size, unique_ptr<unique_ptr<char[]>[]>board)
{

	int new_i, new_j, count;
	int coordinate_i[8] = { -1,0,1,-1,1,-1,0,1 };
	int coordinate_j[8] = { -1,-1,-1,0,0,1,1,1 };

	unique_ptr<unique_ptr<char[]>[]> new_board(new unique_ptr<char[]>[size]);
	for (int i = 0; i < size; i++)
	{
		new_board[i] = unique_ptr<char[]>(new char[size]);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			count = 0;
			for (int k = 0; k < 8; k++)
			{
				new_i = i + coordinate_i[k];
				new_j = j + coordinate_j[k];


				if (new_i<0 || new_j<0 || new_i >=size || new_j >=size)
				{
					continue;
				}
				if (board[new_i][new_j] == 'o')
				{
					count++;
				}

			}

			if (count == 3 && board[i][j] == '.')
			{
				new_board[i][j] = 'o';
			}

			else if ((count == 2 || count == 3) && board[i][j] == 'o')
			{
				new_board[i][j] = 'o';
			}

			else
			{
				new_board[i][j] = '.';
			}
		}

	}


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = new_board[i][j];
		}
	}
	return board;


}


unique_ptr<unique_ptr<char[]>[]> display(int size, int iteration, unique_ptr<unique_ptr<char[]>[]>board)
{
	int iter = 0;
	int iter2 = 0;
	int fps=1;
	int iter_time;
	int sleep_time;
	int real_fps;
	string w2="";
		sf::RenderWindow window(sf::VideoMode(900,900), "Game of life");
		sf::CircleShape shape(10.f);
		sf::CircleShape shape2(10.f);
		shape.setFillColor(sf::Color::Green);
		shape2.setFillColor(sf::Color::Red);
		sf::Event event;

		unique_ptr<unique_ptr<unique_ptr<char[]>[]>[]> new_board(new unique_ptr<unique_ptr<char[]>[]>[size]);
		for (int i = 0; i < size; i++)
		{
			new_board[i] = unique_ptr<unique_ptr<char[]>[]>(new unique_ptr<char[]>[size]);
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				new_board[i][j]= unique_ptr<char[]>(new char[size]);
			}
		}


	    while (window.isOpen())
		{
				for (iter; iter < iteration; iter++)
				{
					unsigned __int64 start = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
					while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
						{
							iter = iteration;
							window.close();
						}


						if (event.type == sf::Event::TextEntered)
						{
							if (event.text.unicode <=57 && event.text.unicode >=48)
							{
								string w(1, static_cast<char>(event.text.unicode));
								w2 += w;
							}
						}

						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
						{
							cout << w2<<endl;
							fps = stoi(w2);
							w2 = "";
							break;
						}

						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
						{
							while(true)
							{
								window.pollEvent(event);
								if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
								{
									break;
								}

									if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add)
									{
										for (int i = 0; i < size; i++)
										{
											for (int j = 0; j < size; j++)
											{
												shape.setPosition(j * 20.f, i * 20.f);
												shape2.setPosition(j * 20.f, i * 20.f);
												if (board[i][j] == 'o')
												{
													window.draw(shape);
												}
												if (board[i][j] == '.')
												{
													window.draw(shape2);
												}
											}
										}
										window.display();
										for (int i = 0; i < size; i++)
										{
											for (int j = 0; j < size; j++)
											{
												iter2 = iter;
												while (iter2 >= size)
												{
													iter2 = iter2 - size;
												}
												new_board[iter2][i][j] = board[i][j];
											}
										}
										board = update_board(size, move(board));
										iter++;
									}



									if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract)
									{
										iter2--;
										if (iter2 <= 0)
										{
											iter2 = 0;
										}
										if (iter2 <= 0 && iter>size)
										{
											iter2 = size-1;
										}

	

										for (int i = 0; i < size; i++)
										{
											for (int j = 0; j < size; j++)
											{
												shape.setPosition(j * 20.f, i * 20.f);
												shape2.setPosition(j * 20.f, i * 20.f);
												if (new_board[iter2][i][j] == 'o')
												{
													window.draw(shape);
												}
												if (new_board[iter2][i][j] == '.')
												{
													window.draw(shape2);
												}
											}
										}
										window.display();

										for (int i = 0; i < size; i++)
										{
											for (int j = 0; j < size; j++)
											{
												board[i][j] = new_board[iter2][i][j];
											}
										}
									
									}


							}
						}


					}



					for (int i = 0; i < size; i++)
					{
						for (int j = 0; j < size; j++)
						{
							shape.setPosition(j * 20, i * 20);
							shape2.setPosition(j * 20, i * 20);
							if (board[i][j] == 'o')
							{
								window.draw(shape);
							}
							if (board[i][j] == '.')
							{
								window.draw(shape2);
							}
						}
					}
					window.display();
					
					for (int i = 0; i < size; i++)
					{
						for (int j = 0; j < size; j++)
						{
							iter2 = iter;
							while(iter2>=size)
							{
								iter2 = iter2 - size;
							}
							new_board[iter2][i][j] = board[i][j];
						}
					}
					board = update_board(size, move(board));
					unsigned __int64 stop = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
					int iter_time = stop - start;
					int sleep_time= (1000 - fps * iter_time) / fps;
					if (sleep_time > 0)
					{
						Sleep(sleep_time);
					}
					else
					{
						sleep_time = 0;
					}
					real_fps = 1000 / (iter_time + sleep_time);
					if (real_fps == 0)
					{
						real_fps = 1;
					}
					if (iter%real_fps == 0)
					cout << "FPS: " << real_fps<< endl;
				}

				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						iter = iteration;
						window.close();
					}
				}

	     }
	return board;
}

unique_ptr<unique_ptr<char[]>[]> display_without_boundary(int size, int iteration, unique_ptr<unique_ptr<char[]>[]>board)
{
	int iter = 0;
	int iter2 = 0;
	int fps = 1;
	int iter_time;
	int sleep_time;
	int real_fps;
	string w2 = "";
	sf::RenderWindow window(sf::VideoMode(900, 900), "Game of life");
	sf::CircleShape shape(10.f);
	sf::CircleShape shape2(10.f);
	shape.setFillColor(sf::Color::Green);
	shape2.setFillColor(sf::Color::Red);
	sf::Event event;

	unique_ptr<unique_ptr<unique_ptr<char[]>[]>[]> new_board(new unique_ptr<unique_ptr<char[]>[]>[size]);
	for (int i = 0; i < size; i++)
	{
		new_board[i] = unique_ptr<unique_ptr<char[]>[]>(new unique_ptr<char[]>[size]);
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			new_board[i][j] = unique_ptr<char[]>(new char[size]);
		}
	}


	while (window.isOpen())
	{
		for (iter; iter < iteration; iter++)
		{
			unsigned __int64 start = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					iter = iteration;
					window.close();
				}


				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode <= 57 && event.text.unicode >= 48)
					{
						string w(1, static_cast<char>(event.text.unicode));
						w2 += w;
					}
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
				{
					cout << w2 << endl;
					fps = stoi(w2);
					w2 = "";
					break;
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				{
					while (true)
					{
						window.pollEvent(event);
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
						{
							break;
						}

						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add)
						{
							for (int i = 0; i < size; i++)
							{
								for (int j = 0; j < size; j++)
								{
									shape.setPosition(j * 20.f, i * 20.f);
									shape2.setPosition(j * 20.f, i * 20.f);
									if (board[i][j] == 'o')
									{
										window.draw(shape);
									}
									if (board[i][j] == '.')
									{
										window.draw(shape2);
									}
								}
							}
							window.display();
							for (int i = 0; i < size; i++)
							{
								for (int j = 0; j < size; j++)
								{
									iter2 = iter;
									while (iter2 >= size)
									{
										iter2 = iter2 - size;
									}
									new_board[iter2][i][j] = board[i][j];
								}
							}
							board = update_board_without_boundary(size, move(board));
							iter++;
						}



						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract)
						{
							iter2--;
							if (iter2 <= 0)
							{
								iter2 = 0;
							}
							if (iter2 <= 0 && iter > size)
							{
								iter2 = size - 1;
							}



							for (int i = 0; i < size; i++)
							{
								for (int j = 0; j < size; j++)
								{
									shape.setPosition(j * 20.f, i * 20.f);
									shape2.setPosition(j * 20.f, i * 20.f);
									if (new_board[iter2][i][j] == 'o')
									{
										window.draw(shape);
									}
									if (new_board[iter2][i][j] == '.')
									{
										window.draw(shape2);
									}
								}
							}
							window.display();

							for (int i = 0; i < size; i++)
							{
								for (int j = 0; j < size; j++)
								{
									board[i][j] = new_board[iter2][i][j];
								}
							}

						}


					}
				}


			}



			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					shape.setPosition(j * 20, i * 20);
					shape2.setPosition(j * 20, i * 20);
					if (board[i][j] == 'o')
					{
						window.draw(shape);
					}
					if (board[i][j] == '.')
					{
						window.draw(shape2);
					}
				}
			}
			window.display();

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					iter2 = iter;
					while (iter2 >= size)
					{
						iter2 = iter2 - size;
					}
					new_board[iter2][i][j] = board[i][j];
				}
			}
			board = update_board_without_boundary(size, move(board));
			unsigned __int64 stop = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
			int iter_time = stop - start;
			int sleep_time = (1000 - fps * iter_time) / fps;
			if (sleep_time > 0)
			{
				Sleep(sleep_time);
			}
			else
			{
				sleep_time = 0;
			}
			if((iter_time + sleep_time)!=0)
			real_fps = 1000 / (iter_time + sleep_time);
			if (real_fps == 0)
			{
				real_fps = 1;
			}
			if (iter%real_fps == 0)
				cout << "FPS: " << real_fps << endl;
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				iter = iteration;
				window.close();
			}
		}

	}
	return board;
}

















