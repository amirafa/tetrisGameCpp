#include <stdio.h>
#include<iostream>
#include<time.h>
#include<Windows.h>
#include<conio.h>
using namespace std;
//_____________________________________________________________________________________
void gotoxy(short x, short y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//_____________________________________________________________________________________
class Display {
protected:
	int row, column, defalt;
	int **p;
	int score, bestScore;
public:
	Display() {}
	Display(int r, int c, int d) {
		row = r;
		column = c;
		defalt = d;
//______________________
		int nr=20, nc=20;
		cout << "Enter x , y :\n";
		cin >> nr >> nc; system("cls");
		row = nr; column = nc;
//_____________________
		int score = 0; int bestScore = 0;
		p = new int*[row];
		for (int i = 0; i < row; i++) p[i] = new int[column];
		for (int j = 0; j < row; j++)
			for (int k = 0; k < column; k++) {
				p[j][k] = d;
			}
	}
	int get(int a, int b) {
		return p[a][b];
	}
	void set(int a, int b, int in) {
		p[a][b] = in;
	}
	void Print() {
		//______________Kadr:
		char f = 205, g = 186, h = 201, l = 187, m = 188, n = 200;
		gotoxy(1, 2); cout << "AmirHosseinRafati";
		gotoxy(4, 4); cout << row << " * " << column;
		gotoxy(0, 5); cout << "___________________";
		gotoxy(2,6); cout << "A:Left <--";
		gotoxy(2, 8); cout << "D:Right -->";
		gotoxy(2, 10); cout << "S:Rotate @";
		gotoxy(0, 11); cout << "___________________";
		gotoxy(4, 12); cout << "Score: " << score;
		gotoxy(4, 14); cout << "Record: " << bestScore;
		gotoxy(20, 1); for (int k = 1; k < column + 1; k++) cout << f;//
		gotoxy(20, row + 2); for (int k = 1; k < column + 1; k++) cout << f;//
		int ct = 1; gotoxy(19, 2); for (int k = 1; k < row + 1; k++) { cout << g; gotoxy(19, 2 + ct); ct++; }
		ct = 1; gotoxy(column + 20, 2); for (int k = 1; k < row + 1; k++) { cout << g; gotoxy(column + 20, 2 + ct); ct++; }
		gotoxy(19, 1); cout << h; gotoxy(column + 20, 1); cout << l;//
		gotoxy(column + 20, row + 2); cout << m; gotoxy(19, row + 2); cout << n;//
																				//________________
		int cnt = 2;
		char a = ' ', b = 176;
		for (int i = 0; i < row; i++) {
			gotoxy(20, cnt);
			for (int j = 0; j < column; j++) {
				if (p[i][j] == 0)cout << a;     //0:empty 7:Block 8:Building 9:Ground
				if (p[i][j] == 7)cout << b;
				if (p[i][j] == 8)cout << b;
				if (p[i][j] == 9)cout << '-';
			}
			cout << endl;
			cnt++;
		}
	}
};
class game :public Display {
protected:
	int status, a;
	int Shape[2][4];
public:
	game(int r, int c, int d) :Display(r, c, d) { Start(); }
	void Clear() {
		int counter = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (p[i][j] == 7 || p[i][j] == 8) {
					p[i][j] = 0;
					counter++;
				}
			}
		}
		Start();
	}
	void Start() {
		srand(time(0));
		for (int k = 0; k < column; k++) { Display::set(row - 1, k, 9); }
		a = rand() % 3;
		int px = (column / 2);
		if (p[1][px+1] != 8) {
			if (a == 0) {
				Display::set(0, px+1, 7);
				Display::set(1, px+1, 7);
				Display::set(1, px+2, 7);
				Display::set(2, px+2, 7);
			}
			if (a == 1) {
				Display::set(0, px+1, 7);
				Display::set(1, px, 7);
				Display::set(1, px+1, 7);
				Display::set(1, px+2, 7);
			}
			if (a == 2) {
				Display::set(0, px+1, 7);
				Display::set(1, px + 1, 7);
				Display::set(2, px + 1, 7);
				Display::set(3, px + 1, 7);
			}
			int count = 0;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < column; j++) {
					if (p[i][j] == 7) {
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
			system("cls"); gotoxy(35, 8); cout << "  score : " << score; score = 0;
			gotoxy(35, 10); cout << "Press to Restart"; cin.get(); cin.get(); Clear(); system("cls");
		}
	}
	void Print() {
		Display::Print();
	}
};
class gamePlay :public game {
protected:
	int samt, rsflag, d;
public:
	gamePlay(int r, int c, int d) :game(r, c, d) {
		d = 1;
		samt = 0; rsflag = 1;
	}
	void Check() {
		int cnt = 0; int t = 0; int booli = 0;
		for (int i = row-1; i > 0; i--) {
			if (p[i][0] == 8) {
				for (int j = 0; j < column; j++) {
					if (p[i][j] != 8)break;
					else cnt++;
				}
				if (cnt == column) {
					for (int k = 0; k < column; k++) {
						p[i][k] = 0;
						t = i; booli = 1;
					}
				}
				else break;
			}
		}
		if (booli == 1) {
			for (int m = t; m > 0; m--) {
				for (int n = 0; n < column; n++) {
					if (p[m][n] == 8) {
						p[m + 1][n] = p[m][n];
						p[m][n] = 0;
					}
				}
			}
		}
	}
	int CheckCol() {
		int cnt = 0;
		for (int i = 0; i < 4; i++) {
			if (p[Shape[0][i]][Shape[1][i] - 1] == 8 || p[Shape[0][i]][Shape[1][i] + 1] == 8) break;
			else cnt++;
		}
		if (cnt == 4) return 1;
		else  return 0;
	}
	void Restart() {
		while (1) {
			status = 0;
			Start();
			rsflag = 1;
			while (rsflag == 1) {
				samt = 0;
				Print();
				if (_kbhit()) {
					char c = _getch();
					d = CheckCol();
					if (c == 'd' && d == 1)  samt = 1;  //77(->)
					if (c == 'a' && d == 1)  samt = -1; //75(<-)
					if (c == 's' && d == 1) status++;   //32(space)
			
													 //Status__________________________________
					if (status == 1 && samt == 0) {
						if (a == 0) {
							p[Shape[0][0]][Shape[1][0]] = 0;
							Shape[0][0] = Shape[0][0] + 1;
							Shape[1][0] = Shape[1][0] + 1;
							p[Shape[0][2]][Shape[1][2]] = 0;
							Shape[0][2] = Shape[0][2] + 1;
							Shape[1][2] = Shape[1][2] - 1;
							p[Shape[0][3]][Shape[1][3]] = 0;
							Shape[0][3] = Shape[0][3];
							Shape[1][3] = Shape[1][3] - 2;
						}
						if (a == 1) {
							p[Shape[0][1]][Shape[1][1]] = 0;
							Shape[0][1] = Shape[0][1] + 1;
							Shape[1][1] = Shape[1][1] + 1;
						}
						if (a == 2) {
							p[Shape[0][0]][Shape[1][0]] = 0;
							Shape[0][0] = Shape[0][0] + 1;
							Shape[1][0] = Shape[1][0] - 1;
							p[Shape[0][2]][Shape[1][2]] = 0;
							Shape[0][2] = Shape[0][2] - 1;
							Shape[1][2] = Shape[1][2] + 1;
							p[Shape[0][3]][Shape[1][3]] = 0;
							Shape[0][3] = Shape[0][3] - 2;
							Shape[1][3] = Shape[1][3] + 2;
						}

					}
					//__________________
					if (status == 2 && samt == 0) {
						if (a == 0) {
							p[Shape[0][0]][Shape[1][0]] = 0;
							Shape[0][0] = Shape[0][0] + 1;
							Shape[1][0] = Shape[1][0] - 1;
							p[Shape[0][2]][Shape[1][2]] = 0;
							Shape[0][2] = Shape[0][2] - 1;
							Shape[1][2] = Shape[1][2] - 1;
							p[Shape[0][3]][Shape[1][3]] = 0;
							Shape[0][3] = Shape[0][3] - 2;
							Shape[1][3] = Shape[1][3];
						}
						if (a == 1) {
							p[Shape[0][0]][Shape[1][0]] = 0;
							Shape[0][0] = Shape[0][0] + 1;
							Shape[1][0] = Shape[1][0] - 1;
						}
						if (a == 2) {
							p[Shape[0][0]][Shape[1][0]] = 0;
							Shape[0][0] = Shape[0][0] - 1;
							Shape[1][0] = Shape[1][0] + 1;
							p[Shape[0][2]][Shape[1][2]] = 0;
							Shape[0][2] = Shape[0][2] + 1;
							Shape[1][2] = Shape[1][2] - 1;
							p[Shape[0][3]][Shape[1][3]] = 0;
							Shape[0][3] = Shape[0][3] + 2;
							Shape[1][3] = Shape[1][3] - 2;
						}
					}
					//__________________
					if (status == 3 && samt == 0) {
						if (a == 0) {
							p[Shape[0][0]][Shape[1][0]] = 0;
							Shape[0][0] = Shape[0][0] - 1;
							Shape[1][0] = Shape[1][0] - 1;
							p[Shape[0][2]][Shape[1][2]] = 0;
							Shape[0][2] = Shape[0][2] - 1;
							Shape[1][2] = Shape[1][2] + 1;
							p[Shape[0][3]][Shape[1][3]] = 0;
							Shape[0][3] = Shape[0][3];
							Shape[1][3] = Shape[1][3] + 2;
						}
						if (a == 1) {
							p[Shape[0][3]][Shape[1][3]] = 0;
							Shape[0][3] = Shape[0][3] - 1;
							Shape[1][3] = Shape[1][3] - 1;
						}
						if (a == 2) {
							p[Shape[0][0]][Shape[1][0]] = 0;
							Shape[0][0] = Shape[0][0] + 1;
							Shape[1][0] = Shape[1][0] - 1;
							p[Shape[0][2]][Shape[1][2]] = 0;
							Shape[0][2] = Shape[0][2] - 1;
							Shape[1][2] = Shape[1][2] + 1;
							p[Shape[0][3]][Shape[1][3]] = 0;
							Shape[0][3] = Shape[0][3] - 2;
							Shape[1][3] = Shape[1][3] + 2;
						}
					}
					//__________________
					if (status == 4 && samt == 0) {    //1st status
						if (a == 0) {
							p[Shape[0][0]][Shape[1][0]] = 0;
							Shape[0][0] = Shape[0][0] - 1;
							Shape[1][0] = Shape[1][0] + 1;
							p[Shape[0][2]][Shape[1][2]] = 0;
							Shape[0][2] = Shape[0][2] + 1;
							Shape[1][2] = Shape[1][2] + 1;
							p[Shape[0][3]][Shape[1][3]] = 0;
							Shape[0][3] = Shape[0][3] + 2;
							Shape[1][3] = Shape[1][3];
							status = 0;
						}
						if (a == 1) {
							p[Shape[0][1]][Shape[1][1]] = 0;
							Shape[0][0] = Shape[0][0] - 1;
							Shape[1][0] = Shape[1][0] + 1;//
							Shape[0][1] = Shape[0][1] - 1;
							Shape[1][1] = Shape[1][1] - 1;//
							Shape[0][3] = Shape[0][3] + 1;
							Shape[1][3] = Shape[1][3] + 1;
							status = 0;
						}
						if (a == 2) {
							p[Shape[0][0]][Shape[1][0]] = 0;
							Shape[0][0] = Shape[0][0] - 1;
							Shape[1][0] = Shape[1][0] + 1;
							p[Shape[0][2]][Shape[1][2]] = 0;
							Shape[0][2] = Shape[0][2] + 1;
							Shape[1][2] = Shape[1][2] - 1;
							p[Shape[0][3]][Shape[1][3]] = 0;
							Shape[0][3] = Shape[0][3] + 2;
							Shape[1][3] = Shape[1][3] - 2;
							status = 0;
						}
					}
					//Samt__________________________________________
					for (int i = 0; i < 4; i++) {
						p[Shape[0][i]][Shape[1][i]] = 0;
						Shape[0][i] = Shape[0][i];
						Shape[1][i] = (Shape[1][i] + samt) % column;
					}
				}
				//Ground || Building Collision_______________
				for (int i = 0; i < 4; i++) {
					if (p[Shape[0][i] + 1][Shape[1][i]] == 9 || p[Shape[0][i] + 1][Shape[1][i]] == 8) {
						for (int j = 0; j < 4; j++) {
							p[Shape[0][j]][Shape[1][j]] = 8;
						}
						score++;
						rsflag = 0;
					}
				}
				//Movement______________
				if (rsflag != 0) {
					for (int i = 0; i < 4; i++) {
						p[Shape[0][i]][Shape[1][i]] = 0;
					}
					for (int i = 0; i < 4; i++) {
						Shape[0][i] = Shape[0][i] + 1;
						Shape[1][i] = Shape[1][i];
						p[Shape[0][i]][Shape[1][i]] = 7;
					}
					Check();
				}
				//______________
				d = 1;
				Sleep(100);
			}
		}
	}
};

int main() {
	gamePlay g1(20, 20, 0);
	g1.Start();
	g1.Restart();
	cin.get();
	cin.get();
}