#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
struct Wezel{

	int wartosc;
	//bool pusty;
	int iloscElementow;
	Wezel **wezel;
	Wezel *rodzic;

	Wezel(int ile)
	{
		iloscElementow = ile;
		//pusty = true;
		rodzic = NULL;
		wezel = new Wezel *[ile];
		for (int i = 0; i < ile; i++) wezel[i] = NULL;
		//for (int i = 0; i < ile; i++) wezel[i]->pusty=true;
	}

	Wezel(){
		//pusty = true;
		rodzic = NULL;
		wezel = NULL;
	};

	void zwolnijPamiec()
	{
		delete[] wezel;
		rodzic = NULL;
	}
};
bool sprawdzamBezdzietnosc(Wezel *wezel)
{
	for (int i = 0; i < wezel->iloscElementow; i++)
	{
		if (!wezel->wezel[i] == NULL)
		{

			//wezel->rodzic->wezel[i]->pusty = true;  //pamietaj o tym !!
			return false;
		}
	}

	//zwraca true jezeli bezdzietny
	return true;
}
void insert(Wezel *wezel, int liczba, int nowaL, int k)
{
	int nowaLiczba = nowaL;
	int numerIndeksu;

	if (wezel->wartosc<0) //jezeli wartosc jest mniejsza od 0 to wezel jest pusty
	{
		wezel->wartosc = liczba;
		//wezel->pusty = false;
	}
	else
	{
		if (wezel->wartosc == liczba)
			printf("%d%s ", liczba, " exist \n");
		else
		{
			//musisz utworzyc nowy wezel, wyliczyc nowy index i dodac wartosc
			numerIndeksu = nowaLiczba % wezel->iloscElementow;
			nowaLiczba = nowaLiczba / wezel->iloscElementow;

			if (wezel->wezel[numerIndeksu] == NULL || wezel->wezel[numerIndeksu]->wartosc<0) // jezeli pusty to tworze nowy
			{
				wezel->wezel[numerIndeksu] = new Wezel(k);
				wezel->wezel[numerIndeksu]->rodzic = wezel;

			}

			insert(wezel->wezel[numerIndeksu], liczba, nowaLiczba, k);
		}

	}
}
void search(Wezel *wezel, int liczba, int nowaL, int k)
{
	int nowaLiczba = nowaL;
	int numerIndeksu;

	if (wezel != NULL)
	{
		if (wezel->wartosc<0)
			{
				printf("%d %s ", liczba, " not exist \n");
			}
			else
			{
				if (wezel->wartosc == liczba)
					printf("%d %s ", liczba, "exist \n");
				else
				{
					//musisz znalezc nowy wezel, wyliczyc nowy index i dodac wartosc
					numerIndeksu = nowaLiczba % wezel->iloscElementow;
					nowaLiczba = nowaLiczba / wezel->iloscElementow;

					search(wezel->wezel[numerIndeksu], liczba, nowaLiczba, k);
				}
			}
	}
	else
	{
		printf("%d %s ", liczba, " not exist \n");
	}
}
void inorder(Wezel *wezel)
{
	if (wezel->wartosc>=0)
	{
		printf("%d ", wezel->wartosc);
		for (int i = 0; i < wezel->iloscElementow; i++)
		{
			if (!wezel->wezel[i] == NULL)
			{
				inorder(wezel->wezel[i]);
			}
		}
	}
}
Wezel *zwrocAdresPierwszegoBezdzietnego(Wezel *wezel)
{
	int i = 0;
	while (i < wezel->iloscElementow)
	{
		if (!wezel->wezel[i] == NULL)
		{
			if (sprawdzamBezdzietnosc(wezel->wezel[i]))
			{
				return wezel->wezel[i];
			}
		}
		i++;

	}
	return NULL;
}

void remove(Wezel *wezel, Wezel *e, int liczba, int nowaL, int k, int numerInd)
{
	int nowaLiczba = nowaL;
	int numerIndeksu, i;

	if (e != NULL)
	{
		//sprawdzam bezdzietnosc, jezeli bezdzietny od razu usuwam
		if (sprawdzamBezdzietnosc(wezel))
		{
			//przypisuje wartosc ostatniego bezdzietnego do szukanego i usuwam ostatniego bezdzietnego
			wezel->rodzic->wezel[numerInd] = NULL;
			e->wartosc = wezel->wartosc;
			wezel->zwolnijPamiec();
			delete wezel;
		}
		else //ma dzieci, przechodze do kolejnego skrajnego lewego dziecka
		{
			i = 0;
			while (i < wezel->iloscElementow)
			{
				if ((!wezel->wezel[i] == NULL) && (wezel->wezel[i]->wartosc>=0) && (wezel->wezel[i]->iloscElementow>=0))
				{
					remove(wezel->wezel[i], e, liczba, nowaL, k, i);
					break;
				}
				i++;
			}
		}
	}
	else
	{
		//szukanie podanego elementu
		if (wezel != NULL)
		{
			if (wezel->wartosc<0)
			{
				printf("%d %s", liczba, " not exist \n");
			}
			else
			{
				if (wezel->wartosc == liczba)
				{
					//sprawdzam bezdzietnosc, jezeli bezdzietny od razu usuwam
					if (sprawdzamBezdzietnosc(wezel))
					{
						wezel->rodzic->wezel[numerInd] = NULL;
						wezel->zwolnijPamiec();
						delete wezel;

					}
					else //ma dzieci, zapamietuje go i od tej pory bede odwolywac sie tylko do jego skrajnego dziecka
					{
						e = wezel;

						i = 0;
						while (i < wezel->iloscElementow)
						{
							if ((!(wezel->wezel[i] == NULL)) && (wezel->wezel[i]->wartosc>=0) && (wezel->wezel[i]->iloscElementow>=0))
							{
								remove(wezel->wezel[i], e, liczba, nowaL, k, i);
								break;
							}
							i++;
						}
					}
				}
				else
				{
					//musisz znalezc nowy wezel, wyliczyc nowy index i dodac wartosc
					numerIndeksu = nowaLiczba % wezel->iloscElementow;
					nowaLiczba = nowaLiczba / wezel->iloscElementow;

					remove(wezel->wezel[numerIndeksu], e, liczba, nowaLiczba, k, numerIndeksu);
				}
			}
	    }
		else
		{
			printf("%d %s", liczba, " not exist \n");
		}
	}

}

int main()
{
	int min, max, n, k, testy, liczba;
	char komenda;
	ifstream plik,o;
	plik.open("2.in");
	plik >> testy;
	plik >> min >> max;
	plik >> n >> k;
	/*scanf("%d", &testy);
	scanf("%d %d", &min, &max);
	scanf("%d %d", &n, &k);
	cin >> testy;
	cin >> min >> max;
	cin >> n >> k;*/
	Wezel *root = new Wezel(n);
	for (int i = 0; i < testy; i++)
	{
		//scanf("%c", &komenda);
		plik >> komenda;
		//cin >> komenda;
		if (komenda != 'P')
			//cin >> liczba;
			//scanf("%d", &liczba);
		    plik >> liczba;
		if (komenda == 'I')
			insert(root, liczba, liczba, k);
		else if (komenda == 'P')
		{
			inorder(root);
			printf("\n");
		}
		else if (komenda == 'L')
			search(root, liczba, liczba, k);
		else if (komenda == 'D')
			remove(root, NULL, liczba, liczba, k, 0);
	}

	delete root;
	getchar();
	getchar();
	return 0;
}

