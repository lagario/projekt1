#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <conio.h>
#include <fstream>

using namespace std;

int n = 0, m = 0;
int **tab;





int s = 0, f = 0;


void display(){
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			if (tab[i][j] == 1) cout << (char)(254);
			if (tab[i][j] == 0) cout << " ";
			if (tab[i][j] == 2) cout << "x";
		}
		cout << endl;
	}
	cout << endl;
}
void fulltab(){
	for (size_t i = 0; i < n; i++)
	for (size_t j = 0; j < m; j++)
		tab[i][j] = 1;
}
void border(){
	for (size_t i = 0; i < n; i++)
	for (size_t j = 0; j < m; j++)
	{
		if (i == 0 || j == 0 || j == m - 1 || i == n - 1)
			tab[i][j] = 1;
		else
			tab[i][j] = 0;
	}
	tab[0][s] = 0;
	tab[n - 1][f] = 0;
}
int ils(int x, int y)
{
	if (x<0) return 0;
	int c = 0;
	if (x > 0 && tab[x - 1][y])c++;
	if (x<n - 1 && tab[x + 1][y])c++;
	if (y > 0 && tab[x][y - 1])c++;
	if (y<m - 1 && tab[x][y + 1])c++;
	return c;
}
bool canmove(int d, int x, int y){
	if (d < 0)d += 1000;
	int a = d % 4;
	if (a == 0 && tab[x][y + 1] == 0) return true;
	if (a == 1 && tab[x - 1][y] == 0) return true;
	if (a == 2 && tab[x][y - 1] == 0) return true;
	if (a == 3 && tab[x + 1][y] == 0) return true;
	return false;
}
bool candig(int d, int x, int y){
	if (d < 0)d += 1000;
	int a = d % 4;
	if (a == 0 && ils(x, y + 1) > 2) return true;
	if (a == 1 && ils(x - 1, y) > 2) return true;
	if (a == 2 && ils(x, y - 1) > 2) return true;
	if (a == 3 && ils(x + 1, y) > 2) return true;
	return false;
}
void move(int d, int &x, int &y){
	if (d < 0)d += 1000;
	int a = d % 4;
	if (a == 0) y++;
	if (a == 1) x--;
	if (a == 2) y--;
	if (a == 3) x++;
}
bool check(){
	int px = 0; int py = s; int direction = 3;
	if (!canmove(direction, px, py)) return false;
	move(direction, px, py);
	while (!(px == 0 || px == n - 1))
	{
		if (canmove(direction + 3, px, py))	direction += 3;
		else if (canmove(direction, px, py))	direction += 0;
		else if (canmove(direction + 1, px, py))	direction += 1;
		else direction += 2;
		move(direction, px, py);
		//tab[px][py] = 2;



	}
	if (px == n - 1)return true;
	return false;
}

void dig(int px, int py, int direction, int bchance){
	while (!(bchance == 0 && px == n - 2))
	{
		if ((!candig(direction + 3, px, py) && !candig(direction, px, py) && !candig(direction + 1, px, py)) || rand() % 100<bchance)
			break;
		int dir;
		do
		{
			int r = rand() % 100;
			dir = direction;
			if (r > 75) dir++;
			if (r < 25) dir += 3;
		} while (!candig(dir, px, py));
		move(dir, px, py); direction = dir;
		tab[px][py] = 0;
		if (rand() % 100 < 90) dig(px, py, rand() % 4, 15);
	}
}
void repair()
{
	int px = 1; int py = s; int direction = 3;
	for (size_t i = 0; i < 10; i++)
	while (px != 0)
	{
		if (canmove(direction + 3, px, py))	direction += 3;
		else if (canmove(direction, px, py))	direction += 0;
		else if (canmove(direction + 1, px, py))	direction += 1;
		else direction += 2;
		move(direction, px, py);
		//tab[px][py] = 2;
		dig(px, py, direction + 3, 15);
		dig(px, py, direction + 1, 15);

	}
}

int main()
{
	do
	{
		cout << "podaj wymiary labityntu" << endl;
		cin >> n >> m;
	} while (n*m > 10000);

	tab = new int *[n];
	for (size_t i = 0; i < n; i++) tab[i] = new int[m];
	fulltab();
	srand(time(NULL));
	s = rand() % (m - 2) + 1;


	tab[0][s] = 0;

	dig(0, s, 3, 0);
	repair();
	do
	{
		f = rand() % (m - 2) + 1;
	} while (tab[n - 2][f] == 1);
	tab[n - 1][f] = 0;




	display();

	ofstream plik("labirynt.txt");
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			if (tab[i][j] == 0) plik << " ";
			else plik << "#";
		}
		plik << endl;
	}

	_getch();
}