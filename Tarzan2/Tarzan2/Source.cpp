#include <iostream>
#include <fstream>
using namespace std;

//Algorytm Bron-Kerbosh, ¿ród³o algorytmu: wikipedia
struct Sasiedzi
{
	int ilosc;
	int tab[200];

	Sasiedzi()
	{
		ilosc = 0;
	}

	void dodajSasiadow(int v)
	{
		tab[ilosc]=v;
		ilosc++;
	}
};

struct Zbior
{
	int ilosc;
	int tab[200];

	Zbior()
	{
		ilosc = 0;
	}

	void dodajWierzcholek(int v)
	{
		tab[ilosc]=v;
		ilosc++;
	}

	void usunWierzcholek(int v)
	{
		for (int i = 0; i < ilosc; i++)
		{
			if (tab[i] == v)
			{
				for (int j = i; j < ilosc-1; j++)
				{
					tab[j] = tab[j + 1];
				}

				break;
			}
		}

		if(ilosc >= 0) ilosc--;
	}

	bool czy(int sasiad, Zbior P)
	{
		for (int i = 0; i < P.ilosc; i++)
		{
			if (P.tab[i] == sasiad)
			{
				return true;
			}
		}
		return false;
	}

	void iloczyn(Zbior P, Sasiedzi N)
	{
		ilosc=0;
		for (int j = 0; j < N.ilosc; j++)
		{
			if (czy(N.tab[j], P))
			{
				tab[ilosc] = N.tab[j];
				ilosc++;
			}
		}

	}
};

struct Klika
{
	int ilosc;
	int tab[200];

	Klika()
	{
		ilosc = 0;
	}

	void wypiszElementy(int k)
	{
		for (int i = 0; i < ilosc; i++)
		{
			cout << tab[i] << " ";
		}
		if (ilosc >= k)cout << "TAK";
		else cout << "NIE";

		cout << endl;
	}

	void dodajElement(Klika R, int v)
	{
		ilosc = 0;
		for (int i = 0; i < R.ilosc; i++)
		{
			tab[i] = R.tab[i];
			ilosc++;
		}
		tab[ilosc] = v;
		ilosc++;
	}
};

bool sprawdzIstnienie(Zbior P, int v)
{
	if (P.ilosc == 0)return false;
	for (int i = 0; i < P.ilosc; i++)
	{
		if (P.tab[i] == v)
		{
			return true;
		}
		
	}
	return false;
}

int BronKerbosh(int p1, int k, int n, int vertex[][200], Klika R, Zbior *P, Zbior *X, bool ZNALEZIONA)
{
	Klika r;
	Zbior p;
	Zbior x;
	Sasiedzi N;
	int v;

	if (P->ilosc == 0 && X->ilosc == 0 && R.ilosc>=p1)
	{
		//R.wypiszElementy(p1);
		ZNALEZIONA = true;
		return 1;
	}
	else
	{
		   for (v = 0; v < n; v++)
			{
			   if (sprawdzIstnienie(*P,v))
			   {
                 //sasiedzi
				for (int j = 0; j < n; j++)
				{
					if (vertex[v][j] == k)
					{
						N.dodajSasiadow(j);
					}
				}

				//iloczyny 
				r.dodajElement(R, v);
				p.iloczyn(*P, N); //z P usuwam nie-sasiadow v
				x.iloczyn(*X, N); //z X usuwam nie-sasiadow v
			
      			BronKerbosh(p1, k, n, vertex, r, &p, &x,ZNALEZIONA);

				P->usunWierzcholek(v);
				X->dodajWierzcholek(v);
			   }
				
			}
		   return 0;
	}
	
}

bool sprawdz(int p1, int k, int n, int vertex[][200], Klika R, Zbior *P, Zbior *X, bool ZNALEZIONA)
{
	if (p1 <= n)
	{
		for (int i = 1; i <= k; i++)
		{
			BronKerbosh(p1, i, n, vertex, R, P, X, ZNALEZIONA);

			if (ZNALEZIONA == true)
			{
				cout << "Tak" << endl;
				return true;
			}
				
		}
	}
	else if (p1==1)
	{
		cout << "Tak" << endl;
		return true;
	}
	else
	{
		cout << "Nie" << endl;
		return true;
	}

	return false;

}

int main()
{
	int n, k, p;
	int vertex[200][200];
	ifstream plik;
	plik.open("t.txt");
	bool ZNALEZIONA;

	plik >> n >> k >> p;

	Klika R;
	Zbior P;
	Zbior X;
	for (int w = 0; w < 100; w++)
	{
		ZNALEZIONA = false;
		for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					plik >> vertex[i][j];
				}

				P.dodajWierzcholek(i);
			}

			if (sprawdz(p, k, n, vertex, R, &P, &X, false) == false)
				cout << "Nie" << endl;
	}
	


	getchar();
	getchar();
	return 0;
}
