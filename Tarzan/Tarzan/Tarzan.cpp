#include <iostream>
#include <math.h>
#include <fstream>
#include <stdio.h>

#include <Windows.h>
using namespace std;
int A = 0;
struct punkt
{
	int x, y;
	bool odwiedzony;
};

double odl(int x1, int y1, int x2, int y2)
{
	A++;
	return sqrt((double)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}

bool odwiedzona(int tab[], int index, int ilosc)
{
	for (int i = 0; i < ilosc; i++)
	{
		if (tab[i] == index)return false;
	}

	return true;
}

bool duplikaty(punkt tab[],int l1, int l2, int indx)
{
	for (int i = 0; i <= indx; i++)
	{
		if (tab[i].x == l1 && tab[i].y == l2)return false;
	}
	return true;
}

int per2(int t[], int k, int ilosc)
{
	int z = 0, j = 0, br = 0; double droga = 0, odleglosc = 0;
	static int h;
	if (k < ilosc)
	{
		for (int i = k; i < ilosc; i++){
			z = t[k];
			t[k] = t[i];
			t[i] = z;
			per2(t, k + 1, ilosc);
			z = t[k];
			t[k] = t[i];
			t[i] = z;
			for (int j = 0; j < ilosc; j++){ cout << t[j]; }
			cout << endl;
		}
	}
	return k;
}

int per(int t[], int k, int ilosc, punkt tab[], double &min, double **Odleglosci)
{
	int z = 0, j = 0, br = 0; double droga = 0, odleglosc=0;
	if (k<ilosc)
	{
		for (int i = k; i<ilosc; i++){
			z = t[k];
			t[k] = t[i];
			t[i] = z;
			per(t,k+1, ilosc, tab,min,Odleglosci);
			z = t[k];
			t[k] = t[i];
			t[i] = z;
		}
	}
else
{
	//cout << h + 1 << " ";;
	//for (int j = 0; j < ilosc; j++){ cout << t[j]; }
	//cout << endl;

	for (int i = 0; i < ilosc - 1; i++)
	{
		if (tab[t[i]].odwiedzony == false)
		{
			//odleglosc = odl(tab[t[i]].x, tab[t[i]].y, tab[t[i + 1]].x, tab[t[i + 1]].y);
		    odleglosc = Odleglosci[t[i]][t[i+1]];

			if (odleglosc<1000.0)
				droga = droga + odleglosc;
			else
			{
				//sprawdzam czy po drodze do rzeki nie trafiam na moja docelowa wioske. Jezeli nie trafiam biegne do rzeki. Jak trafiam ide do wioski
				if (tab[t[i]].y != tab[t[i+1]].y) 
				{
					odleglosc = tab[t[i]].x + abs(tab[t[i]].y - tab[t[i + 1]].y) + tab[t[i + 1]].x; //odleglosc od A do rzeki, wzdluz rzeki do punktu y, od punktu y do B
				}
				droga = droga + odleglosc;

			}

			tab[t[i]].odwiedzony = true;
		}
		if (droga>min && min != 0){ break; br = 1; }
	}

	//odleglosc = odl(tab[t[0]].x, tab[t[0]].y, tab[t[ilosc - 1]].x, tab[t[ilosc - 1]].y); //dodanie drogi od ostatniej wioski t[] do wioski zerowej
	odleglosc = Odleglosci[t[0]][t[ilosc - 1]];

	if (br == 0 || tab[t[ilosc - 1]].odwiedzony == true)
	{
		if (odleglosc<1000.0)
			droga = droga + odleglosc;
		else
		{
			//sprawdzam czy po drodze do rzeki nie trafiam na moja docelowa wioske. Jezeli nie trafiam biegne do rzeki. Jak trafiam ide do wioski
			if (tab[t[0]].y != tab[t[ilosc-1]].y)
			{
				odleglosc = tab[t[0]].x + abs(tab[t[0]].y - tab[t[ilosc - 1]].y) + tab[t[ilosc - 1]].x; //odleglosc od A do rzeki, wzdluz rzeki do punktu y, od punktu y do B
			}
			droga = droga + odleglosc;

		}
	}
	
	if (min == 0) min = droga;
	if (droga < min)min = droga;
	br = 0;
	for (int i = 0; i < ilosc; i++)
		tab[i].odwiedzony = false;
}
		return (int)floor(min);
}
int main()
{
	
	double ** Odleglosci;
	//   VISUAL
	int testy,i,j,ilwiosek,l1,l2,indx=0, *t;
	char zn;
	double min = 0;
	punkt *tab;
	ifstream plik,out;
	plik.open("1.in");
	out.open("2.out");
	int b;
	plik >> testy;
	for (i = 0; i < 2; i++)
	{
		plik >> ilwiosek;
		tab = new punkt[ilwiosek];
		Odleglosci = new double *[ilwiosek];
		plik >> zn;
		plik >> zn;
		for (j = 0; j < ilwiosek; j++)
		{
			plik>>l1; //x
			plik >> zn; 
			plik>>l2;//y
			if (duplikaty(tab,l1,l2, indx))
			{
				tab[indx].x = l1;
				tab[indx].y = l2;
				indx++; //ile punktow
			}
			plik >> zn; // )
			plik >> zn; // ,
			if(j != ilwiosek-1)plik >> zn; // (
			
		}
		//jezeli punktow jest n, przekazuje n-1
		t = new int[indx];
		for (int h = 0; h < indx; h++)
			Odleglosci[h] = new double[indx]; // Tworzymy wiersze
		for (int x = 0; x < indx; x++)
		{
			t[x] = x;
			tab[x].odwiedzony = false;
			for (int y = 0; y < indx; y++) Odleglosci[x][y] = odl(tab[x].x, tab[x].y, tab[y].x, tab[y].y);
		}
		
		out >> b;
		min = 0;
		printf("%i\n",per(t,0,indx,tab,min, Odleglosci));
		printf("doby %i\n", b);
		
		delete[] tab;
		delete[] t;
		delete[] Odleglosci;
		indx = 0;
	}
	cout << A;

	getchar();
	getchar();
	return 0;
}

