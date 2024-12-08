#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
#define ROWS 60 
#define COLS 60
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
		ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState ==

			FROM_LEFT_1ST_BUTTON_PRESSED)

		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void color(int textColor, int backgroundColor = 0) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD color = (backgroundColor << 4) | (textColor & 0x0F);
	SetConsoleTextAttribute(hConsole, color);
}
void grid() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (i == 0 or j == 0 or i == ROWS - 1 or j == COLS - 1) {
				gotoRowCol(i, j);
				cout << "x";
			}
		}
	}
}
struct Position
{
	int x, y;
};
enum DIRECTION {
		UP, DOWN, RIGHT, LEFT

};
struct Snake {
	Position Sp[1000];
	DIRECTION dir;
	char symbol ;
	int lenght ;
	bool isAlive;
};
struct Food {
	Position fp;
};
void init(Snake& S,Snake& S1, Snake& S2) {
	S.Sp[0] = { ROWS / 2 , COLS / 2 };
	S.dir = RIGHT;
	S.symbol = -37;
	S.lenght = 5;
	S.isAlive = true;

	S1.Sp[0] = { ROWS / 4 , COLS / 2 };
	S1.dir = RIGHT;
	S1.symbol = -37;
	S1.lenght = 5;
	S1.isAlive = true; 

	S2.Sp[0] = { 3*ROWS / 4 , COLS / 2 };
	S2.dir = RIGHT;
	S2.symbol = -37;
	S2.lenght = 5;
	S2.isAlive = true;
}
void show_snake(Snake& S, Snake& S1, Snake& S2, char sym = -37) {
	if (S.isAlive) {
		color(6);
		for (int i = 0; i < S.lenght; i++) {
			gotoRowCol(S.Sp[i].x, S.Sp[i].y);
			cout << sym;
		}
	}

	if (S1.isAlive) {
		color(7);
		for (int i = 0; i < S1.lenght; i++) {
			gotoRowCol(S1.Sp[i].x, S1.Sp[i].y);
			cout << sym;
		}
	}

	if (S2.isAlive) {
		color(9);
		for (int i = 0; i < S2.lenght; i++) {
			gotoRowCol(S2.Sp[i].x, S2.Sp[i].y);
			cout << sym;
		}
	}
}
void random_food(Food& F , Snake S) {
	color(4);
	bool haha = true;
	while (haha) {
		F.fp.x = rand() % (ROWS - 2) + 1;
		F.fp.y = rand() % (COLS - 2) + 1;


		haha = false;

		for (int i = 0; i < S.lenght; i++) {
			if (F.fp.x == S.Sp[i].x and F.fp.y == S.Sp[i].y)
				haha = true;
			break;
		}

	}
	gotoRowCol(F.fp.x, F.fp.y);
	cout << "*";
}
void movement(Snake* S, Snake* S1, Snake* S2) {
	Snake *asli=nullptr;
	if (_kbhit()) {
		int ch = _getch();
		switch (ch)
		{
			case 72: {
				if ((*S).dir != DOWN)
					(*S).dir = UP;
				asli = S;
				break;
			}
			case 75: {
				if ((*S).dir != RIGHT)
					(*S).dir = LEFT;
				asli = S;
				break;
			}
			case 77: {
				if ( (*S).dir != LEFT) 
					(*S).dir = RIGHT;
				asli = S;
				break;
			}
			case 80: {
				if ((*S).dir != UP)
					(*S).dir = DOWN;
				asli = S;
				break;

			}
			case 'w': {
				if ((*S1).dir != DOWN)
					(*S1).dir = UP;
				asli = S1;
				break;
			}
			case 'a': {
				if ((*S1).dir != RIGHT)
					(*S1).dir = LEFT;
				asli = S1;
				break;
			}
			case 's': {
				if ((*S1).dir != UP)
					(*S1).dir = DOWN;
				asli = S1;
				break;
			}
			case 'd': {
				if ((*S1).dir != LEFT)
					(*S1).dir = RIGHT;
				asli = S1;
				break;
			}
			case 'i': {
				if ((*S2).dir != DOWN)
					(*S2).dir = UP;
				asli = S2;
				break;
			}
			case 'j': {
				if ((*S2).dir != RIGHT)
					(*S2).dir = LEFT;
				asli = S2;
				break;
			}
			case 'k': {
				if ((*S2).dir != UP)
					(*S2).dir = DOWN;
				asli = S2;
				break;
			}
			case 'l': {
				if ((*S2).dir != LEFT)
					(*S2).dir = RIGHT;
				asli = S2;
				break;
			}
			default: {
				break;
			}
		}

	}
	if (asli == S or asli == S1 or asli == S2)
	{
		if ((*asli).isAlive) {
			for (int i = (*asli).lenght - 1; i > 0; i--) {
				(*asli).Sp[i] = (*asli).Sp[i - 1];
			}
			Position newp = (*asli).Sp[0];
			if ((*asli).dir == UP) newp.x--;
			if ((*asli).dir == DOWN) newp.x++;
			if ((*asli).dir == RIGHT) newp.y++;
			if ((*asli).dir == LEFT) newp.y--;

			if (newp.x < 1) newp.x = ROWS - 2;
			if (newp.x >= ROWS - 1) newp.x = 1;
			if (newp.y < 1) newp.y = COLS - 2;
			if (newp.y >= COLS - 1) newp.y = 1;

			(*asli).Sp[0] = newp;
		}
	}
	else
	{
		asli = S;
		if ((*asli).isAlive) {
			for (int i = (*asli).lenght - 1; i > 0; i--) {
				(*asli).Sp[i] = (*asli).Sp[i - 1];
			}
			Position newp = (*asli).Sp[0];
			if ((*asli).dir == UP) newp.x--;
			if ((*asli).dir == DOWN) newp.x++;
			if ((*asli).dir == RIGHT) newp.y++;
			if ((*asli).dir == LEFT) newp.y--;

			if (newp.x < 1) newp.x = ROWS - 2;
			if (newp.x >= ROWS - 1) newp.x = 1;
			if (newp.y < 1) newp.y = COLS - 2;
			if (newp.y >= COLS - 1) newp.y = 1;

			(*asli).Sp[0] = newp;
		}
		asli = S1;
		if ((*asli).isAlive) {
			for (int i = (*asli).lenght - 1; i > 0; i--) {
				(*asli).Sp[i] = (*asli).Sp[i - 1];
			}
			Position newp = (*asli).Sp[0];
			if ((*asli).dir == UP) newp.x--;
			if ((*asli).dir == DOWN) newp.x++;
			if ((*asli).dir == RIGHT) newp.y++;
			if ((*asli).dir == LEFT) newp.y--;

			if (newp.x < 1) newp.x = ROWS - 2;
			if (newp.x >= ROWS - 1) newp.x = 1;
			if (newp.y < 1) newp.y = COLS - 2;
			if (newp.y >= COLS - 1) newp.y = 1;

			(*asli).Sp[0] = newp;
		}
		asli = S2;
		if ((*asli).isAlive) {
			for (int i = (*asli).lenght - 1; i > 0; i--) {
				(*asli).Sp[i] = (*asli).Sp[i - 1];
			}
			Position newp = (*asli).Sp[0];
			if ((*asli).dir == UP) newp.x--;
			if ((*asli).dir == DOWN) newp.x++;
			if ((*asli).dir == RIGHT) newp.y++;
			if ((*asli).dir == LEFT) newp.y--;

			if (newp.x < 1) newp.x = ROWS - 2;
			if (newp.x >= ROWS - 1) newp.x = 1;
			if (newp.y < 1) newp.y = COLS - 2;
			if (newp.y >= COLS - 1) newp.y = 1;

			(*asli).Sp[0] = newp;
		}
	}
}

bool isKill(Snake S) {

	for (int i = 1; i < S.lenght; i++) {
		if (S.Sp[0].x == S.Sp[i].x and S.Sp[0].y == S.Sp[i].y)
			return true;
	}
	return false;
}
void remove_dead_snake(Snake& S) {
	S.isAlive = false; 
}
bool check_food_collision(Snake& S, Food& F) {
	if (S.Sp[0].x == F.fp.x && S.Sp[0].y == F.fp.y) 
		return true; 
	return false;
}
int main() {
	srand(time(0));
	int n = 0;
	while (n == 0) {

		Snake S;
		Snake S1;
		Snake S2;

		init(S,S1,S2);
		Food F;
		grid();
		random_food(F,S);
	

	do {
		show_snake(S ,S1,S2,' ');

		movement(&S,&S1,&S2);
		show_snake(S,S1,S2);
		if (check_food_collision(S, F)) {
			S.lenght++;		
			random_food(F, S);		
		}
		if (check_food_collision(S1, F)) {
			S1.lenght++;
			random_food(F, S1);
		}
		if (check_food_collision(S2, F)) {
			S2.lenght++;
			random_food(F, S2);
		}
		if (isKill(S)) 
			remove_dead_snake(S);
		if (isKill(S1))
			remove_dead_snake(S1);
		if (isKill(S2))
			remove_dead_snake(S2);

		int aliveCount = 0;
		if (S.isAlive) aliveCount++;
		if (S1.isAlive) aliveCount++;
		if (S2.isAlive) aliveCount++;
		if (aliveCount == 1) 
			break;
		Sleep(50);
	} while (true);

	system("cls");
	if (S.isAlive) cout << "Player 1 wins!" << endl;
	if (S1.isAlive) cout << "Player 2 wins!" << endl;
	if (S2.isAlive) cout << "Player 3 wins!" << endl;

	_getch();
	cin >> n;
	}
	return 0;
}