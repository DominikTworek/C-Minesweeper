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
	@param std  deklarujemy przestrzeñ nazw std. importuje wszystkie identyfikatory z przestrzeni nazw std
	@param sf  deklarujemy przestrzeñ nazw std. importuje wszystkie identyfikatory z przestrzeni nazw sf
*/
using namespace std;
using namespace sf;
/*!
	* \brief Deklarowanie klasy o nazwie "menu" w której znajduj¹ siê wszystkie metody oraz zmienne, które nale¿¹ do menu(opcje/ranking)
    @param trudnosc	Zmienna, przy której ustawiamy w opcjach gry poziom trudnoœci sapera
    @param a	Zmienna, Jest to zmienna deklaruj¹ca rozmiar okna (a*32)
    @param spr_gra	Zmienna typu Bool sprawdzaj¹ca czy gra jest w³¹czona
	@param sprawdzenie	Zmienna typu Bool sprawdzaj¹ca czy okno menu jest w³¹czone
	@param spr_ranking	Zmienna typu Bool sprawdzaj¹ca czy okno ranking jest w³¹czone
	@param plik	Klasa ta udostêpnia nam ca³y interfejs, dziêki któremu bêdziemy mogli obs³u¿yæ dowolny plik znajduj¹cy siê na dysku lub innym noœniku danych
	@param punkty_odczyt	Tablica, do której bêdziemy zapisywaæ odczytane punkty z pliku tekstowego(zastosowanie w rankingu)
	@param nick_odczyt	Tablica, do której bêdziemy zapisywaæ odczytane nicki z pliku tekstowego(zastosowanie w rankingu)
	@param l_p	Zmienna, której u¿ywamy w rankingu do wyœwietlania liczby pojedyñczej
	@param wskaznik_tablicy	Zmienna, dziêki której bêdziemy wskazywaæ miejsce w tablicy z jakiego mamy odczytaæ dane
	@param spr_opcje	Zmienna typu Bool sprawdzaj¹ca czy okno opcje(trudnosc) jest w³¹czone
	@param spr_opcje	Zmienna typu Bool sprawdzaj¹ca czy okno opcje(trudnosc) jest w³¹czone
	@param spr_opcje2	Zmienna typu Bool sprawdzaj¹ca czy okno opcje(rozmiar) jest w³¹czone
*/

class menu
{
public:
	/*!
		*\brief Metoda, która tworzy okno menu
		*W menu znajduj¹ siê 4 przyciski. \n
		*1.Start - Gra zostaje uruchomiona z domyœlnymi wartoœciami (trudnoœæ 1/rozmiar planszy 15x15)
		*2.Opcje - Tutaj znajduj¹ siê wszystkie opcje zwi¹zane z gr¹
		*3.Ranking - Wyœwietlanie graczy, którzy zajêli 5 pierwszych miejscach
		*4.Quit - Wyjœcie z menu
	*/
	void buduj_menu(); 
	/*!
		*\brief Metoda, która tworzy okno opcji
		*w tej metodzie u¿ytkownik podaje rozmiar planszy oraz trudnosc gry. W zale¿noœci od rozmiaru i trudnoœci gry u¿ytkownik mo¿e zdobyæ wiêcej punktów.
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
	*\brief Deklarowanie klasy o nazwie "gra" w której znajduj¹ siê wszystkie metody oraz zmienne, które nale¿¹ do okna gry(klasa dziedziczy zmienne z klasy menu)
	@param spr_przegrana	Zmienna typu Bool sprawdzaj¹ca czy okno przegranej jest w³¹czone
	@param spr_wygrana	Zmienna typu Bool sprawdzaj¹ca czy okno wygranej jest w³¹czone
	@param punkty	Zmienna, której u¿ywamy do zliczania punktów za dobrze zaznaczone bomby
	@param **siatkap	Podwójny wskaŸnik na tablicê. Tablica ta s³u¿y do umieszczania pól po naciœniêciu klawisza na myszce
	@param **siatka	Podwójny wskaŸnik na tablicê. Tablica ta s³u¿y do umieszczania pól przed naciœniêciu klawisza na myszce
	@param wielkosc	Zmienna pomocnicza, u¿ywamy jej gdy chcemy u¿yæ rozmiaru jednej kratki w grze
	@param trafione	Zmienna zliczaj¹ca iloœæ trafionych bomb
	@param zle_trafione	Zmienna zliczaj¹ca iloœæ Ÿle trafionych bomb
	@param muzyka	Kostruktor potrzebny do zadeklarowania muzyki
	@param bomba	Kostruktor potrzebny do zadeklarowania odg³osu wybuchu bomby
*/

class gra: public menu
{
public:
	/*!
		*\brief Metoda, która alokuje pamiêæ na potrzeby gry
	*/
	void alokowanie_pamieci(); 
	/*!
		*\brief Metoda, która dodaje bomby na planszê.
		*W metodzie u¿yty jest operator rand, który w zale¿noœci od poziomu trudnoœci generuje losowo iloœæ bomb w losowych miejscach.
	*/
	void dodaj_bomby();
	/*!
		*\brief Metoda ta jest przeznaczona do tworzenia i funkcjonalnoœci gry \n
		*Jeœli pojawi siê bomba na planszy to ta metoda najpierw sprawdza czy wystêpuje bomba. 
		*Ustawia odpowiedni¹ liczbê w zale¿noœci od iloœci bomb s¹siaduj¹cych z t¹ liczb¹.
	*/
	void dodaj_liczby(); 
	/*!
		*\brief Metoda ta jest przeznaczona do tworzenia i funkcjonalnoœci gry \n
		*Tworzenie okna gry jest podzielone na kilka etapów. \n
		*1.Wczytujemy wszystkie pliki muzyczne/graficzne \n
		*2.Renderujemy grafikê na planszy \n
		*3.Ustawiamy po³o¿enie myszki \n
		*4.Ustawiamy wszystkie akcje po naciœniêciu wybranych przycisków z myszki/klawiatury \n
		*5.Zliczamy punkty/iloœæ trafinonych bomb/iloœæ Ÿle trafionych bomb \n
		*6.Jeœli iloœæ trafionych bomb jest równa iloœci bomb na planszy otwiera nam nowe okno wygranej \n
	*/
	void buduj_gre(); 
	/*!
		*\brief Metoda zwalniaj¹ca pamiêæ
		*Wczeœniej deklarowaliœmy pamiêæ wiêc teraz nale¿y j¹ zwolniæ. Do tego u¿ywamy operatora <delete>
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
	///Metoda w której tworzymy okno koñcowe po przegranej
	void okno_wygrana();
	/*!
		*\brief Metoda w której tworzymy okno koñcowe po wygranej
		*Sprawdzany jest zmienna spr_przegrana. Jeœli jest true to okno siê w³¹czy jeœli false to nie.
		*W tej metodzie wyœwietlamy napisy oraz pole, gdzie wpisujemy nasz wymyœlony nick. Jest on zapisywany do pliku jak i iloœæ punktów.
	*/
	void okno_przegrana(); 
};
/*!
	*\brief Deklarowanie klasy o nazwie "wywolanie"(klasa dziedziczy zmienne z klasy "gra")
*/
class wywolanie : public gra
{
public:
	///Metoda która wywo³uje wszystkie inne metody
	void wywolania(); 
};