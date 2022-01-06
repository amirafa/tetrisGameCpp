#include <stdio.h>
#include<iostream>
#include<time.h>
#include<Windows.h>
#include<conio.h>
using namespace std;
//____________________________________
void gotoxy(short x, short y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//GLobal____________________________________
int game[20][20] = { 0 };
int Shape[2][4] = { 0 };
int samt = 0;
int a, rsFlag = 1;
int gameFlag = 1;
int status = 0;
int score = 0; int bestScore = 0;
int d = 1;     //d for checking colision
//FnSign____________________________________
void Start();
void Restart();
void Print();
//Check_____________________________________
void Check() {
	int cnt = 0; int t = 0; int booli = 0;
	for (int i = 20; i > 0; i--) {
		if (game[i][0] == 8) {
			for (int j = 0; j < 20; j++) {
				if (game[i][j] != 8)break;
				else cnt++;
			}
			if (cnt == 20) {
				for (int k = 0; k < 20; k++) {
					game[i][k] = 0;
					t = i; booli = 1;
				}
			}
			else break;
		}
	}
	if (booli == 1) {
		for (int m = t; m > 0; m--) {
			for (int n = 0; n < 20; n++) {
				if (game[m][n] == 8) {
					game[m + 1][n] = game[m][n];
					game[m][n] = 0;
				}
			}
		}
	}
}
//CheckCol__________________________________
int CheckCol() {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		if (game[Shape[0][i]][Shape[1][i] - 1] == 8 || game[Shape[0][i]][Shape[1][i] + 1] == 8) break;
		else cnt++;
	}
	if (cnt == 4) return 1;
	else  return 0;
}
//__________________________________________
void Start() {
	status = 0;
	srand(time(0));
	for (int k = 0; k < 20; k++) { game[19][k] = 9; }
	a = rand() % 3;
	if (game[1][11] != 8) {
		if (a == 0) {
			game[0][11] = 7;
			game[1][11] = 7;
			game[1][12] = 7;
			game[2][12] = 7;
		}
		if (a == 1) {
			game[0][11] = 7;
			game[1][10] = 7;
			game[1][11] = 7;
			game[1][12] = 7;
		}
		if (a == 2) {
			game[0][11] = 7;
			game[1][11] = 7;
			game[2][11] = 7;
			game[3][11] = 7;
		}
		int count = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 20; j++) {
				if (game[i][j] == 7) {
					Shape[0][count] = i;
					Shape[1][count] = j;
					count++;
				}
			}
		}
	}
	//reaching the roof (Losing)
	else {
		if (score > bestScore)bestScore = score;
		system("cls"); gotoxy(35, 10);
		cout << " *** You Lose ***\n\n\t\t\t\t\tScore: " << score << "\n\n\t\t\t\t     Enter to RESET"; cin.get(); system("cls"); gameFlag = 0;
	}
}
//__________________________________
void Restart() {
	Check();
	while (rsFlag == 1 && gameFlag == 1) {
		samt = 0;
		Print();
		if (_kbhit()) {
			char c = _getch();
			d = CheckCol();
			if (c == 'd' && d == 1)  samt = 1;  //77(->)
			if (c == 'a' && d == 1)  samt = -1; //75(<-)
			if (c == 's' && d == 1) status += 1;//32(space)
		//	c = '0';
			//Status__________________________________
			if (status == 1 && samt == 0) {
				if (a == 0) {
					game[Shape[0][0]][Shape[1][0]] = 0;
					Shape[0][0] = Shape[0][0] + 1;
					Shape[1][0] = Shape[1][0] + 1;
					game[Shape[0][2]][Shape[1][2]] = 0;
					Shape[0][2] = Shape[0][2] + 1;
					Shape[1][2] = Shape[1][2] - 1;
					game[Shape[0][3]][Shape[1][3]] = 0;
					Shape[0][3] = Shape[0][3];
					Shape[1][3] = Shape[1][3] - 2;
				}
				if (a == 1) {
					game[Shape[0][1]][Shape[1][1]] = 0;
					Shape[0][1] = Shape[0][1] + 1;
					Shape[1][1] = Shape[1][1] + 1;
				}
				if (a == 2) {
					game[Shape[0][0]][Shape[1][0]] = 0;
					Shape[0][0] = Shape[0][0] + 1;
					Shape[1][0] = Shape[1][0] - 1;
					game[Shape[0][2]][Shape[1][2]] = 0;
					Shape[0][2] = Shape[0][2] - 1;
					Shape[1][2] = Shape[1][2] + 1;
					game[Shape[0][3]][Shape[1][3]] = 0;
					Shape[0][3] = Shape[0][3] - 2;
					Shape[1][3] = Shape[1][3] + 2;
				}

			}
			//__________________
			if (status == 2 && samt == 0) {
				if (a == 0) {
					game[Shape[0][0]][Shape[1][0]] = 0;
					Shape[0][0] = Shape[0][0] + 1;
					Shape[1][0] = Shape[1][0] - 1;
					game[Shape[0][2]][Shape[1][2]] = 0;
					Shape[0][2] = Shape[0][2] - 1;
					Shape[1][2] = Shape[1][2] - 1;
					game[Shape[0][3]][Shape[1][3]] = 0;
					Shape[0][3] = Shape[0][3] - 2;
					Shape[1][3] = Shape[1][3];
				}
				if (a == 1) {
					game[Shape[0][0]][Shape[1][0]] = 0;
					Shape[0][0] = Shape[0][0] + 1;
					Shape[1][0] = Shape[1][0] - 1;
				}
				if (a == 2) {
					game[Shape[0][0]][Shape[1][0]] = 0;
					Shape[0][0] = Shape[0][0] - 1;
					Shape[1][0] = Shape[1][0] + 1;
					game[Shape[0][2]][Shape[1][2]] = 0;
					Shape[0][2] = Shape[0][2] + 1;
					Shape[1][2] = Shape[1][2] - 1;
					game[Shape[0][3]][Shape[1][3]] = 0;
					Shape[0][3] = Shape[0][3] + 2;
					Shape[1][3] = Shape[1][3] - 2;
				}
			}
			//__________________
			if (status == 3 && samt == 0) {
				if (a == 0) {
					game[Shape[0][0]][Shape[1][0]] = 0;
					Shape[0][0] = Shape[0][0] - 1;
					Shape[1][0] = Shape[1][0] - 1;
					game[Shape[0][2]][Shape[1][2]] = 0;
					Shape[0][2] = Shape[0][2] - 1;
					Shape[1][2] = Shape[1][2] + 1;
					game[Shape[0][3]][Shape[1][3]] = 0;
					Shape[0][3] = Shape[0][3];
					Shape[1][3] = Shape[1][3] + 2;
				}
				if (a == 1) {
					game[Shape[0][3]][Shape[1][3]] = 0;
					Shape[0][3] = Shape[0][3] - 1;
					Shape[1][3] = Shape[1][3] - 1;
				}
				if (a == 2) {
					game[Shape[0][0]][Shape[1][0]] = 0;
					Shape[0][0] = Shape[0][0] + 1;
					Shape[1][0] = Shape[1][0] - 1;
					game[Shape[0][2]][Shape[1][2]] = 0;
					Shape[0][2] = Shape[0][2] - 1;
					Shape[1][2] = Shape[1][2] + 1;
					game[Shape[0][3]][Shape[1][3]] = 0;
					Shape[0][3] = Shape[0][3] - 2;
					Shape[1][3] = Shape[1][3] + 2;
				}
			}
			//__________________
			if (status == 4 && samt == 0) {    //1st status
				if (a == 0) {
					game[Shape[0][0]][Shape[1][0]] = 0;
					Shape[0][0] = Shape[0][0] - 1;
					Shape[1][0] = Shape[1][0] + 1;
					game[Shape[0][2]][Shape[1][2]] = 0;
					Shape[0][2] = Shape[0][2] + 1;
					Shape[1][2] = Shape[1][2] + 1;
					game[Shape[0][3]][Shape[1][3]] = 0;
					Shape[0][3] = Shape[0][3] + 2;
					Shape[1][3] = Shape[1][3];
					status = 0;
				}
				if (a == 1) {
					game[Shape[0][1]][Shape[1][1]] = 0;
					Shape[0][0] = Shape[0][0] - 1;
					Shape[1][0] = Shape[1][0] + 1;//
					Shape[0][1] = Shape[0][1] - 1;
					Shape[1][1] = Shape[1][1] - 1;//
					Shape[0][3] = Shape[0][3] + 1;
					Shape[1][3] = Shape[1][3] + 1;
					status = 0;
				}
				if (a == 2) {
					game[Shape[0][0]][Shape[1][0]] = 0;
					Shape[0][0] = Shape[0][0] - 1;
					Shape[1][0] = Shape[1][0] + 1;
					game[Shape[0][2]][Shape[1][2]] = 0;
					Shape[0][2] = Shape[0][2] + 1;
					Shape[1][2] = Shape[1][2] - 1;
					game[Shape[0][3]][Shape[1][3]] = 0;
					Shape[0][3] = Shape[0][3] + 2;
					Shape[1][3] = Shape[1][3] - 2;
					status = 0;
				}
			}
			//Samt__________________________________________
			for (int i = 0; i < 4; i++) {
				game[Shape[0][i]][Shape[1][i]] = 0;
				Shape[0][i] = Shape[0][i];
				Shape[1][i] = (Shape[1][i] + samt) % 20;
			}
		}
		//Ground || Building Collision_______________
		for (int i = 0; i < 4; i++) {
			if (game[Shape[0][i] + 1][Shape[1][i]] == 9 || game[Shape[0][i] + 1][Shape[1][i]] == 8) {
				for (int j = 0; j < 4; j++) {
					game[Shape[0][j]][Shape[1][j]] = 8;
				}
				score++;
				rsFlag = 0;
			}
		}
		//Movement______________
		if (rsFlag != 0) {
			Check();
			for (int i = 0; i < 4; i++) {
				game[Shape[0][i]][Shape[1][i]] = 0;
			}
			for (int i = 0; i < 4; i++) {
				Shape[0][i] = Shape[0][i] + 1;
				Shape[1][i] = Shape[1][i];
				game[Shape[0][i]][Shape[1][i]] = 7;
			}
		}
		//______________
		d = 1;
		Sleep(100);
	}
}//_____________________________________
void Print() {
	//______________Kadr:
	gotoxy(50, 15); cout << "A:Left <--";
	gotoxy(50, 16); cout << "D:Right -->";
	gotoxy(50, 17); cout << "S:Rotate @";
	gotoxy(7, 15); cout << "Score: " << score;
	gotoxy(7, 16); cout << "Record: " << bestScore;
	char f = 205, g = 186, h = 201, l = 187, m = 188, n = 200;
	gotoxy(20, 1); for (int k = 1; k < 21; k++) cout << f;
	gotoxy(20, 22); for (int k = 1; k < 21; k++) cout << f;
	int ct = 1; gotoxy(19, 2); for (int k = 1; k < 21; k++) { cout << g; gotoxy(19, 2 + ct); ct++; }
	ct = 1; gotoxy(40, 2); for (int k = 1; k < 21; k++) { cout << g; gotoxy(40, 2 + ct); ct++; }
	gotoxy(19, 1); cout << h; gotoxy(40, 1); cout << l;
	gotoxy(40, 22); cout << m; gotoxy(19, 22); cout << n;
	gotoxy(19, 23); cout << "CREATED BY: A.H.RAFATI";
	//________________
	int cnt = 2;
	char a = ' ', b = 176;
	for (int i = 0; i < 20; i++) {
		gotoxy(20, cnt);
		for (int j = 0; j < 20; j++) {
			if (game[i][j] == 0)cout << a;     //0:empty 7:Block 8:Building 9:Ground
			if (game[i][j] == 7)cout << b;
			if (game[i][j] == 8)cout << b;
			if (game[i][j] == 9)cout << '-';
		}
		cout << endl;
		cnt++;
	}
}//____________________________________
int main() {
	while (1) {
		score = 0;
		int counter = 0;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (game[i][j] == 7 || game[i][j] == 8) {
					game[i][j] = 0;
					counter++;
				}
			}
			gameFlag = 1;
		}
		while (gameFlag == 1) {
			rsFlag = 1;
			Start();
			Restart();
		}
	}
	cin.get();
}