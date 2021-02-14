#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

static int hight = 12;
static int width = 50;
static int a, b, ballx, bally, score;
static int tails, tailx[1000], taily[1000];
enum dir : char {
	NON, UP, DOWN, RIGHT, LEFT
} direction;
bool gameOver;
char mode;

using namespace std;

void setup()
{
	srand(time(0));
	tails = 0;
	a = width / 2;
	b = hight / 2;
	ballx = rand() % width - 2;
	bally = rand() % hight - 2;
	if (ballx <= 0)
		ballx = 1;
	if (bally <= 0)
		bally = 1;
	gameOver = false;
	score = 0;
	direction = NON;
}

static void board()
{
	system("cls");
	cout << "SCORE : " << score << "\n\n";
	for (int x = 0; x < hight; x++)
	{
		for (int y = 0; y < width; y++)
		{
			if (y == 0 || y == width - 1 || x == 0 || x == hight - 1)
				cout << "#";
			else if (x == b && y == a)
				cout << "O";
			else if (x == bally && y == ballx)
				cout << "@";
			else
			{
				bool tail = false;
				for (int z = 0; z < tails; z++)
				{
					if (tailx[z] == y && taily[z] == x)
					{
						cout << "o";
						tail = true;
					}
				}
				if (!tail)
					cout << " ";
			}

		}
		cout << "\n";
	}
}

static void dir()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			direction = LEFT;
			break;
		case 's':
			direction = DOWN;
			break;
		case 'w':
			direction = UP;
			break;
		case 'd':
			direction = RIGHT;
			break;
		}
	}
}

static void move()
{
	int pre_tailx = tailx[0];
	int pre_taily = taily[0];
	int pre2_tailx, pre2_taily;
	tailx[0] = a;
	taily[0] = b;
	for (int x = 1; x < tails; x++)
	{
		pre2_tailx = tailx[x];
		pre2_taily = taily[x];
		tailx[x] = pre_tailx;
		taily[x] = pre_taily;
		pre_tailx = pre2_tailx;
		pre_taily = pre2_taily;
	}
	switch (direction)
	{
	case LEFT:
		a--;
		break;
	case DOWN:
		b++;
		break;
	case UP:
		b--;
		break;
	case RIGHT:
		a++;
		break;
	case NON :
		break;
	}
}

static void ball()
{
	if (a == ballx && b == bally)
	{
		ballx = rand() % width - 2;
		bally = rand() % hight - 2;
		if (ballx <= 0)
			ballx = 1;
		if (bally <= 0)
			bally = 1;
		score += 10;
		tails++;
		for (int x = 0; x < tails; x++)
		{
			while (ballx == tailx[x] && bally == taily[x])
			{
				ballx = rand() % width - 2;
				bally = rand() % hight - 2;
				if (ballx <= 0)
					ballx = 1;
				if (bally <= 0)
					bally = 1;
			}
		}
	}
}

static void wall()
{
	if (a == 0)
		a = width - 2;
	else if (a == width - 1)
		a = 1;
	if (b == 0)
		b = hight - 2;
	else if (b == hight - 1)
		b = 1;
}

static void tail()
{
	for (int x = 0; x < tails; x++)
	{
		if (tailx[x] == a && taily[x] == b)
		{
			gameOver = true;
			return;
		}
	}
}

static void box()
{
	if (a == 0 || a == width - 1 || b == 0 || b == hight - 1)
		gameOver = true;
}

static void firma()
{
	cout << "###################################\n";
	cout << "##   MADE BY : MOHAMED HUSSIEN   ##\n";
	cout << "###################################\n\n\n";
}

void choose()
{
	system("cls");
	firma();

	cout << "Infinity [1]\nBox [2]\n\n";
	cout << "Choose the mode to play : ";
	cin >> mode;

	while (mode != '1' && mode != '2')
	{
		system("cls");

		firma();

		cout << "ERROR !!!\n\n";
		cout << "Infinity [1]\nBox [2]\n\n";
		cout << "Choose the mode to play : ";
		cin >> mode;
	}
}

int continuare()
{
	int con;

	cout << "\n\nYOU LOST !!\n\n";
	cout << "YES [1]\n NO [2]\n\n";
	cout << "Do you wnat to continue : ";
	cin >> con;

	return con;
}

void boxmode()
{
	board();
	dir();
	move();
	box();
	ball();
	tail();
}

void infinity()
{
	board();
	dir();
	move();
	wall();
	ball();
	tail();
}