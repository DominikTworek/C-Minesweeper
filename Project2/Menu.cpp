#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include <Windows.h>
#include <fstream>
#include "header.h"


void menu::buduj_menu()
{

	RenderWindow app(VideoMode(a * 32,a * 32), L"Gra Saper Dominik Tworek / Adrian Œmiglarski"); //Rysuje okno rozmiar-nazwa
	Font font;
	font.loadFromFile("fonts/2.otf");

	Font fontsaper;
	fontsaper.loadFromFile("fonts/1.ttf");

	const int liczba_menu = 4;
	Text napis[liczba_menu];
	Text napissaper("Gra Saper", fontsaper, 60);
	napissaper.setPosition((a * 32) / 2 - napissaper.getGlobalBounds().width / 2, 0);

	string str[] = { "Start", "Opcje", "Ranking", "Quit" };
	for (int i = 0; i < liczba_menu; i++)
	{
		napis[i].setFont(font);
		napis[i].setCharacterSize(50);

		napis[i].setString(str[i]);
		napis[i].setPosition((a * 32) / 2 - napis[i].getGlobalBounds().width / 2, 70 + i * 50);
	}

	while (sprawdzenie) //dopóki okno jest otwarte 
	{
		Vector2f mouse(Mouse::getPosition(app));
		Event menub; //dajemy zdarzeniu nazwê event
		while (app.pollEvent(menub)) //gdy uda siê pobraæ zdarzenie to zwróci true jeœli nie to false
		{
			if (menub.type == Event::Closed) //wydarzenie do przycisku Esc
			{
				app.close(); //zamyka aplikacjê
				return;
			}
			else if (napis[0].getGlobalBounds().contains(mouse) &&
				menub.type == Event::MouseButtonReleased && menub.key.code == Mouse::Left)
			{
				sprawdzenie = false;
				spr_gra = true;
				app.close();
			}
			else if (napis[1].getGlobalBounds().contains(mouse) &&
				menub.type == Event::MouseButtonReleased && menub.key.code == Mouse::Left)
			{
				sprawdzenie = false;
				spr_opcje = true;
			}
			else if (napis[2].getGlobalBounds().contains(mouse) &&
				menub.type == Event::MouseButtonReleased && menub.key.code == Mouse::Left)
			{
				menu gra_odwolanie_menu;
				sprawdzenie = false;
				spr_ranking = true;
				app.close();
				gra_odwolanie_menu.buduj_ranking();
			}
			else if (napis[3].getGlobalBounds().contains(mouse) &&
				menub.type == Event::MouseButtonReleased && menub.key.code == Mouse::Left)
			{
				sprawdzenie = false;
				app.close();
				return;
			}
		}
		for (int i = 0; i<liczba_menu; i++)
			if (napis[i].getGlobalBounds().contains(mouse))
				napis[i].setFillColor(Color::Cyan);
			else napis[i].setFillColor(Color::White);
				app.clear();
			for (int i = 0; i<liczba_menu; i++)
				app.draw(napis[i]);
		app.draw(napissaper);
		app.display();
		Sleep(60);
	}
}

void menu::buduj_opcje()
{
	Font font;
	font.loadFromFile("fonts/2.otf");

	Font fontsaper;
	fontsaper.loadFromFile("fonts/1.ttf");

	RenderWindow app(VideoMode(a * 32, a * 32), L"Gra Saper Dominik Tworek / Adrian Œmiglarski"); //Rysuje okno rozmiar-nazwa

	Text trd_wys("", font, 50);
	Text a_wys("", font, 50);
	Text napissaper("Gra Saper", fontsaper, 60);
	Text wstawianie_t("Wpisz trudnosc(1-3)", font, 20);
	Text wstawianie_a("Wpisz rozmiar gry(3-9)", font, 20);

	string trd;

	wstawianie_t.setPosition((a * 32) / 2 - wstawianie_t.getGlobalBounds().width / 2, 75);
	wstawianie_a.setPosition((a * 32) / 2 - wstawianie_a.getGlobalBounds().width / 2, 75);
	napissaper.setPosition((a * 32) / 2 - napissaper.getGlobalBounds().width / 2, 0);

	while (spr_opcje) //dopóki okno jest otwarte 
	{
		Vector2f mouse(Mouse::getPosition(app));
		Event opcje; //dajemy zdarzeniu nazwê event
		while (app.pollEvent(opcje)) //gdy uda siê pobraæ zdarzenie to zwróci true jeœli nie to false
		{
			if (opcje.type == Event::Closed) //wydarzenie do przycisku X
			{
				app.close(); //zamyka aplikacjê
				return ;
			}
		}

		if (opcje.type == Event::KeyReleased && opcje.key.code == Keyboard::Return)
		{
			trudnosc = stoi(trd);
			if (trudnosc == 1 || trudnosc == 2 || trudnosc == 3)
			{
				spr_opcje2 = true;
				spr_opcje = false;
			}
			else
			{
				trd_wys.setCharacterSize(20);
				trd_wys.setString("wpisales zla wartosc. wpisz jeszcze raz");
				trd_wys.setPosition((a * 32) / 2 - trd_wys.getGlobalBounds().width / 2, 95);
			}
		}
		else if (opcje.type == Event::TextEntered)
		{
			if (opcje.text.unicode == 8) //backspace
			{
				if (trd.size() > 0)
					trd.erase(trd.size() - 1, 1);
			}
			else if (opcje.text.unicode < 128 && opcje.text.unicode != 13)
				trd = (char)opcje.text.unicode;

			trd_wys.setString(trd);
			trd_wys.setPosition((a * 32) / 2 - trd_wys.getGlobalBounds().width / 2, 95);
		}
		app.clear();
		app.draw(napissaper);
		app.draw(wstawianie_t);
		app.draw(trd_wys);
		app.display();
		Sleep(60);
	}

	while (spr_opcje2) //dopóki okno jest otwarte 
	{
		Vector2f mouse(Mouse::getPosition(app));
		Event opcje2; //dajemy zdarzeniu nazwê event
		while (app.pollEvent(opcje2)) //gdy uda siê pobraæ zdarzenie to zwróci true jeœli nie to false
		{
			if (opcje2.type == Event::Closed) //wydarzenie do przycisku X
			{
				app.close(); //zamyka aplikacjê
				return ;
			}
			if (opcje2.type == Event::KeyReleased && opcje2.key.code == Keyboard::Return)
			{
				a = stoi(trd);
				if (a >= 3 && a <= 9)
				{
					if (a == 5)
					{
						a = a * 2 + 1;
						spr_opcje2 = false;
						spr_gra = true;
						app.close();
					}
					else
					{
						a = a * 2;
						spr_opcje2 = false;
						spr_gra = true;
						app.close();
					}

				}
				else
				{
					a_wys.setCharacterSize(20);
					a_wys.setString("wpisales zla wartosc. wpisz jeszcze raz");
					a_wys.setPosition((15 * 32) / 2 - a_wys.getGlobalBounds().width / 2, 95);
				}

			}
		}

		if (opcje2.type == Event::TextEntered)
		{
			if (opcje2.text.unicode == 8) //backspace
			{
				if (trd.size() > 0)
					trd.erase(trd.size() - 1, 1);
			}
			else if (opcje2.text.unicode < 128 && opcje2.text.unicode != 13)
				trd = (char)opcje2.text.unicode;

			a_wys.setString(trd);
			a_wys.setPosition((15 * 32) / 2 - a_wys.getGlobalBounds().width / 2, 95);
		}
		app.clear();
		app.draw(napissaper);
		app.draw(wstawianie_a);
		app.draw(a_wys);
		app.display();
		Sleep(10);
	}
}

void menu::buduj_ranking()
{
	RenderWindow app(VideoMode(a * 32, a * 32), L"Grvdrfa Saper Dominik Tworek / Adrian Œmiglarski"); //Rysuje okno rozmiar-nazwa

	Font font;
	font.loadFromFile("fonts/2.otf");

	Font fontsaper;
	fontsaper.loadFromFile("fonts/1.ttf");

	plik.open("ranking.txt", ios::in);

	if (plik.good() == true) //jeœli plik istnieje to wczytuje dane z pliku do tablic
	{
		while (!(plik.eof()))
		{
			plik >> punkty_odczyt[wskaznik_tablicy];
			plik >> nick_odczyt[wskaznik_tablicy];
			wskaznik_tablicy = wskaznik_tablicy + 1;
		}
		plik.close();
	}
	punkty_odczyt[0] = { "Punkty" };
	nick_odczyt[0] = { "Nick" };
	for (int i = 1; i < 2000; i++)//sortowanie tablic
		for (int j = 1; j < 2000 - 1; j++)
			if (punkty_odczyt[j] < punkty_odczyt[j + 1])
			{
				swap(punkty_odczyt[j], punkty_odczyt[j + 1]);
				swap(nick_odczyt[j], nick_odczyt[j + 1]);
			}

	Text napissaper("Gra Saper", fontsaper, 60);
	napissaper.setPosition((a * 32) / 2 - napissaper.getGlobalBounds().width / 2, 0);
	Text wroc("Wroc do menu", font, 25);
	wroc.setPosition((a * 32) / 2 - wroc.getGlobalBounds().width / 2, 260);
	const int liczba_ranking = 6;
	Text miejsce[liczba_ranking];
	Text punkty_text[liczba_ranking];
	Text nick_text[liczba_ranking];
	string podium[] = { "Lp.", "1.", "2.", "3.", "4.", "5." };
	for (int i = 0; i < liczba_ranking; i++)
	{
		miejsce[i].setFont(font);
		miejsce[i].setCharacterSize(25);

		miejsce[i].setString(podium[i]);
		miejsce[i].setPosition((a * 32) / 6 + 50 - miejsce[i].getGlobalBounds().width, 70 + i * 25);
	}

	for (int i = 0; i < liczba_ranking; i++)
	{
		punkty_text[i].setFont(font);
		punkty_text[i].setCharacterSize(25);
		if (punkty_odczyt[i] == "")
			punkty_text[i].setString("brak");
		else
			punkty_text[i].setString(punkty_odczyt[i]);
		punkty_text[i].setPosition((a * 32) / 4 + 50 - miejsce[i].getGlobalBounds().width / 10, 70 + i * 25);
	}

	for (int i = 0; i < liczba_ranking; i++)
	{
		nick_text[i].setFont(font);
		nick_text[i].setCharacterSize(25);
		if (nick_odczyt[i] == "")
			nick_text[i].setString("brak");
		else
			nick_text[i].setString(nick_odczyt[i]);
		nick_text[i].setPosition((a * 32) / 2 + 50 - miejsce[i].getGlobalBounds().width / 10, 70 + i * 25);
	}

	while (spr_ranking) //dopóki okno jest otwarte 
	{
		Event ranking; //dajemy zdarzeniu nazwê event
		Vector2f mouse(Mouse::getPosition(app));
		while (app.pollEvent(ranking)) //gdy uda siê pobraæ zdarzenie to zwróci true jeœli nie to false
		{
			if (ranking.type == Event::Closed) //wydarzenie do przycisku Esc
			{
				app.close(); //zamyka aplikacjê
				return;
			}
			else if (wroc.getGlobalBounds().contains(mouse) &&
				ranking.type == Event::MouseButtonReleased && ranking.key.code == Mouse::Left)
			{
				menu gra_odwolanie_menu;
				spr_ranking = false;
				sprawdzenie = true;
				app.close();
				gra_odwolanie_menu.buduj_menu();
			}
		}
		app.clear();
		app.draw(napissaper);
		for (int i = 0; i<liczba_ranking; i++)
			app.draw(miejsce[i]);
		for (int i = 0; i<liczba_ranking; i++)
			app.draw(punkty_text[i]);
		for (int i = 0; i<liczba_ranking; i++)
			app.draw(nick_text[i]);
		app.draw(wroc);
		app.display();
		Sleep(10);
	}
}

