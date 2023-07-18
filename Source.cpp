#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<math.h>
#include<ctime>
#include<string>
enum colour { white, black };
using namespace std;
#define row 75
#define col 150
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
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
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
struct position {
	int ri, ci;

};
void init(char**& b, int& dim, string pname[], int& turn) {
	ifstream in("BSCS22101-load.txt");
	in >> dim;
	b = new char* [dim];
	for (int r = 0; r < dim; r++) {
		b[r] = new char[dim];
	}
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
			in >> b[r][c];

		}

	}
	for (int i = 0; i < 2; i++) {
		cout << "Enter player name : ";
		cin >> pname[i];
	}
	
	turn = white;
}
void init1(char**& b, int& dim, string pname[], int& turn) {
	ifstream in("BSCS22101-save.txt");
	in >> dim;
	b = new char* [dim];
	for (int r = 0; r < dim; r++) {
		b[r] = new char[dim];
	}
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
			in >> b[r][c];

		}

	}
	for (int i = 0; i < 2; i++) {
		cout << "Enter player name : ";
		cin >> pname[i];
	}

	turn = white;
}
void printBoard(char** b, int dim) {
	system("cls");
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++)
		{
			cout << b[r][c] << " ";
		}
		cout << endl;
	}
}
void turnMsg(string pname) {
	cout << endl<<endl<<endl <<endl<< pname << "'s turn : " << endl;
}

bool isblackpiece(char sym) {
	return sym >= 'a' && sym <= 'z';
}
bool iswhitepiece(char sym) {
	return sym >= 'A' && sym <= 'Z';
}
bool ismypiece(char sym, int turn) {
	if (turn == black) {
		return isblackpiece(sym);
	}
	else {
		return iswhitepiece(sym);
	}
}

bool isvalidsi(char** b, int dim,position si, int turn) {
	if (si.ri < 0 || si.ri >= dim || si.ci < 0 || si.ci >= dim) {
		return false;
	}
	return ismypiece(b[si.ri][si.ci],turn);
}
bool isvaliddc(char** b, int dim, position dc, int turn) {
	if (dc.ri < 0 || dc.ri >= dim || dc.ci < 0 || dc.ci >= dim) {
		return false;
	}
	return !ismypiece(b[dc.ri][dc.ci], turn);
}
void selectPosition(position& p, int dim) {
	int x, y;
	//cout << "Enter coordinates: (A1:I9): " << endl;
	/*char c;
	int d;
	cin >> c>>d; 
	c = toupper(c);*/
	getRowColbyLeftClick(x, y);
	/*p.ri = d - 1;
	p.ci = c - 'A';*/
	//return p.ri, p.ci;
	p.ri = x / dim;
	p.ci = y / dim;
}
void updateboard(char**& b,position& sc, position& dc) {
	char p = b[sc.ri][sc.ci];
	b[dc.ri][dc.ci] = p;
	b[sc.ri][sc.ci] = '-';
}
/*void copyUpdateboard(char**& b, position& sc, position& dc) {
	updateboard(b, sc, dc);
}*/
void turnchange(int& turn) {
	turn = (turn + 1) % 2;
	//return turn;
}

void drawpawn(int r, int c)
{
	gotoRowCol(r - 2, c);
	cout << char(-37);
	gotoRowCol(r - 1, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawking(int r, int c)
{
	gotoRowCol(r - 3, c - 3);
	cout << char(-37) << "  " << char(-37) << "  " << char(-37);
	gotoRowCol(r - 2, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r - 1, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 3, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawlance(int r, int c)
{
	gotoRowCol(r - 2, c);
	cout << char(-37);
	gotoRowCol(r - 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r - 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawknight(int r, int c)
{
	gotoRowCol(r - 2, c - 1);
	cout << char(-37) << char(-37);
	gotoRowCol(r - 1, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << " " << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 2);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 1);
	cout << char(-37) << char(-37);
	gotoRowCol(r + 3, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);

}
void drawsg(int r, int c)
{
	gotoRowCol(r - 2, c);
	cout << char(-37);
	gotoRowCol(r - 1, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 3, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawgg(int r, int c)
{
	gotoRowCol(r - 2, c - 2);
	cout << char(-37) << "   " << char(-37);
	gotoRowCol(r - 1, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 3, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawbishop(int r, int c)
{
	gotoRowCol(r - 2, c);
	cout << char(-37);
	gotoRowCol(r - 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c);
	cout << char(-37);
	gotoRowCol(r + 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 3, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawrook(int r, int c)
{
	gotoRowCol(r - 2, c);
	cout << char(-37);
	gotoRowCol(r - 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37) ;
	gotoRowCol(r + 1, c );
	cout << char(-37) ;
	gotoRowCol(r + 2, c-2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	
	//gotoRowCol(r + 3, c);
	//cout << char(-37);
}
void drawbox(int sr, int sc, int brow, int bcol,int color,int sec_color,char sym) {
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			if (r == ceil((brow - 1) / 2) && c == ceil((bcol - 1) / 2))
			{
				SetClr(sec_color);
				gotoRowCol(sr + r, sc + c);
				switch (sym) {
				
				case 'p':
				case 'w':
					drawpawn(sr+r,sc+c);
					break;	
				case 'P':
				case 'W':
					SetClr(5);
					drawpawn(sr+r, sc+c);
					break;
				case 'L':
				case 'T':
					SetClr(5);
					drawlance(sr+r, sc+c);
					break;
				case 'l':
				case 't':
					drawlance(sr+r, sc+c);
					break;
				case 'n':
				case 'y':
					drawknight(sr+r, sc+c);
					break;
				case 'N':
				case 'Y':
					SetClr(5);
					drawknight(sr+r, sc+c);
					break;
				case 's':
				case 'u':
					drawsg(sr+r, sc+c);
					break;
				case 'S':
				case 'U':
					SetClr(5);
					drawsg(sr+r, sc+c);
					break;
				case 'k':
				case 'o':
					drawking(sr+r, sc+c);
					break;
				case 'K':
				case 'O':
					SetClr(5);
					drawking(sr+r, sc+c);
					break;
				case 'g':
				case 'i':
					drawgg(sr+r,sc+ c);
					break;
				case 'G':
				case 'I':
					SetClr(5);
					drawgg(sr+r, sc+c);
					break;
				case 'B':
				case 'Q':
					SetClr(5);
					drawbishop(sr+r, sc+c);
					break;
				case 'b':
				case 'q':
					drawbishop(sr+r, sc+c);
					break;
				case 'R':
				case 'E':
					SetClr(5);
					drawrook(sr+r, sc+c);
					break;
				case 'r':
				case 'e':
					drawrook(sr+r,sc+ c);
					break;
				case '-':
					gotoRowCol(sr + r, sc + c);
					cout << " ";
					break;
				}

				
				/*
				else {
					SetClr(sec_color);
					gotoRowCol(sr + r, sc + c);
					cout << sym;
				}*/
			}
			else {
				if (r == 0 || c == 0 || r == brow - 1 || c == bcol - 1) {

					SetClr(color);
					gotoRowCol(sr + r, sc + c);
					cout << char(-37);
				}
			}
		}

	}
}
/*
void drawbox1(int sr, int sc, int brow, int bcol, int color, int sec_color,char sym,int& i,int& j) {
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			if (r == ceil((brow -1) / 2) && c == ceil((bcol-1 ) / 2))
			{
				
			}
			else {
				if (r == 0 || c == 0 || r == brow-1  || c == bcol-1 ) {

					SetClr(color);
					gotoRowCol(sr + r, sc + c);
					cout << char(-37);
				}
			}
		}
	}
	for (int r = 0; r <brow ; r++) {
		for (int c = 0; c <bcol; c++) {
			if (r == ceil((brow - 1) / 2) && c == ceil((bcol - 1) / 2))
			{
				SetClr(sec_color);
				gotoRowCol(sr + r, sc + c);
				//cout << sym;
				switch (sym) {
				case 'p':
					drawpawn(sr + r, sc + c);
					//cout << 'p';
					break;
				case 'P':
					SetClr(5);
					drawpawn(sr + r, sc + c);
					//cout << 'p';

					break;
				case 'L':
					SetClr(5);
					drawlance(sr + r, sc + c);
					break;
				case 'l':
					drawlance(sr + r, sc + c);
					break;
				case 'n':
					drawknight(sr + r, sc + c);
					break;
				case 'N':
					SetClr(5);
					drawknight(sr + r, sc + c);
					break;
				case 's':
					drawsg(sr + r, sc + c);
					break;
				case 'S':
					SetClr(5);
					drawsg(sr + r, sc + c);
					break;
				case 'k':
					drawking(sr + r, sc + c);
					break;
				case 'K':
					SetClr(5);
					drawking(sr + r, sc + c);
					break;
				case 'g':
					drawgg(sr + r, sc + c);
					break;
				case 'G':
					SetClr(5);
					drawgg(sr + r, sc + c);
					break;
				case 'B':
					SetClr(5);
					drawbishop(sr + r, sc + c);
					break;
				case 'b':
					drawbishop(sr + r, sc + c);
					break;
				case 'R':
					SetClr(5);
					drawrook(sr + r, sc + c);
					break;
				case 'r':
					drawrook(sr + r, sc + c);
					break;
				}
			}
			else {
				continue;
			}
		}
	}
}*/
void drawbox1(int sr, int sc, int brow, int bcol, int color) {
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			if (r == ceil((brow - 1) / 2) && c == ceil((bcol - 1) / 2))
			{
				continue;
			}
			else {
				if (r == 0 || c == 0 || r == brow - 1 || c == bcol - 1) {

					SetClr(color);
					gotoRowCol(sr + r, sc + c);
					cout << char(-37);
				}
			}
		}
	}
	
}
void drawbox2(int sr, int sc, int brow, int bcol, int color, int sec_color, char sym, int& i, int& j) {
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			if (r == ceil((brow - 1) / 2) && c == ceil((bcol - 1) / 2))
			{
				SetClr(sec_color);
				gotoRowCol(sr + r, sc + c);
				//cout << sym;
				switch (sym) {
				
				case 'p':
					drawpawn(sr + r, sc + c);
				//	cout << 'p';
					break;
				case 'P':
					drawpawn(sr + r, sc + c);
				//	cout << 'p';
					break;
				case 'L':
					drawlance(sr + r, sc + c);
					break;
				case 'l':
					drawlance(sr + r, sc + c);
					break;
				case 'n':
					drawknight(sr + r, sc + c);
					break;
				case 'N':
					drawknight(sr + r, sc + c);
					break;
				case 's':
					drawsg(sr + r, sc + c);
					break;
				case 'S':
					drawsg(sr + r, sc + c);
					break;
				case 'k':
					drawking(sr + r, sc + c);
					break;
				case 'K':
					drawking(sr + r, sc + c);
					break;
				case 'g':
					drawgg(sr + r, sc + c);
					break;
				case 'G':
					drawgg(sr + r, sc + c);
					break;
				case 'B':
					drawbishop(sr + r, sc + c);
					break;
				case 'b':
					drawbishop(sr + r, sc + c);
					break;
				case 'R':
					drawrook(sr + r, sc + c);
					break;
				case 'r':
					drawrook(sr + r, sc + c);
					break;
				}
			}
			else {
				continue;
			}
		}
	}
}

void printbox1(int dim, int brow, int bcol, char** b, string pname, string pname1, char**& a, char**& d, int& i, int& j) {
	for (int r = brow - 2; r < brow; r++) {
		for (int c = bcol + 3; c < bcol + 9; c++) {

			drawbox1(r * brow, c * bcol, brow, bcol, 7);

		}
	}
	int l = 0;
	for (int r = brow - 2; r < brow; r++) {
		for (int c = bcol + 3; c < bcol + i + 4; c++,l++) {
			if ((r % 2) == 0) {
			}
			else {
				if (l <= i) {
					drawbox2(r * brow, c * bcol, brow, bcol, 7, 9, a[0][l], i, j);
				}
			}
		}
	}
     for (int r = brow - 2; r < brow; r++) {
		 int m = 0;
		for (int c = bcol + 3; c < bcol + j + 4; c++,m++) {
			if ((r % 2) == 0) {
				if (m <= j) {
					drawbox2(r * brow, c * bcol, brow, bcol, 7, 5, d[0][m], i, j);
				}
			}
			else {
			}
		}
	}

}

void printbox(int dim, int brow, int bcol,char** b, string pname,string pname1,char**& a,char**& d,int& i,int& j){
	system("cls");
	bool flag = true;
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			//if ((r + c) % 2 == 0) {
			drawbox(r * brow, c * bcol, brow, bcol, 7, 9, b[r][c]);
			if (r == 7 && c == bcol - 1) {
				cout << "   " << pname << " captured pieces: " << endl;
			}
			if (r == 8 && c == bcol - 1) {
				cout << "   " << pname1 << " captured pieces: " << endl;
			}
			
		}
	}
}
void printbox(int dim, int brow, int bcol, char** b, string pname, string pname1) {
	system("cls");
	bool flag = true;
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			//if ((r + c) % 2 == 0) {
			drawbox(r * brow, c * bcol, brow, bcol, 7, 9, b[r][c]);
			if (r == 8 && c == bcol - 1) {
				cout << "   " << pname1 << " captured pieces: " << endl;
			}
			if (r == 7 && c == bcol - 1) {
				cout << "   " << pname << " captured pieces: " << endl;
			}
			//}
			//else {
			//	drawbox(r * brow, c * bcol, brow, bcol, 5,7,b[r][c]);
			//}
		}
	}
	
}

bool ishorizMove(position sc,position dc) {
	return sc.ri == dc.ri;
}
bool isvertMove(position sc, position dc) {
	return sc.ci == dc.ci;
}
bool isdiagMove(position sc, position dc) {
	int r = abs(sc.ri - dc.ri);
	int c = abs(sc.ci - dc.ci);
	return r == c;
}
bool ishorizPathClear1(char** b,position sc, position dc) {
	if (sc.ci < dc.ci) {
		for (int c = sc.ci + 1; c < dc.ci; c++) {
			if (b[sc.ri][c] != '-') {
				return false;
			}
		}
		return true;
	}
	else {
		for (int c = dc.ci + 1; c < sc.ci; c++) {
			if (b[sc.ri][c] != '-') {
				return false;
			}
		}
		return true;
	}
	
}
bool ishorizPathClear2(char** b, position sc, position dc) {
	int cs, ce;
	if (sc.ci < dc.ci) {
		cs = sc.ci + 1;
		ce = dc.ci - 1;
	}
	else {
		cs = dc.ci + 1;
		ce = sc.ci - 1;
	}
	for (int c = cs; c <= ce; c++) {
		if (b[sc.ri][c] != '-') {
			return false;
		}
	}
	return true;
}
bool isvertPathClear1(char** b, position sc, position dc) {
	if (sc.ri < dc.ri) {
		for (int r = sc.ri + 1; r < dc.ri; r++) {
			if (b[r][sc.ci] != '-') {
				return false;
			}
		}
		return true;
	}
	else {
		for (int r = dc.ri + 1; r < sc.ri; r++) {
			if (b[r][sc.ci] != '-') {
				return false;
			}
		}
		return true;
	}

}
bool isvertPathClear2(char** b, position sc, position dc) {
	int rs, re;
	if (sc.ri < dc.ri) {
		rs = sc.ri + 1;
		re = dc.ri - 1;
	}
	else {
		rs = dc.ri + 1;
		re = sc.ri - 1;
	}
	for (int r = rs; r <= re; r++) {
		if (b[r][sc.ci] != '-') {
			return false;
		}
	}
	return true;
}
bool isdiagL2RpathClear1(char** b, position sc, position dc) {
	int d;
	if (sc.ri < dc.ri) {
	     d = dc.ri - sc.ri - 1;
		for (int i = 1; i <= d; i++) {
			if (b[sc.ri+i][sc.ci+i] != '-') {
				return false;
			}
		}
		return true;
	}
	else {
		 d = (sc.ri - dc.ri - 1);
		for (int i = 1; i <= d; i++) {
			if (b[sc.ri - i][sc.ci - i] != '-') {
				return false;
			}
		}
		return true;
	}

}
bool isdiagL2RpathClear2(char** b, position sc, position dc) {
	int d = abs(dc.ri - sc.ri) - 1;

	for (int i = 1; i <= d; i++) {
		if (sc.ri < dc.ri) {
			if (b[sc.ri + i][sc.ci + i] != '-') {
				return false;
			}
		}
		else {
			if (b[sc.ri - i][sc.ci - i] != '-') {
				return false;
			}
		}
	}
	return true;
}
bool isdiagR2LpathClear1(char** b, position sc, position dc) {
	int d;
	if (sc.ri < dc.ri) {
	    d = dc.ri - sc.ri - 1;
		for (int i = 1; i <= d; i++) {
			if (b[sc.ri + i][sc.ci - i] != '-') {
				return false;
			}
		}
		return true;
	}
	else {
	    d = (sc.ri - dc.ri - 1);
		for (int i = 1; i <= d; i++) {
			if (b[sc.ri - i][sc.ci + i] != '-') {
				return false;
			}
		}
		return true;
	}
}
bool isdiagR2LpathClear2(char** b, position sc, position dc) {
	int d = abs(dc.ri - sc.ri) - 1;
	for (int i = 1; i <= d; i++) {
		if (sc.ri < dc.ri) {
			if (b[sc.ri + i][sc.ci - i] != '-') {
				return false;
			}
		}

		else {
			if (b[sc.ri - i][sc.ci + i] != '-') {
				return false;
			}
		}
	}
	return true;

}

bool legalityRook(char** b, position sc, position dc) {
	return ((ishorizMove(sc, dc) && ishorizPathClear2(b, sc, dc)) ||
		(isvertMove(sc, dc) && isvertPathClear2(b, sc, dc)));
}
bool legalitybishop(char** b, position sc, position dc) {
	return (isdiagMove(sc, dc) && (isdiagL2RpathClear1(b, sc, dc) ||
		isdiagR2LpathClear1(b, sc, dc)));
}
bool legalityLance(char** b, position sc, position dc,int turn) {
	if (turn == white) {
		return ((sc.ci == dc.ci) && (sc.ri > dc.ri) && legalityRook(b, sc, dc));
	}
	else {
		return ((sc.ci == dc.ci) && (sc.ri < dc.ri) && legalityRook(b, sc, dc));
	}
}
bool pawnslegality(char** b, position sc, position dc, int turn) {
	int r = abs(sc.ri - dc.ri);
	if (turn == white) {
		return (sc.ci == dc.ci) && r <= 1 &&
			(sc.ri > dc.ri) && (legalityRook(b, sc, dc));
	}
	else {
		return (sc.ci == dc.ci) && r <= 1 &&
			(sc.ri < dc.ri) && (legalityRook(b, sc, dc));
	}
}
bool legalitySilGeneral(char** b, position sc, position dc,int turn) {
	int r = abs(sc.ri - dc.ri);
	int c = abs(sc.ci - dc.ci);
	return (r <= 1 && c <=1 && (pawnslegality(b,sc,dc,turn) || legalitybishop(b,sc,dc)));
}
bool legalitygoldGeneral(char** b, position sc, position dc,int turn) {
	int r = abs(sc.ri - dc.ri);
	int c = abs(sc.ci - dc.ci);
	if (turn == white) {
		return (r <= 1 && c <= 1 && (legalityRook(b, sc, dc) || (sc.ri > dc.ri) && 
			legalitybishop(b, sc, dc)));
	}
	else {
		return (r <= 1 && c <= 1 && (legalityRook(b, sc, dc) || (sc.ri < dc.ri) &&
			legalitybishop(b, sc, dc)));
	}
}
bool legalityking(char** b, position sc, position dc) {
	int r = abs(sc.ri - dc.ri);
	int c = abs(sc.ci - dc.ci);
	return (legalityRook(b,sc, dc) || legalitybishop(b, sc, dc)) && r <= 1 && c <= 1;
}
bool legalityknight(char** b, position sc, position dc,int turn) {
	int r = abs(sc.ri - dc.ri);
	int c = abs(sc.ci - dc.ci);
	if (turn == white) {
		return ((r == 2 && c == 1) && (sc.ri > dc.ri));
	}
	else {
		return ((r == 2 && c == 1) && (sc.ri < dc.ri));
	}
}

bool islegalMove(char** b, position sc, position dc, int dim, int turn) {
	switch (b[sc.ri][sc.ci]) {
	case 'w':
	case 'W':
	case 'u':
	case 'U':
	case 'Y':
	case 'y':
	case 't':
	case 'T':
		return legalitygoldGeneral(b, sc, dc, turn);
		break;
	case 'E':
	case 'e':
		return (legalityking(b, sc, dc) && legalityRook(b, sc, dc) ) ;
		break;
	case 'q':
	case 'Q':
		return (legalitybishop(b, sc, dc) && legalityRook(b, sc, dc));
		break;
	case 'r':
		return legalityRook(b, sc, dc);
		break;
	case 'R':
		return legalityRook(b, sc, dc);
		break;
	case 'b':
		return legalitybishop(b, sc, dc);
		break;
	case 'B':
		return legalitybishop(b, sc, dc);
		break;
	case 'K':
	case 'O':
		return legalityking(b, sc, dc);
		break;
	case 'k':
	case 'o':
		return legalityking(b, sc, dc);
		break;
	case 'N':
		return legalityknight(b, sc, dc, turn);
		break;
	case 'n':
		return legalityknight(b, sc, dc, turn);
		break;
	case 'L':
		return legalityLance(b, sc, dc, turn);
		break;
	case 'l':
		return legalityLance(b, sc, dc, turn);
		break;
	case 'S':
		return legalitySilGeneral(b, sc, dc, turn);
		break;
	case 's':
		return legalitySilGeneral(b, sc, dc, turn);
		break;
	case 'G':
	case 'I':
		return legalitygoldGeneral(b, sc, dc, turn);
		//return (legalitybishop(b, sc, dc) || legalityRook(b, sc, dc));
		 
		break;
	case 'g':
	case 'i':
		return legalitygoldGeneral(b, sc, dc, turn);
		//return (legalitybishop(b, sc, dc) || legalityRook(b, sc, dc));
		break;
	case 'P':
		return pawnslegality(b, sc, dc, turn);
		break;
	case 'p':
		return pawnslegality(b, sc, dc, turn);
		break;
	}
}


bool **compute_highlight(char** b, position sc, int dim, int turn) {
	bool** bmap = new bool*[dim];
	for (int i = 0; i < dim; i++) {
		bmap[i] = new bool[dim] {};
	}
	position dc;
	for (int ri = 0; ri < dim; ri++) {
		for (int ci = 0; ci < dim; ci++) {
			dc.ri = ri;
			dc.ci = ci;
			if (isvaliddc(b, dim, dc, turn) && islegalMove(b, sc, dc, dim, turn)) {
				bmap[ri][ci] = true;
			}
		}
	}
	return bmap;
}
bool** compute_highlight1(char** b, position sc, int dim, int turn) {
	bool** bmap = new bool* [dim];
	for (int i = 0; i < dim; i++) {
		bmap[i] = new bool[dim] {};
	}
	//position dc;
	for (int ri = 0; ri < dim; ri++) {
		for (int ci = 0; ci < dim; ci++) {
			
			if (b[ri][ci]=='-') {
				bmap[ri][ci] = true;
			}
		}
	}
	return bmap;
}
/*
void drawbox1(int sr, int sc, int brow, int bcol, int color, int sec_color, char sym) {
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			if (r == ceil((brow - 1)/2) && c == ceil((bcol - 1)/2))
			{   

				SetClr(sec_color);
				gotoRowCol(sr + r, sc + c);
				cout << sym;
			}
			else {
				if (r == 0 || c==0 || r==brow-1 || c==bcol-1) {
					SetClr(color);
					gotoRowCol(sr + r, sc + c);
					cout << char(-37);
				}
			}
		}

	}
}*/
void highlight(char** b,bool **map, int dim, int brow, int bcol) {
	for (int r = 0; r < dim;r++) {
		for (int c = 0; c < dim; c++) {
			if (map[r][c] == true) {
				drawbox(r * brow, c * bcol, brow, bcol, 6, 7, b[r][c]);
				
			}
		}
	}
}
void unhighlight(char** b, bool** map, int dim, int brow, int bcol) {
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
			if (map[r][c] == true) {
				if ((r + c) % 2 == 0) {
					drawbox(r * brow, c * bcol, brow, bcol, 7, 7, b[r][c]);
				}
				else {
					drawbox(r * brow, c * bcol, brow, bcol, 0, 7, b[r][c]);
				}
			}
		}
	}
}
position findking(char**b,int dim,int turn) {
	char ks;
	position dc;
	if (turn == black) {
		ks = 'k';
	}
	else {
		ks = 'K';
	}
	//position dc;
	for (int ri = 0; ri < dim; ri++) {
		for (int ci = 0; ci < dim; ci++) {
		//	if ((ismypiece(b[r][c], turn)) && (b[r][c] == 'K' || b[r][c] == 'k')) {
			if ((ismypiece(b[ri][ci], turn)) && (b[ri][ci] == ks)) {
				dc.ri = ri;
				dc.ci = ci;
			}
		}
	}
	return dc;
}

bool check(char** b, int dim, int turn) {
	turnchange(turn);
	position dc;
    dc = findking(b,dim, turn);
	turnchange(turn);
	position sc;
	for (int ri = 0; ri < dim; ri++) {
		for (int ci = 0; ci < dim; ci++) {
			sc.ri = ri;
			sc.ci = ci;
			if (isvalidsi(b, dim, sc, turn) && islegalMove(b, sc, dc, dim, turn)) {
				return true;
				//cout << "CHECK!!!!......." << endl;

			}
		}
	}
	return false;
}
bool selfcheck(char** b, int dim, int turn) {
	turnchange(turn);
	return check(b, dim, turn);
}
/*
bool selfcheck(char** b, int dim, int turn) {
	string line;
	ifstream in{ "Text.txt" };
	ofstream out{ "Text1.txt" };
	while (!in.eof()) {
		getline(in, line);
		out << line << "\n";
	}
	turnchange(turn);
	return check(b, dim, turn);
}*/
void _sleep(int l) {
	for (int i = 0; i < l * 100000; i++);
}


void copyupdate(char**& b, int dim, char**& t,position& sc,position& dc) {

	t = new char* [dim];
	for (int r = 0; r < dim; r++) {
		t[r] = new char[dim];
	}
	for (int r = 0; r < dim; r++) {
		for (int c = 0; c < dim; c++) {
		   t[r][c] = b[r][c];
		}
	}
	char p = t[sc.ri][sc.ci];
	t[dc.ri][dc.ci] = p;
	t[sc.ri][sc.ci] = '-';
}
void deleteboard (char**& b, char**& t, int dim,position& sc, position& dc) {
	
	char p = t[dc.ri][dc.ci];
	t[sc.ri][sc.ci] = p;
	t[dc.ri][dc.ci] = '-';

	/*for (int r = 0; r < dim; r++) {
		delete[]t[r];
	}
	delete[]t;*/
}
void capture1(char**& b, position dc,char**& a,int& i) {
	if (a[0][i] != '\0') {
		i++;
	}
	if (b[dc.ri][dc.ci] != '-') {
		a[0][i] = b[dc.ri][dc.ci];
		i++;
	}
	i--;
}
void capture2(char**& b, position dc, char**& d,int& j) {
	if (d[0][j] != '\0') {
		j++;
	}
	if (b[dc.ri][dc.ci] != '-') {
		d[0][j] = b[dc.ri][dc.ci];
		j++;
	}
	j--;
}






bool isblackpiece1(char sym) {
	return sym >= 'a' && sym <= 'z';
}
bool iswhitepiece1(char sym) {
	return sym >= 'A' && sym <= 'Z';
}
bool ismypiece1(char sym, int turn) {
	if (turn == black) {
		return iswhitepiece1(sym);
	}
	else {
		return isblackpiece1(sym);
	}
}

bool isvalidsi1(char** c, int dim, position si, int turn) {
	if (si.ri < dim-2 || si.ri >= dim || si.ci < dim+3 || si.ci >= dim+18) {
		return false;
	}
	return true;
//	return ismypiece1(c[si.ri], turn);
}
bool isvaliddc1(char** b, int dim, position dc, int turn) {
	if (dc.ri < 0 || dc.ri >= dim || dc.ci < 0 || dc.ci >= dim) {
		return false;
	}
	if (!ismypiece(b[dc.ri][dc.ci], black) && !ismypiece(b[dc.ri][dc.ci], white)) {
		return true;
	}
	return false;
}
void selectPosition1(position& p, int dim) {
	int x, y;
	//cout << "Enter coordinates: (A1:I9): " << endl;
	/*char c;
	int d;
	cin >> c>>d;
	c = toupper(c);*/
	getRowColbyLeftClick(x, y);
	/*p.ri = d - 1;
	p.ci = c - 'A';*/
	//return p.ri, p.ci;
	p.ri = x / dim;
	p.ci = y / dim+9;
}

void updateboard2(char**& b, char**& a, position& sc, position& dc) {
	int di = sc.ci - 21;
	char p = a[0][di];
	p = tolower(p);
	b[dc.ri][dc.ci] = p;
	a[0][di] = '-';
}


void updateboard1(char**& b, char**& d, position& sc, position& dc) {
	int di = sc.ci - 21;
	char p = d[0][di];
	p = toupper(p);
	b[dc.ri][dc.ci] = p;
	d[0][di] = '-';
}


void promotion(char**&b,position& sc,int turn) {
	if (turn == white) {
		if (sc.ri == 0 || sc.ri == 1 || sc.ri == 2) {
			if (b[sc.ri][sc.ci] == 'P') {
				b[sc.ri][sc.ci] = 'W';
			}
			if (b[sc.ri][sc.ci] == 'B') {
				b[sc.ri][sc.ci] = 'Q';
			}
			if (b[sc.ri][sc.ci] == 'R') {
				b[sc.ri][sc.ci] = 'E';
			}
			if (b[sc.ri][sc.ci] == 'L') {
				b[sc.ri][sc.ci] = 'T';
			}
			if (b[sc.ri][sc.ci] == 'N') {
				b[sc.ri][sc.ci] = 'Y';
			}
			if (b[sc.ri][sc.ci] == 'S') {
				b[sc.ri][sc.ci] = 'U';
			}
			if (b[sc.ri][sc.ci] == 'G') {
				b[sc.ri][sc.ci] = 'I';
			}
			if (b[sc.ri][sc.ci] == 'K') {
				b[sc.ri][sc.ci] = 'O';
			}
		}
	}
	if (turn == black) {
		if (sc.ri == 6 || sc.ri == 7 || sc.ri == 8) {
			if (b[sc.ri][sc.ci] == 'p') {
				b[sc.ri][sc.ci] = 'w';
			}
			if (b[sc.ri][sc.ci] == 'b') {
				b[sc.ri][sc.ci] = 'q';
			}
			if (b[sc.ri][sc.ci] == 'r') {
				b[sc.ri][sc.ci] = 'e';
			}
			if (b[sc.ri][sc.ci] == 'l') {
				b[sc.ri][sc.ci] = 't';
			}
			if (b[sc.ri][sc.ci] == 'n') {
				b[sc.ri][sc.ci] = 'y';
			}
			if (b[sc.ri][sc.ci] == 's') {
				b[sc.ri][sc.ci] = 'u';
			}
			if (b[sc.ri][sc.ci] == 'g') {
				b[sc.ri][sc.ci] = 'i';
			}
			if (b[sc.ri][sc.ci] == 'k') {
				b[sc.ri][sc.ci] = 'o';
			}
		}
	}
}




void undo(char**& b, position sc, position dc,int turn , char**& a,char**& d,int& i,int& j) {
	char q = b[dc.ri][dc.ci];
	b[sc.ri][sc.ci] = q;
	b[dc.ri][dc.ci] = '-';
	if (turn == white && (i==0 || i==1 || i==2 || i==3 || i==4 )) {
		char p = a[0][i];
		b[dc.ri][dc.ci] = p;
        a[0][i] = '-';
		i--;
	}
	if (turn == black && (j == 0 || j == 1 || j == 2 || j == 3 || j == 4)) {
		char s = d[0][j];
		b[dc.ri][dc.ci] = s;
		d[0][j] = '-';
		j--;
	}
}







char** b;
int main() {
	//	char** b;
	string pname[20];
	int dim = 0, nop = 2, turn = 0;
	position sc, dc;
	char inp;
	cout << "Do you want to continue previous game? (y/n)" << endl;
    s:
	cin >> inp;
	switch (inp) {
	case 'n':
		init(b, dim, pname, turn);
		break;
	case 'N':
		init(b, dim, pname, turn);
		break;
	case 'Y':
		init1(b, dim, pname, turn);
		break;
	case 'y':
		init1(b, dim, pname, turn);
		break;
	default:
		cout << "You enter wrong choice!!!! please enter (y/n)....." << endl;
		goto s;
	}


	printbox(dim, dim, dim, b, pname[0], pname[1]);
	int i = 0, j = 0;
	char** t;
	char** a;
	a = new char* [0];
	a[0] = new char[10] {};
	char** d;
	d = new char* [0];
	d[0] = new char[10] {};
	_getch();
	cout << endl;
	bool** map;
	char input;
	bool** m;



	char*** u;
	u = new char** [10];
	for (int i = 0; i < 10; i++) {
		u[i] = new char* [10];
	}
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			u[r][c] = new char[10];

		}
	}



	while (true) {
		turnMsg(pname[turn]);
		//	do{
		do {
			do {
				do {
					do {
						selectPosition(sc, dim);
					} while (!isvalidsi(b, dim, sc, turn));
					promotion(b, sc, turn);
					map = compute_highlight(b, sc, dim, turn);
					highlight(b, map, dim, dim, dim);
					selectPosition(dc, dim);
					unhighlight(b, map, dim, dim, dim);
				} while (!isvaliddc(b, dim, dc, turn));
			} while (!map[dc.ri][dc.ci]);

			if (selfcheck(b, dim, turn) == true) {
			//	cout << "\n\n\n SELF CHECK!!!!......." << endl;
				cout << "\n\n\nCHECK....." << endl;
				_sleep(10000);
				system("cls");
				//deleteboard(b, t, dim, sc, dc);
				//updateboard(b, sc, dc);
				char p = b[dc.ri][dc.ci];
				b[sc.ri][sc.ci] = p;
				b[dc.ri][dc.ci] = '-';
				printbox(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
				printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
				turnchange(turn);
			}
			//copyupdate(b, dim, t, sc, dc);
		} while (selfcheck(b, dim, turn));
		if (turn == white) {
			capture1(b, dc, a, i);
			printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
		}
		if (turn == black) {
			capture2(b, dc, d, j);
			printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
		}
		updateboard(b, sc, dc);
		printbox(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
		printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
		if (b[dc.ri][dc.ci] == 'k' || b[dc.ri][dc.ci] == 'K') {
			if (check(b, dim, turn) == true) {
				//  cout << "\n\n\nCHECK....." << endl;
				cout << "\n\n\nSELF CHECK....." << endl;
				_sleep(10000);
				system("cls");

				char p = b[dc.ri][dc.ci];
				b[sc.ri][sc.ci] = p;
				b[dc.ri][dc.ci] = '-';
				printbox(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
				printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
				turnchange(turn);

			}
		}
		if (check(b, dim, turn) == true) {
		//  cout << "\n\n\nCHECK....." << endl;
			cout << "\n\n\nCHECK....." << endl;
			_sleep(10000);
			system("cls");
		/*	char p = b[dc.ri][dc.ci];
			b[sc.ri][sc.ci] = p;
			b[dc.ri][dc.ci] = '-';*/
			printbox(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
			printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
		//	turnchange(turn);

		}
		/*
		for (int r = 0; r < 10; r++) {
			for (int c = 0; c < 10; c++) {
				for (int k = 0; k < 10; k++) {
					char q = b[dc.ri][dc.ci];
					b[sc.ri][sc.ci] = q;
					b[dc.ri][dc.ci] = '-';
					u[r][c][k] = b[r][c];
			}
		}
        
		*/



		
			//undo
			cout << "\n\n\n\nDo you want to undo? (y/n)" << endl;
			t:
			cin >> input;
			switch (input) {
			case 'n':
				break;
			case 'N':
				break;
			case 'Y':
				undo(b, sc, dc,turn,a,d,i,j);
				printbox(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
				printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
				turnchange(turn);
				break;
			case 'y':
				undo(b, sc, dc,turn,a,d,i,j);
				printbox(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
				printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
				turnchange(turn);
				break;
			default:
				cout << "\n\n\n\nYou enter wrong choice!!!! please enter (y/n)....." << endl;
				goto t;
			}
		
			//save
		ofstream out{ "BSCS22101-save.txt" };
		if (out.is_open()) {
			out << dim << endl;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					out << b[i][j] << " ";
				}
				out << endl;
			}
		}
		//	}while (input == 'Y' || input == 'y');

		char in;
		if (a[0][0] != '\0' || d[0][0] != '\0') {
			cout << "\n\n\n\n\nDo you want to drop? (y/n)" << endl;
		w:
			cin >> in;
			switch (in) {
			case 'n':
				break;
			case 'N':
				break;
			case 'Y':
				if (turn == white) {
					do {
						do {
							selectPosition1(sc, dim);

						} while (!isvalidsi1(d, dim, sc, turn));

						m = compute_highlight1(b, sc, dim, turn);
						highlight(b, m, dim, dim, dim);
						selectPosition(dc, dim);
						unhighlight(b, map, dim, dim, dim);
					} while (!isvaliddc1(b, dim, dc, turn));


					updateboard2(b, d, sc, dc);
					printbox(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
					printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
					//	i--;

				}
				if (turn == black) {
					do {
						do {
							selectPosition1(sc, dim);

						} while (!isvalidsi1(d, dim, sc, turn));

						m = compute_highlight1(b, sc, dim, turn);
						highlight(b, m, dim, dim, dim);
						selectPosition(dc, dim);
						unhighlight(b, map, dim, dim, dim);
					} while (!isvaliddc1(b, dim, dc, turn));

					updateboard1(b, a, sc, dc);
					printbox(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
					printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
					//	j--;
				}
				break;
			case 'y':
				if (turn == white) {
					do {
						do {
							selectPosition1(sc, dim);

						} while (!isvalidsi1(d, dim, sc, turn));

						m = compute_highlight1(b, sc, dim, turn);
						highlight(b, m, dim, dim, dim);
						selectPosition(dc, dim);
						unhighlight(b, map, dim, dim, dim);
					} while (!isvaliddc1(b, dim, dc, turn));


					updateboard2(b, d, sc, dc);
					printbox(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
					printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
					//	i--;
				}
				if (turn == black) {
					do {
						do {
							selectPosition1(sc, dim);

						} while (!isvalidsi1(d, dim, sc, turn));

						m = compute_highlight1(b, sc, dim, turn);
						highlight(b, m, dim, dim, dim);
						selectPosition(dc, dim);
						unhighlight(b, map, dim, dim, dim);
					} while (!isvaliddc1(b, dim, dc, turn));

					updateboard1(b, a, sc, dc);
					printbox(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
					printbox1(dim, dim, dim, b, pname[0], pname[1], a, d, i, j);
					//	j--;

				}
				break;
			default:
				cout << "\n\n\n\nYou enter wrong choice!!!! please enter (y/n)....." << endl;
				goto w;
			}

		}
		
		turnchange(turn);
		cout << endl;

	}

	return 0;

}










/*
cout << (void*)&b[0];
	cout << (void*)&b[1];
	cout << (void*)&b[2];
	cout << (void*)&b[3];
	cout << (void*)&b[4];
	cout << (void*)&b[5];
	cout << (void*)&b[6];
	cout << (void*)&b[7];
	cout << (void*)&b[8];

	cout << (void*)&b[0][0];
	cout << (void*)&b[0][1];
	cout << (void*)&b[0][2];
	cout << (void*)&b[0][3];

	cout << (void*)&b[1][0];
	cout << (void*)&b[1][1];
	cout << (void*)&b[1][2];
	cout << (void*)&b[1][3];

	cout << (void*)&b[2][0];
	cout << (void*)&b[3][0];
	cout << (void*)&b[4][0];
	cout << (void*)&b[5][0];
	cout << (void*)&b[6][0];
	cout << (void*)&b[7][0];
	cout << (void*)&b[8][0];
	*/

