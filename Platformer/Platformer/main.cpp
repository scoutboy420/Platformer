/** @cond */
#include <SFML/Graphics.hpp>
#include <iostream>
/** @endcond */
#include "Game.h"

int main()
{
	try
	{
		Game game(sf::VideoMode(1280, 720), "Elka Quest");

		while(game.play()) {}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cin.ignore();
	}

	return 0;
}


/*! \mainpage Elka Quest
*
* \section Opis
*
* Celem gry jest dojscie z pomieszczenia poczatkowego do koncowego.
* Aby tego dokonac, gracz musi zbierac klucze, ktore otwieraja drzwi i tym samym umozliwiaja przejscie do kolejnych pomieszczen.
* Utrudnieniem moga byc przeciwnicy i przeszkody porozmieszczane po mapie,
* ktore moga gracza ranic, przeszkadzac w ruchu lub w ostatecznosci zabic.
*
* \section Zalozenia
*
* Cala gra obslugiwana jest przez klase Game. Aktualizuje one wszystkie obiekty, sprawdza kolizje, zmiane pokoi, itd.
* Wszystkie zasoby potrzebne do gry (tekstury, dane z plikow .json, czcionki) znajduja sie w klasie statycznej Resources.
* Wszystkie obiekty w grze dziedzicza z glownej, abstrakcyjnej klasy Entity, przy czym sa jeszcze abstrakcyjne podklasy Entity,
* takie jak MobileEntity czy Enemy, z ktorych powinno dziedziczyc sie, jezeli sa bardziej dopasowane.
* 
* Gra na poczatku tworzy wszystkie pokoje, a kazdy pokoj zawiera obiekty nalezace do danego pokoju,
* na przyklad bloki, klucze, przeszkody. Obiekty, ktore moga sie ruszac i zmieniac pokoje przechowywane sa bezposrednio w Game.
* 
* Jezeli w czasie gry wystapil blad to:
* 1. Jezeli strata nie jest duza lub zapisanie nic nie da to gra sie restartuje i uzytkownik otrzymuje o tym komunikat.
* 2. Jezeli gre mozna zapisac, to zostanie podjeta proba zapisu. 
*    Gra zostaje zakonczona, a w konsoli wyswietla sie komunikat o bledzie i powodzeniu/niepowodzeniu zapisu.
*
*/