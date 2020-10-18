// TicTacToeMiniMax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Move
{
	int row, col;
};

void DrawBoard();
void PlayGame();
void HumanMove();
void DisplayResults(int whoWon, int& retflag);
bool PlaceMarker(int slot);
bool isSpotsLeft(char Board[3][3]);
int AiMove(char Board[3][3]);
int CheckForWin(char Board[3][3]);
int Minimax(char Board[3][3], int depth, bool isMaximizing);

char Board[3][3] = { {' ', ' ', ' '},{' ',' ',' '},{' ',' ',' '} };
char PlayerMarker;
char human;
char artificial;

int CurrentPlayer;


int main()
{
	PlayGame();
}


void PlayGame()
{
	int YourMove = NULL;
	int whoWon = NULL;

	/*introduction to game*/

	while (true)
	{
		cout << "Choose X or O: X goes first: ";
		cin >> human;

		if (human == 'x' || human == 'o')
		{
			break;
		}
	}

	if (human == 'x')
	{
		artificial = 'o';
	}
	else
	{
		artificial = 'x';
	}

	if (human == 'o')
	{
		AiMove(Board);
	}

	DrawBoard();
	do
	{	int retflag;
		whoWon = CheckForWin(Board); /*fix check for win : and display results*/
		DisplayResults(whoWon, retflag);
		if (retflag == 2) break;

		HumanMove();
		DrawBoard();

		AiMove(Board);
		DrawBoard();

	} while (isSpotsLeft(Board) == true);
}

void DrawBoard()
{
	cout << "\n" << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << endl;
	cout << "----------" << endl;
	cout << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << endl;
	cout << "----------" << endl;
	cout << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << endl << endl;
}

void HumanMove()
{
	cout << "Enter your move (1-9): ";
	int slot = NULL;
	cin >> slot;
	int row = slot / 3;
	int col = NULL;
	if (slot % 3 == 0)
	{
		row = row - 1;
		col = 2;
	}

	else
	{
		col = (slot % 3) - 1;
	}

	if (Board[row][col] != 'x' && Board[row][col] != 'o')
	{
		Board[row][col] = human;
	}

}
bool PlaceMarker(int slot)
{
	int row = slot / 3;
	int col = NULL;
	if (slot % 3 == 0)
	{
		row = row - 1;
		col = 2;
	}

	else
	{
		col = (slot % 3) - 1;
	}

	if (Board[row][col] != 'x' && Board[row][col] != 'o')
	{
		return Board[row][col] = PlayerMarker;
	}
	else
	{
		return false;
	}
}

void DisplayResults(int whoWon, int& retflag)
{
	retflag = 1;
	if (whoWon == +10)
	{
		if (human == 'x')
		{
			cout << "\nThe human won" << endl;
			{ retflag = 2; return; };
		}
		else
		{
			cout << "\nArtie won" << endl;
			{ retflag = 2; return; };
		}

	}
	if (whoWon == -10)
	{
		if (artificial == 'o')
		{
			cout << "\nArtie won" << endl;
			{ retflag = 2; return; };
		}
		else
		{
			cout << "\nThe human won" << endl;
			{ retflag = 2; return; };
		}
	}

	if (isSpotsLeft(Board) == false)
	{
		cout << "\nIt's a tie game" << endl;
		{ retflag = 2; return; };
	}
}

int CheckForWin(char Board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		/*Horizontal win*/
		if (Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2])
		{
			if (Board[i][0] == 'x' /*artificial*/)
			{
				return +10;
			}
			else if (Board[i][0] == 'o' /*human*/)
			{
				return -10;
			}
		}

	}
	/*Vertical win*/
	for (int i = 0; i < 3; i++)
	{
		if (Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i])
		{
			if (Board[0][i] == 'x')
			{
				return +10;
			}
			else if (Board[0][i] == 'o')
			{
				return -10;
			}
		}
	}
	/*Diagonal win*/
	if (Board[0][2] == Board[1][1] && Board[1][1] == Board[2][2])
	{
		if (Board[0][2] == 'x')
		{
			return +10;
		}
		else if (Board[0][2] == 'o')
		{
			return -10;
		}
	}

	if (Board[2][0] == Board[1][1] && Board[1][1] == Board[0][2])
	{
		if (Board[2][0] == 'x')
		{
			return +10;
		}
		else if (Board[2][0] == 'o')
		{
			return -10;
		}
	}

	return 0;
}

bool isSpotsLeft(char Board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Board[i][j] == ' ')
			{
				return true;
			}
		}
	}

	return false;
}

int AiMove(char Board[3][3])
{
	int bestScore = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Board[i][j] == ' ')
			{
				Board[i][j] = human; /*maximizing changes depending on who goes first*/
				int score = Minimax(Board, 0, false);
				Board[i][j] = ' ';

				if (score > bestScore)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestScore = score;
				}
			}
		}
	}

	cout << "\nArtie has made a move\n";
	return Board[bestMove.row][bestMove.col] = artificial;
}
int Minimax(char Board[3][3], int depth, bool isMaximizing)
{

	int score = CheckForWin(Board);

	if (score == +10)
	{
		return score;
	}

	if (score == -10)
	{
		return score;
	}

	if (isSpotsLeft(Board) == false)
	{
		return 0;
	}


	if (isMaximizing)
	{
		int bestScore = -1000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (Board[i][j] == ' ')
				{
					Board[i][j] = artificial;
					int score = Minimax(Board, depth + 1, false);
					Board[i][j] = ' ';
					bestScore = max(score, bestScore);

				}
			}
		}
		return bestScore;
	}

	else
	{
		int bestScore = 1000;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (Board[i][j] == ' ')
				{
					Board[i][j] = human;
					int score = Minimax(Board, depth + 1, true);
					Board[i][j] = ' ';
					bestScore = min(score, bestScore);

				}
			}
		}
		return bestScore;
	}
}

