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
void ValidInput(int YourMove, int& tries, int& retflag);
void DisplayResults(int whoWon, int tries, int& retflag);
bool PlaceMarker(int slot);
bool AIPlaceMarker(int slot);
int AiMove();
int NextTurn();
int CheckForWin(char Board[3][3]);
int Minimax(char Board[3][3], int depth, bool isMaximizing);

char Board[3][3] = { {' ', ' ', ' '},{' ',' ',' '},{' ',' ',' '} };
char PlayerMarker;
char human = 'o';
char artificial = 'x';

int CurrentPlayer;


int main()
{
	PlayGame();
}


void PlayGame()
{
	CurrentPlayer = 1;
	int YourMove = NULL;
	int whoWon = NULL;
	int tries = NULL;
	char playerOneMarker = NULL;

	

	DrawBoard();
	/*PlayerMarker = playerOneMarker;*/

	do
	{
		tries++;

		if (CurrentPlayer == 1)
		{
			cout << "Your Move Player " << CurrentPlayer << ": ";
			cin >> YourMove;
		}

		int retflag;
		ValidInput(YourMove, tries, retflag);
		if (retflag == 3) continue;

		DrawBoard();
		/*whoWon = CheckForWin();*/

		DisplayResults(whoWon, tries, retflag);
		if (retflag == 2) break;

		NextTurn();

		AiMove();

	} while (tries < 9);

	if (whoWon == 0)
	{
		cout << "\nIt's a tie game" << endl;
	}
}

void DrawBoard()
{
	cout << "\n" << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << endl;
	cout << "----------" << endl;
	cout << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << endl;
	cout << "----------" << endl;
	cout << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << endl << endl;
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

	if (Board[row][col] != artificial && Board[row][col] != human)
	{
		return Board[row][col] = human;
	}
	else
	{
		return false;
	}
}

bool AIPlaceMarker(int slot)
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

	if (Board[row][col] != artificial && Board[row][col] != human)
	{
		return Board[row][col] = artificial;
	}
	else
	{
		return false;
	}
}

void ValidInput(int YourMove, int& tries, int& retflag)
{
	retflag = 1;
	/*if (YourMove > 9 || YourMove < 0)
	{
		cout << "\nInvalid Input! Try again\n";
		tries--;
		{ retflag = 3; return; };
	}*/

	if (!PlaceMarker(YourMove))
	{
		cout << "\nCan't play here! Try again\n";
		tries--;
		{ retflag = 3; return; };
	}
}

void DisplayResults(int whoWon, int tries, int& retflag)
{
	retflag = 1;
	if (whoWon == 1)
	{
		cout << "\nPlayer One won" << endl;
		{ retflag = 2; return; };
	}
	if (whoWon == 2)
	{
		cout << "\nPlayer Two won" << endl;
		{ retflag = 2; return; };
	}
}

int CheckForWin(char Board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		if (Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2])
		{
			if (Board[i][0] == human)
			{
				return +10;
			}
			else if (Board[i][0] == artificial)
			{
				return -10;
			}
			/*return CurrentPlayer;*/
		}

	}

	for (int i = 0; i < 3; i++)
	{
		if (Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i])
		{
			if (Board[0][i] == human)
			{
				return +10;
			}
			else if (Board[0][i] == artificial)
			{
				return -10;
			}
			/*return CurrentPlayer;*/
		}
	}



	if (Board[0][2] == Board[1][1] && Board[1][1] == Board[2][2])
	{
		if (Board[0][2] == human)
		{
			return +10;
		}
		else if (Board[0][2] == artificial)
		{
			return -10;
		}
		/*return CurrentPlayer;*/
	}
	if (Board[2][0] == Board[1][1] && Board[1][1] == Board[0][2])
	{
		if (Board[2][0] == human)
		{
			return +10;
		}
		else if (Board[2][0] == artificial)
		{
			return -10;
		}
		/*return CurrentPlayer;*/
	}

	return 0;
}

int NextTurn()
{
	if (CurrentPlayer == 1)
	{

		cout << "\nComputer move is: " << AiMove() << endl;
		CurrentPlayer = 2;
	}

	else
	{
		CurrentPlayer = 1;
	}

	/*if (PlayerMarker == 'x')
	{
		PlayerMarker = 'o';
	}
	else
	{
		PlayerMarker = 'x';
	}*/

	return CurrentPlayer;
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

int AiMove()
{
	int bestScore = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Board[i][j] != ' ')
			{
				Board[i][j] = human;
				int score = Minimax(Board, 0, false);
				Board[i][j] = ' ';
				/*bestScore = min(score, bestScore);*/
				if (score > bestScore)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestScore = score;
				}
			}
		}
	}
	return Board[bestMove.row][bestMove.col] = PlayerMarker;

	/*time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);

	int YourMove = (rand() % 9) + 1;

	return YourMove;*/
}
int Minimax(char Board[3][3], int depth, bool isMaximizing)
{
	int score = CheckForWin(Board);

	if (score == 10)
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
					Board[i][j] = human;
					int score = Minimax(Board, depth + 1, true);
					bestScore = max(score, bestScore);
					Board[i][j] = ' ';
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
					Board[i][j] = artificial;
					int score = Minimax(Board, depth + 1, !isMaximizing);
					bestScore = min(score, bestScore);
					Board[i][j] = ' ';
				}
			}
		}
		return bestScore;
	}
}

