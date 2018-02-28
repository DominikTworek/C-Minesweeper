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



void okna_koncowe::okno_wygrana()
{
	RenderWindow okienko_wygrana(VideoMode(480, 480), L"Gra Saper Dominik Tworek / Adrian Œmiglarski"); //Rysuje okno rozmiar-nazwa
	Font font;
	font.loadFromFile("fonts/2.otf");

	Font fontsaper;
	fontsaper.loadFromFile("fonts/1.ttf");


	Text napis_wpisz_nick("Wpisz swoj nick i zatwierdz [ENTER]", font, 15);
	napis_wpisz_nick.setPosition(480 / 2 - napis_wpisz_nick.getGlobalBounds().width / 2, 175);

	std::string punkty_str = std::to_string(punkty);
	Text punkty_wys("", font, 25);
	punkty_wys.setString(punkty_str);
	punkty_wys.setPosition(480 / 2 - punkty_wys.getGlobalBounds().width / 2, 145);

	Text napis_punkty("Twoja Liczba punktow to", font, 30);
	napis_punkty.setPosition(480 / 2 - napis_punkty.getGlobalBounds().width / 2, 115);

	Text wygrana_napis("Wygrales!!!!", font, 40);
	wygrana_napis.setPosition(480 / 2 - wygrana_napis.getGlobalBounds().width / 2, 75);
	wygrana_napis.setFillColor(Color::Green);

	Text napissaper("Gra Saper", fontsaper, 60);
	napissaper.setPosition(480 / 2 - napissaper.getGlobalBounds().width / 2, 0);

	Text nick_pole;
	nick_pole.setString("Nick:");
	nick_pole.setFillColor(Color::White);
	nick_pole.setCharacterSize(30);
	nick_pole.setPosition(480 / 2 - 100 / 2, 205);
	nick_pole.setFont(font);

	string nick;
	ofstream zapis("ranking.txt", ios::out | ios::app);//obiekt tworzymy tylko raz

	while (spr_wygrana) //dopóki okno jest otwarte 
	{
		Event wygrana; //dajemy zdarzeniu nazwê event
		while (okienko_wygrana.pollEvent(wygrana)) //gdy uda siê pobraæ zdarzenie to zwróci true jeœli nie to false
		{
			if (wygrana.type == Event::Closed) //wydarzenie do przycisku X
			{
				okienko_wygrana.close(); //zamyka aplikacjê
				return;
			}
			if (wygrana.type == Event::KeyPressed && wygrana.key.code == Keyboard::Escape)
			{
				okienko_wygrana.close();
				return;
			}
			if (wygrana.type == Event::TextEntered)
			{
				if (wygrana.text.unicode == 8) //backspace
				{
					if (nick.size() > 0)
						nick.erase(nick.size() - 1, 1);
				}
				else if (wygrana.text.unicode == 13) //enter
				{
					zapis << "\n" << punkty << "\n";
					zapis << nick;
					zapis.close(); //zamykamy plik
					return;
				}
				else
					nick += char(wygrana.text.unicode);
			}
			nick_pole.setString(nick);
		}
		okienko_wygrana.clear();
		okienko_wygrana.draw(nick_pole);
		okienko_wygrana.draw(napis_wpisz_nick);
		okienko_wygrana.draw(napissaper);
		okienko_wygrana.draw(wygrana_napis);
		okienko_wygrana.draw(punkty_wys);
		okienko_wygrana.draw(napis_punkty);
		okienko_wygrana.display();
		Sleep(60);
	}
}


void okna_koncowe::okno_przegrana()
{
	RenderWindow okienko_przegrana(VideoMode(480, 480), L"Gra Saper Dominik Tworek / Adrian Œmiglarski"); //Rysuje okno rozmiar-nazwa

	Font font;
	font.loadFromFile("fonts/2.otf");

	Font fontsaper;
	fontsaper.loadFromFile("fonts/1.ttf");

	std::string punkty_str = std::to_string(punkty);
	Text punkty_wys("", font, 25);
	punkty_wys.setString(punkty_str);
	punkty_wys.setPosition(480 / 2 - punkty_wys.getGlobalBounds().width / 2, 145);

	Text napis_punkty("Twoja Liczba punktow to", font, 30);
	napis_punkty.setPosition(480 / 2 - napis_punkty.getGlobalBounds().width / 2, 115);

	Text przegrana_napis("Przegrales :(", font, 40);
	przegrana_napis.setPosition(480 / 2 - przegrana_napis.getGlobalBounds().width / 2, 75);
	przegrana_napis.setFillColor(Color::Red);

	Text napissaper("Gra Saper", fontsaper, 60);
	napissaper.setPosition(480 / 2 - napissaper.getGlobalBounds().width / 2, 0);
	while (spr_przegrana) //dopóki okno jest otwarte 
	{
		Event przegrana; //dajemy zdarzeniu nazwê event
		while (okienko_przegrana.pollEvent(przegrana)) //gdy uda siê pobraæ zdarzenie to zwróci true jeœli nie to false
		{
			if (przegrana.type == Event::Closed) //wydarzenie do przycisku X
			{
				okienko_przegrana.close(); //zamyka aplikacjê
				return;
			}
			if (przegrana.type == Event::KeyPressed && przegrana.key.code == Keyboard::Escape)
			{
				okienko_przegrana.close();
				return;
			}
		}

		okienko_przegrana.clear();
		okienko_przegrana.draw(napissaper);
		okienko_przegrana.draw(przegrana_napis);
		okienko_przegrana.draw(punkty_wys);
		okienko_przegrana.draw(napis_punkty);
		okienko_przegrana.display();
		Sleep(60);
	}
};