#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include <Windows.h>
#include "header.h"


void wywolanie::wywolania()
{
	okna_koncowe gra_odwolanie;
	gra_odwolanie.buduj_menu();
	gra_odwolanie.buduj_ranking();
	gra_odwolanie.buduj_opcje();
	gra_odwolanie.alokowanie_pamieci();
	gra_odwolanie.dodaj_bomby();
	gra_odwolanie.dodaj_liczby();
	gra_odwolanie.buduj_gre();
	gra_odwolanie.zwalnianie_pamieci();
	gra_odwolanie.okno_wygrana();
	gra_odwolanie.okno_przegrana();

}