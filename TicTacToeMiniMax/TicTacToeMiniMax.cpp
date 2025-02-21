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
void ClearBoard();

bool GameOver(int whoWon);
bool PlaceMarker(int slot);
bool isSpotsLeft(char Board[3][3]);
bool PlayAgain();
int AiMove(char Board[3][3]);
int CheckForWin(char Board[3][3]);
int Minimax(char Board[3][3], int depth, bool isMaximizing);

char Board[3][3] = { {' ', ' ', ' '},{' ',' ',' '},{' ',' ',' '} };
char PlayerMarker;
const char human = 'o';
const char artificial = 'x';




int main()
{
	do
	{
		PlayGame();
	} while (PlayAgain());
	
}


void PlayGame()
{
	ClearBoard();
	int whoWon = NULL;
	
	cout << "\n\n   --------------------------------\n";
	cout << "   Welcome to Tic Tac Toe with Artie:\n";
	cout << "the open slots are in numerical order (1-9)\n";
	cout << "   --------------------------------\n\n";

	/*while (true)
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
	}*/

	/*if (human == 'o')
	{
		AiMove(Board);
	}*/
	
	DrawBoard();
	do
	{
		
		AiMove(Board);
		DrawBoard();

		int retflag;
		whoWon = CheckForWin(Board); /*fix check for win : and display results*/
		DisplayResults(whoWon, retflag);
		if (retflag == 2) break;

		HumanMove();
		DrawBoard();

	} while (!GameOver(whoWon)/*isSpotsLeft(Board) != false*/);
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

	if (Board[row][col] != artificial && Board[row][col] != human)
	{
		Board[row][col] = human;
	}
	else
	{
		cout << "Invalid Entry:\n";
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
	if (CheckForWin(Board) == +10)
	{
		/*if (human == 'x')
		{
			cout << "\nThe human won" << endl;
			{ retflag = 2; return; };
		}
		else
		{
			cout << "\nArtie won" << endl;
			{ retflag = 2; return; };
		}*/

		cout << "\nArtie won" << endl;
		{ retflag = 2; return; };
	}
	if (CheckForWin(Board) == -10)
	{
		/*if (artificial == 'o')
		{
			cout << "\nArtie won" << endl;
			{ retflag = 2; return; };
		}
		else
		{
			cout << "\nThe human won" << endl;
			{ retflag = 2; return; };
		}*/
		cout << "\nHuman won" << endl;
		{ retflag = 2; return; };

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
			if (Board[i][0] == artificial)
			{
				return +10;
			}
			else if (Board[i][0] == human)
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
			if (Board[0][i] == artificial)
			{
				return +10;
			}
			else if (Board[0][i] == human)
			{
				return -10;
			}
		}
	}
	/*Diagonal win*/
	if (Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2])
	{
		if (Board[0][0] == artificial)
		{
			return +10;
		}
		else if (Board[0][0] == human)
		{
			return -10;
		}
	}

	if (Board[2][0] == Board[1][1] && Board[1][1] == Board[0][2])
	{
		if (Board[2][0] == artificial)
		{
			return +10;
		}
		else if (Board[2][0] == human)
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

bool PlayAgain()
{
	const int IGNORE_CHARS = 256;
	char answer = 'y';
	bool failure;
	do
	{
		failure = false;
		cout << "\nWould like to challenge Artie again: (y/n) ";
		cin >> answer;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << "Invalid input ";
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');
			answer = tolower(answer);
		}
	} while (failure);
	
	return answer == 'y';
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
				Board[i][j] = artificial;
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
	cout << endl;
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

	if (!isSpotsLeft(Board))
	{
		return 0;
	}
	/*if (score == 0)
	{
		return score;
	}*/


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
					Board[i][j] = human;
					int score = Minimax(Board, depth + 1, true);
					bestScore = min(score, bestScore);
					Board[i][j] = ' ';


				}
			}
		}
		return bestScore;
	}
}

void ClearBoard()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Board[i][j] = ' ';
		}
	}
}
bool GameOver(int whoWon)
{
	return whoWon == +10 || whoWon == -10 || isSpotsLeft(Board)== false;
}