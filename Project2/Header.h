#pragma once

#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

/*!
	@param std  deklarujemy przestrze� nazw std. importuje wszystkie identyfikatory z przestrzeni nazw std
	@param sf  deklarujemy przestrze� nazw std. importuje wszystkie identyfikatory z przestrzeni nazw sf
*/
using namespace std;
using namespace sf;
/*!
	* \brief Deklarowanie klasy o nazwie "menu" w kt�rej znajduj� si� wszystkie metody oraz zmienne, kt�re nale�� do menu(opcje/ranking)
    @param trudnosc	Zmienna, przy kt�rej ustawiamy w opcjach gry poziom trudno�ci sapera
    @param a	Zmienna, Jest to zmienna deklaruj�ca rozmiar okna (a*32)
    @param spr_gra	Zmienna typu Bool sprawdzaj�ca czy gra jest w��czona
	@param sprawdzenie	Zmienna typu Bool sprawdzaj�ca czy okno menu jest w��czone
	@param spr_ranking	Zmienna typu Bool sprawdzaj�ca czy okno ranking jest w��czone
	@param plik	Klasa ta udost�pnia nam ca�y interfejs, dzi�ki kt�remu b�dziemy mogli obs�u�y� dowolny plik znajduj�cy si� na dysku lub innym no�niku danych
	@param punkty_odczyt	Tablica, do kt�rej b�dziemy zapisywa� odczytane punkty z pliku tekstowego(zastosowanie w rankingu)
	@param nick_odczyt	Tablica, do kt�rej b�dziemy zapisywa� odczytane nicki z pliku tekstowego(zastosowanie w rankingu)
	@param l_p	Zmienna, kt�rej u�ywamy w rankingu do wy�wietlania liczby pojedy�czej
	@param wskaznik_tablicy	Zmienna, dzi�ki kt�rej b�dziemy wskazywa� miejsce w tablicy z jakiego mamy odczyta� dane
	@param spr_opcje	Zmienna typu Bool sprawdzaj�ca czy okno opcje(trudnosc) jest w��czone
	@param spr_opcje	Zmienna typu Bool sprawdzaj�ca czy okno opcje(trudnosc) jest w��czone
	@param spr_opcje2	Zmienna typu Bool sprawdzaj�ca czy okno opcje(rozmiar) jest w��czone
*/

class menu
{
public:
	/*!
		*\brief Metoda, kt�ra tworzy okno menu
		*W menu znajduj� si� 4 przyciski. \n
		*1.Start - Gra zostaje uruchomiona z domy�lnymi warto�ciami (trudno�� 1/rozmiar planszy 15x15)
		*2.Opcje - Tutaj znajduj� si� wszystkie opcje zwi�zane z gr�
		*3.Ranking - Wy�wietlanie graczy, kt�rzy zaj�li 5 pierwszych miejscach
		*4.Quit - Wyj�cie z menu
	*/
	void buduj_menu(); 
	/*!
		*\brief Metoda, kt�ra tworzy okno opcji
		*w tej metodzie u�ytkownik podaje rozmiar planszy oraz trudnosc gry. W zale�no�ci od rozmiaru i trudno�ci gry u�ytkownik mo�e zdoby� wi�cej punkt�w.
	*/
	void buduj_opcje(); 
	///Metoda przeznaczona do tworzenia okna ranking
	void buduj_ranking(); 
public:
	int trudnosc = 1;
	int a = 15;
	bool spr_gra = false;
	bool sprawdzenie = true;
	bool spr_ranking = false;

private:
	fstream plik;
	string punkty_odczyt[2000];
	string nick_odczyt[2000];
	int l_p = 1;
	int wskaznik_tablicy = 1;
	bool spr_opcje = false;
	bool spr_opcje2 = false;
};
/*!
	*\brief Deklarowanie klasy o nazwie "gra" w kt�rej znajduj� si� wszystkie metody oraz zmienne, kt�re nale�� do okna gry(klasa dziedziczy zmienne z klasy menu)
	@param spr_przegrana	Zmienna typu Bool sprawdzaj�ca czy okno przegranej jest w��czone
	@param spr_wygrana	Zmienna typu Bool sprawdzaj�ca czy okno wygranej jest w��czone
	@param punkty	Zmienna, kt�rej u�ywamy do zliczania punkt�w za dobrze zaznaczone bomby
	@param **siatkap	Podw�jny wska�nik na tablic�. Tablica ta s�u�y do umieszczania p�l po naci�ni�ciu klawisza na myszce
	@param **siatka	Podw�jny wska�nik na tablic�. Tablica ta s�u�y do umieszczania p�l przed naci�ni�ciu klawisza na myszce
	@param wielkosc	Zmienna pomocnicza, u�ywamy jej gdy chcemy u�y� rozmiaru jednej kratki w grze
	@param trafione	Zmienna zliczaj�ca ilo�� trafionych bomb
	@param zle_trafione	Zmienna zliczaj�ca ilo�� �le trafionych bomb
	@param muzyka	Kostruktor potrzebny do zadeklarowania muzyki
	@param bomba	Kostruktor potrzebny do zadeklarowania odg�osu wybuchu bomby
*/

class gra: public menu
{
public:
	/*!
		*\brief Metoda, kt�ra alokuje pami�� na potrzeby gry
	*/
	void alokowanie_pamieci(); 
	/*!
		*\brief Metoda, kt�ra dodaje bomby na plansz�.
		*W metodzie u�yty jest operator rand, kt�ry w zale�no�ci od poziomu trudno�ci generuje losowo ilo�� bomb w losowych miejscach.
	*/
	void dodaj_bomby();
	/*!
		*\brief Metoda ta jest przeznaczona do tworzenia i funkcjonalno�ci gry \n
		*Je�li pojawi si� bomba na planszy to ta metoda najpierw sprawdza czy wyst�puje bomba. 
		*Ustawia odpowiedni� liczb� w zale�no�ci od ilo�ci bomb s�siaduj�cych z t� liczb�.
	*/
	void dodaj_liczby(); 
	/*!
		*\brief Metoda ta jest przeznaczona do tworzenia i funkcjonalno�ci gry \n
		*Tworzenie okna gry jest podzielone na kilka etap�w. \n
		*1.Wczytujemy wszystkie pliki muzyczne/graficzne \n
		*2.Renderujemy grafik� na planszy \n
		*3.Ustawiamy po�o�enie myszki \n
		*4.Ustawiamy wszystkie akcje po naci�ni�ciu wybranych przycisk�w z myszki/klawiatury \n
		*5.Zliczamy punkty/ilo�� trafinonych bomb/ilo�� �le trafionych bomb \n
		*6.Je�li ilo�� trafionych bomb jest r�wna ilo�ci bomb na planszy otwiera nam nowe okno wygranej \n
	*/
	void buduj_gre(); 
	/*!
		*\brief Metoda zwalniaj�ca pami��
		*Wcze�niej deklarowali�my pami�� wi�c teraz nale�y j� zwolni�. Do tego u�ywamy operatora <delete>
	*/
	void zwalnianie_pamieci(); 
public:
	bool spr_przegrana = false;
	bool spr_wygrana = false;
	int punkty = 0;
private:
	int **siatkap = new int *[a + 200];
	int **siatka = new int *[a + 200];
	int wielkosc = 32;
	int trafione = 0;
	int zle_trafione = 0;
	Music muzyka;
	Music bomba;
};

/*!
	*\brief Deklarowanie klasy o nazwie "okna_koncowe"(klasa dziedziczy zmienne z klasy "gra")
*/
class okna_koncowe : public gra
{
public:
	///Metoda w kt�rej tworzymy okno ko�cowe po przegranej
	void okno_wygrana();
	/*!
		*\brief Metoda w kt�rej tworzymy okno ko�cowe po wygranej
		*Sprawdzany jest zmienna spr_przegrana. Je�li jest true to okno si� w��czy je�li false to nie.
		*W tej metodzie wy�wietlamy napisy oraz pole, gdzie wpisujemy nasz wymy�lony nick. Jest on zapisywany do pliku jak i ilo�� punkt�w.
	*/
	void okno_przegrana(); 
};
/*!
	*\brief Deklarowanie klasy o nazwie "wywolanie"(klasa dziedziczy zmienne z klasy "gra")
*/
class wywolanie : public gra
{
public:
	///Metoda kt�ra wywo�uje wszystkie inne metody
	void wywolania(); 
};