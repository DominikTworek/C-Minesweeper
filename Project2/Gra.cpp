#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include <Windows.h>
#include "header.h"
/*!
* \brief Funkcja ta alokuje pamiêæ na potrzeby gry
*/
void gra::alokowanie_pamieci()
{
	for (int i = 0; i <= a + 98; i++)
	{
		siatkap[i] = new int[a + 98]; //alokujemy pamiêæ
		siatka[i] = new int[a + 98]; //alokujemy pamiêæ
	}
}


void gra::dodaj_bomby()
{
	srand((unsigned int)time(NULL));
	for (int i = 1; i <= a; i++) //dodawanie pustych i bomb na plansze
	{
		for (int j = 1; j <= a; j++)
		{
			siatkap[i][j] = a;
			if (trudnosc == 1)
			{
				if (rand() % 9 == 0)
				{
					siatka[i][j] = a - 1;
				}
				else siatka[i][j] = a - 10;
			}
			if (trudnosc == 2)
			{
				if (rand() % 6 == 0)
				{
					siatka[i][j] = a - 1;
				}
				else siatka[i][j] = a - 10;
			}
			if (trudnosc == 3)
			{
				if (rand() % 4 == 0)
				{
					siatka[i][j] = a - 1;
				}
				else siatka[i][j] = a - 10;
			}
		}
	}
}


void gra::dodaj_liczby()
{
	for (int i = 1; i <= a; i++) //ustalanie liczby <1-8> przy bombach
		for (int j = 1; j <= a; j++)
		{
			int n = a - 10;
			if (siatka[i][j] == a - 1) continue;
			if (siatka[i + 1][j] == a - 1) n++;
			if (siatka[i][j + 1] == a - 1) n++;
			if (siatka[i - 1][j] == a - 1) n++;
			if (siatka[i][j - 1] == a - 1) n++;
			if (siatka[i + 1][j + 1] == a - 1) n++;
			if (siatka[i - 1][j - 1] == a - 1) n++;
			if (siatka[i - 1][j + 1] == a - 1) n++;
			if (siatka[i + 1][j - 1] == a - 1) n++;
			siatka[i][j] = n;
		}
}


void gra::buduj_gre()
{
	RenderWindow app2(VideoMode(a * 32, a * 32), L"Gra Saper Dominik Tworek / Adrian Œmiglarski", 1); //Rysuje okno rozmiar-nazwa
	Texture tekstura; //dodajemy teksturê do okno o nazwie 'tekstura'
	tekstura.loadFromFile("images/tiles.jpg"); //dodajemy Ÿród³o do tekstury
	Sprite s(tekstura); //tworzymy tak jakby div w css
	muzyka.openFromFile("music/1.ogg");
	bomba.openFromFile("music/2.ogg");
	muzyka.play();
	int bomby = 0;
	for (int i = 1; i <= a; i++) //Zliczanie wszystkich bomb na planszy
		for (int j = 1; j <= a; j++)
		{
			if (siatka[i][j] == a - 1)
				bomby++;
		}


	while (spr_gra) //dopóki okno jest otwarte 
	{
		Vector2i pos = Mouse::getPosition(app2); //Przechowuje po³o¿enie myszki w x/y. Vector2i oznacza, ¿e bêdzie pobiera³o w int natomiast vestor2f we float;

		int x = pos.x / wielkosc;
		int y = pos.y / wielkosc;
		app2.clear(Color::Cyan); //ustawiamy kolor dla okna
		Event saper; //dajemy zdarzeniu nazwê event
		while (app2.pollEvent(saper)) //gdy uda siê pobraæ zdarzenie to zwróci true jeœli nie to false
		{
			if (saper.type == Event::Closed) //wydarzenie do przycisku X
			{
				app2.close(); //zamyka aplikacjê
				return;
			}
			if (saper.type == Event::KeyPressed && saper.key.code == Keyboard::Escape)
			{
				app2.close();
				return;
			}

			if (saper.type == Event::MouseButtonPressed)
				if (saper.key.code == Mouse::Right) ///prawy przycisk myszki
				{
					if (siatkap[x + 1][y + 1] == a + 1) ///jeœli jest zaznaczone to odznacza
						siatkap[x + 1][y + 1] = a;
					else if (siatkap[x + 1][y + 1] == a) ///jeœli nie jest zaznaczone to zaznacza
						siatkap[x + 1][y + 1] = a + 1;
				}
			if (saper.type == Event::KeyPressed && saper.key.code == Keyboard::Return)
			{
				spr_gra = false;
				spr_przegrana = true;
				punkty = 0;
			}
		}


		if (saper.type == Event::MouseButtonPressed)
			if (saper.key.code == Mouse::Left)
			{
				siatkap[x + 1][y + 1] = siatka[x + 1][y + 1];
				if (siatkap[x + 1][y + 1] == a - 1)
				{
					bomba.play();
					muzyka.pause();
				}
			}
		if (saper.type == Event::MouseButtonPressed)
			if (saper.key.code == Mouse::Left)
				for (x = 1; x <= a; x++)
					for (y = 1; y <= a; y++)
						if (siatkap[x + 1][y + 1] == a - 10)
						{
							siatkap[x + 2][y + 2] = siatka[x + 2][y + 2];
							siatkap[x + 2][y + 1] = siatka[x + 2][y + 1];
							siatkap[x + 1][y + 2] = siatka[x + 1][y + 2];
							siatkap[x][y] = siatka[x][y];
							siatkap[x + 1][y] = siatka[x + 1][y];
							siatkap[x][y + 1] = siatka[x][y + 1];
							siatkap[x][y + 2] = siatka[x][y + 2];
							siatkap[x + 2][y] = siatka[x + 2][y];
						}


		int b = (a - 10) * 32;
		for (int i = 1; i <= a; i++)
			for (int j = 1; j <= a; j++)
			{
				s.setTextureRect(IntRect(siatkap[i][j] * wielkosc - b, 0, 32, 32));
				s.setPosition((i*wielkosc) - 32, (j*wielkosc) - 32); //jedno okienko ma 32x32 dlatego te¿ dajemy *w dla x/y w tym przypadku dla petli i/j
				app2.draw(s);
			}

		for (int i = 1; i <= a; i++)
			for (int j = 1; j <= a; j++)
			{
				if (siatkap[x + 1][y + 1] == a - 1)
				{
					siatkap[i][j] = siatka[i][j]; //jesli natrafimy na bombe to pokazuje cala plansze
				}
			}

		if (saper.key.code == Mouse::Right) //Zliczanie trafionych i nietrafionych bomb
		{
			trafione = 0;
			zle_trafione = 0;
			for (int i = 1; i <= a; i++)
				for (int j = 1; j <= a; j++)
				{
					if (siatka[i][j] == a - 1 && siatkap[i][j] == a + 1)
						trafione++;
					else if (siatka[i][j] != a - 1 && siatkap[i][j] == a + 1)
						zle_trafione++;
				}
		}


		if (trafione == bomby)
		{
			muzyka.pause();
			//app2.close(); //Wygrana!!
			spr_gra = false;
			punkty = trafione * trudnosc;
			spr_wygrana = true;
		}

		app2.display();
		Sleep(1);
	}
}


void gra::zwalnianie_pamieci()
{
	for (int i = 0; i <= a + 98; i++) //zwalnianie pamiêci
	{
		delete[] siatkap[i]; //uwolnienie pamiec
		delete[] siatka[i]; //uwolnienie pamiec
	}
	delete[] siatkap; //uwolnienie pamiec
	delete[] siatka; //uwolnienie pamiec

	siatka = NULL;
	siatkap = NULL;
}