#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct Wyciag
{
	int xd;
	int yd;
	int xs;
	int ys;
	int podroz;
	int czastrwania;
};
struct Wyciagi
{
	Wyciag wyciag[10000];
	int ile;
	int odwiedzone;
	Wyciag *next;
};


template <class T> void swap3(T& a, T& b)
{
	T c(a); a = b; b = c;
}

struct punkt
{
	int dlugosc_sciezki;
	int wartosc;
	bool odwiedzony;
	int x, y;
	int ind;

};

struct KolejkaP
{
	punkt *tab[9999999];
	int ie;

	 void heapyfiUp(int i)
	 { //przyspieszyc
		 int P = i / 2;

		 while (i > 1)
		 {
			 if (tab[P]->dlugosc_sciezki > tab[i]->dlugosc_sciezki)
			 {
				 swap3(tab[P], tab[i]);
			 }
			 i = P;
			 P = i / 2;
		 }
	 }

	void heapyfy(int i)
	{
		int L = 2 * i;
		int P = 2 * i + 1;
		int min;

		if (L <= ie && tab[L]->dlugosc_sciezki < tab[i]->dlugosc_sciezki) // jezeli lewy element jest mniejszy od rodzica to trzeba go zamienic
		{
			min = L; //mniejszy stoi na lewej stronie
		}
		else min = i;


		if (P <= ie && tab[P]->dlugosc_sciezki < tab[min]->dlugosc_sciezki) // jezeli prawy element jest mniejszy od rodzica to trzeba go zamienic
		{
			min = P; //mniejszy stoi na prawej stronie
		}

		if (min != i)  //zamiana elementow i 
		{
			swap3(tab[i], tab[min]);
			heapyfy(min);
		}

	}

	void buildHeap()
	{
		for (int i = ie / 2; i >= 1; i = i / 2)
		{
			heapyfy(i);
		}
	}

	void insertHeap(int l, int dlugosc_sciezki, int  x, int y, punkt **wysokosci)
	{
		ie++;
		tab[ie] = &wysokosci[y][x];
		tab[ie]->wartosc = l;
		tab[ie]->ind = ie;
		tab[ie]->x = x;
		tab[ie]->y = y;
		tab[ie]->dlugosc_sciezki = dlugosc_sciezki;
		buildHeap();
	}

	punkt removeHeap()
	{
		punkt korzen;
		korzen.wartosc = tab[1]->wartosc;
		korzen.dlugosc_sciezki = tab[1]->dlugosc_sciezki;
		korzen.x = tab[1]->x;
		korzen.y = tab[1]->y;
		korzen.ind = tab[1]->ind;
		tab[1] = tab[ie];
		ie--;
		buildHeap();
		return korzen;
	}
	void wypisz()
	{
		int p;
		punkt liczba;
		for (int i = 1; i <= ie;)
		{
			p = tab[i]->dlugosc_sciezki;
			liczba = removeHeap();
			printf("%d: %d ", liczba.wartosc, p);
		}
	}

};

void sprawdzSasiada(KolejkaP *Q, punkt **odleglosci, punkt u, punkt v)
{
	int d,dv;
	//dv odleglosc danego wierzcholka od poczatku startu

	if (!(odleglosci[v.y][v.x].odwiedzony)) // jezeli wierzcholek nie odwiedzony
	{
		if (odleglosci[u.y][u.x].wartosc < odleglosci[v.y][v.x].wartosc)
			d =  odleglosci[v.y][v.x].wartosc-odleglosci[u.y][u.x].wartosc + 1;
		else
			d = 1;
		dv = u.dlugosc_sciezki + d;
		
		if (odleglosci[v.y][v.x].dlugosc_sciezki > odleglosci[u.y][u.x].dlugosc_sciezki + d)
		{

		   if (odleglosci[v.y][v.x].ind == 0)//sprawdzam czy jest w kopcu, jezeli nie ma, to tworze nowy w kopcu
		   {
			   Q->insertHeap(odleglosci[v.y][v.x].wartosc, dv, v.x, v.y, odleglosci); // musisz wstawic do kolejki nowy wierzcholek	
		   }  
		   else //jezeli jest podmieniam mu wartosc i przestawiam w odpowiednie miejsce
		   {
			  // Q->heapyfiUp(odleglosci[v.y][v.x].ind);
			   Q->insertHeap(odleglosci[v.y][v.x].wartosc, dv, v.x, v.y, odleglosci);
		   }
		}	
	}

}
int Dijkstra(KolejkaP *Q, int xd, int yd, int xilosc, int yilosc, punkt **odleglosci, Wyciagi *wyciagi)
{
	punkt u, v;
	int x, y,i=0,czas;
	int tx, ty, dv,mindv;
	bool czywyciag = false;
    //while (x != xd -1 || y != yd-1)
	//while (Q->ie >0)
	while(odleglosci[yd][xd].odwiedzony !=true)
	{
	    u = Q->removeHeap(); //zwraca i usuwa element o najnizszym priorytecie(dlugosci drogi)
		//czywyciag = false;
		x = u.x;
		y = u.y;
		
		odleglosci[y][x].odwiedzony = true;

		if (wyciagi->ile > 0)
		{
			//sprawdzam czy w tym miejscu jest wyciag
			i = wyciagi->odwiedzone;
			while (i <= wyciagi->ile)
			{
				//czywyciag = false;
				if (wyciagi->wyciag[i].xs == u.x && wyciagi->wyciag[i].ys == u.y && odleglosci[wyciagi->wyciag[i].yd][wyciagi->wyciag[i].xd].odwiedzony == false)
				{
					//while (wyciagi->wyciag[i].xs == u.x && wyciagi->wyciag[i].ys == u.y)
					//{
					if (u.dlugosc_sciezki%wyciagi->wyciag[i].podroz == 0)
					{
						dv = u.dlugosc_sciezki + wyciagi->wyciag[i].czastrwania;
					}
					else
					if (wyciagi->wyciag[i].podroz == 0 || wyciagi->wyciag[i].podroz == 1 || u.dlugosc_sciezki == 0)
						{
							dv = u.dlugosc_sciezki + wyciagi->wyciag[i].czastrwania;
						}
						else
						{
							dv = u.dlugosc_sciezki + (wyciagi->wyciag[i].podroz - u.dlugosc_sciezki%wyciagi->wyciag[i].podroz) + wyciagi->wyciag[i].czastrwania;
						}
				

					wyciagi->odwiedzone++;
						Q->insertHeap(odleglosci[wyciagi->wyciag[i].yd][wyciagi->wyciag[i].xd].wartosc, dv, wyciagi->wyciag[i].xd, wyciagi->wyciag[i].yd, odleglosci);
						//i++;
						//czywyciag = true;
					//}
				
				}
				
				//if(czywyciag==false) 
					i++;
			}
		}
	
			//cout << u.dlugosc_sciezki << " " << x << y << endl;
			//sprawdzam sasiadow
			if (y > 0)
			{
				v.x = x;
				v.y = y - 1;
				sprawdzSasiada(Q, odleglosci, u, v);
			}
			if (y < yilosc - 1)
			{
				v.x = x;
				v.y = y + 1;
				sprawdzSasiada(Q, odleglosci, u, v);
			}
			if (x > 0)
			{
				v.x = x - 1;
				v.y = y;
				sprawdzSasiada(Q, odleglosci, u, v);
			}
			if (x < xilosc - 1)
			{
				v.x = x + 1;
				v.y = y;
				sprawdzSasiada(Q, odleglosci, u, v);
			}
			czywyciag = false;
	}
	return odleglosci[yd][xd].dlugosc_sciezki;
}
void wczytanieDanych()
{
	KolejkaP *Q = new KolejkaP;
	Q->ie = 0;
	int nieskonczonosc = 2147483647; // :)
	ifstream plik, out;
	plik.open("16.in");
	int xilosc=0, yilosc = 0, xs = 0, ys = 0, xd = 0, yd = 0, liczbaWyciagow = 0, i = 0, j = 0, w=0;
	int podroz = 0, czastrwania=0;
	int  xsw,ysw, xdw, ydw;
	//scanf("%d %d %d %d %d %d %d", &xilosc, &yilosc, &xs, &ys, &xd, &yd, &liczbaWyciagow);
	plik >> xilosc >> yilosc >> xs >> ys >> xd >> yd >> liczbaWyciagow;
	Wyciagi *wyciagi = new Wyciagi;
	if (liczbaWyciagow > 0)  //wpisanie wyciagow
	{
		
		for (w = 0; w < liczbaWyciagow; w++)
		{
			plik >> xsw >> ysw >> xdw >> ydw >> czastrwania >> podroz;
			//scanf("%d %d %d %d %d %d", &xsw, &ysw, &xdw, &ydw, &czastrwania, &podroz);
			wyciagi->ile =w;
			wyciagi->wyciag[w].xs=xsw;
			wyciagi->wyciag[w].ys=ysw;
			wyciagi->wyciag[w].xd=xdw;
			wyciagi->wyciag[w].yd=ydw;
			wyciagi->wyciag[w].czastrwania=czastrwania;
			wyciagi->wyciag[w].podroz = podroz;
			//if (w != 0 && wyciagi->wyciag[w - 1].xs == wyciagi->wyciag[w].xs && wyciagi->wyciag[w - 1].ys == wyciagi->wyciag[w].ys)wyciagi->wyciag[w].n

		}
		
	}
	wyciagi->odwiedzone = 0;
	punkt **wysokosci = new punkt *[yilosc];

	for (i = 0; i < yilosc; i++)
	{
		wysokosci[i] = new  punkt[xilosc];
		for (j = 0; j < xilosc; j++)
		{
			//scanf("%d", &wysokosci[i][j].wartosc);
			plik >> wysokosci[i][j].wartosc;
			//cout << wysokosci[i][j].wartosc;
			
			if (j == xs && i == ys)
			{
				Q->insertHeap(wysokosci[i][j].wartosc, 0, j,i, wysokosci); // pierwszy wierzcholek ma najnizszy priorytet
				wysokosci[i][j].dlugosc_sciezki = 0;
				wysokosci[i][j].ind = 1;
			}
			else
			{
				wysokosci[i][j].dlugosc_sciezki = nieskonczonosc;
				wysokosci[i][j].ind = 0;
			}


			wysokosci[i][j].odwiedzony = false;
		}
	}

	cout<<Dijkstra(Q, xd, yd, xilosc, yilosc, wysokosci, wyciagi);
	delete[] wyciagi;
	delete[] wysokosci;
}


int main()
{
	wczytanieDanych();
	
    getchar();
	getchar();
	return 0;
	

}