#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>

// Board propogation rules:
// < 2 living neighbours = death
// > 3 living neighbours = death
// == 3 live neighbours = alive

void goto_xy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Board
{
	Board(int x, int y, double proportion)
	{
		create_board(x, y);
		populate_board(proportion);
	}

	void display_board()
	{
		goto_xy(0, 10);
		for (size_t i = 0; i < board.size(); ++i)
		{
			for (size_t j = 0; j < board[0].size(); ++j)
			{
				if (board[i][j] == 1) std::cout << "#";
				else std::cout << " ";
			}
			std::cout << std::endl;
		}
	}	

	void populate_board(const double proportion)
	{
		// Seed
		srand(static_cast<unsigned int>(time(nullptr)));
		int alive = 0;
		for (size_t i = 0; i < board.size(); ++i)
		{
			for (size_t j = 0; j < board[0].size(); ++j)
			{
				double random = (double)rand() / RAND_MAX;
				if (random <= proportion) 
				{
					board[i][j] = 1;
					++alive;
				}			
			}
		}
		living = alive;
	}

	void create_board(const int X, const int Y)
	{
		for (int i = 0; i < Y; ++i)
		{
			std::vector<int> line;
			for (int j = 0; j < X; ++j)
			{
				line.push_back(0);	
			}

			board.push_back(line);
		}
	}

	void simulate_generation()
	{
		living = 0;
		std::vector<std::vector<int>> second_board;
		for (size_t i = 0; i < board.size(); ++i)
		{
			std::vector<int> line;
			for (size_t j = 0; j < board.size(); ++j)
			{
				// This is a lazy approach, there are more optimised methods
				int living_neighbours = 0;
				// Row above
				if (i != 0)
				{
					if (board[i-1][j-1] == 1 && j != 0) ++living_neighbours;
					if (board[i-1][j] == 1) ++living_neighbours;
					if (board[i-1][j+1] == 1 && j != board[0].size() - 1) ++living_neighbours;
				}
				// Left cell
				if (j != 0 && board[i][j-1] == 1) ++living_neighbours;
				// Right cell
				if (j != board[0].size() - 1 && board[i][j+1] == 1) ++living_neighbours;
				// Row below
				if (i != board.size() - 1)
				{
					if (board[i+1][j-1] == 1 && j != 0) ++living_neighbours;
					if (board[i+1][j] == 1) ++living_neighbours;
					if (board[i+1][j+1] == 1 && j != board[0].size() - 1) ++living_neighbours;
				}

				// Evaluate
				if (living_neighbours < 2 || living_neighbours > 3) line.push_back(0);
				else if (living_neighbours == 3) 
				{
					++living;
					line.push_back(1);
				}
				else if (board[i][j] == 1) 
				{
					++living;
					line.push_back(1);
				}
				else line.push_back(0);
			}
			second_board.push_back(line);
		}

		// Fold new board into old board
		board = second_board;
		++generations;
	}

	std::vector<std::vector<int>> board;
	int generations = 0;
	int living;
};

void hide_cursor()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(console, &cursor_info);
	cursor_info.bVisible = FALSE;
	SetConsoleCursorInfo(console, &cursor_info);
}

int main()
{
	system("cls");
	const int X = 50;
	const int Y = 50;
	const double PROPORTION = 0.2d;

	Board game = Board(X, Y, PROPORTION);
	game.display_board();
	hide_cursor();

	while (true)
	{
		Sleep(10);
		goto_xy(0,0);
		std::cout << "Generations: " << game.generations << "     " << std::endl;
		std::cout << "Alive: " << game.living << "       " << std::endl;
		std::cout << "\n\n\n\n\n" << std::endl;
		game.simulate_generation();
		game.display_board();
	}

	return 0;
}
