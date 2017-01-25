#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<conio.h>
using namespace std;



struct punkts
{
	double dl;
	int nrp;
	punkts* nast;

};

struct punkt
{
	int nr;
	double odl;
	bool done;
	punkt* nast;
	punkts* sasiad;
	int poprzednik;
};

void dodajp(punkt* &glowa)
{
	punkt* nowy = new punkt;
	nowy->odl = 99999999;
	nowy->sasiad = NULL;
	nowy->done = false;
	nowy->poprzednik = 0;
	if (glowa == NULL)
	{
		nowy->nr = 1;
		nowy->nast = NULL;

	}
	else
	{
		nowy->nr = glowa->nr + 1;
		nowy->nast = glowa;
	}
	glowa = nowy;
}
void dodajs(punkt* p, int nr1, double d)
{
	punkts* nowy = new punkts;
	nowy->nrp = nr1;
	nowy->dl = d;
	if (p->sasiad == NULL)
		nowy->nast = NULL;
	else
		nowy->nast = p->sasiad;
	p->sasiad = nowy;
}
void dodajd(int nr1, int nr2, double d, punkt*glowa)
{
	while (glowa)
	{
		if (glowa->nr == nr1)
			dodajs(glowa, nr2, d);
		if (glowa->nr == nr2)
			dodajs(glowa, nr1, d);
		glowa = glowa->nast;
	}
}

bool isdigits(const string &str)
{
	return str.find_first_not_of("0123456789") == string::npos;
}

bool isdigits2(const string &str)
{
	return str.find_first_not_of("0123456789.") == string::npos;
}

punkt* znajdz(int nr1, punkt*glowa)
{
	while (glowa)
	{
		if (glowa->nr == nr1)
			return glowa;
		glowa = glowa->nast;
	}
}
bool check(int a, int b, punkt* glowa)
{
	punkts* tmp = znajdz(a, glowa)->sasiad;
	while (tmp)
	{
		if (tmp->nrp == b)
			return true;
		tmp = tmp->nast;
	}
	return false;
}

punkt* najbp(punkt* glowa)
{
	punkt* tmp = glowa;
	int a = 1000000000;
	int n = 0;
	while (tmp)
	{
		if (tmp->odl < a&&tmp->done == false)
		{
			n = tmp->nr;
			a = tmp->odl;
		}
		tmp = tmp->nast;
	}
	if (n == 0) return NULL;
	return znajdz(n, glowa);
}

int main()
{
	punkt* glowa = NULL;
	string a;
	int ilp = 0, start = 0, meta;
	double dist = 0;
	bool end = false;

	cout << "podaj liczbe punktow" << endl;
	do
	{
		cin >> a;
		if (isdigits(a))
			ilp = atoi(a.c_str());
	} while (ilp<1);
	for (size_t i = 0; i < ilp; i++)

		dodajp(glowa);

	cout << "podaj polaczenia miedzy punktami:" << endl << endl;

	for (;;)
	{
		do
		{
			start = 0;
			cout << "podaj nr pierwszego punktu" << endl << ", lub wpisz k i zakoncz podawanie polaczen " << endl;
			cin >> a;
			if (a == "k"){
				end = true;
				break;
			}
			if (isdigits(a))
				start = atoi(a.c_str());

		} while (start<1 || start>ilp);

		if (end) break;

		do
		{
			meta = 0;
			cout << "podaj nr drugiego punktu" << endl;
			cin >> a;
			if (isdigits(a))
				meta = atoi(a.c_str());

		} while (meta<1 || meta>ilp);
		do
		{
			dist = 0;
			cout << "podaj odleglosc" << endl;
			cin >> a;
			if (isdigits2(a))
				dist = atof(a.c_str());

		} while (dist <= 0);
		if (check(start, meta, glowa))
			cout << "sciezka laczaca te punkty juz istnieje" << endl;
		else
			dodajd(start, meta, dist, glowa);
	}




	do
	{
		start = 0;
		cout << "podaj nr startowego punktu" << endl;
		cin >> a;
		if (isdigits(a))
			start = atoi(a.c_str());

	} while (start<1 || start>ilp);

	do
	{
		meta = 0;
		cout << "podaj nr koncowego punktu" << endl;
		cin >> a;
		if (isdigits(a))
			meta = atoi(a.c_str());

	} while (meta<1 || meta>ilp);


	znajdz(meta, glowa)->odl = 0;
	punkt*tmp = najbp(glowa);
	while (tmp)
	{


		punkts*tmp2 = tmp->sasiad;
		while (tmp2)
		{
			if (znajdz(tmp2->nrp, glowa)->odl > tmp->odl + tmp2->dl)
			{
				znajdz(tmp2->nrp, glowa)->odl = tmp->odl + tmp2->dl;
				znajdz(tmp2->nrp, glowa)->poprzednik = tmp->nr;

			}
			tmp2 = tmp2->nast;
		}
		tmp->done = true;
		tmp = najbp(glowa);
	}

	punkt* tmp3 = znajdz(start, glowa);
	cout << start;
	while (tmp3->poprzednik)
	{
		cout << " -> " << tmp3->poprzednik;
		tmp3 = znajdz(tmp3->poprzednik, glowa);
	}

	//punkt* tmp4 = glowa;
	//for (size_t i = 0; i < ilp; i++)
	//{
	//	cout << tmp4->nr <<endl<< tmp4->odl<<endl<<endl;
	//	punkts*tmp5=tmp4->sasiad;
	//	while (tmp5)
	//	{
	//		cout << tmp5->dl << endl << tmp5->nrp << endl << endl;
	//		tmp5 = tmp5->nast;
	//	}
	//	cout << endl << endl << endl;
	//	tmp4 = tmp4->nast;
	//}
	cout << "wcisnij s zeby zapisac do pliku";
	if (_getch() == 's');
	{
		ofstream plik("droga.txt");
		punkt* tmp6 = znajdz(start, glowa);
		plik << start;
		while (tmp6->poprzednik)
		{
			plik << " -> " << tmp6->poprzednik;
			tmp6 = znajdz(tmp6->poprzednik, glowa);
		}
	}
	return 0;
}